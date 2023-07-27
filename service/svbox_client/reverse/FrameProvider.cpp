#include "FrameProvider.h"
#include <QDateTime>
#include <QDebug>


FrameProvider::FrameProvider(QObject* parent):
    QObject(parent)
{
}


FrameProvider::~FrameProvider()
{
}

void FrameProvider::setVideoSurface(QAbstractVideoSurface* surface)
{
    if (m_surface && m_surface != surface && m_surface->isActive()) {
        m_surface->stop();
    }

    m_surface = surface;

    if (m_surface && m_format.isValid())
    {
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);

    }
}

void  FrameProvider::setFormat(int width, int heigth, int format)
{
    QSize size(width, heigth);
    QVideoSurfaceFormat surfaceFormat(size, static_cast<QVideoFrame::PixelFormat>(format));
    m_format = surfaceFormat;

    if (m_surface)
    {
        if (m_surface->isActive())
        {
            m_surface->stop();
        }
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void  FrameProvider::doProvide(const QVideoFrame& frame)
{
    static qint64  before = QDateTime::currentMSecsSinceEpoch();
    qint64 fps =  QDateTime::currentMSecsSinceEpoch() - before;
    before += fps;
    //qDebug() << fps;
    if (m_surface)
        m_surface->present(frame);
}

