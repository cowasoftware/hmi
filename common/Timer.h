#ifndef _TIMER_H  
#define _TIMER_H  
   
#include <QObject> 
#include <memory> 

#include "Data.h"
#include "log.h"

using namespace Cowa;

class QTimer;  
class CTimer : public QObject  
{  
    Q_OBJECT  
   
public:  
    CTimer(QObject* parent = NULL);  
    ~CTimer();
    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();
    void init();
    void startTimer();
    void stopTimer();
  
Q_SIGNALS:
    void dealSubDataSignal(int data);

public Q_SLOTS:  
    void handleTimeout();  //超时处理函数 
    void TimerExit();

private:  
    std::shared_ptr<QTimer>     m_pTimer; 
    DataType                    m_cType; 
};  
   
 #endif //_TIMER_H  
