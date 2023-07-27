#pragma once
#include "CTaskThreadManagerMacro.h"
#include <stdint.h>

class Semaphore;
class CTask
{
	friend class CTaskThread;
public:
	CTask();
    CTask(int32_t taskId);

	virtual ~CTask();

public:
    virtual void DoTask() = 0;
    virtual void StopTask();
    virtual bool ReExecute();
    virtual CTask* Clone();

    int32_t GetTaskId();

private:
	void SetWaitForSendHandle(Semaphore* waitForSend);
	Semaphore* GetWaitForSendHandle();

protected:
    int32_t m_taskId;

	Semaphore* m_waitForSend;
};