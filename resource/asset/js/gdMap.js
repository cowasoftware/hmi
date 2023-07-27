// 全局变量
var map = null;
var  _Bridge = null;//全局变量  _Bridge
var  _QWebChannel = null;//全局变量 QWebChannel
// var _WebObject = null;
var curr_pos = new Array(); // 当前位置
var curr_point = null;
var start_pos_marker;
var curve_paths = [];    // 路径上的点
let img_url = "../image/autodrive/map_icon/navigation_icon.png"
var map = null;
var centerPoint = null;
var myIcon = null;
let canRemove = true; // 覆盖物是否可清除
let iconWidth = 100;
let iconHeight = 100;

function onApiLoaded() {
    // 1.1、初始化地图对象，加载地图
    centerPoint = [121.408871,31.171342]  // 创建点坐标 (华鑫慧享城)
    map = new AMap.Map("container", {
        center: centerPoint,
        viewMode: '2D',
        zoom: 18,
        animateEnable: false,
        doubleClickZoom: false,
        zoomEnable: false,
        dragEnable: false,
        mapStyle: "amap://styles/37eb17497ca83953af7afcbb3e02bab2",
    });
    // 缩放控件
    // map.plugin(["AMap.ToolBar"], function() {
    //     map.addControl(new AMap.ToolBar({
    //         position: {
    //             top: '110px',
    //             right: '40px'
    //         }
    //     }));
    // });
    // 1.2、创建一个自定义icon
    myIcon = new AMap.Icon({
        // 图标尺寸
        // size: new AMap.Size(40, 40),
        // 图标的取图地址
        image: img_url,
        // 图标所用图片大小
        imageSize: new AMap.Size(iconWidth, iconHeight),
        // 图标取图偏移量
        // imageOffset: new AMap.Pixel(-9, -3)
    });
    // 1.3、添加定位组件
    addMyControl();

    map.on('dblclick', addPoint);
    try {
        _QWebChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
            _Bridge = channel.objects.webObject;
            window.webObject = _Bridge;
            // 增加事件监听
            // map.on('dblclick', addPoint);
            // 2.1 接收主车位置
            window.webObject.sendCurrentPos.connect(markCurrentPos);
            // 2.3 接收驾车路线
            window.webObject.sendCurvePath.connect(drivingRoute);
            // 清除上次的轨迹
            window.webObject.clearPoint.connect(() => {
                canRemove = true;
                curve_paths = [];
                if (canRemove) {
                    map.clearMap();
                    // 重新添加marker
                    map.add(start_pos_marker);
                    canRemove = false;
                }
            });
            // 标记目的地
            window.webObject.markDestination.connect(markDestination);
            // 定位到当前位置
            window.webObject.locate.connect(() => {
                if(curr_point == null) {
                    map.panTo(centerPoint);
                } else {
                    map.panTo(curr_point);
                }
            });
        });
    } catch(e) {
        console.error("init error!!!");
    }
}

// 添加定位组件
function addLocationControl() {
    var options = {
        'showButton': true,//是否显示定位按钮
        'position': 'RB',//定位按钮的位置
        /* LT LB RT RB */
        'offset': [32, 170],//定位按钮距离对应角落的距离
        'showMarker': true,//是否显示定位点
        'convert': true,
        'panToLocation ': true,
        'timeout': 500,
        'markerOptions':{//自定义定位点样式，同Marker的Options
          'offset': new AMap.Pixel(-18, -36),
          'content':'<img src="https://a.amap.com/jsapi_demos/static/resource/img/user.png" style="width:36px;height:36px"/>'
        },
        'borderRadius': '5px',
        'buttonSize': '12px',
        'showCircle': true,//是否显示定位精度圈
        'circleOptions': {//定位精度圈的样式
            'strokeColor': '#0093FF',
            'noSelect': true,
            'strokeOpacity': 0.5,
            'strokeWeight': 1,
            'fillColor': '#02B0FF',
            'fillOpacity': 0.25
        }
    }
    AMap.plugin(["AMap.Geolocation"], function() {
        var geolocation = new AMap.Geolocation(options);
        map.addControl(geolocation);
        geolocation.getCurrentPosition(function(status,result){
            console.log(status);
            console.log(result.position);
            if(status=='complete'){
                console.log("定位成功，当前位置：" + result.position);
                // map.setZoomAndCenter(18, result.position, true);
            }else{
                // 自动定位失败则移动到主车位置
                if (curr_point != null) {
                    map.panTo(curr_point);
                } else {
                    map.panTo(point);
                }
            }
        });
    });
}

