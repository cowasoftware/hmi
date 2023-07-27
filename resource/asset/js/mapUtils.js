function loadJScript() {
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = "https://api.map.baidu.com/api?type=webgl&v=1.0&ak=aoxQr3uFO8ciYN0Fcgta821p0lbD9Ib6&callback=loadMap&s=1";
    document.body.appendChild(script);
}


// 全局变量
var  _Bridge = null;//全局变量  _Bridge
var  _QWebChannel = null;//全局变量 QWebChannel
// var _WebObject = null;
var curr_pos = new Array(); // 当前位置
var curr_point = null;
var start_pos_marker;
var curve_paths = [];    // 路径上的点
let img_url = "../image/autodrive/current_pos.png"
var map = null;
var point = null;
var myIcon = null;

function loadMap() {
    // 1、初始化固定地图
    map = new BMapGL.Map('container'); // 创建Map实例 
    // var point = new BMapGL.Point(121.42500606776105, 31.18102267127553); // 创建点坐标
    point = new BMapGL.Point(121.415,31.177); // 创建点坐标 (华鑫慧享城)
    map.centerAndZoom(point, 18); // 中心点坐标和地图级别
    map.enableScrollWheelZoom(true); // 启用滚轮放大缩小
    map.disableDoubleClickZoom(); // 禁用双击放大
    map.setMapStyleV2({styleJson: mapStyle});
    myIcon = new BMapGL.Icon(img_url, new BMapGL.Size(40, 40));
    // 添加定位组件
    addMyControl();

    // 2、处理相关逻辑
    try {
        _QWebChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
            _Bridge = channel.objects.webObject;
            window.webObject = _Bridge;
            // 2.1 标记主车位置
            markCurrentPos();
            // 2.2 地图选点
            addPoint();
            // 2.3 规划驾车路线
            driving_route();
            removePoint();
        });
    } catch(e) {
        console.error("init error!!!");
    }
}

// 3、地图长按选点
// addPoint(map);

// 4、绘制路径
// var points0 = [
//     new BMapGL.Point(121.41575401095938,31.178363242497223),
//     new BMapGL.Point(121.41771506905403,31.181399594890163),
//     new BMapGL.Point(121.4218926487499,31.182555967070535),
//     new BMapGL.Point(121.42231341217253,31.176069762203067),
//     new BMapGL.Point(120.59634892348123,31.33554870662581),
//     new BMapGL.Point(120.90856704409678,31.179366819167218),
//     new BMapGL.Point(121.42097598557932,31.173485491838004),
// ];
// alert("points0:" + points0);

function initialize() {
    var map = new BMapGL.Map('container'); // 创建Map实例
    var point = new BMapGL.Point(116.404, 39.915); // 创建点坐标
    map.centerAndZoom(point, 14); // 中心点坐标和地图级别
    map.enableScrollWheelZoom(true); // 启用滚轮放大缩小
}


function markCurrentPos() {
    // 接收主车位置
    if(_Bridge == "" || _Bridge == null || _Bridge == undefined) {
        // alert("js与QT桥未初始化");
        return;
    }
    //接收信号
    var handleData = function (curr_x, curr_y) {
        //todo
        // alert(curr_x + "," + curr_y);
        curr_pos = [];
        curr_pos.push(curr_x);
        curr_pos.push(curr_y);
        // 先清除上一次的当前位置
        map.removeOverlay(start_pos_marker);
        // TODO 创建点标记
        curr_point = new BMapGL.Point(curr_x, curr_y);
        start_pos_marker = new BMapGL.Marker(curr_point, {icon: myIcon});
        // 在地图上添加点标记
        map.addOverlay(start_pos_marker);
        // curr_point = null;
        // delete curr_point;
    }
    window.webObject.sendCurrentPos.connect(handleData);
}

// 添加地图控件
function addMapControls() {
    // 创建定位控件
    var locationControl = new BMapGL.LocationControl({
        // 控件的停靠位置（可选，默认左上角）
        anchor: BMAP_ANCHOR_BOTTOM_RIGHT,
        // 控件基于停靠位置的偏移量（可选）
        offset: new BMapGL.Size(20, 170)
    });
    // 将控件添加到地图上
    map.addControl(locationControl);

    // 添加定位事件
    locationControl.addEventListener("locationSuccess", function (e) {
        var address = '';
        address += e.addressComponent.province;
        address += e.addressComponent.city;
        address += e.addressComponent.district;
        address += e.addressComponent.street;
        address += e.addressComponent.streetNumber;
        // alert("当前定位地址为：" + address);
    });
    locationControl.addEventListener("locationError", function (e) {
        // alert(e.message);
    });
}

// 添加自定义控件
function addMyControl() {
    function ZoomControl() {
        // 默认停靠位置和偏移量
	    this.defaultAnchor = BMAP_ANCHOR_BOTTOM_RIGHT;
	    this.defaultOffset = new BMapGL.Size(32, 170);
    }
    // 通过JavaScript的prototype属性继承于BMap.Control
	ZoomControl.prototype = new BMapGL.Control();
    // 自定义控件必须实现自己的initialize方法,并且将控件的DOM元素返回
    ZoomControl.prototype.initialize = function(map){
        // 创建一个DOM元素
        var div = document.createElement("location_control");
        // 设置样式
        // div.style.cursor = "pointer";
        // div.style.border = "1px solid gray";
        div.style.position = "absolute";
        div.style.width = "80px";
        div.style.height = "80px";
        div.style.backgroundImage = "url('../image/autodrive/position.png')";

        // 绑定事件,点击一次放大两级
        div.onclick = function(e){
            // 定位当前位置
            if(curr_point == null) {
                map.centerAndZoom(point, 18);
            } else {
                map.centerAndZoom(curr_point, 18);
            }
        }
        // 添加DOM元素到地图中
        map.getContainer().appendChild(div);
        // 将DOM元素返回
        return div;
      }
      // 创建控件
      var myZoomCtrl = new ZoomControl();
      // 添加到地图当中
      map.addControl(myZoomCtrl);
}

