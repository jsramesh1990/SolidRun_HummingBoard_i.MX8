#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QObject>
#include <QString>
#include <QStack>

class CalculatorEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY displayChanged)
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged)
    
public:
    explicit CalculatorEngine(QObject *parent = nullptr);
    
    QString display() const { return m_display; }
    QString expression() const { return m_expression; }
    
    Q_INVOKABLE void inputDigit(int digit);
    Q_INVOKABLE void inputOperator(const QString &op);
    Q_INVOKABLE void inputFunction(const QString &func);
    Q_INVOKABLE void inputConstant(const QString &constant);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void clearEntry();
    Q_INVOKABLE void backspace();
    Q_INVOKABLE void evaluate();
    Q_INVOKABLE void toggleSign();
    Q_INVOKABLE void percent();
    Q_INVOKABLE void memoryStore();
    Q_INVOKABLE void memoryRecall();
    Q_INVOKABLE void memoryClear();
    
signals:
    void displayChanged();
    void expressionChanged();
    void errorOccurred(const QString &error);
    
private:
    QString m_display;
    QString m_expression;
    QString m_currentNumber;
    QString m_operator;
    double m_accumulator;
    double m_memory;
    bool m_hasDecimal;
    bool m_justEvaluated;
    
    void updateDisplay();
    double parseNumber(const QString &str);
    QString formatNumber(double num);
    double evaluateExpression(const QString &expr);
    bool isValidOperator(const QString &op);
    int precedence(const QString &op);
    double applyOperator(double a, const QString &op, double b);
};

#endif // CALCULATORENGINE_H
