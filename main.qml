import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4

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
    Row{
        spacing: parent.width * .05
        x: terminal.width + parent.width * .05
        y: parent.height * 0.05
        Button{
            width: 50
            height: 50
            font.pointSize: 10
            text: "Silent"
        }

        Button{
            width: 50
            height: 50
            font.pointSize: 10
            text: "Normal"
        }

        Button{
            width: 50
            height: 50
            font.pointSize: 10
            text: "Cool"
        }
    }
}
