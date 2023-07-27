#pragma once
#include "common.h"

class ReadConfig
{
public:
    ReadConfig()=delete;
    ReadConfig(const std::string&  config_file_path);
    std::string get_publish_base_info_ip_port() const;
    std::string get_publish_camera_ip_port() const;
    std::string get_publish_filter_point_cloud_ip_port() const;
    std::string get_server_ip_port() const;

    int get_publish_base_info_hwm() const;
    int get_publish_camera_hwm() const;
    int get_publish_filter_point_cloud_hwm() const;

private:
    std::string get_ip_port(const std::string& type) const;
    int get_hwm(const std::string& type) const;
    std::string _config_file_path;
    Json::Value _config_value;
    bool _json_parse_state;
};