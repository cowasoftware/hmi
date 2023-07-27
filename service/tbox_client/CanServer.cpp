#include "CanServer.h"
//#include "UIDataHandle.h"
#include "CleanData.h"
#include "DashBoardData.h"
#include "Diagnosis12VDCData.h"
#include "Diagnosis48VDCData.h"
#include "DiagnosisBattery11EFData.h"
#include "DiagnosisBattery13EFData.h"
#include "DiagnosisBattery33EFData.h"
#include "DiagnosisBatteryData.h"
#include "DiagnosisBrake5FData.h"
#include "DiagnosisBrake60Data.h"
#include "DiagnosisBrakeData.h"
#include "DiagnosisCommuData.h"
#include "DiagnosisEPS5CData.h"
#include "DiagnosisEPSData.h"
#include "DiagnosisFan902Data.h"
#include "DiagnosisFanA02Data.h"
#include "DiagnosisFanB02Data.h"
#include "DiagnosisFanC02Data.h"
#include "DiagnosisHigPreDump15Data.h"
#include "DiagnosisHigPreDump16Data.h"
#include "DiagnosisIO71Data.h"
#include "DiagnosisIO78Data.h"
#include "DiagnosisIO79Data.h"
#include "DiagnosisIOData.h"
#include "DiagnosisMainDriData.h"
#include "DiagnosisSweepDiskData.h"
#include "LevelDBManager.h"
#include "LightScreenData.h"
#include "MCU1Data.h"
#include "Util.h"
#include <QDebug>
#include <QString>
#include "frame_video.h"
#include "ConfigConstants.h"

#define NETWORK_MSG_SAVE_KEY "NetWorkMsg"
#define LOGGER GetLogMgr().getLogger()

CCanServer::CCanServer() : m_nReqFlag(false) {}

inline CLogMgr &CCanServer::GetLogMgr()
{
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT_AND_CONSOLE);
  return my_logger;
}

void CCanServer::init()
{
  m_ZmqSubIF.setDataCb(std::bind(&CCanServer::zmqSubCb, this, std::placeholders::_1, std::placeholders::_2));
  std::string subAddr;
#ifdef PLATFORM_IMX8
  // ret = m_ZmqSubIF.connect(CAN_ZMQ_SUB_ADDR_VEHICLE);
  subAddr = CAN_ZMQ_SUB_ADDR_VEHICLE;
  std::cout << "Cur Platform is IMX8" << std::endl;
#else
  // ret = m_ZmqSubIF.connect(CAN_ZMQ_SUB_ADDR);
    subAddr = CAN_ZMQ_SUB_ADDR;
  //subAddr = "tcp://192.168.1.10:40000";

#endif
  bool ret = false;
  while (!ret)
  {
    ret = m_ZmqSubIF.connect(subAddr);
    if (!ret)
    {
      LOGGER->Cowa_Warn("SubAddr bind error, please try again, the addr is: ", subAddr);
    }
    else
    {
      // LOGGER->Cowa_Info("mZmqSubIF.connect success, ret = %s", ret);
    }
    sleep(1);
  }
  // std::cout << "mZmqSubIF.connect, ret: " << (uint32_t)ret << std::endl;

  std::vector<std::string> topicVec;
  topicVec.push_back(TOPIC_CAN_ID_0x6E);
  topicVec.push_back(TOPIC_CAN_ID_0x6F);
  topicVec.push_back(TOPIC_CAN_ID_0x70);
  topicVec.push_back(TOPIC_CAN_ID_0x71);
  topicVec.push_back(TOPIC_CAN_ID_0x78);
  topicVec.push_back(TOPIC_CAN_ID_0x79);
  topicVec.push_back(TOPIC_CAN_ID_0x7B);
  topicVec.push_back(TOPIC_CAN_ID_0x7C);
  topicVec.push_back(TOPIC_CAN_ID_0x7D);
  topicVec.push_back(TOPIC_CAN_ID_0x63);
  topicVec.push_back(TOPIC_CAN_ID_0x62);
  topicVec.push_back(TOPIC_CAN_ID_0x61);
  topicVec.push_back(TOPIC_CAN_ID_0x5F);
  topicVec.push_back(TOPIC_CAN_ID_0x60);
  topicVec.push_back(TOPIC_CAN_ID_0x5E);
  topicVec.push_back(TOPIC_CAN_ID_0x5D);
  topicVec.push_back(TOPIC_CAN_ID_0x5C);
  topicVec.push_back(TOPIC_CAN_ID_0x511);
  topicVec.push_back(TOPIC_CAN_ID_0x512);
  topicVec.push_back(TOPIC_CAN_ID_0x08FF32F0);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF15EF);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF16EF);
  topicVec.push_back(TOPIC_CAN_ID_0x18FF12F7);
  topicVec.push_back(TOPIC_CAN_ID_0x18F412EF);
  topicVec.push_back(TOPIC_CAN_ID_0x18F413EF);
  topicVec.push_back(TOPIC_CAN_ID_0x18F433EF);
  topicVec.push_back(TOPIC_CAN_ID_0x18F411EF);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF7902);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF7A02);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF7B02);
  topicVec.push_back(TOPIC_CAN_ID_0x0CFF7C02);
  topicVec.push_back(TOPIC_NETWORK_MSG);
  topicVec.push_back(TOPIC_REP_EVENT_ID_HMI_GET_CAN_DATA);
  topicVec.push_back(TOPIC_REP_EVENT_ID_HMI_GET_NETWORK_DATA);

  ret = m_ZmqSubIF.subscribe(topicVec);
  LOGGER->Cowa_Info(("mZmqSubIF.connect, ret: " + std::to_string(ret)).c_str());

  m_ZmqSubIF.recvData();

  m_ZmqReqIF.setOnlineCb([=](bool online)
                         { 
        std::string msg_str = "";
        msg_str.append("mZmqReqIF online: ").append(std::to_string((uint32_t)online));
        LOGGER->Cowa_Info(msg_str.c_str());
        std::lock_guard<std::mutex> itsLock(m_Mutex);
        m_aCoonected = online; });
std::string reqAddr;
#ifdef PLATFORM_IMX8
  reqAddr = CAN_ZMQ_REQ_ADDR_VEHICLE;
  ret = m_ZmqReqIF.connect(reqAddr);
#else
  reqAddr = CAN_ZMQ_REQ_ADDR;
  // reqAddr = CAN_ZMQ_REQ_ADDR_HOST;
  ret = m_ZmqReqIF.connect(reqAddr);
#endif
  std::string msg_str = "";
  msg_str.append("ZmqReqIF.connect, ret: ").append(std::to_string((uint32_t)ret))
  .append(", reqAddr is: [" + reqAddr + "]");
  LOGGER->Cowa_Info(msg_str.c_str());
  // m_spThread.reset(new std::thread(std::bind(&CCanServer::threadFunc, this)));
}

void CCanServer::initH264() {
  m_ZmqSub_H264.setDataCb(std::bind(&CCanServer::zmqH264SubCb, this, std::placeholders::_1, std::placeholders::_2));
  std::string subAddr;
#ifdef PLATFORM_IMX8
  // ret = m_ZmqSubIF.connect(CAN_ZMQ_SUB_ADDR_VEHICLE);
  subAddr = CAN_ZMQ_SUB_ADDR_VEHICLE;
  std::cout << "Cur Platform is IMX8" << std::endl;
#else
  // ret = m_ZmqSubIF.connect(CAN_ZMQ_SUB_ADDR);
  // subAddr = "tcp://192.168.1.2:40000";
  subAddr = REVERSE_IMAGE_URL;

#endif
  bool ret = false;
  while (!ret)
  {
    ret = m_ZmqSub_H264.connect(subAddr);
    if (!ret)
    {
      LOGGER->Cowa_Warn(("SubAddr bind error, please try again, the addr is:[" + subAddr + "]").c_str());
    }else
    {
      LOGGER->Cowa_Info(("m_ZmqSub_H264.connect success, subAddr: [" + subAddr + "]").c_str());
      // std::cout << "m_ZmqSub_H264.connect success. subAddr: " << subAddr << std::endl;
    }
    sleep(1);
  }
  std::vector<std::string> topicVec;
  // topicVec.push_back("/camera/surround/back/h264");
  topicVec.push_back(REVERSE_IMAGE_TOPIC);

  ret = m_ZmqSub_H264.subscribe(topicVec);
  LOGGER->Cowa_Info(("m_ZmqSub_H264 subscribe topic ret: [" + std::to_string(ret) + "]").c_str());
  m_ZmqSub_H264.recvData();

  m_ZmqReq_H264.setOnlineCb([=](bool online)
                         { 
        std::string msg_str = "";
        msg_str.append("m_ZmqReq_H264 online: ").append(std::to_string((uint32_t)online));
        LOGGER->Cowa_Info(msg_str.c_str());
        std::lock_guard<std::mutex> itsLock(m_Mutex);
        m_aCoonected = online; });
#ifdef PLATFORM_IMX8
  ret = m_ZmqReqIF.connect(CAN_ZMQ_REQ_ADDR_VEHICLE);
#else
  // ret = m_ZmqReq_H264.connect(CAN_ZMQ_REQ_ADDR);
#endif
  // std::string msg_str = "";
  // msg_str.append("m_ZmqReq_H264.connect, ret: ").append(std::to_string((uint32_t)ret));
  // LOGGER->Cowa_Info(msg_str.c_str());
}

