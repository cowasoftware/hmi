#pragma once
#include "common.h"
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_base_of<google::protobuf::Message, T>::value, Message_Ptr>::type  CreateMessage(const T& msg)
{
  static_assert(std::is_base_of<google::protobuf::Message, T>::value, "Input must be a protobuf.");
  std::string msg_string;
  msg.SerializeToString(&msg_string);
  auto ret = std::make_shared<zmq::message_t>();
  ret->rebuild(msg_string.c_str(), msg_string.size());  // memcpy here

  return ret;
};