#ifndef CWImageView_H
#define CWImageView_H

#include <QImage>
#include <QPainter>
#include <QObject>
#include <QQuickPaintedItem>
#include "qmlreflect.h"

class CWImageView : public QQuickPaintedItem
{
    Q_OBJECT
    PROPERTY(quint32, width, 0);
    PROPERTY(quint32, height, 0);
    PROPERTY(quint32, x, 0);
    PROPERTY(quint32, y, 0);

public:
    explicit CWImageView(QQuickItem *parent = nullptr);
    virtual ~CWImageView();
    virtual void paint(QPainter *painter) override;


private:
    void free();

Q_SIGNALS:
    void signalRedraw();

public Q_SLOTS:
    void updateImage();

private:
    QImage *m_pImage;
    std::shared_ptr<QImage> m_spImage;
    
};

#endif