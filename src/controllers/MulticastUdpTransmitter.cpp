#include <arpa/inet.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <cstring>
#include <controllers/MulticastUdpTransmitter.hpp>
#include <protocols/IpProtocol.hpp>
#include <utils/Log.hpp>

MulticastUdpTransmitter::MulticastUdpTransmitter()
{
}

MulticastUdpTransmitter::~MulticastUdpTransmitter()
{
    closeTransmitter();
}

void MulticastUdpTransmitter::open(
    const std::string& interface,
    IpProtocol protocol)
{
    if (protocol == IpProtocol::IPV4)
    {
        m_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_descriptor <= 0)
        {
            throw std::runtime_error("could not open socket");
        }

        if (interface.size() >= IFNAMSIZ)
        {
            throw std::invalid_argument("interface name is too long");
        }

        struct ifreq interfaceRequest;
        strncpy(interfaceRequest.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);

        if (ioctl(m_descriptor, SIOCGIFADDR, &interfaceRequest) == -1)
        {
            throw std::runtime_error(
                "could not determine IPv4 address of interface \"" + interface + "\" "
                "(" + std::string(strerror(errno)) + ")");
        }

        char buffer[INET_ADDRSTRLEN];
        auto interfaceAddress = (sockaddr_in*) &interfaceRequest.ifr_addr;
        inet_ntop(interfaceAddress->sin_family, &interfaceAddress->sin_addr, buffer, INET_ADDRSTRLEN);
        m_interfaceAddress = buffer;
        LOG_DEBUG("m_interfaceAddress=" << m_interfaceAddress);

        if (setsockopt(
                m_descriptor,
                IPPROTO_IP,
                IP_MULTICAST_IF,
                &interfaceAddress->sin_addr,
                sizeof(interfaceAddress->sin_addr)) < 0)
        {
            throw std::runtime_error(
                "could not bind multicast socket to selected interface (" + std::string(strerror(errno)) + ")");
        }
    }
    else
    {
        throw std::invalid_argument(
            "protocol \"" + Protocol::IpProtocol::toIdentifier(protocol) + "\" is not supported");
    }

    m_protocol = protocol;
}

void MulticastUdpTransmitter::closeTransmitter(void)
{
    GenericDescriptor::close();
}

void MulticastUdpTransmitter::sendMessage(const MulticastMessage& message)
{
    if (!isConnected())
    {
        throw std::runtime_error("socket is closed");
    }

    if (message.protocol == IpProtocol::IPV4)
    {
        struct sockaddr_in targetAddress;
        targetAddress.sin_family = AF_INET;
        targetAddress.sin_port = htons(message.port);
        if (inet_pton(targetAddress.sin_family, message.host.c_str(), &targetAddress.sin_addr.s_addr) < 1)
        {
            throw std::invalid_argument("invalid IPv4 host");
        }

        if (sendto(m_descriptor, message.message.data(), message.message.size(), 0, (const sockaddr*) &targetAddress, sizeof(targetAddress)) < 0)
        {
            throw std::runtime_error(
                "could not send message to \"" + message.host + ":" + std::to_string(message.port) + "\" "
                "(" + std::string(strerror(errno)) + ")");
        }
    }
    else
    {
        throw std::invalid_argument(
            "protocol \"" + Protocol::IpProtocol::toIdentifier(message.protocol) + "\" is not supported");
    }
}
