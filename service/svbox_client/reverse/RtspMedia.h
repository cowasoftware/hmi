#pragma once
#include <QThread>
#include <QImage>
#include <QPainter>
#include <QVideoFrame>
#include <QWaitCondition>
#include <QMutex>
#include <QMutexLocker>
#include "VideoDecoder.h"


class RtspMedia:public QThread
{
    Q_OBJECT
public:
    explicit RtspMedia(QObject* parent = nullptr);
    ~RtspMedia();
    void destroy();
    void run() override;
    void pushMediaData(const std::string &data);

public:
    enum Status {
        Free,
        Invalid,
        Loaded,
        Playing,
        Paused,
        Stopped,
    };
Q_SIGNALS:
    void init();
    void load(QString url);
    void loadMediaData(const std::string &data);
    void play();
    void getInfo(QSize size, QVideoFrame::PixelFormat format);
    void getFrame(const QVideoFrame& frame);

    void free();
    void invalid();
    void loaded();
    void played();
    // void paused();
    // void stopped();
public Q_SLOTS:
    void doInit();
    void doLoad(QString);
    void doLoadMediaData(const std::string &data);
    void doPlay();
private:
    // bool m_reqStop = false;
    // bool m_reqPause = false;
    Status m_status = Free;
    std::list<std::string> m_dataList;
    std::condition_variable m_condr;
    std::mutex m_listMtx;
    QMutex m_mtx;
    QWaitCondition m_cond;
    QThread m_thread;
    VideoDecoder m_decoder;

};
