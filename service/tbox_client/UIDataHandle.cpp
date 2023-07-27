#include <QDebug>
#include "UIDataHandle.h"
#include "ConfigManager.h"

#define LOGGER GetLogMgr().getLogger()

CUIDataHandle::CUIDataHandle(QObject *parent) 
    : QObject(parent)
    , m_bRuning(false)
    , m_bStartTimer(false)
{
    // std::cout << "ui handle construct-------------------" << std::endl;
    // printf(" UI handle ThreadID: %d\n", std::this_thread::get_id());
}

CUIDataHandle::~CUIDataHandle()
{
    // m_spCanThread->quitFlag(true);
    // m_spCanThread->exit(0);
    // m_spCanThread->quit();
    // m_spCanThread->wait();
    LOGGER->Cowa_Info("ui handle destroy------------");
}

inline CLogMgr& CUIDataHandle::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT);
  return my_logger;
}

void CUIDataHandle::init()
{
    LOGGER->Cowa_Info("CUIDataHandle::");
    m_spCanThread = std::make_shared<CCanServer>();
    // m_spCanThread = new CCanServer();
    QObject::connect(&(*m_spCanThread), SIGNAL(dealSubDataSignal(int)), this, SLOT(handleSubData(int)));
    //QObject::connect(&(*m_spCanThread), SIGNAL(notifyTimer()), this, SLOT(startTimer()));
    QObject::connect(this, SIGNAL(signalCmdProcess(int)), &(*m_spCanThread), SLOT(cmdReqSlot(int)));

    m_spCanThread->init();
    m_spCanThread->initH264();
    m_spCanThread->start();

    //m_spTimer = std::make_shared<CTimer>();
    //QObject::connect(&(*m_spTimer), SIGNAL(dealSubDataSignal(int)), this, SLOT(handleSubData(int)));
    //QObject::connect(this, SIGNAL(signalStopTimer()), &(*m_spTimer), SLOT(TimerExit()));
    //m_spTimer->init();
    // m_bRuning = true;
    // m_spThread.reset(new std::thread(std::bind(&CUIDataHandle::threadFunc, this)));
}

void CUIDataHandle::loadLocalData()
{
    m_spCanThread->loadLocalData();
}

void CUIDataHandle::startTimer()
{
    // if (m_spTimer != nullptr)
    // {
    //     if (!m_bStartTimer)
    //     {
    //         std::cout << "******************* start timer *****************" << std::endl;
    //         m_spTimer->startTimer();
    //         m_bStartTimer = true;
    //     }
        
    // }else
    // {
    //     std::cout << "m_spTimer is nullptr..., please check.." << std::endl;
    // }
    
}

void CUIDataHandle::destroy()
{
    m_spCanThread->quitFlag(true);
    m_spCanThread->quit();
    LOGGER->Cowa_Info("UI Handle destroy...........");
    // m_spCanThread->wait();
}

int CUIDataHandle::threadFunc()
{
    return 0;
}

void CUIDataHandle::processSubData(const std::shared_ptr<IData> &data)
{
}

std::shared_ptr<CCanServer> CUIDataHandle::canServerPtr()
{
    return m_spCanThread;
}

void CUIDataHandle::sendSignal()
{
    LOGGER->Cowa_Info("CUIDataHandle::", __FUNCTION__, "test signal");
    // Q_EMIT signal1();
    // // Q_EMIT signal2(m_strValue, m_intValue);
    // Q_EMIT signalDashBoard(50, 3000, "D", "5.1", 2);                        ////测试仪表盘信号
    // Q_EMIT signalLightScreen(1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, "str", 1); ////测试灯光信号
    // Q_EMIT signalLeftRightLight(1, 0);                                      //转向灯
    // // Q_EMIT signalTravelDistance(12345); //行驶里程
    // // Q_EMIT signalMCU1Data(1000, 2);
    // Q_EMIT signalDiagnosisIO(0, 0);
    // Q_EMIT signalDiagnosisBattery(3, 1, 2, 0, 0, 0, 0, 4);
    // Q_EMIT signalDiagnosisMainDri(1000, 40, 1, 0, 2, 0, 1, 0, 1, 0);
    // Q_EMIT signalDiagnosisBrake(10, 20, 30, 40, 50);
    // Q_EMIT signalDiagnosisEPS(10, 45, 360);
    // Q_EMIT signalDiagnosis12VDC(1, 1, 220, 380, 45, 1);
    // Q_EMIT signalDiagnosis48VDC(100, 200, 1, 1, 1, 555);
    // Q_EMIT signalDiagnosisFan902(1, 1, 1, 1, 1, 1, 1, 100, 200);
    // Q_EMIT signalDiagnosisCommu(0, 1);
    // Q_EMIT signalDiagnosisBrakePark(1);
}

void CUIDataHandle::getCanData(int dataType)
{
    // Q_EMIT signalDashBoard(88, 5000, "D", "8.8", 2);
    // auto data = std::make_shared<CDashBoardData>();
    // m_spCanThread->pushGetCanData(std::static_pointer_cast<IData>(data));
    m_spCanThread->pushGetCanData(dataType);
    LOGGER->Cowa_Info(("getCanData:: dataType = " + std::to_string(dataType)).c_str());
}

