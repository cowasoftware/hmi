import QtQuick 2.0


QtObject {
     property var ioStatus:{
            0: "关闭",
            1: "打开",
            2: "--"
     }
     property var battOverTemp: {
            0 : "正常",
            1 : "温度过高故障一级报警",
            2 : "温度过高故障二级报警",
            3 : "温度过高故障三级级报警" 
     }
     property var insuWarn: {
            0 : "正常",
            1 : "一级报警",
            2 : "二级报警",
            3 : "三级报警" 
     }
     property var lessElcWarn : {
            0 : "正常",    
            1 : "一级馈电告警",    
            2 : "二级馈电告警",    
            3 : "三级馈电告警"  
     }
     property var adhessWarn : {
            0 : "正常",    
            1 : "粘连"
     }
     property var sohWarn : {
            0 : "正常",    
            1 : "报警",    
            2 : "暂不执行",    
            3 : "暂不执行"
     }
     property var relaySts : {
            0 : "断开",
            1 : "闭合",
            2 : "未知"
     }
     property var connecSts : {
            0 : "未连接",
            1 : "连接"
     }
     property var prechargeSts : {
            0 : "未预充",    
            1 : "预充中",    
            2 : "预充成功",    
            3 : "预充失败"
     }
     property var bmsSts : {
            0 : "default",                           
            1 : "INITIAL",                           
            2 : "STANDBY",                     
            3 : "PRECHG",    
            4 : "Normal Discharge",    
            5 : "AC_CHARGING",     
            6 : "DC_CHARGING",      
            7 : "Reserved",    
            8 : "Reserved",    
            9 : "Cut off HV",    
            10 : "Power Hold(After run)",     
            11 : "INITIAL_FAILED",    
            12 : "Precharge_Failed",    
            13 : "end_of_charge",    
            14 : "Emergency_Cut_off_HV" 
     }
     property var backEnb : {
            0 : "不使能",
            1 : "使能"
     }
     property var balanceSts : {
            0 : "未开启",
            1 : "开启均衡"    

     }
     property var socLow : {
            0 : "正常",
            1 : "故障"    

     }
     property var wakeUpType : {
            0 : "default",    
            1 : "KEY",    
            2 : "快充插枪"
     }
     property var battBalan : {
            0 : "正常",    
            1 : "温度过不均衡故障一级报警",    
            2 : "温度不均衡故障二级报警",    
            3 : "温度不均衡故障三级级报警" 
     }
     property var battLess : {
            0 : "正常",    
            1 : "温度过低故障一级报警",   
            2 : "温度过低故障二级报警",    
            3 : "温度过高故障三级级报警"
     }
     property var warmSts : {
            0 : "默认状态",    
            1 : "充电加热中",    
            2 : "充电加热结束",    
            3 : "充电加热暂停"
     }
     property var sysFault : {
            0 : "Normal",       
            1 : "Warning",       
            2 : "Derate power",       
            3 : "Limp home",       
            4 : "Shutdowm",       
            5 : "emergency shutdown",       
            6 : "Reserved",
            7 : "Reserved"
     }
     property var hVLock : {
            0 : "正常",       
            1 : "故障",       
            2 : "预留",       
            3 : "预留"
     }
     property var pwReq : {
            0 : "正常",
            1 : "请求下电"
     }
     property var intePass : {
            0 : "自检未完成或不正常",
            1 : "自检完成并正常"
     }
     property var gearSts : {
         0 : "空挡",
         1 : "倒车挡",
         2 : "前进挡"
     }
     property var backBk : {
         0 : "未生效",
         1 : "生效"
     }
     property var accSts : {
         0 : "无故障",
         1 : "告警",
         2 : "故障"
     }
     property var comSts : {
         0 : "正常",
         1 : "正常",
         2 : "二级报警",
         3 : "一级报警"
     }
     property var busBadDis : {
         0 : "放电完成",
         1 : "放电中或未放电"
     }
     property var brakeAct : {
         0 : "未踩刹车",
         1 : "已踩刹车"
     }
     property var mainWarn : {
         0 : "无效",
         1 : "有效"
     }
     property var otherWarn : {
         0 : "未报警",
         1 : "报警"
     }
     property var brakelightSts : {
         0 : "未请求",
         1 : "请求"
     }
     property var enableSwi: {
         0 : "输出禁止",
         1 : "输出使能"
     }
     property var outState : {
         0 : "输出禁止",
         1 : "输出正常",
         2 : "故障"
     }
     property var dcState : {
         0 : "正常",
         1 : "异常"
     }
     property var cutSts : {
         0 : "未切断",
         1 : "切断"
     }
     property var volWarn : {
         0 : "无故障",
         1 : "一级故障",
         2 : "二级故障", 
         3 : "三级故障"
     }
     property var vcState : {
         0 : "停机", 
         1 : "充电中",
         2 : "充电完成"
     }
     property var commuSts : {
         0 : "正常",
         1 : "出现故障",
         2 : "--"
     }
     property var fanFaultLevel : {
         0 : "正常",
         1 : "一级故障",
         2 : "二级故障",
         3 : "三级故障",
         4 : "四级故障"
     }
     property var fanModeSts : {
            0 : "Standby",
            1 : "转速控制",
            2 : "转矩控制",
            3 : "主动放电"
     }
     property var enSts : {
            0 : "控制器禁止PWM输出",
            1 : "控制器使能PWM输出"
     }
     property var preAllow : {
            0 : "不允许上高压",
            1 : "允许上高压"
     }
     property var dirSts : {
            1 : "电机正转",
            0 : "电机反转"
     }
     property var fanValid : {
            0 : "无效",
            1 : "有效"
     }
     property var fanC02Sts : {
            0 : "正常",
            1 : "一级故障",
            2 : "二级故障",
            3 : "三级故障",
            4 : "四级故障"
     }
}
