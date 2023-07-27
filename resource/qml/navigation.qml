import QtQuick 2.0
//import QtWebView 1.1

Item {
    width: 1770
    height: 1080

    Text {
        id: text1
        x: 338
        y: 250
        width: 872
        height: 358
        text: qsTr("navigation on the way...")
        font.pixelSize: 30
        font.styleName: "Regular"
    }
    //  WebView{
    //        id:webView
    //        anchors.centerIn: parent
    //        width: parent.width
    //        height: parent.height
    //        url:"qrc:///resource/asset/html/index.html";
    //        onLoadProgressChanged: {
    //            if(webView.loadProgress == 100){
    //                console.log("Load Completed !");
    //                var queryStr = "setText();";
    //                webView.runJavaScript(queryStr,function(result){console.log(result);});
    //            }
    //        }
    //    }


}
