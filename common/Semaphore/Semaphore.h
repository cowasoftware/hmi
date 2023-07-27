#pragma once
#include <condition_variable>
#include <mutex>
#include "SemaphoreMacro.h"
#ifdef _MSC_VER
#include <windows.h>
#elif __unix__
#include <string>
#endif

class Semaphore
{
public:
	Semaphore();

	~Semaphore();

public:
	void signal();

	void wait();

	bool wait(int32_t timeout);

	void createProcessSemaphore(const std::string& name, int32_t signalCount = 800000000);

	void openProcessSemaphore(const std::string& name);

	void closeProcessSemaphore();

	void processSignal();

	void processWait();

	bool processWait(int32_t timeout);

	void event();

	void eventAll();

	void eventWait();

	bool eventWait(int32_t timeout);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::mutex m_mtx;
	std::condition_variable m_cv;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	int32_t m_count;

#ifdef _MSC_VER
	HANDLE m_processSemaphore;
#elif __unix__
	int m_processSemaphoreId;
	std::string m_name;
#endif
};