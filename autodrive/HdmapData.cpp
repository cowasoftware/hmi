#include "HdmapData.h"
#include "GlParam.h"
#include "ShaderNameDataManager.h"
#include "cppgl.h"
#include "Util.h"
#include <math.h>
#include <fstream>
#include "Glm.h"
#include "OpenGLManager.h"
#include "CiniAPI.h"
//#include "SendToMessageTest.h"
#include "MapConfig.h"
#include "SystemOS.h"

extern MapConfig g_config;

#if (SYSTEM_OS == 1)
int32_t g_major = 3;
int32_t g_minor = 0;
bool g_isES = true;
#elif (SYSTEM_OS == 2)
int32_t g_major = 3;
int32_t g_minor = 3;
bool g_isES = false;
#endif

double x_min_temp = std::numeric_limits<double>::max();
double x_max_temp = -std::numeric_limits<double>::max();
double y_min_temp = std::numeric_limits<double>::max();
double y_max_temp = -std::numeric_limits<double>::max();
double z_min_temp = std::numeric_limits<double>::max();
double z_max_temp = -std::numeric_limits<double>::max();

double x_min = 0.0;
double x_max = 0.0;
double y_min = 0.0;
double y_max = 0.0;
double z_min = 0.0;
double z_max = 0.0;

//double x_min = 346745.095048;
//double x_max = 353171.786146;
//double y_min = 3447119.664685;
//double y_max = 3451636.005403;
//double z_min = 5.180199;
//double z_max = 26.252018;

double g_lineHeight = 0.65;
double g_roadHeight = 0.5;
double g_groundHeight = 0.0;
double g_waveHeight = 0.85;
double g_trajectoryHeight = 0.7;
double g_heroCarHeight = 1.0;

double g_groundMargin = 100;
double g_lineWidth = 0.2;
double g_trajectoryWidth = 0.6;
double g_treeWidth = 0.6;

double g_crosswalkSpace = 1.5;
double g_crosswalkLineWidth = 0.6;

//虚线中实线所占点的个数，包含收尾，虚线两端不画
int32_t g_virtualLineNum = 20;

int32_t g_windowWidth = 1770;
int32_t g_windowHeight = 1080;
int32_t g_perspectiveAngle = 45;
float g_perspectiveFrontBegin = 0.01f;
float g_perspectiveFrontEnd = 500.0f;

double g_constant = 1.0;
double g_linear = 0.0009;
double g_quadratic = 0.00005;
double g_cutOff = 80;
double g_outCutOff = 85;

// ColorInfo g_whiteLineColor = {255, 255, 255, 100};
// ColorInfo g_yellowLineColor = {255, 255, 0, 100};
// ColorInfo g_cubeColor = {0, 255, 0, 100};
// ColorInfo g_groundColor = {80, 80, 80, 100};
// ColorInfo g_roadColor = {19, 27, 39, 100};
// ColorInfo g_skyColor = {35, 45, 63, 100};

ColorInfo g_whiteLineColor = {167, 182, 190, 100};
ColorInfo g_yellowLineColor = {255, 204, 22, 100};
ColorInfo g_cubeColor = {82, 91, 97, 100};
ColorInfo g_groundColor = {53, 57, 61, 100};
ColorInfo g_roadColor = {32, 32, 32, 100};
ColorInfo g_skyColor = {23, 31, 43, 100};

GlmVec3 g_cameraPos(1.2f,20.0f,2.0f);
GlmVec3 g_lightPos(1.2f, 20.0f, 2.0f);
GlmVec3 g_shineDirection(-0.2f, -1.0f, -0.3f);


std::string g_groundTexturePath = "resource/3d/obj/ground.jpg";

std::unordered_map<std::string, std::pair<COWA::MapData::Road_RoadType, std::vector<Point3DGL>>> g_roadMap;

std::unordered_map<std::string, std::vector<CurvePointInfo>> g_curveMap;

std::unordered_map<std::string, LaneInfo> g_laneMap;

std::unordered_map<std::string, std::vector<Point3DGL>> g_crosswalkMap;
std::unordered_map<std::string, std::vector<std::vector<Point3DGL>>> g_crosswalkClipMap;

std::unordered_map<std::string, std::vector<Point3DGL>> g_signalMap;

std::unordered_map<std::string, std::vector<Point3DGL>> g_crossroadMap;

std::string getRoadTypeString(COWA::MapData::Road_RoadType roadType)
{
	std::string roadTypeString;
	switch (roadType)
	{
	case COWA::MapData::Road_RoadType::Road_RoadType_NONE:
	{
		roadTypeString = "未知类型";
	}
	break;
	case COWA::MapData::Road_RoadType::Road_RoadType_CITY_DRIVING:
	{
		roadTypeString = "城市道路";
	}
	break;
	case COWA::MapData::Road_RoadType::Road_RoadType_VIADUCT:
	{
		roadTypeString = "高架桥";
	}
	break;
	case COWA::MapData::Road_RoadType::Road_RoadType_EXPRESSWAY:
	{
		roadTypeString = "高速公路";
	}
	break;
	case COWA::MapData::Road_RoadType::Road_RoadType_TUNNEL:
	{
		roadTypeString = "隧道";
	}
	break;
	default:
		break;
	}
	return roadTypeString;
}

std::string getCurveTypeString(COWA::MapData::LaneCurve_Type curveType)
{
	std::string curveTypeString;
	switch (curveType)
	{
	case COWA::MapData::LaneCurve_Type::LaneCurve_Type_REALITY:
	{
		curveTypeString = "REALITY";
	}
	break;
	case COWA::MapData::LaneCurve_Type::LaneCurve_Type_VIRTUAL:
	{
		curveTypeString = "VIRTUAL";
	}
	break;
	case COWA::MapData::LaneCurve_Type::LaneCurve_Type_CENTRAL:
	{
		curveTypeString = "CENTRAL";
	}
	break;
	default:
		break;
	}
	return curveTypeString;
}