void CCanServer::loadLocalData()
{
  //联网之前先把本地数据加载一遍
  std::string networkData;
  if (LevelDBManager::instance().getConfig(NETWORK_MSG_SAVE_KEY, networkData))
  {
    parseNetWorkMsg(networkData);
  }
  //去掉从配置文件中读取电量信息
  // LevelDBManager::instance().findConfig(
  //     "CanMsg_0x", [=](const std::string &key, const std::string &value) {
  //       topicMsg(0, key, value, false);
  //     });
}

int CCanServer::threadFunc()
{
  std::shared_ptr<IData> data_set = nullptr;
  // std::shared_ptr<IData> data_get = nullptr;
  int data_get = -1;
  while (1)
  {
    if (m_isStoped)
    {
      return true;
    }
    if (m_aCoonected == 0)
    {
      LOGGER->Cowa_Warn("is not connected now, wating...");
    }
    while (m_aCoonected == 0)
    {
      if (m_isStoped)
        return true;
      sleep(1);
    }
    std::string msg_str = "";
    msg_str.append("now: gIsConnected:").append(std::to_string((uint32_t)m_aCoonected.load()));
    LOGGER->Cowa_Info(msg_str.c_str());
    //  sleep(1);

    //设置数据
    {
      std::unique_lock<std::mutex> guard(m_cmdMutex);
      while (m_cmdData.empty() && m_getCanData.empty())
      {
        LOGGER->Cowa_Info(" cmd data is empty....");
        if (m_isStoped)
        {
          break;
        }
        m_ConCmd.wait(guard);
      }
      if (m_isStoped)
      {
        break;
      }
      LOGGER->Cowa_Info("begin handle cmd data......");
      if (!m_getCanData.empty())
      {
        data_get = m_getCanData.front();
        m_getCanData.pop_front();
      }
      if (!m_cmdData.empty())
      {
        data_set = m_cmdData.front();
        m_cmdData.pop_front();
      }
    }
    if (data_get != -1)
    {
      processGetCanData(data_get);
      data_get = -1;
    }
    if (data_set)
    {
      processCmdData(data_set);
      data_set.reset();
      // std::cout << " data ptr is nullptr" << std::endl;
      // continue;
    }

    if (m_isStoped)
      break;
  }
  LOGGER->Cowa_Info("begin to exist");
  return true;
}

void CCanServer::destroy()
{
  // m_isStoped = true;
  // sleep(1);
  m_ConCmd.notify_all();
  if (m_spThread->joinable())
  {
    m_spThread->join();
  }
  LOGGER->Cowa_Info("thread exit !!!");
}

void CCanServer::run()
{
  std::shared_ptr<IData> data_set = nullptr;
  // std::shared_ptr<IData> data_get = nullptr;
  int data_get = -1;
  while (1)
  {
    if (m_isStoped)
    {
      return;
    }
    if (m_aCoonected == 0)
    {
      LOGGER->Cowa_Warn("is not connected now, wating...");
    }
    while (m_aCoonected == 0)
    {
      if (m_nReqFlag) //意外断开连接，需要置位，连接成功可以再次主动请求数据
      {
        m_nReqFlag = false;
      }
      if (m_isStoped)
        return;
      sleep(1);
    }
    //连接成功主动请求can数据，需确定是否需要这样做
    if (m_aCoonected && !m_nReqFlag)
    {
      if (zmqReqAllData()) //请求成功再复位
      {
        m_nReqFlag = true;
      }
    }

    std::string msg_str = "";
    msg_str.append("now: gIsConnected:").append(std::to_string((uint32_t)m_aCoonected.load()));
    LOGGER->Cowa_Info(msg_str.c_str());
    //  sleep(1);

    //设置数据
    {
      std::unique_lock<std::mutex> guard(m_cmdMutex);
      while (m_cmdData.empty() && m_getCanData.empty())
      {
        LOGGER->Cowa_Info(" cmd data is empty....");
        if (m_isStoped)
        {
          break;
        }
        m_ConCmd.wait(guard);
      }
      if (m_isStoped)
      {
        break;
      }
      LOGGER->Cowa_Info("begin handle cmd data......");
      if (!m_getCanData.empty())
      {
        data_get = m_getCanData.front();
        m_getCanData.pop_front();
      }
      if (!m_cmdData.empty())
      {
        data_set = m_cmdData.front();
        m_cmdData.pop_front();
      }
    }
    if (data_get != -1)
    {
      processGetCanData(data_get);
      data_get = -1;
    }
    if (data_set)
    {
      processCmdData(data_set);
      data_set.reset();
      // std::cout << " data ptr is nullptr" << std::endl;
      // continue;
    }

    if (m_isStoped)
      break;
  }
  LOGGER->Cowa_Info("begin to exist");
}

std::shared_ptr<IData> CCanServer::getSubData()
{
  std::shared_ptr<IData> spData = nullptr;
  {
    std::unique_lock<std::mutex> guard(m_listMutex);
    if (!m_lData.empty())
    {
      spData = m_lData.front();
      m_lData.pop_front();
    }
    else
    {
      m_isStartTimer = false;
      return nullptr;
    }
  }
  return spData;
}

std::shared_ptr<IData> CCanServer::getCmdData()
{
  std::shared_ptr<IData> spData = nullptr;
  {
    std::unique_lock<std::mutex> guard(m_cmdMutex);
    if (m_cmdData.size() > 0)
    {
      spData = m_cmdData.front();
      m_cmdData.pop_front();
    }
    else
    {
      return nullptr;
    }
  }
  return spData;
}

void CCanServer::pushSubData(const std::shared_ptr<IData> &pdata)
{
  {
    std::unique_lock<std::mutex> guard(m_listMutex);
    m_lData.push_back(pdata);
  }

  // m_ConSub.notify_one();
  Q_EMIT dealSubDataSignal(m_cType.SCRB_CAN_DATA);
  // if (!m_isStartTimer)
  // {
  //     Q_EMIT notifyTimer();
  //     m_isStartTimer = true;
  // }

  // LOGGER->Cowa_Info("CCanServer::pushSubData please deal......");
  //  printf(" Push Sub Data ThreadID: %d\n", std::this_thread::get_id());
}

void CCanServer::cmdReqSlot(int cmd)
{
  LOGGER->Cowa_Info(".........cmdReqSlot ......");
}

void CCanServer::quitFlag(bool flag)
{
  m_isStoped = flag;

  m_ZmqSubIF.stop();
  LOGGER->Cowa_Info(" m_ZmqSubIF.stop() has been executed!");
  m_ZmqReqIF.stop();
  LOGGER->Cowa_Info(" m_ZmqReqIF.stop() has been executed!");
  m_ZmqSub_H264.stop();
  m_ZmqReq_H264.stop();
  // destroy();
}

void CCanServer::pushCmdData(const std::shared_ptr<IData> &pdata)
{
  std::unique_lock<std::mutex> guard(m_cmdMutex);
  m_cmdData.push_back(pdata);
  m_ConCmd.notify_one();
  // LOGGER->Cowa_Info("push Cmd data to set................");
}

void CCanServer::processCmdData(const std::shared_ptr<IData> &pdata)
{
  LOGGER->Cowa_Info("process Cmd data.......");
  if (!pdata)
  {
    LOGGER->Cowa_Warn("process cmd data error, pdata is nullptr...");
    return;
  }
  if (pdata->m_nDataType == m_cType.CLEAN_DATA) // 0x64
  {
    auto spData = std::dynamic_pointer_cast<CCleanData>(pdata);
    setCleanCmdData(spData);
  }
}

