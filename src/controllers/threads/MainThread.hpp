#ifndef CONTROLLERS_THREADS_MAINTHREAD_HPP_
#define CONTROLLERS_THREADS_MAINTHREAD_HPP_

#include <ctime>
#include <memory>
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
};

#endif /* CONTROLLERS_THREADS_MAINTHREAD_HPP_ */
