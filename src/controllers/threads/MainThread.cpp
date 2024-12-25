#include <algorithm>
#include <csignal>
#include <controllers/threads/MainThread.hpp>
#include <models/MdnsResourceRecord.hpp>
#include <protocols/MdnsMessage.hpp>
#include <protocols/resource-record-payload/ResourceRecordAPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordPtrPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordSrvPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordTxtPayload.hpp>
#include <protocols/ByteArray.hpp>
#include <utils/Log.hpp>

MainThread::MainThread(const CommandlineArguments& arguments):
    m_arguments(arguments)
{
}

MainThread::~MainThread()
{
}

void MainThread::run(void)
{
    m_mdnsReceiver.open(m_arguments.inInterface, mDnsAddress, mDnsPort);
    m_mdnsInQueryTransmitter.open(m_arguments.inInterface);
    for (auto& outInterface: m_arguments.outInterfaces)
    {
        auto mdnsOutReplyTransmitter = std::make_unique<MulticastUdpTransmitter>();
        mdnsOutReplyTransmitter->open(outInterface);
        m_mdnsOutReplyTransmitters.push_back(std::move(mdnsOutReplyTransmitter));
    }

    enableSignalHandlers();

    timeval selectTimeout;
    reloadTimeout(selectTimeout, true);

    while (true)
    {
        int maxDescriptor = 0;
        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(m_mdnsReceiver.descriptor(), &descriptors);
        maxDescriptor = max(m_mdnsReceiver.descriptor(), maxDescriptor);
        FD_SET(m_mdnsInQueryTransmitter.descriptor(), &descriptors);
        maxDescriptor = max(m_mdnsInQueryTransmitter.descriptor(), maxDescriptor);

        auto selectResult = select(maxDescriptor + 1, &descriptors, nullptr, nullptr, &selectTimeout);
        // LOG_DEBUG("selectResult=" << selectResult);

        if (selectResult < 0)
        {
            break;
        }
        else if (selectResult == 0)
        {
            handleTimeout();
            reloadTimeout(selectTimeout);
        }
        else if (FD_ISSET(m_mdnsReceiver.descriptor(), &descriptors))
        {
            handleMdnsReceiverMessage();
        }
        else if (FD_ISSET(m_mdnsInQueryTransmitter.descriptor(), &descriptors))
        {
            handleMdnsInQueryTransmitterMessage();
        }
    }

    m_mdnsReceiver.closeReceiver();
    m_mdnsInQueryTransmitter.closeTransmitter();
    for (auto& mdnsOutReplyTransmitter: m_mdnsOutReplyTransmitters)
    {
        mdnsOutReplyTransmitter->closeTransmitter();
    }
}

int MainThread::max(int a, int b)
{
    return (a > b) ? a : b;
}

void MainThread::signalHandler(int signal)
{
    LOG_INFO("Caught signal " << signal);
}

void MainThread::enableSignalHandlers(void)
{
    struct sigaction signalAction;
    signalAction.sa_handler = signalHandler;
    sigemptyset(&signalAction.sa_mask);
    signalAction.sa_flags = 0;

    sigaction(SIGINT, &signalAction, nullptr);
}

void MainThread::handleTimeout(void)
{
    auto mdnsMessage = MdnsMessage::query({
        MdnsQueryRecord({ "_spotify-connect" , "_tcp", "local" }, DnsResourceType::PTR, 1) });

    MulticastMessage message {
        Protocol::MdnsMessage::toByteArray(mdnsMessage),
        mDnsAddress,
        mDnsPort,
        IpProtocol::IPV4 };

    // LOG_INFO(
    //     "mdnsMessage=" << Protocol::ByteArray::toHex(message.message, " "));

    m_mdnsInQueryTransmitter.sendMessage(message);
}

void MainThread::handleMdnsReceiverMessage(void)
{
    try
    {
        handleMdnsMessage(m_mdnsReceiver.receiveMessage());
    }
    catch(const std::exception& e)
    {
        LOG_WARNING("Could not handle received multicast mDNS message (" << e.what() << ")! Skipping.");
    }
}

void MainThread::handleMdnsInQueryTransmitterMessage(void)
{
    try
    {
        handleMdnsMessage(m_mdnsInQueryTransmitter.receiveMessage());
    }
    catch(const std::exception& e)
    {
        LOG_WARNING("Could not handle received unicast mDNS message (" << e.what() << ")! Skipping.");
    }
}

void MainThread::handleMdnsMessage(const MulticastMessage& message)
{
    auto mdnsMessage = Protocol::MdnsMessage::fromByteArray(message.message);
    // LOG_DEBUG("MainThread::handleMdnsMessage(" << mdnsMessage << ")");

    if (mdnsMessage.hasResourceRecords())
    {
        LOG_DEBUG("From: " << message.host << ":" << message.port);
        if (mdnsMessage.hasAnswers())
        {
            LOG_DEBUG("Answers:");
            for (auto& answer: mdnsMessage.answers)
            {
                LOG_DEBUG("  " << answer);
            }
        }
        if (mdnsMessage.hasAuthorityRecords())
        {
            LOG_DEBUG("Authority Records:");
            for (auto& authorityRecord: mdnsMessage.authorityRecords)
            {
                LOG_DEBUG("  " << authorityRecord);
            }
        }
        if (mdnsMessage.hasAdditionalRecords())
        {
            LOG_DEBUG("Additional Record:");
            for (auto& additionalRecord: mdnsMessage.additionalRecords)
            {
                LOG_DEBUG("  " << additionalRecord);
            }
        }
    }

    proxySpotifyConnectInformationIfApplicable(message.host, mdnsMessage);
}

