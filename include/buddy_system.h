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