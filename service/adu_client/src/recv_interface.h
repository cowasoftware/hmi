#pragma once

#include "common.h"

class SubsRecvInterface : public std::enable_shared_from_this<SubsRecvInterface> {
 public:
  typedef enum {
    ERROR_NET_CONNECT = 1,
    ERROR_NET_RECV,
  } Errno;

 public:
  using Ptr = std::shared_ptr<SubsRecvInterface>;
  virtual ~SubsRecvInterface() = default;
  virtual void onRecv(Message_Ptr msg) = 0;
  virtual void onError(Errno err) = 0;
};

class ResponseRecvInterface : public std::enable_shared_from_this<ResponseRecvInterface> {
 public:

 public:
  using Ptr = std::shared_ptr<ResponseRecvInterface>;
  virtual ~ResponseRecvInterface() = default;
  virtual void onRecv(request_response::RequestResponseDataType& reponse_proto) = 0;
};