#pragma once

#include "common.h"
// 阻塞队列的头文件包含了atomic的头文件
#include "blockingconcurrentqueue.h"
#include "recv_interface.h"

class TcpClient : public std::enable_shared_from_this<TcpClient> {
 public:
  using Ptr = std::shared_ptr<TcpClient>;
  using MsgQueue = moodycamel::BlockingConcurrentQueue<zmq::message_t>;
  static TcpClient::Ptr start(std::string url);
  TcpClient(std::string url);
  virtual ~TcpClient();
  void add_request(Message_Ptr ptr)
  {
    _request_curve_points_queue.enqueue(std::move(*ptr));
  }
  void send(zmq::message_t& msg);

  void handle_response(zmq::message_t& response_data);

  void add_listener(RequestType idx, ResponseRecvInterface::Ptr callback)
  { 
    std::lock_guard<std::mutex> lg(_mutex);
    _listeners_vec[idx-1].push_back(callback);
  }
  void clear_unvaild_listener() 
  { 
    std::lock_guard<std::mutex> lg(_mutex);
    for(auto& _listener_mem_list : _listeners_vec)
    {
        _listener_mem_list.remove_if([](std::weak_ptr<ResponseRecvInterface> _listener){
          auto p = _listener.lock();
          if(p) return true;
          else return false;      
        });
    }
  }
  void stop(){
    _stop = true;
    wait_request_thread_ptr();
    wait_response_thread_ptr();
  }

 private:

  void set_request_thread_ptr(std::shared_ptr<std::thread> request_thread_ptr)
  {
    if(request_thread_ptr && !_request_thread_ptr)
    {
      _request_thread_ptr = request_thread_ptr;
    }
  } 

  void set_response_thread_ptr(std::shared_ptr<std::thread> response_thread_ptr)
  {
    if(response_thread_ptr && !_response_thread_ptr)
    {
      _response_thread_ptr = response_thread_ptr;
    } 
  }

  void wait_request_thread_ptr()
  {
    if(_request_thread_ptr && _request_thread_ptr->joinable())
    {
      _request_thread_ptr->join();
    }
  }

  void wait_response_thread_ptr()
  {
    if(_response_thread_ptr && _response_thread_ptr->joinable())
    {
      _response_thread_ptr->join();
    }
  }
  void run_response();
  void run_request();
  void connect();
  std::string _url;
  zmq::context_t _ctx;
  zmq::socket_t _socket;
  MsgQueue _request_curve_points_queue;
  MsgQueue _reponse_curve_points_queue;
  std::vector<std::list<std::weak_ptr<ResponseRecvInterface>>> _listeners_vec;
  std::mutex _mutex;
  std::atomic<bool> _stop = false;

  std::shared_ptr<std::thread> _request_thread_ptr;
  std::shared_ptr<std::thread> _response_thread_ptr;
};
