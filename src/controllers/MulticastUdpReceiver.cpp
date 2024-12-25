#include <arpa/inet.h>
#include <linux/if.h>
#include <netinet/ip.h>
#include <sys/ioctl.h>
#include <cstring>
#include <stdexcept>
#include <controllers/MulticastUdpReceiver.hpp>
#include <protocols/IpProtocol.hpp>
#include <utils/Log.hpp>

MulticastUdpReceiver::MulticastUdpReceiver():
    m_interfaceIndex(-1)
{
}

MulticastUdpReceiver::~MulticastUdpReceiver()
{
    closeReceiver();
}

void MulticastUdpReceiver::open(
    const std::string& interface,
    const std::string& multicastAddress,
    int port,
    IpProtocol protocol)
{
    if (protocol == IpProtocol::IPV4)
    {
        m_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_descriptor <= 0)
        {
            throw std::runtime_error("could not open socket");
        }

        struct sockaddr_in bindAddress;
        bindAddress.sin_family = AF_INET;
        bindAddress.sin_port = htons(port);
        bindAddress.sin_addr.s_addr = htonl(INADDR_ANY);

        auto bindResult = bind(m_descriptor, (const sockaddr*) &bindAddress, sizeof(bindAddress));
        if (bindResult < 0)
        {
            throw std::runtime_error(
                "could not bind to port " + std::to_string(port) + " (" + std::string(strerror(errno)) + ")");
        }
        m_protocol = protocol;
    }
    else
    {
        throw std::invalid_argument(
            "protocol \"" + Protocol::IpProtocol::toIdentifier(protocol) + "\" is not supported");
    }

    m_interfaceIndex = getInterfaceIndex(m_descriptor, interface);
    m_multicastAddress = multicastAddress;
    renewMulticastMembership();
}

void MulticastUdpReceiver::closeReceiver(void)
{
    dropMulticastMembership();
    GenericDescriptor::close();
}

void MulticastUdpReceiver::dropMulticastMembership(void)
{
    updateMulticastMembership(IP_DROP_MEMBERSHIP, false);
}

void MulticastUdpReceiver::renewMulticastMembership(void)
{
    updateMulticastMembership(IP_ADD_MEMBERSHIP, true);
}

void MulticastUdpReceiver::updateMulticastMembership(int option, bool invalidPrerequisitesAreFatal)
{
    if (!isConnected())
    {
        if (invalidPrerequisitesAreFatal)
        {
            throw std::runtime_error("socket is closed");
        }
        else
        {
            return;
        }
    }
    if (m_multicastAddress.empty())
    {
        if (invalidPrerequisitesAreFatal)
        {
            throw std::runtime_error("multicast address is missing");
        }
        else
        {
            return;
        }
    }

    if (m_protocol == IpProtocol::IPV4)
    {
        struct ip_mreqn multicastMembershipRequest;
        if (inet_pton(AF_INET, m_multicastAddress.c_str(), &multicastMembershipRequest.imr_multiaddr) != 1)
        {
            throw std::runtime_error("invalid multicast address \"" + m_multicastAddress + "\"");
        }
        multicastMembershipRequest.imr_address.s_addr = htonl(INADDR_ANY);
        multicastMembershipRequest.imr_ifindex = m_interfaceIndex;

        if (setsockopt(
                m_descriptor,
                IPPROTO_IP,
                option,
                &multicastMembershipRequest,
                sizeof(multicastMembershipRequest)) < 0)
        {
            throw std::runtime_error(
                "could not update multicast membership (" + std::string(strerror(errno)) + ")");
        }
    }
    else
    {
        throw std::invalid_argument(
            "protocol \"" + Protocol::IpProtocol::toIdentifier(m_protocol) + "\" is not supported");
    }
}

int MulticastUdpReceiver::getInterfaceIndex(int descriptor, const std::string& interface)
{
    if (interface.size() >= IFNAMSIZ)
    {
        throw std::invalid_argument("interface name is too long");
    }

    struct ifreq interfaceRequest;
    strncpy(interfaceRequest.ifr_name, interface.c_str(), IFNAMSIZ);
    if (ioctl(descriptor, SIOCGIFINDEX, &interfaceRequest) == -1)
    {
        throw std::runtime_error(
            "could not determine index of interface \"" + interface + "\" (" + std::string(strerror(errno)) + ")");
    }
    return interfaceRequest.ifr_ifindex;
}
