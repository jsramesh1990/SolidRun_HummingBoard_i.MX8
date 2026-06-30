#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>

// Calculation result structure
struct CalculationResult {
    std::string expression;
    double result;
    bool success;
    std::string error_message;
    
    CalculationResult() : result(0.0), success(false) {}
    CalculationResult(const std::string& expr, double res) 
        : expression(expr), result(res), success(true) {}
    CalculationResult(const std::string& expr, const std::string& error) 
        : expression(expr), result(0.0), success(false), error_message(error) {}
};

// History entry structure
struct HistoryEntry {
    std::string timestamp;
    std::string expression;
    double result;
    std::string operation_type;
};

// Calculator class
class Calculator {
private:
    double memory;
    std::vector<HistoryEntry> history;
    std::string history_file;
    
    // Private helper methods
    double evaluateExpression(const std::string& expr);
    bool validateExpression(const std::string& expr);
    std::string formatResult(double value);
    void saveToHistory(const HistoryEntry& entry);
    
public:
    Calculator();
    ~Calculator();
    
    // Basic arithmetic operations
    CalculationResult add(double a, double b);
    CalculationResult subtract(double a, double b);
    CalculationResult multiply(double a, double b);
    CalculationResult divide(double a, double b);
    CalculationResult modulus(int a, int b);
    CalculationResult power(double base, double exponent);
    
    // Scientific operations
    CalculationResult squareRoot(double value);
    CalculationResult sin(double angle_degrees);
    CalculationResult cos(double angle_degrees);
    CalculationResult tan(double angle_degrees);
    CalculationResult log10(double value);
    CalculationResult ln(double value);
    CalculationResult exp(double value);
    CalculationResult factorial(int n);
    
    // Memory operations
    CalculationResult memoryAdd(double value);
    CalculationResult memorySubtract(double value);
    CalculationResult memoryRecall();
    CalculationResult memoryClear();
    double getMemoryValue() const;
    
    // Complex expression evaluation
    CalculationResult evaluate(const std::string& expression);
    
    // History operations
    std::vector<HistoryEntry> getHistory(int limit = 10) const;
    CalculationResult clearHistory();
    CalculationResult saveHistoryToFile(const std::string& filename = "");
    CalculationResult loadHistoryFromFile(const std::string& filename = "");
    
    // Utility functions
    CalculationResult percentage(double value);
    CalculationResult negate(double value);
    CalculationResult reciprocal(double value);
};

// Command Processor for handling different operations
class CommandProcessor {
private:
    std::unique_ptr<Calculator> calculator;
    std::map<std::string, std::string> parseCommand(const std::string& command);
    
public:
    CommandProcessor();
    std::string processCommand(const std::string& command);
};

#endif // CALCULATOR_H
