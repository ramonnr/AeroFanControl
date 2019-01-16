import QtQuick 2.0
import QtQuick.Controls 2.4
import Style 1.0

Item {
    id: fanButton

    signal clicked()

    width: 50
    height: 40

    property int  animDuration: 1000
    property string btext: "notSet"
    property bool selected: false

    Rectangle{
        id: rekt
        width: parent.width
        height: parent.height
        //anchors.fill: parent
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
    Rectangle{
        width: parent.width
        height: parent.height
        color: "Black"
        opacity: 0.2
        visible: !selected
    }

    Button{
        id: button
        width: parent.width * .95
        height: parent.height * .95
        x: rekt.x- (rekt.width - width)
        y: rekt.y - (rekt.height - height)
        text: btext
    }
    Component.onCompleted: {
        button.clicked.connect(clicked)
    }
}
