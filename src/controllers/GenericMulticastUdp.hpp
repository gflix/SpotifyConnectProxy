#ifndef CONTROLLERS_GENERICMULTICASTUDP_HPP_
#define CONTROLLERS_GENERICMULTICASTUDP_HPP_

#include <controllers/GenericDescriptor.hpp>
#include <models/MulticastMessage.hpp>

class GenericMulticastUdp: public GenericDescriptor
{
public:
    GenericMulticastUdp();
    virtual ~GenericMulticastUdp();

    MulticastMessage receiveMessage(void);

protected:
    IpProtocol m_protocol;

    using GenericDescriptor::close;
};

#endif /* CONTROLLERS_GENERICMULTICASTUDP_HPP_ */
