cmake_minimum_required(VERSION 3.13)  
project(WalmartLuaProject)               
set(CMAKE_CXX_STANDARD 17)            
set(SOURCE_FILES main.cpp)
add_executable(WalmartLua ${SOURCE_FILES})
target_include_directories(WalmartLua
  PRIVATE
    header/)