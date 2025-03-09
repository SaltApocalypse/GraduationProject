cmake_minimum_required(VERSION 3.23)
project(GraduationProject CXX)

# ========== 项目设置 ==========
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENABLE_PLAYGROUND True) # 编译测试文件

# ========== 编译库 ==========
# 设置库文件输出目录
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件
set(LIB_SIGNAL ${PROJECT_SOURCE_DIR}/src/utils/Signal.cpp)

# 编译静态库
add_library(Signal STATIC ${LIB_SIGNAL})

# 设置库文件的输出目录
set_target_properties(Signal PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY}
    LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY}
)

# ========== 编译测试文件 ==========
if(DEFINED ENABLE_PLAYGROUND)
    add_subdirectory("playground")
endif()

# ========== 查找依赖库 ==========
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

# ========== 编译子模块 ==========
add_subdirectory("src/watchdog")

# ========== 编译其他可执行文件 ===========
# add_executable(${PROJECT_NAME} "src/main.cpp")
# target_link_libraries(${PROJECT_NAME} spdlog::spdlog boost::boost)