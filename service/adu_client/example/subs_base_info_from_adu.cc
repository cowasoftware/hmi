#include "subs_base_info_from_adu.h"
#include "helper.h"



void SubsBaseInfoFromAdu::onRecv(Message_Ptr msg)
{
    hmi::BaseInfoDataType new_msg;
    //有点云的时候解析一包数据就要4-8ms
    // std::cout << "ParseFromArray start";
    new_msg.ParseFromArray(msg->data(), msg->size());

    if(new_msg.has_lane_info())
    {
        std::cout << "crossroad_id_size:" << new_msg.lane_info().crossroad_id_size() << std::endl;
        std::cout << "crosswalk_id_size:" << new_msg.lane_info().crosswalk_id_size()<< std::endl;
        std::cout << "road_id_size:" << new_msg.lane_info().road_id_size() << std::endl;
        std::cout << "signal_id_size:" << new_msg.lane_info().signal_id_size() << std::endl;
        std::cout << "lane_id_size:" << new_msg.lane_info().lane_id_size() << std::endl;
    }
}