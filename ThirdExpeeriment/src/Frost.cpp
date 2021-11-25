#include <cstdlib>
#include "HuffmanTree.h"
#include "Frost.h"

void Frost::init(int *weight, int leaves)
{
    trees = (HuffmanTree *)malloc((leaves + 1) * sizeof(HuffmanTree)); //分配内存空间
    for (int i = 0; i < MaxCharSize; i++)
        if (weight[i])
            push(trees->newTree(weight[i], (char)i));
}
void Frost::push(HuffmanTree tree)
{
    trees[++num] = tree;
    check_up(num);
}

HuffmanTree Frost::pop()
{
    HuffmanTree tree = trees[1];
    trees[1] = trees[num--];
    check_down(1);
    return tree;
}

void Frost::check_down(int i)
{
    if (i * 2 > num)
        return;
    int min;
    if (i * 2 + 1 > num)
        min = i * 2;
    else
        min = trees[i * 2] < trees[i * 2 + 1] ? i * 2 : i * 2 + 1;
    if (trees[min] < trees[i])
    {
        trees[0] = trees[min];
        trees[min] = trees[i];
        trees[i] = trees[0];
        check_down(min);
    }
    return;
}
void Frost::check_up(int i)
{
    if (i / 2 < 1)
        return;
    if (trees[i] < trees[i / 2])
    {
        trees[0] = trees[i / 2];
        trees[i / 2] = trees[i];
        trees[i] = trees[0];
        check_up(i / 2);
    }
}
