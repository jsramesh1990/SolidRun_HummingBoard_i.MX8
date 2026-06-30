import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
import socket
import threading
import json
import time
from datetime import datetime

class CalculatorGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculator - Python GUI")
        self.root.geometry("600x800")
        self.root.configure(bg="#2c3e50")
        
        # Connection variables
        self.host = "localhost"
        self.port = 8080
        self.socket = None
        self.connected = False
        
        # Calculator state
        self.current_input = ""
        self.memory_value = 0
        self.history = []
        
        # Create fonts
        self.title_font = ("Helvetica", 18, "bold")
        self.display_font = ("Courier", 24)
        self.button_font = ("Arial", 12)
        
        # Setup UI
        self.setup_ui()
        
        # Try to connect to backend
        self.connect_to_backend()
        
        # Bind keyboard events
        self.root.bind('<Key>', self.key_press)
        self.root.bind('<Return>', lambda e: self.calculate())
        self.root.bind('<Escape>', lambda e: self.clear_all())
        self.root.bind('<Delete>', lambda e: self.clear_entry())
        
        # Handle window closing
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def setup_ui(self):
        # Main container
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(0, weight=1)
        for i in range(10):
            main_frame.rowconfigure(i, weight=1)
        
        # Connection status
        self.status_frame = ttk.Frame(main_frame)
        self.status_frame.grid(row=0, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 10))
        
        self.status_label = ttk.Label(
            self.status_frame,
            text="🔴 Disconnected from C++ Backend",
            font=("Arial", 10, "bold"),
            foreground="red"
        )
        self.status_label.grid(row=0, column=0, sticky=tk.W)
        
        # Connection controls
        ttk.Button(
            self.status_frame,
            text="Reconnect",
            command=self.reconnect,
            width=10
        ).grid(row=0, column=1, padx=5)
        
        ttk.Button(
            self.status_frame,
            text="Disconnect",
            command=self.disconnect,
            width=10
        ).grid(row=0, column=2, padx=5)
        
        # Title
        title_label = ttk.Label(
            main_frame,
            text="CALCULATOR GUI (Python Frontend)",
            font=self.title_font,
            foreground="#3498db"
        )
        title_label.grid(row=1, column=0, columnspan=4, pady=(0, 20))
        
        # Display frame
        display_frame = ttk.Frame(main_frame)
        display_frame.grid(row=2, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 20))
        
        # Entry widget for display
        self.display_var = tk.StringVar()
        self.display_entry = ttk.Entry(
            display_frame,
            textvariable=self.display_var,
            font=self.display_font,
            justify='right',
            state='readonly',
            width=25
        )
        self.display_entry.grid(row=0, column=0, sticky=(tk.W, tk.E), ipady=10)
        display_frame.columnconfigure(0, weight=1)
        
        # Memory display
        self.memory_label = ttk.Label(
            main_frame,
            text="Memory: 0",
            font=("Arial", 10),
            foreground="#95a5a6"
        )
        self.memory_label.grid(row=3, column=0, columnspan=4, sticky=tk.W, pady=(0, 10))
        
        # History display
        history_frame = ttk.LabelFrame(main_frame, text="Calculation History", padding="5")
        history_frame.grid(row=4, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 20))
        
        self.history_text = scrolledtext.ScrolledText(
            history_frame,
            height=6,
            width=50,
            font=("Consolas", 10),
            state='disabled'
        )
        self.history_text.grid(row=0, column=0, sticky=(tk.W, tk.E))
        history_frame.columnconfigure(0, weight=1)
        
        # Basic buttons frame
        basic_frame = ttk.LabelFrame(main_frame, text="Basic Operations", padding="5")
        basic_frame.grid(row=5, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 10))
        
        # Number buttons
        num_buttons = [
            ('7', 0, 0), ('8', 0, 1), ('9', 0, 2), ('/', 0, 3),
            ('4', 1, 0), ('5', 1, 1), ('6', 1, 2), ('*', 1, 3),
            ('1', 2, 0), ('2', 2, 1), ('3', 2, 2), ('-', 2, 3),
            ('0', 3, 0), ('.', 3, 1), ('=', 3, 2), ('+', 3, 3),
        ]
        
        for (text, row, col) in num_buttons:
            if text == '=':
                btn = ttk.Button(
                    basic_frame,
                    text=text,
                    command=self.calculate,
                    style='Accent.TButton'
                )
            else:
                btn = ttk.Button(
                    basic_frame,
                    text=text,
                    command=lambda t=text: self.button_click(t),
                    width=5
                )
            btn.grid(row=row, column=col, padx=2, pady=2)
        
        # Control buttons
        control_frame = ttk.Frame(main_frame)
        control_frame.grid(row=6, column=0, columnspan=4, pady=(0, 10))
        
        control_buttons = [
            ('C', self.clear_all),
            ('CE', self.clear_entry),
            ('⌫', self.backspace),
            ('%', lambda: self.send_command("PERCENT", self.current_input)),
            ('±', lambda: self.send_command("NEGATE", self.current_input)),
            ('1/x', lambda: self.send_command("RECIPROCAL", self.current_input)),
        ]
        
        for i, (text, command) in enumerate(control_buttons):
            ttk.Button(
                control_frame,
                text=text,
                command=command,
                width=8
            ).grid(row=0, column=i, padx=2)
        
        # Scientific buttons frame
        sci_frame = ttk.LabelFrame(main_frame, text="Scientific Functions", padding="5")
        sci_frame.grid(row=7, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 10))
        
        scientific_buttons = [
            ('sin', 'SIN'), ('cos', 'COS'), ('tan', 'TAN'), ('√', 'SQRT'),
            ('x²', lambda: self.send_command("POW", f"{self.current_input} 2")),
            ('x^y', self.power_dialog), ('log', 'LOG'), ('ln', 'LN'),
            ('e^x', 'EXP'), ('x!', 'FACT'), ('π', self.insert_pi), ('e', self.insert_e),
        ]
        
        # Create scientific buttons in 3x4 grid
        for i, (text, command) in enumerate(scientific_buttons):
            row = i // 4
            col = i % 4
            if callable(command):
                btn = ttk.Button(
                    sci_frame,
                    text=text,
                    command=command,
                    width=8
                )
            else:
                btn = ttk.Button(
                    sci_frame,
                    text=text,
                    command=lambda cmd=command: self.send_command(cmd, self.current_input),
                    width=8
                )
            btn.grid(row=row, column=col, padx=2, pady=2)
        
        # Memory operations frame
        mem_frame = ttk.LabelFrame(main_frame, text="Memory Operations", padding="5")
        mem_frame.grid(row=8, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=(0, 10))
        
        memory_buttons = [
            ('M+', 'MADD'), ('M-', 'MSUB'), ('MR', 'MR'), ('MC', 'MC'),
        ]
        
        for i, (text, command) in enumerate(memory_buttons):
            ttk.Button(
                mem_frame,
                text=text,
                command=lambda cmd=command: self.send_command(cmd, self.current_input),
                width=10
            ).grid(row=0, column=i, padx=5)
        
        # History operations frame
        hist_frame = ttk.Frame(main_frame)
        hist_frame.grid(row=9, column=0, columnspan=4, pady=(10, 0))
        
        hist_buttons = [
            ('View History', self.view_history),
            ('Clear History', self.clear_history),
            ('Save History', self.save_history),
            ('Load History', self.load_history),
        ]
        
        for i, (text, command) in enumerate(hist_buttons):
            ttk.Button(
                hist_frame,
                text=text,
                command=command,
                width=12
            ).grid(row=0, column=i, padx=2)
        
        # Configure styles
        self.configure_styles()
    
    def configure_styles(self):
        style = ttk.Style()
        style.theme_use('clam')
        
        # Configure colors
        style.configure('TButton', font=self.button_font)
        style.configure('Accent.TButton', background='#3498db', foreground='white')
        
        # Configure entry
        style.configure('TEntry', fieldbackground='#ecf0f1', font=self.display_font)
    
    def connect_to_backend(self):
        """Connect to the C++ backend server"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.settimeout(2)
            self.socket.connect((self.host, self.port))
            self.connected = True
            self.status_label.config(text="🟢 Connected to C++ Backend", foreground="green")
            print("Connected to C++ backend")
            
            # Start a thread to receive updates
            self.receive_thread = threading.Thread(target=self.receive_updates, daemon=True)
            self.receive_thread.start()
            
        except Exception as e:
            self.connected = False
            self.status_label.config(text="🔴 Disconnected from C++ Backend", foreground="red")
            print(f"Failed to connect to C++ backend: {e}")
    
    def reconnect(self):
        """Reconnect to the backend"""
        if self.socket:
            self.socket.close()
        self.connect_to_backend()
    
    def disconnect(self):
        """Disconnect from backend"""
        if self.socket:
            self.send_command("EXIT", "")
            self.socket.close()
            self.connected = False
            self.status_label.config(text="🔴 Disconnected from C++ Backend", foreground="red")
    
    def send_command(self, command, param=None):
        """Send a command to the C++ backend"""
        if not self.connected:
            messagebox.showerror("Connection Error", "Not connected to C++ backend")
            return None
        
        try:
            # Format command
            if param and param.strip():
                cmd = f"{command} {param.strip()}"
            else:
                cmd = command
            
            # Send command
            self.socket.send(cmd.encode('utf-8'))
            
            # Receive response
            response = self.socket.recv(1024).decode('utf-8')
            
            # Parse response
            return self.parse_response(response)
            
        except Exception as e:
            print(f"Error sending command: {e}")
            messagebox.showerror("Communication Error", f"Failed to communicate with backend: {e}")
            return None
    
    def parse_response(self, response):
        """Parse response from C++ backend"""
        parts = response.split('|', 3)
        
        if len(parts) < 3:
            return {"status": "ERROR", "message": "Invalid response format"}
        
        status = parts[0]
        expression = parts[1]
        result_str = parts[2]
        error_msg = parts[3] if len(parts) > 3 else ""
        
        try:
            result = float(result_str) if result_str else 0
        except:
            result = 0
        
        if status == "SUCCESS":
            # Update display if there's a result
            if expression and result != 0:
                self.current_input = str(result)
                self.display_var.set(self.current_input)
                
                # Add to history
                self.add_to_history(expression, result)
            
            # Handle special cases
            if expression == "Memory Recall":
                self.memory_value = result
                self.memory_label.config(text=f"Memory: {self.memory_value}")
            elif expression.startswith("M +") or expression.startswith("M -"):
                self.memory_value = result
                self.memory_label.config(text=f"Memory: {self.memory_value}")
            
            return {"status": "SUCCESS", "expression": expression, "result": result}
        else:
            messagebox.showerror("Calculation Error", error_msg or "Unknown error occurred")
            return {"status": "ERROR", "message": error_msg}
    
    def add_to_history(self, expression, result):
        """Add calculation to history"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        entry = f"{timestamp}: {expression} = {result}"
        self.history.append(entry)
        
        # Update history display
        self.update_history_display()
    
    def update_history_display(self):
        """Update the history text widget"""
        self.history_text.config(state='normal')
        self.history_text.delete(1.0, tk.END)
        for entry in self.history[-10:]:  # Show last 10 entries
            self.history_text.insert(tk.END, entry + "\n")
        self.history_text.config(state='disabled')
        self.history_text.see(tk.END)
    
    def receive_updates(self):
        """Thread to receive updates from backend"""
        while self.connected:
            try:
                # This could be extended to receive push updates from backend
                time.sleep(1)
            except:
                break
    
    # GUI Event Handlers
    def button_click(self, char):
        """Handle button clicks"""
        self.current_input += str(char)
        self.display_var.set(self.current_input)
    
    def calculate(self):
        """Calculate the current expression"""
        if not self.current_input:
            return
        
        # Send calculation to backend
        response = self.send_command("EVAL", self.current_input)
        
        if response and response["status"] == "SUCCESS":
            # Update display with result
            self.current_input = str(response["result"])
            self.display_var.set(self.current_input)
    
    def clear_all(self):
        """Clear all input"""
        self.current_input = ""
        self.display_var.set("")
    
    def clear_entry(self):
        """Clear current entry"""
        self.current_input = ""
        self.display_var.set("")
    
    def backspace(self):
        """Delete last character"""
        self.current_input = self.current_input[:-1]
        self.display_var.set(self.current_input)
    
    def insert_pi(self):
        """Insert pi constant"""
        self.current_input = "3.14159265359"
        self.display_var.set(self.current_input)
    
    def insert_e(self):
        """Insert e constant"""
        self.current_input = "2.71828182846"
        self.display_var.set(self.current_input)
    
    def power_dialog(self):
        """Show dialog for power operation"""
        if not self.current_input:
            messagebox.showwarning("Input Required", "Enter base value first")
            return
        
        dialog = tk.Toplevel(self.root)
        dialog.title("Power Operation")
        dialog.geometry("300x150")
        dialog.transient(self.root)
        dialog.grab_set()
        
        ttk.Label(dialog, text="Enter exponent:").pack(pady=10)
        
        exponent_var = tk.StringVar()
        entry = ttk.Entry(dialog, textvariable=exponent_var, font=("Arial", 12))
        entry.pack(pady=5, padx=20, fill=tk.X)
        entry.focus()
        
        def apply_power():
            exponent = exponent_var.get()
            if exponent:
                self.send_command("POW", f"{self.current_input} {exponent}")
                dialog.destroy()
        
        button_frame = ttk.Frame(dialog)
        button_frame.pack(pady=10)
        
        ttk.Button(button_frame, text="Apply", command=apply_power).pack(side=tk.LEFT, padx=5)
        ttk.Button(button_frame, text="Cancel", command=dialog.destroy).pack(side=tk.LEFT, padx=5)
        
        dialog.bind('<Return>', lambda e: apply_power())
    
    def view_history(self):
        """View complete history from backend"""
        response = self.send_command("HISTORY", "")
        if response and response["status"] == "SUCCESS":
            # Parse history data
            if len(response.get("expression", "").split(";")) > 1:
                history_items = response["expression"].split(";")
                history_text = "\n".join(history_items)
                messagebox.showinfo("Complete History", history_text)
    
    def clear_history(self):
        """Clear calculation history"""
        if messagebox.askyesno("Clear History", "Are you sure you want to clear all history?"):
            response = self.send_command("CLEAR_HISTORY", "")
            if response and response["status"] == "SUCCESS":
                self.history.clear()
                self.update_history_display()
                messagebox.showinfo("Success", "History cleared successfully")
    
    def save_history(self):
        """Save history to file"""
        response = self.send_command("SAVE_HISTORY", "")
        if response and response["status"] == "SUCCESS":
            messagebox.showinfo("Success", f"History saved with {response['result']} entries")
    
    def load_history(self):
        """Load history from file"""
        response = self.send_command("LOAD_HISTORY", "")
        if response:
            if response["status"] == "SUCCESS":
                messagebox.showinfo("Success", f"Loaded {response['result']} history entries")
                # Refresh history display
                self.view_history()
    
    def key_press(self, event):
        """Handle keyboard input"""
        key = event.char
        
        if key.isdigit() or key in '+-*/.()':
            self.button_click(key)
        elif key == '\x08':  # Backspace
            self.backspace()
        elif key == '\r':  # Enter
            self.calculate()
        elif key == '\x1b':  # Escape
            self.clear_all()
    
    def on_closing(self):
        """Handle window closing"""
        self.disconnect()
        self.root.destroy()

def main():
    root = tk.Tk()
    app = CalculatorGUI(root)
    
    # Center window
    root.update_idletasks()
    width = root.winfo_width()
    height = root.winfo_height()
    x = (root.winfo_screenwidth() // 2) - (width // 2)
    y = (root.winfo_screenheight() // 2) - (height // 2)
    root.geometry(f'{width}x{height}+{x}+{y}')
    
    root.mainloop()

if __name__ == "__main__":
    main()
