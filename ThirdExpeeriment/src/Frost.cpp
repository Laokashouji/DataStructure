#include <cstdlib>
#include <algorithm>
#include "HuffmanTree.h"
#include "Frost.h"

bool cmp(HuffmanTree a, HuffmanTree b)
{
    return a.root()->w() < b.root()->w();
}
void Frost::init(unsigned long long *weight)
{
    for (int i = 0; i < MaxCharSize; i++)
        if (weight[i])
            trees.push_back(HuffmanTree::newTree(weight[i], (unsigned char)i));
    std::stable_sort(trees.begin() + num, trees.end(), cmp);
}
void Frost::push(HuffmanTree tree)
{
    trees.insert(trees.begin() + num, tree);
    std::stable_sort(trees.begin() + num, trees.end(), cmp);
    /*
    for (auto it = trees.begin() + num; it < trees.end(); it++) {
        fprintf(stderr, "%d ", it->root()->w());
    }
    fputs("\n", stderr);
    */
}

HuffmanTree Frost::pop()
{
    HuffmanTree tree = trees[num];
    num ++;
    return tree;
}