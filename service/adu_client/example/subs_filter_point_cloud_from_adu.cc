#include "subs_filter_point_cloud_from_adu.h"
#include "helper.h"



void SubsFilterPointCloudFromAdu::onRecv(Message_Ptr msg)
{
    // std::cout << "time";
    utm_point_cloud::PointCloudDataType new_msg;
    //有点云的时候解析一包数据就要4-8ms
    // std::cout << "ParseFromArray start";
    new_msg.ParseFromArray(msg->data(), msg->size());
    uint32_t sum = 0;
    if(new_msg.has_point_cloud_collect() && new_msg.point_cloud_collect().point_cloud_size())
    {
    
        for( auto& point_cloud_data : new_msg.point_cloud_collect().point_cloud())
        {
            sum += point_cloud_data.point_size();
        }
    }
    std::cout << "filter_point_cloud_size:" << sum << std::endl;

}