void MainThread::proxySpotifyConnectInformationIfApplicable(
    const std::string& targetHost,
    const MdnsMessage& mdnsMessage)
{
    if (mdnsMessage.messageType == DnsMessageType::REPLY &&
        mdnsMessage.authoritativeAnswer &&
        mdnsMessage.responseCode == 0 &&
        mdnsMessage.hasAnswers() &&
        mdnsMessage.hasAdditionalRecords() &&
        mdnsMessage.answers.front().fullName() == "_spotify-connect._tcp.local")
    {
        LOG_INFO("Proxying received Spotify Connect information...");

        try
        {
            auto ptrIt = std::find_if(
                mdnsMessage.answers.cbegin(),
                mdnsMessage.answers.cend(),
                [](const MdnsResourceRecord& item) {
                    return item.type == DnsResourceType::PTR;
                });
            auto txtIt = std::find_if(
                mdnsMessage.additionalRecords.cbegin(),
                mdnsMessage.additionalRecords.cend(),
                [](const MdnsResourceRecord& item) {
                    return item.type == DnsResourceType::TXT;
                });
            auto srvIt = std::find_if(
                mdnsMessage.additionalRecords.cbegin(),
                mdnsMessage.additionalRecords.cend(),
                [](const MdnsResourceRecord& item) {
                    return item.type == DnsResourceType::SRV;
                });

            if (ptrIt == mdnsMessage.additionalRecords.cend() ||
                txtIt == mdnsMessage.additionalRecords.cend() ||
                srvIt == mdnsMessage.additionalRecords.cend())
            {
                throw std::runtime_error("expected PTR, TXT and/or SRV records are not available");
            }

            auto ptrData = dynamic_cast<ResourceRecordPtrPayload*>(ptrIt->decodedData.get());
            auto txtData = dynamic_cast<ResourceRecordTxtPayload*>(txtIt->decodedData.get());
            auto srvData = dynamic_cast<ResourceRecordSrvPayload*>(srvIt->decodedData.get());

            if (!ptrData || !txtData || !srvData || ptrData->domainName.empty())
            {
                throw std::runtime_error("expected PTR, TXT and/or SRV records were not decoded");
            }

            auto proxiedMdnsMessage = MdnsMessage::reply();
            proxiedMdnsMessage.answers.push_back(std::move(MdnsResourceRecord(
                { "_spotify-connect", "_tcp", "local" },
                DnsResourceType::PTR,
                1,
                false,
                60,
                Protocol::ResourceRecordPtrPayload::toByteArray(ResourceRecordPtrPayload(
                    DnsResourceType::PTR,
                    { ptrData->domainName.front(), "_spotify-connect", "_tcp", "local" })))));
            proxiedMdnsMessage.answers.push_back(std::move(MdnsResourceRecord(
                { ptrData->domainName.front(), "_spotify-connect", "_tcp", "local" },
                DnsResourceType::SRV,
                1,
                false,
                60,
                Protocol::ResourceRecordSrvPayload::toByteArray(ResourceRecordSrvPayload(
                    DnsResourceType::SRV,
                    0,
                    0,
                    srvData->port,
                    { ptrData->domainName.front(), "local" })))));
            proxiedMdnsMessage.answers.push_back(std::move(MdnsResourceRecord(
                { ptrData->domainName.front(), "_spotify-connect", "_tcp", "local" },
                DnsResourceType::TXT,
                1,
                false,
                60,
                Protocol::ResourceRecordTxtPayload::toByteArray(ResourceRecordTxtPayload(
                    DnsResourceType::TXT,
                    txtData->lines)))));
            proxiedMdnsMessage.answers.push_back(std::move(MdnsResourceRecord(
                { ptrData->domainName.front(), "local" },
                DnsResourceType::A,
                1,
                false,
                60,
                Protocol::ResourceRecordAPayload::toByteArray(ResourceRecordAPayload(
                    DnsResourceType::A,
                    targetHost )))));

            auto proxiedMdnsMessageBytes = Protocol::MdnsMessage::toByteArray(proxiedMdnsMessage);

            MulticastMessage proxiedMessage {
                proxiedMdnsMessageBytes,
                mDnsAddress,
                mDnsPort,
                IpProtocol::IPV4 };

            for (auto& mdnsOutReplyTransmitter: m_mdnsOutReplyTransmitters)
            {
                mdnsOutReplyTransmitter->sendMessage(proxiedMessage);
            }

        }
        catch(const std::exception& e)
        {
            LOG_WARNING("Could not proxy the Spotify Connect information (" << e.what() << ")! Skipping.");
        }
    }

}

void MainThread::reloadTimeout(timeval& timeout, bool initial)
{
    if (initial)
    {
        timeout.tv_sec = 1;
    }
    else
    {
        timeout.tv_sec = 10;
    }
    timeout.tv_usec = 0;
}
