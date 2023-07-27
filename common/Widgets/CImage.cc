#include "CImage.h"
#include "CWidgetManager.h"
#include <QDebug>


CWImageView::CWImageView(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    qDebug() << "CWImageView is created..";
    //默认图片
    // m_pImage = new QImage("/resource/asset/image/debug/light/camera_loading.png");
    m_pImage = nullptr;
    // connect(this, SIGNAL(signalRedraw()), this, SLOT(update()));
}

CWImageView::~CWImageView() {
    free();
}

void CWImageView::paint(QPainter *painter)
{
    qDebug() << "paint image......";
    if (painter == nullptr) {
        return;
    }
    m_pImage = CWidgetManager::getInstance().getQImage();
    if (m_pImage == nullptr){
        qDebug() << "QImage data is null!!!";
        return;
    }
    
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true );
    painter->drawImage(QRect(get_x(), get_y(), get_width(), get_height()), *m_pImage);
    // 释放指针
    free();
}

void CWImageView::updateImage() {
    this->update();
}

void CWImageView::free() {
    if(m_pImage != nullptr) {
        delete m_pImage;
        m_pImage = nullptr;
    }
}


