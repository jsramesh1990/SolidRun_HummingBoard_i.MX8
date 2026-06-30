#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

// Class to represent calculation history
class Calculation {
private:
    string expression;
    double result;
    
public:
    Calculation(const string& expr, double res) : expression(expr), result(res) {}
    
    string getExpression() const { return expression; }
    double getResult() const { return result; }
    
    void display() const {
        cout << expression << " = " << result << endl;
    }
};

// Calculator class with history tracking
class Calculator {
private:
    vector<Calculation> history;
    string filename = "calculator_history.txt";
    
    // Clear input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Save calculation to file
    void saveToFile(const string& expr, double result) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << expr << " = " << result << endl;
            file.close();
        }
    }
    
    // Display main menu
    void displayMenu() {
        cout << "\n=================================" << endl;
        cout << "     SCIENTIFIC CALCULATOR" << endl;
        cout << "=================================" << endl;
        cout << "1. Basic Arithmetic" << endl;
        cout << "2. Scientific Operations" << endl;
        cout << "3. View History" << endl;
        cout << "4. Save History to File" << endl;
        cout << "5. Load History from File" << endl;
        cout << "6. Clear History" << endl;
        cout << "7. Exit" << endl;
        cout << "=================================" << endl;
        cout << "Enter your choice (1-7): ";
    }
    
    // Display scientific operations menu
    void displayScientificMenu() {
        cout << "\nScientific Operations:" << endl;
        cout << "1. Square Root (√)" << endl;
        cout << "2. Power (x^y)" << endl;
        cout << "3. Sine (sin)" << endl;
        cout << "4. Cosine (cos)" << endl;
        cout << "5. Tangent (tan)" << endl;
        cout << "6. Logarithm (log10)" << endl;
        cout << "7. Natural Logarithm (ln)" << endl;
        cout << "8. Exponential (e^x)" << endl;
        cout << "9. Absolute Value" << endl;
        cout << "10. Floor" << endl;
        cout << "11. Ceil" << endl;
        cout << "12. Back to Main Menu" << endl;
        cout << "Enter your choice (1-12): ";
    }
    
    // Get number input with validation
    double getNumber(const string& prompt) {
        double num;
        while (true) {
            cout << prompt;
            if (cin >> num) {
                return num;
            } else {
                cout << "Invalid input! Please enter a valid number." << endl;
                clearInputBuffer();
            }
        }
    }
    
    // Get operator input with validation
    char getOperator() {
        char op;
        while (true) {
            cout << "Enter operator (+, -, *, /, %): ";
            cin >> op;
            if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%') {
                return op;
            } else {
                cout << "Invalid operator! Please enter +, -, *, /, or %" << endl;
                clearInputBuffer();
            }
        }
    }
    
    // Perform basic calculation
    void performBasicCalculation() {
        double num1 = getNumber("Enter first number: ");
        char op = getOperator();
        double num2;
        
        if (op != '%') {
            num2 = getNumber("Enter second number: ");
        } else {
            // For modulus, we need integers
            cout << "Enter second number (integer): ";
            int intNum2;
            while (!(cin >> intNum2)) {
                cout << "Invalid input! Please enter an integer: ";
                clearInputBuffer();
            }
            num2 = intNum2;
        }
        
        double result;
        string expr;
        bool validOperation = true;
        
        switch (op) {
            case '+':
                result = num1 + num2;
                expr = to_string(num1) + " + " + to_string(num2);
                break;
            case '-':
                result = num1 - num2;
                expr = to_string(num1) + " - " + to_string(num2);
                break;
            case '*':
                result = num1 * num2;
                expr = to_string(num1) + " * " + to_string(num2);
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    expr = to_string(num1) + " / " + to_string(num2);
                } else {
                    cout << "Error: Division by zero!" << endl;
                    validOperation = false;
                }
                break;
            case '%':
                if (static_cast<int>(num2) != 0) {
                    result = static_cast<int>(num1) % static_cast<int>(num2);
                    expr = to_string(static_cast<int>(num1)) + " % " + to_string(static_cast<int>(num2));
                } else {
                    cout << "Error: Modulus by zero!" << endl;
                    validOperation = false;
                }
                break;
            default:
                validOperation = false;
                break;
        }
        
        if (validOperation) {
            cout << "\nResult: " << expr << " = " << result << endl;
            history.push_back(Calculation(expr, result));
            saveToFile(expr, result);
        }
    }
    
    // Perform scientific calculation
    void performScientificCalculation() {
        int choice;
        displayScientificMenu();
        cin >> choice;
        
        if (choice == 12) return;
        
        double num, num2, result;
        string expr;
        
        switch (choice) {
            case 1: // Square root
                num = getNumber("Enter number: ");
                if (num >= 0) {
                    result = sqrt(num);
                    expr = "√(" + to_string(num) + ")";
                } else {
                    cout << "Error: Cannot calculate square root of negative number!" << endl;
                    return;
                }
                break;
                
            case 2: // Power
                num = getNumber("Enter base: ");
                num2 = getNumber("Enter exponent: ");
                result = pow(num, num2);
                expr = to_string(num) + "^" + to_string(num2);
                break;
                
            case 3: // Sine
                num = getNumber("Enter angle in degrees: ");
                result = sin(num * M_PI / 180.0);
                expr = "sin(" + to_string(num) + "°)";
                break;
                
            case 4: // Cosine
                num = getNumber("Enter angle in degrees: ");
                result = cos(num * M_PI / 180.0);
                expr = "cos(" + to_string(num) + "°)";
                break;
                
            case 5: // Tangent
                num = getNumber("Enter angle in degrees: ");
                if (fmod(num + 90, 180) != 0) {
                    result = tan(num * M_PI / 180.0);
                    expr = "tan(" + to_string(num) + "°)";
                } else {
                    cout << "Error: Tangent undefined for this angle!" << endl;
                    return;
                }
                break;
                
            case 6: // Logarithm base 10
                num = getNumber("Enter number: ");
                if (num > 0) {
                    result = log10(num);
                    expr = "log10(" + to_string(num) + ")";
                } else {
                    cout << "Error: Logarithm of non-positive number!" << endl;
                    return;
                }
                break;
                
            case 7: // Natural logarithm
                num = getNumber("Enter number: ");
                if (num > 0) {
                    result = log(num);
                    expr = "ln(" + to_string(num) + ")";
                } else {
                    cout << "Error: Logarithm of non-positive number!" << endl;
                    return;
                }
                break;
                
            case 8: // Exponential
                num = getNumber("Enter exponent: ");
                result = exp(num);
                expr = "e^" + to_string(num);
                break;
                
            case 9: // Absolute value
                num = getNumber("Enter number: ");
                result = fabs(num);
                expr = "|" + to_string(num) + "|";
                break;
                
            case 10: // Floor
                num = getNumber("Enter number: ");
                result = floor(num);
                expr = "floor(" + to_string(num) + ")";
                break;
                
            case 11: // Ceil
                num = getNumber("Enter number: ");
                result = ceil(num);
                expr = "ceil(" + to_string(num) + ")";
                break;
                
            default:
                cout << "Invalid choice!" << endl;
                return;
        }
        
        cout << "\nResult: " << expr << " = " << result << endl;
        history.push_back(Calculation(expr, result));
        saveToFile(expr, result);
    }
    
    // Display calculation history
    void displayHistory() {
        if (history.empty()) {
            cout << "\nNo calculations in history." << endl;
            return;
        }
        
        cout << "\nCalculation History:" << endl;
        cout << "====================" << endl;
        for (size_t i = 0; i < history.size(); i++) {
            cout << i + 1 << ". ";
            history[i].display();
        }
    }
    
    // Save history to file manually
    void saveHistoryToFile() {
        ofstream file("manual_save_history.txt");
        if (file.is_open()) {
            for (const auto& calc : history) {
                file << calc.getExpression() << " = " << calc.getResult() << endl;
            }
            file.close();
            cout << "History saved to 'manual_save_history.txt'" << endl;
        } else {
            cout << "Error: Could not save history to file." << endl;
        }
    }
    
    // Load history from file
    void loadHistoryFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            int count = 0;
            
            cout << "\nLoading history from file..." << endl;
            while (getline(file, line)) {
                // Simple parsing - in a real app you'd want more robust parsing
                size_t equalPos = line.find(" = ");
                if (equalPos != string::npos) {
                    string expr = line.substr(0, equalPos);
                    string resultStr = line.substr(equalPos + 3);
                    
                    try {
                        double result = stod(resultStr);
                        history.push_back(Calculation(expr, result));
                        count++;
                    } catch (...) {
                        // Skip invalid lines
                    }
                }
            }
            file.close();
            cout << "Loaded " << count << " calculations from file." << endl;
        } else {
            cout << "No history file found or could not open file." << endl;
        }
    }
    
    // Clear history
    void clearHistory() {
        char confirm;
        cout << "\nAre you sure you want to clear all history? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            history.clear();
            cout << "History cleared." << endl;
        } else {
            cout << "Operation cancelled." << endl;
        }
    }
    
public:
    // Run the calculator
    void run() {
        int choice;
        
        cout << fixed << setprecision(6);
        
        do {
            displayMenu();
            
            if (!(cin >> choice)) {
                cout << "Invalid input! Please enter a number between 1 and 7." << endl;
                clearInputBuffer();
                continue;
            }
            
            switch (choice) {
                case 1:
                    performBasicCalculation();
                    break;
                case 2:
                    performScientificCalculation();
                    break;
                case 3:
                    displayHistory();
                    break;
                case 4:
                    saveHistoryToFile();
                    break;
                case 5:
                    loadHistoryFromFile();
                    break;
                case 6:
                    clearHistory();
                    break;
                case 7:
                    cout << "\nThank you for using the calculator!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 7." << endl;
                    break;
            }
            
            // Pause before clearing screen
            if (choice != 7) {
                cout << "\nPress Enter to continue...";
                clearInputBuffer();
                cin.get();
                
                // Clear screen (platform dependent)
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
            
        } while (choice != 7);
    }
};

// Main function
int main() {
    Calculator calculator;
    calculator.run();
    return 0;
}
