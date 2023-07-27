#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QObject>
// #include <QQuickItem>
#include <QtWidgets/QWidget>
#include <DashboardCommon.h>

class Dashboard : public DashboardCommon
{
    Q_OBJECT
	Q_PROPERTY(int mRate READ getRate WRITE setRate);

public:
    explicit Dashboard(QQuickItem *parent = nullptr);
    virtual ~Dashboard();
	int getRate() const;
	void setRate(int rate);

protected:

	/** 重绘事件
	 */
    // void paintEvent(QPaintEvent *);

	void paint(QPainter *painter) override;

	void drawFrame(QPainter *painter) override;

	void drawScale(QPainter *painter) override;

	void drawScaleNum(QPainter *painter) override;
	
	void drawNumericValue(QPainter *painter) override;

private:
	int m_rate;

Q_SIGNALS:
	void signalRedraw();

public Q_SLOTS:
	void repaint();

};

#endif // DASHBOARD_H
