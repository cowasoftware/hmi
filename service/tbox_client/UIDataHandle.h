#ifndef UIDATAHANDLE_H
#define UIDATAHANDLE_H

#include <QObject>
#include <QVariant>
#include <memory>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include "Singleton.h"
#include "StatusData.h"
#include "DashBoardData.h"
#include "LightScreenData.h"
#include "CleanData.h"
#include "DiagnosisIOData.h"
#include "MCU1Data.h"
#include "MsgType.h"
#include "CanServer.h"
#include "DiagnosisStatusCode.h"
#include "DiagnosisBatteryData.h"
#include "DiagnosisMainDriData.h"
#include "DiagnosisBrakeData.h"
#include "DiagnosisEPSData.h"
#include "Diagnosis12VDCData.h"
#include "Diagnosis48VDCData.h"
#include "DiagnosisFan902Data.h"
#include "DiagnosisFanA02Data.h"
#include "DiagnosisFanB02Data.h"
#include "DiagnosisFanC02Data.h"
#include "DiagnosisSweepDiskData.h"
#include "DiagnosisHigPreDump15Data.h"
#include "DiagnosisHigPreDump16Data.h"
#include "DiagnosisCommuData.h"
#include "DiagnosisBrake60Data.h"
#include "DiagnosisIO71Data.h"
#include "DiagnosisIO78Data.h"
#include "DiagnosisIO79Data.h"
#include "DiagnosisBattery13EFData.h"
#include "DiagnosisBattery33EFData.h"
#include "DiagnosisBattery11EFData.h"
#include "DiagnosisBrake5FData.h"
#include "DiagnosisEPS5CData.h"
#include "Timer.h"
#include "log.h"

using namespace Cowa;

//业务类
class CUIDataHandle : public QObject
{
    Q_OBJECT
public:
    explicit CUIDataHandle(QObject* parent = nullptr);
    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();
    void init();
    int threadFunc();
    void destroy();
    ~CUIDataHandle();
    Q_INVOKABLE void sendSignal();             // qml端访问 信号测试接口
    Q_INVOKABLE void getCanData(int dataType); //更新仪表盘数据

    //设置仪表盘数据
    void setDashBoardData(CDashBoardData &data);
    //设置灯光数据
    void setLightScreenData(CLightScreenData &data);
    // model
    // DataModel& getModel();
    void pushSubData(const std::shared_ptr<IData> &data);
    void processSubData(const std::shared_ptr<IData> &data);

    std::shared_ptr<CCanServer> canServerPtr();

Q_SIGNALS:

    //仪表盘信号
    void signalDashBoard(int nSpd, QString strCruSpd, int nTravelDistance);
    //灯光信号
    void signalLightScreen(bool bDoubleFlash, bool bLightReady, bool bLightParking,
                           bool bLeftSteering, bool bRightSteering, bool bWorkLight,
                           bool bPositionLight, bool bHeadLights, bool bBatteryFailure,
                           bool bHighVoltageCutOff, bool bOverheatAlarm, bool bVehicleFailure,
                           bool bCriticalBatteryFailure, QString strVehicleChargingTips, bool bVehicleready
                           /*int     nCruisingRangeDisplay*/);
    //左右转向灯
    void signalLeftRightLight(bool bLeftSteering, bool bRightSteering);
    //里程表信号
    void signalTravelDistance(int distance, int todayMile);
    // cmd signal
    void signalCmdProcess(int cmd);
    // IO诊断信号
    void signalDiagnosisIO(int nTurnLeft, int nTurnRight, int nWorkFlag, int nTrunOnFlag,
                           int nLowBeam, int nSmallLight, int nAutoDrive, int nEmergencyFlash, int nStop);
    
