#ifndef ODOMETER_H 
#define ODOMETER_H

#include <QObject>
#include <DashboardCommon.h>

class Odometer : public DashboardCommon
{
    Q_OBJECT
	Q_PROPERTY(int mTotalMileage READ getTotalMileage WRITE setTotalMileage);

public:
    explicit Odometer(QQuickItem *parent = nullptr);
    ~Odometer();

    int getTotalMileage() const;
	void setTotalMileage(int totalMileage);

protected:

	void paint(QPainter *painter) override;

	void drawFrame(QPainter *painter) override;

	void drawScale(QPainter *painter) override;

	void drawScaleNum(QPainter *painter) override;
	
	void drawNumericValue(QPainter *painter) override;

private:
    int m_totalMileage;

Q_SIGNALS:
	void signalRedraw();

public Q_SLOTS:
	void repaint();

};

#endif // ODOMETER_H
