cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartNutritionServer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOCKET_DIR ${CMAKE_SOURCE_DIR}/socket)

# Include main.cpp in the sources list
file(GLOB SOURCES ${SRC_DIR}/*.cpp ${SOURCE_DIR}/*/cpp ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB HEADERS ${INCLUDE_DIR}/*.hpp ${SOCKET_DIR}/*.hpp)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${SOCKET_DIR})

# Create executable
add_executable(SmartNutritionServer ${SOURCES} ${HEADERS})


# Platform-specific settings
if (WIN32)
    # Windows-specific settings
    target_link_libraries(SmartNutritionServer PRIVATE ws2_32)  # For Winsock on Windows
elseif (UNIX)
    # Linux-specific settings
    find_package(Threads REQUIRED)
    target_link_libraries(SmartNutritionServer PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()