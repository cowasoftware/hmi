import QtQuick 2.0
//import QtWebView 1.1
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15
import App.RtspPlayer 1.0

Control {
    width: 1770
    height: 1080

    // RtspPlayer {
    //     id: player
    //     // url: "rtsp://118.25.144.84:8554/live/testa"
    //     // url: "/home/cowa/Works/tboxhmi/resource/asset/videos/dump.h264"
    //     url: appDir + "/dump.h264"
    //     onStatusChanged: {
    //         console.log("**************url状态改变")
    //         if (status === RtspPlayer.Loaded) {
    //             play()
    //         }
    //     }
    // }

    RtspPlayer {
        id: player
        Component.onCompleted: {
            // play()
        }
    }

    contentItem: ColumnLayout {
        spacing: 0
        VideoOutput {
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: player
            fillMode: VideoOutput.PreserveAspectCrop
        }
    }

    Component.onDestruction: {
        console.log("********the reverse image page is destroyed!!!!******")
        player.loadPage(false)
        player.destroy()
    }

    Connections {
        target: window
        function onLoadReverseImage()
        {
            player.loadPage(true)
        }
    }

}
