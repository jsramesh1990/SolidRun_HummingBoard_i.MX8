import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: dashboardView
    color: backgroundColor
    
    GridLayout {
        anchors.fill: parent
        anchors.margins: 20
        columns: 3
        rows: 3
        columnSpacing: 20
        rowSpacing: 20
        
        DashboardCard {
            title: "System Status"
            color: "#4CAF50"
            
            ColumnLayout {
                spacing: 10
                
                Label {
                    text: "CPU: " + systemMonitor.stats.cpuUsage.toFixed(1) + "%"
                    color: "white"
                    font.pixelSize: 16
                }
                
                Label {
                    text: "Memory: " + systemMonitor.stats.memoryUsage.toFixed(1) + "%"
                    color: "white"
                    font.pixelSize: 16
                }
                
                Label {
                    text: "Temperature: " + systemMonitor.stats.temperature.toFixed(1) + "°C"
                    color: "white"
                    font.pixelSize: 16
                }
            }
        }
        
        DashboardCard {
            title: "Quick Access"
            color: "#2196F3"
            
            ColumnLayout {
                spacing: 10
                
                Button {
                    text: "Calculator"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Calculator")
                }
                
                Button {
                    text: "GPIO Control"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("GPIO")
                }
                
                Button {
                    text: "MQTT"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("MQTT")
                }
            }
        }
        
        DashboardCard {
            title: "System Info"
            color: "#FF9800"
            
            ColumnLayout {
                spacing: 10
                
                Label {
                    text: "Kernel: " + systemMonitor.stats.kernelVersion
                    color: "white"
                    font.pixelSize: 14
                    wrapMode: Text.WordWrap
                }
                
                Label {
                    text: "IP: " + systemMonitor.stats.ipAddress
                    color: "white"
                    font.pixelSize: 14
                }
                
                Label {
                    text: "Uptime: " + Math.floor(systemMonitor.stats.uptime / 3600) + "h " + 
                          Math.floor((systemMonitor.stats.uptime % 3600) / 60) + "m"
                    color: "white"
                    font.pixelSize: 14
                }
            }
        }
        
        DashboardCard {
            title: "Data Structures"
            color: "#9C27B0"
            Layout.fillHeight: true
            
            ColumnLayout {
                spacing: 8
                
                Button {
                    text: "Linked List"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Data Structures")
                }
                
                Button {
                    text: "Binary Tree"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Data Structures")
                }
                
                Button {
                    text: "Hash Table"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Data Structures")
                }
            }
        }
        
        DashboardCard {
            title: "Algorithms"
            color: "#E91E63"
            Layout.fillHeight: true
            
            ColumnLayout {
                spacing: 8
                
                Button {
                    text: "Sorting"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Algorithms")
                }
                
                Button {
                    text: "Searching"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Algorithms")
                }
                
                Button {
                    text: "Graph Algorithms"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("Algorithms")
                }
            }
        }
        
        DashboardCard {
            title: "Embedded Interfaces"
            color: "#607D8B"
            Layout.fillHeight: true
            
            ColumnLayout {
                spacing: 8
                
                Button {
                    text: "GPIO"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("GPIO")
                }
                
                Button {
                    text: "I2C"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("I2C")
                }
                
                Button {
                    text: "SPI"
                    Layout.fillWidth: true
                    onClicked: appController.navigateTo("SPI")
                }
            }
        }
    }
    
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: systemMonitor.refresh()
    }
}
