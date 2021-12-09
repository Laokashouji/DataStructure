#pragma once
#include <cstddef>
#include <cstdlib>

#define MaxCharSize 256
#define MaxTreeDepth 256
class Node
{
private:
    unsigned int weight; //保存权重, 即字符出现的次数
    char element;        //保存代表的字符
    Node *parent, *lchild, *rchild;

public:
    Node(int weight = 0, char element = '\0', Node *parent = NULL, Node *lchild = NULL, Node *rchild = NULL)
        : weight(weight), element(element), parent(parent), lchild(lchild), rchild(rchild) {}

    static Node newNode(Node *node1, Node *node2); //合并节点
    bool is_leave();                               //判断是否是叶子节点
    char data() { return element; }                //返回节点代表的字符
    Node *left() { return lchild; }                //返回节点的左儿子
    Node *right() { return rchild; }               //返回字节的右儿子
    int w() { return weight; }                     //返回节点的权重
};

class HuffmanTree
{
private:
    Node *head;//哈夫曼树的根节点

public:
    HuffmanTree(Node *head = NULL) : head(head) {}
    static HuffmanTree BuildHT(unsigned long long *weght);//建立哈夫曼树
    static HuffmanTree newTree(int weight, char element);//搭建一颗只有一个节点的新树
    static HuffmanTree combine(HuffmanTree left, HuffmanTree right);//合并两棵树
    Node *root() { return head; }//返回根节点
};
