#pragma once


#include "FrameProvider.h"
#include "RtspMedia.h"
#include "qmlreflect.h"
#include "Singleton.h"
#include "CanServer.h"
#include "UIDataHandle.h"

class RtspPlayer :public FrameProvider {

public:
    enum Status {
		Free,
		Loaded,
		Playing,
		Paused,
		Stopped,
	};
	Q_OBJECT
	Q_ENUM(Status)
	PROPERTY(QString, url, "")
	READ_PROPERTY(int, status, Free)

public:
	
public:
	RtspPlayer();
	virtual ~RtspPlayer();
	Q_INVOKABLE void destroy();

public:
	Q_INVOKABLE void load(QString url);
    Q_INVOKABLE void play();
	// 测试保存h264文件
	// void saveToFile(const std::string& data);

public Q_SLOTS:
	// 加载倒车影像页面
	void loadPage(bool canLoad);
	// 加载media数据
    void loadMediaData(const std::string& data);

private:
	RtspMedia* m_media = nullptr;
	std::shared_ptr<CCanServer>         m_canServer;
	bool m_canLoad = false;
	// FILE *mFile = fopen("/home/cowa/Works/reverse_image/svbox/aaa.h264","wb+");
};
// typedef Singleton<RtspPlayer> SingletonRtspPlayer;
