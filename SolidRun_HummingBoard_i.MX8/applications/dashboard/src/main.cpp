#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "AppController.h"
#include "DeviceManager.h"
#include "SystemMonitor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QQuickStyle::setStyle("Material");
    
    qmlRegisterType<AppController>("EmbeddedLearning", 1, 0, "AppController");
    qmlRegisterType<DeviceManager>("EmbeddedLearning", 1, 0, "DeviceManager");
    qmlRegisterType<SystemMonitor>("EmbeddedLearning", 1, 0, "SystemMonitor");
    
    QQmlApplicationEngine engine;
    
    DeviceManager deviceManager;
    SystemMonitor systemMonitor;
    AppController appController;
    
    engine.rootContext()->setContextProperty("deviceManager", &deviceManager);
    engine.rootContext()->setContextProperty("systemMonitor", &systemMonitor);
    engine.rootContext()->setContextProperty("appController", &appController);
    
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    
    if (engine.rootObjects().isEmpty())
        return -1;
    
    return app.exec();
}
