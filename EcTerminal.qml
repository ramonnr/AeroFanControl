import QtQuick 2.4
import QtQuick.Layouts 1.3
import Style 1.0

Item {
    id: terminalRoot
    width: parent.width
    height: parent.height

    Rectangle{
        width: terminalRoot.width
        height: terminalRoot.height
        color: Style.terminalBackground
    }

    GridView {
        id: grid
        interactive: false
        width: parent.width * .9
        height: parent.height * 0.985
        x: parent.width * 0.05
        y: parent.height * 0.01
        cellHeight: height / 32
        cellWidth: width / 8

        model: ECData.modelHex
        delegate: Rectangle{
            Text{
                text: modelData
                color: Style.terminalText
            }
        }
    }
}
