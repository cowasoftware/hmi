#include "context.h"

Context::Context(const std::string& config_file_path):_read_config(config_file_path), 
    _send_data_proxy(_read_config.get_server_ip_port())
{
    _base_info_subscriber = Subscriber::start(_read_config.get_publish_base_info_ip_port(), 
                                              _read_config.get_publish_base_info_hwm(),
                                              "_base_info_subs");
    _filter_point_cloud_subscriber = Subscriber::start(_read_config.get_publish_filter_point_cloud_ip_port(),
                                                       _read_config.get_publish_filter_point_cloud_hwm(),  
                                                        "_filter_subs");

    _camera_subscriber = Subscriber::start(_read_config.get_publish_camera_ip_port(),
                                                       _read_config.get_publish_camera_hwm(),  
                                                        "_camera");                                                    
}
Context::~Context()
{
    if(_base_info_subscriber)
    {
        std::cout << "_base_info_subscriber is delete" << std::endl;
        _base_info_subscriber->stop();
    }
    if(_filter_point_cloud_subscriber)
    {
        std::cout << "_filter_point_cloud_subscriber is delete" << std::endl;
        _filter_point_cloud_subscriber->stop();
    }
    if(_camera_subscriber)
    {
        std::cout << "_camera_subscriber is delete" << std::endl;
        _camera_subscriber->stop();
    }
}


void Context::send_unvaild_request()
{
    _send_data_proxy.send_unvaild_request();
}


void Context::send_auto_drive(DrivingMode drive_mode)
{
    _send_data_proxy.send_auto_drive(drive_mode);
}

void Context::send_camera_channel_name(std::string channel_name)
{
    _send_data_proxy.send_camera_channel_name(channel_name);
}



void Context::send_curve_points_request(const std::vector<Wgs8451Position>&  data_source)
{
    _send_data_proxy.send_curve_points_request(data_source);
}

void Context::add_base_info_subs_listener(SubsRecvInterface::Ptr callback)
{
    _base_info_subscriber->add_listener(callback);
}

void Context::add_filter_point_cloud_subs_listener(SubsRecvInterface::Ptr callback)
{
    _filter_point_cloud_subscriber->add_listener(callback);
}

void Context::add_camera_subs_listener(SubsRecvInterface::Ptr callback)
{
    _camera_subscriber->add_listener(callback);
}


void Context::add_response_listener(RequestType idx,ResponseRecvInterface::Ptr callback)
{
    _send_data_proxy.add_listener(idx, callback);
}