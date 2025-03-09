cmake_minimum_required(VERSION 3.23)

get_filename_component(PLAYGROUND ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PLAYGROUND} CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 管理库
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

# 设置链接库
set(EXTRA_LIBS boost::boost)

# 遍历每个文件并编译
file(GLOB CPP_FILES "*.cpp")

foreach(CPP_FILE ${CPP_FILES})
    # 对每个文件获取文件名
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
    
    target_link_libraries(${EXECUTABLE_NAME} ${EXTRA_LIBS} ${spdlog_LIBRARIES})
endforeach()