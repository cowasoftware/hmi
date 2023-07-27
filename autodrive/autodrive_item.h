#pragma once

#include <map>
#include <set>

#include <QTimer>
#include <QQuickFramebufferObject>


class AutodriveItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    AutodriveItem(QQuickItem *parent = nullptr);
    ~AutodriveItem();
Q_SIGNALS:
    void sigGeometryChanged(QRectF);

protected:
    QQuickFramebufferObject::Renderer *createRenderer() const override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    QTimer timer_;
    QRectF geometry_;
};
