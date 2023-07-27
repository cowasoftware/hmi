#pragma once

#include "common.h"
#include "recv_interface.h"
#include "context.h"

class SubsBaseInfoFromAdu : public SubsRecvInterface {
 public: 
  virtual void onRecv(Message_Ptr msg) override;
  virtual void onError(Errno err) override
  {
    std::cout << "recv vehicle info from adu fail, code:" << err << std::endl;
  }
};