//#pragma once
#include <cstddef>
class Node
{
private:
    unsigned int weight;
    char element;
    Node *parent, *lchild, *rchild;

public:
    Node(int weight = 0, char element = '\0', Node *parent = NULL, Node *lchild = NULL, Node *rchild = NULL)
        : weight(weight), element(element), parent(parent), lchild(lchild), rchild(rchild) {}

    static Node newNode(Node *node1, Node *node2);

    bool operator<(const Node &b)
    {
        return weight < b.weight;
    }
};

class HuffmanTree
{
private:
    Node *head;
    HuffmanTree(Node *head = NULL) : head(head) {}

public:
    HuffmanTree BuildHT(int *weght, int leaves);
    HuffmanTree newTree(int weight, char element);

    HuffmanTree combine(HuffmanTree left, HuffmanTree right);
    bool operator<(const HuffmanTree &b)
    {
        return *head < *(b.head);
    }
};

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