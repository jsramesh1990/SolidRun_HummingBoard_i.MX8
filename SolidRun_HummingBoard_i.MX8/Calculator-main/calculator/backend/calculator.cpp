#include "calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <stdexcept>

using namespace std;

// Calculator implementation
Calculator::Calculator() : memory(0.0), history_file("calculator_history.dat") {
    loadHistoryFromFile();
}

Calculator::~Calculator() {
    saveHistoryToFile();
}

// Helper: Format result to avoid scientific notation for small numbers
string Calculator::formatResult(double value) {
    ostringstream oss;
    if (fabs(value) < 1e10 && fabs(value) > 1e-4) {
        oss << fixed << setprecision(10);
        string str = to_string(value);
        // Remove trailing zeros
        str.erase(str.find_last_not_of('0') + 1, string::npos);
        if (str.back() == '.') str.pop_back();
        return str;
    }
    oss << value;
    return oss.str();
}

// Basic arithmetic operations
CalculationResult Calculator::add(double a, double b) {
    double result = a + b;
    string expr = to_string(a) + " + " + to_string(b);
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "addition"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::subtract(double a, double b) {
    double result = a - b;
    string expr = to_string(a) + " - " + to_string(b);
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "subtraction"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::multiply(double a, double b) {
    double result = a * b;
    string expr = to_string(a) + " * " + to_string(b);
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "multiplication"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::divide(double a, double b) {
    if (b == 0) {
        return CalculationResult(to_string(a) + " / " + to_string(b), 
                                "Error: Division by zero");
    }
    double result = a / b;
    string expr = to_string(a) + " / " + to_string(b);
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "division"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::modulus(int a, int b) {
    if (b == 0) {
        return CalculationResult(to_string(a) + " % " + to_string(b), 
                                "Error: Modulus by zero");
    }
    int result = a % b;
    string expr = to_string(a) + " % " + to_string(b);
    HistoryEntry entry = {to_string(time(nullptr)), expr, static_cast<double>(result), "modulus"};
    saveToHistory(entry);
    return CalculationResult(expr, static_cast<double>(result));
}

CalculationResult Calculator::power(double base, double exponent) {
    double result = pow(base, exponent);
    string expr = to_string(base) + " ^ " + to_string(exponent);
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "power"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

// Scientific operations
CalculationResult Calculator::squareRoot(double value) {
    if (value < 0) {
        return CalculationResult("sqrt(" + to_string(value) + ")", 
                                "Error: Square root of negative number");
    }
    double result = sqrt(value);
    string expr = "sqrt(" + to_string(value) + ")";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "square_root"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::sin(double angle_degrees) {
    double radians = angle_degrees * M_PI / 180.0;
    double result = std::sin(radians);
    string expr = "sin(" + to_string(angle_degrees) + "°)";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "sine"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::cos(double angle_degrees) {
    double radians = angle_degrees * M_PI / 180.0;
    double result = std::cos(radians);
    string expr = "cos(" + to_string(angle_degrees) + "°)";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "cosine"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::tan(double angle_degrees) {
    double radians = angle_degrees * M_PI / 180.0;
    // Check for undefined values (90°, 270°, etc.)
    if (fmod(angle_degrees + 90, 180) == 0) {
        return CalculationResult("tan(" + to_string(angle_degrees) + "°)", 
                                "Error: Tangent undefined for this angle");
    }
    double result = std::tan(radians);
    string expr = "tan(" + to_string(angle_degrees) + "°)";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "tangent"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::log10(double value) {
    if (value <= 0) {
        return CalculationResult("log10(" + to_string(value) + ")", 
                                "Error: Logarithm of non-positive number");
    }
    double result = std::log10(value);
    string expr = "log10(" + to_string(value) + ")";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "log10"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::ln(double value) {
    if (value <= 0) {
        return CalculationResult("ln(" + to_string(value) + ")", 
                                "Error: Natural log of non-positive number");
    }
    double result = std::log(value);
    string expr = "ln(" + to_string(value) + ")";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "natural_log"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::exp(double value) {
    double result = std::exp(value);
    string expr = "exp(" + to_string(value) + ")";
    HistoryEntry entry = {to_string(time(nullptr)), expr, result, "exponential"};
    saveToHistory(entry);
    return CalculationResult(expr, result);
}

CalculationResult Calculator::factorial(int n) {
    if (n < 0) {
        return CalculationResult(to_string(n) + "!", 
                                "Error: Factorial of negative number");
    }
    if (n > 20) { // Prevent overflow
        return CalculationResult(to_string(n) + "!", 
                                "Error: Number too large for factorial");
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    string expr = to_string(n) + "!";
    HistoryEntry entry = {to_string(time(nullptr)), expr, static_cast<double>(result), "factorial"};
    saveToHistory(entry);
    return CalculationResult(expr, static_cast<double>(result));
}

// Memory operations
CalculationResult Calculator::memoryAdd(double value) {
    memory += value;
    return CalculationResult("M + " + to_string(value), memory);
}

CalculationResult Calculator::memorySubtract(double value) {
    memory -= value;
    return CalculationResult("M - " + to_string(value), memory);
}

CalculationResult Calculator::memoryRecall() {
    return CalculationResult("Memory Recall", memory);
}

CalculationResult Calculator::memoryClear() {
    memory = 0.0;
    return CalculationResult("Memory Clear", memory);
}

double Calculator::getMemoryValue() const {
    return memory;
}

// Complex expression evaluation (basic implementation)
CalculationResult Calculator::evaluate(const string& expression) {
    try {
        // Simple expression parser (for demonstration)
        // In a real application, you would use a proper expression parser
        istringstream iss(expression);
        double a, b;
        char op;
        
        if (iss >> a >> op >> b) {
            switch (op) {
                case '+': return add(a, b);
                case '-': return subtract(a, b);
                case '*': return multiply(a, b);
                case '/': return divide(a, b);
                case '^': return power(a, b);
                default: 
                    return CalculationResult(expression, 
                                            "Error: Unsupported operator");
            }
        }
        
        // Try scientific functions
        if (expression.find("sqrt") == 0) {
            double val = stod(expression.substr(5, expression.length() - 6));
            return squareRoot(val);
        } else if (expression.find("sin") == 0) {
            double val = stod(expression.substr(4, expression.find(')') - 4));
            return sin(val);
        }
        
        return CalculationResult(expression, 
                                "Error: Could not parse expression");
    } catch (const exception& e) {
        return CalculationResult(expression, 
                                "Error: " + string(e.what()));
    }
}

// History operations
void Calculator::saveToHistory(const HistoryEntry& entry) {
    history.push_back(entry);
    if (history.size() > 100) { // Keep only last 100 entries
        history.erase(history.begin());
    }
}

vector<HistoryEntry> Calculator::getHistory(int limit) const {
    if (limit <= 0 || limit >= history.size()) {
        return history;
    }
    return vector<HistoryEntry>(history.end() - limit, history.end());
}

CalculationResult Calculator::clearHistory() {
    history.clear();
    return CalculationResult("Clear History", 0);
}

CalculationResult Calculator::saveHistoryToFile(const string& filename) {
    string file = filename.empty() ? history_file : filename;
    ofstream out(file, ios::binary);
    if (!out) {
        return CalculationResult("Save History", 
                                "Error: Could not open file for writing");
    }
    
    for (const auto& entry : history) {
        out << entry.timestamp << "|"
            << entry.expression << "|"
            << entry.result << "|"
            << entry.operation_type << "\n";
    }
    
    out.close();
    return CalculationResult("Save History", static_cast<double>(history.size()));
}

CalculationResult Calculator::loadHistoryFromFile(const string& filename) {
    string file = filename.empty() ? history_file : filename;
    ifstream in(file, ios::binary);
    if (!in) {
        return CalculationResult("Load History", 
                                "Warning: No history file found");
    }
    
    history.clear();
    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string timestamp, expression, operation_type;
        double result;
        char delimiter;
        
        getline(iss, timestamp, '|');
        getline(iss, expression, '|');
        iss >> result;
        iss.ignore(); // Skip delimiter
        getline(iss, operation_type);
        
        HistoryEntry entry = {timestamp, expression, result, operation_type};
        history.push_back(entry);
    }
    
    in.close();
    return CalculationResult("Load History", static_cast<double>(history.size()));
}

// Utility functions
CalculationResult Calculator::percentage(double value) {
    double result = value / 100.0;
    return CalculationResult(to_string(value) + "%", result);
}

CalculationResult Calculator::negate(double value) {
    return CalculationResult("-(" + to_string(value) + ")", -value);
}

CalculationResult Calculator::reciprocal(double value) {
    if (value == 0) {
        return CalculationResult("1/(" + to_string(value) + ")", 
                                "Error: Division by zero");
    }
    return CalculationResult("1/(" + to_string(value) + ")", 1.0 / value);
}

// CommandProcessor implementation
CommandProcessor::CommandProcessor() {
    calculator = make_unique<Calculator>();
}

map<string, string> CommandProcessor::parseCommand(const string& command) {
    map<string, string> result;
    istringstream iss(command);
    string cmd;
    iss >> cmd;
    
    result["command"] = cmd;
    
    // Parse parameters based on command type
    if (cmd == "CALC" || cmd == "EVAL") {
        // Get the rest of the line as expression
        string expr;
        getline(iss, expr);
        if (!expr.empty() && expr[0] == ' ') {
            expr = expr.substr(1);
        }
        result["expression"] = expr;
    } else if (cmd == "ADD" || cmd == "SUB" || cmd == "MUL" || cmd == "DIV" || 
               cmd == "POW" || cmd == "PERCENT" || cmd == "NEGATE" || cmd == "RECIPROCAL") {
        string param1, param2;
        iss >> param1;
        if (cmd != "PERCENT" && cmd != "NEGATE" && cmd != "RECIPROCAL") {
            iss >> param2;
            result["param2"] = param2;
        }
        result["param1"] = param1;
    } else if (cmd == "SQRT" || cmd == "SIN" || cmd == "COS" || cmd == "TAN" || 
               cmd == "LOG" || cmd == "LN" || cmd == "EXP" || cmd == "FACT") {
        string param;
        iss >> param;
        result["param"] = param;
    } else if (cmd == "MADD" || cmd == "MSUB") {
        string param;
        iss >> param;
        result["param"] = param;
    }
    
    return result;
}

string CommandProcessor::processCommand(const string& command) {
    auto parts = parseCommand(command);
    string cmd = parts["command"];
    
    ostringstream response;
    
    try {
        if (cmd == "CALC" || cmd == "EVAL") {
            auto result = calculator->evaluate(parts["expression"]);
            response << (result.success ? "SUCCESS" : "ERROR") << "|"
                    << result.expression << "|"
                    << result.result << "|"
                    << result.error_message;
        }
        else if (cmd == "ADD") {
            double a = stod(parts["param1"]);
            double b = stod(parts["param2"]);
            auto result = calculator->add(a, b);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "SUB") {
            double a = stod(parts["param1"]);
            double b = stod(parts["param2"]);
            auto result = calculator->subtract(a, b);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "MUL") {
            double a = stod(parts["param1"]);
            double b = stod(parts["param2"]);
            auto result = calculator->multiply(a, b);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "DIV") {
            double a = stod(parts["param1"]);
            double b = stod(parts["param2"]);
            auto result = calculator->divide(a, b);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "SQRT") {
            double val = stod(parts["param"]);
            auto result = calculator->squareRoot(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "SIN") {
            double val = stod(parts["param"]);
            auto result = calculator->sin(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "COS") {
            double val = stod(parts["param"]);
            auto result = calculator->cos(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "TAN") {
            double val = stod(parts["param"]);
            auto result = calculator->tan(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "LOG") {
            double val = stod(parts["param"]);
            auto result = calculator->log10(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "LN") {
            double val = stod(parts["param"]);
            auto result = calculator->ln(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "EXP") {
            double val = stod(parts["param"]);
            auto result = calculator->exp(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "FACT") {
            int val = stoi(parts["param"]);
            auto result = calculator->factorial(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "POW") {
            double a = stod(parts["param1"]);
            double b = stod(parts["param2"]);
            auto result = calculator->power(a, b);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "PERCENT") {
            double val = stod(parts["param1"]);
            auto result = calculator->percentage(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "NEGATE") {
            double val = stod(parts["param1"]);
            auto result = calculator->negate(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "RECIPROCAL") {
            double val = stod(parts["param1"]);
            auto result = calculator->reciprocal(val);
            if (result.success) {
                response << "SUCCESS|" << result.expression << "|" << result.result;
            } else {
                response << "ERROR|||" << result.error_message;
            }
        }
        else if (cmd == "MADD") {
            double val = stod(parts["param"]);
            auto result = calculator->memoryAdd(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "MSUB") {
            double val = stod(parts["param"]);
            auto result = calculator->memorySubtract(val);
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "MR") {
            auto result = calculator->memoryRecall();
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "MC") {
            auto result = calculator->memoryClear();
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "HISTORY") {
            auto history = calculator->getHistory(10);
            response << "SUCCESS|History|" << history.size() << "|";
            for (const auto& entry : history) {
                response << entry.expression << " = " << entry.result << ";";
            }
        }
        else if (cmd == "CLEAR_HISTORY") {
            auto result = calculator->clearHistory();
            response << "SUCCESS|" << result.expression << "|" << result.result;
        }
        else if (cmd == "SAVE_HISTORY") {
            auto result = calculator->saveHistoryToFile();
            response << (result.success ? "SUCCESS" : "ERROR") << "|"
                    << result.expression << "|"
                    << result.result << "|"
                    << result.error_message;
        }
        else if (cmd == "LOAD_HISTORY") {
            auto result = calculator->loadHistoryFromFile();
            response << (result.success ? "SUCCESS" : "ERROR") << "|"
                    << result.expression << "|"
                    << result.result << "|"
                    << result.error_message;
        }
        else if (cmd == "EXIT" || cmd == "QUIT") {
            response << "EXIT|Goodbye!";
        }
        else {
            response << "ERROR|||Unknown command: " << cmd;
        }
    } catch (const exception& e) {
        response << "ERROR|||" << e.what();
    }
    
    return response.str();
}