std::string getLanePointTypeString(COWA::MapData::LanePoint_Type lanePointType)
{
	std::string lanePointTypeString;
	switch (lanePointType)
	{
	case COWA::MapData::LanePoint_Type::LanePoint_Type_UNKNOWN:
	{
		lanePointTypeString = "未知路线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW:
	{
		lanePointTypeString = "黄虚线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE:
	{
		lanePointTypeString = "白虚线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW:
	{
		lanePointTypeString = "黄实线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE:
	{
		lanePointTypeString = "白实线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW:
	{
		lanePointTypeString = "双黄线";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_CURB:
	{
		lanePointTypeString = "马路牙";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_BLANK:
	{
		lanePointTypeString = "无边界";
	}
	break;
	case COWA::MapData::LanePoint_Type::LanePoint_Type_VIRTUAL:
	{
		lanePointTypeString = "虚拟线";
	}
	break;
	default:
		break;
	}
	return lanePointTypeString;
}

std::string getLaneTypeString(COWA::MapData::Lane_LaneType laneType)
{
	std::string laneTypeString;
	switch (laneType)
	{
	case COWA::MapData::Lane_LaneType_NONE:
	{
		laneTypeString = "虚拟车道";
	}
	break;
	case COWA::MapData::Lane_LaneType_CITY_DRIVING:
	{
		laneTypeString = "机动车道";
	}
	break;
	case COWA::MapData::Lane_LaneType_BIKING:
	{
		laneTypeString = "非机动车道";
	}
	break;
	case COWA::MapData::Lane_LaneType_PARKING:
	{
		laneTypeString = "停车车道";
	}
	break;
	case COWA::MapData::Lane_LaneType_EMERGENCY_LINE:
	{
		laneTypeString = "应急车道";
	}
	break;
	case COWA::MapData::Lane_LaneType_SIDEWALK:
	{
		laneTypeString = "人行道";
	}
	break;
	case COWA::MapData::Lane_LaneType_WAITINGAREA:
	{
		laneTypeString = "待转区";
	}
	break;
	case COWA::MapData::Lane_LaneType_HYBRID:
	{
		laneTypeString = "机非混合道路";
	}
	break;
	default:
		break;
	}
	return laneTypeString;
}

std::string getLaneDirectionTypeString(COWA::MapData::Lane_LaneDirection laneDirectionType)
{
	std::string laneDirectionTypeString;
	switch (laneDirectionType)
	{
	case COWA::MapData::Lane_LaneDirection::Lane_LaneDirection_FORWARD:
	{
		laneDirectionTypeString = "单向向前行驶";
	}
	break;
	case COWA::MapData::Lane_LaneDirection::Lane_LaneDirection_BACKWARD:
	{
		laneDirectionTypeString = "单向向后行驶";
	}
	break;
	case COWA::MapData::Lane_LaneDirection::Lane_LaneDirection_BIDIRECTION:
	{
		laneDirectionTypeString = "双向行驶";
	}
	break;
	default:
		break;
	}
	return laneDirectionTypeString;
}

std::string getLaneTurnTypeString(COWA::MapData::Lane_LaneTurn laneTurnType)
{
	std::string laneTurnTypeString;
	switch (laneTurnType)
	{
	case COWA::MapData::Lane_LaneTurn::Lane_LaneTurn_NO_TURN:
	{
		laneTurnTypeString = "直行";
	}
	break;
	case COWA::MapData::Lane_LaneTurn::Lane_LaneTurn_LEFT_TURN:
	{
		laneTurnTypeString = "左转";
	}
	break;
	case COWA::MapData::Lane_LaneTurn::Lane_LaneTurn_RIGHT_TURN:
	{
		laneTurnTypeString = "右转";
	}
	break;
	case COWA::MapData::Lane_LaneTurn::Lane_LaneTurn_U_TURN:
	{
		laneTurnTypeString = "掉头";
	}
	break;
	default:
		break;
	}
	return laneTurnTypeString;
}

bool IsSamePoint(const Point3DGL &a, const Point3DGL &b)
{
	double x = a.m_x - b.m_x;
	double y = a.m_y - b.m_y;
	double z = a.m_z - b.m_z;
	const double EPSINON = 0.000001;
	if (x <= EPSINON && x >= -EPSINON && y <= EPSINON && y >= -EPSINON && z <= EPSINON && z >= -EPSINON)
	{
		return true;
	}
	return false;
}

bool IsPopLast(const Point3DGL &a, const Point3DGL &b, const Point3DGL &c)
{
	double x1 = a.m_x - b.m_x;
	double y1 = a.m_y - b.m_y;
	double z1 = a.m_z - b.m_z;
	double x2 = c.m_x - b.m_x;
	double y2 = c.m_y - b.m_y;
	double z2 = c.m_z - b.m_z;
	if (IsSamePoint(a, b))
	{
		// printf("IsPopLast error\n");
		return false;
	}
	if (IsSamePoint(b, c))
	{
		return true;
	}
	return ((x1 * x2 + y1 * y2 + z1 * z2) / (pow((x1 * x1 + y1 * y1 + z1 * z1), 0.5) * pow((x2 * x2 + y2 * y2 + z2 * z2), 0.5))) < -0.996;
}

std::shared_ptr<COWA::MapData::HdMap> LoadHdMap()
{
	std::shared_ptr<COWA::MapData::HdMap> hdmap = std::make_shared<COWA::MapData::HdMap>();
	std::ifstream inFile;
	std::string mapPath = Util::GetCurrentExePath() + "resource/maps/" + g_config.m_mapName;
	std::cout << "map path " << mapPath << std::endl;
	inFile.open(mapPath, std::ios::in | std::ios::binary);
	// inFile.open(Util::GetCurrentExePath() + "../../maps/hdmap_xuhui_d20220828.bin", std::ios::in | std::ios::binary);
	if (inFile)
	{
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string data(buffer.str());
		hdmap->ParseFromString(data);
		inFile.close();
		std::cout << "map file read ok" << std::endl;
		return hdmap;
	}
	std::cout << "map file does not exist " << std::endl;
	return hdmap;
}

void ParseHdMap(const std::shared_ptr<COWA::MapData::HdMap> &hdMap)
{
	// if (hdMap->has_header())
	//{
	//	COWA::MapData::Header header = hdMap->header();
	//	if (header.has_version())
	//	{
	//		//RCSend("version = %s", header.version().c_str());
	//	}
	//	if (header.has_date())
	//	{
	//		//RCSend("date = %s", header.date().c_str());
	//	}
	//	if (header.has_projection())
	//	{
	//		//RCSend("projection = %s", header.projection().c_str());
	//	}
	//	if (header.has_generation())
	//	{
	//		//RCSend("generation = %s", header.generation().c_str());
	//	}
	//	if (header.has_md5())
	//	{
	//		//RCSend("md5 = %s", header.md5().c_str());
	//	}
	//	int32_t logSize = header.log_size();
	//	//RCSend("log size = %d", logSize);
	//	for (auto index = 0; index < logSize; ++index)
	//	{
	//		//RCSend("log[%d] = %s", index, header.log(index).c_str());
	//	}
	// }
	g_roadMap.clear();
	int32_t roadSize = hdMap->road_size();
	// RCSend("road size = %d", roadSize);
	for (auto index = 0; index < roadSize; ++index)
	{
		COWA::MapData::Road road = hdMap->road(index);
		// RCSend("road[%d] id = %s", index, road.id().id().c_str());
		const std::string &&roadTypeString = getRoadTypeString(road.type());
		// RCSend("road[%d] type = %s", index, roadTypeString.c_str());

		int32_t lane_id_aSize = road.lane_id_a_size();
		int32_t lane_id_bSize = road.lane_id_b_size();
		// RCSend("road[%d] lane_id_aSize = %d, lane_id_bSize = %d", index, lane_id_aSize, lane_id_bSize);
		std::string lane_id_a_string;
		for (auto index = 0; index < lane_id_aSize; ++index)
		{
			lane_id_a_string += road.lane_id_a(index).id() + ",";
		}
		if (!lane_id_a_string.empty())
		{
			lane_id_a_string.pop_back();
		}
		// RCSend("road[%d] lane_id_a_string = %s", index, lane_id_a_string.c_str());
		std::string lane_id_b_string;
		for (auto index = 0; index < lane_id_bSize; ++index)
		{
			lane_id_b_string += road.lane_id_b(index).id() + ",";
		}
		if (!lane_id_b_string.empty())
		{
			lane_id_b_string.pop_back();
		}
		// RCSend("road[%d] lane_id_b_string = %s", index, lane_id_b_string.c_str());

		std::vector<Point3DGL> vecRoadBoundary;
		if (road.has_boundary())
		{
			COWA::MapData::LaneCurve boundary = road.boundary();
			if (boundary.has_id())
			{
				// RCSend("road[%d] lane curve id = %s", index, boundary.id().id().c_str());
			}
			const std::string &&curveTypeString = getCurveTypeString(boundary.type());
			// RCSend("road[%d] lane curve type = %s", index, curveTypeString.c_str());
			if (boundary.type() != COWA::MapData::LaneCurve_Type::LaneCurve_Type_REALITY)
			{
				continue;
			}

			double offsetX = boundary.offset_x();
			double offsetY = boundary.offset_y();

			int32_t boundary_pointSize = boundary.point_size();
			// RCSend("road[%d] lane point size = %d", index, boundary_pointSize);
			for (auto pointIndex = 0; pointIndex < boundary_pointSize; ++pointIndex)
			{
				COWA::MapData::LanePoint lanePoint = boundary.point(pointIndex);
				std::string lanePointTypeString = getLanePointTypeString(lanePoint.type());
				// RCSend("road[%d] lane point[%d] type = %s, height = %f", index, pointIndex, lanePointTypeString.c_str(), lanePoint.height());
				if (lanePoint.type() == COWA::MapData::LanePoint_Type::LanePoint_Type_BLANK ||
					lanePoint.type() == COWA::MapData::LanePoint_Type::LanePoint_Type_VIRTUAL)
				{
					continue;
				}
				Point3DGL point;
				point.m_x = lanePoint.x() + offsetX;
				point.m_y = lanePoint.y() + offsetY;
				point.m_z = lanePoint.z();
				vecRoadBoundary.emplace_back(point);
			}

			int32_t stripSize = boundary.strip_size();
			if (stripSize != 0)
			{
				// RCSend("road[%d] lane curve strip size = %d", index, stripSize);
			}
		}
		g_roadMap[road.id().id()] = std::pair<COWA::MapData::Road_RoadType, std::vector<Point3DGL>>(road.type(), vecRoadBoundary);
	}
	int32_t lane_curveSize = hdMap->lane_curve_size();
	// RCSend("lane_curve size = %d", lane_curveSize);

	for (auto laneCurveIndex = 0; laneCurveIndex < lane_curveSize; ++laneCurveIndex)
	{
		COWA::MapData::LaneCurve lane_curve = hdMap->lane_curve(laneCurveIndex);
		if (lane_curve.has_id())
		{
			// RCSend("lane curve[%d] id = %s", laneCurveIndex, lane_curve.id().id().c_str());
		}
		const std::string &&curveTypeString = getCurveTypeString(lane_curve.type());
		// RCSend("lane curve[%d] type = %s", laneCurveIndex, curveTypeString.c_str());
		if (lane_curve.type() != COWA::MapData::LaneCurve_Type::LaneCurve_Type_REALITY)
		{
			continue;
		}

		double offsetX = lane_curve.offset_x();
		double offsetY = lane_curve.offset_y();

		std::vector<CurvePointInfo> vecCurvePointInfo;
		int32_t lane_curve_pointSize = lane_curve.point_size();
		// RCSend("lane curve[%d] lane point size = %d", laneCurveIndex, lane_curve_pointSize);
		for (auto pointIndex = 0; pointIndex < lane_curve_pointSize; ++pointIndex)
		{
			COWA::MapData::LanePoint lanePoint = lane_curve.point(pointIndex);
			std::string lanePointTypeString = getLanePointTypeString(lanePoint.type());
			// lanePoint.type() == COWA::MapData::LanePoint_Type::LanePoint_Type_BLANK ||
			if (lanePoint.type() == COWA::MapData::LanePoint_Type::LanePoint_Type_VIRTUAL)
			{
				continue;
			}

			if (lanePoint.height() != 0)
			{
				printf("height = %f\n", lanePoint.height());
			}
			if (lanePointTypeString != "虚拟线")
			{
				// RCSend("lane curve[%d] lane point[%d] type = %s, height = %f", laneCurveIndex, pointIndex, lanePointTypeString.c_str(), lanePoint.height());
			}
			CurvePointInfo info;
			info.m_type = lanePoint.type();
			info.m_point.m_x = lanePoint.x() + offsetX;
			info.m_point.m_y = lanePoint.y() + offsetY;
			info.m_point.m_z = lanePoint.z();

			x_min_temp = std::min(x_min_temp, info.m_point.m_x);
			x_max_temp = std::max(x_max_temp, info.m_point.m_x);
			y_min_temp = std::min(y_min_temp, info.m_point.m_y);
			y_max_temp = std::max(y_max_temp, info.m_point.m_y);
			z_min_temp = std::min(z_min_temp, info.m_point.m_z);
			z_max_temp = std::max(z_max_temp, info.m_point.m_z);

			//RCSend("x_min = %lf, y_min = %lf", x_min, y_min);

			vecCurvePointInfo.emplace_back(info);
		}

		int32_t stripSize = lane_curve.strip_size();
		if (stripSize != 0)
		{
			// RCSend("lane curve[%d] strip size = %d", laneCurveIndex, stripSize);
		}

		if (!vecCurvePointInfo.empty())
		{
			g_curveMap[lane_curve.id().id()] = vecCurvePointInfo;
		}
	}

	x_min = x_min_temp;
	x_max = x_max_temp;
	y_min = y_min_temp;
	y_max = y_max_temp;
	z_min = z_min_temp;
	z_max = z_max_temp;

	printf("x_min = %lf, x_max = %lf, y_min = %lf, y_max = %lf, z_min = %lf, z_max = %lf\n",
		x_min, x_max, y_min, y_max, z_min, z_max);

	int32_t laneSize = hdMap->lane_size();
	// RCSend("lane size = %d", laneSize);

	for (auto laneIndex = 0; laneIndex < laneSize; ++laneIndex)
	{
		COWA::MapData::Lane lane = hdMap->lane(laneIndex);
		// RCSend("lane[%d] id = %s", laneIndex, lane.id().id().c_str());
		std::string laneTypeString = getLaneTypeString(lane.type());
		// RCSend("lane[%d] type = %s", laneIndex, laneTypeString.c_str());
		if (lane.type() == COWA::MapData::Lane_LaneType_NONE)
		{
			continue;
		}

		LaneInfo info;
		info.m_type = lane.type();

		if (lane.has_central_line())
		{
			// RCSend("lane[%d] central_line = %s", laneIndex, lane.central_line().id().c_str());
		}
		int32_t leftLineSize = lane.left_line_size();
		if (leftLineSize != 1)
		{
			// RCSend("lane[%d] leftLineSize = %d", laneIndex, leftLineSize);
		}
		else
		{
			// RCSend("lane[%d] leftLine id = %s", laneIndex, lane.left_line(0).id().c_str());
		}

		for (auto index = 0; index < leftLineSize; ++index)
		{
			info.m_leftLane.push_back(lane.left_line(index).id());
		}

		int32_t rightLineSize = lane.right_line_size();
		if (rightLineSize != 1)
		{
			// RCSend("lane[%d] rightLineSize = %d", laneIndex, rightLineSize);
		}
		else
		{
			// RCSend("lane[%d] rightLine id = %s", laneIndex, lane.right_line(0).id().c_str());
		}

		for (auto index = 0; index < rightLineSize; ++index)
		{
			info.m_rightLane.push_back(lane.right_line(index).id());
		}

		g_laneMap[lane.id().id()] = info;

		int32_t predecessor_idSize = lane.predecessor_id_size();
		// RCSend("lane[%d] predecessor_idSize = %d", laneIndex, predecessor_idSize);
		if (predecessor_idSize != 0)
		{
			// RCSend("lane[%d] predecessor_id = %s", laneIndex, lane.predecessor_id(0).id().c_str());
		}
		int32_t successor_idSize = lane.successor_id_size();
		// RCSend("lane[%d] successor_idSize = %d", laneIndex, successor_idSize);
		if (successor_idSize != 0)
		{
			// RCSend("lane[%d] successor_id = %s", laneIndex, lane.successor_id(0).id().c_str());
		}
		int32_t left_neighbor_forward_lane_idSize = lane.left_neighbor_forward_lane_id_size();
		// RCSend("lane[%d] left_neighbor_forward_lane_idSize = %d", laneIndex, left_neighbor_forward_lane_idSize);
		if (left_neighbor_forward_lane_idSize != 0)
		{
			// RCSend("lane[%d] left_neighbor_forward_lane_id = %s", laneIndex, lane.left_neighbor_forward_lane_id(0).id().c_str());
		}
		int32_t right_neighbor_forward_lane_idSize = lane.right_neighbor_forward_lane_id_size();
		// RCSend("lane[%d] right_neighbor_forward_lane_idSize = %d", laneIndex, right_neighbor_forward_lane_idSize);
		if (right_neighbor_forward_lane_idSize != 0)
		{
			// RCSend("lane[%d] right_neighbor_forward_lane_id = %s", laneIndex, lane.right_neighbor_forward_lane_id(0).id().c_str());
		}
		int32_t left_neighbor_reverse_lane_idSize = lane.left_neighbor_reverse_lane_id_size();
		// RCSend("lane[%d] left_neighbor_reverse_lane_idSize = %d", laneIndex, left_neighbor_reverse_lane_idSize);
		if (left_neighbor_reverse_lane_idSize != 0)
		{
			// RCSend("lane[%d] left_neighbor_reverse_lane_id = %s", laneIndex, lane.left_neighbor_reverse_lane_id(0).id().c_str());
		}
		int32_t right_neighbor_reverse_lane_idSize = lane.right_neighbor_reverse_lane_id_size();
		// RCSend("lane[%d] right_neighbor_reverse_lane_idSize = %d", laneIndex, right_neighbor_reverse_lane_idSize);
		if (right_neighbor_reverse_lane_idSize != 0)
		{
			// RCSend("lane[%d] right_neighbor_reverse_lane_id = %s", laneIndex, lane.right_neighbor_reverse_lane_id(0).id().c_str());
		}
		if (lane.has_direction())
		{
			// RCSend("lane[%d] direction = %s", laneIndex, getLaneDirectionTypeString(lane.direction()).c_str());
		}
		if (lane.has_turn())
		{
			// RCSend("lane[%d] turn = %s", laneIndex, getLaneTurnTypeString(lane.turn()).c_str());
		}
		int32_t lane_markSize = lane.mark_size();
		if (lane_markSize != 0)
		{
			// printf("lane[%d] lane_markSize = %d\n", laneIndex, lane_markSize);
		}
	}

	int32_t crosswalkSize = hdMap->crosswalk_size();
	////RCSend("crosswalk size = %d", crosswalkSize);

	for (auto index = 0; index < crosswalkSize; ++index)
	{
		COWA::MapData::Crosswalk crosswalk = hdMap->crosswalk(index);
		std::vector<Point3DGL> vecCrosswalkInfo;
		if (crosswalk.has_polygon())
		{
			COWA::MapData::Polygon polygon = crosswalk.polygon();
			for (auto pointIndex = 0; pointIndex < polygon.point_size(); ++pointIndex)
			{
				Point3DGL point;
				COWA::MapData::PointENU pointENU = polygon.point(pointIndex);
				point.m_x = pointENU.x();
				point.m_y = pointENU.y();
				point.m_z = pointENU.z();
				vecCrosswalkInfo.emplace_back(point);
			}
		}
		if (crosswalk.has_oriention())
		{
			printf("oriention = %f\n", crosswalk.oriention());
		}

		if (!vecCrosswalkInfo.empty())
		{
			g_crosswalkMap[crosswalk.id().id()] = vecCrosswalkInfo;
		}
	}
	//
	// int32_t signalSize = hdMap->signal_size();
	////RCSend("signal size = %d", signalSize);
	//
	int32_t crossroadSize = hdMap->crossroad_size();
	////RCSend("crossroad size = %d", crossroadSize);
	for (auto index = 0; index < crossroadSize; ++index)
	{
		COWA::MapData::Crossroad crossroad = hdMap->crossroad(index);
		std::vector<Point3DGL> vecCrossroadInfo;
		if (crossroad.has_boundary())
		{
			COWA::MapData::Polygon polygon = crossroad.boundary();
			for (auto pointIndex = 0; pointIndex < polygon.point_size(); ++pointIndex)
			{
				auto pointENU = polygon.point(pointIndex);
				Point3DGL point;
				point.m_x = pointENU.x();
				point.m_y = pointENU.y();
				point.m_z = pointENU.z();
				vecCrossroadInfo.emplace_back(point);
			}
		}
		if (!vecCrossroadInfo.empty())
		{
			g_crossroadMap[crossroad.id().id()] = vecCrossroadInfo;
		}
	}

	int32_t signalSize = hdMap->signal_size();
	for (auto index = 0; index < signalSize; ++index)
	{
		COWA::MapData::Signal signal = hdMap->signal(index);
		std::vector<Point3DGL> vecPoint;
		for (auto stopLineIndex = 0; stopLineIndex < signal.stop_line_size(); ++stopLineIndex)
		{
			COWA::MapData::PointENU pointENU = signal.stop_line(stopLineIndex);
			Point3DGL point;
			point.m_x = pointENU.x();
			point.m_y = pointENU.y();
			point.m_z = pointENU.z();
			vecPoint.emplace_back(point);
		}
		g_signalMap[signal.id().id()] = vecPoint;
	}

	//
	// int32_t rampSize = hdMap->ramp_size();
	////RCSend("ramp size = %d", rampSize);
	//
	// int32_t roadmarkSize = hdMap->roadmark_size();
	////RCSend("roadmark size = %d", roadmarkSize);
	//
	// int32_t parking_spaceSize = hdMap->parking_space_size();
	////RCSend("parking_space size = %d", parking_spaceSize);
	//
	// int32_t overlapSize = hdMap->overlap_size();
	////RCSend("overlap size = %d", overlapSize);
	//
	// int32_t objectsSize = hdMap->objects_size();
	////RCSend("objects size = %d", objectsSize);
	//
	// int32_t lane_changeSize = hdMap->lane_change_size();
	////RCSend("lane_change size = %d", lane_changeSize);
	//
	// int32_t tideSize = hdMap->tide_size();
	////RCSend("tide size = %d", tideSize);
}

void CurveMapToCurveMapRelease()
{
	for (auto it = g_curveMap.begin(); it != g_curveMap.end(); ++it)
	{
		std::vector<CurvePointInfo> &vecCurvePointInfo = it->second;
		CurvePointInfo *preInfo = nullptr;
		for (auto itCurve = vecCurvePointInfo.begin(); itCurve != vecCurvePointInfo.end();)
		{
			CurvePointInfo &currentInfo = *itCurve;
			if (itCurve == vecCurvePointInfo.end())
			{
				break;
			}

			if (preInfo == nullptr)
			{
				if (currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW ||
					currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE ||
					currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW ||
					currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_CURB)
				{
					preInfo = &currentInfo;
				}
				++itCurve;
				continue;
			}

			++itCurve;
			if (itCurve == vecCurvePointInfo.end())
			{
				break;
			}
			const CurvePointInfo &nextInfo = *itCurve;
			--itCurve;
			if ((currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW ||
				 currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE ||
				 currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW ||
				 currentInfo.m_type == COWA::MapData::LanePoint_Type::LanePoint_Type_CURB) &&
				(*preInfo).m_type == currentInfo.m_type &&
				currentInfo.m_type == nextInfo.m_type &&
				IsPopLast((*preInfo).m_point, currentInfo.m_point, nextInfo.m_point))
			{
				itCurve = vecCurvePointInfo.erase(itCurve);
				++itCurve;
				continue;
			}
			preInfo = &currentInfo;
			++itCurve;
		}
	}
}

std::pair<Point3DGL, Point3DGL> PointToPair(const Point3DGL &point1, const Point3DGL &point2, double lineWidth)
{
	GlmVec3 vec3Point1(point1.m_x, point1.m_y, point1.m_z);
	GlmVec3 vec3Point2(point2.m_x, point2.m_y, point2.m_z);

	GlmVec3 widthVec3 = Glm::normalize(Glm::cross(Glm::minus(vec3Point1, vec3Point2), GlmVec3(0, 0, 1)));
	widthVec3.scale(lineWidth / 2);

	std::pair<Point3DGL, Point3DGL> result;
	vec3Point2.add(widthVec3);
	result.first.m_x = vec3Point2.x();
	result.first.m_y = vec3Point2.y();
	result.first.m_z = vec3Point2.z();
	vec3Point2.minus(widthVec3);
	vec3Point2.minus(widthVec3);
	result.second.m_x = vec3Point2.x();
	result.second.m_y = vec3Point2.y();
	result.second.m_z = vec3Point2.z();

	return result;
}

double lineLength(const Point3DGL &a, const Point3DGL &b)
{
	return pow((a.m_x - b.m_x) * (a.m_x - b.m_x) + (a.m_y - b.m_y) * (a.m_y - b.m_y), 0.5);
}

//获取线中等距的点
std::vector<Point3DGL> GetLineEqualPoint(const Point3DGL &a, const Point3DGL &b, double space)
{
	std::vector<Point3DGL> result;
	if (OpenGLManager::instance().floatCompareZero(space))
	{
		return result;
	}
	double length = lineLength(a, b);
	int32_t num = (int32_t)(length / space);
	if (num == 0)
	{
		return result;
	}

	double margin = (length - (num - 1) * space) / 2;

	GlmVec3 direct(a.m_x - b.m_x, a.m_y - b.m_y, 0);
	direct = Glm::normalize(direct);
	GlmVec3 marginVec = direct;
	direct.scale(space);
	marginVec.scale(margin);

	GlmVec3 point(b.m_x, b.m_y, 0);
	for (auto index = 0; index < num; ++index)
	{
		if (index == 0)
		{
			point.add(marginVec);
			result.emplace_back(std::move(Point3DGL{point.x(), point.y(), 0}));
			continue;
		}
		point.add(direct);
		result.emplace_back(std::move(Point3DGL{point.x(), point.y(), 0}));
	}

	return result;
}

//获取点到直线的距离
double GetPointDistance(const Point3DGL &a, const std::pair<Point3DGL, Point3DGL> &line)
{
	double x1 = a.m_x;
	double y1 = a.m_y;
	double z1 = a.m_z;
	double x2 = line.first.m_x;
	double y2 = line.first.m_y;
	double z2 = line.first.m_z;
	double x3 = line.second.m_x;
	double y3 = line.second.m_y;
	double z3 = line.second.m_z;
	double area = (x1 * y2 - x1 * y3 + x2 * y3 - x2 * y1 + x3 * y1 - x3 * y2) * 0.5;
	if (area < 0)
	{
		area *= -1;
	}
	return area / lineLength(line.first, line.second);
}

//根据点和方向获取人行道单个矩形
std::vector<Point3DGL> GetRectLine(const Point3DGL &a, const GlmVec3 &direct, double lineWidth)
{
	GlmVec3 point(a.m_x, a.m_y, 0);
	point.add(direct);
	Point3DGL b(point.x(), point.y(), 0);
	std::pair<Point3DGL, Point3DGL> &&bPair = PointToPair(a, b, lineWidth);
	std::vector<Point3DGL> result;
	result.emplace_back(std::move(bPair.first));
	result.emplace_back(std::move(bPair.second));
	std::pair<Point3DGL, Point3DGL> &&aPair = PointToPair(b, a, lineWidth);
	result.emplace_back(std::move(aPair.first));
	result.emplace_back(std::move(aPair.second));
	return result;
}

double GetVariance(const std::vector<double> &vecDistance)
{
	double avg = 0;
	for (std::size_t index = 0; index < vecDistance.size(); ++index)
	{
		avg += vecDistance[index];
	}
	avg /= vecDistance.size();
	double variance = 0;
	for (std::size_t index = 0; index < vecDistance.size(); ++index)
	{
		variance += (vecDistance[index] - avg) * (vecDistance[index] - avg);
	}
	variance /= vecDistance.size();
	return variance;
}

std::vector<std::vector<Point3DGL>> CurvePointClip(std::vector<Point3DGL> &vecCurvePointInfo, double crosswalkSpace,
	double crosswalkLineWidth)
{
	std::vector<std::vector<Point3DGL>> result;
	if (vecCurvePointInfo.size() <= 2)
	{
		return result;
	}
	if (IsSamePoint(vecCurvePointInfo[0], vecCurvePointInfo.back()))
	{
		vecCurvePointInfo.pop_back();
	}
	if (vecCurvePointInfo.size() <= 2)
	{
		return result;
	}
	std::vector<std::pair<Point3DGL, Point3DGL>> vecLine;
	double maxLength = 0;
	Point3DGL pointA;
	Point3DGL pointB;
	int32_t pointInLineIndex = -1;
	for (std::size_t index = 0; index < vecCurvePointInfo.size(); ++index)
	{
		if (index == 0)
		{
			double currentLength = lineLength(vecCurvePointInfo.back(), vecCurvePointInfo[0]);
			if (currentLength > maxLength)
			{
				maxLength = currentLength;
				pointA = vecCurvePointInfo.back();
				pointB = vecCurvePointInfo[0];
				pointInLineIndex = 0;
			}
			vecLine.emplace_back(std::move(std::pair<Point3DGL, Point3DGL>(vecCurvePointInfo.back(), vecCurvePointInfo[0])));
		}
		else
		{
			double currentLength = lineLength(vecCurvePointInfo[index - 1], vecCurvePointInfo[index]);
			if (currentLength > maxLength)
			{
				maxLength = currentLength;
				pointA = vecCurvePointInfo[index - 1];
				pointB = vecCurvePointInfo[index];
				pointInLineIndex = index;
			}
			vecLine.emplace_back(std::move(std::pair<Point3DGL, Point3DGL>(vecCurvePointInfo[index - 1], vecCurvePointInfo[index])));
		}
	}
	const std::vector<Point3DGL> &vecLineEqualPoint = GetLineEqualPoint(pointA, pointB, crosswalkSpace);
	if (vecLineEqualPoint.empty())
	{
		return result;
	}

	double minVariance = std::numeric_limits<double>::max();
	std::vector<double> minVarianceVecDistance;

	for (std::size_t lineIndex = 0; lineIndex < vecLine.size(); ++lineIndex)
	{
		if (lineIndex == (std::size_t)pointInLineIndex)
		{
			continue;
		}
		std::vector<double> vecDistance;
		for (std::size_t index = 0; index < vecLineEqualPoint.size(); ++index)
		{
			Point3DGL point = vecLineEqualPoint[index];
			point.m_x -= x_min;
			point.m_y -= y_min;
			point.m_z = 0;
			std::pair<Point3DGL, Point3DGL> line = vecLine[lineIndex];
			line.first.m_x -= x_min;
			line.first.m_y -= y_min;
			line.first.m_z = 0;
			line.second.m_x -= x_min;
			line.second.m_y -= y_min;
			line.second.m_z = 0;
			double distance = GetPointDistance(point, line);
			vecDistance.push_back(distance);
		}
		double variance = GetVariance(vecDistance);
		if (variance < minVariance)
		{
			minVariance = variance;
			minVarianceVecDistance = vecDistance;
		}
	}

	double drawDistance = 0;
	for (std::size_t index = 0; index < minVarianceVecDistance.size(); ++index)
	{
		drawDistance += minVarianceVecDistance[index];
	}
	drawDistance = drawDistance / minVarianceVecDistance.size();

	GlmVec3 direct = Glm::normalize(Glm::cross(GlmVec3(pointB.m_x - pointA.m_x, pointB.m_y - pointA.m_y, 0.0), GlmVec3(0.0, 0.0, 1.0)));
	direct.scale(drawDistance);
	for (std::size_t index = 0; index < vecLineEqualPoint.size(); ++index)
	{
		result.emplace_back(std::move(GetRectLine(vecLineEqualPoint[index], direct, crosswalkLineWidth)));
	}
	return result;
}

void CrosswalkClip()
{
	g_crosswalkClipMap.clear();
	for (auto it = g_crosswalkMap.begin(); it != g_crosswalkMap.end(); ++it)
	{
		g_crosswalkClipMap[it->first] = std::move(CurvePointClip(it->second, g_crosswalkSpace, g_crosswalkLineWidth));
	}
}

std::set<std::string> LaneIdToLaneCurveId(const std::set<std::string>& laneId)
{
	std::set<std::string> result;
	for (auto itLane = laneId.begin(); itLane != laneId.end(); ++itLane)
	{
		auto itLaneMap = g_laneMap.find(*itLane);
		if (itLaneMap == g_laneMap.end())
		{
			continue;
		}
		for (std::size_t index = 0; index < itLaneMap->second.m_leftLane.size(); ++index)
		{
			std::string leftId = itLaneMap->second.m_leftLane[index];
			result.insert(leftId);
		}
		for (std::size_t index = 0; index < itLaneMap->second.m_rightLane.size(); ++index)
		{
			result.insert(itLaneMap->second.m_rightLane[index]);
		}
	}
	return result;
}

std::pair<std::vector<float>, std::vector<DrawInfo>> DataToVertices()
{
	std::pair<std::vector<float>, std::vector<DrawInfo>> result;
	std::vector<float>& vecData = result.first;
	std::vector<DrawInfo>& vecDrawInfo = result.second;
	int32_t dataIndex = 0;
	for (auto it = g_curveMap.begin(); it != g_curveMap.end(); ++it)
	{
		std::vector<CurvePointInfo>& vecCurvePointInfo = it->second;
		if (vecCurvePointInfo.empty())
		{
			continue;
		}
		int32_t lastType = -1;
		DrawInfo info;
		info.m_mapElementType = MapElementType::MAP_LANE_CURVE;
		info.m_mapElementId = it->first;
		COWA::MapData::LanePoint_Type currentType = (COWA::MapData::LanePoint_Type)-1;

		for (std::size_t index = 0; index < vecCurvePointInfo.size(); ++index)
		{
			if (vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW &&
				vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE &&
				vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW &&
				vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE &&
				vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW &&
				vecCurvePointInfo[index].m_type != COWA::MapData::LanePoint_Type::LanePoint_Type_CURB)
			{
				continue;
			}

			currentType = vecCurvePointInfo[index].m_type;

			if (lastType == -1)
			{
				lastType = currentType;
			}
			else if (lastType != currentType)
			{
				if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_yellowLineColor;
				}
				else if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_whiteLineColor;
				}
				else if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_yellowLineColor;
				}
				else if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_whiteLineColor;
				}
				else if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_yellowLineColor;
				}
				else if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_CURB)
				{
					info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
					info.m_color = g_cubeColor;
				}
				if (dataIndex != 0)
				{
					if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW ||
						lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE)
					{
						std::vector<float> vecPointData;
						int32_t dataCount = dataIndex * 3 * 2;
						while (dataCount-- != 0)
						{
							vecPointData.insert(vecPointData.begin(), vecData.back());
							vecData.pop_back();
						}
						int32_t linePoint = dataIndex / 2;
						if (linePoint > g_virtualLineNum * 3)
						{
							int32_t lineCount = ((linePoint - 2 * g_virtualLineNum + 1) / (g_virtualLineNum - 1) + 1) / 2;
							int32_t virtualEmptyNum = (linePoint - lineCount * g_virtualLineNum) / (lineCount + 1);
							int32_t collectIndex = virtualEmptyNum * 2 * 3 * 2 - 1;
							for (auto lineIndex = 0; lineIndex < lineCount; ++lineIndex)
							{
								int32_t collectPointCount = g_virtualLineNum * 2 * 3 * 2;
								while (collectPointCount-- != 0)
								{
									vecData.push_back(vecPointData[++collectIndex]);
								}
								info.m_size = g_virtualLineNum * 2;
								vecDrawInfo.emplace_back(info);
								collectIndex += virtualEmptyNum * 2 * 3 * 2;
							}
						}
					}
					else
					{
						info.m_size = dataIndex;
						vecDrawInfo.emplace_back(info);
					}
					dataIndex = 0;
					lastType = currentType;
				}
			}

			Point3DGL point;
			point.m_x = vecCurvePointInfo[index].m_point.m_x - x_min;
			point.m_y = vecCurvePointInfo[index].m_point.m_y - y_min;
			point.m_z = g_lineHeight;

			if (dataIndex == 0)
			{
				if (vecCurvePointInfo.size() > index + 1 && vecCurvePointInfo[index + 1].m_type == currentType)
				{
					Point3DGL nextPoint;
					nextPoint.m_x = vecCurvePointInfo[index + 1].m_point.m_x - x_min;
					nextPoint.m_y = vecCurvePointInfo[index + 1].m_point.m_y - y_min;
					nextPoint.m_z = g_lineHeight;
					std::pair<Point3DGL, Point3DGL> pairPoint = PointToPair(nextPoint, point, g_lineWidth);
					vecData.push_back(pairPoint.second.m_x);
					vecData.push_back(pairPoint.second.m_y);
					vecData.push_back(g_lineHeight);

					vecData.push_back(0.0f);
					vecData.push_back(0.0f);
					vecData.push_back(1.0f);

					vecData.push_back(pairPoint.first.m_x);
					vecData.push_back(pairPoint.first.m_y);
					vecData.push_back(g_lineHeight);

					vecData.push_back(0.0f);
					vecData.push_back(0.0f);
					vecData.push_back(1.0f);
					dataIndex += 2;
				}
			}
			else
			{
				Point3DGL prePoint;
				prePoint.m_x = vecCurvePointInfo[index - 1].m_point.m_x - x_min;
				prePoint.m_y = vecCurvePointInfo[index - 1].m_point.m_y - y_min;
				prePoint.m_z = g_lineHeight;
				std::pair<Point3DGL, Point3DGL> pairPoint = PointToPair(prePoint, point, g_lineWidth);
				vecData.push_back(pairPoint.first.m_x);
				vecData.push_back(pairPoint.first.m_y);
				vecData.push_back(g_lineHeight);

				vecData.push_back(0.0f);
				vecData.push_back(0.0f);
				vecData.push_back(1.0f);

				vecData.push_back(pairPoint.second.m_x);
				vecData.push_back(pairPoint.second.m_y);
				vecData.push_back(g_lineHeight);

				vecData.push_back(0.0f);
				vecData.push_back(0.0f);
				vecData.push_back(1.0f);
				dataIndex += 2;
			}
		}

		if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_yellowLineColor;
		}
		else if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_whiteLineColor;
		}
		else if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_YELLOW)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_yellowLineColor;
		}
		else if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_SOLID_WHITE)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_whiteLineColor;
		}
		else if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOUBLE_YELLOW)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_yellowLineColor;
		}
		else if (currentType == COWA::MapData::LanePoint_Type::LanePoint_Type_CURB)
		{
			info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
			info.m_color = g_cubeColor;
		}

		if (dataIndex != 0)
		{
			if (lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_YELLOW ||
				lastType == COWA::MapData::LanePoint_Type::LanePoint_Type_DOTTED_WHITE)
			{
				std::vector<float> vecPointData;
				int32_t dataCount = dataIndex * 3 * 2;
				while (dataCount-- != 0)
				{
					vecPointData.insert(vecPointData.begin(), vecData.back());
					vecData.pop_back();
				}
				int32_t linePoint = dataIndex / 2;
				if (linePoint > g_virtualLineNum * 3)
				{
					int32_t lineCount = ((linePoint - 2 * g_virtualLineNum + 1) / (g_virtualLineNum - 1) + 1) / 2;
					int32_t virtualEmptyNum = (linePoint - lineCount * g_virtualLineNum) / (lineCount + 1);
					int32_t collectIndex = virtualEmptyNum * 2 * 3 * 2 - 1;
					for (auto lineIndex = 0; lineIndex < lineCount; ++lineIndex)
					{
						int32_t collectPointCount = g_virtualLineNum * 2 * 3 * 2;
						while (collectPointCount-- != 0)
						{
							vecData.push_back(vecPointData[++collectIndex]);
						}
						info.m_size = g_virtualLineNum * 2;
						vecDrawInfo.emplace_back(info);
						collectIndex += virtualEmptyNum * 2 * 3 * 2;
					}
				}
			}
			else
			{
				info.m_size = dataIndex;
				vecDrawInfo.emplace_back(info);
			}
			dataIndex = 0;
			lastType = -1;
		}
	}

	for (auto it = g_crosswalkClipMap.begin(); it != g_crosswalkClipMap.end(); ++it)
	{
		const std::vector<std::vector<Point3DGL>>& vecCurvePointInfoArray = it->second;
		for (std::size_t arrayIndex = 0; arrayIndex < vecCurvePointInfoArray.size(); ++arrayIndex)
		{
			const std::vector<Point3DGL>& vecCurvePointInfo = vecCurvePointInfoArray[arrayIndex];
			if (vecCurvePointInfo.size() <= 2)
			{
				continue;
			}
			for (std::size_t index = 0; index < vecCurvePointInfo.size(); ++index)
			{
				vecData.push_back(vecCurvePointInfo[index].m_x - x_min);
				vecData.push_back(vecCurvePointInfo[index].m_y - y_min);
				// vecData.push_back(vecCurvePointInfo[index].m_z - z_min + 0.35);
				vecData.push_back(g_lineHeight);

				vecData.push_back(0.0f);
				vecData.push_back(0.0f);
				vecData.push_back(1.0f);
			}
			DrawInfo info;
			info.m_mapElementType = MapElementType::MAP_CROSSWALK;
			info.m_mapElementId = it->first;
			info.m_drawType = cppgl::CPPGL_TRIANGLE_FAN;
			info.m_size = vecCurvePointInfo.size();
			info.m_color = g_whiteLineColor;
			vecDrawInfo.emplace_back(info);
		}
	}

	// for (auto it = g_crosswalkMap.begin(); it != g_crosswalkMap.end(); ++it)
	//{
	//     const std::vector<Point3DGL>& vecCurvePointInfo = it->second;
	//     if (vecCurvePointInfo.size() <= 2)
	//     {
	//         continue;
	//     }
	//     for (auto index = 0; index < vecCurvePointInfo.size(); ++index)
	//     {
	//         vecData.push_back(vecCurvePointInfo[index].m_x - x_min);
	//         vecData.push_back(vecCurvePointInfo[index].m_y - y_min);
	//         //vecData.push_back(vecCurvePointInfo[index].m_z - z_min + 0.35);
	//         vecData.push_back(g_lineHeight);
	//     }
	//	DrawInfo info;
	//	info.m_drawType = cppgl::CPPGL_LINE_LOOP;
	//	info.m_size = vecCurvePointInfo.size();
	//	info.m_color = {255, 0, 0, 100};
	//	vecDrawInfo.emplace_back(info);
	// }

	for (auto it = g_roadMap.begin(); it != g_roadMap.end(); ++it)
	{
		const std::vector<Point3DGL> &vecRoadPointInfo = it->second.second;
		for (std::size_t index = 0; index < vecRoadPointInfo.size(); ++index)
		{
			vecData.push_back(vecRoadPointInfo[index].m_x - x_min);
			vecData.push_back(vecRoadPointInfo[index].m_y - y_min);
			// vecData.push_back(vecRoadPointInfo[index].m_z - z_min);
			vecData.push_back(g_roadHeight);

			vecData.push_back(0.0f);
			vecData.push_back(0.0f);
			vecData.push_back(1.0f);
		}
		DrawInfo info;
		info.m_mapElementType = MapElementType::MAP_ROAD;
		info.m_mapElementId = it->first;
		info.m_drawType = cppgl::CPPGL_TRIANGLE_FAN;
		info.m_size = vecRoadPointInfo.size();
		info.m_color = g_roadColor;
		vecDrawInfo.emplace_back(info);
	}

	for (auto it = g_crossroadMap.begin(); it != g_crossroadMap.end(); ++it)
	{
		const std::vector<Point3DGL> &vecCrossroadPointInfo = it->second;
		for (std::size_t index = 0; index < vecCrossroadPointInfo.size(); ++index)
		{
			vecData.push_back(vecCrossroadPointInfo[index].m_x - x_min);
			vecData.push_back(vecCrossroadPointInfo[index].m_y - y_min);
			// vecData.push_back(vecCrossroadPointInfo[index].m_z - z_min);
			vecData.push_back(g_roadHeight);

			vecData.push_back(0.0f);
			vecData.push_back(0.0f);
			vecData.push_back(1.0f);
		}
		DrawInfo info;
		info.m_mapElementType = MapElementType::MAP_CROSSROAD;
		info.m_mapElementId = it->first;
		info.m_drawType = cppgl::CPPGL_TRIANGLE_FAN;
		info.m_size = vecCrossroadPointInfo.size();
		info.m_color = g_roadColor;
		vecDrawInfo.emplace_back(info);
	}

	dataIndex = 0;
	for (auto it = g_signalMap.begin(); it != g_signalMap.end(); ++it)
	{
		const std::vector<Point3DGL> &vecSignalInfo = it->second;
		for (std::size_t index = 0; index < vecSignalInfo.size(); ++index)
		{
			Point3DGL point;
			point.m_x = vecSignalInfo[index].m_x - x_min;
			point.m_y = vecSignalInfo[index].m_y - y_min;
			point.m_z = g_lineHeight;

			if (dataIndex == 0)
			{
				if (vecSignalInfo.size() > index + 1)
				{
					Point3DGL nextPoint;
					nextPoint.m_x = vecSignalInfo[index + 1].m_x - x_min;
					nextPoint.m_y = vecSignalInfo[index + 1].m_y - y_min;
					nextPoint.m_z = g_lineHeight;
					std::pair<Point3DGL, Point3DGL> pairPoint = PointToPair(nextPoint, point, g_lineWidth);
					vecData.push_back(pairPoint.first.m_x);
					vecData.push_back(pairPoint.first.m_y);
					vecData.push_back(g_lineHeight);

					vecData.push_back(0.0f);
					vecData.push_back(0.0f);
					vecData.push_back(1.0f);

					vecData.push_back(pairPoint.second.m_x);
					vecData.push_back(pairPoint.second.m_y);
					vecData.push_back(g_lineHeight);

					vecData.push_back(0.0f);
					vecData.push_back(0.0f);
					vecData.push_back(1.0f);
					dataIndex += 2;
				}
			}
			else
			{
				Point3DGL prePoint;
				prePoint.m_x = vecSignalInfo[index - 1].m_x - x_min;
				prePoint.m_y = vecSignalInfo[index - 1].m_y - y_min;
				prePoint.m_z = g_lineHeight;
				std::pair<Point3DGL, Point3DGL> pairPoint = PointToPair(prePoint, point, g_lineWidth);
				vecData.push_back(pairPoint.first.m_x);
				vecData.push_back(pairPoint.first.m_y);
				vecData.push_back(g_lineHeight);

				vecData.push_back(0.0f);
				vecData.push_back(0.0f);
				vecData.push_back(1.0f);

				vecData.push_back(pairPoint.second.m_x);
				vecData.push_back(pairPoint.second.m_y);
				vecData.push_back(g_lineHeight);

				vecData.push_back(0.0f);
				vecData.push_back(0.0f);
				vecData.push_back(1.0f);
				dataIndex += 2;
			}
		}
		DrawInfo info;
		info.m_mapElementType = MapElementType::MAP_SIGNAL;
		info.m_mapElementId = it->first;
		info.m_drawType = cppgl::CPPGL_TRIANGLE_STRIP;
		info.m_size = dataIndex;
		info.m_color = g_whiteLineColor;
		vecDrawInfo.emplace_back(info);
		dataIndex = 0;
	}

	vecData.push_back(-g_groundMargin);
	vecData.push_back(-g_groundMargin);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);
