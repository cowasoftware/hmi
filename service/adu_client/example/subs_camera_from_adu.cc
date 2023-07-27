#include "subs_camera_from_adu.h"
#include "helper.h"



void SubsCameraFromAdu::onRecv(Message_Ptr msg)
{
    svbox::ImageFrame new_msg;
    //有点云的时候解析一包数据就要4-8ms
    new_msg.ParseFromArray(msg->data(), msg->size());
    std::cout << "recv camera" << std::endl;

}