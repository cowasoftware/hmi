#pragma once
#include <atomic>
#include <vector>
#include <mutex>
#include <memory>
#include "GlParam.h"

namespace cppgl
{
	class CppGL;
};
class QOpenGLFramebufferObject;
class AutodriveRenderer;

class AutodriveManager
{
protected:
	AutodriveManager();

public:
	static AutodriveManager& instance();

public:
	void init();

	void initMap();

	bool isInited();

	void render(QOpenGLFramebufferObject* frameBuffer);

	void reset();

	void uninit();

public:
	std::atomic<bool> m_isInited;
	cppgl::CppGL* m_GL;

	DrawMemoryInfo m_allRoadInfo;
	DrawMemoryInfo m_groundInfo;
	uint32_t m_groundTextureId;

	//std::mutex m_saveMutex;
	//std::vector<std::shared_ptr<QImage>> m_vecSaveImage;

	std::pair<std::vector<float>, std::vector<DrawInfo>> m_verticesData;

	std::vector<uint32_t> m_vecThreadId;

	int32_t m_frameId;
	uint64_t m_oldTimestamp;
};