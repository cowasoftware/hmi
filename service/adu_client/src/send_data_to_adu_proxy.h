#pragma once

#include "common.h"
#include "client.h"
#include "coordinate_convert.h"



class SendDtatToAduProxy
{
public:
    SendDtatToAduProxy()=delete;
    ~SendDtatToAduProxy();
    SendDtatToAduProxy(const std::string& url);
    void send_curve_points_request(const std::vector<Wgs8451Position>& data_source);
    void send_auto_drive(DrivingMode drive_mode);
    void send_camera_channel_name(std::string channel_name);
    void add_listener(RequestType idx, ResponseRecvInterface::Ptr callback);
    void send_unvaild_request();
private:
    std::shared_ptr<TcpClient> _client_ptr;
    static std::atomic<unsigned long long> _sequence_id;
};