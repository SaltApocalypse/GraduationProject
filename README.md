# 简介

毕业设计，新数据开放平台

写着写着想起来可以拿来熟悉一下 CMake 和之前没摸成的 Conan。

# 部署

``` bash
# 系统：目前用的 Ubuntu-22.04

# 部署 Conan 包管理工具 和 CMake
sudo apt install python3-pip # 新装好的应该没有 pip
sudo snap cmake --classic # 2204 apt 源的 cmake 版本是 3.22，用了 `--preset` 参数需要 Cmake >= 3.23
pip install conan

conan profile detect # 自动创建 Conan 配置

conan install . --output-folder=build --build=missing # 根据 conanfile.py 部署第三方包
cmake --preset conan-release         # 使用 conan 生成的预设来配置项目
cmake --build --preset conan-release # 构建项目

# 这句留着给我复制的
code ~/.bashrc
alias build='cmake --preset conan-release && cmake --build --preset conan-release'
source ~/.bashrc
```

# TODO:

- [ ] 熟悉 CMake
- [ ] 熟悉 Conan
- [ ] 写完毕设
- [ ] 做成 Docker 容器
- [ ] 试一下 CI/CD

# 踩坑

## `CMake Tools` 报错：IntelliSense 未获取到 Conan 生成的依赖路径

1. 在 CMakeLists 中添加了 `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`，重新生成构建文件会出现 `compile_commands.json`（在我的预设下路径应该是 `${workspaceFolder}/build/build/Release/compile_commands.json`）。
2. 打开 `C/C++` 扩展的配置，手动配置：`C/C++ Configurations -> Advanced Settings -> Compile commands`，输入前一步最后 compile_commands.json 的路径。

# 笔记，避免隔几天回来忘完所以给自己做的

1. `playground` 是一些单独的测试，目录下有自己的编译配置，除了加依赖库别的不用再管了。
2. 库和模块要在根目录的编译配置项里写。没有 `lib` 目录直接跑一遍构建。