cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartNutritionServer)

set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/boost_1_81_0/boost)
add_subdirectory(libs/Crow)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_ROUTES ${CMAKE_SOURCE_DIR}/routes)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_ROUTES})

# Include main.cpp in the sources list
file(GLOB SOURCES ${SRC_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB HEADERS ${INCLUDE_DIR}/*.hpp ${INCLUDE_ROUTES}/*.hpp ) 

# Create executable
add_executable(SmartNutritionServer ${SOURCES} ${HEADERS})

# target_include_directories(SmartNutritionServer PUBLIC ${INCLUDE_PATHS})
target_link_libraries(SmartNutritionServer PUBLIC Crow::Crow)