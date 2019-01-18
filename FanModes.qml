import QtQuick 2.0
import QtQuick.Controls 2.4
import FanState 1.0
Item{
    id: fanModesRoot

    Component{
        id: pbutton
        Item{
            id: inner
            width: 50
            height: 40
            property int  animDuration: 3000
            property string btext: "notSet"
            property bool selected: false
            Rectangle{
                anchors.fill: parent
                color: "Transparent"
                visible: selected
                opacity: 0.2
                SequentialAnimation on color{
                    loops: Animation.Infinite
                    ColorAnimation {
                        from: Style.terminalText
                        to: "black"
                        duration: animDuration
                    }
                    ColorAnimation{
                        from: "black"
                        to: Style.terminalText
                        duration: animDuration
                    }
                }
            }
            Button{
                width: parent.width * .95
                height: parent.height * .95
                x: parent.x + (parent.width - width)/2
                y: parent.y + (parent.height - height)/2
                text: btext
            }
        }
    }

    Row{
        id: row
        anchors.fill: parent
        anchors.leftMargin: parent.width * .1
        anchors.topMargin: 10//parent.height * .05
        spacing: 10
        FanButton{
            btext: "Silent"
            selected: ECData.mode === FanState.Silent
            onClicked: ECData.setSilent()
        }
        FanButton{
            btext: "Normal"
            selected: ECData.mode === FanState.Normal
            onClicked: ECData.setNormal()
        }
        //TODO - this
        FanButton{
            btext: "Cool"
            selected: ECData.mode === FanState.Cool
            onClicked: ECData.setCool()
        }
    }
}