    void signalDiagnosisIO71(int nBrakeOil_line, int nBox_up, int nBox_dowm, int nBox_Arrive, int nChengGan_Arrive,
                             int nEban_switch, int nBoxDoor_switch, int nLeftBrush_arrive, int nRightBrush_arrive, int nLeftBrush_open,
                             int nLeftBrush_close, int nRightBrush_open, int nRightBrush_close, int ndustbin_returnSwitch, int nWaterLine_show);
    
    void signalDiagnosisIO78(int nTurnLeftLight, int nTurnRightLight, int nLowBeam, int nWorkLight_relay, int nsmall_light,
                             int nreversing_light, int nbrake_light, int nReversing_buzzer);
   
    void signalDiagnosisIO79(int nBoxDoor_open, int nBoxDoor_close, int nLeftBrush_up, int nLeftBrush_down, int nLeftBrush_open,
                             int nLeftBrush_close, int nRightBrush_up, int nRightBrush_down, int nRightBrush_open, int nRightBrush_close, int nEban_switch_open,
                             int nEban_switch_close, int nXiZwitch_up, int nXiZwitch_down, int nDustbin_up, int nDustbin_down,int nLVWaterRoad_relay,
                             int nSewagecyclevalve, int nDelayCutDown);
    // void signalMCU1Data(int speed, int gear);
    void signalDoubleFlash(int doubleFlash);
    //诊断主驱信息
    void signalDiagnosisMainDri(int nMotSpeed, int nMotTorque, int nRotaryWarning, int nIntePass,
                                int nGearSts, int nBackBrake, int nAccPdlSts, int nBusbardischarg,
                                int nBrakeActive, int nMotSpeedValid, int nOverCurrentFault,
                                int nPowerLimtWarning, int nMCUTempWarning, int nMotTempWarning, int nBusbarOverVoltFault, int nBusbarLessVoltFault,
                                int nSpeedControlValid, int nGeneralFaultWarning, int nGearWarning, int nHoldReq, int nApdlPercent);
    //诊断电池信息
    void signalDiagnosisBattery(int nBattOverTempFault, int nInsulationFault,int nCellLessVoltWarning, int nCellOverVoltWarning, int nBattLessElectWarning, int nPositiveRelayAdhesion,
                                int nPTCRelayAdhesion, int nSOHWarning, int nPositionRelaySts, int nPTCRelaySts, int nBattVoltImbalance, int nDischgOverCurrent,
                                int nChgOverCurrent, int nItselfCANerror, int nBattGeneralLessVolt, int nBattGeneralOverVolt, int nBMSHardwareFault,
                                int nCANerror, int nCCsignConnetSts, int nPrechargeSts, int nBMSsts, int nBackChgEnb, int nWarmModel, int nBalanceSts,
                                int nSOCLow, int nCurrentSensorFault, int nTempSensorFault, int nNegativeRelayAdhesion, int nPrechgRelaySts, int nNegativeRelaySts,
                                int nDCchgPositiveRelaySts, int nDCchgGunOverTempFault, int nCellCollectLineCutFault, int nPrechgRelayAdhesion, int nDCchgPositiveRelayAdhesion,
                                int nWakeUpType, int nBattTempImbalanceFault, int nBattLessTempFault, int nWarmSts);
   
    void signalDiagnosisBattery13EF(int nGeneralVolt, int nGeneralCurrent, int nSOC, int nBattSerialData, int nCellVoltSensorFault,
                                    int nGeneralVoltSensorFault, int n12VLessVolt, int n12VOverVolt);
    void signalDiagnosisBattery33EF(int nBattMaxTemp, int nBattMaxTempCode, int nBattMinTemp, int nBattMinTempCode,
                                    int nDCchgGunBaseTemp0, int nDCchgGunBaseTemp1, int nAverageTemp);
    void signalDiagnosisBattery11EF(int nSystemFaultLevel, int nHVlock, int nPowerDownReq, int nBMSMaxDischgPower,
                                    int nBMSMaxChgPower, int nDCchgVoltDemand, int nDCchgCurrentDemand, int nSystemStsCode);
    //诊断制动信息
    void signalDiagnosisBrake(int nEHB_WorkSts, int nBrakePress, int npedalPercent,
                              int nPistonDisplacement, int nTargetPress, int nParkReq, int nBrakeSts, int nfaultLevel);
    
