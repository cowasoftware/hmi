#pragma once

#include <iostream>
#include "common.h"

enum LightColor {
    UNKNOWN = 0,
    RED = 1,
    YELLOW = 2,
    GREEN = 3
};

enum LightDirection {
    FORWARD = 1,
    LEFT = 2,
    RIGHT = 3,
    UTURN = 4,
    NONE = 5
};

class ParseRequestHelper
{
public:
    ParseRequestHelper()=delete;
    ~ParseRequestHelper();

private:
    /* data */

};

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


void uint32_to_request_status_enum(uint32_t status);

LightDirection uint32_to_traffic_light_direction_enum(uint32_t direction);

LightColor uint32_to_traffic_light_state_enum(uint32_t state);

#ifdef __cplusplus
}
#endif
