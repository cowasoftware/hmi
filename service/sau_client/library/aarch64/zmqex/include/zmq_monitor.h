#ifndef ZMQ_MONITOR_H_
#define ZMQ_MONITOR_H_

#include <unordered_map>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>

#include "zmq.hpp"




namespace cowa
{
namespace zmqex
{


using ZmqMonitorCb = std::function<void(int events,const char* addr)>;

class ZmqMonitor : public zmq::monitor_t 
{
public:
    ZmqMonitor(zmq::socket_t &socket,const std::string &addr="inproc://monitor",int events = ZMQ_EVENT_CONNECTED | ZMQ_EVENT_DISCONNECTED | ZMQ_EVENT_CLOSED);
    virtual ~ZmqMonitor();

    bool connected();
    void clean();

    void set_callback(ZmqMonitorCb func);

private:
    void on_event_connected(const zmq_event_t& event, const char* addr) override;
    void on_event_disconnected(const zmq_event_t& event, const char* addr) override;
    void on_event_closed(const zmq_event_t& event, const char* addr) override;

    void on_event_accepted(const zmq_event_t &event_, const char *addr_) override;
    //void on_event_accept_failed(const zmq_event_t &event_, const char *addr_) override;

private:
    bool connected_;//是否连接
    bool closed_;

    std::thread thread_;
    std::mutex  mtx_;
    zmq::socket_ref _socket;
    std::atomic<bool> stopped_;
    ZmqMonitorCb func_;

};
 
}// namespace zmqex
}// namespace cowa








#endif