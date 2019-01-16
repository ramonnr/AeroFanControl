import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtCharts 2.3

Window {
    id: root
    visible: true
    width: 320
    height: 240
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    title: qsTr("Gigabyte Embedded Controller Manipulator")
    color: "#00000000"
    function moveWindow(pos){
        root.x += pos.x
        root.y += pos.y
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
    Rectangle{
        id: outline
        width: root.width
        height: root.height
        border.color:"Black"
        color:"transparent"
    }
    EcTerminal{
        id: terminal
        width: 100
        height: parent.height
    }
    FanModes{
        id: fanmode
        anchors.left: terminal.right
        width: root.width - terminal.width
        height: 60//root.height
    }
    ChartView{
        //title: "line"
        anchors.top: fanmode.bottom
        anchors.left: terminal.right
        width: parent.width - terminal.width
        height: parent.height - fanmode.height
        backgroundColor: "transparent"
        LineSeries {
            name: "wat  "
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
        }
    }
}
