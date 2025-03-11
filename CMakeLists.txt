cmake_minimum_required(VERSION 3.23)
project(GraduationProject CXX)

# ========== 项目设置 ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== 查找依赖库 ==========
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

# ========== 添加头文件 ==========
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/utils)

# ========== 编译库 ==========
add_subdirectory("src/utils")

# ========== 编译子模块 ==========
add_subdirectory("src/watchdog")

# ========== 编译测试文件 ==========
add_subdirectory("playground")

# ========== 编译其他可执行文件 ===========
# add_executable(${PROJECT_NAME} "src/main.cpp")
# target_link_libraries(${PROJECT_NAME} spdlog::spdlog boost::boost)