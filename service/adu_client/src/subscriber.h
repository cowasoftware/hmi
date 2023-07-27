#pragma once

#include "common.h"
#include "recv_interface.h"


class Subscriber : public std::enable_shared_from_this<Subscriber> {
 public:
  using Ptr = std::shared_ptr<Subscriber>;
  static Subscriber::Ptr start(std::string url, int hwm, const std::string subscriber_name);

  Subscriber(const std::string url, int hwm, const std::string subscriber_name);
  virtual ~Subscriber();
  void run();
  void stop() { 
      _stop = true;
      wait_sub_thread_ptr();
    }
  void add_listener(SubsRecvInterface::Ptr callback) 
  { 
    std::lock_guard<std::mutex> lg(_mutex);
    _listeners.emplace_back(callback);
  }
  void clear_unvaild_listener() 
  { 
    std::lock_guard<std::mutex> lg(_mutex);
    _listeners.remove_if([](std::weak_ptr<SubsRecvInterface> _listener){
      auto p = _listener.lock();
      if(p) return true;
      else return false;      
    });
  }
 protected:
  void onRecv(Message_Ptr data) {
    std::lock_guard<std::mutex> lg(_mutex);
    // gettm(getTimeStamp());
    // std::cout << " recv succ, msg size:" << data->size() << std::endl;;
    // CRINFO << "recv succ, msg size:" << data->size();
    for(const auto& _listener :_listeners )
    {
      auto p = _listener.lock();
      if(p) p->onRecv(data);
    }
    //if (_listener) { _listener->onRecv(data); }
  }
  void onError(SubsRecvInterface::Errno err) {
    std::lock_guard<std::mutex> lg(_mutex);
    for(const auto& _listener :_listeners )
    {
      auto p = _listener.lock();
      if(p) p->onError(err);
    }
    //if (_listener) _listener->onError(err);
  }

 private:
  std::time_t getTimeStamp()
  {
      std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
      auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
      std::time_t timestamp = tmp.count();
      //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
      return timestamp;
  }
  void gettm(std::time_t timestamp)
  {
      std::time_t milli = timestamp/*+ (std::time_t)8*60*60*1000*/;//此处转化为东八区北京时间，如果是其它时区需要按需求修改
      auto mTime = std::chrono::milliseconds(milli);
      auto tp=std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(mTime);
      auto tt = std::chrono::system_clock::to_time_t(tp);
      std::tm* now = std::gmtime(&tt);
      printf("%4d年%02d月%02d日 %02d:%02d:%02d.%ld:",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec, milli%1000);
  }

  void set_sub_thread_ptr(std::shared_ptr<std::thread> sub_thread_ptr)
  {
    if(sub_thread_ptr && !_sub_thread_ptr)
    {
      _sub_thread_ptr = sub_thread_ptr;
    }
  } 


  void wait_sub_thread_ptr()
  {
    if(_sub_thread_ptr && _sub_thread_ptr->joinable())
    {
      _sub_thread_ptr->join();
    }
  }

  void connect();
  std::atomic<bool> _stop;
  bool _state;
  std::string _url;
  int _hwm;
  std::string _subscriber_name;
  zmq::context_t _ctx;
  zmq::socket_t _socket;
  std::list<std::weak_ptr<SubsRecvInterface>> _listeners;
  std::mutex _mutex;
  std::shared_ptr<std::thread> _sub_thread_ptr;
};