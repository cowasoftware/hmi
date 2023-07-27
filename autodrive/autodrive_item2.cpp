#include <QSGSimpleRectNode>
#include <QTimer>
#include <QDebug>
#include <QQuickWindow>
#include <QSGImageNode>
#include <QOffscreenSurface>

#include <three.h>

#include "SystemOS.h"

#include "autodrive_item2.h"
#include "autodrive_renderer2.h"

#if (SYSTEM_OS == 1)
#include "qtgles3.h"
#elif (SYSTEM_OS == 2)
#include "qtglcore330.h"
#endif

extern int32_t g_windowWidth;
extern int32_t g_windowHeight;

cppgl::CppGL *g_gl = nullptr;

AutodriveItem2::AutodriveItem2(QQuickItem *parent)
    : QQuickItem(parent)
{

    setFlag(ItemHasContents, true); // 有图像显示，设置为true

    auto timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this,
            [&]()
            {
                static bool is_first = true;

                if (is_first)
                {
                    update();
                    if (isVisible())
                    {
                        is_first = false;
                    }
                }
                else if (isVisible())
                {
                    update();
                }
            });

    timer->setInterval(1000 / 120);
    timer->start();
}

AutodriveItem2::~AutodriveItem2()
{
}

QSGNode *AutodriveItem2::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    auto *node = static_cast<QSGImageNode *>(oldNode);

    if (!node)
    {
        node = window()->createImageNode();
        image_ = QImage(width(), height(), QImage::Format_RGB888);
        QSGTexture *texture = window()->createTextureFromImage(image_);
        node->setTexture(texture);
    }

    if (!renderer_)
    {
        if (g_gl == nullptr)
        {
#if (SYSTEM_OS == 1)
            gl_ = new QtGLES3();
#elif (SYSTEM_OS == 2)
            gl_ = new QtGLCORE330();
#endif
            g_gl = gl_;
        }
        else
        {
            gl_ = g_gl;
        }
        g_windowWidth = width();
        g_windowHeight = height();
        renderer_ = new AutodriveRenderer2(*gl_, size());
        connect(this, &AutodriveItem2::sigGeometryChanged, renderer_, &AutodriveRenderer2::ResetSize);
        connect(window(), &QQuickWindow::sceneGraphInvalidated, renderer_,
                [&]()
                {
                    renderer_->deleteLater();
                    ObjectManager::ins()
                        .Destroy();
                });
        renderer_->Init();
    }

    renderer_->Sync();
    int textId = renderer_->Render();

    QQuickWindow::CreateTextureOptions texOpts;
    texOpts.setFlag(QQuickWindow::TextureHasAlphaChannel);
    QSGTexture *texture = window()->createTextureFromNativeObject(QQuickWindow::NativeObjectTexture, &textId, 0, size().toSize(), texOpts);
    node->setTextureCoordinatesTransform(QSGImageNode::MirrorVertically);
    node->setTexture(texture);
    node->setRect(boundingRect());
    return node;
}

void AutodriveItem2::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_EMIT sigGeometryChanged(newGeometry);
}