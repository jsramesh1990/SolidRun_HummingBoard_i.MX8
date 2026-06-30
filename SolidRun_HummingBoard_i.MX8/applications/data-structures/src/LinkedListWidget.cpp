#include "LinkedListWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

LinkedListWidget::LinkedListWidget(QWidget *parent)
    : QWidget(parent)
    , m_list(new LinkedList<int>)
{
    setupUI();
}

LinkedListWidget::~LinkedListWidget()
{
    delete m_list;
}

void LinkedListWidget::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Display area
    m_displayLabel = new QLabel("[]");
    m_displayLabel->setAlignment(Qt::AlignCenter);
    m_displayLabel->setStyleSheet("font-size: 16px; font-family: monospace; padding: 10px;");
    mainLayout->addWidget(m_displayLabel);
    
    // Input area
    QHBoxLayout* inputLayout = new QHBoxLayout;
    m_valueInput = new QLineEdit;
    m_valueInput->setPlaceholderText("Enter value");
    m_indexInput = new QLineEdit;
    m_indexInput->setPlaceholderText("Index");
    
    inputLayout->addWidget(m_valueInput);
    inputLayout->addWidget(m_indexInput);
    mainLayout->addLayout(inputLayout);
    
    // Operation buttons
    QGridLayout* buttonLayout = new QGridLayout;
    
    QStringList buttons = {
        "Push Front", "Push Back", "Insert At",
        "Pop Front", "Pop Back", "Remove At",
        "Insert Before", "Insert After", "Remove Value",
        "Reverse", "Find", "Clear"
    };
    
    int row = 0, col = 0;
    for (const QString& text : buttons) {
        QPushButton* btn = new QPushButton(text);
        connect(btn, &QPushButton::clicked, [this, text]() {
            handleButtonClick(text);
        });
        buttonLayout->addWidget(btn, row, col);
        col++;
        if (col >= 4) {
            col = 0;
            row++;
        }
    }
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    updateDisplay();
}

void LinkedListWidget::handleButtonClick(const QString& button)
{
    bool ok;
    int value = m_valueInput->text().toInt(&ok);
    int index = m_indexInput->text().toInt(&ok);
    
    try {
        if (button == "Push Front") {
            if (ok) m_list->pushFront(value);
        } else if (button == "Push Back") {
            if (ok) m_list->pushBack(value);
        } else if (button == "Insert At") {
            if (ok && !m_indexInput->text().isEmpty()) {
                m_list->insertAt(index, value);
            }
        } else if (button == "Pop Front") {
            if (!m_list->isEmpty()) {
                int val = m_list->popFront();
                QMessageBox::information(this, "Popped", QString("Value: %1").arg(val));
            }
        } else if (button == "Pop Back") {
            if (!m_list->isEmpty()) {
                int val = m_list->popBack();
                QMessageBox::information(this, "Popped", QString("Value: %1").arg(val));
            }
        } else if (button == "Remove At") {
            if (!m_indexInput->text().isEmpty()) {
                int val = m_list->removeAt(index);
                QMessageBox::information(this, "Removed", QString("Value: %1").arg(val));
            }
        } else if (button == "Insert Before") {
            if (ok && !m_indexInput->text().isEmpty()) {
                int before = m_indexInput->text().toInt();
                m_list->insertBefore(value, before);
            }
        } else if (button == "Insert After") {
            if (ok && !m_indexInput->text().isEmpty()) {
                int after = m_indexInput->text().toInt();
                m_list->insertAfter(value, after);
            }
        } else if (button == "Remove Value") {
            if (ok) {
                if (m_list->removeValue(value)) {
                    QMessageBox::information(this, "Success", "Value removed");
                } else {
                    QMessageBox::warning(this, "Not Found", "Value not found in list");
                }
            }
        } else if (button == "Reverse") {
            m_list->reverse();
        } else if (button == "Find") {
            if (ok) {
                int pos = m_list->find(value);
                if (pos != -1) {
                    QMessageBox::information(this, "Found", QString("Value found at index %1").arg(pos));
                } else {
                    QMessageBox::information(this, "Not Found", "Value not found in list");
                }
            }
        } else if (button == "Clear") {
            m_list->clear();
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    
    updateDisplay();
}

void LinkedListWidget::updateDisplay()
{
    m_displayLabel->setText(m_list->toString());
}
