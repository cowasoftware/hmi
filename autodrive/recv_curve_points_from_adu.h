#pragma once

#include "common.h"
#include "recv_interface.h"
#include "context.h"
#include <QObject>
#include "AduHelper.h"


class RecvNotifier : public QObject {
  Q_OBJECT

  Q_SIGNALS:
    void notify_path_unreachable();
    void notify_curve_paths(std::vector<std::pair<double, double>> curve_paths);
    void notify_curve_paths(QList<QList<double>> curve_paths);
};



class RecvCurvePointsFromAdu : public ResponseRecvInterface {
 public: 
  RecvCurvePointsFromAdu();
  virtual void onRecv(request_response::RequestResponseDataType& reponse_proto) override;
  private:
    RecvNotifier notifier;
};