void CUIDataHandle::setDashBoardData(CDashBoardData &data)
{
    LOGGER->Cowa_Info("setDashBoardData:: set dash board data");
}

void CUIDataHandle::slotSetCruiseControlCmd(int mode)
{
    // m_cDashBoard.m_nControlMode = mode;
    LOGGER->Cowa_Info(("set Cruise control cmd data: " + std::to_string(mode)).c_str());
}

void CUIDataHandle::setLightScreenData(CLightScreenData &data)
{
    LOGGER->Cowa_Info("set light screen data");
}

void CUIDataHandle::slotSetTopCleanCmd(int mode, int onOff)
{
    switch (mode)
    {
    case m_eMsgType.LEFT_BRUSH_DOWN:
        m_cClean.m_nLeftbrushDown = onOff;
        break;
    case m_eMsgType.LEFT_BRUSH_UP:
        m_cClean.m_nLeftbrushUp = onOff;
        break;
    case m_eMsgType.LEFT_BRUSH_EXTEND:
        m_cClean.m_nLeftbrushExtend = onOff;
        break;
    case m_eMsgType.LEFT_BRUSH_NARROW:
        m_cClean.m_nLeftbrushNarrow = onOff;
        break;
    case m_eMsgType.RIGHT_BRUSH_EXTEND:
        m_cClean.m_nRightbrushExtend = onOff;
        break;
    case m_eMsgType.RIGHT_BRUSH_NARROW:
        m_cClean.m_nRightbrushNarrow = onOff;
        break;
    case m_eMsgType.RIGHT_BRUSH_DOWN:
        m_cClean.m_nRightbrushDown = onOff;
        break;
    case m_eMsgType.RIGHT_BRUSH_UP:
        m_cClean.m_nRightbrushUp = onOff;
        break;
    case m_eMsgType.TANK_OPEN:
        m_cClean.m_nTankOpen = onOff;
        break;
    case m_eMsgType.TANK_CLOSE:
        m_cClean.m_nTankClose = onOff;
        break;
    case m_eMsgType.NOZZLE_DOWN:
        m_cClean.m_nNozzleDown = onOff;
        break;
    case m_eMsgType.NOZZLE_UP:
        m_cClean.m_nNozzleUp = onOff;
        break;
    case m_eMsgType.EXTEND_RELAY:
        m_cClean.m_nExtendRelay = onOff;
        break;
    case m_eMsgType.WITHDRAW_RELAY:
        m_cClean.m_nWithdrawRelay = onOff;
        break;
    case m_eMsgType.SEWAGE_LOOP:
        m_cClean.m_nSewageLoop = onOff;
        break;
    case m_eMsgType.FAN_CALIBRATION:
        m_cClean.m_nFanCalibration = onOff;
        break;
    case m_eMsgType.FAN_WORK_DEBUG:
        m_cClean.m_nFanWorkDebug = onOff;
        break;
    case m_eMsgType.FAN_SPEEDACC:
        m_cClean.m_nFanSpeedAcc = onOff;
        break;
    case m_eMsgType.FAN_SPEEDMIN:
        m_cClean.m_nFanSpeedMin = onOff;
        break;
    case m_eMsgType.LEFT_BRUSH_WORK_DEBUG:
        m_cClean.m_nLeftBrushWorkDebug = onOff;
        break;
    case m_eMsgType.RIGHT_BRUSH_WORK_DEBUG:
        m_cClean.m_nRightBrushWorkDebug = onOff;
        break;
    case m_eMsgType.BRUSH_SPEED_ACC:
        m_cClean.m_nBrushSpeedAcc = onOff;
        break;
    case m_eMsgType.BRUSH_SPEED_MIN:
        m_cClean.m_nBrushSpeedMin = onOff;
        break;
    case m_eMsgType.SPRAY_PUMP_DEBUG:
        m_cClean.m_nSprayPumpDebug = onOff;
        break;
    case m_eMsgType.EPS_CALIBRATION:
        m_cClean.m_nEPSCalibration = onOff;
        break;
    case m_eMsgType.FAN_CLEAN_MODE:
        m_cClean.m_nFanMode = CLEAN_MODE;
        break;
    case m_eMsgType.FAN_STANDARD_MODE:
        m_cClean.m_nFanMode = STANDARD_MODE;
        break;
    case m_eMsgType.FAN_STRONG_MODE:
        m_cClean.m_nFanMode = STRONG_MODE;
        break;
    case m_eMsgType.HIGH_PRECLEAN_STOP_MODE:
        m_cClean.m_nHighPreClean = HPCSTOP_MODE;
        break;
    case m_eMsgType.HIGH_PRECLEAN_START_MODE:
        m_cClean.m_nHighPreClean = HPCSTART_MODE;
        break;
    case m_eMsgType.DUST_NORMAL_MODE:
        m_cClean.m_nDustSupMode = NORMAL_MODE;
        break;
    case m_eMsgType.DUST_SUPRE_MODE:
        m_cClean.m_nDustSupMode = DUSTSUPRE_MODE;
        break;
    case m_eMsgType.TANK_TILT:
        m_cClean.m_nTankTilt = onOff;
        break;
    case m_eMsgType.TANK_RESET:
        m_cClean.m_nTankReset = onOff;
        break;
    case m_eMsgType.WORK_LIGHT:
        m_cClean.m_nWorklight = onOff;
        break;
    case m_eMsgType.WORK_START:
        m_cClean.m_nWorkStart = onOff;
        break;
    case m_eMsgType.CURISE_START:
        m_cClean.m_nCuriseStart = onOff;
        break;
    case m_eMsgType.CURISE_ACC:
        m_cClean.m_nCuriseAcc = onOff;
        break;
    case m_eMsgType.CURISE_DEC:
        m_cClean.m_nCuriseDec = onOff;
        break;

    default:
        break;
    }
    // Q_EMIT signalCmdProcess(mode);
    auto data = std::make_shared<CCleanData>(m_cClean);
    m_spCanThread->pushCmdData(std::static_pointer_cast<IData>(data));
    // 会一直输出日志，去掉
    LOGGER->Cowa_Info(("top clean cmd: " + std::to_string(mode) + ", Switch: " + std::to_string(onOff)).c_str());
}

