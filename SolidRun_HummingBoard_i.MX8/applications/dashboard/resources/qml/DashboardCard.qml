import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: card
    property string title: "Card"
    property color color: "#2196F3"
    property alias content: contentArea.children
    
    color: card.color
    radius: 10
    Layout.minimumWidth: 200
    Layout.minimumHeight: 150
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 10
        
        Label {
            text: card.title
            color: "white"
            font.pixelSize: 18
            font.bold: true
        }
        
        Rectangle {
            id: contentArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }
    }
}
