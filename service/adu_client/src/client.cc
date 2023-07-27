/*
 * Copyright 2012-2022, YaoyongLiu <yaoyong.liu@cowarobot.com>
 * All rights reserved.
 */

#include "client.h"
#include "helper.h"

TcpClient::TcpClient(std::string url) : _url(url), _ctx(1)
{
  this->connect();
  _listeners_vec.resize(MAX_REQUEST_TYPE);
}

void TcpClient::run_request() {
    set_thread_name("Client Send");
    
    while(!this->_stop)
    {
      zmq::message_t request_data;
      if(_request_curve_points_queue.wait_dequeue_timed(request_data, 1000000))
      {
        send(request_data);
      }
    }
    std::cout << "Client Send is stop" << std::endl;
}

void TcpClient::handle_response(zmq::message_t& response_data)
{
  request_response::RequestResponseDataType parsed_proto;
  if(parsed_proto.ParseFromArray(response_data.data(), response_data.size()) &&
     parsed_proto.IsInitialized() &&
     parsed_proto.has_response_status() &&
     parsed_proto.response_status().IsInitialized())
  {
     
      std::lock_guard<std::mutex> lg(_mutex);
      auto request_type = parsed_proto.request_type();
      // std::cout << "request_type:" << request_type;
      if(request_type == MIN_UNVAILD_REQUEST_TYPE || request_type > MAX_REQUEST_TYPE)
      {
        std::cout << "===REQUEST TYPE ERROR===" << std::endl;
        std::cout << parsed_proto.DebugString() << std::endl;
        std::cout << "========================" << std::endl;
        return;
      }
      auto _listener_list = _listeners_vec[parsed_proto.request_type() - 1];
      for(const auto& _listener : _listener_list)
      {
        auto p = _listener.lock();
        if(p) p->onRecv(parsed_proto);
      }
  }
  else
  {
    std::cout << "msg parse fail" << std::endl;
  }
}

void TcpClient::run_response() {
    set_thread_name("Client Resp");
    while(!this->_stop)
    {
      zmq::message_t response_data;
      if(_reponse_curve_points_queue.wait_dequeue_timed(response_data, 1000000))
      {
        handle_response(response_data);
      }
    }
    std::cout << "Client Resp is stop" << std::endl;
}


TcpClient::Ptr TcpClient::start(std::string url) {
  auto tcpclient = std::make_shared<TcpClient>(url);
  std::weak_ptr<TcpClient> weak_ptr = tcpclient;

  auto request_thread_ptr =  std::make_shared<std::thread>([weak_ptr]() {
    auto strong = weak_ptr.lock();
    if (strong) { 
      // CRINFO << "REQUEST:" << strong.use_count();
      strong->run_request(); 
    }
  });
  tcpclient->set_request_thread_ptr(request_thread_ptr);


  auto response_thread_ptr =  std::make_shared<std::thread>([weak_ptr]() {
    auto strong = weak_ptr.lock();
    if (strong) { 
      // CRINFO << "RESPONSE:" << strong.use_count();
      strong->run_response(); 
      }
  });
   tcpclient->set_response_thread_ptr(response_thread_ptr);


  return tcpclient;
}



TcpClient::~TcpClient()
{
  _socket.close();
  _ctx.close();
}

void TcpClient::connect()
{
  try
  {
    _socket = zmq::socket_t(_ctx, ZMQ_REQ);
     _socket.connect(_url);
  }
  catch(const std::exception& e)
  {
    // std::cout << e.what() << std::endl;
    std::cout << "connect client exception: " << _url << std::endl;

    std::stringstream ss;
    ss << "connect client exception: " << _url << " ,info:" << e.what() << std::endl;
    throw ss.str();
  }
  
  if (!_socket.connected()) { 
    std::cout << "connect client is not connect: " << _url << std::endl;
    std::stringstream ss;
    ss << "connect client is not connect: " << _url << std::endl;
    throw ss.str();
  }
  
  // 开启TCP保活机制，防止网络连接因长时间无数据而被中断
  int tcp_keep_alive = 1;
  zmq_setsockopt(_socket.handle(), ZMQ_TCP_KEEPALIVE, &tcp_keep_alive, sizeof(tcp_keep_alive));

  // 网络连接空闲2min即发送保活包
  int tcp_keep_idle = 120;
  zmq_setsockopt(_socket.handle(), ZMQ_TCP_KEEPALIVE_IDLE, &tcp_keep_idle, sizeof(tcp_keep_idle));


  //设置接收超时为100s
  int recv_time_wait = 100000;
  zmq_setsockopt(_socket.handle(), ZMQ_RCVTIMEO, &recv_time_wait, sizeof(recv_time_wait));

  // 设置socker关闭前的停留时间
  // 停留时间指定了在对一个socket调用zmq_close(3)函数之后，这个socekt上即将被发送但还没有被发送到对端的消息在内存中继续停留的时间
  int close_time_wait = 0;
  zmq_setsockopt(_socket.handle(), ZMQ_LINGER, &close_time_wait, sizeof(close_time_wait));

  std::cout << "connect client success: " << _url << std::endl;
}




void TcpClient::send(zmq::message_t& msg)
{
  if (msg.size()) {
    //放入到队列中去
    try
    {
      //不阻塞
      auto ok = _socket.send(msg, zmq::send_flags::none);
      if (!ok) {
        std::cout << "TcpClient send: fail" << std::endl;
        return;
      }
      else
      {
        try{
          // std::cout << "TcpClient send: succ" << std::endl;
          zmq::message_t reply;
          //如果服务器没有启动，启动了客户端后又关闭掉的话这个线程会一直阻塞在这里
          //阻塞接口,但是设置了超时时间，时间为1s
          auto result = _socket.recv(reply, zmq::recv_flags::none);
          // std::cout << *result << std::endl;
          if(result)
          {
            _reponse_curve_points_queue.enqueue(std::move(reply));
          }
        }
        catch(const std::exception& e)
        {
          std::cout << "TcpClient recv response: exception, "  << e.what() << std::endl;
        }
      } 
    }
    catch(const std::exception& e)
    {
      std::cout << "TcpClient send: exception, " << e.what() << std::endl;
    }

  }
}