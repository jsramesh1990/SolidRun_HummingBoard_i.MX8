#include "CalculatorEngine.h"
#include <QDebug>
#include <QRegularExpression>
#include <cmath>
#include <stack>
#include <vector>
#include <sstream>

CalculatorEngine::CalculatorEngine(QObject *parent)
    : QObject(parent)
    , m_display("0")
    , m_accumulator(0)
    , m_memory(0)
    , m_hasDecimal(false)
    , m_justEvaluated(false)
{
}

void CalculatorEngine::inputDigit(int digit)
{
    if (m_justEvaluated) {
        clear();
        m_justEvaluated = false;
    }
    
    if (m_currentNumber == "0" && digit != 0) {
        m_currentNumber = QString::number(digit);
    } else if (m_currentNumber == "0" && digit == 0) {
        // Do nothing
    } else {
        m_currentNumber += QString::number(digit);
    }
    
    updateDisplay();
}

void CalculatorEngine::inputOperator(const QString &op)
{
    if (m_justEvaluated) {
        m_justEvaluated = false;
    }
    
    if (!m_currentNumber.isEmpty()) {
        m_expression += m_currentNumber + " " + op + " ";
        m_currentNumber.clear();
        m_hasDecimal = false;
    } else if (m_operator.isEmpty()) {
        // Handle negative number
        if (op == "-") {
            m_currentNumber = "-";
        }
    } else {
        // Replace last operator
        m_expression.chop(3);
        m_expression += op + " ";
    }
    
    m_operator = op;
    emit expressionChanged();
}

void CalculatorEngine::inputFunction(const QString &func)
{
    if (m_justEvaluated) {
        clear();
        m_justEvaluated = false;
    }
    
    double value = parseNumber(m_currentNumber.isEmpty() ? m_display : m_currentNumber);
    double result = 0;
    
    if (func == "sin") {
        result = sin(value);
    } else if (func == "cos") {
        result = cos(value);
    } else if (func == "tan") {
        result = tan(value);
    } else if (func == "log") {
        result = log10(value);
    } else if (func == "ln") {
        result = log(value);
    } else if (func == "sqrt") {
        result = sqrt(value);
    } else if (func == "x^2") {
        result = value * value;
    } else if (func == "1/x") {
        if (value != 0) {
            result = 1.0 / value;
        } else {
            emit errorOccurred("Division by zero");
            return;
        }
    } else if (func == "factorial") {
        if (value < 0 || value != floor(value)) {
            emit errorOccurred("Invalid input for factorial");
            return;
        }
        result = 1;
        for (int i = 2; i <= value; ++i) {
            result *= i;
        }
    }
    
    m_expression = func + "(" + m_display + ") = ";
    m_display = formatNumber(result);
    m_currentNumber = QString::number(result);
    m_hasDecimal = m_currentNumber.contains('.');
    m_justEvaluated = true;
    
    emit displayChanged();
    emit expressionChanged();
}

void CalculatorEngine::inputConstant(const QString &constant)
{
    double value = 0;
    if (constant == "π") {
        value = M_PI;
    } else if (constant == "e") {
        value = M_E;
    }
    
    m_display = formatNumber(value);
    m_currentNumber = QString::number(value);
    emit displayChanged();
}

void CalculatorEngine::clear()
{
    m_display = "0";
    m_expression.clear();
    m_currentNumber.clear();
    m_operator.clear();
    m_accumulator = 0;
    m_hasDecimal = false;
    m_justEvaluated = false;
    
    emit displayChanged();
    emit expressionChanged();
}

void CalculatorEngine::clearEntry()
{
    m_display = "0";
    m_currentNumber.clear();
    m_hasDecimal = false;
    emit displayChanged();
}

void CalculatorEngine::backspace()
{
    if (!m_currentNumber.isEmpty() && m_currentNumber != "0") {
        m_currentNumber.chop(1);
        if (m_currentNumber.isEmpty() || m_currentNumber == "-") {
            m_currentNumber = "0";
        }
        updateDisplay();
    }
}

