# Makefile for Buddy System Project

# 编译器设置
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I include

# 目录设置
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# 源文件和目标文件
SOURCES = $(SRC_DIR)/buddy_system.cpp
OBJECTS = $(BUILD_DIR)/buddy_system.o
TARGET = test
MAIN_SOURCE = test.cpp

# 默认目标
all: $(TARGET)

# 创建构建目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 编译目标文件
$(BUILD_DIR)/buddy_system.o: $(SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译主程序
$(TARGET): $(OBJECTS) $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(MAIN_SOURCE) -o $@

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理生成的文件
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# 重新编译
rebuild: clean all

# 调试版本
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)

# 发布版本
release: CXXFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# 检查代码风格（如果有clang-format）
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SOURCES) $(MAIN_SOURCE) $(INCLUDE_DIR)/*.h; \
		echo "代码格式化完成"; \
	else \
		echo "clang-format 未安装，跳过格式化"; \
	fi

# 显示帮助信息
help:
	@echo "可用的目标:"
	@echo "  all      - 编译程序 (默认)"
	@echo "  run      - 编译并运行程序"
	@echo "  clean    - 清理生成的文件"
	@echo "  rebuild  - 重新编译"
	@echo "  debug    - 编译调试版本"
	@echo "  release  - 编译发布版本"
	@echo "  format   - 格式化代码"
	@echo "  help     - 显示此帮助信息"

# 声明伪目标
.PHONY: all run clean rebuild debug release format help

# 确保目录存在
$(OBJECTS): | $(BUILD_DIR)
