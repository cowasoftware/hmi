#pragma once

#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
class Position
{

public:
    Position(const double& longitude = 0.0, const double& latitude = 0.0):_longitude(longitude), _latitude(latitude)
    {

    }
    virtual std::string to_string() const = 0;
    virtual std::string position_to_string() const
    {
        std::stringstream ss;
        ss <<  "longitude=" << std::setprecision(15) << _longitude \
            << ", latitude=" << std::setprecision(15)  << _latitude;
        return ss.str();
    }
    const double& get_longitude() const 
    {
        return _longitude;
    }

    const double& get_latitude() const 
    {
        return _latitude;
    }

private:
    double _longitude;
    double _latitude;
};

class Bd09Position  final : public Position
{

public:
    Bd09Position(const double& longitude = 0.0, const double& latitude = 0.0):Position(longitude, latitude)
    {

    }
    virtual std::string to_string() const override
    { 
        return "Bd09 " + position_to_string();
    }
};
class Gcj02Position  final : public Position
{

public:
    Gcj02Position(const double& longitude = 0.0, const double& latitude = 0.0):Position(longitude, latitude)
    {
        
    }
    virtual std::string to_string() const override
    { 
        return "Gcj02 " + position_to_string();
    }
};

class Wgs84Position  final : public Position
{

public:
    Wgs84Position(const double& longitude = 0.0, const double& latitude = 0.0):Position(longitude, latitude)
    {
        
    }

    virtual std::string to_string() const override
    { 
        return "Wgs84 " + position_to_string();
    }
};

class Wgs8451Position  final : public Position
{

public:
    virtual std::string position_to_string() const override
    {
        std::stringstream ss;
        ss <<  "x_51=" << std::setprecision(15) << get_longitude() \
            << ", y_51=" << std::setprecision(15)  << get_latitude();
        return ss.str();        
    }

    Wgs8451Position(const double& x_51 = 0.0, const double& y_51 = 0.0):Position(x_51, y_51)
    {
        
    }

    virtual std::string to_string() const override
    { 
        return "Wgs8451 " + position_to_string();
    }
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

Gcj02Position bd09_to_gcj02(const Bd09Position& bd09_position);
Bd09Position gcj02_to_bd09(const Gcj02Position& gcj02_position);
Wgs84Position gcj02_to_wgs84(const Gcj02Position& gcj02_position);
Gcj02Position wgs84_to_gcj02(const Wgs84Position& wgs84_position);
Bd09Position wgs84_to_bd09(const Wgs84Position& wgs84_position);
Wgs84Position bd09_to_wgs84(const Bd09Position& bd09_position);
Wgs8451Position wgs84_to_wgs8451(const Wgs84Position& wgs84_position);
Wgs84Position wgs8451_to_wgs84(const Wgs8451Position& wgs8451_position);

const double x_PI = 3.14159265358979323846 * 3000.0 / 180.0;
const double PI = 3.1415926535897932384626;
const double a = 6378245.0;
const double ee = 0.00669342162296594323;
const std::string wgs84_longlat = "EPSG:4326"; //+proj=longlat +datum=WGS84 +no_defs
const std::string wgs84_51 = "EPSG:32651"; //+proj=utm +zone=51 +datum=WGS84 +units=m +no_defs

#ifdef __cplusplus    
}
#endif /* __cplusplus */


