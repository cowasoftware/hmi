#include <QDebug>
#include <QTimer>

#include "./autodrive_item.h"
#include "./autodrive_renderer.h"

AutodriveItem::AutodriveItem(QQuickItem *parent) : QQuickFramebufferObject(parent),
												   timer_(this)

{
	setMirrorVertically(true);
	setAcceptedMouseButtons(Qt::AllButtons);
	setAcceptHoverEvents(true);
	setFlag(ItemAcceptsInputMethod, true);

	auto timeout = [this]()
	{
		update();
	};

	connect(&timer_, &QTimer::timeout, timeout);
	timer_.setInterval(1000/60);
	timer_.start();
}

AutodriveItem::~AutodriveItem()
{
}

QQuickFramebufferObject::Renderer *AutodriveItem::createRenderer() const
{
	auto render = new AutodriveRenderer();
	render->resetCamera(geometry_);
	connect(this, &AutodriveItem::sigGeometryChanged, render, &AutodriveRenderer::resetCamera);
	return render;
}

void AutodriveItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
	geometry_ = newGeometry;
	Q_EMIT sigGeometryChanged(newGeometry);
}
