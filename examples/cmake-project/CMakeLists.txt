cmake_minimum_required(VERSION 3.0)

project(app)

find_package(Fluidika REQUIRED)

add_executable(app main.cpp)

target_link_libraries(app Fluidika::Fluidika)
