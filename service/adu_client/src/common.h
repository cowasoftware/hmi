#pragma once

#include <iostream>
#include <memory>
#include <zmq.hpp>
#include <thread>
#include <exception>
#include <mutex>
#include <fstream>
#include <list>
#include <unistd.h>
#include <pthread.h>
#include <atomic>


#include "json/json.h"

#include "utm_point_cloud.pb.h"
#include "hmi_base_info.pb.h"
#include "request_response.pb.h"
#include "svbox.pb.h"

#include "chassis.pb.h"


#define  MANUAL_MODE  COWA::NavMsg::VehicleDrive_DrivingMode_MANUAL 
#define  AUTO_DRIVE_MODE  COWA::NavMsg::VehicleDrive_DrivingMode_AUTO_DRIVE 
#define  AUTO_STEER_ONLY_MODE COWA::NavMsg::VehicleDrive_DrivingMode_AUTO_STEER_ONLY 
#define  AUTO_SPEED_ONLY_MODE  COWA::NavMsg::VehicleDrive_DrivingMode_AUTO_SPEED_ONLY 
#define  EMERGENCY COWA::NavMsg::VehicleDrive_DrivingMode_EMERGENCY_MODE 
#define  STANDBY_MODE COWA::NavMsg::VehicleDrive_DrivingMode_STANDBY 
#define  PARKING_MODE  COWA::NavMsg::VehicleDrive_DrivingMode_PARKING 
using DrivingMode = COWA::NavMsg::VehicleDrive_DrivingMode;

using Message_Ptr = std::shared_ptr<zmq::message_t>;

#define DEFAULT_PUBLISH_BASE_INFO_IP_PORT "tcp://192.168.1.2:9014"
#define DEFAULT_PUBLISH_FILTER_POINT_CLOUD_IP_PORT "tcp://192.168.1.2:9015"
#define DEFAULT_PUBLISH_CAMERA_IP_PORT "tcp://192.168.1.2:9016"
#define DEFAULT_SERVER_IP_PORT "tcp://192.168.1.2:9017"
#define DEFAULT_PUBLISH_ORIGIN_POINT_CLOUD_IP_PORT "tcp://0.0.0.0:9018"
#define DEFALUT_PUB_HWM 1000


#define DEFAULLT_CONFIG_FILE_PATH "./hmi_client_config.json"

#define MIN_UNVAILD_REQUEST_TYPE     request_response::RequestResponseDataType_RequestType_MIN_UNVAILD_TYPE
#define TARGET_CURVE_TYPE        request_response::RequestResponseDataType_RequestType_TARGET_CURVE_TYPE 
#define ENABLE_AUTO_DRIVE_TYPE   request_response::RequestResponseDataType_RequestType_ENABLE_AUTO_DRIVE_TYPE
#define ENABLE_CAMERA_TYPE   request_response::RequestResponseDataType_RequestType_ENABLE_CAMERA_TYPE 
#define MAX_REQUEST_TYPE     (request_response::RequestResponseDataType_RequestType_MAX_UNVAILD_TYPE-1)

using RequestType = request_response::RequestResponseDataType::RequestType;    
