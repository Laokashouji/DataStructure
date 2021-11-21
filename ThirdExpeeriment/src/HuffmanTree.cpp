#include <algorithm>
#include "HuffmanTree.h"
#define INF (2 << 31) - 1

HuffmanTree HuffmanTree::BuildHT(int *weight, int leaves) // weight为各个字符出现的次数, leaves为字符数
{
    Frost HT;
    HT.init(weight, leaves);

    //建树
    HuffmanTree first, second;
    for (int i = 1; i < leaves; ++i)
    {
        first = HT.pop();
        second = HT.pop();
        HT.push(HuffmanTree::combine(first, second));
    }
    return HT.top();
}

void Frost::init(int *weight, int leaves)
{
    trees = (HuffmanTree *)malloc((leaves + 1) * sizeof(HuffmanTree)); //分配内存空间
    num = 0;                                                           //初始化节点
    for (int i = 1; i <= leaves; i++)
        push(trees->newTree(*weight, (char)i));
}

Node Node::newNode(Node *node1, Node *node2)
{
    return Node(node1->weight + node2->weight, NULL, node1, node2);
}
HuffmanTree HuffmanTree::newTree(int weight, char element)
{
    HuffmanTree T;
    *(T.head) = Node(weight, element);
    return T;
}

HuffmanTree Frost::pop()
{
    HuffmanTree tree = trees[1];
    trees[1] = trees[num--];
    check_down(1);
    return tree;
}
void Frost::push(HuffmanTree tree)
{
    trees[++num] = tree;
    check_up(num);
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

HuffmanTree HuffmanTree::combine(HuffmanTree left, HuffmanTree right)
{
    HuffmanTree tree;
    *(tree.head) = Node::newNode(left.head, right.head);
   return tree;
}