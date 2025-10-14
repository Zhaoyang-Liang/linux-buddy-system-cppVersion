# Buddy System Design

## 索引计算方法

level 从0开始；
offset 从0开始；
index 从0开始；



## API :



## Architecture:

用树把buddy_st维护起来。buddy_st的level当前buddy节点的树的层数，tree表示他下面有多少的节点。tree的每个节点是一个buddy_st_status，表示节点的状态。

面向用户的时候，用户只能使用offset来访问内存。（长条状）。
