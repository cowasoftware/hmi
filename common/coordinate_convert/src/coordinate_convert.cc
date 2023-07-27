#include "coordinate_convert.h"
#include <proj.h>

double translate_lon(double lon, double lat)
{
    double ret = 300.0 + lon +2.0*lat + 0.1*lon*lon +0.1*lon*lat + 0.1*sqrt(abs(lon));
    ret += (20.0 * sin(6.0*lon*PI) + 20.0*sin(2.0*lon*PI)) *2.0 / 3.0;
    ret += (20.0 * sin(lon*PI) + 40.0*sin(lon/3.0 *PI)) *2.0 /3.0;
    ret += (150 * sin(lon/12.0 *PI) + 300.0*sin(lon/30.0 * PI)) *2.0 /3.0;
    return ret;
}
double translate_lat(double lon, double lat)
{
    double ret = -100 + 2.0*lon + 3.0*lat + 0.2*lat*lat + 0.1*lon*lat + 0.2*sqrt((abs(lon)));
    ret += (20.0 *sin(6.0*lon*PI) + 20*sin(2.0*lon*PI)) *2.0 /3.0;
    ret += (20.0 *sin(lat*PI) + 40.0*sin(lat/3.0*PI)) *2.0 /3.0;
    ret += (160.0*sin(lat/12.0*PI) + 320.0*sin(lat/30.0 *PI)) *2.0 /3.0;
    return ret;
}

bool outof_China(double lon, double lat)
{
    return (lon<72.004 || lon>137.8374 || lat<0.8293 || lat >55.8271 || false);
} 

Gcj02Position bd09_to_gcj02(const Bd09Position& bd09_position)
{
    double x = bd09_position.get_longitude() - 0.0065;
    double y = bd09_position.get_latitude() - 0.006;
    double z = sqrt(x*x + y*y) - 0.00002*sin(y*x_PI);
    double theta = atan2(y,x) - 0.000003*cos(x*x_PI);
    
    return {z*cos(theta), z*sin(theta)};
}
Bd09Position gcj02_to_bd09(const Gcj02Position& gcj02_position)
{
    double z = sqrt(gcj02_position.get_longitude()*gcj02_position.get_longitude() + gcj02_position.get_latitude()*gcj02_position.get_latitude()) + 0.00002*sin(gcj02_position.get_latitude() * x_PI);
    double theta = atan2(gcj02_position.get_latitude(),gcj02_position.get_longitude()) + 0.000003 * cos(gcj02_position.get_longitude() * x_PI);
    return {z*cos(theta) + 0.0065, z*sin(theta) + 0.006};
}

Wgs84Position gcj02_to_wgs84(const Gcj02Position& gcj02_position)
{
    if(outof_China(gcj02_position.get_longitude(),gcj02_position.get_latitude()))
    {
        return {gcj02_position.get_longitude(), gcj02_position.get_latitude()};
    }
    else
    {
        double dlat = translate_lat(gcj02_position.get_longitude() - 105.0,gcj02_position.get_latitude() -35.0);
        double dlon = translate_lon(gcj02_position.get_longitude() - 105.0,gcj02_position.get_latitude() -35.0);
        double radlat = gcj02_position.get_latitude()/180.0 *PI;
        double magic = sin(radlat);
        magic = 1 - ee*magic*magic;
        double squrtmagic = sqrt(magic);
        dlon = (dlon *180.0)/(a/squrtmagic*cos(radlat)*PI);
        dlat = (dlat *180.0)/((a*(1-ee))/(magic * squrtmagic)*PI);
        return {gcj02_position.get_longitude() - dlon, gcj02_position.get_latitude() - dlat};
    }
}
Gcj02Position wgs84_to_gcj02(const Wgs84Position& wgs84_position)
{
    //POSITION gcj_pos;
    if(outof_China(wgs84_position.get_longitude(),wgs84_position.get_latitude()))
    {
        return { wgs84_position.get_longitude(), wgs84_position.get_latitude()};
    }
    else
    {
        double dlat = translate_lat(wgs84_position.get_longitude() - 105.0,wgs84_position.get_latitude() - 35.0);
        double dlon = translate_lon(wgs84_position.get_longitude() - 105.0,wgs84_position.get_latitude() - 35.0);
        double radlat = wgs84_position.get_latitude()/180.0 * PI;
        double magic = sin(radlat);
        magic = 1 - ee*magic*magic;
        double squrtmagic = sqrt(magic);
        dlon = (dlon *180.0)/(a/squrtmagic*cos(radlat)*PI);
        dlat = (dlat *180.0)/((a*(1-ee))/(magic * squrtmagic)*PI);
        return { wgs84_position.get_longitude() + dlon, wgs84_position.get_latitude() +dlat};
    }
}

Bd09Position wgs84_to_bd09(const Wgs84Position& wgs84_position)
{
    Bd09Position bd_position;
    Gcj02Position gcj_position;
    gcj_position = wgs84_to_gcj02(wgs84_position);
    bd_position = gcj02_to_bd09(gcj_position);
    return bd_position;
}
Wgs84Position bd09_to_wgs84(const Bd09Position& bd09_position)
{
    Wgs84Position wgs_position;
    Gcj02Position gcj_position;
    gcj_position = bd09_to_gcj02(bd09_position);
    wgs_position = gcj02_to_wgs84(gcj_position);
    return wgs_position;

}

Wgs8451Position wgs84_to_wgs8451(const Wgs84Position& wgs84_position)
{
    PJ_CONTEXT *context;
    PJ *P;
    PJ *norm;
    PJ_COORD transforing_coord, transfored_coord;

    context = proj_context_create();
    P = proj_create_crs_to_crs (context,
                                wgs84_longlat.c_str(),
                                wgs84_51.c_str(), /* or EPSG:32632 */
                                NULL);
    if (0 == P) {
        std::cout << "Failed to create transformation object." << std::endl;
        return {0, 0};
    }

    norm = proj_normalize_for_visualization(context, P);
    if (0 == norm) {
        std::cout << "Failed to normalize transformation object."<< std::endl;
        return 1;
    }
    proj_destroy(P);
    P = norm;
    transforing_coord = proj_coord(wgs84_position.get_longitude(), wgs84_position.get_latitude(), 0, 0);
    transfored_coord = proj_trans(P, PJ_FWD, transforing_coord);
    proj_destroy(P);
    proj_context_destroy(context);
    return {transfored_coord.enu.e, transfored_coord.enu.n};
}
Wgs84Position wgs8451_to_wgs84(const Wgs8451Position& wgs8451_position)
{
    PJ_CONTEXT *context;
    PJ *P;
    PJ *norm;
    PJ_COORD transforing_coord, transfored_coord;

    context = proj_context_create();
    P = proj_create_crs_to_crs (context,
                                wgs84_51.c_str(), 
                                wgs84_longlat.c_str(),
                                NULL);
    if (0 == P) {
        std::cout << "Failed to create transformation object." << std::endl;
        return {0, 0};
    }

    norm = proj_normalize_for_visualization(context, P);
    if (0 == norm) {
        std::cout << "Failed to normalize transformation object." << std::endl;
        return 1;
    }
    proj_destroy(P);
    P = norm;
    //这一步不确定有没有问题
    transforing_coord = proj_coord(wgs8451_position.get_longitude(), wgs8451_position.get_latitude(), 0, 0);
    transfored_coord = proj_trans(P, PJ_FWD, transforing_coord);
    proj_destroy(P);
    proj_context_destroy(context);
    return {transfored_coord.lp.lam, transfored_coord.lp.phi};
}