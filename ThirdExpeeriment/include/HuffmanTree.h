#pragma once
#include <cstddef>
#define MaxCharSize 256
#define MaxTreeDepth 100
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
    bool is_leave();
    char data() {return element;}
    Node* show_parent(){return parent;}
    Node* left(){return lchild;}
    Node* right(){return rchild;}
    int w(){return weight;}
    bool operator<(const Node &b){
        return weight < b.weight;
    }
};

class HuffmanTree
{
private:
    Node *head;

public:
    HuffmanTree(Node *head = NULL) : head(head) {}
    HuffmanTree BuildHT(int *weght, int leaves);
    HuffmanTree newTree(int weight, char element);
    HuffmanTree combine(HuffmanTree left, HuffmanTree right);
    Node* root() {return head;}
    bool operator < (const HuffmanTree &b){
        return *head < *(b.head);
    }
    void showTree();
};

