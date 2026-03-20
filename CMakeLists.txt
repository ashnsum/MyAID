cmake_minimum_required(VERSION 3.10)
project(MyAID)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(myapp app/Engine/main.cpp)