#include "Frost.h"
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

bool Node::is_leave()
{
    if(lchild == NULL && rchild == NULL)
        return true;
    return false;
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

HuffmanTree HuffmanTree::combine(HuffmanTree left, HuffmanTree right)
{
    HuffmanTree tree;
    *(tree.head) = Node::newNode(left.head, right.head);
   return tree;
}