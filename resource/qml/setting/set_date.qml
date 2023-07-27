import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1


//日期设置
Item {

    property string yval: ""
    property string mval: ""
    property string dval: ""
    property string hval: ""
    property string minval: ""
    property string sval: ""
    property bool sflag: false
    width: 1446
    height: 960
    Rectangle {
            id: date_title_id
            x: 0
            y: 0
            width: 1446
            height: 120
            color: "#4f4f4f"

            Text {
                id: text1
                x: 48
                y: 38
                width: 288
                height: 45
                color: "#ffffff"
                text: qsTr("使用网络提供的时间")
                font.pixelSize: 32
                font.styleName: "Regular"
                horizontalAlignment : Text.AlignHCenter
            }


            // 开关
            Switch {
                id: left_switch_id
                x: 1158
                y: 30
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: left_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: left_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        if (left_switch_id.checked)
                        {
                            sflag = true
                        }else
                        {
                            sflag = false
                        }
                    }

                    Rectangle {
                        x: left_switch_id.checked ? parent.width - width - 2 : 1
                        width: left_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                }
            }
        }

    Rectangle {
        id: set_datetime_id
        x: 0
        y: 120
        width: 1446
        height: 840
        color: "#2b2b2b"

        Text {
            id: text2
            x: 310
            y: 68
            width: 128
            height: 45
            color: !sflag ? "#ffffff" : "#8b8b8b"
            text: qsTr("设置日期")
            font.pixelSize: 32
            font.styleName: "Regular"
        }

        Text {
            id: text3
            x: 998
            y: 68
            width: 128
            height: 45
            color: !sflag ? "#ffffff" : "#8b8b8b"
            text: qsTr("设置时间")
            font.pixelSize: 32
            font.styleName: "Regular"
        }

        Rectangle {
            id: set_date_id
            x: 124
            y: 153
            width: 500
            height: 600
            color: "#3b3b3b"

            Rectangle {
                id: date_show_id
                width: 500
                height: 88
                color: "#4f4f4f"

                Rectangle {
                    x: 141
                    y: 27
                    width: 221
                    height: 34
                    color: "#4f4f4f"
                    Text {
                        id: select_date_show_id
                        color: "#ffffff"
                        text: qsTr(yval+"年"+mval+"月"+dval+"日"+"星期"+sval)
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                }
            }

            //select date
            ListModel{
                 id: listmodel_year
                 // ListElement{yname:"2003"} ListElement{yname:"2004"}    ListElement{yname:"2005"}    ListElement{yname:"2006"} ListElement{yname:"2007"}
                  ListElement{yname:"2008"} ListElement{yname:"2009"}    ListElement{yname:"2010"}    ListElement{yname:"2011"} ListElement{yname:"2012"}
                  ListElement{yname:"2013"} ListElement{yname:"2014"}    ListElement{yname:"2015"}    ListElement{yname:"2016"} ListElement{yname:"2017"}
                  ListElement{yname:"2018"} ListElement{yname:"2019"}    ListElement{yname:"2020"}    ListElement{yname:"2021"} ListElement{yname:"2022"}
                  ListElement{yname:"2023"} ListElement{yname:"2024"}    ListElement{yname:"2025"}    ListElement{yname:"2026"} ListElement{yname:"2027"}
                  ListElement{yname:"2028"} ListElement{yname:"2029"}    ListElement{yname:"2030"}    ListElement{yname:"2031"} ListElement{yname:"2032"}
                  ListElement{yname:"2033"} ListElement{yname:"2034"}    ListElement{yname:"2035"}    ListElement{yname:"2036"} ListElement{yname:"2037"}
             }
             Component{
                 id: com_delegate_year
                 Column{
                     id: wrapper_year
                     Text {
                         id: nameText
                         text: yname
                         font.pixelSize: wrapper_year.PathView.isCurrentItem ? 36 : 30
                         color: wrapper_year.PathView.isCurrentItem && !sflag ? "#5b89ff" : "#a9a9a9"
                         onColorChanged: {
                             yval = yname
                             countWeekDay(yval, mval, dval)

                         }
                     }

                 }

             }
             ListModel{
                 id:listmodel_start_month
                 ListElement{startmname:"01"}  ListElement{startmname:"02"}  ListElement{startmname:"03"}  ListElement{startmname:"04"}  ListElement{startmname:"05"}
                 ListElement{startmname:"06"}  ListElement{startmname:"07"}  ListElement{startmname:"08"}  ListElement{startmname:"09"}  ListElement{startmname:"10"}
                 ListElement{startmname:"11"}  ListElement{startmname:"12"}
             }
             Component{
                 id: com_delegate_start_month
                 Column{
                     id: wrapper_start_month
                     Text {
                         id: txt_home_date_start_month
                         text: startmname
                         font.pixelSize: wrapper_start_month.PathView.isCurrentItem ? 36 : 30
                         color: wrapper_start_month.PathView.isCurrentItem && !sflag ? "#5b89ff" : "#a9a9a9"
                         onColorChanged: {
                             mval = startmname
                             countWeekDay(yval, mval, dval)
                         }
                     }
                 }
             }
             ListModel{
                 id: listmodel_start_day
                 ListElement{startdname:"01"}    ListElement{startdname:"02"}    ListElement{startdname:"03"}    ListElement{startdname:"04"}    ListElement{startdname:"05"}
                 ListElement{startdname:"06"}    ListElement{startdname:"07"}    ListElement{startdname:"08"}    ListElement{startdname:"09"}    ListElement{startdname:"10"}
                 ListElement{startdname:"11"}    ListElement{startdname:"12"}    ListElement{startdname:"13"}    ListElement{startdname:"14"}    ListElement{startdname:"15"}
                 ListElement{startdname:"16"}    ListElement{startdname:"17"}    ListElement{startdname:"18"}    ListElement{startdname:"19"}    ListElement{startdname:"20"}
                 ListElement{startdname:"21"}    ListElement{startdname:"22"}    ListElement{startdname:"23"}    ListElement{startdname:"23"}    ListElement{startdname:"25"}
                 ListElement{startdname:"26"}    ListElement{startdname:"27"}    ListElement{startdname:"28"}    ListElement{startdname:"29"}    ListElement{startdname:"30"}
                 ListElement{startdname:"31"}
             }
             Component{
                 id: com_delegate_start_day
                 Column{
                     id: wrapper_start_day
                     Text {
                         id: txt_home_date_start_day
                         text: startdname
                         font.pixelSize: wrapper_start_day.PathView.isCurrentItem ? 36 : 30
                         color: wrapper_start_day.PathView.isCurrentItem && !sflag? "#5b89ff" : "#a9a9a9"
                         onColorChanged: {
                             dval = wrapper_start_day.PathView.isCurrentItem ? startdname : dval
                             countWeekDay(yval, mval, dval)
                         }
                     }
                 }
             }

             Rectangle{//起始年
                 id:rec_home_date_start_year
                 width: 87
                 height: 411
                 x: 60
                 y: 88
                 color: "#3b3b3b"
                 PathView{
                     id: pathview_start_year
                     anchors.fill: parent
                     model:listmodel_year
                     delegate: com_delegate_year
                     pathItemCount: 5
                     preferredHighlightBegin: 0.5
                     preferredHighlightEnd: 0.5
                     path: Path{
                         startX: 44
                         startY: 23
                         PathLine{x:44; y:93}
                         PathLine{x:44; y:163}
                         PathLine{x:44; y:233}
                         PathLine{x:44; y:303}
                         PathLine{x:44; y:373}
                     }
                     onCurrentIndexChanged: {
                         if ((currentIndex + 2019)%4 == 0)//润年
                         {
                             if (pathview_start_month.currentIndex == 1 && listmodel_start_day.count == 28)//2月
                             {
                                 listmodel_start_day.insert(28, {startdname:"29"})
                             }
                         }else{
                             if (pathview_start_month.currentIndex == 1 && listmodel_start_day.count == 29)//2月
                             {
                                 listmodel_start_day.remove(28)
                             }
                         }
                     }
                 }

             }
             Rectangle{//year label
                 id: label_home_date_start_year
                 x: 159
                 y: 268
                 width: 20
                 height: 28
                 color: "#3b3b3b"
                 Text {
                     color: !sflag ? "#5b89ff" : "#a9a9a9"
                     text: qsTr("年")
                     font.pixelSize: 20
                     font.styleName: "Regular"

                 }
             }

             Rectangle{//起始月
                 id: rec_home_date_start_month
                 height: 411
                 width: 44
                 x: 250
                 y: 88
                 color: "#3b3b3b"

                 PathView{
                     id: pathview_start_month
                     anchors.fill: parent
                     model: listmodel_start_month
                     delegate: com_delegate_start_month
                     pathItemCount: 5
                     preferredHighlightBegin: 0.5
                     preferredHighlightEnd: 0.5
                     path: Path{
                         startX: 22
                         startY: 23
                         PathLine{x:22; y:93}
                         PathLine{x:22; y:163}
                         PathLine{x:22; y:233}
                         PathLine{x:22; y:303}
                         PathLine{x:22; y:373}
                     }
                     onCurrentIndexChanged: {//
                         //console.log("取余：  " + (pathview_start_year.currentIndex + 2019)%4)
                         if (currentIndex == 1)//2月
                         {//2月上下都为31天
                             if ((pathview_start_year.currentIndex + 2019)%4 == 0)//润年
                             {
                                 listmodel_start_day.remove(30)//31日
                                 listmodel_start_day.remove(29)//30日
                             }else{
                                 listmodel_start_day.remove(30)//31日
                                 listmodel_start_day.remove(29)//30日
                                 listmodel_start_day.remove(28)//29日
                             }
                         }else if (currentIndex == 3 || currentIndex == 5 || currentIndex == 8 || currentIndex == 10){//4、6、9、11月，30天
                             listmodel_start_day.remove(30)//30天这些月份，之前之后的月份都是31天
                         }else if (currentIndex == 0 || currentIndex == 2 || currentIndex == 4 || currentIndex == 6 || currentIndex == 7 || currentIndex == 9 || currentIndex == 11){
                             //1、3、5、7、8、10、12月
                             if (listmodel_start_day.count == 28)
                             {
                                 listmodel_start_day.insert(28, {startdname:"29"})
                                 listmodel_start_day.insert(29, {startdname:"30"})
                                 listmodel_start_day.insert(30, {startdname:"31"})
                             }else if (listmodel_start_day.count == 29){
                                 listmodel_start_day.insert(29, {startdname:"30"})
                                 listmodel_start_day.insert(30, {startdname:"31"})
                             }else if (listmodel_start_day.count == 30){
                                 listmodel_start_day.insert(30, {startdname:"31"})
                             }
                         }
                     }
                 }
             }
             Rectangle{//month label
                 id: label_home_date_start_month
                 x: 303
                 y: 268
                 height: 28
                 width: 20

                 color: "#3b3b3b"
                 Text {
                     color: !sflag ? "#5b89ff" : "#a9a9a9"
                     text: qsTr("月")
                     font.pixelSize: 20
                     font.styleName: "Regular"
                 }
             }
             Rectangle{//起始日
                 id:rec_home_date_start_day
                 x: 396
                 y: 88
                 height: 411
                 width: 44
                 color: "#3b3b3b"

                 PathView{
                     id: pathview_start_day
                     anchors.fill: parent
                     model: listmodel_start_day
                     delegate: com_delegate_start_day
                     pathItemCount: 5
                     preferredHighlightBegin: 0.5
                     preferredHighlightEnd: 0.5
                     path: Path{
                         startX: 22
                         startY: 23
                         PathLine{x:22; y:93}
                         PathLine{x:22; y:163}
                         PathLine{x:22; y:233}
                         PathLine{x:22; y:303}
                         PathLine{x:22; y:373}
                     }
                 }
             }
             Rectangle{//day label
                 id: label_home_date_start_day
                 x: 447
                 y: 268
                 height: 28
                 width: 20
                 color: "#3b3b3b"
                 Text {
                     color: !sflag ? "#5b89ff" : "#a9a9a9"
                     text: qsTr("日")
                     font.pixelSize: 20
                     font.styleName: "Regular"
                 }
             }

            Button{
                id: unselected_id
                x:40
                y:499
                width: 200
                height: 60
                background: Rectangle {
                    color: "#4f4f4f"
                    Text{
                        text: qsTr("取消")
                        anchors.centerIn: parent
                        font.pixelSize: 24
                        font.styleName: "Regular"
                        color: !sflag ? "#ffffff" : "#8b8b8b"
                    }
                }
                onClicked: {
                    if (!sflag)
                    {
                        console.log("取消")
                    }

                }
            }

            Button{
                id: selected_id
                x:261
                y:499
                width: 200
                height: 60
                background: Rectangle {
                    color: !sflag ? "#5b89ff" : "#4f4f4f"
                    Text{
                        text: qsTr("确定")
                        anchors.centerIn: parent
                        font.pixelSize: 24
                        font.styleName: "Regular"
                        color: !sflag ? "#ffffff" : "#8b8b8b"
                    }
                }
                onClicked: {
                    if (!sflag)
                    {
                        console.log("确定")
                        //TODO
                    }
                }
            }
        }

        Rectangle {
            id: set_time_id
            x: 812
            y: 153
            width: 500
            height: 600
            color: "#3b3b3b"

            Rectangle {
                id: time_show_id
                width: 500
                height: 88
                color: "#4f4f4f"

                    Rectangle {
                        x: 200
                        y: 28
                        width: 101
                        height: 34
                        color: "#4f4f4f"
                        Text {
                            id: select_time_show_id
                            color: "#ffffff"
                            text: qsTr(hval+"时"+minval+"分")
                            font.pixelSize: 24
                            font.styleName: "Regular"
                        }
                    }

            }
            //time select
            ListModel{
                 id: listmodel_hour
                  ListElement{hname:"01"} ListElement{hname:"02"}    ListElement{hname:"03"}    ListElement{hname:"04"} ListElement{hname:"05"}
                  ListElement{hname:"06"} ListElement{hname:"07"}    ListElement{hname:"08"}    ListElement{hname:"09"} ListElement{hname:"10"}
                  ListElement{hname:"11"} ListElement{hname:"12"}    ListElement{hname:"13"}    ListElement{hname:"14"} ListElement{hname:"15"}
                  ListElement{hname:"16"} ListElement{hname:"17"}    ListElement{hname:"18"}    ListElement{hname:"19"} ListElement{hname:"20"}
                  ListElement{hname:"21"} ListElement{hname:"22"}    ListElement{hname:"23"}    ListElement{hname:"00"}
             }
             Component{
                 id: com_delegate_hour
                 Column{
                     id: wrapper_hour
                     Text {
                         id: nameText
                         text: hname
                         font.pixelSize: wrapper_hour.PathView.isCurrentItem ? 36 : 30
                         color: wrapper_hour.PathView.isCurrentItem && !sflag? "#5b89ff" : "#a9a9a9"
                         onColorChanged: {
                             hval = hname
                         }
                     }
                 }
             }
             ListModel{
                 id:listmodel_start_minute
                 ListElement{startmname:"01"}  ListElement{startmname:"02"}  ListElement{startmname:"03"}  ListElement{startmname:"04"}  ListElement{startmname:"05"}
                 ListElement{startmname:"06"}  ListElement{startmname:"07"}  ListElement{startmname:"08"}  ListElement{startmname:"09"}  ListElement{startmname:"10"}
                 ListElement{startmname:"11"}  ListElement{startmname:"12"}  ListElement{startmname:"13"}  ListElement{startmname:"14"}  ListElement{startmname:"15"}
                 ListElement{startmname:"16"}  ListElement{startmname:"17"}  ListElement{startmname:"18"}  ListElement{startmname:"19"}  ListElement{startmname:"20"}
                 ListElement{startmname:"21"}  ListElement{startmname:"22"}  ListElement{startmname:"23"}  ListElement{startmname:"24"}  ListElement{startmname:"25"}
                 ListElement{startmname:"26"}  ListElement{startmname:"27"}  ListElement{startmname:"28"}  ListElement{startmname:"29"}  ListElement{startmname:"30"}
                 ListElement{startmname:"31"}  ListElement{startmname:"32"}  ListElement{startmname:"33"}  ListElement{startmname:"34"}  ListElement{startmname:"35"}
                 ListElement{startmname:"36"}  ListElement{startmname:"37"}  ListElement{startmname:"38"}  ListElement{startmname:"39"}  ListElement{startmname:"40"}
                 ListElement{startmname:"41"}  ListElement{startmname:"42"}  ListElement{startmname:"43"}  ListElement{startmname:"44"}  ListElement{startmname:"45"}
                 ListElement{startmname:"46"}  ListElement{startmname:"47"}  ListElement{startmname:"48"}  ListElement{startmname:"49"}  ListElement{startmname:"50"}
                 ListElement{startmname:"51"}  ListElement{startmname:"52"}  ListElement{startmname:"53"}  ListElement{startmname:"54"}  ListElement{startmname:"55"}
                 ListElement{startmname:"56"}  ListElement{startmname:"57"}  ListElement{startmname:"58"}  ListElement{startmname:"59"}  ListElement{startmname:"00"}
             }
             Component{
                 id: com_delegate_start_minute
                 Column{
                     id: wrapper_start_minute
                     Text {
                         id: txt_home_date_start_minute
                         text: startmname
                         font.pixelSize: wrapper_start_minute.PathView.isCurrentItem ? 36 : 30
                         color: wrapper_start_minute.PathView.isCurrentItem && !sflag? "#5b89ff" : "#a9a9a9"
                         onColorChanged: {
                             minval = startmname
                         }
                     }
                 }
             }

             Rectangle{//hour
                 id:rec_home_date_start_hour
                 x: 122
                 y: 88
                 height: 411
                 width: 44
                 color: "#3b3b3b"

                 PathView{
                     id: pathview_start_hour
                     anchors.fill: parent
                     model: listmodel_hour
                     delegate: com_delegate_hour
                     pathItemCount: 5
                     preferredHighlightBegin: 0.5
                     preferredHighlightEnd: 0.5
                     path: Path{
                         startX: 22
                         startY: 23
                         PathLine{x:22; y:93}
                         PathLine{x:22; y:163}
                         PathLine{x:22; y:233}
                         PathLine{x:22; y:303}
                         PathLine{x:22; y:373}
                     }
                 }
             }
             Rectangle{//hour label
                 id: label_home_date_start_hour
                 x: 171
                 y: 268
                 height: 28
                 width: 20
                 color: "#3b3b3b"

                 Text {
                     color: !sflag ? "#5b89ff" : "#a9a9a9"
                     text: qsTr("时")
                     font.pixelSize: 20
                     font.styleName: "Regular"
                 }
             }

             Rectangle{//minute
                 id:rec_home_date_start_minute
                 x: 339
                 y: 88
                 height: 411
                 width: 44
                 color: "#3b3b3b"

                 PathView{
                     id: pathview_start_minute
                     anchors.fill: parent
                     model: listmodel_start_minute
                     delegate: com_delegate_start_minute
                     pathItemCount: 5
                     preferredHighlightBegin: 0.5
                     preferredHighlightEnd: 0.5
                     path: Path{
                         startX: 22
                         startY: 23
                         PathLine{x:22; y:93}
                         PathLine{x:22; y:163}
                         PathLine{x:22; y:233}
                         PathLine{x:22; y:303}
                         PathLine{x:22; y:373}
                     }
                 }
             }
             Rectangle{//minute label
                 id: label_home_date_start_minute
                 x: 395
                 y: 268
                 height: 28
                 width: 20
                 color: "#3b3b3b"
                 Text {
                     color: !sflag ? "#5b89ff" : "#a9a9a9"
                     text: qsTr("分")
                     font.pixelSize: 20
                     font.styleName: "Regular"
                 }
             }



            Button{
                id: unselected_time_id
                x:40
                y:499
                width: 200
                height: 60
                background: Rectangle {
                    color: "#4f4f4f"
                    Text{
                        text: qsTr("取消")
                        anchors.centerIn: parent
                        font.pixelSize: 24
                        font.styleName: "Regular"
                        color: !sflag ? "#ffffff" : "#8b8b8b"
                    }
                }
                onClicked: {
                    if(!sflag)
                    {
                        console.log("取消")

                    }
                }
            }

            Button{
                id: selected_time_id
                x:261
                y:499
                width: 200
                height: 60
                background: Rectangle {
                    color: !sflag ? "#5b89ff" : "#4f4f4f"
                    Text{
                        text: qsTr("确定")
                        anchors.centerIn: parent
                        font.pixelSize: 24
                        font.styleName: "Regular"
                        color: !sflag ? "#ffffff" : "#8b8b8b"
                    }
                }
                onClicked: {
                    if (!sflag)
                    {
                        console.log("确定")
                        //TODO
                    }

                }
            }
        }


    }
    function countWeekDay(ynum, mnum, dnum) { //year, month, day
        //console.log("num1=" + ynum, mnum, dnum)
        var yval = parseInt(ynum)
        var mval = parseInt(mnum)
        var dval = parseInt(dnum)
        if (mval < 3)
        {
            mval += 12
            yval -= 1
        }

        var countNum = parseInt(yval%2000)
        var tmpNum = parseInt(26*(mval+1)/10)
        var sumNum = countNum+parseInt((countNum/4))+(20/4)-2*20+tmpNum+dval-1
        //console.log("countnum = "+parseInt(countNum/4), "tmp ="+ tmpNum, "sumNum ="+sumNum)

        var day = sumNum%7
        //console.log("day = ", day)
        switch(day)
        {
        case 1:
            sval = "一"
            break
        case 2:
            sval = "二"
            break
        case 3:
            sval = "三"
            break
        case 4:
            sval = "四"
            break
        case 5:
            sval = "五"
            break
        case 6:
            sval = "六"
            break
        case 0:
            sval = "日"
            break
        default:
            break
        }

    }
 }
