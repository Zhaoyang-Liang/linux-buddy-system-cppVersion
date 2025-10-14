/**
 * @file buddy_system.h
 * @brief 伙伴系统内存管理器模拟接口
 * @date 2025-10-14
 * @copyright Copyright (c) 2025 Zhaoyang-Liang. All rights reserved.
 * 
 * @note 本文件部分设计思路参考了项目：
 *       https://github.com/ucore-test/buddy-system-in-ucore-test
 *       原项目未声明开源许可，本实现仅在学习与研究基础上重新编写，
 *       与原代码实现存在差异。
 */

#ifndef BUDDY_SYSTEM_CPP
#define BUDDY_SYSTEM_CPP

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include "index_caculate.h"

namespace buddy_system {

struct buddy_st* new_buddy(int level) ;

void buddy_delete(struct buddy_st* buddy);

int buddy_alloc(struct buddy_st* buddy, int size);

void buddy_free(struct buddy_st* buddy, int offset);

int buddy_size(struct buddy_st* buddy, int offset);

void buddy_show(struct buddy_st *self);

} // namespace buddy_system





#endif