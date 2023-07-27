#pragma once
#include <mutex>
#include "InfoParam.h"
#include <map>
#include "GlParam.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <atomic>
#include <set>
#include "GlmVec4.h"
#include "hdmap.pb.h"

/** 数据管理类
*/
class DataManager
{
protected:
	/** 构造函数
	*/
	DataManager();

public:
	/** 单一实例
	@return 返回单一实例
	*/
	static DataManager& instance();

	/** 设置主车位置
	*/
	void setHeroCarPos(double heroCarX, double heroCarY, double heroCarZ);

	/** 获取主车位置
	@return 返回主车位置
	*/
	std::tuple<double, double, double> heroCarPos();

	/** 设置主车偏航角
	@param [in] heroCarTheta 主车偏航角
	*/
	void setHeroCarTheta(double heroCarTheta);

	/** 获取主车偏航角
	@return 返回主车偏航角
	*/
	double heroCarTheta();

	/** 设置主车四元数
	@param [in] quaternion 四元数
	*/
	void setHeroCarQuaternion(const GlmVec4& quaternion);

	/** 获取主车四元数
	@return 返回主车四元数
	*/
	GlmVec4 heroCarQuaternion();

	/** 设置时间戳
	@param [in] timestamp 时间戳
	*/
	void setTimestamp(uint64_t timestamp);

	/** 获取时间戳
	@return 返回事件戳
	*/
	uint64_t timestamp();

	/** 设置障碍物信息
	@param [in] obstacleMap 障碍物信息
	*/
	void setObstacleMap(const std::map<int32_t, ObstacleFrameInfo>& obstacleMap);

	/** 获取障碍物信息
	@return 返回障碍物信息
	*/
	std::map<int32_t, ObstacleFrameInfo> obstacleMap();

	/** 设置预测轨迹
	@param [in] vecPoint 预测轨迹
	*/
	void setTrajectoryPoints(const std::vector<Point3DGL>& vecPoint);

	/** 获取预测轨迹
	@return 返回预测轨迹
	*/
	std::vector<Point3DGL> trajectoryPoints();

	/** 加载点云
	@param [in] plantCount 同种类加载个数
	*/
	void loadObjectPointList(int32_t plantCount);

	/** 获取点云
	@return 返回点云，1表示树干，2表示植被
	*/
	std::map<int32_t, std::vector<std::vector<Point3DGL>>> objectPointList();

	/** 生成树木所在位置
	@param [in] roadMap 路面数据
	*/
	void makeTreePoint(const std::unordered_map<std::string,
		std::pair<COWA::MapData::Road_RoadType, std::vector<Point3DGL>>>& roadMap);

	/** 获取树木位置
	@return 返回树木位置
	*/
	std::vector<std::vector<Point3DGL>> treePoint();

	/** 设置真实点云
	@param [in] vecCloud 真实点云
	*/
	void setCloud(const std::vector<float>& vecCloud);

	/** 获取真实点云
	@return 返回真实点云
	*/
	std::vector<float> cloud();

	/** 设置主车附近的地图
	@param [in] vecLaneId 车道ID
	@param [in] vecRoadId 路面ID
	@param [in] vecCrossroadId 路口ID
	@param [in] vecCrosswalkId 人行道ID
	@param [in] vecSignalId 红绿灯ID
	*/
	void setMap(const std::set<std::string>& vecLaneId, const std::set<std::string>& vecRoadId,
		const std::set<std::string>& vecCrossroadId, const std::set<std::string>& vecCrosswalkId,
		const std::set<std::string>& vecSignalId);

	/** 获取主车附近的地图
	@param [out] vecLaneId 车道ID
	@param [out] vecRoadId 路面ID
	@param [out] vecCrossroadId 路口ID
	@param [out] vecCrosswalkId 人行道ID
	@param [out] vecSignalId 红绿灯ID
	*/
	void map(std::set<std::string>& vecLaneId, std::set<std::string>& vecRoadId,
		std::set<std::string>& vecCrossroadId, std::set<std::string>& vecCrosswalkId,
		std::set<std::string>& vecSignalId);

public:
	std::mutex m_mutex;
	double m_heroCarX;
    double m_heroCarY;
	double m_heroCarZ;
	double m_heroCarTheta;
	GlmVec4 m_quaternion;
	std::map<int32_t, ObstacleFrameInfo> m_obstacleMap;
	std::vector<Point3DGL> m_vecPoint;
	std::map<int32_t, std::vector<std::vector<Point3DGL>>> m_allPlant;
	std::vector<std::vector<Point3DGL>> m_vecResultRoadPoint;
	std::atomic<uint64_t> m_currentTimestamp;
	std::vector<float> m_vecCloud;
	std::set<std::string> m_vecLaneId;
	std::set<std::string> m_vecRoadId;
	std::set<std::string> m_vecCrossroadId;
	std::set<std::string> m_vecCrosswalkId;
	std::set<std::string> m_vecSignalId;
};