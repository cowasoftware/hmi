#include "UIBarHandle.h"
#include "CanServer.h"
#include "UIDataHandle.h"
#include <QDateTime>
#include <QDebug>
#include <QQmlContext>
#include <QTimer>
#include <QWindow>
#include <QtQuick/QQuickItem>
#include <string>
#include <thread>
//#include "SendToMessageTest.h"

#define LOGGER GetLogMgr().getLogger()

CUIBarHandle::CUIBarHandle(QObject *parent) : QObject(parent) {}

inline CLogMgr& CUIBarHandle::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT);
  return my_logger;
}

void CUIBarHandle::init() {
  auto spCanServer = SingletonCUIDataHandle::getInstance()->canServerPtr();
  QObject::connect(spCanServer.get(),
                   &CCanServer::updateCanMsg_0x18F413EFToUIBarHandle, this,
                   &CUIBarHandle::onUpdateCanMsg_0x18F413EFToUIBarHandle);
  QObject::connect(spCanServer.get(),
                   &CCanServer::updateCanMsg_0x6FToUIBarHandle, this,
                   &CUIBarHandle::onUpdateCanMsg_0x6FToUIBarHandle);
  QObject::connect(spCanServer.get(), &CCanServer::updateModermToUIBarHandle,
                   this, &CUIBarHandle::onUpdateModermToUIBarHandle);
}

void CUIBarHandle::uninit() {}

void CUIBarHandle::initData() {
  onUpdateBarWindow();
  SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(
      DataType::LIGHTSCREEN_DATA);
  SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(
      DataType::BAR_0x18F413EF_DATA);
  SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(
      DataType::BAR_NETWORK_DATA);

  QTimer *timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onUpdateBarWindow()));
  // timer->start();
  timer->start(1000);
}

void CUIBarHandle::setAppItem(QObject *qmlAppObj) {
  //获取qml在的源窗口
  QWindow *qmlWindow = qobject_cast<QWindow *>(qmlAppObj);
  //设置一个窗口标签，确认自己拿到的窗口句柄就是自己想要的
  qmlWindow->setTitle("cowatboxhmi");
  // Qml窗口的句柄
  WId parent_HWND = qmlWindow->winId();
  m_qmlAppItem = qmlWindow->property("contentItem").value<QQuickItem *>();
}

QQuickItem *CUIBarHandle::findFirstItem(const QString &itemId,
                                        QQuickItem *parentBeginItem) {
  QQuickItem *parentItem = parentBeginItem;
  if (parentBeginItem == nullptr) {
    parentItem = m_qmlAppItem;
  }

  if (parentItem == nullptr) {
    return nullptr;
  }

  QQmlContext *rootContext = qmlContext(parentItem);
  if (rootContext == nullptr) {
    return nullptr;
  }
  if (rootContext->nameForObject(parentItem) == itemId) {
    return parentItem;
  }

  QList<QQuickItem *> list = parentItem->childItems();
  if (list.isEmpty()) {
    return nullptr;
  }

  for (QQuickItem *item : list) {
    if (item == nullptr) {
      continue;
    }
    QQmlContext *context = qmlContext(item);
    if (context == nullptr) {
      continue;
    }
    QString idName = context->nameForObject(item);
    if (idName == itemId) {
      return item;
    }
    QQuickItem *itemFind = findFirstItem(itemId, item);
    if (itemFind != nullptr) {
      return itemFind;
    }
  }
  return nullptr;
}