void CCanServer::setCleanCmdData(const std::shared_ptr<CCleanData> &pdata)
{
  if (!pdata)
  {
    LOGGER->Cowa_Warn("set clean cmd error, pdata is nullptr...");
    return;
  }

  LOGGER->Cowa_Info("set clean cmd data to tbox...............");
  auto spData = std::dynamic_pointer_cast<CCleanData>(pdata);
  CanServiceMsg canServiceMsg;
  static uint32_t count = 0;
  ++count;
  canServiceMsg.set_eventid(EVENT_ID_SET_CAN_DATA);
  canServiceMsg.set_seqnum(count);
  auto canData = canServiceMsg.add_candata();
  // canData->set_canid(CAN_ID_0x65);
  // CanMsg_0x65 canMsg;
  // canMsg.set_vehicle_code(2);
  canData->set_canid(CAN_ID_0x64);
  CanMsg_0x64 canMsg;
  //上装指令设置
  canMsg.set_pdm_leftbrush_down(spData->m_nLeftbrushDown);
  canMsg.set_pdm_leftbrush_up(spData->m_nLeftbrushUp);
  canMsg.set_pdm_leftbrush_extend(spData->m_nLeftbrushExtend);
  canMsg.set_pdm_leftbrush_narrow(spData->m_nLeftbrushNarrow);
  canMsg.set_pdm_rightbrush_extend(spData->m_nRightbrushExtend);
  canMsg.set_pdm_rightbrush_narrow(spData->m_nRightbrushNarrow);
  canMsg.set_pdm_rightbrush_down(spData->m_nRightbrushDown);
  canMsg.set_pdm_rightbrush_up(spData->m_nRightbrushUp);
  canMsg.set_pdm_tank_open(spData->m_nTankOpen);
  canMsg.set_pdm_tank_close(spData->m_nTankClose);
  canMsg.set_pdm_nozzle_down(spData->m_nNozzleDown);
  canMsg.set_pdm_nozzle_up(spData->m_nNozzleUp);
  canMsg.set_pdm_extend_relay(spData->m_nExtendRelay);
  canMsg.set_pdm_withdraw_relay(spData->m_nWithdrawRelay);
  canMsg.set_pdm_sewage_loop(spData->m_nSewageLoop);
  canMsg.set_pdm_fan_calibration(spData->m_nFanCalibration);
  canMsg.set_pdm_fan_work_debug(spData->m_nFanWorkDebug);
  canMsg.set_pdm_fan_speed_acc(spData->m_nFanSpeedAcc);
  canMsg.set_pdm_fan_speed_min(spData->m_nFanSpeedMin);
  canMsg.set_pdm_leftbrush_work_debug(spData->m_nLeftBrushWorkDebug);
  canMsg.set_pdm_rightbrushwork_debug(spData->m_nRightBrushWorkDebug);
  canMsg.set_pdm_brush_speed_acc(spData->m_nBrushSpeedAcc);
  canMsg.set_pdm_brush_speed_min(spData->m_nBrushSpeedMin);
  canMsg.set_pdm_spray_pump_debug(spData->m_nSprayPumpDebug);
  canMsg.set_pdm_eps_calibration(spData->m_nEPSCalibration);
  canMsg.set_pdm_work_mode(spData->m_nFanMode);
  canMsg.set_pdm_hppump_work(spData->m_nHighPreClean);
  canMsg.set_pdm_dust_mode(spData->m_nDustSupMode);
  canMsg.set_pdm_tank_tilt(spData->m_nTankTilt);
  canMsg.set_pdm_tank_reset(spData->m_nTankReset);
  canMsg.set_pdm_worklight(spData->m_nWorklight);
  canMsg.set_pdm_work_start(spData->m_nWorkStart);
  canMsg.set_curise_start(spData->m_nCuriseStart);
  canMsg.set_curise_acc(spData->m_nCuriseAcc);
  canMsg.set_curise_dec(spData->m_nCuriseDec);

  std::string tmpdata = "";
  canMsg.SerializeToString(&tmpdata);
  canData->set_data(tmpdata);
  std::string strdata = "";
  if (!canServiceMsg.SerializeToString(&strdata))
  {
    LOGGER->Cowa_Warn("serialize to string error");
  }
  else
  {
    std::string repData = "";
    ZmqReturnCode code = m_ZmqReqIF.request(strdata, repData, 0);
    std::string msg_str = "";
    msg_str.append("set can data:").append(std::to_string((uint32_t)code));
    LOGGER->Cowa_Info(msg_str.c_str());
  }
}

void CCanServer::pushGetCanData(int dataType)
{
  std::unique_lock<std::mutex> guard(m_cmdMutex);
  m_getCanData.push_back(dataType);
  m_ConCmd.notify_one();
  LOGGER->Cowa_Info("push get can data cmd to set................");
}

void CCanServer::processGetCanData(int dataType)
{
  // LOGGER->Cowa_Info("processGetCanData process get data.......");
  if (dataType < 0)
  {
    LOGGER->Cowa_Warn("process get can data is error, check the error...");
    return;
  }
  if (dataType == m_cType.DASHBOARD_DATA) // 0x6E
  {
    // auto spData = std::dynamic_pointer_cast<CDashBoardData>(pdata);
    getUpdateData(CAN_ID_0x6E);
  }
  else if (dataType == m_cType.LIGHTSCREEN_DATA)
  {
    getUpdateData(CAN_ID_0x6F);
  }
  else if (dataType == m_cType.BAR_0x18F413EF_DATA)
  {
    getUpdateData(CAN_ID_0x18F413EF);
  }
  else if (dataType == m_cType.BAR_NETWORK_DATA)
  {
    getNetWorkData();
  }
  else
  {
    std::string msg_str = "";
    msg_str.append(" Data type  is unknow, please check....type : ").append(std::to_string(dataType));
    LOGGER->Cowa_Warn(msg_str.c_str());
  }
}

void CCanServer::getUpdateData(int dataType)
{
  //获取数据请求
  LOGGER->Cowa_Info("get dashboard  data from tbox...............");
  CanServiceMsg canServiceMsg;
  static uint32_t count = 0;
  ++count;
  // canServiceMsg.set_eventid(EVENT_ID_GET_CAN_DATA);
  canServiceMsg.set_eventid(EVENT_ID_HMI_GET_CAN_DATA);
  canServiceMsg.set_seqnum(count);
  auto canData = canServiceMsg.add_candata();
  canData->set_canid(dataType);
  // char buffer[256] = {0x00};
  // canServiceMsg.SerializeToArray(buffer, canServiceMsg.ByteSize());
  // std::string data = buffer;

  std::string strdata = "";
  canServiceMsg.SerializeToString(&strdata);

  std::string repData = "";
  ZmqReturnCode code = m_ZmqReqIF.request(strdata, repData, 0);
  if (code == E_SUCCESS)
  {
    LOGGER->Cowa_Info("[1-1] request success");
  }
  //{
  //    CanServiceMsg canServiceMsg;
  //    canServiceMsg.set_eventid(EVENT_ID_HMI_GET_NETWORK_DATA);
  //    canServiceMsg.set_seqnum(0);
  //    auto canData = canServiceMsg.add_candata();
  //    canData->set_canid(NETWORK_ID_LTE); // TODO::现在信息较少，
  //    std::string data = "";
  //    canServiceMsg.SerializeToString(&data);
  //
  //    std::string repData = "";
  //    ZmqReturnCode code = m_ZmqReqIF.request(data, repData, 0);
  //    if (code == E_SUCCESS)
  //    {
  //        std::cout << "[2-1] request success" << std::endl;
  //    }
  //}
}

bool CCanServer::zmqReqAllData()
{
  //主动请求数据
  LOGGER->Cowa_Info("zmqReqAllData request all data from can...");
  getNetWorkData();
  std::vector<int> ReqCanIdVec;
  ReqCanIdVec.push_back(CAN_ID_0x64);
  ReqCanIdVec.push_back(CAN_ID_0x65);
  ReqCanIdVec.push_back(CAN_ID_0x6E);
  ReqCanIdVec.push_back(CAN_ID_0x6F);
  ReqCanIdVec.push_back(CAN_ID_0x70);
  ReqCanIdVec.push_back(CAN_ID_0x71);
  ReqCanIdVec.push_back(CAN_ID_0x78);
  ReqCanIdVec.push_back(CAN_ID_0x79);
  ReqCanIdVec.push_back(CAN_ID_0x7B);
  ReqCanIdVec.push_back(CAN_ID_0x7C);
  ReqCanIdVec.push_back(CAN_ID_0x7D);
  ReqCanIdVec.push_back(CAN_ID_0x63);
  ReqCanIdVec.push_back(CAN_ID_0x62);
  ReqCanIdVec.push_back(CAN_ID_0x61);
  ReqCanIdVec.push_back(CAN_ID_0x5F);
  ReqCanIdVec.push_back(CAN_ID_0x60);
  ReqCanIdVec.push_back(CAN_ID_0x5E);
  ReqCanIdVec.push_back(CAN_ID_0x5D);
  ReqCanIdVec.push_back(CAN_ID_0x5C);
  ReqCanIdVec.push_back(CAN_ID_0x511);
  ReqCanIdVec.push_back(CAN_ID_0x512);
  ReqCanIdVec.push_back(CAN_ID_0x08FF32F0);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF15EF);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF16EF);
  ReqCanIdVec.push_back(CAN_ID_0x18FF12F7);
  ReqCanIdVec.push_back(CAN_ID_0x18F412EF);
  ReqCanIdVec.push_back(CAN_ID_0x18F413EF);
  ReqCanIdVec.push_back(CAN_ID_0x18F433EF);
  ReqCanIdVec.push_back(CAN_ID_0x18F411EF);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF7902);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF7A02);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF7B02);
  ReqCanIdVec.push_back(CAN_ID_0x0CFF7C02);

  CanServiceMsg canServiceMsg;
  static uint32_t count = 0;
  ++count;
  // canServiceMsg.set_eventid(EVENT_ID_GET_CAN_DATA);
  canServiceMsg.set_eventid(EVENT_ID_HMI_GET_CAN_DATA);
  canServiceMsg.set_seqnum(count);
  for (auto &i : ReqCanIdVec)
  {
    auto canData = canServiceMsg.add_candata();
    canData->set_canid(i);
  }

  std::string strdata = "";
  canServiceMsg.SerializeToString(&strdata);

  std::string repData = "";
  ZmqReturnCode code = m_ZmqReqIF.request(strdata, repData, 0);
  if (code == E_SUCCESS)
  {
    LOGGER->Cowa_Info("******** Req All data request success ********");
    return true;
  }
  else
  {
    LOGGER->Cowa_Info("******** Req All data request faild ********");
    return false;
  }
}

