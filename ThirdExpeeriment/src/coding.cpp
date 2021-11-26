#include <cstring>
#include "coding.h"

void encoding(Node* root, char (*coding_table)[MaxTreeDepth], char code[], int t)
{
    if (root->is_leave())
    {
        code[t] = '\0';
        strcpy(coding_table[root->data()], code);
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

int count_occchar(char *codingstring, int *appear_times)
{
    memset(appear_times, 0, sizeof(appear_times));
    for (int i = 0; codingstring[i] != '\0'; i++)
        appear_times[(int)codingstring[i]]++;
    
    int tot = 0;
    for(int i = 0; i < MaxCharSize; i++)
    if(appear_times[i])  tot++;
    return tot;
}

HuffmanTree build_tree(char *codedstring)
{
    
}