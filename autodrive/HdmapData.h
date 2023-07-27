#pragma once
#include "hdmap.pb.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "GlParam.h"
#include "GlmVec3.h"

struct LaneInfo
{
	//道路类型
	COWA::MapData::Lane_LaneType m_type;
	//道路中左车道id集合
	std::vector<std::string> m_leftLane;
	//道路中右车道id集合
	std::vector<std::string> m_rightLane;
};

struct CurvePointInfo
{
	//点类型
	COWA::MapData::LanePoint_Type m_type;
	//点坐标
	Point3DGL m_point;
};

extern int32_t g_major;
extern int32_t g_minor;
extern bool g_isES;

extern double x_min;
extern double x_max;
extern double y_min;
extern double y_max;
extern double z_min;
extern double z_max;

extern double g_lineHeight;
extern double g_roadHeight;
extern double g_groundHeight;
extern double g_waveHeight;
extern double g_trajectoryHeight;

extern double g_groundMargin;
extern double g_lineWidth;
extern double g_trajectoryWidth;
extern double g_treeWidth;

extern double g_crosswalkSpace;
extern double g_crosswalkLineWidth;

extern int32_t g_virtualLineNum;

extern double g_constant;
extern double g_linear;
extern double g_quadratic;
extern double g_cutOff;
extern double g_outCutOff;

// ColorInfo g_whiteLineColor = {255, 255, 255, 100};
// ColorInfo g_yellowLineColor = {255, 255, 0, 100};
// ColorInfo g_cubeColor = {0, 255, 0, 100};
// ColorInfo g_groundColor = {80, 80, 80, 100};
// ColorInfo g_roadColor = {19, 27, 39, 100};
// ColorInfo g_skyColor = {35, 45, 63, 100};

extern ColorInfo g_whiteLineColor;
extern ColorInfo g_yellowLineColor;
extern ColorInfo g_cubeColor;
extern ColorInfo g_groundColor;
extern ColorInfo g_roadColor;
extern ColorInfo g_skyColor;

extern std::unordered_map<std::string, std::pair<COWA::MapData::Road_RoadType, std::vector<Point3DGL>>> g_roadMap;

extern std::unordered_map<std::string, std::vector<CurvePointInfo>> g_curveMap;

extern std::unordered_map<std::string, LaneInfo> g_laneMap;

extern std::unordered_map<std::string, std::vector<Point3DGL>> g_crosswalkMap;
extern std::unordered_map<std::string, std::vector<std::vector<Point3DGL>>> g_crosswalkClipMap;

extern std::unordered_map<std::string, std::vector<Point3DGL>> g_signalMap;

extern std::unordered_map<std::string, std::vector<Point3DGL>> g_crossroadMap;


std::string getRoadTypeString(COWA::MapData::Road_RoadType roadType);

std::string getCurveTypeString(COWA::MapData::LaneCurve_Type curveType);

std::string getLanePointTypeString(COWA::MapData::LanePoint_Type lanePointType);

std::string getLaneTypeString(COWA::MapData::Lane_LaneType laneType);

std::string getLaneDirectionTypeString(COWA::MapData::Lane_LaneDirection laneDirectionType);

std::string getLaneTurnTypeString(COWA::MapData::Lane_LaneTurn laneTurnType);

bool IsSamePoint(const Point3DGL& a, const Point3DGL& b);

bool IsPopLast(const Point3DGL& a, const Point3DGL& b, const Point3DGL& c);

std::shared_ptr<COWA::MapData::HdMap> LoadHdMap();

void ParseHdMap(const std::shared_ptr<COWA::MapData::HdMap>& hdMap);

void CurveMapToCurveMapRelease();

std::pair<Point3DGL, Point3DGL> PointToPair(const Point3DGL& point1, const Point3DGL& point2, double lineWidth);

double lineLength(const Point3DGL& a, const Point3DGL& b);

std::vector<Point3DGL> GetLineEqualPoint(const Point3DGL& a, const Point3DGL& b, double space);

double GetPointDistance(const Point3DGL& a, const std::pair<Point3DGL, Point3DGL>& line);

std::vector<Point3DGL> GetRectLine(const Point3DGL& a, const GlmVec3& direct, double lineWidth);

double GetVariance(const std::vector<double>& vecDistance);

std::vector<std::vector<Point3DGL>> CurvePointClip(std::vector<Point3DGL>& vecCurvePointInfo,
	double crosswalkSpace, double crosswalkLineWidth);

void CrosswalkClip();

std::set<std::string> LaneIdToLaneCurveId(const std::set<std::string>& laneId);

std::pair<std::vector<float>, std::vector<DrawInfo>> DataToVertices();

bool IsPointInBoundary(const Point3DGL& point, const std::vector<Point3DGL>& boundary);