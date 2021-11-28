#include <cstring>
#include "coding.h"

void encoding(Node *root, char (*coding_table)[MaxTreeDepth], char code[], int t)
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

//统计字符出现次数
int count_occchar(char *codingstring, int *appear_times)
{
    memset(appear_times, 0, sizeof(appear_times));
    int l = strlen(codingstring);
    for (int i = 0; i < l; i++)
        appear_times[(int)codingstring[i]]++;

    int tot = 0;
    for (int i = 0; i < MaxCharSize; i++)
        if (appear_times[i])
            tot++;
    return tot;
}

//通过信息还原哈夫曼树
HuffmanTree build_tree(int *msg, int mode)
{
    if (mode == 1 || mode == 2)
    {
        HuffmanTree HT;
        int leaves = 0;
        for (int i = 0; i < MaxCharSize; i++)
            if (msg[i])
                leaves++;
        return HT.BuildHT(msg, leaves);
    }

}