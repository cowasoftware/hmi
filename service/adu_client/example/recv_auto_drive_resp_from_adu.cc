#include "recv_auto_drive_resp_from_adu.h"
#include "helper.h"

void RecvAutoDriveRespFromAdu::onRecv(request_response::RequestResponseDataType& reponse_proto)
{

    auto request_status = reponse_proto.response_status().reponse_status_code();
    uint32_to_request_status_enum(request_status);
    std::cout <<  reponse_proto.response_status().reponse_status_msg() << std::endl;
}