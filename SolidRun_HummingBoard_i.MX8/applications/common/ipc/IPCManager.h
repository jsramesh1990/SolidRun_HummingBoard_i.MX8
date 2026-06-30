#ifndef IPCMANAGER_H
#define IPCMANAGER_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QMap>

class IPCManager : public QObject
{
    Q_OBJECT
    
public:
    static IPCManager* instance();
    
    bool registerObject(const QString& path, QObject* object);
    bool unregisterObject(const QString& path);
    
    QDBusInterface* getInterface(const QString& service, const QString& path, 
                                 const QString& interface = QString());
    
    bool sendSignal(const QString& service, const QString& path, 
                    const QString& interface, const QString& signal,
                    const QVariantList& args = QVariantList());
                    
    QVariant callMethod(const QString& service, const QString& path,
                       const QString& interface, const QString& method,
                       const QVariantList& args = QVariantList());
                       
signals:
    void signalReceived(const QString& service, const QString& path,
                       const QString& interface, const QString& signal,
                       const QVariantList& args);
                       
private:
    explicit IPCManager(QObject *parent = nullptr);
    
    static IPCManager* m_instance;
    QMap<QString, QDBusConnection> m_connections;
    QMap<QString, QDBusInterface*> m_interfaces;
};

#endif // IPCMANAGER_H
