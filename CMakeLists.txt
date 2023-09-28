cmake_minimum_required(VERSION 3.20.0)

project (rt1 VERSION 1.0 DESCRIPTION "Temp project" LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 11 )

include_directories(src)

file(GLOB SOURCES "src/*.cpp")

message("SOURCES = ${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)
