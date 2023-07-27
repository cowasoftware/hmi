#pragma once

#include <QDebug>
#include <QTimer>
#include <QRectF>

#include <cppgl.h>
#include <three.h>
#include <QImage>
#include <vector>
#include <mutex>
#include <memory>
#include "GlParam.h"

class Skybox;

class MapRenderer : public QObject
{
	Q_OBJECT
public:
	MapRenderer(cppgl::CppGL *gl, QObject *parent = nullptr);
	virtual ~MapRenderer();

public:
	void Init();
	void Sync();
	void Render();

Q_SIGNALS:
	void mapInited();

public Q_SLOTS:
	void ResetCamera(QRectF rect);
	void onMapInited();

private:
	cppgl::CppGL* m_GL;
	Skybox* skybox_;
};