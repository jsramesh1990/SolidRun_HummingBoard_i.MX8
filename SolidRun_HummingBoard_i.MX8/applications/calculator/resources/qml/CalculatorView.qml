import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: calculatorView
    color: "#1E1E1E"
    
    property int displayHeight: 120
    property int buttonSize: 70
    property int spacing: 5
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10
        
        // Display
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: displayHeight
            color: "#2D2D2D"
            radius: 5
            
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                
                Label {
                    text: calculatorEngine.expression
                    color: "#888888"
                    font.pixelSize: 14
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                    elide: Text.ElideRight
                }
                
                Label {
                    text: calculatorEngine.display
                    color: "white"
                    font.pixelSize: 32
                    font.bold: true
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                }
            }
        }
        
        // Function buttons
        RowLayout {
            spacing: spacing
            Layout.fillWidth: true
            
            CalculatorButton {
                text: "sin"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("sin")
            }
            CalculatorButton {
                text: "cos"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("cos")
            }
            CalculatorButton {
                text: "tan"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("tan")
            }
            CalculatorButton {
                text: "log"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("log")
            }
            CalculatorButton {
                text: "ln"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("ln")
            }
        }
        
        RowLayout {
            spacing: spacing
            Layout.fillWidth: true
            
            CalculatorButton {
                text: "x²"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("x^2")
            }
            CalculatorButton {
                text: "√"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("sqrt")
            }
            CalculatorButton {
                text: "1/x"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("1/x")
            }
            CalculatorButton {
                text: "x!"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputFunction("factorial")
            }
            CalculatorButton {
                text: "π"
                color: "#3F51B5"
                onClicked: calculatorEngine.inputConstant("π")
            }
        }
        
        // Memory buttons
        RowLayout {
            spacing: spacing
            Layout.fillWidth: true
            
            CalculatorButton {
                text: "MC"
                color: "#455A64"
                onClicked: calculatorEngine.memoryClear()
            }
            CalculatorButton {
                text: "MR"
                color: "#455A64"
                onClicked: calculatorEngine.memoryRecall()
            }
            CalculatorButton {
                text: "MS"
                color: "#455A64"
                onClicked: calculatorEngine.memoryStore()
            }
            CalculatorButton {
                text: "M+"
                color: "#455A64"
                onClicked: {
                    calculatorEngine.memoryStore()
                    calculatorEngine.inputOperator("+")
                }
            }
            CalculatorButton {
                text: "M-"
                color: "#455A64"
                onClicked: {
                    calculatorEngine.memoryStore()
                    calculatorEngine.inputOperator("-")
                }
            }
        }
        
        // Main buttons
        GridLayout {
            columns: 4
            rows: 5
            spacing: spacing
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            CalculatorButton {
                text: "C"
                color: "#E53935"
                onClicked: calculatorEngine.clear()
            }
            CalculatorButton {
                text: "CE"
                color: "#E53935"
                onClicked: calculatorEngine.clearEntry()
            }
            CalculatorButton {
                text: "⌫"
                color: "#E53935"
                onClicked: calculatorEngine.backspace()
            }
            CalculatorButton {
                text: "÷"
                color: "#FF8F00"
                onClicked: calculatorEngine.inputOperator("/")
            }
            
            CalculatorButton {
                text: "7"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(7)
            }
            CalculatorButton {
                text: "8"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(8)
            }
            CalculatorButton {
                text: "9"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(9)
            }
            CalculatorButton {
                text: "×"
                color: "#FF8F00"
                onClicked: calculatorEngine.inputOperator("*")
            }
            
            CalculatorButton {
                text: "4"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(4)
            }
            CalculatorButton {
                text: "5"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(5)
            }
            CalculatorButton {
                text: "6"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(6)
            }
            CalculatorButton {
                text: "-"
                color: "#FF8F00"
                onClicked: calculatorEngine.inputOperator("-")
            }
            
            CalculatorButton {
                text: "1"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(1)
            }
            CalculatorButton {
                text: "2"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(2)
            }
            CalculatorButton {
                text: "3"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(3)
            }
            CalculatorButton {
                text: "+"
                color: "#FF8F00"
                onClicked: calculatorEngine.inputOperator("+")
            }
            
            CalculatorButton {
                text: "±"
                color: "#424242"
                onClicked: calculatorEngine.toggleSign()
            }
            CalculatorButton {
                text: "0"
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(0)
            }
            CalculatorButton {
                text: "."
                color: "#424242"
                onClicked: calculatorEngine.inputDigit(-1) // Decimal point
            }
            CalculatorButton {
                text: "="
                color: "#43A047"
                font.pixelSize: 24
                onClicked: calculatorEngine.evaluate()
            }
        }
    }
}
