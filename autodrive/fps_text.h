#pragma once

#include <QQuickPaintedItem>

class FPSText: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)
public:
    FPSText(QQuickItem *parent = 0);
    ~FPSText();
    void paint(QPainter *);
    Q_INVOKABLE int fps()const;

Q_SIGNALS:
    void fpsChanged(int);

private:
    void recalculateFPS();
    int _currentFPS;
    int _cacheCount;
    QVector<qint64> _times;
};