void CalculatorEngine::evaluate()
{
    if (m_justEvaluated) {
        return;
    }
    
    QString expr = m_expression;
    if (!m_currentNumber.isEmpty()) {
        expr += m_currentNumber;
    }
    
    if (expr.isEmpty()) {
        return;
    }
    
    try {
        double result = evaluateExpression(expr);
        m_display = formatNumber(result);
        m_expression = expr + " = " + m_display;
        m_currentNumber = QString::number(result);
        m_hasDecimal = m_currentNumber.contains('.');
        m_justEvaluated = true;
        
        emit displayChanged();
        emit expressionChanged();
    } catch (const std::exception &e) {
        emit errorOccurred(e.what());
    }
}

void CalculatorEngine::toggleSign()
{
    if (m_currentNumber.isEmpty()) {
        m_currentNumber = m_display;
    }
    
    if (m_currentNumber.startsWith("-")) {
        m_currentNumber.remove(0, 1);
    } else {
        m_currentNumber = "-" + m_currentNumber;
    }
    
    updateDisplay();
}

void CalculatorEngine::percent()
{
    if (m_currentNumber.isEmpty()) {
        m_currentNumber = m_display;
    }
    
    double value = parseNumber(m_currentNumber) / 100.0;
    m_display = formatNumber(value);
    m_currentNumber = QString::number(value);
    emit displayChanged();
}

void CalculatorEngine::memoryStore()
{
    m_memory = parseNumber(m_currentNumber.isEmpty() ? m_display : m_currentNumber);
}

void CalculatorEngine::memoryRecall()
{
    m_display = formatNumber(m_memory);
    m_currentNumber = QString::number(m_memory);
    emit displayChanged();
}

void CalculatorEngine::memoryClear()
{
    m_memory = 0;
}

void CalculatorEngine::updateDisplay()
{
    if (m_currentNumber.isEmpty()) {
        m_display = "0";
    } else {
        m_display = m_currentNumber;
    }
    emit displayChanged();
}

double CalculatorEngine::parseNumber(const QString &str)
{
    return str.toDouble();
}

QString CalculatorEngine::formatNumber(double num)
{
    if (std::isnan(num) || std::isinf(num)) {
        return "Error";
    }
    
    QString str = QString::number(num, 'g', 15);
    return str;
}

double CalculatorEngine::evaluateExpression(const QString &expr)
{
    // Tokenize the expression
    std::vector<QString> tokens;
    QString current;
    
    for (QChar ch : expr) {
        if (ch.isSpace()) {
            if (!current.isEmpty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (ch.isDigit() || ch == '.') {
            current += ch;
        } else if (ch == '-') {
            if (current.isEmpty() || tokens.empty() || 
                tokens.back() == "(" || isOperator(tokens.back())) {
                current += ch;
            } else {
                if (!current.isEmpty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                tokens.push_back(QString(ch));
            }
        } else {
            if (!current.isEmpty()) {
                tokens.push_back(current);
                current.clear();
            }
            if (ch == '(' || ch == ')' || ch == '+' || ch == '*' || 
                ch == '/' || ch == '^') {
                tokens.push_back(QString(ch));
            }
        }
    }
    if (!current.isEmpty()) {
        tokens.push_back(current);
    }
    
    // Convert to postfix using Shunting-yard algorithm
    std::vector<QString> output;
    std::stack<QString> operators;
    
    for (const QString &token : tokens) {
        if (isNumber(token)) {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop();
            }
        } else if (isOperator(token)) {
            while (!operators.empty() && operators.top() != "(" &&
                   precedence(token) <= precedence(operators.top())) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }
    
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    
    // Evaluate postfix expression
    std::stack<double> values;
    for (const QString &token : output) {
        if (isNumber(token)) {
            values.push(token.toDouble());
        } else if (isOperator(token)) {
            if (values.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            double result = applyOperator(a, token, b);
            values.push(result);
        }
    }
    
    if (values.empty()) {
        throw std::runtime_error("Invalid expression");
    }
    
    return values.top();
}

bool CalculatorEngine::isNumber(const QString &token)
{
    bool ok;
    token.toDouble(&ok);
    return ok;
}

bool CalculatorEngine::isOperator(const QString &token)
{
    return token == "+" || token == "-" || token == "*" || 
           token == "/" || token == "^";
}

bool CalculatorEngine::isValidOperator(const QString &op)
{
    return isOperator(op);
}

int CalculatorEngine::precedence(const QString &op)
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

double CalculatorEngine::applyOperator(double a, const QString &op, double b)
{
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    }
    if (op == "^") return pow(a, b);
    throw std::runtime_error("Unknown operator");
}
