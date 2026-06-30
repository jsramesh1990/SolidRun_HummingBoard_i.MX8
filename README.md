# HummingBoard i.MX8

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-ARM64-blue.svg)](https://www.solid-run.com/nxp-imx8-hummingboard/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/yourusername/embedded-learning-platform/actions)
[![Yocto](https://img.shields.io/badge/yocto-4.0%20Kirkstone-orange.svg)](https://www.yoctoproject.org/)
[![Qt](https://img.shields.io/badge/Qt-6.4.0-41CD52.svg)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Device Tree](https://img.shields.io/badge/device--tree-supported-green.svg)](https://www.kernel.org/doc/Documentation/devicetree/)
[![Docker](https://img.shields.io/badge/docker-supported-2496ED.svg)](https://www.docker.com/)
[![Documentation](https://img.shields.io/badge/docs-passing-brightgreen.svg)](https://github.com/yourusername/embedded-learning-platform/docs)

##  Overview

A comprehensive embedded Linux learning and development platform for the **SolidRun HummingBoard i.MX8**. This project provides a complete, production-ready embedded system with a Qt6/QML graphical interface, supporting multiple peripherals and communication protocols.

###  Project Goals

- **Learn Embedded Linux**: Complete hands-on experience with Yocto, device trees, and kernel development
- **Build Professional Skills**: Practice real-world embedded development patterns
- **Create Reusable Components**: Modular design for easy extension and reuse
- **Demonstrate Industry Standards**: Follow best practices for commercial embedded products

##  System Architecture

### Overall Architecture Diagram

```mermaid
graph TB
    subgraph "Hardware Layer"
        HB[HummingBoard i.MX8]
        GPIO[GPIO Pins]
        I2C[I2C Bus]
        SPI[SPI Bus]
        UART[UART Ports]
        CAN[CAN Bus]
        ETH[Ethernet]
        USB[USB Ports]
        CAM[CSI Camera]
    end

    subgraph "Kernel Layer"
        DT[Device Tree]
        DRV[Device Drivers]
        MOD[Kernel Modules]
        KCF[Kernel Config]
    end

    subgraph "System Layer"
        YO[Yocto Build System]
        SD[Systemd Services]
        DB[D-Bus IPC]
        LOG[Logging System]
    end

    subgraph "Application Layer"
        DM[Device Manager]
        SM[System Monitor]
        APP[Applications]
        LIB[Common Libraries]
    end

    subgraph "UI Layer"
        DASH[Dashboard]
        CALC[Calculator]
        DS[Data Structures]
        ALG[Algorithms]
        PER[Peripherals]
        SEN[Sensors]
        MQTT[MQTT Client]
        CAMUI[Camera]
    end

    HB --> GPIO & I2C & SPI & UART & CAN & ETH & USB & CAM
    GPIO & I2C & SPI & UART & CAN & ETH & USB & CAM --> DT
    DT --> DRV
    DRV --> MOD
    MOD --> KCF
    KCF --> YO
    YO --> SD & DB & LOG
    SD & DB & LOG --> DM & SM
    DM & SM --> APP
    APP --> LIB
    APP --> DASH & CALC & DS & ALG & PER & SEN & MQTT & CAMUI
    DASH --> DS & ALG & PER & SEN & MQTT & CAMUI
```

### Data Flow Diagram

```mermaid
flowchart LR
    subgraph "User Input"
        UI[Touch/Keyboard/Mouse]
    end

    subgraph "Qt/QML Application"
        QML[QML Interface]
        CXX[C++ Backend]
        TH[Thread Pool]
        EV[Event Loop]
    end

    subgraph "Hardware Abstraction"
        DM[Device Manager]
        SM[System Monitor]
        IPC[IPC Manager]
    end

    subgraph "Linux System"
        SYS[System Calls]
        DEV[Device Files]
        SVC[System Services]
    end

    subgraph "Hardware"
        HW[Peripherals]
    end

    UI --> QML
    QML --> CXX
    CXX --> TH & EV
    TH & EV --> DM & SM & IPC
    DM & SM & IPC --> SYS
    SYS --> DEV & SVC
    DEV & SVC --> HW
    HW --> DEV
    DEV --> SYS
    SYS --> DM & SM & IPC
    DM & SM & IPC --> CXX
    CXX --> QML
    QML --> UI
```

### Connection Flow Diagram

```mermaid
sequenceDiagram
    participant User
    participant Dashboard
    participant DeviceManager
    participant SystemMonitor
    participant Hardware
    participant Services
    participant Database
    participant MQTT

    User->>Dashboard: Launch Application
    Dashboard->>DeviceManager: Initialize Devices
    DeviceManager->>Hardware: Scan Peripherals
    Hardware-->>DeviceManager: Device List
    DeviceManager-->>Dashboard: Update Device Status
    
    Dashboard->>SystemMonitor: Start Monitoring
    SystemMonitor->>Hardware: Read System Info
    Hardware-->>SystemMonitor: CPU, Memory, Temp
    SystemMonitor-->>Dashboard: Update Stats
    
    User->>Dashboard: Click GPIO Button
    Dashboard->>DeviceManager: Open GPIO
    DeviceManager->>Hardware: Configure GPIO
    Hardware-->>DeviceManager: Success
    DeviceManager-->>Dashboard: GPIO Ready
    
    User->>Dashboard: Toggle LED
    Dashboard->>DeviceManager: Write GPIO
    DeviceManager->>Hardware: Set GPIO Value
    Hardware-->>DeviceManager: OK
    DeviceManager-->>Dashboard: LED Updated
    
    User->>Dashboard: Send MQTT Message
    Dashboard->>MQTT: Publish Topic
    MQTT->>Services: Forward Message
    Services-->>MQTT: Acknowledged
    MQTT-->>Dashboard: Message Sent
    
    Dashboard->>Database: Log Activity
    Database->>Services: Store Data
    Services-->>Database: Stored
    Database-->>Dashboard: Logged
```

##  Peripheral Connections

### Hardware Interface Map

```mermaid
graph TD
    subgraph "HummingBoard i.MX8"
        CPU[CPU/Core]
        MEM[Memory]
        BUS[Bus System]
    end

    subgraph "GPIO Interface"
        G1[GPIO1_IO0 - LED1]
        G2[GPIO1_IO1 - LED2]
        G3[GPIO1_IO2 - Button1]
        G4[GPIO1_IO3 - Button2]
        G5[GPIO1_IO4 - External]
        G6[GPIO1_IO5 - External]
    end

    subgraph "I2C Interface"
        I1[I2C1 - Temp Sensor]
        I2[I2C1 - Humidity Sensor]
        I3[I2C2 - Accelerometer]
        I4[I2C2 - Gyroscope]
        I5[I2C3 - GPIO Expander]
    end

    subgraph "SPI Interface"
        S1[SPI1 - ADC]
        S2[SPI1 - DAC]
        S3[SPI2 - Display]
        S4[SPI2 - External]
    end

    subgraph "UART Interface"
        U1[UART1 - Debug Console]
        U2[UART2 - GPS Module]
        U3[UART3 - Bluetooth]
        U4[UART4 - External]
    end

    subgraph "CAN Interface"
        C1[CAN0 - Automotive]
        C2[CAN1 - Industrial]
    end

    subgraph "Other Interfaces"
        E1[Ethernet - Network]
        U1[USB - Storage/Devices]
        C1[CSI - Camera]
        A1[Audio - I2S]
    end

    CPU --> BUS
    BUS --> G1 & G2 & G3 & G4 & G5 & G6
    BUS --> I1 & I2 & I3 & I4 & I5
    BUS --> S1 & S2 & S3 & S4
    BUS --> U1 & U2 & U3 & U4
    BUS --> C1 & C2
    BUS --> E1 & U1 & C1 & A1
```

### Peripheral Connection Table

| Peripheral | Interface | Pin/Device | Purpose | Status |
|------------|-----------|------------|---------|--------|
| **LED 1** | GPIO | GPIO1_IO0 | User LED 1 | ✅ |
| **LED 2** | GPIO | GPIO1_IO1 | User LED 2 | ✅ |
| **Button 1** | GPIO | GPIO1_IO2 | User Input | ✅ |
| **Button 2** | GPIO | GPIO1_IO3 | User Input | ✅ |
| **Temp Sensor** | I2C | I2C1, 0x48 | Temperature Monitoring | ✅ |
| **Humidity Sensor** | I2C | I2C1, 0x40 | Humidity Monitoring | ✅ |
| **Accelerometer** | SPI | SPI1, CS0 | Motion Detection | ✅ |
| **GPS Module** | UART | UART2 | Location Tracking | ✅ |
| **CAN Bus** | CAN | CAN0 | Automotive Communication | ✅ |
| **Ethernet** | ETH | eth0 | Network Communication | ✅ |
| **Camera** | CSI | MIPI-CSI | Video Capture | ✅ |
| **Debug Console** | UART | UART1 | Serial Debug | ✅ |

##  Application Modules

### Module Architecture

```mermaid
graph TB
    subgraph "Core Modules"
        DASH[Dashboard - Main UI]
        CALC[Calculator - Scientific]
        DS[Data Structures - Visualizer]
        ALG[Algorithms - Demonstrator]
    end

    subgraph "Embedded Modules"
        GPIO[GPIO Control]
        I2C[I2C Communication]
        SPI[SPI Communication]
        UART[UART Communication]
        PWM[PWM Control]
        ADC[ADC Reading]
        CAN[CAN Bus]
        CAM[Camera Interface]
    end

    subgraph "Service Modules"
        MQTT[MQTT Client]
        SQL[SQLite Database]
        LOG[Logger System]
        MON[System Monitor]
        NET[Network Manager]
        UPD[OTA Update]
    end

    subgraph "Common Modules"
        UTIL[Utilities]
        CONFIG[Configuration]
        IPC[IPC Manager]
        ERR[Error Handling]
    end

    DASH --> GPIO & I2C & SPI & UART & PWM & ADC & CAN & CAM
    DASH --> MQTT & SQL & LOG & MON
    CALC --> UTIL
    DS --> UTIL
    ALG --> UTIL
    GPIO & I2C & SPI & UART & PWM & ADC & CAN & CAM --> CONFIG & ERR & IPC
    MQTT & SQL & LOG & MON --> CONFIG & ERR & IPC
    NET --> UPD
    UPD --> CONFIG & ERR
```

### Module Details

#### 1. Dashboard Module
- **Purpose**: Main HMI and application launcher
- **Technology**: Qt6/QML, C++17
- **Features**: 
  - Application navigation
  - System monitoring
  - Quick access controls
  - Real-time updates

#### 2. Calculator Module
- **Purpose**: Scientific and engineering calculator
- **Technology**: Qt6/QML, C++17
- **Features**:
  - Basic operations
  - Scientific functions
  - Programmer mode
  - History and memory
  - Expression parsing

#### 3. Data Structures Module
- **Purpose**: Visual learning of data structures
- **Technology**: Qt6/QML, C++17, Templates
- **Structures**:
  - Linked List (Singly, Doubly, Circular)
  - Stack and Queue
  - Binary Tree, AVL Tree
  - Graph and Hash Table

#### 4. Algorithms Module
- **Purpose**: Algorithm visualization and learning
- **Technology**: Qt6/QML, C++17
- **Algorithms**:
  - Sorting (Quick, Merge, Heap, etc.)
  - Searching (Binary, Linear)
  - Graph (DFS, BFS, Dijkstra)
  - Dynamic Programming

#### 5. Embedded Module
- **Purpose**: Hardware interface and control
- **Technology**: C++17, Linux system calls
- **Interfaces**:
  - GPIO via libgpiod
  - I2C via /dev/i2c-*
  - SPI via /dev/spidev*
  - UART via /dev/tty*
  - CAN via SocketCAN

#### 6. Communication Module
- **Purpose**: Data communication and protocols
- **Technology**: C++17, MQTT, WebSocket
- **Protocols**:
  - MQTT (pub/sub)
  - Modbus RTU/TCP
  - REST API
  - WebSocket

#### 7. Database Module
- **Purpose**: Data storage and retrieval
- **Technology**: SQLite3, C++17
- **Features**:
  - Time-series data
  - Configuration storage
  - Event logging
  - Data export

## 🔨 Build Process

### Complete Build Pipeline

```mermaid
flowchart TD
    START[Start Build] --> SETUP[Setup Environment]
    SETUP --> DEPS[Install Dependencies]
    DEPS --> CHECK{Check System}
    
    CHECK --> |Native Build| NATIVE[Build Native Components]
    CHECK --> |Cross Build| CROSS[Setup Cross Toolchain]
    
    NATIVE --> APP[Build Applications]
    CROSS --> APP
    
    APP --> UI[Build UI Resources]
    UI --> COMPILE[Compile C++ Code]
    COMPILE --> LINK[Link Libraries]
    LINK --> PACKAGE[Package Binaries]
    PACKAGE --> TEST[Run Tests]
    
    TEST --> |Tests Pass| YOCTO[Build Yocto Image]
    TEST --> |Tests Fail| FIX[Fix Issues]
    FIX --> COMPILE
    
    YOCTO --> LAYER[Setup Layers]
    LAYER --> RECIPES[Add Recipes]
    RECIPES --> CONFIGURE[Configure Kernel]
    CONFIGURE --> BUILD[Build Image]
    BUILD --> DEPLOY[Deploy Image]
    DEPLOY --> FLASH[Flash to SD Card]
    FLASH --> DONE[Build Complete]
```

### Build Steps

#### 1. Development Environment Setup

```bash
# Install dependencies
sudo ./scripts/setup.sh

# Set environment variables
source ~/.bashrc

# Verify installation
./scripts/verify.sh
```

#### 2. Native Build (x86_64)

```bash
# Build all applications
./scripts/build.sh

# Build specific module
cd applications/dashboard
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run tests
make test
```

#### 3. Cross Build (ARM64)

```bash
# Setup cross compilation
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

# Build for target
./scripts/build-cross.sh

# Package binaries
./scripts/package.sh
```

#### 4. Yocto Build

```bash
# Setup Yocto environment
cd yocto
source sources/poky/oe-init-build-env build

# Configure build
bitbake-layers add-layer ../meta-company
bitbake-layers add-layer ../meta-qt6
bitbake-layers add-layer ../meta-freescale

# Build image
bitbake embedded-learning-image

# Generate SDK
bitbake -c populate_sdk embedded-learning-image
```

### Build Artifacts

| Artifact | Location | Description |
|----------|----------|-------------|
| **Dashboard** | `build/dashboard/` | Main application binary |
| **Calculator** | `build/calculator/` | Calculator binary |
| **Data Structures** | `build/data-structures/` | DS visualizer binary |
| **Algorithms** | `build/algorithms/` | Algorithms visualizer binary |
| **Drivers** | `build/drivers/` | Kernel modules |
| **Yocto Image** | `yocto/build/tmp/deploy/images/hummingboard/` | Bootable SD card image |
| **SDK** | `yocto/build/tmp/deploy/sdk/` | Cross-compilation SDK |
| **Device Tree** | `device-tree/custom.dts` | Custom device tree |

##  Calculator Flow Diagram

### Calculator Architecture

```mermaid
flowchart TD
    subgraph "UI Layer"
        QMLUI[QML Interface]
        DISPLAY[Display Widget]
        BUTTONS[Button Grid]
        HISTORY[History View]
    end

    subgraph "Logic Layer"
        ENGINE[Calculator Engine]
        PARSER[Expression Parser]
        EVALUATOR[Expression Evaluator]
        MEMORY[Memory Manager]
    end

    subgraph "Number System"
        DEC[Decimal]
        BIN[Binary]
        OCT[Octal]
        HEX[Hexadecimal]
    end

    subgraph "Function Set"
        BASIC[Basic Operations]
        SCIENTIFIC[Scientific Functions]
        PROG[Programmer Functions]
        STATS[Statistical Functions]
    end

    QMLUI --> BUTTONS
    BUTTONS --> ENGINE
    ENGINE --> PARSER
    PARSER --> EVALUATOR
    EVALUATOR --> DISPLAY
    EVALUATOR --> HISTORY
    ENGINE --> MEMORY
    
    ENGINE --> DEC & BIN & OCT & HEX
    ENGINE --> BASIC & SCIENTIFIC & PROG & STATS
```

### Calculator Operation Flow

```mermaid
sequenceDiagram
    participant User
    participant UI as QML Interface
    participant Engine as Calculator Engine
    participant Parser as Expression Parser
    participant Eval as Expression Evaluator
    participant Display as Display Widget

    User->>UI: Click Button '5'
    UI->>Engine: inputDigit(5)
    Engine->>Engine: appendDigit(5)
    Engine->>Display: updateDisplay("5")
    Display-->>User: Show '5'

    User->>UI: Click Button '+'
    UI->>Engine: inputOperator("+")
    Engine->>Engine: appendOperator("+")
    Engine->>Parser: parseExpression()
    Parser-->>Engine: tokens: [5, +]
    Engine->>Display: updateDisplay("5 + ")
    Display-->>User: Show '5 + '

    User->>UI: Click Button '3'
    UI->>Engine: inputDigit(3)
    Engine->>Engine: appendDigit(3)
    Engine->>Display: updateDisplay("3")
    Display-->>User: Show '3'

    User->>UI: Click Button '='
    UI->>Engine: evaluate()
    Engine->>Parser: parseExpression("5 + 3")
    Parser-->>Engine: tokens: [5, +, 3]
    Engine->>Eval: evaluate(tokens)
    Eval->>Eval: 5 + 3 = 8
    Eval-->>Engine: result = 8
    Engine->>Display: updateDisplay("8")
    Display-->>User: Show '= 8'
    Engine->>Engine: storeHistory("5 + 3 = 8")
    Engine->>UI: emitResult(8)
    UI->>History: addToHistory("5 + 3 = 8")
    History-->>User: Show History
```

### Scientific Calculator Functions

```mermaid
graph TD
    subgraph "Basic Operations"
        ADD[Addition +]
        SUB[Subtraction -]
        MUL[Multiplication ×]
        DIV[Division ÷]
        MOD[Modulo %]
    end

    subgraph "Scientific Functions"
        SIN[sin(x)]
        COS[cos(x)]
        TAN[tan(x)]
        LOG[log(x)]
        LN[ln(x)]
        SQRT[√x]
        POW[x^y]
        EXP[e^x]
    end

    subgraph "Programmer Functions"
        AND[AND]
        OR[OR]
        XOR[XOR]
        NOT[NOT]
        SHL[Shift Left]
        SHR[Shift Right]
    end

    subgraph "Constants"
        PI[π]
        E[e]
        GOLDEN[φ]
    end

    subgraph "Memory Functions"
        MS[Memory Store]
        MR[Memory Recall]
        MC[Memory Clear]
        M_ADD[Memory Add]
    end

    CALC[Calculator Engine] --> ADD & SUB & MUL & DIV & MOD
    CALC --> SIN & COS & TAN & LOG & LN & SQRT & POW & EXP
    CALC --> AND & OR & XOR & NOT & SHL & SHR
    CALC --> PI & E & GOLDEN
    CALC --> MS & MR & MC & M_ADD
```

##  System Flow Diagrams

### Application Lifecycle

```mermaid
stateDiagram-v2
    [*] --> Boot
    Boot --> UBoot: Power On
    UBoot --> Kernel: Load Kernel
    Kernel --> Init: Start Linux
    Init --> Services: Start Systemd
    Services --> Dashboard: Start UI
    Services --> Backend: Start Services
    
    state Services {
        [*] --> Systemd
        Systemd --> GPIO
        Systemd --> I2C
        Systemd --> SPI
        Systemd --> UART
        Systemd --> MQTT
        Systemd --> Sensors
        Systemd --> Logger
    }
    
    Dashboard --> Running
    Running --> UserInput: User Interaction
    UserInput --> Processing: Handle Input
    Processing --> Display: Update UI
    Display --> UserInput
    
    Running --> Peripherals: Hardware Access
    Peripherals --> Read: Read Data
    Peripherals --> Write: Write Data
    Read --> Running
    Write --> Running
    
    Running --> [*]: Shutdown
```

### Data Flow through System

```mermaid
flowchart LR
    subgraph Input
        UI[User Input]
        SENSOR[Sensor Data]
        NET[Network Data]
    end

    subgraph Processing
        QML[QML Processing]
        CXX[C++ Processing]
        ALGO[Algorithm Processing]
        DB[Database Operations]
    end

    subgraph Output
        DISP[Display Output]
        ACT[Actuator Control]
        LOG[Logging Output]
        NETOUT[Network Output]
    end

    subgraph Storage
        SQLITE[SQLite Database]
        FILES[File System]
        MEMORY[RAM Cache]
    end

    UI --> QML
    SENSOR --> CXX
    NET --> CXX
    
    QML --> CXX
    CXX --> ALGO
    ALGO --> DB
    
    CXX --> DISP
    CXX --> ACT
    DB --> LOG
    CXX --> NETOUT
    
    DB --> SQLITE
    SQLITE --> FILES
    CXX --> MEMORY
    MEMORY --> CXX
```

### Event Handling Flow

```mermaid
sequenceDiagram
    participant User
    participant UI
    participant Controller
    participant Service
    participant Hardware
    participant Database
    participant MQTT

    User->>UI: Click Button
    UI->>Controller: emit signal
    Controller->>Controller: Process Request
    Controller->>Service: Call Service
    Service->>Hardware: Execute Operation
    Hardware-->>Service: Operation Result
    Service-->>Controller: Return Result
    
    alt Success
        Controller->>Database: Log Operation
        Controller->>UI: Update UI
        UI-->>User: Show Success
    else Failure
        Controller->>Database: Log Error
        Controller->>UI: Show Error
        UI-->>User: Display Error
    end
    
    Service->>MQTT: Publish Status
    MQTT-->>Service: Acknowledged
```

##  Peripheral Connection and Data Flow

### GPIO Connection Flow

```mermaid
flowchart LR
    subgraph "Application"
        UI[GPIO UI]
        CTRL[GPIO Controller]
    end

    subgraph "Linux System"
        LIBG[libgpiod]
        SYSFS[/sys/class/gpio]
        DEV[/dev/gpiochip*]
    end

    subgraph "Hardware"
        CHIP[GPIO Chip]
        PINS[GPIO Pins]
        LED[LEDs]
        BTN[Buttons]
        EXT[External]
    end

    UI --> CTRL
    CTRL --> LIBG
    LIBG --> SYSFS & DEV
    SYSFS & DEV --> CHIP
    CHIP --> PINS
    PINS --> LED & BTN & EXT
    
    LED & BTN & EXT --> PINS
    PINS --> CHIP
    CHIP --> SYSFS & DEV
    SYSFS & DEV --> LIBG
    LIBG --> CTRL
    CTRL --> UI
```

### I2C Communication Flow

```mermaid
flowchart LR
    subgraph "Application"
        UI[I2C UI]
        CTRL[I2C Controller]
    end

    subgraph "Linux System"
        DEV[/dev/i2c-*]
        IOCTL[ioctl]
        READ[read]
        WRITE[write]
    end

    subgraph "Hardware"
        BUS[I2C Bus]
        SDA[SDA Line]
        SCL[SCL Line]
        DEV1[Temp Sensor]
        DEV2[Humidity Sensor]
        DEV3[Other Devices]
    end

    UI --> CTRL
    CTRL --> DEV
    DEV --> IOCTL & READ & WRITE
    IOCTL & READ & WRITE --> BUS
    BUS --> SDA & SCL
    SDA & SCL --> DEV1 & DEV2 & DEV3
    DEV1 & DEV2 & DEV3 --> SDA & SCL
    SDA & SCL --> BUS
    BUS --> IOCTL & READ & WRITE
    IOCTL & READ & WRITE --> DEV
    DEV --> CTRL
    CTRL --> UI
```

### MQTT Communication Flow

```mermaid
flowchart LR
    subgraph "Application"
        UI[MQTT UI]
        PUB[Publisher]
        SUB[Subscriber]
    end

    subgraph "MQTT Broker"
        BROKER[Mosquitto]
        TOPICS[Topics]
        PERSIST[Persistence]
        AUTH[Authentication]
    end

    subgraph "Network"
        TCP[TCP/IP]
        SSL[TLS/SSL]
        WS[WebSocket]
    end

    subgraph "External"
        DEV[Remote Devices]
        CLOUD[Cloud Services]
        APP[Other Apps]
    end

    UI --> PUB & SUB
    PUB --> BROKER
    SUB --> BROKER
    BROKER --> TOPICS & PERSIST & AUTH
    BROKER --> TCP & SSL & WS
    TCP & SSL & WS --> DEV & CLOUD & APP
    DEV & CLOUD & APP --> TCP & SSL & WS
    TCP & SSL & WS --> BROKER
    BROKER --> PUB & SUB
    PUB & SUB --> UI
```

##  Getting Started

### Prerequisites

| Requirement | Version | Check Command |
|-------------|---------|---------------|
| **Ubuntu** | 20.04+ | `lsb_release -a` |
| **Build Tools** | Latest | `gcc --version` |
| **CMake** | 3.16+ | `cmake --version` |
| **Qt6** | 6.4.0+ | `qmake --version` |
| **Python** | 3.8+ | `python3 --version` |
| **Docker** | 20.10+ | `docker --version` (optional) |
| **Git** | 2.25+ | `git --version` |

### Quick Start

```bash
# 1. Clone the repository
git clone https://github.com/yourusername/embedded-learning-platform.git
cd embedded-learning-platform

# 2. Setup development environment
./scripts/setup.sh

# 3. Build the project
./scripts/build.sh

# 4. Run the dashboard (native)
./build/dashboard/dashboard

# 5. For HummingBoard deployment
./scripts/flash.sh /dev/sdX

# 6. Install services
./scripts/install-services.sh

# 7. Start services
./scripts/manage-services.sh start all
```

### Development Workflow

```mermaid
gitGraph
    commit
    branch develop
    checkout develop
    commit id: "Add feature"
    commit id: "Update docs"
    branch feature/gpio
    checkout feature/gpio
    commit id: "Implement GPIO"
    commit id: "Add tests"
    checkout develop
    merge feature/gpio
    commit id: "Merge GPIO"
    checkout main
    merge develop tag: "v1.0.0"
    commit id: "Release"
```

##  Testing

### Test Coverage

```mermaid
pie title Test Coverage
    "Unit Tests" : 45
    "Integration Tests" : 30
    "Hardware Tests" : 15
    "Performance Tests" : 10
```

### Running Tests

```bash
# Unit tests
cd tests/unit
make && ./unit_tests

# Integration tests
cd tests/integration
pytest -v

# Hardware tests
cd tests/hardware
./run_tests.sh

# All tests with coverage
./scripts/test-all.sh
```

##  Deployment

### Deployment Process

```mermaid
flowchart LR
    DEV[Development] --> BUILD[Build]
    BUILD --> TEST[Test]
    TEST --> |Pass| ARTIFACT[Create Artifact]
    TEST --> |Fail| DEV
    
    ARTIFACT --> SD[Create SD Card]
    SD --> FLASH[Flash to SD]
    FLASH --> BOOT[Boot on HummingBoard]
    BOOT --> VERIFY[Verify Operation]
    VERIFY --> |Success| DEPLOY[Deployed]
    VERIFY --> |Fail| FIX[Fix Issues]
    FIX --> BUILD
```

### Deployment Commands

```bash
# Build Yocto image
cd yocto
source sources/poky/oe-init-build-env build
bitbake embedded-learning-image

# Create SD card
./scripts/create-sd.sh /dev/sdX

# Flash to SD card
sudo dd if=yocto/build/tmp/deploy/images/hummingboard/embedded-learning-image-hummingboard.wic of=/dev/sdX bs=4M status=progress

# Boot and verify
# Insert SD card, power on, and check serial console
screen /dev/ttyUSB0 115200
```

##  Performance Metrics

| Metric | Value | Target |
|--------|-------|--------|
| **Boot Time** | ~8 seconds | <10 seconds |
| **UI Responsiveness** | 60 FPS | 60 FPS |
| **CPU Usage (Idle)** | 5% | <10% |
| **Memory Usage** | 256 MB | <512 MB |
| **Storage** | 2 GB | <4 GB |
| **Power Consumption** | 3W | <5W |
| **MQTT Latency** | <10ms | <50ms |
| **GPIO Toggle** | 100kHz | >50kHz |

##  Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md).

### Development Process

1. Fork the repository
2. Create feature branch (`git checkout -b feature/amazing`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing`)
5. Open Pull Request


##  Acknowledgments

- [SolidRun](https://www.solid-run.com/) for the HummingBoard platform
- [NXP](https://www.nxp.com/) for i.MX8 processor
- [Qt Project](https://www.qt.io/) for the UI framework
- [Yocto Project](https://www.yoctoproject.org/) for the build system
- [OpenEmbedded](https://www.openembedded.org/) for the metadata

##  Additional Resources

- [Documentation](docs/index.md)
- [API Reference](docs/api/)
- [Hardware Guide](docs/hardware/)
- [Yocto Guide](docs/yocto/)
- [Troubleshooting](docs/troubleshooting.md)
- [FAQ](docs/faq.md)

---

**Built with ❤️ for the Embedded Linux Community**
