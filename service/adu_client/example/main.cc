#include "context.h"
#include "recv_curve_points_from_adu.h"
#include "recv_auto_drive_resp_from_adu.h"
#include "recv_camera_resp_from_adu.h"
#include "subs_base_info_from_adu.h"
#include "subs_filter_point_cloud_from_adu.h"
#include "subs_camera_from_adu.h"
#include "coordinate_convert.h"
#include "helper.h"


class RequestRoutingHelper{

public:
    RequestRoutingHelper()=delete;
    RequestRoutingHelper( Context& context, std::vector<Wgs8451Position>& convert_test_dest_point): \
        _context(context), _convert_test_dest_point(convert_test_dest_point)
    {

    }

    void requese_auto_drive()
    {
        _context.send_auto_drive(MANUAL_MODE);
        std::thread([this]{
            _context.send_auto_drive(STANDBY_MODE);
        }).detach();    

        sleep(0.1);

        std::thread([this]{
            _context.send_auto_drive(AUTO_DRIVE_MODE);
        }).detach(); 
    }

void request_camera_channel_name()
    {
        _context.send_camera_channel_name("/camera/panorama/2/h264");

        sleep(5);

        _context.send_camera_channel_name("/camera/panorama/3/h264");

        sleep(5);

        _context.send_camera_channel_name("");

        sleep(5);

        _context.send_camera_channel_name("/camera/panorama/3/h264");

        sleep(5);

        _context.send_camera_channel_name("/camera/surround/back/h264");

        // std::thread([this]{
        //     _context.send_camera_channel_name("/camera/panorama/3/h264 ");
        // }).detach();

        // sleep(0.1);

        // std::thread([this]{
        //     _context.send_camera_channel_name("/camera/surround/back/h264 ");
        // }).detach();

    }


    void request_vaild_type()
    {
        _context.send_unvaild_request();

        std::thread([this]{
            _context.send_unvaild_request();
        }).detach();

        sleep(0.1);

        std::thread([this]{
            _context.send_unvaild_request();
        }).detach();
    }

    void request_routing(unsigned int start, unsigned int end)
    {
        if(start >= _convert_test_dest_point.size() ||
           end > _convert_test_dest_point.size()    || 
           end <= start )
            {
                std::cout << "convert test dest point num is " << _convert_test_dest_point.size() << std::endl; 
                std::cout << "start:" << start << " end:" << end << " is error" << std::endl; 
            }
        std::vector<Wgs8451Position> send_point(_convert_test_dest_point.begin()+ start, _convert_test_dest_point.begin()+ end);
        _context.send_curve_points_request(send_point);

        std::thread(
            [&,send_point](){
                _context.send_curve_points_request(send_point);

            }
        ).detach();

        sleep(0.1);

        std::thread(
            [&,send_point](){
                _context.send_curve_points_request(send_point);
            }
        ).detach();

    }

private:
    Context& _context;
    std::vector<Wgs8451Position>& _convert_test_dest_point;
};



std::vector<Wgs8451Position>  test_dest_point_coordinate_convert(std::vector<Bd09Position>& test_dest_point)
{
    std::vector<Wgs8451Position> convert_test_dest_point;
    for(const auto& bd09 : test_dest_point)
    {
        std::cout << bd09.to_string() << std::endl;
        auto wgs84 = bd09_to_wgs84(bd09);
        auto wgs8451 = wgs84_to_wgs8451(wgs84);
        std::cout << wgs8451.to_string() << std::endl;
        convert_test_dest_point.push_back(wgs8451);
    }
    return convert_test_dest_point;
}

int main()
{

    // int major, minor, patch;
    // zmq_version (&major, &minor, &patch);
    // printf ("当前ZMQ版本号为 %d.%d.%d\n", major, minor, patch);

    std::vector<Bd09Position> test_dest_point{
        {121.44350911905663,31.194924554709814},
        {121.44089823836904,31.192936920716445},
    };
    auto convert_test_dest_point = test_dest_point_coordinate_convert(test_dest_point);

    // std::vector<Wgs8451Position> convert_test_dest_point{
    //         {350646.17330579471,3451767.0548205273},
    //         {350393.72007097094,3451551.2246910823},
    //     };


    Context context;
    auto recv_base_info_from_adu = std::make_shared<SubsBaseInfoFromAdu>();
    context.add_base_info_subs_listener(recv_base_info_from_adu);

    auto recv_filter_point_cloud_from_adu = std::make_shared<SubsFilterPointCloudFromAdu>();
    context.add_filter_point_cloud_subs_listener(recv_filter_point_cloud_from_adu);
    

    auto recv_camera_from_adu = std::make_shared<SubsCameraFromAdu>();
    context.add_camera_subs_listener(recv_camera_from_adu);


    auto recv_curve_points_from_adu = std::make_shared<RecvCurvePointsFromAdu>();
    context.add_response_listener(TARGET_CURVE_TYPE, recv_curve_points_from_adu);
    
    auto recv_auto_drive_resp_from_adu = std::make_shared<RecvAutoDriveRespFromAdu>();
    context.add_response_listener(ENABLE_AUTO_DRIVE_TYPE, recv_auto_drive_resp_from_adu);

    auto recv_camera_resp_from_adu = std::make_shared<RecvCameraRespFromAdu>();
    context.add_response_listener(ENABLE_CAMERA_TYPE, recv_camera_resp_from_adu);

    RequestRoutingHelper request_routing_helper(context,convert_test_dest_point);
    for(unsigned int end = 1; end <= convert_test_dest_point.size(); end++)
    {
        sleep(1);
        request_routing_helper.request_routing(0, end);
    }
    request_routing_helper.request_camera_channel_name();
    // sleep(2);

    while(true)
    {
        sleep(1);
    }
}