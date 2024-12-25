#ifndef MODELS_MULTICASTMESSAGE_HPP_
#define MODELS_MULTICASTMESSAGE_HPP_

#include <ostream>
#include <models/ByteArray.hpp>
#include <models/IpProtocol.hpp>

struct MulticastMessage
{
    explicit MulticastMessage(
        ByteArray message = ByteArray(),
        std::string host = std::string(),
        int port = 0,
        IpProtocol protocol = IpProtocol::INVALID);
    virtual ~MulticastMessage();

    ByteArray message;
    std::string host;
    int port;
    IpProtocol protocol;
};

std::ostream& operator<<(std::ostream& stream, const MulticastMessage& item);

#endif /* MODELS_MULTICASTMESSAGE_HPP_ */
