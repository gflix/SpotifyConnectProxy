#ifndef CONTROLLERS_THREADS_MAINTHREAD_HPP_
#define CONTROLLERS_THREADS_MAINTHREAD_HPP_

#include <ctime>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <controllers/MulticastUdpReceiver.hpp>
#include <controllers/MulticastUdpTransmitter.hpp>
#include <models/CommandlineArguments.hpp>
#include <models/MdnsMessage.hpp>

class MainThread
{
public:
    MainThread(const CommandlineArguments& arguments);
    virtual ~MainThread();

    void run(void);

    static void signalHandler(int signal);
    static int max(int a, int b);

    static constexpr char mDnsAddress[] = "224.0.0.251";
    static constexpr unsigned int mDnsPort = 5353;

protected:
    CommandlineArguments m_arguments;
    MulticastUdpReceiver m_mdnsReceiver;
    MulticastUdpTransmitter m_mdnsInQueryTransmitter;
    std::vector<std::unique_ptr<MulticastUdpTransmitter>> m_mdnsOutReplyTransmitters;

    void enableSignalHandlers(void);
    void handleTimeout(void);
    void handleMdnsReceiverMessage(void);
    void handleMdnsInQueryTransmitterMessage(void);
    void handleMdnsMessage(const MulticastMessage& message);
    void proxySpotifyConnectInformationIfApplicable(
        const std::string& targetHost,
        const MdnsMessage& mdnsMessage);

    void reloadTimeout(timeval& timeout, bool initial = false);

    template<typename T>
    MdnsResourceRecords::const_iterator findResourceRecord(const MdnsMessage& message, T pred)
    {
        auto it = std::find_if(
            message.answers.cbegin(),
            message.answers.cend(),
            pred);

        if (it != message.answers.cend())
        {
            return it;
        }

        it = std::find_if(
            message.additionalRecords.cbegin(),
            message.additionalRecords.cend(),
            pred);

        if (it != message.additionalRecords.cend())
        {
            return it;
        }

        it = std::find_if(
            message.authorityRecords.cbegin(),
            message.authorityRecords.cend(),
            pred);

        if (it != message.authorityRecords.cend())
        {
            return it;
        }

        throw std::out_of_range("expected resource record not found");
    }
};

#endif /* CONTROLLERS_THREADS_MAINTHREAD_HPP_ */
