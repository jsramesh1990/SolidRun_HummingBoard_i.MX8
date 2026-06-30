#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QString>
#include <QList>

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentView READ currentView WRITE setCurrentView NOTIFY currentViewChanged)
    Q_PROPERTY(QList<QString> menuItems READ menuItems CONSTANT)
    
public:
    explicit AppController(QObject *parent = nullptr);
    
    QString currentView() const { return m_currentView; }
    void setCurrentView(const QString &view);
    
    QList<QString> menuItems() const { return m_menuItems; }
    
signals:
    void currentViewChanged();
    void viewChanged(const QString &view);
    
public slots:
    void navigateTo(const QString &view);
    void back();
    
private:
    QString m_currentView;
    QList<QString> m_menuItems;
};

#endif // APPCONTROLLER_H
