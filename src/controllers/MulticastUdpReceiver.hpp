#ifndef CONTROLLERS_MULTICASTUDPRECEIVER_HPP_
#define CONTROLLERS_MULTICASTUDPRECEIVER_HPP_

#include <controllers/GenericMulticastUdp.hpp>

class MulticastUdpReceiver: public GenericMulticastUdp
{
public:
    MulticastUdpReceiver();
    virtual ~MulticastUdpReceiver();

    void open(
        const std::string& interface,
        const std::string& multicastAddress,
        int port,
        IpProtocol protocol = IpProtocol::IPV4);
    void closeReceiver(void);
    void dropMulticastMembership(void);
    void renewMulticastMembership(void);

protected:
    std::string m_multicastAddress;
    int m_interfaceIndex;

    void updateMulticastMembership(int option, bool invalidPrerequisitesAreFatal = true);

    static int getInterfaceIndex(int descriptor, const std::string& interface);
};

#endif /* CONTROLLERS_MULTICASTUDPRECEIVER_HPP_ */
