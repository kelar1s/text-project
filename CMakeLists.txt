cmake_minimum_required(VERSION 3.15)

project(text_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)

add_executable(text_project ${SOURCES})