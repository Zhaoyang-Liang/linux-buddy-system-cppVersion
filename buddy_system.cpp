#include "buddy_system.h"


namespace buddy_system {

#define NODE_UNUSED 0
#define NODE_USED 1  // 只有最底层节点可能是这个状态
#define NODE_SPLIT 2
#define NODE_FULL 3


struct buddy_st {
    int level;
    unsigned char tree[];
};

struct buddy_st* new_buddy(int level) {
    int last_level_node_num = 1 << level ; 
    int all_node_num = 2 * last_level_node_num - 1;

    // 要给一个结构体分配结构体本身的大小加上柔性数组的大小；
    struct buddy_st* buddy = (struct buddy_st*)malloc(sizeof(struct buddy_st) + all_node_num * sizeof(unsigned char));

    buddy->level = level;
    memset(buddy->tree, NODE_UNUSED, all_node_num*sizeof(unsigned char));

    return buddy;
}

void free_buddy(struct buddy_st* buddy){
    free(buddy);
}

void _mark_parent(struct buddy_st* buddy, int index){
    /**
     * @brief 在分配某个index节点的时候，父亲如果不满就是split，满了就是full
     * @param buddy : 头节点
     * @param index : cur_index （child）
     */

    while(true){

        int brother_node_index = brother_index(index);
        if(brother_node_index >= 0 &&( buddy->tree[brother_node_index] == NODE_USED || buddy->tree[brother_node_index] == NODE_FULL )){
            int parent_node_index = parent_index(index);
            buddy->tree[parent_node_index] = NODE_FULL;
            continue; // 继续向上标记
        }else{
            break; // 标记结束
        }        
    }
    return ;
}


int buddy_alloc(struct buddy_st* buddy, int size_needed){
    /**
     * @brief 分配内存
     * @param buddy : 头节点
     * @param size_needed : 请求分配的内存大小
     * 
     * @return 分配的内存大小，失败返回-1
     */
    int size_to_alloc ;
    int max_level_length = 1 << buddy->level;

    assert(size_needed > 0);
    
    if(size_needed == 0){
        // 如果要分配0个字节，则分配1个字节
        size_to_alloc = 1 ;
    }else{
        size_to_alloc = next_pow_of_2(size_needed);
    } 

    if(max_level_length < size_to_alloc){
        return -1;
    }

    int cur_index = 0 ;
    int cur_level = 0 ;
    int cur_length = max_level_length;
    // 从根节点开始，找到第一个可以分配的节点

    while(true){
        // 当前可以就分配，不可看左侧，一直看左侧，到头看右侧，之后回溯看右侧
        if(size_to_alloc == cur_length){
            if(buddy->tree[cur_index] == NODE_UNUSED){
                buddy->tree[cur_index] = NODE_USED;
                _mark_parent(buddy, cur_index);
                return index2offset(cur_index, cur_level, buddy->level);
            }
        }else if(size_to_alloc < cur_length) { // 当前控制层的offset过大，不合适，需要分配各更小的
           
            if(buddy->tree[cur_index] == NODE_UNUSED){ // unused（是第一次分配控制节点或者是树枝）
                // 如果当前节点是 UNUSED，则拆分它并向左子继续

                buddy->tree[cur_index] = NODE_SPLIT;
                // buddy->tree[left_child_index(cur_index)] = NODE_UNUSED;
                // buddy->tree[right_child_index(cur_index)] = NODE_UNUSED;

                cur_index = left_child_index(cur_index);
                cur_length = cur_length / 2;
                cur_level++;
                continue;
            }else if (buddy->tree[cur_index] == NODE_SPLIT){ 
                // 节点被拆分过，继续向左子搜索
                cur_index = left_child_index(cur_index);
                cur_length /= 2;
                cur_level++;
                continue;
            }else if (buddy->tree[cur_index] == NODE_USED || buddy->tree[cur_index] == NODE_FULL){
                // 当前节点被使用或者满了，向右子搜索
            }
        }

        if(cur_index & 1 == 1){ // isleft
            cur_index ++ ; // 向右一个节点
            continue; // 看看右侧节点是否可行
        }

        while(true){ // 回溯到父亲节点
            cur_level -- ;
            cur_index = parent_index(cur_index);
            cur_length = cur_length * 2;
            if(cur_index < 0){
                std::cout << "alloc failed" << std::endl;
                return -1;
            }
            if(cur_index & 1 == 1){
                cur_index++ ; // 看父亲的右侧节点
                break;
            }       
        }       
    }
   
    // return 0;
}








} // namespace buddy_system
