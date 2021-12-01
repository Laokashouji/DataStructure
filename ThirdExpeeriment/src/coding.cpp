#include <cstring>
#include <iostream>
#include <fstream>
#include "coding.h"
using namespace std;

void encoding(Node *root, char (*coding_table)[MaxTreeDepth], char code[], int t)
{
    if (root->is_leave())
    {
        code[t] = '\0';
        strcpy(coding_table[(unsigned char)root->data()], code);
        return;
    }
    if (root->left() != NULL)
    {
        code[t] = '0';
        encoding(root->left(), coding_table, code, t + 1);
    }
    if (root->right() != NULL)
    {
        code[t] = '1';
        encoding(root->right(), coding_table, code, t + 1);
    }
    return;
}

bool count_occchar_group(unsigned long long *appear_times, char *infile)
{
    ifstream in(infile, ios::binary | ios::in); //以二进制输入格式打开
    if (!in)
    {
        cout << "Failed to open file!";
        return false;
    }
    memset(appear_times, 0, sizeof(appear_times));
    unsigned char ch;
    in.seekg(0, ios::end);
    unsigned long long l = in.tellg();
    in.seekg(0, ios::beg);
    for (int i = 0; i < l; i++)
    {
        in.read((char *)&ch, sizeof(char));
        appear_times[ch]++;
    }
    in.close();
    return true;
}


void release(Node *root)
{
    if (root->left())
        release(root->left());
    if (root->right())
        release(root->right());
    free(root);
}