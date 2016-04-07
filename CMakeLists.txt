cmake_minimum_required(VERSION 3.2)
project(rabin)

#============================================================================
# Internal compiler options
#============================================================================

# Setting compiler properties
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

#============================================================================
# Compile targets
#============================================================================

add_library(${PROJECT_NAME} rabin.c rabin.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}-exec main.cpp)
target_link_libraries(${PROJECT_NAME}-exec ${PROJECT_NAME})