void CCanServer::getNetWorkData()
{
  CanServiceMsg canServiceMsg;
  canServiceMsg.set_eventid(EVENT_ID_HMI_GET_NETWORK_DATA);
  canServiceMsg.set_seqnum(0);
  auto canData = canServiceMsg.add_candata();
  canData->set_canid(NETWORK_ID_LTE); // TODO::现在信息较少，
  std::string data = "";
  canServiceMsg.SerializeToString(&data);

  std::string repData = "";
  ZmqReturnCode code = m_ZmqReqIF.request(data, repData, 0);
  if (code == E_SUCCESS)
  {
    LOGGER->Cowa_Info("[2-1] request success");
  }
}

void CCanServer::parseCanMsg_0x5D(COWA::CanMsg::CanMsg_0x5D canMsg)
{
  LOGGER->Cowa_Info("parse Receive Can Msg 0x5D....");
  std::shared_ptr<CDiagnosisEPSData> data =
      std::make_shared<CDiagnosisEPSData>();
  data->m_nWorkModel = stoi(Util::Int_to_Hex(canMsg.work_model()));
  data->m_nTargeTangle = canMsg.targetangle() - 32768;
  data->m_nWheelPalstance = canMsg.wheelpalstance() - 32768;

  data->m_nAutoCMD_model = stoi(Util::Int_to_Hex(canMsg.autocmd_model()));
  data->m_nCurrentangle = canMsg.currentangle() - 32768;
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_EPS_DATA);
}
void CCanServer::parseCanMsg_0x61(COWA::CanMsg::CanMsg_0x61 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x61....");
  std::shared_ptr<CDiagnosisBrakeData> data = std::make_shared<CDiagnosisBrakeData>();
  // std::shared_ptr<CDiagnosisBrakeData> data = m_Brake61Data;
  data->m_nEHB_WorkSts = stoi(Util::Int_to_Hex(canMsg.ehb_worksts()));
  data->m_nBrakePress = canMsg.brakepress();
  data->m_npedalPercent = canMsg.pedal_percent();
  data->m_nPistonDisplacement = canMsg.pistondisplacement() * 0.001 - 5;
  data->m_nTargetPress = canMsg.targetpress();

  data->m_nParkReq = stoi(Util::Int_to_Hex(canMsg.parkreq()));
  data->m_nBrakeSts = stoi(Util::Int_to_Hex(canMsg.brakests()));
  data->m_nfaultLevel = stoi(Util::Int_to_Hex(canMsg.faultlevel()));
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BRAKE_DATA);
}

void CCanServer::parseCanMsg_0x63(COWA::CanMsg::CanMsg_0x63 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x63....");
  std::shared_ptr<CDiagnosis12VDCData> data = std::make_shared<CDiagnosis12VDCData>();
  // std::shared_ptr<CDiagnosis12VDCData> data = m_Dc12VData;
  data->m_nOutEnable = canMsg.out_enable();
  data->m_nState = canMsg.state();
  data->m_nINVoltage = canMsg.in_voltage() * 2;
  data->m_nINCurrent = canMsg.in_current() * 0.05;
  data->m_nDCDCTemperature = canMsg.dcdc_temperature() - 40;
  data->m_nOverTemperature = canMsg.over_temperature();

  data->m_nOut_voltage = canMsg.out_voltage() * 0.125;
  data->m_nOut_current = canMsg.out_current() * 0.05;
  data->m_nIn_over_current = canMsg.in_over_current();
  data->m_nOut_over_current = canMsg.out_over_current();
  data->m_nIn_over_voltage = canMsg.in_less_voltage();
  data->m_nIn_less_voltage = canMsg.out_over_voltage();
  data->m_nOut_over_voltage = canMsg.out_over_voltage();
  data->m_nOut_less_voltage = canMsg.out_less_voltage();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_12VDC_DATA);
}

void CCanServer::parseCanMsg_0x6E(COWA::CanMsg::CanMsg_0x6E canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x6E....");
  std::shared_ptr<CDashBoardData> data = std::make_shared<CDashBoardData>();
  // std::shared_ptr<CDashBoardData> data = m_BoardData;
  data->m_nTravelDistance =
      canMsg.travel_distance() * 0.1; //乘以因子换算出实际数据
  data->m_nSpeed = canMsg.vehice_speed();
  data->m_fCruiseSpeed = canMsg.curise_speed();
  data->m_nCuriseOff = canMsg.curise_off();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DASHBOARD_DATA);
}

void CCanServer::parseCanMsg_0x6F(COWA::CanMsg::CanMsg_0x6F canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x6F....");
  std::shared_ptr<CLightScreenData> data = std::make_shared<CLightScreenData>();
  // std::shared_ptr<CLightScreenData> data = m_LightData;
  data->m_bPositionLight = canMsg.locationlight_sts();
  data->m_bHeadLights = canMsg.biglight_sts();
  data->m_bLeftSteering = canMsg.turnleftlight_sts();
  data->m_bRightSteering = canMsg.turnrightlight_sts();
  data->m_bWorkLight = canMsg.worklight_sts();
  data->m_bLightParking = canMsg.park_sts();
  data->m_bBatteryFailure = canMsg.batteryfault_normal();
  data->m_bHighVoltageCutOff = canMsg.batteryhvturnoff();
  data->m_bOverheatAlarm = canMsg.motoroverheat_warning();
  data->m_bVehicleFailure = canMsg.vehiclefault();
  data->m_bCriticalBatteryFailure = canMsg.batteryfault_major();
  data->m_strVehicleChargingTips =
      QString::number(canMsg.vehiclecharge_remind(), 10);
  data->m_bVehicleready = canMsg.vehicleready();
  data->m_bSeatStatus = canMsg.seat_sts();
  data->m_nSoftwareVersion =
      canMsg.software_version() * 0.1; //乘以因子换算出实际数据
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.LIGHTSCREEN_DATA);
  //电池是否是充电状态
  uint32_t isCharge = canMsg.charge_sts();
  Q_EMIT updateCanMsg_0x6FToUIBarHandle(isCharge);
}

void CCanServer::parseCanMsg_0x70(COWA::CanMsg::CanMsg_0x70 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x70....");
  std::shared_ptr<CDiagnosisIOData> data = std::make_shared<CDiagnosisIOData>();
  // std::shared_ptr<CDiagnosisIOData> data = m_IO70Data;
  data->m_nTurnLeft = canMsg.turnleft_i();
  data->m_nTurnRight = canMsg.turnright_i();
  data->m_nWorkFlag = canMsg.workflag_i();
  data->m_nTrunOnFlag = canMsg.trunonflag_i();
  data->m_nLowBeam = canMsg.lowbeam_i();
  data->m_nSmallLight = canMsg.small_light_i();
  data->m_nAutoDrive = canMsg.autodrive_i();
  data->m_nEmergencyFlash = canMsg.emergencyflash_i();
  data->m_nStop = canMsg.stop_i();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_IO_DATA);
}

void CCanServer::parseCanMsg_0x08FF32F0(
    COWA::CanMsg::CanMsg_0x08FF32F0 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x08FF32F0....");
  std::shared_ptr<CDiagnosisMainDriData> data = std::make_shared<CDiagnosisMainDriData>();
  // std::shared_ptr<CDiagnosisMainDriData> data = m_MainDriData;
  int motSpeed = canMsg.motspeed() - 30000; //转速偏移量
  if (motSpeed < 10 && motSpeed > -10)      //倒车的时候转速是负数要考虑
  {
    motSpeed = 0;
  }
  else
  {
    motSpeed /= 10; //忽略个位显示处理
    motSpeed *= 10;
  }
  data->m_nMotSpeed = motSpeed;
  data->m_nMotTorque = canMsg.mottorque();
  data->m_nRotaryWarning = canMsg.rotarywarning();
  data->m_nIntePass = canMsg.intepass();
  data->m_nGearSts = canMsg.gearsts();
  data->m_nBackBrake = canMsg.backbrake();
  data->m_nAccPdlSts = canMsg.accpdlsts();
  data->m_nBusbardischarg = canMsg.busbardischarg();
  data->m_nBrakeActive = canMsg.brakeactive();
  data->m_nMotSpeedValid = canMsg.motspeedvalid();

  data->m_nOverCurrentFault = canMsg.overcurrentfault();
  data->m_nPowerLimtWarning = canMsg.powerlimtwarning();
  data->m_nMCUTempWarning = canMsg.mcutempwarning();
  data->m_nMotTempWarning = canMsg.mottempwarning();
  data->m_nBusbarOverVoltFault = canMsg.busbarovervoltfault();
  data->m_nBusbarLessVoltFault = canMsg.busbarlessvoltfault();
  data->m_nSpeedControlValid = canMsg.speedcontrolvalid();
  data->m_nGeneralFaultWarning = canMsg.generalfaultwarning();
  data->m_nGearWarning = canMsg.gearwarning();
  data->m_nHoldReq = canMsg.holdreq();
  data->m_nApdlPercent = canMsg.apdlpercent();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_MAINDRI_DATA);
}

