#ifndef CONTROLLERS_MULTICASTUDPTRANSMITTER_HPP_
#define CONTROLLERS_MULTICASTUDPTRANSMITTER_HPP_

#include <controllers/GenericMulticastUdp.hpp>

class MulticastUdpTransmitter: public GenericMulticastUdp
{
public:
    MulticastUdpTransmitter();
    virtual ~MulticastUdpTransmitter();

    void open(
        const std::string& interface,
        IpProtocol protocol = IpProtocol::IPV4);
    void closeTransmitter(void);
    void sendMessage(const MulticastMessage& message);

protected:
    std::string m_interfaceAddress;
};

#endif /* CONTROLLERS_MULTICASTUDPTRANSMITTER_HPP_ */
