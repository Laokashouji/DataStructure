#pragma once

#include "HuffmanTree.h"
#include <vector>
class Frost
{
private:
    std::vector<HuffmanTree> trees;//使用vector保存森林, 便于使用stable_sort建立哈夫曼树, 保证不同小组之间建立的哈夫曼树相同
    int num = 0;//指向vector中有效的第一棵树, 从trees[num]开始往后的树才在森林当中;  使用num可以使push和pop可以更方便的实现而不破坏森林的稳定性

public:
    void init(unsigned long long *weight);//初始化森林
    HuffmanTree pop();//取森林中最小的树
    void push(HuffmanTree tree);//向森林开头插入一棵树
    HuffmanTree top(){return trees[num];};//返回森林中最小的树
};
