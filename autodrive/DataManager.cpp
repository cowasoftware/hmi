#include "DataManager.h"
#include "GlmVec3.h"
#include "Glm.h"
//#include "SendToMessageTest.h"
#include "json/json.h"
#include "Util.h"
#include <math.h>
#include "HdmapData.h"
#include "CloudPoint/CloudPoint.h"

extern double g_trajectoryWidth;
extern double x_min;
extern double y_min;
extern double g_roadHeight;
extern double g_treeWidth;

DataManager::DataManager():
m_heroCarX(0.0),
m_heroCarY(0.0),
m_heroCarTheta(0.0)
{

}

DataManager& DataManager::instance()
{
	static DataManager s_dataManager;
	return s_dataManager;
}

void DataManager::setHeroCarPos(double heroCarX, double heroCarY, double heroCarZ)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_heroCarX = heroCarX;
	m_heroCarY = heroCarY;
    m_heroCarZ = heroCarZ;
}

std::tuple<double, double,double> DataManager::heroCarPos()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return std::tuple<double, double,double>(m_heroCarX, m_heroCarY, m_heroCarZ);
}

void DataManager::setHeroCarTheta(double heroCarTheta)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_heroCarTheta = heroCarTheta;
}

double DataManager::heroCarTheta()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_heroCarTheta;
}

void DataManager::setHeroCarQuaternion(const GlmVec4& quaternion)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_quaternion = quaternion;
}

GlmVec4 DataManager::heroCarQuaternion()
{
    std::lock_guard<std::mutex> lock(m_mutex);
	return m_quaternion;
}

void DataManager::setTimestamp(uint64_t timestamp)
{
    m_currentTimestamp = timestamp;
}

uint64_t DataManager::timestamp()
{
    return m_currentTimestamp;
}

void DataManager::setObstacleMap(const std::map<int32_t, ObstacleFrameInfo>& obstacleMap)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_obstacleMap = obstacleMap;
}

std::map<int32_t, ObstacleFrameInfo> DataManager::obstacleMap()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_obstacleMap;
}

//static std::pair<Point3DGL, Point3DGL> PointToPair(const Point3DGL &point1, const Point3DGL &point2, double lineWidth)
//{
//	GlmVec3 vec3Point1(point1.m_x, point1.m_y, point1.m_z);
//	GlmVec3 vec3Point2(point2.m_x, point2.m_y, point2.m_z);
//
//	GlmVec3 widthVec3 = Glm::normalize(Glm::cross(Glm::minus(vec3Point1, vec3Point2), GlmVec3(0, 0, 1)));
//	widthVec3.scale(lineWidth / 2);
//
//	std::pair<Point3DGL, Point3DGL> result;
//	vec3Point2.add(widthVec3);
//	result.first.m_x = vec3Point2.x();
//	result.first.m_y = vec3Point2.y();
//	result.first.m_z = vec3Point2.z();
//	vec3Point2.minus(widthVec3);
//	vec3Point2.minus(widthVec3);
//	result.second.m_x = vec3Point2.x();
//	result.second.m_y = vec3Point2.y();
//	result.second.m_z = vec3Point2.z();
//
//	return result;
//}

void DataManager::setTrajectoryPoints(const std::vector<Point3DGL>& vecPoint)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (vecPoint.size() < 2)
	{
		m_vecPoint.clear();
		return;
	}

	m_vecPoint = vecPoint;
}

std::vector<Point3DGL> DataManager::trajectoryPoints()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_vecPoint;
}

void DataManager::loadObjectPointList(int32_t plantCount)
{
	m_allPlant.clear();
    
    if (!g_allCloudMap.empty())
    {
        m_allPlant = std::move(g_allCloudMap);
    }
    //RCSend("size = %d,%d,%d", m_allPlant.size(), m_allPlant[1].size(), m_allPlant[2].size());

    //for (auto itCloud = g_cloudInfoMap.begin(); itCloud != g_cloudInfoMap.end(); ++itCloud)
    //{
    //    for (std::size_t index = 0; index < itCloud->second.first; ++index)
    //    {
    //        m_allPlant[itCloud->first].push_back(g_plant_1);
    //        m_allPlant[itCloud->first].push_back(g_plant_2);
    //    }
    //}

	//std::vector<std::string> vecPath = Util::findFilePath(Util::GetCurrentExePath() + "tree");
    //
    //int32_t plantType = 0;
//
    //for (std::size_t pathIndex = 0; pathIndex < vecPath.size(); ++pathIndex)
    //{
    //    const std::string& name = vecPath[pathIndex];
    //    if (name.find("树干") != std::string::npos)
    //    {
    //        plantType = 1;
    //    }
    //    else if (name.find("植被") != std::string::npos)
    //    {
    //        plantType = 2;
    //    }
    //    if (m_allPlant[plantType].size() >= (std::size_t)plantCount)
    //    {
    //        continue;
    //    }
    //    std::string jsonString = Util::readFile(vecPath[pathIndex]);
    //    Json::Reader reader;
    //    Json::Value value;
    //    reader.parse(jsonString, value);
    //    if (value.isArray())
    //    {
    //        double avgx = 0;
    //        double avgy = 0;
    //        std::vector<Point3DGL> vecPoint;
    //        for (std::size_t index = 0; index < value.size(); ++index)
    //        {
    //            vecPoint.push_back(Point3DGL());
    //            Point3DGL& point = vecPoint.back();
    //            point.m_x = value[(int32_t)index][0].asDouble();
    //            point.m_y = value[(int32_t)index][1].asDouble();
    //            point.m_z = value[(int32_t)index][2].asDouble();
    //            avgx = avgx * index / (index + 1) + point.m_x / (index + 1);
    //            avgy = avgy * index / (index + 1) + point.m_y / (index + 1);
    //        }
//
    //        for (std::size_t index = 0; index < vecPoint.size(); ++index)
    //        {
    //            vecPoint[index].m_x -= avgx;
    //            vecPoint[index].m_y -= avgy;
    //        }
//
    //        m_allPlant[plantType].push_back(vecPoint);
    //    }
    //}
}

