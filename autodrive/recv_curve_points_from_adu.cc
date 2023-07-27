#include "recv_curve_points_from_adu.h"
#include "AduProxy.h"
// #include "helper.h"
#include "AduHelper.h"

RecvCurvePointsFromAdu::RecvCurvePointsFromAdu() {
    qRegisterMetaType<std::vector<std::pair<double, double>>>("std::vector<std::pair<double, double>>");
    QObject::connect(&notifier, SIGNAL(notify_curve_paths(std::vector<std::pair<double, double>>)), SingletonCAduProxy::getInstance(), SLOT(target_curve_paths(std::vector<std::pair<double, double>>)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_path_unreachable()), SingletonCAduProxy::getInstance(), SLOT(handle_path_unreachable()), Qt::QueuedConnection);
}


void RecvCurvePointsFromAdu::onRecv(request_response::RequestResponseDataType& reponse_proto)
{
    
    auto request_status = reponse_proto.response_status().reponse_status_code();
    uint32_to_request_status_enum(request_status);
    if(request_status == request_response::ResponseStatusType_RequestStatusEnum_REQUEST_FAIL) {
        Q_EMIT notifier.notify_path_unreachable();
    }
    std::cout <<  reponse_proto.response_status().reponse_status_msg() << std::endl;;
    if(request_status == request_response::ResponseStatusType_RequestStatusEnum_REQUEST_SUCC && \
        reponse_proto.target_curve_points_size())
    {
        std::cout << "target curve points size:" << reponse_proto.target_curve_points_size()  << std::endl;
        // 解析行驶路线
        std::vector<std::pair<double, double>> curve_path_vect;
        // QList<QList<double>> pathList;
        for(const auto& point :  reponse_proto.target_curve_points())
        {
             std::pair<double, double> points = std::make_pair(point.x(), point.y());
             curve_path_vect.push_back(points);
            //  pathList.append({point.x(), point.y()});
        }
        // adu_service->target_curve_paths(curve_path_vect);
        Q_EMIT notifier.notify_curve_paths(curve_path_vect);
    }
}