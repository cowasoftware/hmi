#pragma once

#include "common.h"
#include "recv_interface.h"
#include "context.h"

class SubsCameraFromAdu : public SubsRecvInterface {
 public: 
  virtual void onRecv(Message_Ptr msg) override;
  virtual void onError(Errno err) override
  {
    std::cout << "recv camera from adu fail, code:" << err << std::endl;
  }
};