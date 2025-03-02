cmake_minimum_required(VERSION 3.23)
project(GraduationProject CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} spdlog::spdlog boost::boost)