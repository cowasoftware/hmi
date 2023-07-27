import QtQuick 2.0

// 清洗指令
QtObject {
    enum CmdType {

        LEFT_BRUSH_DOWN = 0,//左扫盘下降
        LEFT_BRUSH_UP,      //左扫盘上升
        LEFT_BRUSH_EXTEND,  //左扫盘展开
        LEFT_BRUSH_NARROW,  //左扫盘收拢

        RIGHT_BRUSH_EXTEND = 4, //右扫盘展开
        RIGHT_BRUSH_NARROW,     //右扫盘收拢
        RIGHT_BRUSH_DOWN,       //右扫盘下降
        RIGHT_BRUSH_UP,         //右扫盘上升

        TANK_OPEN = 8,          //箱门打开
        TANK_CLOSE,             //箱门关闭

        NOZZLE_DOWN = 10,       //吸嘴下降
        NOZZLE_UP,              //吸嘴上升

        EXTEND_RELAY = 12,      //颚板张开
        WITHDRAW_RELAY,         //颚板收回

        SEWAGE_LOOP = 14,       //污水循环工作

        FAN_CALIBRATION = 15,   //风机标定
        FAN_WORK_DEBUG,         //风机工作
        FAN_SPEEDACC,           //风机加速
        FAN_SPEEDMIN,           //风机减速

        LEFT_BRUSH_WORK_DEBUG = 19, //左扫盘工作
        RIGHT_BRUSH_WORK_DEBUG,     //右扫盘工作
        BRUSH_SPEED_ACC,            //扫盘加速
        BRUSH_SPEED_MIN,            //扫盘减速

        SPRAY_PUMP_DEBUG = 23,      //喷淋泵工作

        EPS_CALIBRATION = 24,       //EPS中位标定

        FAN_CLEAN_MODE = 25,        //保洁模式
        FAN_STANDARD_MODE,          //标准模式
        FAN_STRONG_MODE,            //强劲模式

        HIGH_PRECLEAN_STOP_MODE = 28,//停止高压清洗
        HIGH_PRECLEAN_START_MODE,    //开始高压清洗

        DUST_NORMAL_MODE = 30,       //正常模式
        DUST_SUPRE_MODE,             //抑尘模式

        TANK_TILT = 32,              //箱体倾翻
        TANK_RESET,                  //箱体复位
        WORK_LIGHT,                  //工作灯
        WORK_START,                  //工作开始

        CURISE_START = 36,           //开始巡航
        //CURISE_STOP = 37,  // stop巡航
        CURISE_ACC,                  //巡航加速
        CURISE_DEC                   //巡航减速
    }
    enum GetCanDataType
    {
        CLEAN_DATA = 0,
        DASHBOARD_DATA,
        LIGHTSCREEN_DATA,
        STATUS_DATA,
        DIAGNOSIS_IO_DATA,
        MCU1_DATA,
        DIAGNOSIS_BATTERY_DATA,
        DIAGNOSIS_MAINDRI_DATA,
        DIAGNOSIS_BRAKE_DATA,
        DIAGNOSIS_EPS_DATA,
        DIAGNOSIS_12VDC_DATA,
        DIAGNOSIS_48VDC_DATA,
        DIAGNOSIS_FAN902_DATA,
        DIAGNOSIS_FANA02_DATA,
        DIAGNOSIS_FANB02_DATA,
        DIAGNOSIS_FANC02_DATA,
        DIAGNOSIS_LEFTSWEEP_DATA,
        DIAGNOSIS_RIGHTSWEEP_DATA,
        DIAGNOSIS_SWEEPDISK_DATA,
        DIAGNOSIS_HIGPREPUM15_DATA,
        DIAGNOSIS_HIGPREPUM16_DATA,
        DIAGNOSIS_COMMUNI_DATA,
        DIAGNOSIS_BRAKE60_DATA,
        BAR_0x18F413EF_DATA,
        BAR_NETWORK_DATA,
	DIAGNOSIS_IO71_DATA,
        DIAGNOSIS_IO78_DATA,
        DIAGNOSIS_IO79_DATA,
        DIAGNOSIS_BATTERY13EF_DATA,
        DIAGNOSIS_BATTERY33EF_DATA,
        DIAGNOSIS_BATTERY11EF_DATA,
        DIAGNOSIS_BRAKE5F_DATA,
        DIAGNOSIS_EPS5C_DATA
    }
}
