#include "RtspMedia.h"
#include "VideoDecoder.h"
#include <QDateTime>
#include <QDebug>
//#include "util/test.h"

RtspMedia::RtspMedia(QObject* parent)
{
    connect(this,&RtspMedia::load,this,&RtspMedia::doLoad,Qt::QueuedConnection);
    connect(this,&RtspMedia::loadMediaData,this,&RtspMedia::doLoadMediaData,Qt::QueuedConnection);
    connect(this,&RtspMedia::play,this,&RtspMedia::doPlay,Qt::DirectConnection);
    connect(this,&RtspMedia::init, this, &RtspMedia::doInit, Qt::QueuedConnection);
    // moveToThread(&m_thread);
    // m_thread.start();
}

RtspMedia::~RtspMedia() {
    // doStop();
    // m_thread.wait();
}

void RtspMedia::destroy() {
    // doStop();
    // m_thread.wait();
}

void RtspMedia::run() {
    std::string data;
    while(true) {
        {
            std::unique_lock<std::mutex> guard(m_listMtx);
            while(m_dataList.empty()) {
                m_condr.wait(guard);
            }
            std::cout << "the size of m_dataList: " << m_dataList.size() << std::endl;
            if(!m_dataList.empty()) {
                data = m_dataList.front();
                m_dataList.pop_front();
            }
        }
        if(!data.empty()) {
            doLoadMediaData(data);
        }
    }
}

void RtspMedia::pushMediaData(const std::string &data) {
    {
        std::unique_lock<std::mutex> guard(m_listMtx);
        m_dataList.push_back(data);
        m_condr.notify_one();
    }
}

void RtspMedia::doInit() {
    int error = 0;
    // callback function
    auto call = [this](auto frame){
        Q_EMIT getFrame(frame);
    };
    error = m_decoder.initDecoder(call);
    if(error){
       m_status = Invalid;
       Q_EMIT invalid();
       return;
    }
    m_status = Loaded;
    Q_EMIT getInfo(QSize(m_decoder.width(),m_decoder.height()),m_decoder.format());
    qDebug() <<"*******init suscceed!!!";
}

void RtspMedia::doLoad(QString url)
{
    int error = 0;

    if(url.isEmpty()){
        m_status = Free;
        Q_EMIT free();
        return;
    }

    auto call = [this](auto frame){
        Q_EMIT getFrame(frame);
    };

    error = m_decoder.open(url,call);

    if(error){
       m_status = Invalid;
       Q_EMIT invalid();
       return;
    }

    m_status = Loaded;
    Q_EMIT getInfo(QSize(m_decoder.width(),m_decoder.height()),m_decoder.format());
    Q_EMIT loaded();

    {
        QMutexLocker playlocker(&m_mtx);
        m_cond.wait(&m_mtx);
        m_status = Playing;
        Q_EMIT played();
    }

    error =  m_decoder.decode2();
    if(error){
        return;
    }

    // while(!m_reqStop){
    //     if(m_reqPause){
    //         QMutexLocker pauselocker(&m_mtx);
    //         m_status = Paused;
    //         Q_EMIT paused();
    //         m_cond.wait(&m_mtx);
    //         m_reqPause = false;
    //         if(m_reqStop){
    //             break;
    //         }
    //         m_status =Playing;
    //         Q_EMIT played();
    //     }
    //     error =  m_decoder.decode2();
    //     if(error){
    //         break;
    //     }
    // }

    // {
    //     QMutexLocker locker(&m_mtx);
    //     m_reqPause = false;
    //     m_reqStop = false;
    //     m_status = Stopped;
    //     Q_EMIT stopped();
    // }

}

void RtspMedia::doLoadMediaData(const std::string &data)
{
    if(data.empty()) {
        qDebug() << "doLoadMediaData, data is empty";
        return;
    }
    qDebug() << "******start load media data *******";
    int error = 0;
    error =  m_decoder.decodeMediaData(data);
    if(error){
        return;
    }
}

void RtspMedia::doPlay()
{
    QMutexLocker locker(&m_mtx);
    if(m_status == Loaded){
        m_cond.notify_all();
    }else{
        qDebug() << "Only play afte loaded";
    }

}
