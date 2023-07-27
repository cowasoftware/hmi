#pragma once

#include <QObject>

#include "object_renderer.h"
#include "map_renderer.h"
#include "offscreen_context.h"

class AutodriveRenderer2 : public QObject
{
    Q_OBJECT
public:
    AutodriveRenderer2(cppgl::CppGL &gl, QSizeF const &size);
    ~AutodriveRenderer2();

public Q_SLOTS:
    void ResetSize(QRectF);

public:
    void Init();
    void Sync();
    uint32_t Render();

private:
    cppgl::CppGL &gl_;
    ObjectRenderer *object_renderer_ = nullptr;
    MapRenderer *map_renderer_ = nullptr;
    OffscreenContext *ctx_ = nullptr;
    QSizeF size_;
};