void CUIDataHandle::slotDiagnosisCmd(int mode, int onOff)
{
    LOGGER->Cowa_Info(("diagnosis cmd: " + std::to_string(mode) + ", Switch: " + std::to_string(onOff)).c_str());
}

void CUIDataHandle::pushSubData(const std::shared_ptr<IData> &data)
{
    {
        std::unique_lock<std::mutex> guard(m_Mutex);
        m_lData.push_back(data);
    }
    m_conVal.notify_one();
    LOGGER->Cowa_Info("push data to list");
}

void CUIDataHandle::handleSubData(int dataType)
{
    std::shared_ptr<IData> data = nullptr;
    if (dataType == m_cDataType.LOCAL_CAN_DATA)
    {
        data = m_lData.front();
        m_lData.pop_front();
    }
    else
    {
        data = m_spCanThread->getSubData();
        // if (data == nullptr)//没有数据的时候停止定时器
        // {
        //     if (m_spTimer != nullptr && m_bStartTimer)
        //     {
        //         std::cout << "******* NO sub data to process, stop timer *********" << std::endl;
        //         m_spTimer->stopTimer();
        //         m_bStartTimer = false;
                
        //     }else
        //     {
        //         std::cout << "******* timer m_spTimer is nullptr, check error ****" << std::endl; 
        //     }
        // }
    }

    if (data)
    {
        int type = data->m_nDataType;
        if (type == m_cDataType.DASHBOARD_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDashBoardData>(data);
            std::string theDayFirstMile = SingletonConfigManager::getInstance()->getTodayMile(std::to_string(tmpData->m_nTravelDistance));
            LOGGER->Cowa_Info(("the day first mile is: " + theDayFirstMile).c_str());
            Q_EMIT signalDashBoard(tmpData->m_nSpeed,
                                 QString::number(tmpData->m_fCruiseSpeed, 'f', 1), //保留一位小数
                                 tmpData->m_nCuriseOff);                           //向UI发送信号 仪表盘
            int todayMile = tmpData->m_nTravelDistance - stoi(theDayFirstMile);
            LOGGER->Cowa_Info(("the today mile is: " + std::to_string(todayMile)).c_str());
            Q_EMIT signalTravelDistance(tmpData->m_nTravelDistance, todayMile);
        
        }
        else if (type == m_cDataType.LIGHTSCREEN_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CLightScreenData>(data);
            Q_EMIT signalLightScreen(tmpData->m_bDoubleFlash, //灯光信号通知UI
                                   tmpData->m_bLightReady,
                                   tmpData->m_bLightParking,
                                   tmpData->m_bLeftSteering,
                                   tmpData->m_bRightSteering,
                                   tmpData->m_bWorkLight,
                                   tmpData->m_bPositionLight,
                                   tmpData->m_bHeadLights,
                                   tmpData->m_bBatteryFailure,
                                   tmpData->m_bHighVoltageCutOff,
                                   tmpData->m_bOverheatAlarm,
                                   tmpData->m_bVehicleFailure,
                                   tmpData->m_bCriticalBatteryFailure,
                                   tmpData->m_strVehicleChargingTips,
                                   tmpData->m_bVehicleready);
            Q_EMIT signalLeftRightLight(tmpData->m_bLeftSteering,
                                      tmpData->m_bRightSteering);
            Q_EMIT signalSoftWareVersion(tmpData->m_nSoftwareVersion);
        }
        else if (type == m_cDataType.DIAGNOSIS_IO_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisIOData>(data);
            m_cDiagnosisIO = *tmpData;
            m_cDiagnosisIO.m_bFlush = true;
            Q_EMIT signalDiagnosisIO(tmpData->m_nTurnLeft,
                                   tmpData->m_nTurnRight,
                                   tmpData->m_nWorkFlag,
                                   tmpData->m_nTrunOnFlag,
                                   tmpData->m_nLowBeam,
                                   tmpData->m_nSmallLight,
                                   tmpData->m_nAutoDrive,
                                   tmpData->m_nEmergencyFlash,
                                   tmpData->m_nStop);

            Q_EMIT signalDoubleFlash(tmpData->m_nEmergencyFlash);
        }
        else if (type == m_cDataType.DIAGNOSIS_IO71_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisIO71Data>(data);
            m_cDiagnosisIO71Data = *tmpData;
            m_cDiagnosisIO71Data.m_bFlush = true;
            Q_EMIT signalWaterLine(tmpData->m_nWaterLine_show);
            Q_EMIT signalDiagnosisIO71(tmpData->m_nBrakeOil_line,
                                     tmpData->m_nBox_up,
                                     tmpData->m_nBox_dowm,
                                     tmpData->m_nBox_Arrive,
                                     tmpData->m_nChengGan_Arrive,
                                     tmpData->m_nEban_switch,
                                     tmpData->m_nBoxDoor_switch,
                                     tmpData->m_nLeftBrush_arrive,
                                     tmpData->m_nRightBrush_arrive,
                                     tmpData->m_nLeftBrush_open,
                                     tmpData->m_nLeftBrush_close,
                                     tmpData->m_nRightBrush_open,
                                     tmpData->m_nRightBrush_close,
                                     tmpData->m_ndustbin_returnSwitch,
                                     tmpData->m_nWaterLine_show);
        }
        else if (type == m_cDataType.DIAGNOSIS_IO78_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisIO78Data>(data);
            m_cDiagnosisIO78Data = *tmpData;
            m_cDiagnosisIO78Data.m_bFlush = true;
            Q_EMIT signalDiagnosisIO78(tmpData->m_nTurnLeftLight,
                                     tmpData->m_nTurnRightLight,
                                     tmpData->m_nLowBeam,
                                     tmpData->m_nWorkLight_relay,
                                     tmpData->m_nsmall_light,
                                     tmpData->m_nreversing_light,
                                     tmpData->m_nbrake_light,
                                     tmpData->m_nReversing_buzzer);
        }
        else if (type == m_cDataType.DIAGNOSIS_IO79_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisIO79Data>(data);
            m_cDiagnosisIO79Data = *tmpData;
            m_cDiagnosisIO79Data.m_bFlush = true;
            Q_EMIT signalDiagnosisIO79(tmpData->m_nBoxDoor_open,
                                     tmpData->m_nBoxDoor_close,
                                     tmpData->m_nLeftBrush_up,
                                     tmpData->m_nLeftBrush_down,
                                     tmpData->m_nLeftBrush_open,
                                     tmpData->m_nLeftBrush_close,
                                     tmpData->m_nRightBrush_up,
                                     tmpData->m_nRightBrush_down,
                                     tmpData->m_nRightBrush_open,
                                     tmpData->m_nRightBrush_close,
                                     tmpData->m_nEban_switch_open,
                                     tmpData->m_nEban_switch_close,
                                     tmpData->m_nXiZwitch_up,
                                     tmpData->m_nXiZwitch_down,
                                     tmpData->m_nDustbin_up,
                                     tmpData->m_nDustbin_down,
                                     tmpData->m_nLVWaterRoad_relay,
                                     tmpData->m_nSewagecyclevalve,
                                     tmpData->m_nDelayCutDown);
        }
        else if (type == m_cDataType.DIAGNOSIS_MAINDRI_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisMainDriData>(data);
            m_cDiagnosisMainDri = *tmpData;
            m_cDiagnosisMainDri.m_bFlush = true;
            Q_EMIT signalDiagnosisMainDri(tmpData->m_nMotSpeed,
                                        tmpData->m_nMotTorque,
                                        tmpData->m_nRotaryWarning,
                                        tmpData->m_nIntePass,
                                        tmpData->m_nGearSts,
                                        tmpData->m_nBackBrake,
                                        tmpData->m_nAccPdlSts,
                                        tmpData->m_nBusbardischarg,
                                        tmpData->m_nBrakeActive,
                                        tmpData->m_nMotSpeedValid,
                                        tmpData->m_nOverCurrentFault,
                                        tmpData->m_nPowerLimtWarning,
                                        tmpData->m_nMCUTempWarning,
                                        tmpData->m_nMotTempWarning,
                                        tmpData->m_nBusbarOverVoltFault,
                                        tmpData->m_nBusbarLessVoltFault,
                                        tmpData->m_nSpeedControlValid,
                                        tmpData->m_nGeneralFaultWarning,
                                        tmpData->m_nGearWarning,
                                        tmpData->m_nHoldReq,
                                        tmpData->m_nApdlPercent);
            // 档位信息
            Q_EMIT signalGearData(tmpData->m_nGearSts);
        }
        else if (type == m_cDataType.DIAGNOSIS_BATTERY_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBatteryData>(data);
            m_cDiagnosisBattry = *tmpData;
            m_cDiagnosisBattry.m_bFlush = true;
            Q_EMIT signalDiagnosisBattery(tmpData->m_nBattOverTempFault, tmpData->m_nInsulationFault, tmpData->m_nCellLessVoltWarning, tmpData->m_nCellOverVoltWarning, tmpData->m_nBattLessElectWarning,
                                        tmpData->m_nPositiveRelayAdhesion, tmpData->m_nPTCRelayAdhesion, tmpData->m_nSOHWarning, tmpData->m_nPositionRelaySts, tmpData->m_nPTCRelaySts, tmpData->m_nBattVoltImbalance,
                                        tmpData->m_nDischgOverCurrent, tmpData->m_nChgOverCurrent, tmpData->m_nItselfCANerror, tmpData->m_nBattGeneralLessVolt, tmpData->m_nBattGeneralOverVolt,
                                        tmpData->m_nBMSHardwareFault, tmpData->m_nCANerror, tmpData->m_nCCsignConnetSts, tmpData->m_nPrechargeSts, tmpData->m_nBMSsts, tmpData->m_nBackChgEnb,
                                        tmpData->m_nWarmModel, tmpData->m_nBalanceSts, tmpData->m_nSOCLow, tmpData->m_nCurrentSensorFault, tmpData->m_nTempSensorFault, tmpData->m_nNegativeRelayAdhesion,
                                        tmpData->m_nPrechgRelaySts, tmpData->m_nNegativeRelaySts, tmpData->m_nDCchgPositiveRelaySts, tmpData->m_nDCchgGunOverTempFault, tmpData->m_nCellCollectLineCutFault, tmpData->m_nPrechgRelayAdhesion,
                                        tmpData->m_nDCchgPositiveRelayAdhesion, tmpData->m_nWakeUpType, tmpData->m_nBattTempImbalanceFault, tmpData->m_nBattLessTempFault, tmpData->m_nWarmSts);
        }
        else if (type == m_cDataType.DIAGNOSIS_BATTERY13EF_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBattery13EFData>(data);
            m_cDiagnosisBattery13EFData = *tmpData;
            m_cDiagnosisBattery13EFData.m_bFlush = true;
            Q_EMIT signalDiagnosisBattery13EF(tmpData->m_nGeneralVolt,
                                            tmpData->m_nGeneralCurrent,
                                            tmpData->m_nSOC,
                                            tmpData->m_nBattSerialData,
                                            tmpData->m_nCellVoltSensorFault,
                                            tmpData->m_nGeneralVoltSensorFault,
                                            tmpData->m_n12VLessVolt,
                                            tmpData->m_n12VOverVolt);
        }
        else if (type == m_cDataType.DIAGNOSIS_BATTERY33EF_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBattery33EFData>(data);
            m_cDiagnosisBattery33EFData = *tmpData;
            m_cDiagnosisBattery33EFData.m_bFlush = true;
            Q_EMIT signalDiagnosisBattery33EF(tmpData->m_nBattMaxTemp,
                                            tmpData->m_nBattMaxTempCode,
                                            tmpData->m_nBattMinTemp,
                                            tmpData->m_nBattMinTempCode,
                                            tmpData->m_nDCchgGunBaseTemp0,
                                            tmpData->m_nDCchgGunBaseTemp1,
                                            tmpData->m_nAverageTemp);
        }
        else if (type == m_cDataType.DIAGNOSIS_BATTERY11EF_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBattery11EFData>(data);
            m_cDiagnosisBattery11EFData = *tmpData;
            m_cDiagnosisBattery11EFData.m_bFlush = true;
            Q_EMIT signalDiagnosisBattery11EF(tmpData->m_nSystemFaultLevel,
                                            tmpData->m_nHVlock,
                                            tmpData->m_nPowerDownReq,
                                            tmpData->m_nBMSMaxDischgPower,
                                            tmpData->m_nBMSMaxChgPower,
                                            tmpData->m_nDCchgVoltDemand,
                                            tmpData->m_nDCchgCurrentDemand,
                                            tmpData->m_nSystemStsCode);
        }
        else if (type == m_cDataType.DIAGNOSIS_BRAKE_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBrakeData>(data);
            m_cDiagnosisBrake = *tmpData;
            m_cDiagnosisBrake.m_bFlush = true;
            Q_EMIT signalDiagnosisBrake(tmpData->m_nEHB_WorkSts,
                                      tmpData->m_nBrakePress,
                                      tmpData->m_npedalPercent,
                                      tmpData->m_nPistonDisplacement,
                                      tmpData->m_nTargetPress,
                                      tmpData->m_nParkReq,
                                      tmpData->m_nBrakeSts,
                                      tmpData->m_nfaultLevel);
        }
        else if (type == m_cDataType.DIAGNOSIS_BRAKE60_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBrake60Data>(data);
            m_cDiagnosisBrake60 = *tmpData;
            m_cDiagnosisBrake60.m_bFlush = true;
            Q_EMIT signalDiagnosisBrake60(tmpData->m_nBrakeSts, tmpData->m_nParklight_sts, tmpData->m_nFaultlight_sts, tmpData->m_nSwitch_sts,
                                        tmpData->m_nSystem_sts, tmpData->m_nFault_message);
        }
        else if (type == m_cDataType.DIAGNOSIS_BRAKE5F_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisBrake5FData>(data);
            m_cDiagnosisBrake5FData = *tmpData;
            m_cDiagnosisBrake5FData.m_bFlush = true;
            Q_EMIT signalDiagnosisBrake5F(tmpData->m_nfaultCode1, tmpData->m_nfaultCode2, tmpData->m_nfaultCode3);
        }
        else if (type == m_cDataType.DIAGNOSIS_EPS_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisEPSData>(data);
            m_cDiagnosisEPS = *tmpData;
            m_cDiagnosisEPS.m_bFlush = true;
            Q_EMIT signalDiagnosisEPS(tmpData->m_nWorkModel,
                                    tmpData->m_nTargeTangle,
                                    tmpData->m_nWheelPalstance,
                                    tmpData->m_nAutoCMD_model,
                                    tmpData->m_nCurrentangle);
        }
        else if (type == m_cDataType.DIAGNOSIS_EPS5C_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisEPS5CData>(data);
            m_cDiagnosisEPS5CData = *tmpData;
            m_cDiagnosisEPS5CData.m_bFlush = true;
            Q_EMIT signalDiagnosisEPS5C(tmpData->m_nOut_torque,
                                      tmpData->m_nTarget_torque,
                                      tmpData->m_nFaultCode_92);
        }
        else if (type == m_cDataType.DIAGNOSIS_12VDC_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosis12VDCData>(data);
            m_cDiagnosis12V = *tmpData;
            m_cDiagnosis12V.m_bFlush = true;
            Q_EMIT signalDiagnosis12VDC(tmpData->m_nOutEnable,
                                      tmpData->m_nState,
                                      tmpData->m_nINVoltage,
                                      tmpData->m_nINCurrent,
                                      tmpData->m_nDCDCTemperature,
                                      tmpData->m_nOverTemperature,
                                      tmpData->m_nOut_voltage,
                                      tmpData->m_nOut_current,
                                      tmpData->m_nIn_over_current,
                                      tmpData->m_nOut_over_current,
                                      tmpData->m_nIn_over_voltage,
                                      tmpData->m_nIn_less_voltage,
                                      tmpData->m_nOut_over_voltage,
                                      tmpData->m_nOut_less_voltage);
        }
        else if (type == m_cDataType.DIAGNOSIS_48VDC_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosis48VDCData>(data);
            m_cDiagnosis48V = *tmpData;
            m_cDiagnosis48V.m_bFlush = true;
            Q_EMIT signalDiagnosis48VDC(tmpData->m_nOUTVolt,
                                      tmpData->m_nOUTCurrent,
                                      tmpData->m_nDCSts,
                                      tmpData->m_nOUTCutDownSts,
                                      tmpData->m_nFaultLevel,
                                      tmpData->m_nRadiatorTemp,
                                      tmpData->m_nINCutDownSts);
        }
        else if (type == m_cDataType.DIAGNOSIS_FAN902_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisFan902Data>(data);
            m_cDiagnosisFan902 = *tmpData;
            m_cDiagnosisFan902.m_bFlush = true;
            Q_EMIT signalDiagnosisFan902(tmpData->m_nFaultLevl,
                                       tmpData->m_nModSts,
                                       tmpData->m_nEnSts,
                                       tmpData->m_nPrechargeAllow,
                                       tmpData->m_nDirSts,
                                       tmpData->m_nActTorValid,
                                       tmpData->m_nActSpdValid,
                                       tmpData->m_nActTor,
                                       tmpData->m_nActSpd);
        }
        else if (type == m_cDataType.DIAGNOSIS_FANA02_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisFanA02Data>(data);
            m_cDiagnosisFanA02 = *tmpData;
            m_cDiagnosisFanA02.m_bFlush = true;
            Q_EMIT signalDiagnosisFanA02(tmpData->m_nDCVolt,
                                       tmpData->m_nDCCur,
                                       tmpData->m_nACCur);
        }
        else if (type == m_cDataType.DIAGNOSIS_FANB02_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisFanB02Data>(data);
            m_cDiagnosisFanB02 = *tmpData;
            m_cDiagnosisFanB02.m_bFlush = true;
            Q_EMIT signalDiagnosisFanB02(tmpData->m_nMotorMinAvaTor,
                                       tmpData->m_nMotorMaxAvaTor,
                                       tmpData->m_nMotorIGBTTemp,
                                       tmpData->m_nMTemp,
                                       tmpData->m_nCTemp);
        }
        else if (type == m_cDataType.DIAGNOSIS_FANC02_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisFanC02Data>(data);
            m_cDiagnosisFanC02 = *tmpData;
            m_cDiagnosisFanC02.m_bFlush = true;
            Q_EMIT signalDiagnosisFanC02(tmpData->m_nMOvSpdSts, tmpData->m_nMBlockSts, tmpData->m_nMOvTempSts,
                                       tmpData->m_nMOvCurSts, tmpData->m_nMShrSts, tmpData->m_nMShrGrdSts, tmpData->m_nCOvTempSts,
                                       tmpData->m_nCAuxBatSts, tmpData->m_nPreChaSts, tmpData->m_nIGBTModSts, tmpData->m_nIGBTOvTempSts,
                                       tmpData->m_nIGBTOvCurSts, tmpData->m_nCOvVoltSts, tmpData->m_nCLowVoltSts, tmpData->m_nIGBTTempSenSts,
                                       tmpData->m_nCANFault, tmpData->m_nMTempSenSts, tmpData->m_nCTempSenSts, tmpData->m_nCVoltSenSts,
                                       tmpData->m_nCCurSenSts, tmpData->m_nACCurSenSts, tmpData->m_nCTranFaultSts, tmpData->m_nMCutOffSts);
        }
        else if (type == m_cDataType.DIAGNOSIS_LEFTSWEEP_DATA ||
                 type == m_cDataType.DIAGNOSIS_RIGHTSWEEP_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisSweepDiskData>(data);
            if (tmpData->m_nDataType == m_cDataType.DIAGNOSIS_LEFTSWEEP_DATA)
            {
                m_cDiagnosisSweepDiskLeft = *tmpData;
                m_cDiagnosisSweepDiskLeft.m_bFlush = true;
            }
            else
            {
                m_cDiagnosisSweepDiskRight = *tmpData;
                m_cDiagnosisSweepDiskRight.m_bFlush = true;
            }
            Q_EMIT signalDiagnosisSweepDisk(tmpData->m_nMainVoltage,
                                          tmpData->m_nCurrentMotcurrent,
                                          tmpData->m_nEnableSts,
                                          tmpData->m_nWheelSts,
                                          tmpData->m_nMotTemperature,
                                          tmpData->m_nMotCurrentSpeed,
                                          tmpData->m_nOverCurrent,
                                          tmpData->m_nOverVoltage,
                                          tmpData->m_nOverTemperature,
                                          tmpData->m_nLochedRotor,
                                          tmpData->m_nHallSignalError,
                                          tmpData->m_nMotFualtItself,
                                          tmpData->m_nDataType);
        }
        else if (type == m_cDataType.DIAGNOSIS_HIGPREPUM15_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisHigPreDump15Data>(data);
            m_cDiagnosisHigPreDump15 = *tmpData;
            m_cDiagnosisHigPreDump15.m_bFlush = true;
            Q_EMIT signalDiagnosisHigPreDump15(tmpData->m_nMOTspeed, tmpData->m_nMOTBusbarVolt,
                                             tmpData->m_nMotTemp,
                                             tmpData->m_nIGBTTemp,
                                             tmpData->m_nMOT_current_AC,
                                             tmpData->m_nMOTFaultCodeSign);
        }
        else if (type == m_cDataType.DIAGNOSIS_HIGPREPUM16_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisHigPreDump16Data>(data);
            m_cDiagnosisHigPreDump16 = *tmpData;
            m_cDiagnosisHigPreDump16.m_bFlush = true;
            Q_EMIT signalDiagnosisHigPreDump16(tmpData->m_nMCUintSts, tmpData->m_nMCUModelSts);
        }
        else if (type == m_cDataType.DIAGNOSIS_COMMUNI_DATA)
        {
            auto tmpData = std::dynamic_pointer_cast<CDiagnosisCommuData>(data);
            m_cDiagnosisCommu = *tmpData;
            m_cDiagnosisCommu.m_bFlush = true;
            Q_EMIT signalDiagnosisCommu(tmpData->m_nBMS_CANerror, tmpData->m_nMCU_CANerror, tmpData->m_nEHB_CANerror,
                                      tmpData->m_nEPB_CANerror,
                                      tmpData->m_nEPS_CANerror,
                                      tmpData->m_nDC48V_CANerror,
                                      tmpData->m_nAC_CANerror,
                                      tmpData->m_nADU_CANerror,
                                      tmpData->m_nICU_CANerror,
                                      tmpData->m_nDC12V_CANerror,
                                      tmpData->m_nGPS_CANerror,
                                      tmpData->m_nFJI_CANerror,
                                      tmpData->m_nWP_CANerror,
                                      tmpData->m_nSPL_CANerror,
                                      tmpData->m_nSPR_CANerror);
        }

        data.reset();
    }
    // LOGGER->Cowa_Info("CUIDataHandle::", __FUNCTION__);
}

