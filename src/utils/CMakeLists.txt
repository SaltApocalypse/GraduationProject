cmake_minimum_required(VERSION 3.23)
project(Library CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== 设置根目录 ==========
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/../..)

# ========== 设置库文件输出目录 ==========
set(LIBRARY_OUTPUT_DIRECTORY "${SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})

# ========== 查找依赖库 ==========
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

# ========== 查找头文件 ==========
include_directories(${SOURCE_DIR}/include)

# ========== 编译库 ==========
# LOGGER
add_library(Logger STATIC ${PROJECT_SOURCE_DIR}/Logger.cpp)
target_link_libraries(Logger PRIVATE spdlog::spdlog)

# SCHEDULER
add_library(Scheduler STATIC ${PROJECT_SOURCE_DIR}/Scheduler.cpp)
target_link_libraries(Scheduler Boost::boost)

