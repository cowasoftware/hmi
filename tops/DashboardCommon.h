#ifndef DASHBOARDCOMMON_H
#define DASHBOARDCOMMON_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include "QTimer"
#include <iostream>

class DashboardCommon: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int mWidth READ getWidth WRITE setWidth);
	Q_PROPERTY(int mHeight READ getHeight WRITE setHeight);

public:
    explicit DashboardCommon(QQuickItem *parent = nullptr);
    ~DashboardCommon();

    int getWidth() const;
	void setWidth(int width);

	int getHeight() const;
	void setHeight(int height);

protected:

    /** 重绘函数
     * @param painter 
     */
	virtual void paint(QPainter *painter) override;

    /** 绘制主体部分，即外层圆弧
	 * @param painter 
	 */
	virtual void drawFrame(QPainter *painter);

	/** 绘制外层的表冠（圆弧）
	 * @param painter 
	 * @param xPos 外接矩形左上角x坐标
	 * @param yPos 外接矩形左上角y坐标
	 * @param width 外接矩形宽
	 * @param height 外接矩形高
	 * @param srartAngle	起始角度，逆时针方向为正，3点钟方向为0度角 
	 * @param endAngle 		终止角度
	 * @param lineWidth		画笔线宽
	 * @param color 	弧线颜色
	 * @param opcity 	不透明度
	 */
	void drawCrown(QPainter *painter, const int xPos, const int yPos, const int width, const int height, const int srartAngle, const int endAngle, const int lineWidth, QColor color, const qreal opcity);

	/** 绘制刻度线
	 * @param painter 
	 */
	virtual void drawScale(QPainter *painter);

	/** 绘制刻度值
	 * @param painter 
	 */
	virtual void drawScaleNum(QPainter *painter);

    // /** 绘制标题
	//  * @param painter 
	//  */
	// virtual void drawTitle(QPainter *painter);
	// virtual void drawIndicator(QPainter *painter);
    /** 绘制数值
	 * @param painter 
	 */
	virtual void drawNumericValue(QPainter *painter);

protected:
    int m_width;
	int m_height;
	int m_startAngle;
	int m_endAngle;
	int m_maxValue;
	int m_minValue;
	QString m_units;
    QTimer *m_updateTimer;

	QPainter* painter;

Q_SIGNALS:

public Q_SLOTS:
	virtual void repaint();

};

#endif // DASHBOARDCOMMON_H
