#pragma once
#include "CTask.h"
#include <list>
#include <map>
#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

class Semaphore;

class CTaskThread
{
    friend class CTaskThreadManager;
public:
    void PostTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel = 1);

    bool TryPostTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel = 1);

    void SendTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel = 1);

    bool HasTask();

	void StopCurTask();

    void StopTask(int32_t taskId, int32_t taskLevel = 0);

    void StopAllTask();

    void GetWaitTaskInfo(std::map<int32_t, int32_t>& taskCountMap);

	int32_t GetWaitTaskCount();

	int32_t GetCurTaskLevel();

	void WaitForEnd();

public:
	~CTaskThread();

private:
    CTaskThread(int32_t threadId);

    bool CreateThread();

    void DestroyThread();

    void SetExitSignal();

    void WaitForExit();

    void PopToCurTask();

    void StopTaskInList(const std::list<std::shared_ptr<CTask>>& taskList, int32_t taskId);

    void WorkThread();

    void StopAllTaskUnlock();

	void HandlePostTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel);

private:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    std::map<int32_t, std::list<std::shared_ptr<CTask>>> m_taskMap;

    std::shared_ptr<CTask> m_spCurTask;

    std::shared_ptr<CTask> m_spCurTaskBk;

    std::unique_ptr<std::thread> m_spWorkThread;

    std::mutex m_mutex;

    std::atomic<bool> m_hasExitSignal;

	std::atomic<bool> m_waitForEndSignal;

	std::atomic<int32_t> m_curTaskLevel;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    
    int32_t m_threadId;

	Semaphore* m_semaphore;
};