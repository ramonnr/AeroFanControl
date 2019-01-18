import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtCharts 2.3
import QtGraphicalEffects 1.0

Window {
    id: root
    visible: true
    width: 320
    height: 240
    flags: Qt.FramelessWindowHint
    title: qsTr("Gigabyte Embedded Controller Manipulator")
    color: "Transparent"

    Connections{
        target: ECData
        onWarning:{
            var comp = Qt.createComponent("qrc:/Warning.qml")
            var comp2 = comp.createObject(root,{
                                              "parent":root,
                                              "title": title,
                                              "text": body
                                          })
            comp2.open()
        }
    }

    function moveWindow(pos){
        root.x += pos.x
        root.y += pos.y
    }

    Rectangle{
        id: background
        anchors.fill:parent
        anchors.margins: 0
        radius: 10
        color:"white"
    }
    //LinearGradient{
    //    anchors.fill: parent
    //    start: Qt.point(0,0)
    //    end: Qt.point(root.width,root.height)
    //    gradient:Gradient{
    //        GradientStop{position: 0.0; color: "Gray"}
    //        GradientStop{position: 1.0; color: "Black"}
    //    }
    //}
    FanGraph{
        anchors.left:terminal.right
        anchors.top: fanmode.bottom
        anchors.margins:10
        width:parent.width - terminal.width
        height: parent.height - fanmode.height
    }
    MouseArea{
        id: windowDrag
        anchors.fill: parent
        pressAndHoldInterval: 50
        property bool dragActive: false
        property int dragX
        property int dragY
        onPressAndHold: {
            dragActive = true
            dragX = mouseX
            dragY = mouseY
        }
        onMouseXChanged: {
            if(dragActive){
                moveWindow(Qt.point(mouseX - dragX,0))
            }
        }
        onMouseYChanged: {
            if(dragActive){
                moveWindow(Qt.point(0, mouseY - dragY))
            }
        }
        onReleased: {
            dragActive = false
        }
    }
    EcTerminal{
        id: terminal
        width: 100
        height: parent.height
        radius:10
    }
    FanModes{
        id: fanmode
        anchors.left: terminal.right
        width: root.width - terminal.width
        height: 60
    }

}
