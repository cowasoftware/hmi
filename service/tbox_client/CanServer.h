#ifndef CANSERVER_H
#define CANSERVER_H

#include <thread>
#include <condition_variable>
#include <iostream>
#include <signal.h>
#include <string>
#include <map>
#include <QThread>
#include <memory>
#include <unistd.h>
#include <atomic>

#include "CanIdDef.hpp"
#include "CanMsg.pb.h"
#include "CanService.pb.h"
#include "CanServiceComm.hpp"
#include "ZmqIF.hpp"
#include "Network.pb.h"

#include "Data.h"
#include "log.h"

class CCleanData;
class CDashBoardData;

using namespace COWA;
using namespace COWA::CanService;
using namespace COWA::CanMsg;
using namespace Cowa;

class CCanServer : public QThread
{
    Q_OBJECT
public:
    CCanServer();
    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();
    void init();
    void initH264();
    void loadLocalData();
    int threadFunc();
    void destroy();
    void run();
    void quitFlag(bool flag);
    void processCmdData(const std::shared_ptr<IData>& pdata);
    void setCleanCmdData(const std::shared_ptr<CCleanData>& pdata);

    std::shared_ptr<IData> getSubData();
    void pushSubData(const std::shared_ptr<IData>& pdata);
    void pushCmdData(const std::shared_ptr<IData>& pdata);
    std::shared_ptr<IData> getCmdData();
    void pushGetCanData(int dataType);
    void processGetCanData(int dataType);
    void getUpdateData(int dataType);
    void getNetWorkData();

    void parseCanMsg_0x5D(COWA::CanMsg::CanMsg_0x5D canMsg);
    void parseCanMsg_0x61(COWA::CanMsg::CanMsg_0x61 canMsg);
    void parseCanMsg_0x63(COWA::CanMsg::CanMsg_0x63 canMsg);
    void parseCanMsg_0x6E(COWA::CanMsg::CanMsg_0x6E canMsg);
    void parseCanMsg_0x6F(COWA::CanMsg::CanMsg_0x6F canMsg);
    void parseCanMsg_0x70(COWA::CanMsg::CanMsg_0x70 canMsg);
    void parseCanMsg_0x08FF32F0(COWA::CanMsg::CanMsg_0x08FF32F0 canMsg);
    void parseCanMsg_0x18F412EF(COWA::CanMsg::CanMsg_0x18F412EF canMsg);
    void parseCanMsg_0x18FF12F7(COWA::CanMsg::CanMsg_0x18FF12F7 canMsg);
    void parseCanMsg_0x0CFF7902(COWA::CanMsg::CanMsg_0x0CFF7902 canMsg);
    void parseCanMsg_0x0CFF7A02(COWA::CanMsg::CanMsg_0x0CFF7A02 canMsg);
    void parseCanMsg_0x0CFF7B02(COWA::CanMsg::CanMsg_0x0CFF7B02 canMsg);
    void parseCanMsg_0x0CFF7C02(COWA::CanMsg::CanMsg_0x0CFF7C02 canMsg);
    void parseCanMsg_0x511(COWA::CanMsg::CanMsg_0x511 canMsg);
    void parseCanMsg_0x512(COWA::CanMsg::CanMsg_0x512 canMsg);
    void parseCanMsg_0x0CFF15EF(COWA::CanMsg::CanMsg_0x0CFF15EF canMsg);
    void parseCanMsg_0x0CFF16EF(COWA::CanMsg::CanMsg_0x0CFF16EF canMsg);
    void parseCanMsg_0x62(COWA::CanMsg::CanMsg_0x62 canMsg);
    void parseCanMsg_0x60(COWA::CanMsg::CanMsg_0x60 canMsg);
    void parseCanMsg_0x18F413EF(COWA::CanMsg::CanMsg_0x18F413EF canMsg);
    void parseCanMsg_0x71(COWA::CanMsg::CanMsg_0x71 canMsg);
    void parseCanMsg_0x78(COWA::CanMsg::CanMsg_0x78 canMsg);
    void parseCanMsg_0x79(COWA::CanMsg::CanMsg_0x79 canMsg);
    void parseCanMsg_0x18F433EF(COWA::CanMsg::CanMsg_0x18F433EF canMsg);
    void parseCanMsg_0x18F411EF(COWA::CanMsg::CanMsg_0x18F411EF canMsg);
    void parseCanMsg_0x5F(COWA::CanMsg::CanMsg_0x5F canMsg);
    void parseCanMsg_0x5C(COWA::CanMsg::CanMsg_0x5C canMsg);

    void parseNetWorkMsg(const std::string& networkData);

    // 处理流媒体信息
    void parseMediaMsg(const std::string& mediaData);
    
    //订阅回调函数
    void zmqSubCb(const std::string& topic, const std::string& data);

    // 订阅h264数据回调函数
    void zmqH264SubCb(const std::string& topic, const std::string& data);

    //消息内容
    void topicMsg(uint32_t canId, const std::string& topic, const std::string& data, bool isSave);

    bool zmqReqAllData();
    

    // TODO 保存zmq发过来的h264文件
    // void proceFrame(const std::string &data);
    // void proceFrame2(const std::string &data);
    // std::string getSystemTimeNow();
    // uint64_t getSystemTime();

Q_SIGNALS:
    void dealSubDataSignal(int data);
    void updateCanMsg_0x6FToUIBarHandle(quint32 isCharge);
    void updateCanMsg_0x18F413EFToUIBarHandle(quint32 voltage, quint32 electricity, quint32 soc);
    void updateModermToUIBarHandle(QString csq, QString cops);
    void notifyTimer();
    void sendMediaData(const std::string &data);

public Q_SLOTS:
    void cmdReqSlot(int cmd);

private:
    ZmqSubIF                                m_ZmqSubIF;
    ZmqReqIF                                m_ZmqReqIF;
    ZmqSubIF                                m_ZmqSub_H264;
    ZmqReqIF                                m_ZmqReq_H264;
    std::atomic<bool>                       m_aCoonected{false};
    std::atomic<bool>                       m_isStoped{false};
    std::atomic<bool>                       m_isStartTimer{false};
    std::mutex                              m_Mutex;
    std::shared_ptr<std::thread>            m_spThread;  //数据处理线程

    std::mutex                              m_listMutex;
    std::condition_variable                 m_ConSub;
    std::list<std::shared_ptr<IData>>       m_lData;
    std::mutex                              m_cmdMutex;
    std::list<std::shared_ptr<IData>>       m_cmdData;
    std::condition_variable                 m_ConCmd;
    //std::list<std::shared_ptr<IData>>       m_getCanData;
    std::list<int>                          m_getCanData;
    bool                                    m_nReqFlag;                    
    DataType                                m_cType;
};

#endif //CANSERVER_H