#pragma once
#include <QObject>
#include "Singleton.h"
#include "log.h"

using namespace Cowa;

class QQuickItem;

/** 顶部UI数据层
*/
class CUIBarHandle : public QObject
{
	Q_OBJECT
public:
    /** 构造函数
    @param [in] parent 父指针
    */
	explicit CUIBarHandle(QObject* parent = nullptr);

public:

    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();

    /** 初始化
    */
	void init();

    /** 反初始化
    */
	void uninit();

    /** 界面数据初始化
    */
    void initData();

    /** 设置大窗口指针
    @param [in] qmlAppObj qml根节点
    */
    void setAppItem(QObject* qmlAppObj);

	/** 查找界面中Item指针
    @param [in] itemId qml中节点id名
    @param [in] parentBeginItem 起始查找根节点，填空则查找所有节点 
    @return 返回查找到的节点指针
    */
    QQuickItem* findFirstItem(const QString& itemId, QQuickItem* parentBeginItem = nullptr);

    /** 设置电池电量
    @param [in] percent 百分比
    */
    void setEnergyPercent(qint32 percent);

    /** 设置电池是否是充电状态
    @param [in] isCharge 是否是充电状态
    */
    void setEnergyIsCharge(bool isCharge);

    /** 设置电压
    @param [in] voltage 电压
    */
    void setVoltage(const QString& voltage);

    /** 设置电流
    @param [in] electricity 电流
    */
    void setElectricity(const QString& electricity);

Q_SIGNALS:
    /** 更新日期
    @param [in] dateString 日期字符串
    */
    void signalUpdateDate(const QString& dateString);

    /** 更新时间
    @param [in] timeString 时间字符串
    */
    void signalUpdateTime(const QString& timeString);

    /** 更新星期
    @param [in] weekString 星期字符串
    */
    void signalUpdateWeek(const QString& weekString);

    /** 更新电池电量
    @param [in] percent 电量百分比
    */
    void signalUpdateEnergyPercent(qint32 percent);

    /** 更新电池是否是充电状态
    @param [in] isCharge 是否是充电状态
    */
    void signalUpdateEnergyIsCharge(bool isCharge);

    /** 更新电压
    @param [in] voltage 电压
    */
    void signalUpdateVoltage(const QString& voltage);
    
    /** 更新电流
    @param [in] electricity 电流
    */
    void signalUpdateElectricity(const QString& electricity);

    /** 更新卡
    @param [in] cardString 卡信息
    @param [in] quality 信号质量，0-4和99，99表示无信号
    */
    void signalUpdateCard(const QString& cardString, qint32 quality);

private Q_SLOTS:
    /** 更新窗口时间
    */
    void onUpdateBarWindow();

    /** 接收电压电流的can消息
    @param [in] voltage 电压
    @param [in] electricity 电流
    @param [in] soc 电量
    */
    void onUpdateCanMsg_0x18F413EFToUIBarHandle(quint32 voltage, quint32 electricity, quint32 soc);

    /** 接收CanMsg_0x6F消息
    @param [in] isCharge 是否是充电状态
    */
    void onUpdateCanMsg_0x6FToUIBarHandle(quint32 isCharge);

    /** 接收网络信息消息
    @param [in] csq 信号质量
    @param [in] cops 运营商
    */
    void onUpdateModermToUIBarHandle(QString csq, QString cops);

protected:
    //qml窗口指针
	QQuickItem* m_qmlAppItem;
    //日期
    QString m_barDate;
    //时间
    QString m_barTime;
    //星期
    QString m_barWeek;
};

typedef Singleton<CUIBarHandle> SingletonCUIBarHandle;