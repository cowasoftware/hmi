#include "Timer.h"

#include <QDebug>
#include <QTimer>
#include <iostream>

#define TIMER_TIMEOUT (300) // 100ms
#define LOGGER GetLogMgr().getLogger()

CTimer::CTimer(QObject *parent)
    : QObject(parent)
{
}

CTimer::~CTimer()
{
}

inline CLogMgr& CTimer::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT);
  return my_logger;
}

void CTimer::init()
{
    m_pTimer = std::make_shared<QTimer>(this);
    connect(&(*m_pTimer), SIGNAL(timeout()), this, SLOT(handleTimeout()));
}

void CTimer::startTimer()
{
    if (m_pTimer != nullptr)
    {
        m_pTimer->start(TIMER_TIMEOUT);
    }else
    {
        LOGGER->Cowa_Warn("startTimer error, m_pTimer is nullptr...");
    }
    
}

void CTimer::stopTimer()
{
    if (m_pTimer->isActive())
    {
        m_pTimer->stop();
    }
}

void CTimer::handleTimeout()
{
    //qDebug() << "Enter timeout processing function\n";
    Q_EMIT dealSubDataSignal(m_cType.SCRB_CAN_DATA);
}

void CTimer::TimerExit()
{
    stopTimer();
}
