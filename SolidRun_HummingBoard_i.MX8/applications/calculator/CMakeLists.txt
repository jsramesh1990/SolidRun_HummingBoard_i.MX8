cmake_minimum_required(VERSION 3.16)
project(Calculator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 QuickLayouts)

set(SOURCES
    src/main.cpp
    src/CalculatorEngine.cpp
)

set(HEADERS
    src/CalculatorEngine.h
)

qt6_add_resources(RESOURCES resources/resources.qrc)

add_executable(calculator ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(calculator
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickLayouts
)

install(TARGETS calculator DESTINATION bin)