void CCanServer::parseCanMsg_0x18FF12F7(
    COWA::CanMsg::CanMsg_0x18FF12F7 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x18FF12F7....");
  std::shared_ptr<CDiagnosis48VDCData> data =
      std::make_shared<CDiagnosis48VDCData>();
  data->m_nOUTVolt = canMsg.outvolt() * 0.1;
  data->m_nOUTCurrent = canMsg.outcurrent() * 0.1;
  data->m_nDCSts = canMsg.dcsts();
  data->m_nOUTCutDownSts = canMsg.outcutdownsts();
  data->m_nFaultLevel = canMsg.faultlevel();
  data->m_nRadiatorTemp = canMsg.radiatortemp() - 40;

  data->m_nINCutDownSts = canMsg.incutdownsts();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_48VDC_DATA);
}

void CCanServer::parseCanMsg_0x18F412EF(
    COWA::CanMsg::CanMsg_0x18F412EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x18F412EF....");
  std::shared_ptr<CDiagnosisBatteryData> data = std::make_shared<CDiagnosisBatteryData>();
  // std::shared_ptr<CDiagnosisBatteryData> data = m_BatteryData;
  data->m_nBattOverTempFault = canMsg.battovertempfault();
  data->m_nInsulationFault = canMsg.insulationfault();
  data->m_nBattLessElectWarning = canMsg.battlesselectwarning();
  data->m_nPositionRelaySts = canMsg.positionrelaysts();
  data->m_nSOHWarning = canMsg.sohwarning();
  data->m_nCANerror = canMsg.canerror();
  data->m_nCCsignConnetSts = canMsg.ccsignconnetsts();
  data->m_nPrechargeSts = canMsg.prechargests();
  data->m_nCellLessVoltWarning = canMsg.celllessvoltwarning();
  data->m_nCellOverVoltWarning = canMsg.cellovervoltwarning();
  data->m_nPositiveRelayAdhesion = canMsg.positiverelayadhesion();
  data->m_nPTCRelayAdhesion = canMsg.ptcrelayadhesion();
  data->m_nPTCRelaySts = canMsg.ptcrelaysts();
  data->m_nBattVoltImbalance = canMsg.battvoltimbalance();
  data->m_nDischgOverCurrent = canMsg.dischgovercurrent();
  data->m_nChgOverCurrent = canMsg.chgovercurrent();
  data->m_nItselfCANerror = canMsg.itselfcanerror();
  data->m_nBattGeneralLessVolt = canMsg.battgenerallessvolt();
  data->m_nBattGeneralOverVolt = canMsg.battgeneralovervolt();
  data->m_nBMSHardwareFault = canMsg.bmshardwarefault();
  data->m_nBMSsts = canMsg.bmssts();
  data->m_nBackChgEnb = canMsg.backchgenb();
  data->m_nWarmModel = canMsg.warmmodel();
  data->m_nBalanceSts = canMsg.balancests();
  data->m_nSOCLow = canMsg.soclow();
  data->m_nCurrentSensorFault = canMsg.currentsensorfault();
  data->m_nTempSensorFault = canMsg.tempsensorfault();
  data->m_nNegativeRelayAdhesion = canMsg.negativerelayadhesion();
  data->m_nPrechgRelaySts = canMsg.prechargests();
  data->m_nNegativeRelaySts = canMsg.negativerelaysts();
  data->m_nDCchgPositiveRelaySts = canMsg.dcchgpositiverelaysts();
  data->m_nDCchgGunOverTempFault = canMsg.dcchggunovertempfault();
  data->m_nCellCollectLineCutFault = canMsg.cellcollectlinecutfault();
  data->m_nPrechgRelayAdhesion = canMsg.prechgrelayadhesion();
  data->m_nDCchgPositiveRelayAdhesion = canMsg.dcchgpositiverelayadhesion();
  data->m_nWakeUpType = canMsg.wakeuptype();
  data->m_nBattTempImbalanceFault = canMsg.batttempimbalancefault();
  data->m_nBattLessTempFault = canMsg.battlesstempfault();
  data->m_nWarmSts = canMsg.warmsts();

  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BATTERY_DATA);
}

void CCanServer::parseCanMsg_0x0CFF7902(
    COWA::CanMsg::CanMsg_0x0CFF7902 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF7902....");
  std::shared_ptr<CDiagnosisFan902Data> data =
      std::make_shared<CDiagnosisFan902Data>();
  data->m_nFaultLevl = canMsg.faultlevl();
  data->m_nModSts = canMsg.modsts();
  data->m_nEnSts = canMsg.ensts();
  data->m_nPrechargeAllow = canMsg.precharge_allow();
  data->m_nDirSts = canMsg.dirsts();
  data->m_nActTorValid = canMsg.acttor_valid();
  data->m_nActSpdValid = canMsg.actspd_valid();
  data->m_nActTor = canMsg.acttor() * 0.25 - 5000;
  data->m_nActSpd = canMsg.actspd() - 12000;
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_FAN902_DATA);
}

void CCanServer::parseCanMsg_0x0CFF7A02(
    COWA::CanMsg::CanMsg_0x0CFF7A02 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF7A02....");
  std::shared_ptr<CDiagnosisFanA02Data> data =
      std::make_shared<CDiagnosisFanA02Data>();
  data->m_nDCVolt = canMsg.dcvolt();
  data->m_nDCCur = canMsg.dccur() * 0.125 - 1000;
  data->m_nACCur = canMsg.accur() * 0.125;

  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_FANA02_DATA);
}

void CCanServer::parseCanMsg_0x0CFF7B02(
    COWA::CanMsg::CanMsg_0x0CFF7B02 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF7B02....");
  std::shared_ptr<CDiagnosisFanB02Data> data =
      std::make_shared<CDiagnosisFanB02Data>();
  data->m_nMotorMinAvaTor = canMsg.motorminavator() * 0.25 - 5000;
  data->m_nMotorMaxAvaTor = canMsg.motormaxavator() * 0.25;
  data->m_nMotorIGBTTemp = canMsg.motorigbttemp() - 40;
  data->m_nMTemp = canMsg.mtemp() - 40;
  data->m_nCTemp = canMsg.ctemp() - 40;

  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_FANB02_DATA);
}

void CCanServer::parseCanMsg_0x0CFF7C02(
    COWA::CanMsg::CanMsg_0x0CFF7C02 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF7C02....");
  std::shared_ptr<CDiagnosisFanC02Data> data =
      std::make_shared<CDiagnosisFanC02Data>();
  data->m_nMOvSpdSts = canMsg.movspdsts();
  data->m_nMBlockSts = canMsg.mblocksts();
  data->m_nMOvTempSts = canMsg.movtempsts();
  data->m_nMOvCurSts = canMsg.movcursts();
  data->m_nMShrSts = canMsg.mshrsts();
  data->m_nMShrGrdSts = canMsg.mshrgrdsts();
  data->m_nCOvTempSts = canMsg.covtempsts();
  data->m_nCAuxBatSts = canMsg.cauxbatsts();
  data->m_nPreChaSts = canMsg.prechasts();
  data->m_nIGBTModSts = canMsg.igbtmodsts();
  data->m_nIGBTOvTempSts = canMsg.igbtovtempsts();
  data->m_nIGBTOvCurSts = canMsg.igbtovcursts();
  data->m_nCOvVoltSts = canMsg.covvoltsts();
  data->m_nCLowVoltSts = canMsg.clowvoltsts();
  data->m_nIGBTTempSenSts = canMsg.igbttempsensts();
  data->m_nCANFault = canMsg.canfault();
  data->m_nMTempSenSts = canMsg.mtempsensts();
  data->m_nCTempSenSts = canMsg.ctempsensts();
  data->m_nCVoltSenSts = canMsg.cvoltsensts();
  data->m_nCCurSenSts = canMsg.ccursensts();
  data->m_nACCurSenSts = canMsg.accursensts();
  data->m_nCTranFaultSts = canMsg.ctranfaultsts();
  data->m_nMCutOffSts = canMsg.mcutoffsts();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_FANC02_DATA);
}

void CCanServer::parseCanMsg_0x511(COWA::CanMsg::CanMsg_0x511 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x511....");
  std::shared_ptr<CDiagnosisSweepDiskData> data = std::make_shared<CDiagnosisSweepDiskData>();
  // std::shared_ptr<CDiagnosisSweepDiskData> data = m_SweepLeftData;
  data->m_nMainVoltage = canMsg.spr_main_voltage();
  data->m_nCurrentMotcurrent = canMsg.spr_currentmotcurrent();
  data->m_nEnableSts = canMsg.spr_enable_sts();
  data->m_nWheelSts = canMsg.spr_wheel_sts();
  data->m_nMotTemperature = canMsg.spr_mot_temperature();
  data->m_nMotCurrentSpeed = canMsg.spr_motcurrentspeed();
  data->m_nOverCurrent = canMsg.spr_overcurrent();
  data->m_nOverVoltage = canMsg.spr_overvoltage511();
  data->m_nOverTemperature = canMsg.spr_overtemperature();
  data->m_nLochedRotor = canMsg.spr_lochedrotor();
  data->m_nHallSignalError = canMsg.spr_hallsignalerror();
  data->m_nMotFualtItself = canMsg.spr_motfualt_itself();
  data->m_nDataType = m_cType.DIAGNOSIS_LEFTSWEEP_DATA;
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_LEFTSWEEP_DATA);
}
void CCanServer::parseCanMsg_0x512(COWA::CanMsg::CanMsg_0x512 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x512....");
  std::shared_ptr<CDiagnosisSweepDiskData> data = std::make_shared<CDiagnosisSweepDiskData>();
  // std::shared_ptr<CDiagnosisSweepDiskData> data = m_SweepRightData;
  data->m_nMainVoltage = canMsg.spl_main_voltage();
  data->m_nCurrentMotcurrent = canMsg.spl_currentmotcurrent();
  data->m_nEnableSts = canMsg.spl_enable_sts();
  data->m_nWheelSts = canMsg.spl_wheel_sts();
  data->m_nMotTemperature = canMsg.spl_mot_temperature();
  data->m_nMotCurrentSpeed = canMsg.spl_motcurrentspeed();
  data->m_nOverCurrent = canMsg.spl_overcurrent511();
  data->m_nOverVoltage = canMsg.spl_overvoltage511();
  data->m_nOverTemperature = canMsg.spl_overtemperature();
  data->m_nLochedRotor = canMsg.spl_lochedrotor();
  data->m_nHallSignalError = canMsg.spl_hallsignalerror();
  data->m_nMotFualtItself = canMsg.spl_motfualt_itself();
  data->m_nDataType = m_cType.DIAGNOSIS_RIGHTSWEEP_DATA;
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_RIGHTSWEEP_DATA);
}

