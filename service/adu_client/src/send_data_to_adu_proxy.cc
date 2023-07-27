#include "send_data_to_adu_proxy.h"
#include "create_message_template.h"
#include "helper.h"

std::atomic<unsigned long long> SendDtatToAduProxy::_sequence_id = 0;

SendDtatToAduProxy::SendDtatToAduProxy(const std::string& url)
{
    _client_ptr = TcpClient::start(url);
}
SendDtatToAduProxy::~SendDtatToAduProxy()
{
    if(_client_ptr)
    {
        std::cout << "_client_ptr is delete" << std::endl;
        _client_ptr->stop();
    } 
}

void SendDtatToAduProxy::send_unvaild_request()
{
    request_response::RequestResponseDataType new_msg;
    new_msg.set_sequence_id(_sequence_id++);
    new_msg.set_request_type(MIN_UNVAILD_REQUEST_TYPE);
    if(new_msg.IsInitialized())
    {
        auto send_msg = CreateMessage(new_msg);
        request_response::RequestResponseDataType parsed_msg;
        parsed_msg.ParseFromArray(send_msg->data(), send_msg->size());
        std::cout <<  parsed_msg.DebugString() << std::endl;
        _client_ptr->add_request(send_msg);
    }    
}

void SendDtatToAduProxy::send_camera_channel_name(std::string channel_name)
{
    request_response::RequestResponseDataType new_msg;
    new_msg.set_sequence_id(_sequence_id++);
    new_msg.set_request_type(ENABLE_CAMERA_TYPE);
    new_msg.set_camera_channel_name(channel_name);
    if(new_msg.IsInitialized())
    {
        auto send_msg = CreateMessage(new_msg);
        request_response::RequestResponseDataType parsed_msg;
        parsed_msg.ParseFromArray(send_msg->data(), send_msg->size());
        std::cout <<  parsed_msg.DebugString() << std::endl;
        _client_ptr->add_request(send_msg);
    }      
}



void SendDtatToAduProxy::send_auto_drive(DrivingMode drive_mode)
{
    request_response::RequestResponseDataType new_msg;
    new_msg.set_sequence_id(_sequence_id++);
    new_msg.set_request_type(ENABLE_AUTO_DRIVE_TYPE);
    new_msg.set_auto_drive_mode(drive_mode);
    if(new_msg.IsInitialized())
    {
        auto send_msg = CreateMessage(new_msg);
        request_response::RequestResponseDataType parsed_msg;
        parsed_msg.ParseFromArray(send_msg->data(), send_msg->size());
        std::cout <<  parsed_msg.DebugString() << std::endl;
        _client_ptr->add_request(send_msg);
    }    
}

void SendDtatToAduProxy::send_curve_points_request(const std::vector<Wgs8451Position>& data_source)
{
    request_response::RequestResponseDataType new_msg;
    if(0 == data_source.size())
    {
        std::cout << "data source waypoint is 0" << std::endl;
        return;
    }
    for(const auto& p : data_source)
    {
        auto waypoint = new_msg.add_target_curve_points();
        waypoint->set_x(p.get_longitude());
        waypoint->set_y(p.get_latitude());
    }
    new_msg.set_sequence_id(_sequence_id++);
    new_msg.set_request_type(TARGET_CURVE_TYPE);

    if(new_msg.IsInitialized())
    {
        auto send_msg = CreateMessage(new_msg);
        request_response::RequestResponseDataType parsed_msg;
        parsed_msg.ParseFromArray(send_msg->data(), send_msg->size());
        std::cout <<  parsed_msg.DebugString() << std::endl;
        _client_ptr->add_request(send_msg);
    }
}

void SendDtatToAduProxy::add_listener(RequestType idx,ResponseRecvInterface::Ptr callback)
{
    _client_ptr->add_listener(idx, callback);
}
