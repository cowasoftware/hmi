#include "recv_curve_points_from_adu.h"
#include "helper.h"

void RecvCurvePointsFromAdu::onRecv(request_response::RequestResponseDataType& reponse_proto)
{

    auto request_status = reponse_proto.response_status().reponse_status_code();
    uint32_to_request_status_enum(request_status);
    std::cout <<  reponse_proto.response_status().reponse_status_msg() << std::endl;;
    if(request_status == request_response::ResponseStatusType_RequestStatusEnum_REQUEST_SUCC && \
        reponse_proto.target_curve_points_size())
    {
        std::cout << "target curve points size:" << reponse_proto.target_curve_points_size()  << std::endl;
    }
}