function AMapLocationPlug() {            
    AMap.locateControlDiv.prototype = {  
        addTo: function(map, dom){  
           dom.appendChild(this._getHtmlDom(map));  
        },
        _getHtmlDom:function(map){                  
          this.map=map;                  
          // 创建一个能承载控件的<div>容器                  
          var controlUI = document.createElement("location_control");                  
          controlUI.style.width ='80px';     //设置控件容器的宽度  
          controlUI.style.height ='20px';    //设置控件容器的高度                  
          controlUI.style.backgroundColor ='white';                     
          controlUI.style.borderStyle ='solid';                  
          controlUI.style.borderWidth ='2px';                  
          controlUI.style.cursor ='pointer';                  
          controlUI.style.textAlign ='center';                   
                     
          // 设置控件的位置                   
          controlUI.style.position ='absolute';                  
          controlUI.style.left ='120px';     //设置控件离地图的左边界的偏移量                  
          controlUI.style.top ='5px';        //设置控件离地图上边界的偏移量                  
          controlUI.style.zIndex ='300';     //设置控件在地图上显示                  
                     
       // 设置控件字体样式                  
          controlUI.style.fontFamily ='Arial,sens-serif';                  
          controlUI.style.fontSize ='12px';                  
          controlUI.style.paddingLeft ='4px';                  
          controlUI.style.paddingRight ='4px';                  
          controlUI.innerHTML ="返回中心";                  
                     
          // 设置控件响应点击onclick事件                  
          controlUI.onclick = function(){                  
             map.setCenter(new AMap.LngLat(116.404, 39.915));                  
          }                  
          return controlUI;                  
        }                  
     }
}

// 添加自定义控件
function addMyControl() {
    function ZoomControl() {
        // 默认停靠位置和偏移量
	    this.defaultAnchor = 'RB';
	    this.defaultOffset = new AMap.Size(32, 190);
    }
    var options = {
        position: 'RB',
        offset: new AMap.Pixel(32, 190)
    }
    // 通过JavaScript的prototype属性继承于BMap.Control
	ZoomControl.prototype = new AMap.Control(options);
    // 自定义控件必须实现自己的initialize方法,并且将控件的DOM元素返回
    ZoomControl.prototype.addTo = function(map){
        // 创建一个DOM元素
        var div = document.createElement("location_control");
        // 设置样式
        // div.style.cursor = "pointer";
        // div.style.border = "1px solid gray";
        // 设置控件的位置                   
        div.style.position ='absolute';                  
        div.style.right ='400px';     //设置控件离地图的右边界的偏移量                  
        div.style.bottom ='84px';   //设置控件离地图上边界的偏移量                  
        div.style.zIndex ='300';     //设置控件在地图上显示 

        div.style.width = "166px";
        div.style.height = "76px";
        div.style.backgroundImage = "url('../image/autodrive/dashboard/position.png')";
        // 绑定事件,点击一次放大两级
        div.onclick = function(e){
            // 定位当前位置
            if(curr_point == null) {
                map.panTo(centerPoint);
            } else {
                map.panTo(curr_point);
            }
        }
        // 添加DOM元素到地图中
        var node = map.getContainer();
        node.appendChild(div);
        // 将DOM元素返回
        return div;
    }
      // 创建控件
      var myZoomCtrl = new ZoomControl();
      // 添加到地图当中
      map.addControl(myZoomCtrl);
}

// 接收到qml的点，标记目的地
function markDestination(x, y) {
    // 创建点标记
    // 点标记显示内容，HTML要素字符串
    var point = new AMap.LngLat(x, y);
    console.log("destination: ", point);
    var markerContent = '' +
    '<div class="custom-content-marker">' +
    '   <img src="https://a.amap.com/jsapi_demos/static/demo-center/icons/poi-marker-red.png" width="25" height="34">' +
    '</div>';
    var end_pos_marker = new AMap.Marker({
        position: point,
        // 将 html 传给 content
        content: markerContent,
        icon: new AMap.Icon({
            // size: new AMap.Size(25, 34),
            image: 'https://a.amap.com/jsapi_demos/static/demo-center/icons/poi-marker-red.png',
            imageSize: new AMap.Size(25, 34)
        }),
        anchor: 'bottom-center',
    });
    map.add(end_pos_marker);
}

