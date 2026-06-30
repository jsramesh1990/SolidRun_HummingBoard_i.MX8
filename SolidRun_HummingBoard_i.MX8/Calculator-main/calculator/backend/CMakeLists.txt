cmake_minimum_required(VERSION 3.10)
project(CalculatorBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(calculator_backend 
    calculator.cpp
    main.cpp
)

# Windows specific settings
if(WIN32)
    target_link_libraries(calculator_backend ws2_32)
endif()

# Set output directory
set_target_properties(calculator_backend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
