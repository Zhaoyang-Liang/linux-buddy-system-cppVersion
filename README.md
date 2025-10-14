# Buddy System 项目

一个用C++实现的伙伴系统内存管理器。

## 项目结构

```
OS_lab/
├── CMakeLists.txt          # CMake构建文件
├── test.cpp               # 测试程序
├── include/               # 头文件目录
│   ├── buddy_system.h     # 伙伴系统头文件
│   └── index_caculate.h   # 索引计算头文件
└── src/                   # 源文件目录
    └── buddy_system.cpp   # 伙伴系统实现
```

## 构建和运行

### 使用CMake（推荐）

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 编译
make

# 运行测试
./test
```

## 功能特性

- 内存分配和释放
- 自动内存合并
- 内存大小查询
- 可视化内存树显示
- 支持0字节分配（转换为1字节）

## 测试说明

测试程序包含7个测试用例，验证了伙伴系统的各种功能：
1. 基本分配功能
2. 大块分配
3. 小块分配
4. 中等块分配
5. 内存释放和合并
6. 最大分配测试
7. 边界情况测试
