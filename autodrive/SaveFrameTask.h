#pragma once
#include "CTaskThreadManagerAPI.h"
#include <memory>

class QImage;

class SaveFrameTask : public CTask
{
public:
	SaveFrameTask();

public:
	void DoTask();

	void setParam(uint64_t time, int32_t frameNum, const std::shared_ptr<QImage>& spFrame);

private:
	uint64_t m_time;
	int32_t m_frameNum;
	std::shared_ptr<QImage> m_spFrame;
};