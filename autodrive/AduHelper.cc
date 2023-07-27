#include "AduHelper.h"


void uint32_to_request_status_enum(uint32_t status)
{
    switch (status)
    {
        case request_response::ResponseStatusType_RequestStatusEnum_NO_REQUEST:
            std::cout << "NO_REQUEST" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_SUCC:
            std::cout << "REQUEST_SUCC" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_FAIL:
            std::cout << "REQUEST_FAIL" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_WAIT:
            std::cout << "REQUEST_WAIT" << std::endl;
            break;
        default:
            std::cout << "REQUEST_ERROR" << std::endl;
            break;
    }
}

LightDirection uint32_to_traffic_light_direction_enum(uint32_t direction) {
    LightDirection dir;
    switch(direction) {
        case COWA::NavMsg::TrafficLight2_Direction_FORWARD:
            // std::cout << "FORWARD" << std::endl;
            dir = FORWARD;
            break;
        case COWA::NavMsg::TrafficLight2_Direction_LEFT:
            // std::cout << "LEFT" << std::endl;
            dir = LEFT;
            break;
        case COWA::NavMsg::TrafficLight2_Direction_RIGHT:
            // std::cout << "RIGHT" << std::endl;
            dir = RIGHT;
            break;
        case COWA::NavMsg::TrafficLight2_Direction_UTURN:
            // std::cout << "UTURN" << std::endl;
            dir = UTURN;
            break;
        default:
            std::cout << "NO_DIRECTION" << std::endl;
            dir = NONE;
            break;
    }
    return dir;
}

LightColor uint32_to_traffic_light_state_enum(uint32_t state) {
    LightColor color;
    switch(state) {
        case COWA::NavMsg::TrafficLight2_State_RED:
            // std::cout << "RED" << std::endl;
            color = RED;
            break;
        case COWA::NavMsg::TrafficLight2_State_YELLOW:
            // std::cout << "YELLOW" << std::endl;
            color = YELLOW;
            break;
        case COWA::NavMsg::TrafficLight2_State_GREEN:
            // std::cout << "GREEN" << std::endl;
            color = GREEN;
            break;
        case COWA::NavMsg::TrafficLight2_State_UNKNOWN:
            // std::cout << "UNKNOWN" << std::endl;
            color = UNKNOWN;
            break;
        default:
            // std::cout << "NO_STATE" << std::endl;
            color = UNKNOWN;
            break;
    }
    return color;
}
