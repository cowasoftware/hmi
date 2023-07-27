#include "SaveFrameTask.h"
#include <QImage>
#include "Util.h"
//#include "SendToMessageTest.h"
#include <chrono>
#include "OpenGLManager.h"

SaveFrameTask::SaveFrameTask():
m_time(0),
m_frameNum(0),
m_spFrame(nullptr)
{

}

void SaveFrameTask::DoTask()
{
	auto mTime = std::chrono::nanoseconds(m_time);
    auto tp = std::chrono::time_point<std::chrono::system_clock,std::chrono::nanoseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* now = std::gmtime(&tt);
    int32_t year = now->tm_year + 1900;
    int32_t month = now->tm_mon + 1;
	uint64_t mill = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count()
        -std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count() * 1000;
    std::string fileName = Util::Format("frame/%d%02d%02d%02d%02d%02d%03lld_%d.png",
		year, month, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, mill, m_frameNum);

	m_spFrame->save((OpenGLManager::instance().GetCurrentExePath() + fileName).c_str());
}

void SaveFrameTask::setParam(uint64_t time, int32_t frameNum, const std::shared_ptr<QImage>& spFrame)
{
	m_time = time;
	m_frameNum = frameNum;
	m_spFrame = spFrame;
}