void CCanServer::parseCanMsg_0x0CFF15EF(
    COWA::CanMsg::CanMsg_0x0CFF15EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF15EF....");
  std::shared_ptr<CDiagnosisHigPreDump15Data> data = std::make_shared<CDiagnosisHigPreDump15Data>();
  // std::shared_ptr<CDiagnosisHigPreDump15Data> data = m_HigPre15Data;
  data->m_nMOTspeed = canMsg.motspeed() * 0.5;

  data->m_nMOTBusbarVolt = canMsg.motbusbarvolt();
  data->m_nMotTemp = canMsg.mottemp() - 40;
  data->m_nIGBTTemp = canMsg.igbttemp() - 40;
  data->m_nMOT_current_AC = canMsg.mot_current_ac();
  data->m_nMOTFaultCodeSign = canMsg.motfaultcodesign();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_HIGPREPUM15_DATA);
}
void CCanServer::parseCanMsg_0x0CFF16EF(
    COWA::CanMsg::CanMsg_0x0CFF16EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x0CFF16EF....");
  std::shared_ptr<CDiagnosisHigPreDump16Data> data = std::make_shared<CDiagnosisHigPreDump16Data>();
  // std::shared_ptr<CDiagnosisHigPreDump16Data> data = m_HigPre16Data;
  data->m_nMCUintSts = stoi(Util::Int_to_Hex(canMsg.mcuintsts()));
  data->m_nMCUModelSts = canMsg.mcumodelsts();

  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_HIGPREPUM16_DATA);
}

void CCanServer::parseCanMsg_0x62(COWA::CanMsg::CanMsg_0x62 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x62....");
  std::shared_ptr<CDiagnosisCommuData> data =
      std::make_shared<CDiagnosisCommuData>();
  data->m_nBMS_CANerror = canMsg.bms_canerror();
  data->m_nMCU_CANerror = canMsg.mcu_canerror();

  data->m_nEHB_CANerror = canMsg.ehb_canerror();
  data->m_nEPB_CANerror = canMsg.epb_canerror();
  data->m_nEPS_CANerror = canMsg.eps_canerror();
  data->m_nDC48V_CANerror = canMsg.dc48v_canerror();
  data->m_nAC_CANerror = canMsg.ac_canerror();
  data->m_nADU_CANerror = canMsg.adu_canerror();
  data->m_nICU_CANerror = canMsg.icu_canerror();
  data->m_nDC12V_CANerror = canMsg.dc12v_canerror();
  data->m_nGPS_CANerror = canMsg.gps_canerror();
  data->m_nFJI_CANerror = canMsg.fji_canerror();
  data->m_nWP_CANerror = canMsg.wp_canerror();
  data->m_nSPL_CANerror = canMsg.spl_canerror();
  data->m_nSPR_CANerror = canMsg.spr_canerror();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_COMMUNI_DATA);
}

void CCanServer::parseCanMsg_0x60(COWA::CanMsg::CanMsg_0x60 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x60....");
  std::shared_ptr<CDiagnosisBrake60Data> data = std::make_shared<CDiagnosisBrake60Data>();
  // std::shared_ptr<CDiagnosisBrake60Data> data = m_Brake60Data;
  data->m_nBrakeSts = canMsg.brake_sts();

  data->m_nParklight_sts = canMsg.parklight_sts();
  data->m_nFaultlight_sts = canMsg.faultlight_sts();
  data->m_nSwitch_sts = canMsg.switch_sts();
  data->m_nSystem_sts = canMsg.system_sts();
  data->m_nFault_message = stoi(Util::Int_to_Hex(canMsg.fault_message()));

  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BRAKE60_DATA);
}

// void CCanServer::parseCanMsg_0x18F413EF(COWA::CanMsg::CanMsg_0x18F413EF
// canMsg)
// {
//     std::cout << "parse Receive Can Msg 0x18F413EF...." << std::endl;
//     uint32_t volt = canMsg.generalvolt();
//     uint32_t elec = canMsg.generalcurrent();
//     uint32_t soc = canMsg.soc();
//     Q_EMIT updateCanMsg_0x18F413EFToUIBarHandle(volt, elec, soc);
// }

void CCanServer::parseNetWorkMsg(const std::string &networkData)
{
  COWA::Network::Moderm moderm;
  if (moderm.ParseFromString(networkData))
  {
    // NOTE::空的也可以反序列化成功
    LOGGER->Cowa_Info(("parse Receive Moderm Msg, data:" + moderm.DebugString()).c_str());

    std::string csq = moderm.csq();
    std::string cops = moderm.cops();
    // TODO 判断逻辑需修改
    if (csq == "'ERR'" || csq == "ERR")
    {
      LOGGER->Cowa_Warn("ERROR: csq error");
    }
    else if (cops == "'ERR'" || cops == "ERR")
    {
      LOGGER->Cowa_Warn("ERROR: cops error");
    }
    else
    {
      //持久化网络消息
      LevelDBManager::instance().setConfig(NETWORK_MSG_SAVE_KEY, networkData);
      Q_EMIT updateModermToUIBarHandle(csq.c_str(), cops.c_str());
    }
  }
  else
  {
    LOGGER->Cowa_Warn("[3] canMsg parse data error");
  }
}

void CCanServer::parseMediaMsg(const std::string &mediaData)
{
  // 1、mediaData into uint8
  CanServiceMsg msg;
  msg.ParseFromString(mediaData);
  const char *data = mediaData.data();
  qDebug() << "***********data = " << data;
}

void CCanServer::parseCanMsg_0x71(COWA::CanMsg::CanMsg_0x71 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x71....");
  std::shared_ptr<CDiagnosisIO71Data> data =
      std::make_shared<CDiagnosisIO71Data>();
  data->m_nBrakeOil_line = canMsg.brakeoil_line();
  data->m_nBox_up = canMsg.box_up();
  data->m_nBox_dowm = canMsg.box_dowm();
  data->m_nBox_Arrive = canMsg.box_arrive();
  data->m_nChengGan_Arrive = canMsg.chenggan_arrive();
  data->m_nEban_switch = canMsg.eban_switch();
  data->m_nBoxDoor_switch = canMsg.boxdoor_switch();
  data->m_nLeftBrush_arrive = canMsg.leftbrush_arrive();
  data->m_nRightBrush_arrive = canMsg.rightbrush_arrive();
  data->m_nLeftBrush_open = canMsg.leftbrush_open();
  data->m_nLeftBrush_close = canMsg.leftbrush_close();
  data->m_nRightBrush_open = canMsg.rightbrush_open();
  data->m_nRightBrush_close = canMsg.rightbrush_close();
  data->m_ndustbin_returnSwitch = canMsg.dustbin_returnswitch();
  data->m_nWaterLine_show = canMsg.waterline_show();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_IO71_DATA);
}
void CCanServer::parseCanMsg_0x78(COWA::CanMsg::CanMsg_0x78 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x78....");
  std::shared_ptr<CDiagnosisIO78Data> data =
      std::make_shared<CDiagnosisIO78Data>();
  data->m_nTurnLeftLight = canMsg.turnleftlight();
  data->m_nTurnRightLight = canMsg.turnrightlight();
  data->m_nLowBeam = canMsg.lowbeam();
  data->m_nWorkLight_relay = canMsg.worklight_relay();
  data->m_nsmall_light = canMsg.small_light();
  data->m_nreversing_light = canMsg.reversing_light();
  data->m_nbrake_light = canMsg.brake_light();
  data->m_nReversing_buzzer = canMsg.reversing_buzzer();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_IO78_DATA);
}

