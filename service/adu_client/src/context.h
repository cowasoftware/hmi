#pragma once

#include "common.h"
#include "subscriber.h"
#include "read_config.h"
#include "send_data_to_adu_proxy.h"




class Context
{
public:
    ~Context();
    Context(const std::string& config_file_path = DEFAULLT_CONFIG_FILE_PATH);
    void send_curve_points_request(const std::vector<Wgs8451Position>&  data_source);
    void add_base_info_subs_listener(SubsRecvInterface::Ptr callback);
    void add_filter_point_cloud_subs_listener(SubsRecvInterface::Ptr callback);
     void add_camera_subs_listener(SubsRecvInterface::Ptr callback);
    void send_auto_drive(DrivingMode drive_mode);
    void send_camera_channel_name(std::string channel_name);
    void send_unvaild_request();
    void add_response_listener(RequestType idx,ResponseRecvInterface::Ptr callback);
private:
    ReadConfig _read_config;
    Subscriber::Ptr _base_info_subscriber;
    Subscriber::Ptr _filter_point_cloud_subscriber;
    Subscriber::Ptr _camera_subscriber;
    SendDtatToAduProxy _send_data_proxy;
};

