cmake_minimum_required(VERSION 3.10)
project(RayTracing LANGUAGES CXX)

file(GLOB SOURCES src/*.cpp include/*.h)

add_executable(RayTracer ${SOURCES} ./main.cpp)

target_include_directories(RayTracer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" 
                                            "${CMAKE_CURRENT_SOURCE_DIR}/Vector"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb")
