import QtQuick 2.15
import ConfigClass 1.0

Item {
    id: rootid
    // width: 1446 * gConfig.resolution_ratio;
    // height: 960 / gConfig.resolution_ratio;
    width: 1446;
    height: 960;
    property int currentIndex: gConfig.currentIndex

    /* 版本升级 */
    // Rectangle {
    //     id: upgrade
    //     width: 1446
    //     height: 960
    //     // color: "#2b2b2b"
    //     color: gConfig.background[currentIndex]
    //     Text {
    //         id: version_upgrade_label
    //         text: qsTr("当前版本为最新版本")
    //         width: 319 * gConfig.resolution_ratio
    //         height: 50 / gConfig.resolution_ratio
    //         x: 66
    //         y: 40
    //         color: gConfig.textColor[currentIndex]
    //         font.pixelSize: 36
    //         font.styleName: "Regular"
    //     }

    //     Text {
    //         id: version_code_label
    //         text: qsTr("V1.2.5")
    //         width: 137 * gConfig.resolution_ratio
    //         height: 62 / gConfig.resolution_ratio
    //         x: 66
    //         y: 108
    //         color: gConfig.textColor[currentIndex]
    //         font.pixelSize: 44
    //         font.styleName: "Regular"
    //     }
    // }

    Rectangle {
        width: parent.width
        height: parent.height
        color: gConfig.background[currentIndex]
        // color: "#ffffff"

        Loader {
            id: version_upgrade_id
            width: parent.width
            height: parent.height
            source: "qrc:///resource/qml/setting/upgrade_items.qml"
        }
    }

    // TODO 测试不同版本
    // Text {
    //     id: version_code_label
    //     text: qsTr("TEST")
    //     width: 137
    //     height: 62
    //     x: 620
    //     y: 500
    //     color: gConfig.textColor[currentIndex]
    //     font.pixelSize: 44
    //     font.styleName: "Regular"
    // }

}
