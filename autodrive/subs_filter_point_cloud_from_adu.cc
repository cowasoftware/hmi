#include "subs_filter_point_cloud_from_adu.h"
#include "helper.h"
#include "DataManager.h"
#include "MapConfig.h"

extern MapConfig g_config;
extern double x_min;
extern double y_min;
extern double z_min;

void SubsFilterPointCloudFromAdu::onRecv(Message_Ptr msg)
{
    // std::cout << "time";
    utm_point_cloud::PointCloudDataType new_msg;
    new_msg.ParseFromArray(msg->data(), msg->size());
    //有点云的时候解析一包数据就要4-8ms
    // 点云
    if (new_msg.has_point_cloud_collect())
    {
        std::vector<float> vecCloud;
        utm_point_cloud::PointCloudCollect pointCloudCollect = new_msg.point_cloud_collect();
        int32_t pointCloudSize = pointCloudCollect.point_cloud_size();
        for (int32_t pointCloudIndex = 0; pointCloudIndex < pointCloudSize; ++pointCloudIndex)
        {
            ::utm_point_cloud::PointCloud pointCloud = pointCloudCollect.point_cloud(pointCloudIndex);
            int32_t pointSize = pointCloud.point_size();
            for (int32_t pointIndex = 0; pointIndex < pointSize; ++pointIndex)
            {
                ::utm_point_cloud::PointXYZ point = pointCloud.point(pointIndex);
                float x = point.x() - x_min;
                float y = point.y() - y_min;
                float z = 0.0f;
                if (point.has_z())
                {
                    z = point.z() - z_min;
                }
                vecCloud.push_back(x);
                vecCloud.push_back(y);
                vecCloud.push_back(z);
                //RCSend("%lf, %lf", x, y);
            }
        }
        if (g_config.m_debug)
        {
            printf("cloud point size = %d\n", (int32_t)vecCloud.size());
            if (vecCloud.size() > 5 * 3)
            {
                printf("cloud[12] = %f, 13 = %f, 14 = %f\n", vecCloud[12], vecCloud[13], vecCloud[14]);
            }
            if (vecCloud.size() > 15 * 3)
            {
                printf("cloud[42] = %f, 43 = %f, 44 = %f\n", vecCloud[42], vecCloud[43], vecCloud[44]);
            }
        }
        DataManager::instance().setCloud(vecCloud);
    }

}