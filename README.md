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
```

# TODO:

- [ ] 熟悉 CMake
- [ ] 熟悉 Conan
- [ ] 写完毕设
- [ ] 做成 Docker 容器
- [ ] 试一下 CI/CD