    void signalDiagnosisBrake5F(int nfaultCode1, int nfaultCode2, int nfaultCode3);

    void signalDiagnosisBrake60(int nBrakeSts, int nParklight_sts, int nFaultlight_sts, int nSwitch_sts,
                                int nSystem_sts, int nFault_message);
    
    //诊断EPS信息
    void signalDiagnosisEPS(int nWorkModel, int nTargeTangle, int nWheelPalstance, int nAutoCMD_model, int nCurrentangle);
    
    void signalDiagnosisEPS5C( int nOut_torque, int nTarget_torque, int nFaultCode_92);

    //诊断12V DC信息
    void signalDiagnosis12VDC(int nOutEnable, int nState, int nINVoltage, int nINCurrent, int nDCDCTemperature, int nOverTemperature,
                              int nOut_voltage, int nOut_current, int nIn_over_current, int nOut_over_current, int nIn_over_voltage, int nIn_less_voltage,
                              int nOut_over_voltage, int nOut_less_voltage);
    //诊断48V DC信息
    void signalDiagnosis48VDC(int nOUTVolt, int nOUTCurrent, int nDCSts,
                              int nOUTCutDownSts, int nFaultLevel, int nRadiatorTemp, int nINCutDownSts);
    //诊断风机信息
    void signalDiagnosisFan902(int nFaultLevl, int nModSts, int nEnSts,
                               int nPrechargeAllow, int nDirSts, int nActTorValid,
                               int nActSpdValid, int nActTor, int nActSpd);

    void signalDiagnosisFanA02(int nDCVolt, int nDCCur, int nACCur);

    void signalDiagnosisFanB02(int nMotorMinAvaTor, int nMotorMaxAvaTor, int nMotorIGBTTemp,
                               int nMTemp, int nCTemp);

    void signalDiagnosisFanC02(int nMOvSpdSts, int nMBlockSts, int nMOvTempSts, int nMOvCurSts, int nMShrSts,
                               int nMShrGrdSts, int nCOvTempSts, int nCAuxBatSts, int nPreChaSts, int nIGBTModSts,
                               int nIGBTOvTempSts, int nIGBTOvCurSts, int nCOvVoltSts, int nCLowVoltSts, int nIGBTTempSenSts,
                               int nCANFault, int nMTempSenSts, int nCTempSenSts, int nCVoltSenSts, int nCCurSenSts,
                               int nACCurSenSts, int nCTranFaultSts, int nMCutOffSts);
    //诊断扫盘信息
    void signalDiagnosisSweepDisk(int nMainVoltage, int nCurrentMotcurrent, int nEnableSts,
                                  int nWheelSts, int nMotTemperature, int nMotCurrentSpeed, int nOverCurrent, int nOverVoltage, int nOverTemperature,
                                  int nLochedRotor, int nHallSignalError, int nMotFualtItself, int sweepType);
    //诊断高压水泵信息
    void signalDiagnosisHigPreDump15(int nMOTspeed, int nMOTBusbarVolt, int nMotTemp,
                                     int nIGBTTemp, int nMOT_current_AC, int nMOTFaultCodeSign);
    void signalDiagnosisHigPreDump16(int nMCUintSts, int nMCUModelSts);
    //诊断通信信息
    void signalDiagnosisCommu(int nBMS_CANerror, int nMCU_CANerror, int nEHB_CANerror, int nEPB_CANerror,
                              int nEPS_CANerror, int nDC48V_CANerror, int nAC_CANerror, int nADU_CANerror, int nICU_CANerror, int nDC12V_CANerror,
                              int nGPS_CANerror, int nFJI_CANerror, int nWP_CANerror, int nSPL_CANerror, int nSPR_CANerror);
    
