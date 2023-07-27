import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: camera_element_id
    width: 1446
    height: 860
    // color: "#2b2b2b"
    property int resolution : 0
    property int configIndex: 0
    property var camera_image_url: "qrc:/resource/asset/image/debug/light/camera_loading.png"

    // color: gConfig.background[configIndex]
    color: "#24ED2E"

    Image {
        width: parent.width
        height: 813
        source:  camera_element_id.camera_image_url
        fillMode: Image.PreserveAspectFit
    }
}