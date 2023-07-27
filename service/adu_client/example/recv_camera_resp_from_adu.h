#pragma once

#include "common.h"
#include "recv_interface.h"
#include "context.h"

class RecvCameraRespFromAdu : public ResponseRecvInterface {
 public: 
  virtual void onRecv(request_response::RequestResponseDataType& reponse_proto) override;
};