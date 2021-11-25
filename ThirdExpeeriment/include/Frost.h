#pragma once

#include "HuffmanTree.h"

class Frost
{
private:
    HuffmanTree *trees;
    int num = 0;

public:
    void init(int *weight, int leaves);
    HuffmanTree pop();
    void push(HuffmanTree tree);
    void check_down(int i);
    void check_up(int i);
    HuffmanTree top(){
        return trees[1];
    }
    bool operator<(const Frost &b)
    {
        return trees[1] < b.trees[1];
    }
};