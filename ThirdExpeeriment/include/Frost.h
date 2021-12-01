#pragma once

#include "HuffmanTree.h"
#include <vector>
class Frost
{
private:
    //HuffmanTree *trees;   //用手写堆实现森林合并, 也可使用, 为配合小组输出格式改为stable_sort
    std::vector<HuffmanTree> trees;
    int num = 0;

public:
    void init(unsigned long long *weight);
    HuffmanTree pop();
    void push(HuffmanTree tree);
    void check_down(int i);
    void check_up(int i);
    HuffmanTree top(){
        return trees[num];
    }
};