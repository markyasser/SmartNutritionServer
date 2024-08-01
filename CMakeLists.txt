cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartNutritionServer)

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

# Find Boost
set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/boost_1_81_0)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Include main.cpp in the sources list
file(GLOB SOURCES ${SRC_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB HEADERS ${INCLUDE_DIR}/*.hpp ${INCLUDE_ROUTES}/*.hpp ) 

# Create executable
add_executable(SmartNutritionServer ${SOURCES} ${HEADERS})

# Platform-specific settings
if (WIN32)
    # Windows-specific settings
    if(MSVC)
        # MSVC settings
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    else()
        # MinGW settings
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Windows)
elseif (UNIX)
    # Linux-specific settings
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Linux)
endif()

# Additional settings
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(SmartNutritionServer PRIVATE DEBUG)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")  # Use /Zi for MSVC debug information
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Use -g for GCC/Clang debug information
    endif()
else()
    target_compile_definitions(SmartNutritionServer PRIVATE NDEBUG)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")  # Use /O2 for MSVC optimization
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")  # Use -O2 for GCC/Clang optimization
    endif()
endif()
