#pragma once

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include "qmlreflect.h"

class FrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
public:
    FrameProvider(QObject* parent =nullptr);
    virtual ~FrameProvider();

public:
    QAbstractVideoSurface* videoSurface() const { return m_surface; }
    void setVideoSurface(QAbstractVideoSurface* surface);

public:
    void setFormat(int width, int heigth, int format);

public Q_SLOTS:
    void doProvide(const QVideoFrame& frame);

private:
    QAbstractVideoSurface* m_surface = NULL;
    QVideoSurfaceFormat m_format;
};
