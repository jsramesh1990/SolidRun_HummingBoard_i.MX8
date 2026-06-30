import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import EmbeddedLearning 1.0

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    visible: true
    title: "Embedded Learning Platform"
    
    property string currentView: appController.currentView
    
    // Colors
    property color primaryColor: "#2196F3"
    property color backgroundColor: "#F5F5F5"
    property color cardColor: "#FFFFFF"
    property color textColor: "#333333"
    property color accentColor: "#FF4081"
    
    // Components
    header: ToolBar {
        id: headerBar
        height: 60
        background: Rectangle {
            color: primaryColor
        }
        
        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            
            ToolButton {
                text: "☰"
                font.pixelSize: 24
                onClicked: drawer.open()
            }
            
            Label {
                text: "Embedded Learning Platform"
                color: "white"
                font.pixelSize: 20
                font.bold: true
                Layout.fillWidth: true
            }
            
            ToolButton {
                text: "⚙"
                font.pixelSize: 20
                onClicked: appController.navigateTo("Settings")
            }
        }
    }
    
    Drawer {
        id: drawer
        width: Math.min(root.width * 0.3, 300)
        height: root.height
        
        ListView {
            id: menuListView
            anchors.fill: parent
            model: appController.menuItems
            delegate: ItemDelegate {
                width: parent.width
                height: 50
                text: modelData
                highlighted: ListView.isCurrentItem
                
                onClicked: {
                    appController.navigateTo(modelData)
                    drawer.close()
                }
            }
        }
    }
    
    StackLayout {
        id: stackLayout
        anchors.fill: parent
        anchors.margins: 10
        currentIndex: getViewIndex(currentView)
        
        // Dashboard View
        DashboardView {}
        
        // Calculator View
        CalculatorView {}
        
        // Data Structures View
        DataStructuresView {}
        
        // Algorithms View
        AlgorithmsView {}
        
        // GPIO View
        GPIOView {}
        
        // I2C View
        I2CView {}
        
        // SPI View
        SPIView {}
        
        // UART View
        UARTView {}
        
        // CAN View
        CANView {}
        
        // MQTT View
        MQTTView {}
        
        // Sensors View
        SensorsView {}
        
        // Camera View
        CameraView {}
        
        // System Monitor View
        SystemMonitorView {}
        
        // Settings View
        SettingsView {}
    }
    
    function getViewIndex(view) {
        var index = appController.menuItems.indexOf(view)
        return index >= 0 ? index : 0
    }
}
