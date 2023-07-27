#ifndef ZMQEX_CLIENT_H_
#define ZMQEX_CLIENT_H_

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#include "zmq.hpp"
#include "zmq_monitor.h"


namespace cowa
{
namespace zmqex
{


using ZmqClientCb = std::function<void(const std::string& msg)>;


class ZmqClient
{
public:
    ZmqClient(const std::string& url,ZmqClientCb func=nullptr);
    virtual ~ZmqClient();

    bool connect();
    bool connected();
    bool send(const std::string& msg);
    void stop();
    void set_monitor_callback(ZmqMonitorCb func);
    std::string get_error();
private:
    std::string         url_;
    ZmqClientCb         recv_cb_;
    zmq::context_t      ctx_;
    zmq::socket_t       socket_;
    std::thread         thread_;
    std::atomic<bool>   stopped_;
    std::unique_ptr<ZmqMonitor> monitor_;
    ZmqMonitorCb        monitor_cb_;
    std::string         error_info_;

};




}//namespace zmqex
}//namespace cowa



#endif
