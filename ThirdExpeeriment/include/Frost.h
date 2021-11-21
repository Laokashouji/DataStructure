#pragma once

#include "HuffmanTree.h"

class Frost
{
private:
    HuffmanTree *trees;
    int num;

public:
    void init(int *weight, int leaves);
    HuffmanTree pop();
    void push(HuffmanTree tree);
    void check_down(int i);
    void check_up(int i);
    HuffmanTree combine(HuffmanTree left, HuffmanTree right);
    HuffmanTree top(){
        return trees[1];
    }
    bool operator<(const Frost &b)
    {
        return trees[1] < b.trees[1];
    }
};