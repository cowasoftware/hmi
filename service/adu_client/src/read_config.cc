#include "read_config.h"

ReadConfig::ReadConfig(const std::string&  config_file_path):_config_file_path(config_file_path)
{
    char current_path[1024] = {0};
    if( -1 == ::readlink("/proc/self/exe", current_path, 1024))
    {
        throw "get curren dir is error";
    }
    std::string current_path_string(current_path);
    std::string::size_type iPos = current_path_string .find_last_of('/') + 1;
    std::string current_dir_string = current_path_string .substr(0,iPos);

    _config_file_path =  current_dir_string + _config_file_path;
    std::cout << "config file path: " <<  _config_file_path << std::endl;
    std::ifstream ifs(_config_file_path, std::ios::in);
    if(ifs)
    {
        Json::CharReaderBuilder builder;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, ifs, &_config_value, &errs)) {
            std::cout << "json parse err:" << errs << std::endl;
        }
        else{
            std::cout << "json parse succ" << std::endl;
        }
        _json_parse_state = true;
    }
    else
    {
        std::cout << "config file is not exit" << std::endl;
        _json_parse_state = false;
    }
}

std::string ReadConfig::get_ip_port(const std::string& type) const
{
    std::string ip_port;
    if(_json_parse_state)
    {
        Json::Value config_publish_value = _config_value[type];
        //"tcp://172.28.9.53:9013"
        ip_port =  config_publish_value["protocol_type"].asString() + "://" + config_publish_value["ip"].asString() + \
            ":" + config_publish_value["port"].asString(); 
    }
    return ip_port;
}

std::string ReadConfig::get_server_ip_port() const
{
    std::string server_ip_port= get_ip_port("server");
    if(!server_ip_port.size())
    {
        server_ip_port = DEFAULT_SERVER_IP_PORT;
    }
    std::cout << "server_ip_port:" << server_ip_port << std::endl;
    return server_ip_port;
}

std::string ReadConfig::get_publish_base_info_ip_port() const
{
    std::string base_info_subscirbe_ip_port = get_ip_port("publish_base_info");

    if(!base_info_subscirbe_ip_port.size())
    {
        base_info_subscirbe_ip_port = DEFAULT_PUBLISH_BASE_INFO_IP_PORT;
    }
    std::cout << "base_info_subscirbe_ip_port:" << base_info_subscirbe_ip_port << std::endl;
    return base_info_subscirbe_ip_port;
}

std::string ReadConfig::get_publish_camera_ip_port() const
{
    std::string publish_camera_ip_port= get_ip_port("publish_camera");
    if(!publish_camera_ip_port.size())
    {
        publish_camera_ip_port = DEFAULT_PUBLISH_CAMERA_IP_PORT;
    }
    std::cout << "publish_camera_ip_port:" << publish_camera_ip_port << std::endl;
    return publish_camera_ip_port;
}

std::string ReadConfig::get_publish_filter_point_cloud_ip_port() const
{
    std::string publish_filter_point_cloud_ip_port= get_ip_port("publish_filter_point_cloud");
    if(!publish_filter_point_cloud_ip_port.size())
    {
        publish_filter_point_cloud_ip_port = DEFAULT_PUBLISH_FILTER_POINT_CLOUD_IP_PORT;
    }
    std::cout << "publish_filter_point_cloud:" << publish_filter_point_cloud_ip_port << std::endl;
    return publish_filter_point_cloud_ip_port;
}


int ReadConfig::get_hwm(const std::string& type) const
{
    int hwm  = DEFALUT_PUB_HWM;
    if(_json_parse_state)
    {
        Json::Value config_publish_value = _config_value[type];
        hwm = config_publish_value["hwm"].asInt();
    }
    return hwm;
}

int ReadConfig::get_publish_base_info_hwm() const
{
    int hwm = get_hwm("publish_base_info");
    std::cout << "publish_base_info_ip_hwm:" << hwm << std::endl;
    return hwm;
}

int ReadConfig::get_publish_filter_point_cloud_hwm() const
{
    int hwm = get_hwm("publish_filter_point_cloud");
    std::cout << "publish_filter_point_cloud_hwm:" << hwm << std::endl;
    return hwm;
}

int ReadConfig::get_publish_camera_hwm() const
{
    int hwm = get_hwm("publish_camera");
    std::cout << "publish_camera_hwm:" << hwm << std::endl;
    return hwm;
}