std::map<int32_t, std::vector<std::vector<Point3DGL>>> DataManager::objectPointList()
{
	return m_allPlant;
}

void DataManager::makeTreePoint(const std::unordered_map<std::string,
	std::pair<COWA::MapData::Road_RoadType, std::vector<Point3DGL>>>& roadMap)
{
    std::vector<std::vector<Point3DGL>> vecRoadPoint;
    for (auto it = roadMap.begin(); it != roadMap.end(); ++it)
	{
        std::vector<Point3DGL> roadPoint;
        Point3DGL firstPoint;
		const std::vector<Point3DGL>& vecRoadPointInfo = it->second.second;
		for (std::size_t index = 0; index < vecRoadPointInfo.size(); ++index)
		{
            Point3DGL point = Point3DGL(vecRoadPointInfo[index].m_x - x_min,
                vecRoadPointInfo[index].m_y - y_min, g_roadHeight);
            if (index == 0)
            {
                firstPoint = point;
            }
            if (index == vecRoadPointInfo.size() - 1 && point.m_x == firstPoint.m_x && point.m_y == firstPoint.m_y)
            {
                break;
            }
			roadPoint.push_back(point);
		}
        if (roadPoint.size() >= 3)
        {
            vecRoadPoint.push_back(roadPoint);
        }
	}

    std::vector<std::vector<Point3DGL>> vecTreePoint;
    for (std::size_t roadIndex = 0; roadIndex < vecRoadPoint.size(); ++roadIndex)
    {
        const std::vector<Point3DGL>& roadPoint = vecRoadPoint[roadIndex];
        std::vector<Point3DGL> vecPairPoint;
        const std::pair<Point3DGL, Point3DGL>& firstPairPoint = PointToPair(roadPoint[1], roadPoint[0], g_treeWidth);
        vecPairPoint.push_back(firstPairPoint.second);
        vecPairPoint.push_back(firstPairPoint.first);
        for (std::size_t pointIndex = 1; pointIndex < roadPoint.size(); ++pointIndex)
        {
            const std::pair<Point3DGL, Point3DGL>& pairPoint = PointToPair(roadPoint[pointIndex - 1],
                roadPoint[pointIndex], g_treeWidth);
            vecPairPoint.push_back(pairPoint.first);
            vecPairPoint.push_back(pairPoint.second);
        }
        vecTreePoint.push_back(vecPairPoint);
    }

    m_vecResultRoadPoint.clear();
    for (std::size_t roadTreeIndex = 0; roadTreeIndex < vecTreePoint.size(); ++roadTreeIndex)
    {
        std::vector<Point3DGL> resultRoadPoint;
        const std::vector<Point3DGL>& roadPairPoint = vecTreePoint[roadTreeIndex];
        for (std::size_t pointTreeIndex = 0; pointTreeIndex < roadPairPoint.size(); ++pointTreeIndex)
        {
            const Point3DGL& pPoint = roadPairPoint[pointTreeIndex];
            
            bool isInRoad = false;
            for (std::size_t roadIndex = 0; roadIndex < vecRoadPoint.size(); ++roadIndex)
            {
                const std::vector<Point3DGL>& roadPoint = vecRoadPoint[roadIndex];
                if (IsPointInBoundary(pPoint, roadPoint))
                {
                    isInRoad = true;
                    break;
                }
            }
            if (!isInRoad)
            {
                resultRoadPoint.push_back(pPoint);
            }
        }
        if (!resultRoadPoint.empty())
        {
            m_vecResultRoadPoint.push_back(resultRoadPoint);
        }
    }
}

std::vector<std::vector<Point3DGL>> DataManager::treePoint()
{
    return m_vecResultRoadPoint;
}

void DataManager::setCloud(const std::vector<float>& vecCloud)
{
    std::lock_guard<std::mutex> lock(m_mutex);
	m_vecCloud = vecCloud;
    //RCSend("cloudsize = %d", vecCloud.size());
}

std::vector<float> DataManager::cloud()
{
    std::lock_guard<std::mutex> lock(m_mutex);
	return m_vecCloud;
}

void DataManager::setMap(const std::set<std::string>& vecLaneId, const std::set<std::string>& vecRoadId,
	const std::set<std::string>& vecCrossroadId, const std::set<std::string>& vecCrosswalkId,
	const std::set<std::string>& vecSignalId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!vecLaneId.empty())
    {
        m_vecLaneId = vecLaneId;
    }
    if (!vecRoadId.empty())
    {
        m_vecRoadId = vecRoadId;
    }
    if (!vecCrossroadId.empty())
    {
        m_vecCrossroadId = vecCrossroadId;
    }
    if (!vecCrosswalkId.empty())
    {
        m_vecCrosswalkId = vecCrosswalkId;
    }
    if (!vecSignalId.empty())
    {
        m_vecSignalId = vecSignalId;
    }
}

void DataManager::map(std::set<std::string>& vecLaneId, std::set<std::string>& vecRoadId,
	std::set<std::string>& vecCrossroadId, std::set<std::string>& vecCrosswalkId,
	std::set<std::string>& vecSignalId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    vecLaneId = m_vecLaneId;
    vecRoadId = m_vecRoadId;
    vecCrossroadId = m_vecCrossroadId;
    vecCrosswalkId = m_vecCrosswalkId;
    vecSignalId = m_vecSignalId;
}