//
	vecData.push_back((x_max - x_min) + g_groundMargin);
	vecData.push_back(-g_groundMargin);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);
//
	vecData.push_back((x_max - x_min) + g_groundMargin);
	vecData.push_back((y_max - y_min) + g_groundMargin);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);
//
	vecData.push_back(-g_groundMargin);
	vecData.push_back((y_max - y_min) + g_groundMargin);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);
//
	DrawInfo info;
	info.m_mapElementType = MAP_GROUND;
	info.m_mapElementId = "ground";
	info.m_drawType = cppgl::CPPGL_TRIANGLE_FAN;
	info.m_size = 4;
	info.m_color = g_groundColor;
	vecDrawInfo.emplace_back(info);

	return result;
}

bool IsPointInBoundary(const Point3DGL& point, const std::vector<Point3DGL>& boundary)
{
	if (boundary.size() < 3)
	{
		return false;
	}
	GlmVec3 p(point.m_x, point.m_y, point.m_z);
	bool isInRoad = false;
	const Point3DGL& aPoint = boundary[0];
	GlmVec3 a(aPoint.m_x, aPoint.m_y, aPoint.m_z);
	GlmVec3 pa(a);
    pa.minus(p);
    pa = Glm::normalize(pa);

    for (std::size_t pointIndex = 2; pointIndex < boundary.size(); ++pointIndex)
    {
        const Point3DGL& bPoint = boundary[pointIndex - 1];
        const Point3DGL& cPoint = boundary[pointIndex - 0];
        
        GlmVec3 b(bPoint.m_x, bPoint.m_y, bPoint.m_z);
        GlmVec3 c(cPoint.m_x, cPoint.m_y, cPoint.m_z);

        GlmVec3 pb(b);
        pb.minus(p);
        pb = Glm::normalize(pb);

        GlmVec3 pc(c);
        pc.minus(p);
        pc = Glm::normalize(pc);

        float allAngle = Glm::angle(acos(Glm::dot(pa, pb))) + Glm::angle(acos(Glm::dot(pa, pc))) + Glm::angle(acos(Glm::dot(pb, pc)));
        if (allAngle > 359.9 && allAngle < 360.1)
        {
            isInRoad = true;
            break;
        }
    }
	return isInRoad;
}