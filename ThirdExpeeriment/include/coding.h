#pragma once

#include "HuffmanTree.h"


void encoding(Node* root, char (*coding_table)[MaxTreeDepth], char code[], int t);
void decoding();
int count_occchar(char *codingstring, unsigned long long *appear_times);
bool count_occchar_group(unsigned long long *appear_times, char *infile);
void release(Node *root);