void CCanServer::parseCanMsg_0x79(COWA::CanMsg::CanMsg_0x79 canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x79....");
  std::shared_ptr<CDiagnosisIO79Data> data =
      std::make_shared<CDiagnosisIO79Data>();
  data->m_nBoxDoor_open = canMsg.boxdoor_open();
  data->m_nBoxDoor_close = canMsg.boxdoor_close();
  data->m_nLeftBrush_up = canMsg.leftbrush_up();
  data->m_nLeftBrush_down = canMsg.leftbrush_down();
  data->m_nLeftBrush_open = canMsg.leftbrush_open();
  data->m_nLeftBrush_close = canMsg.leftbrush_close();
  data->m_nRightBrush_up = canMsg.rightbrush_up();
  data->m_nRightBrush_down = canMsg.rightbrush_down();
  data->m_nRightBrush_open = canMsg.rightbrush_open();
  data->m_nRightBrush_close = canMsg.rightbrush_close();
  data->m_nEban_switch_open = canMsg.eban_switch_open();
  data->m_nEban_switch_close = canMsg.eban_switch_close();
  data->m_nXiZwitch_up = canMsg.xizwitch_up();
  data->m_nXiZwitch_down = canMsg.xizwitch_down();
  data->m_nDustbin_up = canMsg.dustbin_up();
  data->m_nDustbin_down = canMsg.dustbin_down();
  data->m_nLVWaterRoad_relay = canMsg.lvwaterroad_relay();
  data->m_nSewagecyclevalve = canMsg.sewagecyclevalve();
  data->m_nDelayCutDown = canMsg.delaycutdown();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_IO79_DATA);
}

void CCanServer::parseCanMsg_0x18F413EF(
    COWA::CanMsg::CanMsg_0x18F413EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x18F413EF....");
  std::shared_ptr<CDiagnosisBattery13EFData> data = std::make_shared<CDiagnosisBattery13EFData>();
  // std::shared_ptr<CDiagnosisBattery13EFData> data = m_Battery13Data;
  data->m_nGeneralVolt = canMsg.generalvolt() * 0.1;
  data->m_nGeneralCurrent = canMsg.generalcurrent() * 0.1 - 500;
  data->m_nSOC = canMsg.soc() * 0.1;
  data->m_nBattSerialData = canMsg.battserialdata();
  data->m_nCellVoltSensorFault = canMsg.cellvoltsensorfault();
  data->m_nGeneralVoltSensorFault = canMsg.generalvoltsensorfault();
  data->m_n12VLessVolt = canMsg.less12vvolt();
  data->m_n12VOverVolt = canMsg.over12vvolt();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BATTERY13EF_DATA);
  Q_EMIT updateCanMsg_0x18F413EFToUIBarHandle(
      canMsg.generalvolt(), canMsg.generalcurrent(), canMsg.soc());
}

void CCanServer::parseCanMsg_0x18F433EF(
    COWA::CanMsg::CanMsg_0x18F433EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x18F433EF....");
  std::shared_ptr<CDiagnosisBattery33EFData> data = std::make_shared<CDiagnosisBattery33EFData>();
  // std::shared_ptr<CDiagnosisBattery33EFData> data = m_Battery33Data;
  data->m_nBattMaxTemp = canMsg.battmaxtemp() - 40;
  data->m_nBattMaxTempCode = canMsg.battmaxtempcode();
  data->m_nBattMinTemp = canMsg.battmintemp() - 40;
  data->m_nBattMinTempCode = canMsg.battmintempcode();
  data->m_nDCchgGunBaseTemp0 = canMsg.dcchggunbasetemp0() - 40;
  data->m_nDCchgGunBaseTemp1 = canMsg.dcchggunbasetemp1() - 40;
  data->m_nAverageTemp = canMsg.averagetemp() - 40;
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BATTERY33EF_DATA);
}

void CCanServer::parseCanMsg_0x18F411EF(
    COWA::CanMsg::CanMsg_0x18F411EF canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x18F411EF....");
  std::shared_ptr<CDiagnosisBattery11EFData> data = std::make_shared<CDiagnosisBattery11EFData>();
  // std::shared_ptr<CDiagnosisBattery11EFData> data = m_Battery11Data;
  data->m_nSystemFaultLevel = canMsg.systemfaultlevel();
  data->m_nHVlock = canMsg.hvlock();
  data->m_nPowerDownReq = canMsg.powerdownreq();
  data->m_nBMSMaxDischgPower = canMsg.bmsmaxdischgpower();
  data->m_nBMSMaxChgPower = canMsg.bmsmaxchgpower();
  data->m_nDCchgVoltDemand = canMsg.dcchgvoltdemand() * 0.1;
  data->m_nDCchgCurrentDemand = canMsg.dcchgcurrentdemand() * 0.1 - 400;
  data->m_nSystemStsCode = canMsg.systemstscode();
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BATTERY11EF_DATA);
}

void CCanServer::parseCanMsg_0x5F(COWA::CanMsg::CanMsg_0x5F canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x5F....");
  std::shared_ptr<CDiagnosisBrake5FData> data = std::make_shared<CDiagnosisBrake5FData>();
  // std::shared_ptr<CDiagnosisBrake5FData> data = m_Brake5FData;
  data->m_nfaultCode1 = stoi(Util::Int_to_Hex(canMsg.faultcode1()));
  data->m_nfaultCode2 = stoi(Util::Int_to_Hex(canMsg.faultcode2()));
  data->m_nfaultCode3 = stoi(Util::Int_to_Hex(canMsg.faultcode3()));
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_BRAKE5F_DATA);
}

void CCanServer::parseCanMsg_0x5C(COWA::CanMsg::CanMsg_0x5C canMsg)
{
  // LOGGER->Cowa_Info("parse Receive Can Msg 0x5C....");
  std::shared_ptr<CDiagnosisEPS5CData> data =
      std::make_shared<CDiagnosisEPS5CData>();
  data->m_nOut_torque = canMsg.out_torque() - 32770;
  data->m_nTarget_torque = canMsg.target_torque() - 32770;
  data->m_nFaultCode_92 = stoi(Util::Int_to_Hex(canMsg.faultcode_92()));
  pushSubData(std::static_pointer_cast<IData>(data));
  // pushSubDataType(m_cType.DIAGNOSIS_EPS5C_DATA);
}

void CCanServer::zmqSubCb(const std::string &topic, const std::string &data)
{
  //#include "CanIdMsgMap.hpp"
  // if中为请求响应消息
  if (topic == TOPIC_REP_EVENT_ID_HMI_GET_CAN_DATA)
  {
    if (data.empty())
    {
      LOGGER->Cowa_Info("[2] data empty");
      return;
    }
    CanServiceMsg msg;
    if (msg.ParseFromString(data))
    {
      int canDataSize = msg.candata_size();
      if (canDataSize == 0)
      {
        LOGGER->Cowa_Info("[2] dataSize zero");
        return;
      }
      else
      {
        for (int i = 0; i < canDataSize; i++)
        {
          const auto &candatapkg = msg.candata(i);
          topicMsg(candatapkg.canid(), "", candatapkg.data(), true);
          // if (msg.candata(i).canid() == CAN_ID_0x6E)
          //{
          //     COWA::CanMsg::CanMsg_0x6E canMsg;
          //     if (canMsg.ParseFromString(
          //             msg.candata(i).data()))
          //     { // NOTE::空的也可以反序列化成功
          //         parseCanMsg_0x6E(canMsg);
          //         std::cout << "[0x6E] sucess, data:" << canMsg.DebugString()
          //         << std::endl;
          //     }
          //     else
          //     {
          //         std::cout << "[0x6E] anMsg parse data error" << std::endl;
          //     }
          // }
          // else if (msg.candata(i).canid() == CAN_ID_0x6F)
          //{
          //     COWA::CanMsg::CanMsg_0x6F canMsg;
          //     if (canMsg.ParseFromString(
          //             msg.candata(i).data()))
          //     { // NOTE::空的也可以反序列化成功
          //         parseCanMsg_0x6F(canMsg);
          //         std::cout << "[0x6F] sucess, data:" << canMsg.DebugString()
          //         << std::endl;
          //     }
          //     else
          //     {
          //         std::cout << "[0x6F] anMsg parse data error" << std::endl;
          //     }
          // }
          // else if (msg.candata(i).canid() == CAN_ID_0x18F413EF)
          //{
          //     COWA::CanMsg::CanMsg_0x18F413EF canMsg;
          //     if (canMsg.ParseFromString(msg.candata(i).data()))
          //     {
          //         std::cout << "[0x18F413EF] success, data:" <<
          //         canMsg.DebugString() << std::endl;
          //         parseCanMsg_0x18F413EF(canMsg);
          //     }
          //     else
          //     {
          //         std::cout << "[0x18F413EF] anMsg parse data error" <<
          //         std::endl;
          //     }
          // }
        }
      }
    }
    else
    {
      LOGGER->Cowa_Warn("[2] parse error");
    }
  }
  else if (topic == TOPIC_REP_EVENT_ID_HMI_GET_NETWORK_DATA)
  {
    LOGGER->Cowa_Info("Deal Net Work Info ......");
    if (data.empty())
    {
      LOGGER->Cowa_Info("[3] data empty");
      return;
    }

    CanServiceMsg msg;
    if (msg.ParseFromString(data))
    {
      int canDataSize = msg.candata_size();
      if (canDataSize != 1)
      {
        LOGGER->Cowa_Info("[3] dataSize not one");
        return;
      }
      else
      {
        const auto &candatapkg = msg.candata(0);
        const std::string &networkdata = candatapkg.data();
        if (candatapkg.canid() == NETWORK_ID_LTE)
        {
          //解析网络消息
          parseNetWorkMsg(networkdata);
        }
      }
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
    }
  }
  else if (topic == TOPIC_NETWORK_MSG)
  {
    LOGGER->Cowa_Info("Receive Pub Net Work Info ......");
    if (data.empty())
    {
      LOGGER->Cowa_Info("[TOPIC_NETWORK_MSG] data empty");
      return;
    }
    parseNetWorkMsg(data);
  }
  else
  {
    // canserver服务器主动推送的消息
    topicMsg(0, topic, data, true);
  }
}

