cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartNutritionServer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(ROUTES_DIR ${CMAKE_SOURCE_DIR}/routes)


# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${ROUTES_DIR})

set(MIDDLEWARES_DIR ${INCLUDE_DIR}/middlewares)
include_directories(${MIDDLEWARES_DIR})

# Include main.cpp in the sources list
file(GLOB SOURCES ${SRC_DIR}/*.cpp ${ROUTES_DIR}/*.cpp  ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB HEADERS ${INCLUDE_DIR}/*.hpp ${ROUTES_DIR}/*.hpp ) 

# Create executable
add_executable(SmartNutritionServer ${SOURCES} ${HEADERS})

# Find the Crow package
set(CROW_DIR ${CMAKE_SOURCE_DIR}/lib/cmake/Crow)
find_package(Crow REQUIRED CONFIG PATHS ${CROW_DIR})
target_include_directories(SmartNutritionServer PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SmartNutritionServer PUBLIC Crow::Crow)