void CUIDataHandle::slotDiagnosisUpdateData(int dataType)
{
    std::shared_ptr<IData> data = nullptr;
    switch (dataType)
    {
    case m_cDataType.DIAGNOSIS_IO_DATA:
        if (m_cDiagnosisIO.m_bFlush)
        {
            data = std::make_shared<CDiagnosisIOData>(m_cDiagnosisIO);
        }
        break;
    case m_cDataType.DIAGNOSIS_IO71_DATA:
        if (m_cDiagnosisIO71Data.m_bFlush)
        {
            data = std::make_shared<CDiagnosisIO71Data>(m_cDiagnosisIO71Data);
        }
        break;
    case m_cDataType.DIAGNOSIS_IO78_DATA:
        if (m_cDiagnosisIO78Data.m_bFlush)
        {
            data = std::make_shared<CDiagnosisIO78Data>(m_cDiagnosisIO78Data);
        }
        break;
    case m_cDataType.DIAGNOSIS_IO79_DATA:
        if (m_cDiagnosisIO79Data.m_bFlush)
        {
            data = std::make_shared<CDiagnosisIO79Data>(m_cDiagnosisIO79Data);
        }
        break;
    case m_cDataType.DIAGNOSIS_BATTERY_DATA:
        if (m_cDiagnosisBattry.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBatteryData>(m_cDiagnosisBattry);
        }
        break;
    case m_cDataType.DIAGNOSIS_BATTERY13EF_DATA:
        if (m_cDiagnosisBattery13EFData.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBattery13EFData>(m_cDiagnosisBattery13EFData);
        }
        break;
    case m_cDataType.DIAGNOSIS_BATTERY33EF_DATA:
        if (m_cDiagnosisBattery33EFData.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBattery33EFData>(m_cDiagnosisBattery33EFData);
        }
        break;
    case m_cDataType.DIAGNOSIS_BATTERY11EF_DATA:
        if (m_cDiagnosisBattery11EFData.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBattery11EFData>(m_cDiagnosisBattery11EFData);
        }
        break;
    case m_cDataType.DIAGNOSIS_MAINDRI_DATA:
        if (m_cDiagnosisMainDri.m_bFlush)
        {
            data = std::make_shared<CDiagnosisMainDriData>(m_cDiagnosisMainDri);
        }
        break;
    case m_cDataType.DIAGNOSIS_BRAKE_DATA:
        if (m_cDiagnosisBrake.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBrakeData>(m_cDiagnosisBrake);
        }
        break;
    case m_cDataType.DIAGNOSIS_BRAKE5F_DATA:
        if (m_cDiagnosisBrake5FData.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBrake5FData>(m_cDiagnosisBrake5FData);
        }
        break;
    case m_cDataType.DIAGNOSIS_BRAKE60_DATA:
        if (m_cDiagnosisBrake60.m_bFlush)
        {
            data = std::make_shared<CDiagnosisBrake60Data>(m_cDiagnosisBrake60);
        }
        break;
    case m_cDataType.DIAGNOSIS_EPS_DATA:
        if (m_cDiagnosisEPS.m_bFlush)
        {
            data = std::make_shared<CDiagnosisEPSData>(m_cDiagnosisEPS);
        }
        break;
    case m_cDataType.DIAGNOSIS_EPS5C_DATA:
        if (m_cDiagnosisEPS5CData.m_bFlush)
        {
            data = std::make_shared<CDiagnosisEPS5CData>(m_cDiagnosisEPS5CData);
        }
        break;
    case m_cDataType.DIAGNOSIS_12VDC_DATA:
        if (m_cDiagnosis12V.m_bFlush)
        {
            data = std::make_shared<CDiagnosis12VDCData>(m_cDiagnosis12V);
        }
        break;
    case m_cDataType.DIAGNOSIS_48VDC_DATA:
        if (m_cDiagnosis48V.m_bFlush)
        {
            data = std::make_shared<CDiagnosis48VDCData>(m_cDiagnosis48V);
        }
        break;
    case m_cDataType.DIAGNOSIS_FAN902_DATA:
        if (m_cDiagnosisFan902.m_bFlush)
        {
            data = std::make_shared<CDiagnosisFan902Data>(m_cDiagnosisFan902);
        }
        break;
    case m_cDataType.DIAGNOSIS_FANA02_DATA:
        if (m_cDiagnosisFanA02.m_bFlush)
        {
            data = std::make_shared<CDiagnosisFanA02Data>(m_cDiagnosisFanA02);
        }
        break;
    case m_cDataType.DIAGNOSIS_FANB02_DATA:
        if (m_cDiagnosisFanB02.m_bFlush)
        {
            data = std::make_shared<CDiagnosisFanB02Data>(m_cDiagnosisFanB02);
        }
        break;
    case m_cDataType.DIAGNOSIS_FANC02_DATA:
        if (m_cDiagnosisFanC02.m_bFlush)
        {
            data = std::make_shared<CDiagnosisFanC02Data>(m_cDiagnosisFanC02);
        }
        break;
    case m_cDataType.DIAGNOSIS_LEFTSWEEP_DATA:
        if (m_cDiagnosisSweepDiskLeft.m_bFlush)
        {
            data = std::make_shared<CDiagnosisSweepDiskData>(m_cDiagnosisSweepDiskLeft);
            data->m_nDataType = m_cDataType.DIAGNOSIS_LEFTSWEEP_DATA;
        }
        break;
    case m_cDataType.DIAGNOSIS_RIGHTSWEEP_DATA:
        if (m_cDiagnosisSweepDiskRight.m_bFlush)
        {
            data = std::make_shared<CDiagnosisSweepDiskData>(m_cDiagnosisSweepDiskRight);
            data->m_nDataType = m_cDataType.DIAGNOSIS_RIGHTSWEEP_DATA;
        }
        break;
    case m_cDataType.DIAGNOSIS_HIGPREPUM15_DATA:
        if (m_cDiagnosisHigPreDump15.m_bFlush)
        {
            data = std::make_shared<CDiagnosisHigPreDump15Data>(m_cDiagnosisHigPreDump15);
        }
        break;
    case m_cDataType.DIAGNOSIS_HIGPREPUM16_DATA:
        if (m_cDiagnosisHigPreDump16.m_bFlush)
        {
            data = std::make_shared<CDiagnosisHigPreDump16Data>(m_cDiagnosisHigPreDump16);
        }
        break;
    case m_cDataType.DIAGNOSIS_COMMUNI_DATA:
        if (m_cDiagnosisCommu.m_bFlush)
        {
            data = std::make_shared<CDiagnosisCommuData>(m_cDiagnosisCommu);
        }
        break;
    default:
        break;
    }
    if (data)
    {
        m_lData.push_back(data);
        handleSubData(m_cDataType.LOCAL_CAN_DATA);
    }

    // qDebug() << "CUIDataHandle::" << __FUNCTION__ << dataType;
}
