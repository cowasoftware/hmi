#ifndef CWidgetManager_H
#define CWidgetManager_H

#include <QObject>
#include <QImage>
#include <QPainter>

/**
 * 自定义组件管理类
*/
class CWidgetManager : public QObject
{
    Q_OBJECT
public:
    CWidgetManager(/* args */);
    ~CWidgetManager();
    static CWidgetManager& getInstance();
    void setQImage(QImage* image);
    void setQImage(std::shared_ptr<QImage> image_ptr);

    std::shared_ptr<QImage> getQImagePtr();
    QImage* getQImage();
    // 生成对应的控件
    void createWidgetFromData(const char *data, int size, const char *format);
    
    // qml注册组件
    void registerWidget();

private:
    void free();

private:
    QImage *m_pImage;
    std::shared_ptr<QImage>  m_spImage;

};
#endif


