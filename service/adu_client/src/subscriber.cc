#include "subscriber.h"
#include "helper.h"

Subscriber::Subscriber(const std::string url,  int hwm, const std::string subscriber_name) : _stop(false), _state(true), _url(url), _hwm(hwm), _subscriber_name(subscriber_name),_ctx(1) {
  this->connect();
}

Subscriber::~Subscriber() {}

void Subscriber::connect() {
  try
  {
    _socket = zmq::socket_t(_ctx, ZMQ_SUB);

    //保留最新的的一条消息
    if(0 == _hwm)
    {
      //SUB时仅仅保留最新的消息
      int only_keep_last_message = 1;
      zmq_setsockopt(_socket.handle(), ZMQ_CONFLATE, &only_keep_last_message, sizeof(only_keep_last_message));
    }

    _socket.connect(_url);
  }
  catch(const std::exception& e)
  {
    std::cout << "connect sub exception: " << _url << " ,info:" << e.what() << std::endl;
    std::stringstream ss;
    ss << "connect sub exception: " << _url << " ,info:" << e.what() << std::endl;
    throw ss.str();
  }


  if (!_socket.connected()) { 
    std::cout << "connect sub is not connect: " << _url << std::endl;
    std::stringstream ss;
    ss << "connect sub is not connect: " << _url << std::endl;
    throw ss.str();
  }
  
  //设置订阅者的消息过滤器
  //0为接受任何消息
  _socket.setsockopt(ZMQ_SUBSCRIBE, nullptr, 0);

  //设置接收超时为100s
  int recv_time_wait = 100000;
  zmq_setsockopt(_socket.handle(), ZMQ_RCVTIMEO, &recv_time_wait, sizeof(recv_time_wait));

  // 设置socker关闭前的停留时间
  // 停留时间指定了在对一个socket调用zmq_close(3)函数之后，这个socekt上即将被发送但还没有被发送到对端的消息在内存中继续停留的时间
  int close_time_wait = 0;
  zmq_setsockopt(_socket.handle(), ZMQ_LINGER, &close_time_wait, sizeof(close_time_wait));


  if (DEFALUT_PUB_HWM != _hwm)
  {
     zmq_setsockopt(_socket.handle(), ZMQ_RCVHWM, &_hwm, sizeof(_hwm));
  }


  std::cout << "connect sub success: " << this->_url << ", hwm:" << _hwm << std::endl;
}

void Subscriber::run() {
  set_thread_name(_subscriber_name);
  while (!this->_stop) { 
    try
    {
      auto request = std::make_shared<zmq::message_t>();
      auto ok = this->_socket.recv(*request, zmq::recv_flags::none);
      if (ok) { 
        if(_state == false)
        {
          _state = true;
          std::cout << _subscriber_name << " sub is succ" << std::endl;
        }
        onRecv(request); 
      }
      else {
        if(_state == true)
        {
          _state = false;
          onError(SubsRecvInterface::ERROR_NET_RECV);
        }
      }
    }
    catch(std::exception e)
    {
      std::cout << "Subscriber recv: exception, " << e.what() << std::endl;
    }

  }
  std::cout <<"Subscriber is stop" << std::endl;
}

Subscriber::Ptr Subscriber::start(const std::string url, int hwm, const std::string subscriber_name) {
  auto subscriber = std::make_shared<Subscriber>(url, hwm, subscriber_name);
  std::weak_ptr<Subscriber> weak_ptr = subscriber;

  subscriber->set_sub_thread_ptr(std::make_shared<std::thread>(
    std::thread([weak_ptr]() {
      auto strong = weak_ptr.lock();
      if (strong) { strong->run(); }
    }
  )));

  return subscriber;
}