#include <models/MulticastMessage.hpp>
#include <protocols/ByteArray.hpp>

MulticastMessage::MulticastMessage(
    ByteArray message,
    std::string host,
    int port,
    IpProtocol protocol):
    message(message),
    host(host),
    port(port),
    protocol(protocol)
{
}

MulticastMessage::~MulticastMessage()
{
}

std::ostream& operator<<(std::ostream& stream, const MulticastMessage& item)
{
    stream << "MulticastMessage[";
    stream << "message=" << Protocol::ByteArray::toHex(item.message, " ") << ",";
    stream << "host=" << item.host << ",";
    stream << "port=" << item.port << ",";
    stream << "protocol=" << item.protocol;
    stream << "]";

    return stream;
}
