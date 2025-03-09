cmake_minimum_required(VERSION 3.23)
get_filename_component(SUB_MODULE ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${SUB_MODULE} CXX)

# ========== 项目设置 ==========
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 设置库文件地址，在主项目中
set(LIB_PATH ${PROJECT_SOURCE_DIR}/../..)

# ========== 查找依赖库 ==========
# find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

# ========== 编译各个子模块 ==========
# 调度模块
add_executable(Scheduler "src/Scheduler.cpp")
target_link_libraries(Scheduler boost::boost ${LIB_PATH}/lib/libSignal.a)