void CUIBarHandle::onUpdateBarWindow() {
  QDateTime dateTime = QDateTime::currentDateTime();

  //更新顶部日期
  QString barDate = dateTime.toString("yyyy-MM-dd");
  if (m_barDate != barDate) {
    m_barDate = barDate;
    Q_EMIT signalUpdateDate(m_barDate);
  }

  //更新顶部时间
  QString barTime = dateTime.toString("hh:mm:ss");
  if (m_barTime != barTime) {
    m_barTime = barTime;
    Q_EMIT signalUpdateTime(m_barTime);
  }

  //更新顶部星期
  QString barWeek = dateTime.toString("dddd");
  if (m_barWeek != barWeek) {
    m_barWeek = barWeek;
    Q_EMIT signalUpdateWeek(m_barWeek);
  }

  // static int xx = 0;
  // if (++xx == 100)
  //{
  //     SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(DataType::LIGHTSCREEN_DATA);
  //     SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(DataType::BAR_0x18F413EF_DATA);
  //     SingletonCUIDataHandle::getInstance()->canServerPtr()->pushGetCanData(DataType::BAR_NETWORK_DATA);
  // }
}

void CUIBarHandle::onUpdateCanMsg_0x18F413EFToUIBarHandle(quint32 voltage,
                                                          quint32 electricity,
                                                          quint32 soc) {
  setVoltage(QString::number((int32_t)(voltage * 0.1)));
  if (electricity != 0)
  {
    setElectricity(QString::number((int32_t)(electricity * 0.1 - 500)));
  }else
  {
    setElectricity(QString::number((int32_t)(electricity)));
  }
  
  setEnergyPercent(soc * 0.1);
}

void CUIBarHandle::onUpdateCanMsg_0x6FToUIBarHandle(quint32 isCharge) {
  setEnergyIsCharge(isCharge == 1);
}

void CUIBarHandle::onUpdateModermToUIBarHandle(QString csq, QString cops) {
  LOGGER->Cowa_Info(("CUIBarHandle recive Moderm Msg, data:" + csq.toStdString() + cops.toStdString()).c_str());
  if (csq == "'ERR'" || csq == "ERR") {
    LOGGER->Cowa_Warn("ERROR: csq error");
    return;
  }
  if (cops == "'ERR'" || cops == "ERR") {
    LOGGER->Cowa_Warn("ERROR: cops error");
    return;
  }

  QStringList list = csq.split(",");
  if (list.size() != 2) {
    LOGGER->Cowa_Warn("ERROR: csq data error, csq = ");
    return;
  }
  int32_t RSSI = atoi(list[0].toStdString().c_str());
  if ((RSSI < 0 || RSSI > 31) && RSSI != 99) {
    LOGGER->Cowa_Warn("ERROR: csq data error, csq = ");
    return;
  }

  int32_t quality = 0;
  if (RSSI == 99) {
    quality = 99;
  } else {
    int32_t qualityValue = std::min(std::max(4 * RSSI - 26, 0), 100);
    if (qualityValue > 20 && qualityValue <= 40) {
      quality = 1;
    } else if (qualityValue > 40 && qualityValue <= 60) {
      quality = 2;
    } else if (qualityValue > 60 && qualityValue <= 80) {
      quality = 3;
    } else if (qualityValue > 80 && qualityValue <= 100) {
      quality = 4;
    }
  }

  // CHINA MOBILE表示中国移动，其他显示中国电信
  QString cardString =
      cops.indexOf("CHINA MOBILE") != -1 ? "中国移动" : "中国电信";
  LOGGER->Cowa_Info(("Q_EMIT QML  Moderm Msg, data:" + cardString.toStdString() + std::to_string(quality)).c_str());
  Q_EMIT signalUpdateCard(cardString, quality);
  // Q_EMIT signalUpdateCard("中国移动", 3);
}

void CUIBarHandle::setEnergyPercent(qint32 percent) {
  if (percent < 0 || percent > 100) {
    LOGGER->Cowa_Warn("ERROR: energy percent error");
    return;
  }
  Q_EMIT signalUpdateEnergyPercent(percent);
}

void CUIBarHandle::setEnergyIsCharge(bool isCharge) {
  Q_EMIT signalUpdateEnergyIsCharge(isCharge);
}

void CUIBarHandle::setVoltage(const QString &voltage) {
  Q_EMIT signalUpdateVoltage(voltage);
}

void CUIBarHandle::setElectricity(const QString &electricity) {
  Q_EMIT signalUpdateElectricity(electricity);
}