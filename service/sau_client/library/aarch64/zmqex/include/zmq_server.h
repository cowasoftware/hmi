#ifndef ZMQEX_SERVER_H_
#define ZMQEX_SERVER_H_

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

using ZmqServerCb = std::function<void(uint32_t rid,const std::string& msg)>;

class ZmqServer
{
public:
    ZmqServer(const std::string& url,ZmqServerCb func=nullptr);
    virtual ~ZmqServer();

    bool start();
    void stop();
    bool send(uint32_t rid,const std::string& msg);
    void set_monitor_cb(ZmqMonitorCb func);

    std::string get_error();
private:
    std::string     url_;
    ZmqServerCb     recv_cb_;
    zmq::context_t  ctx_;
    zmq::socket_t   socket_;
    std::thread     thread_;
    std::atomic<bool> stopped_;
    std::unique_ptr<ZmqMonitor> monitor_;
    ZmqMonitorCb    monitor_cb_;
    std::string     error_info_;
};

}//end namespace zmqex
}//end namespace cowa





#endif
