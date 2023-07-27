#include "CWidgetManager.h"
#include "CImage.h"
#include <QDebug>


CWidgetManager::CWidgetManager(/* args */)
{
    m_pImage = nullptr;
}

CWidgetManager::~CWidgetManager()
{
    free();
}

CWidgetManager& CWidgetManager::getInstance() {
    static CWidgetManager s_manager;
    return s_manager;
}

void CWidgetManager::createWidgetFromData(const char *data, int size, const char *format = nullptr) {
    // 根据format构造对应的控件
    // qDebug() << "create widget from data." << data;
    if(0 == strcmp(format, "JPG") || 0 == strcmp(format, "PNG") || 0 == strcmp(format, "JPEG") || 0 == strcmp(format, "GIF") || 0 == strcmp(format, "BPM")) {
        // 转化成图片
        m_pImage = new QImage();
        bool result = m_pImage->loadFromData(reinterpret_cast<const uchar*>(data), size, format);
        if(!result) {
            // qDebug() << "create widget failed, format is error!!!";
            return;
        }
    }
}

void CWidgetManager::setQImage(QImage* image) {
    m_pImage = image;
}

void CWidgetManager::setQImage(std::shared_ptr<QImage> image_ptr) {
    m_spImage = image_ptr;
}

std::shared_ptr<QImage> CWidgetManager::getQImagePtr() {
    return m_spImage;
}

QImage* CWidgetManager::getQImage() {
    return m_pImage;
} 

void CWidgetManager::free() {
    if(m_pImage != nullptr) {
        delete m_pImage;
        m_pImage = nullptr;
    }
}

void CWidgetManager::registerWidget() {
    int versionMajor = 1;
    int versionMinor = 0;
    qmlRegisterType<CWImageView>("Cowa.ImageView",versionMajor,versionMinor,"CWImageView");
}

