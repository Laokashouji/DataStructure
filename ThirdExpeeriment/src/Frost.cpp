#include <cstdlib>
#include <algorithm>
#include "HuffmanTree.h"
#include "Frost.h"

// stable_sort的参数, 用于排序; 根节点权重越小的树越小
bool cmp(HuffmanTree a, HuffmanTree b)
{
    return a.root()->w() < b.root()->w();
}

//初始化森林, 为每一个出现过的字符建一颗树
void Frost::init(unsigned long long *weight)
{
    for (int i = 0; i < MaxCharSize; i++)
        if (weight[i])
            trees.push_back(HuffmanTree::newTree(weight[i], (unsigned char)i));
    std::stable_sort(trees.begin() + num, trees.end(), cmp); //输出化后进行稳定排序, 以保证不同小组之间建立的哈夫曼树相同
}

//像森林中添加树, 将树加在森林的最前面
void Frost::push(HuffmanTree tree)
{
    trees.insert(trees.begin() + num, tree);
    std::stable_sort(trees.begin() + num, trees.end(), cmp);
}
//取森林中最小的树
HuffmanTree Frost::pop()
{
    //通过num来实现不实际删除节点取树, 以保持森林的稳定性
    HuffmanTree tree = trees[num];
    num++;
    return tree;
}