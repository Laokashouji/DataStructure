#include "Frost.h"
#include "HuffmanTree.h"

//建哈夫曼树
HuffmanTree HuffmanTree::BuildHT(unsigned long long *weight) // weight为各个字符出现的次数, leaves为字符数
{
    Frost HT;
    int leaves = 0;
    for (int i = 0; i < MaxCharSize; i++) //求总共出现了几个不同的字符
        if (weight[i])
            leaves++;
    HT.init(weight); //初始化森林, 即为每个不同的字符建一棵树

    //将森林合并成为哈夫曼树
    HuffmanTree first, second;
    for (int i = 1; i < leaves; ++i) //总共有leaves个不同的字符, 所以要做leaves - 1次合并所有树
    {
        first = HT.pop();                //取森林中最小的数
        second = HT.pop();               //取森林中第二小的树
        HT.push(combine(first, second)); //将这两棵树合并后的新树加入森林中
    }
    return HT.top(); //合并后森林中的最后一颗树即为哈夫曼树
}

//判断该节点是否为叶子节点
bool Node::is_leave()
{
    if (lchild == NULL && rchild == NULL)
        return true;
    return false;
}

//将node1和node2分别作为左右孩子, 二者的权重之和作为权重, 新建节点
Node Node::newNode(Node *node1, Node *node2)
{
    return Node(node1->weight + node2->weight, '\0', NULL, node1, node2);
}

//初始化森林时使用, 新建一颗根节点权值为weight, 保存字符为element的树, 无其他节点
HuffmanTree HuffmanTree::newTree(int weight, char element)
{
    HuffmanTree T;
    T.head = (Node *)malloc(sizeof(Node));
    *(T.head) = Node(weight, element);
    return T;
}

//将两棵树连接成为新树
HuffmanTree HuffmanTree::combine(HuffmanTree left, HuffmanTree right)
{
    HuffmanTree tree;
    tree.head = (Node *)malloc(sizeof(Node));
    *(tree.head) = Node::newNode(left.head, right.head);
    return tree;
}
