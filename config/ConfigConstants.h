#pragma once

// config constants
#define INDEX "index"
#define MILEAGE "mileage"
#define MEDIA_VOLUME "mediaVolume"
#define NOTIFICATION_VOLUME "notificationVolume"
#define VERHICLE_VOLUME "verhicleVolume"
#define BRIGHTNESS "brightness"
#define DEBUG_ENABLE "enable_debug"
// #define HMI_BUILD_VERSION "HMI_BUILD_VERSION"

// reverse image
// #define REVERSE_IMAGE_URL "tcp://172.31.10.124:40000"
#define REVERSE_IMAGE_URL "tcp://192.168.1.2:40000"
#define REVERSE_IMAGE_TOPIC "VehicleReverse_H264Data"
#define IMAGE_FRAME_ENCODE_H264 "H264"
#define IMAGE_FRAME_ENCODE_JPEG "JPEG"

// leveldb file id
#define FILE_ID 0
#define LOGIN_INFO_KEY "login_info"

// hmi server url
#define HMI_REMOTE_BASE_URL "http://hmi.cowarobot.work/api"
#define GET_SERVER_TIME_URL "/v1/time"
#define LOGOUT_QR_URL "/v1/logout/qr"
#define LOGOUT_PARAM_VEHICLE "vehicle"
#define LOGOUT_PARAM_OPEN_ID "open_id"

// vehicle server url
#define VEHICLE_SERVER_URL "https://iot.cowarobot.com/server/auth/check/token"
#define REQUEST_METHOD_GET "get"
#define REQUEST_METHOD_POST "post"
#define REQUEST_HEADERS_CONTENT_TYPE_JSON "application/json"
#define REQUEST_HEADERS_CONTENT_TYPE_FORM "application/x-www-form-urlencoded"
#define REQUEST_DATA "token"

// login info
#define LOGIN_USERNAME "user_name"
#define LOGIN_VEHICLE_ID "vehicle_id"
#define LOGIN_OPEN_ID "open_id"
#define LOGIN_STATUS "login_status"
#define LOGIN_DATATIME "login_datetime"

// login status
#define STATUS_ONLINE "online"
#define STATUS_OFFLINE "offline"

// redis server
#define REDIS_SERVER_IP "192.168.1.1"
#define REDIS_SERVER_PORT 6379
// #define REDIS_SERVER_IP "127.0.0.1"

// 主车位置更新阈值
#define DISTANCE_THRESHOLD 1
//地球半径
#define EARTH_RADIUS 6378137 
