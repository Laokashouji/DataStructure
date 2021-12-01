#pragma once

#include "HuffmanTree.h"

void encoding(Node* root, char (*coding_table)[MaxTreeDepth], char code[], int t);//求编码表
bool count_occchar_group(unsigned long long *appear_times, char *infile);//求待编码文件中各字符出现的次数
void release(Node *root);//释放哈夫曼树