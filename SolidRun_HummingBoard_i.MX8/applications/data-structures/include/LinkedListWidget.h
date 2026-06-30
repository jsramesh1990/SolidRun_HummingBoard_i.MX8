#ifndef LINKEDLISTWIDGET_H
#define LINKEDLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "LinkedList.h"

class LinkedListWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LinkedListWidget(QWidget *parent = nullptr);
    ~LinkedListWidget();
    
private slots:
    void handleButtonClick(const QString& button);
    
private:
    void setupUI();
    void updateDisplay();
    
    LinkedList<int>* m_list;
    QLabel* m_displayLabel;
    QLineEdit* m_valueInput;
    QLineEdit* m_indexInput;
};

#endif // LINKEDLISTWIDGET_H
