import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Cowa.HMI2.Model 1.0

Control {
    id: control
    background: Rectangle {
        color: "#214F85"
    }
    contentItem: ColumnLayout {
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 272
            Layout.topMargin: 40
            Rectangle {
                Layout.preferredWidth: 336
                Layout.preferredHeight: 60
                radius: 12
                color: "#2780FF"
                border.color: "#51B6FF"
                border.width: 2
                Text {
                    anchors.centerIn: parent
                    text: vmodel.name
                    font.pixelSize: 32
                    font.weight: Font.Medium
                    font.family: ""
                    color: "#FFFFFF"
                }
            }
            ColumnLayout {
                Layout.preferredWidth: 336
                Layout.topMargin: 0
                Layout.bottomMargin: 24
                spacing: 12
                RowLayout {
                    Layout.leftMargin: 20
                    Image {
                        Layout.preferredWidth: 24
                        Layout.preferredHeight: 24
                        source: "qrc:/resource/asset/image/autodrive/icon/Subtract.png"
                    }
                    Text {
                        font.pixelSize: 24
                        text: qsTr("下一站")
                        color: "#FFFFFF"
                    }
                }
                Text {
                    Layout.preferredWidth: 300
                    Layout.preferredHeight: 60
                    Layout.leftMargin: 20
                    font.pixelSize: 40
                    text: vmodel.nextStation.name
                    elide: Text.ElideRight
                    color: "#FFFFFF"
                }
            }
        }
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 376
            Layout.fillHeight: true
            color: "#EEF5FF"
            radius: 12
            Rectangle {
                width: parent.width
                height: parent.radius
                color: parent.color
                anchors.bottom: parent.bottom
            }
            ListView {
                id: listView
                currentIndex: vmodel.currentStationIndex
                preferredHighlightBegin: height * 0.2
                preferredHighlightEnd: preferredHighlightBegin
                highlightRangeMode: ListView.ApplyRange
                boundsBehavior: ListView.StopAtBounds
                anchors.fill: parent
                model: vmodel.stations
                delegate: Control {
                    property ListView view: ListView.view
                    id: indicator
                    width: ListView.view.width
                    height: 72
                    leftPadding: 40
                    contentItem: RowLayout {
                        spacing: 24
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 4
                            Rectangle {
                                width: parent.width
                                height: parent.height / 2
                                anchors.top: parent.top
                                visible: index !== 0
                                color: view.currentIndex >= index ? "#2780FF" : "#8DA0B6DB"
                            }
                            Rectangle {
                                width: parent.width
                                height: parent.height / 2
                                anchors.bottom: parent.bottom
                                color: view.currentIndex > index ? "#2780FF" : "#8DA0B6DB"
                                visible: index !== view.count - 1
                            }
                            Loader {
                                Component {
                                    id: targetDelegate
                                    Rectangle {
                                        width: 16
                                        height: 16
                                        radius: 8
                                        color: "#FFFFFF"
                                        border.width: 3
                                        border.color: "#2780FF"
                                    }
                                }
                                Component {
                                    id: stayDelegate
                                    Rectangle {
                                        width: 24
                                        height: 24
                                        radius: 12
                                        color: "#FFFFFF"
                                        Rectangle {
                                            width: 16
                                            height: 16
                                            radius: 8
                                            color: "#2780FF"
                                            border.width: 3
                                            border.color: "#68A5FF"
                                            anchors.centerIn: parent
                                        }
                                    }
                                }
                                Component {
                                    id: passDelegate
                                    Rectangle {
                                        width: 14
                                        height: 14
                                        radius: 7
                                        color: "#8DA0B6DB"
                                    }
                                }
                                anchors.centerIn: parent
                                sourceComponent: order === vmodel.currentStation.order ? stayDelegate : (order < vmodel.currentStation.order ? passDelegate : targetDelegate)
                            }
                        }
                        Text {
                            text: name
                            font.pixelSize: 28
                            color: order === vmodel.nextStation.order ? "#D82929" : (order < vmodel.currentStation.order ? "#8DA0B6" : "#333333")
                        }
                    }
                }
                clip: true
            }
        }
    }

    RealtimeRouteModel {
        id: vmodel
    }
}
