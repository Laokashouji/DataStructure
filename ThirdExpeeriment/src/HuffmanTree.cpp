#include "Frost.h"
#include "HuffmanTree.h"
HuffmanTree HuffmanTree::BuildHT(unsigned long long *weight) // weight为各个字符出现的次数, leaves为字符数
{
    Frost HT;
    //初始化森林, 即为每个字符都建一棵树
    int leaves = 0;
    for (int i = 0; i < MaxCharSize; i++)
        if (weight[i])
            leaves++;
    HT.init(weight);
    //将森林转化为一颗哈夫曼树
    HuffmanTree first, second;
    for (int i = 1; i < leaves; ++i)
    {
        first = HT.pop();
        second = HT.pop();
        HT.push(combine(first, second));
    }
    return HT.top();
}

bool Node::is_leave()
{
    if (lchild == NULL && rchild == NULL)
        return true;
    return false;
}
Node Node::newNode(Node *node1, Node *node2)
{
    return Node(node1->weight + node2->weight, '\0', NULL, node1, node2);
}
HuffmanTree HuffmanTree::newTree(int weight, char element)
{
    HuffmanTree T;
    T.head = (Node *)malloc(sizeof(Node));
    *(T.head) = Node(weight, element);
    return T;
}

HuffmanTree HuffmanTree::combine(HuffmanTree left, HuffmanTree right)
{
    HuffmanTree tree;
    tree.head = (Node *)malloc(sizeof(Node));
    *(tree.head) = Node::newNode(left.head, right.head);
    return tree;
}
