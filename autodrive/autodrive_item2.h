#pragma once

#include <QQuickItem>
#include <QImage>
#include <QSize>

#include "autodrive_renderer2.h"

class AutodriveItem2 : public QQuickItem
{
    Q_OBJECT
public:
    AutodriveItem2(QQuickItem *parent = nullptr);
    ~AutodriveItem2();

Q_SIGNALS:
    void sigGeometryChanged(QRectF);
    
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    QImage image_;
    cppgl::CppGL* gl_{nullptr};
    AutodriveRenderer2* renderer_{nullptr};
};