void CCanServer::zmqH264SubCb(const std::string &topic, const std::string &data)
{
  // TODO 临时topic
  LOGGER->Cowa_Info(("zmqH264SubCb::Receive Reverse Image Info ......, topic=[" + topic+"]").c_str());
  if (data.empty())
  {
    LOGGER->Cowa_Info("[VehicleReverse_H264Data] data empty");
    return;
  }
  // proceFrame(data);
  Q_EMIT sendMediaData(data);
}

void CCanServer::topicMsg(uint32_t canId, const std::string &topic,
                          const std::string &data, bool isSave)
{
  if (canId == CAN_ID_0x6E || topic == TOPIC_CAN_ID_0x6E)
  {
    COWA::CanMsg::CanMsg_0x6E canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x6E)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x6E(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x6F || topic == TOPIC_CAN_ID_0x6F)
  {
    COWA::CanMsg::CanMsg_0x6F canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x6F)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x6F(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x18F413EF || topic == TOPIC_CAN_ID_0x18F413EF)
  {
    COWA::CanMsg::CanMsg_0x18F413EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x18F413EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x18F413EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x08FF32F0 || topic == TOPIC_CAN_ID_0x08FF32F0)
  {
    COWA::CanMsg::CanMsg_0x08FF32F0 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x08FF32F0)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x08FF32F0(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x70 || topic == TOPIC_CAN_ID_0x70)
  {
    COWA::CanMsg::CanMsg_0x70 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x70)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x70(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x18F412EF || topic == TOPIC_CAN_ID_0x18F412EF)
  {
    COWA::CanMsg::CanMsg_0x18F412EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x18F412EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x18F412EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x5D || topic == TOPIC_CAN_ID_0x5D)
  {
    COWA::CanMsg::CanMsg_0x5D canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x5D)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x5D(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x61 || topic == TOPIC_CAN_ID_0x61)
  {
    COWA::CanMsg::CanMsg_0x61 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x61)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x61(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x63 || topic == TOPIC_CAN_ID_0x63)
  {
    COWA::CanMsg::CanMsg_0x63 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x63)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x63(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x18FF12F7 || topic == TOPIC_CAN_ID_0x18FF12F7)
  {
    COWA::CanMsg::CanMsg_0x18FF12F7 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x18FF12F7)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x18FF12F7(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF7902 || topic == TOPIC_CAN_ID_0x0CFF7902)
  {
    COWA::CanMsg::CanMsg_0x0CFF7902 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF7902)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF7902(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF7A02 || topic == TOPIC_CAN_ID_0x0CFF7A02)
  {
    COWA::CanMsg::CanMsg_0x0CFF7A02 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF7A02)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF7A02(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF7B02 || topic == TOPIC_CAN_ID_0x0CFF7B02)
  {
    COWA::CanMsg::CanMsg_0x0CFF7B02 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF7B02)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF7B02(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF7C02 || topic == TOPIC_CAN_ID_0x0CFF7C02)
  {
    COWA::CanMsg::CanMsg_0x0CFF7C02 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF7C02)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF7C02(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x511 || topic == TOPIC_CAN_ID_0x511)
  {
    COWA::CanMsg::CanMsg_0x511 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x511)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x511(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x512 || topic == TOPIC_CAN_ID_0x512)
  {
    COWA::CanMsg::CanMsg_0x512 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x512)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x512(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF15EF || topic == TOPIC_CAN_ID_0x0CFF15EF)
  {
    COWA::CanMsg::CanMsg_0x0CFF15EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF15EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF15EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x0CFF16EF || topic == TOPIC_CAN_ID_0x0CFF16EF)
  {
    COWA::CanMsg::CanMsg_0x0CFF16EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x0CFF16EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x0CFF16EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x62 || topic == TOPIC_CAN_ID_0x62)
  {
    COWA::CanMsg::CanMsg_0x62 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x62)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x62(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x60 || topic == TOPIC_CAN_ID_0x60)
  {
    COWA::CanMsg::CanMsg_0x60 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x60)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x60(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x71 || topic == TOPIC_CAN_ID_0x71)
  {
    COWA::CanMsg::CanMsg_0x71 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x71)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x71(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x78 || topic == TOPIC_CAN_ID_0x78)
  {
    COWA::CanMsg::CanMsg_0x78 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x78)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x78(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x79 || topic == TOPIC_CAN_ID_0x79)
  {
    COWA::CanMsg::CanMsg_0x79 canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x79)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x79(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x18F433EF || topic == TOPIC_CAN_ID_0x18F433EF)
  {
    COWA::CanMsg::CanMsg_0x18F433EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x18F433EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x18F433EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x18F411EF || topic == TOPIC_CAN_ID_0x18F411EF)
  {
    COWA::CanMsg::CanMsg_0x18F411EF canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x18F411EF)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x18F411EF(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x5F || topic == TOPIC_CAN_ID_0x5F)
  {
    COWA::CanMsg::CanMsg_0x5F canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x5F)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x5F(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }
  else if (canId == CAN_ID_0x5C || topic == TOPIC_CAN_ID_0x5C)
  {
    COWA::CanMsg::CanMsg_0x5C canMsg;
    if (canMsg.ParseFromString(data))
    {
      std::string msg_str = "";
      // msg_str.append("canId:0x").append(std::to_string(canId))
      //      .append(", topic:").append(TOPIC_CAN_ID_0x5C)
      //      .append(", data:").append(canMsg.DebugString());
      // LOGGER->Cowa_Info(msg_str.c_str());
      parseCanMsg_0x5C(canMsg);
    }
    else
    {
      LOGGER->Cowa_Warn("parse error");
      isSave = false;
    }
  }

  if (isSave)
  {
    std::string saveTopic = topic;
    if (canId != 0)
    {
      saveTopic = Util::Format("CanMsg_0x%X", canId);
    }

    //持久化消息
    LevelDBManager::instance().setConfig(saveTopic, data);
  }
}

// TODO 测试播放zmq发过来的h264文件
// void CCanServer::proceFrame(const std::string &data)
// {
//     // qDebug() << "******写入文件×××××××××";
//     svbox::ImageFrame msg;
//     if(!msg.ParseFromString(data)) {
//       qDebug() << "********数据解析失败！！！！！！";
//       return;
//     }
//     uint64_t len = msg.data().size();
//     // qDebug() << "****文件大小"<< len << ", size = " << msg.data().size();
//     if(len > 0 && (mFile != NULL)) {
//       fwrite(msg.data().data(), 1, len, mFile);
//       fflush(mFile);
//     }
// }

// void CCanServer::proceFrame2(const std::string &data)
// {
//     svbox::ImageFrame msg;
//     if(msg.ParseFromString(data)) {
//       std::string timeNow = getSystemTimeNow();
//       uint64_t timeNow_l = getSystemTime();
//       uint64_t datalen = msg.data().size();

//       auto head = (FrameHeader*)msg.header().data();

//       if (++mSeqNum != head->sequence && mSeqNum != 1) {
//           qDebug() << "sequence not continuous, mSeqNum:" << (mSeqNum - 1) << ", sequence:" << head->sequence
//                 << ", dletaSeq:" << (head->sequence - mSeqNum + 1);
//       }
//       mSeqNum = head->sequence;

//       qDebug() << "header info (sequence=" << head->sequence << ", width=" << head->width
//             << ", height=" << head->height << ", timestamp=" << head->timestamp
//             << ", exposure=" << head->exposure << ", timeNow=" << timeNow_l << ").";
//         if ((msg.data().size() > 0) && (mFile != NULL)) {
//           fwrite((char*)&timeNow_l, 1, 8, mFile);
//           fwrite((char*)&head->timestamp, 1, 8, mFile);
//           fwrite((char*)&datalen, 1, 8, mFile);
//           fwrite(msg.data().data(), 1, msg.data().size(), mFile);
//           fflush(mFile);
//       }

//       uint64_t timeNow_end = getSystemTime();
//       ++mIndex;
//       qDebug() << "trans consumer:" << (timeNow_l - head->timestamp * (1e-6)) << ", mIndex:" << mIndex
//             << ", writeFileTime:" << (timeNow_end - timeNow_l);
//     }
// }

// std::string CCanServer::getSystemTimeNow() {
//   //首先创建一个time_t 类型的变量nowtime
//   time_t nowtime;
//   //然后创建一个新时间结构体指针 p
// 	struct tm* p;
//   //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
// 	time(&nowtime);
//   //由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。
// 	p = localtime(&nowtime);
//   std::string time_res;
// 	time_res = std::to_string(p->tm_hour) + ":" + std::to_string(p->tm_min) + ":" + std::to_string(p->tm_sec);
// 	//控制格式输出
// 	return time_res;
// }

// uint64_t CCanServer::getSystemTime() {
//   std::time_t t = std::time(0);  // t is an integer type
//   return t;
// }