// 添加点
function addPoint(e) {
    if(window.webObject.cancleClickEvent == true) {
        return;   
    }
    // 鼠标选点
    var address;
    var lng = e.lnglat.getLng();
    var lat = e.lnglat.getLat();
    var point = new AMap.LngLat(lng, lat);
    console.log("点击位置: [" + point + "]");
    console.log("canRemove: ", canRemove);
    // 先移除所有覆盖物
    if (canRemove) {
        map.clearMap();
        canRemove = false;
    }
    // 创建点标记
     // 点标记显示内容，HTML要素字符串
     var markerContent = '' +
     '<div class="custom-content-marker">' +
     '   <div class="close-btn">X</div>' +
     '   <img src="https://a.amap.com/jsapi_demos/static/demo-center/icons/poi-marker-red.png" width="25" height="34">' +
     '</div>';
    var end_pos_marker = new AMap.Marker({
        position: point,
         // 将 html 传给 content
        content: markerContent,
        icon: new AMap.Icon({
            // size: new AMap.Size(25, 34),
            image: 'https://a.amap.com/jsapi_demos/static/demo-center/icons/poi-marker-red.png',
            imageSize: new AMap.Size(25, 34)
        }),
        anchor: 'bottom-center',
    });
    end_pos_marker.on('click', removePoint);
    map.add(end_pos_marker);
    // map.setFitView();   // 根据地图上添加的覆盖物分布情况，自动缩放地图到合适的视野级别
    var geocoder;
    map.plugin(["AMap.Geocoder"], function() { //加载地理编码插件
        geocoder = new AMap.Geocoder({
            city: "021", 
            radius: 1000 //范围，默认：500
        });
        geocoder.getAddress(point, (status, result) => {
            console.log(result.regeocode.addressComponent.building);
            if (status === 'complete'&&result.regeocode) {
                console.log(result.regeocode);
                address = result.regeocode.formattedAddress;
                console.log(address);
            }else{
                console.error('根据经纬度查询地址失败');
            }
            // 数据传送到qml端
            window.webObject.addPoint(address, lng, lat);
        });
    });
}
// 删除选中的点
function removePoint() {
    var point = this.getPosition();
    console.log("remove point: [" + point + "]");
    this.remove();
    // 数据传送到qml端
    window.webObject.removePoint(point.getLng(), point.getLat());
}

// 标记主车位置
function markCurrentPos(curr_x, curr_y) {
    // 接收主车位置
    if(_Bridge == "" || _Bridge == null || _Bridge == undefined) {
        console.error("js与QT桥未初始化");
        return;
    }
    curr_pos = [];
    curr_pos.push(curr_x);
    curr_pos.push(curr_y);
    last_point = curr_point;
    // 先清除上一次的当前位置
    // if (start_pos_marker != null || start_pos_marker != undefined) {
    //     start_pos_marker.remove();
    // }
    // TODO 创建点标记
    curr_point = new AMap.LngLat(curr_x, curr_y);
    map.panTo(curr_point);
    if(start_pos_marker == null || start_pos_marker == undefined) {
        // 将 icon 传入 marker
        start_pos_marker = new AMap.Marker({
            position: curr_point,
            icon: myIcon,
            offset: new AMap.Pixel(-iconWidth/2, -iconHeight / 2)
        });
        // 将 markers 添加到地图
        map.add(start_pos_marker);
    } else {
        start_pos_marker.setPosition(curr_point);
    }
    // curr_point = null;
    // delete curr_point;
}

// 规划驾车路线
function drivingRoute(data) {
    if(_Bridge == "" || _Bridge == null || _Bridge == undefined) {
        console.error("js与QT桥未初始化");
        return;
    }
    log.info("points.size: " + data.length);
    for (let i = 0; i < data.length; i++) {
        // alert("points："+ data[i][0] + ", " + data[i][1]);
        var point = new AMap.LngLat(data[i][0], data[i][1]);
        curve_paths.push(point);
        point = null;
        delete point;
    }
    if (curve_paths.length > 1) {
        drawPath();
    }
    // 清除数组
    canRemove = true;
    curve_paths = [];
}

// 绘制路线
function drawPath() {
    //绘制折线以及样式
    var trackLine = new AMap.Polyline({
        path: curve_paths,
        isOutline: true,
        outlineColor: '#2B71FF',
        borderWeight: 4,
        strokeColor: "#42B0FF",//设置颜色
        strokeWeight: 8,//宽度
        strokeOpacity: 0.8,//折线的透明度，取值范围0 - 1
        strokeStyle: "solid",
        lineJoin: 'round',
        lineCap: 'round',
        zIndex: 50,
    });
    map.add(trackLine);
    // map.setFitView();
}

// 删除上次的轨迹
function removePath() {
    var allOverlay = map.getOverlays();
    map.clearOverlays();
    // 对每个marker恢复操作
    allOverlay = map.getOverlays();
    for(var i = 0; i < allOverlay.length; i++) {
        allOverlay[i].enableMassClear();
    }
}