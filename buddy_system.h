#ifndef BUDDY_SYSTEM_CPP
#define BUDDY_SYSTEM_CPP

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "index_caculate.h"

struct buddy_st* new_buddy(int level) ;

void buddy_delete(struct buddy *);

int buddy_alloc(struct buddy *, int size);

void buddy_free(struct buddy *, int offset);

int buddy_size(struct buddy *, int offset);





#endif