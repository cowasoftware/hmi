#include "RtspPlayer.h"
#include <QDebug>


RtspPlayer::RtspPlayer():
    m_media(nullptr)
{
    m_media = new RtspMedia();
    m_canServer = SingletonCUIDataHandle::getInstance()->canServerPtr();

    connect(m_media,&RtspMedia::getInfo,this,[this](QSize size, int format){
        setFormat(size.width(),size.height(),format);
    });

    connect(m_media,&RtspMedia::getFrame,this,&RtspPlayer::doProvide);

    connect(this, &RtspPlayer::urlChanged, this, [this]() {
        load(get_url());
    });
    // Q_EMIT m_media->init();
    m_media->doInit();
    m_media->start();

    // connect(&(*m_canServer), &CCanServer::sendMediaData, this, &RtspPlayer::loadMediaData);
    connect(&(*m_canServer), SIGNAL(sendMediaData(const std::string &)), this, SLOT(loadMediaData(const std::string &)));
}

RtspPlayer::~RtspPlayer()
{
    // m_media->deleteLater();
}

void RtspPlayer::destroy() {
    qDebug() << "******************RtspPlayer destroy.**********";
    m_media->quit();
    m_media->wait();
    m_media->deleteLater();
}

void RtspPlayer::load(QString url)
{
    switch(get_status()){
    case Free:
        Q_EMIT m_media->load(url);
        break;
    case Loaded:
    case Paused:
        Q_EMIT m_media->load(url);
        break;
    case Stopped:
        Q_EMIT m_media->load(url);
        break;
    default:
        break;
    }
}

void RtspPlayer::loadMediaData(const std::string &data) {
    // saveToFile(data);
    // std::cout << __func__ << std::endl;
    if(m_canLoad) {
        m_media->pushMediaData(data);
    }
}

void RtspPlayer::play()
{
    qDebug() << "*********start play media";
    switch(get_status()){
    case Free:
        qDebug() << "data is empty, can not play";
        break;
    case Loaded:
        Q_EMIT m_media->play();
        break;
    default:
        break;
    }
}

void RtspPlayer::loadPage(bool canLoad) {
    m_canLoad = canLoad;
}

// void RtspPlayer::saveToFile(const std::string &data)
// {
//     svbox::ImageFrame msg;
//     if(!msg.ParseFromString(data)) {
//       qDebug() << "*******parse data failed!!!!";
//       return;
//     }
//     uint64_t len = msg.data().size();
//     if(len > 0 && (mFile != NULL)) {
//       fwrite(msg.data().data(), 1, len, mFile);
//       fflush(mFile);
//     }
// }