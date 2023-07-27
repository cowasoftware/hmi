#include "../src/coordinate_convert.h"


int main()
{


    Bd09Position bd09{121.41, 31.178};
    std::cout << bd09.to_string() << std::endl;
    auto wgs84 = bd09_to_wgs84(bd09);
    std::cout << wgs84.to_string() << std::endl;
    auto wgs8451 = wgs84_to_wgs8451(wgs84);
    std::cout << wgs8451.to_string() << std::endl;

    // Wgs8451Position w8451(347968.32 , 3450057.50);
    // std::cout <<  w8451.to_string() << std::endl;

    // Wgs84Position w84= wgs8451_to_wgs84(w8451);
    // std::cout <<  w84.to_string() << std::endl;

    // // Wgs8451Position w84_2= wgs84_to_wgs8451(w84);
    // // std::cout <<  w84_2.to_string() << std::endl;

    // Bd09Position bd09 = wgs84_to_bd09(w84);
    // std::cout << bd09.to_string() << std::endl;
    // Gcj02Position gcj02 = bd09_to_gcj02(bd09);
    // std::cout << gcj02.to_string() << std::endl;

    // Bd09Position bd09_back = gcj02_to_bd09(gcj02);
    // std::cout << bd09_back.to_string() << std::endl;
    // Wgs84Position wgs84_back = bd09_to_wgs84(bd09_back);
    // std::cout << wgs84_back.to_string() << std::endl;
    // Wgs8451Position wgs8451_back = wgs84_to_wgs8451(wgs84_back);
    // std::cout << wgs8451_back.to_string() << std::endl;
}

