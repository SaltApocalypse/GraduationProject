cmake_minimum_required(VERSION 3.23)
project(GraduationProject CXX)

find_package(spdlog REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)