    void signalDiagnosisBrakePark(int nBrkeSts);

    //停止定时器
    void signalStopTimer();
    //水位信息
    void signalWaterLine(int waterLine);
    //电控程序版本
    void signalSoftWareVersion(int version);
    // 档位信息
    void signalGearData(int nGearSts);

public Q_SLOTS:
    //下发巡航指令
    void slotSetCruiseControlCmd(int mode);
    //下发上装功能指令
    void slotSetTopCleanCmd(int mode, int onOff);
    //下发诊断指令
    void slotDiagnosisCmd(int mode, int onOff);
    void handleSubData(int rslt);

    //诊断数据更新槽函数
    void slotDiagnosisUpdateData(int dataType);
    //加载本地数据
    void loadLocalData();
    //启动定时器
    void startTimer();

private:
    CStatusData                         m_cStatus;                     //状态栏
    CDashBoardData                      m_cDashBoard;               //仪表盘
    CLightScreenData                    m_cLightScreen;           //灯光
    CCleanData                          m_cClean;                       //上装功能
    std::list<std::shared_ptr<IData>>   m_lData; //存放不同类型的数据类
    std::mutex                          m_Mutex;
    std::condition_variable             m_conVal;
    bool                                m_bRuning;
    bool                                m_bStartTimer;

    std::shared_ptr<std::thread>        m_spThread;
    std::shared_ptr<CCanServer>         m_spCanThread;
    std::shared_ptr<CTimer>             m_spTimer;
    // CCanServer*                     m_spCanThread;
    CMCU1Data m_cMCU1Data;
    CDigStatusCode                      m_cStatusCode; //保存一份诊断数据
    CDiagnosisIOData                    m_cDiagnosisIO;
    CDiagnosisBatteryData               m_cDiagnosisBattry;
    CDiagnosisMainDriData               m_cDiagnosisMainDri;          
    CDiagnosisBrakeData                 m_cDiagnosisBrake;
    CDiagnosisEPSData                   m_cDiagnosisEPS;
    CDiagnosis12VDCData                 m_cDiagnosis12V;
    CDiagnosis48VDCData                 m_cDiagnosis48V;
    CDiagnosisFan902Data                m_cDiagnosisFan902;
    CDiagnosisFanA02Data                m_cDiagnosisFanA02;
    CDiagnosisFanB02Data                m_cDiagnosisFanB02;
    CDiagnosisFanC02Data                m_cDiagnosisFanC02;
    CDiagnosisSweepDiskData             m_cDiagnosisSweepDiskLeft;
    CDiagnosisSweepDiskData             m_cDiagnosisSweepDiskRight;
    CDiagnosisHigPreDump15Data          m_cDiagnosisHigPreDump15;
    CDiagnosisHigPreDump16Data          m_cDiagnosisHigPreDump16;
    CDiagnosisCommuData                 m_cDiagnosisCommu;
    CDiagnosisBrake60Data               m_cDiagnosisBrake60;
    CDiagnosisIO71Data                  m_cDiagnosisIO71Data;
    CDiagnosisIO78Data                  m_cDiagnosisIO78Data;
    CDiagnosisIO79Data                  m_cDiagnosisIO79Data;
    CDiagnosisBattery13EFData           m_cDiagnosisBattery13EFData;
    CDiagnosisBattery33EFData           m_cDiagnosisBattery33EFData;
    CDiagnosisBattery11EFData           m_cDiagnosisBattery11EFData;
    CDiagnosisBrake5FData               m_cDiagnosisBrake5FData;
    CDiagnosisEPS5CData                 m_cDiagnosisEPS5CData;
public:
    CMsgType m_eMsgType;                //消息类型
    DataType m_cDataType;               //数据类型
};
typedef Singleton<CUIDataHandle> SingletonCUIDataHandle;

#endif // UIDATAHANDLE_H
