cmake_minimum_required(VERSION 3.16)
project(Dashboard VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 QuickLayouts SerialPort Mqtt Sql)

set(SOURCES
    src/main.cpp
    src/AppController.cpp
    src/DeviceManager.cpp
    src/SystemMonitor.cpp
)

set(HEADERS
    src/AppController.h
    src/DeviceManager.h
    src/SystemMonitor.h
)

qt6_add_resources(RESOURCES resources/resources.qrc)

add_executable(dashboard ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(dashboard
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickLayouts
    Qt6::SerialPort
    Qt6::Mqtt
    Qt6::Sql
)

qt6_target_compile_definitions(dashboard)

install(TARGETS dashboard DESTINATION bin)
