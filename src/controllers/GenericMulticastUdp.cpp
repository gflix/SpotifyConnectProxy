#include <arpa/inet.h>
#include <netinet/ip.h>
#include <cstring>
#include <controllers/GenericMulticastUdp.hpp>
#include <protocols/IpProtocol.hpp>

GenericMulticastUdp::GenericMulticastUdp():
    m_protocol(IpProtocol::INVALID)
{
}

GenericMulticastUdp::~GenericMulticastUdp()
{
}

MulticastMessage GenericMulticastUdp::receiveMessage(void)
{
    MulticastMessage message;
    uint8_t messageBuffer[4096];
    ssize_t bytesReceived;

    if (m_protocol == IpProtocol::IPV4)
    {
        struct sockaddr_in peerAddress;
        socklen_t peerAddressLength = sizeof(peerAddress);
        bytesReceived = ::recvfrom(
            m_descriptor,
            messageBuffer,
            sizeof(messageBuffer),
            0,
            (sockaddr*) &peerAddress,
            &peerAddressLength);

        message.protocol = m_protocol;
        if (bytesReceived >= 0)
        {
            char ipAddressBuffer[INET_ADDRSTRLEN];
            inet_ntop(peerAddress.sin_family, &peerAddress.sin_addr, ipAddressBuffer, INET_ADDRSTRLEN);
            message.host = std::string(ipAddressBuffer);
            message.port = ntohs(peerAddress.sin_port);
            message.message = ByteArray(messageBuffer, bytesReceived);
        }
    }
    else
    {
        throw std::invalid_argument(
            "protocol \"" + Protocol::IpProtocol::toIdentifier(m_protocol) + "\" is not supported");
    }

    if (bytesReceived < 0)
    {
        throw std::runtime_error(
            "could not receive message (" + std::string(strerror(errno)) + ")");
    }

    return message;
}