// 地图选点
function addPoint() {
    // 鼠标选点
    var address;
    var lng;
    var lat;
    // 创建点标记
    var end_pos_marker = null;
    // 单击取消选点
    // map.addEventListener("click", function (e) {
    //     if(end_pos_marker != null && end_pos_marker != undefined && end_pos_marker != "") {
    //         map.removeOverlay(end_pos_marker);
    //         end_pos_marker = null;
    //         lng = e.latlng.lng;
    //         // 纬度
    //         lat = e.latlng.lat;
    //         // 数据传送到qml端
    //         window.webObject.removePoint(address, lng, lat);
    //     }
    // });
    // dbclick事件
    map.addEventListener("dblclick", function (e) {
        // 经度
        lng = e.latlng.lng;
        // 纬度
        lat = e.latlng.lat;
        // 创建点标记
        end_pos_marker = new BMapGL.Marker(new BMapGL.Point(lng, lat));
        // 在地图上添加点标记
        map.addOverlay(end_pos_marker);
        end_pos_marker.disableMassClear();
        // alert("点击位置经纬度："+ lng + ","+ lat);
        var point = new BMapGL.Point(lng, lat);
        var gc = new BMapGL.Geocoder();
        gc.getLocation(point, function (rs) {
            console.log(rs.address);//地址信息
            address = rs.address;
            // alert("点击位置：" + rs.address);
            // 数据传送到qml端
            window.webObject.addPoint(address, lng, lat);
        });
    });

    // longpress事件
    // map.addEventListener("longpress", function (e) {
    //     // 经度
    //     lng = e.latlng.lng;
    //     // 纬度
    //     lat = e.latlng.lat;
    //     // 创建点标记
    //     var end_pos_marker = new BMapGL.Marker(new BMapGL.Point(lng, lat));
    //     // 在地图上添加点标记
    //     map.addOverlay(end_pos_marker);
    //     end_pos_marker.disableMassClear();
    //     // alert("长按位置经纬度：" + lng + "," + lat);
    //     // 数据传送到qml端
    //     window.webObject.addPoint(lng, lat);

    // });
}

// 规划驾车路线
function driving_route() {
    if(_Bridge == "" || _Bridge == null || _Bridge == undefined) {
        // alert("js与QT桥未初始化");
        return;
    }
    window.webObject.sendCurvePath.connect(function (data) {
        // alert("points.size: " + data.length);
        for (let i = 0; i < data.length; i++) {
            // alert("points："+ data[i][0] + ", " + data[i][1]);
            var point = new BMapGL.Point(data[i][0], data[i][1]);
            curve_paths.push(point);
            point = null;
            delete point;
        }
        removePath();
        if (curve_paths.length > 1) {
            drawPath();
        }
    });
}

// 绘制路线
function drawPath() {
    //绘制箭头及其样式
    // var sy = new BMapGL.Symbol(BMap_Symbol_SHAPE_BACKWARD_OPEN_ARROW, {
    //     scale: 0.6,//图标缩放大小
    //     strokeColor:'#fff',//设置矢量图标的线填充颜色
    //     strokeWeight: 2,//设置线宽
    // });
    // var icons = new BMapGL.IconSequence(sy, '100%', '10%',false);//设置为true，可以对轨迹进行编辑
    //绘制折线以及样式
    var trackLine = new BMapGL.Polyline(curve_paths, {
        strokeColor: "#4299FF",//设置颜色
        strokeWeight: 6,//宽度
        strokeOpacity: 0.8,//折线的透明度，取值范围0 - 1
        enableEditing: false,//是否启用线编辑，默认为false
        enableClicking: false,//是否响应点击事件，默认为true
        icons: []
    });
    map.addOverlay(trackLine);
    // 清除
    curve_paths = []
}

// 删除之前的点
function removePoint() {
    window.webObject.clearPoint.connect(function () {
        var allOverlay = map.getOverlays();
        for(var i = 0; i < allOverlay.length; i++) {
            allOverlay[i].enableMassClear();
        }
        // map.clearOverlays();
    });
}

// 删除上次的轨迹
function removePath() {
    var allOverlay = map.getOverlays();
    map.clearOverlays();
    // for(var i = 0; i < allOverlay.length - 1; i++) {
    //     // if(allOverlay[i].toString().indexOf("Marker") > 0) { // 删除标记点
    //     //     map.removeOverlay(allOverlay[i]);
    //     // }

    //     // if(allOverlay[i].toString().indexOf("Polyline") > 0) { // 删除标折线
    //     //     map.removeOverlay(allOverlay[i]);
    //     // }
    //     map.removeOverlay(allOverlay[i]);
    // }
    // 对每个marker恢复操作
    allOverlay = map.getOverlays();
    for(var i = 0; i < allOverlay.length; i++) {
        allOverlay[i].enableMassClear();
    }
}

// bd sdk路线
function driving() {
    var p1 = new BMapGL.Point(121.41575401095938,31.178363242497223);
    var p2 = new BMapGL.Point(121.42097598557932,31.173485491838004);
    var driving = new BMapGL.DrivingRoute(map, { renderOptions: { map: map, autoViewport: true } });
    driving.search(p1, p2);
}

// window.onload = loadJScript; // 异步加载地图