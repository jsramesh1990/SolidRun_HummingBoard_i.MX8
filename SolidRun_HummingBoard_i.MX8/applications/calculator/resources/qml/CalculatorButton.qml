import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: button
    property color color: "#424242"
    
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.minimumWidth: 50
    Layout.minimumHeight: 50
    
    background: Rectangle {
        color: button.down ? Qt.darker(button.color, 1.5) : button.color
        radius: 5
        border.color: Qt.darker(button.color, 1.2)
        border.width: 1
    }
    
    contentItem: Text {
        text: button.text
        color: "white"
        font.pixelSize: button.font.pixelSize || 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
