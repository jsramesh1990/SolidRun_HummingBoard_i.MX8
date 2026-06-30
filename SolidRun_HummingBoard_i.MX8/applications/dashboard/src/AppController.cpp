#include "AppController.h"
#include <QDebug>

AppController::AppController(QObject *parent)
    : QObject(parent)
    , m_currentView("Dashboard")
{
    // Initialize menu items
    m_menuItems = {
        "Dashboard",
        "Calculator",
        "Data Structures",
        "Algorithms",
        "GPIO",
        "I2C",
        "SPI",
        "UART",
        "CAN",
        "MQTT",
        "Sensors",
        "Camera",
        "System Monitor",
        "Settings"
    };
}

void AppController::setCurrentView(const QString &view)
{
    if (m_currentView != view) {
        m_currentView = view;
        emit currentViewChanged();
    }
}

void AppController::navigateTo(const QString &view)
{
    qDebug() << "Navigating to:" << view;
    setCurrentView(view);
    emit viewChanged(view);
}

void AppController::back()
{
    // For simplicity, navigate back to Dashboard
    navigateTo("Dashboard");
}
