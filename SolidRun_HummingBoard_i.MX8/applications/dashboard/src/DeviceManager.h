#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QMap>

struct DeviceInfo {
    QString name;
    QString path;
    QString type;
    bool available;
};

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<DeviceInfo> devices READ devices NOTIFY devicesChanged)
    
public:
    explicit DeviceManager(QObject *parent = nullptr);
    
    QList<DeviceInfo> devices() const { return m_devices; }
    
    Q_INVOKABLE bool scanDevices();
    Q_INVOKABLE bool openDevice(const QString &path);
    Q_INVOKABLE bool closeDevice(const QString &path);
    Q_INVOKABLE bool readDevice(const QString &path, QByteArray &data);
    Q_INVOKABLE bool writeDevice(const QString &path, const QByteArray &data);
    
signals:
    void devicesChanged();
    void deviceOpened(const QString &path);
    void deviceClosed(const QString &path);
    void dataReceived(const QString &path, const QByteArray &data);
    void errorOccurred(const QString &path, const QString &error);
    
private:
    QList<DeviceInfo> m_devices;
    QMap<QString, void*> m_deviceHandles;
    
    void enumerateDevices();
};

Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEMANAGER_H
