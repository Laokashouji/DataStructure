#pragma once

#include "HuffmanTree.h"


void encoding(Node* root, char (*coding_table)[MaxTreeDepth], char code[], int t);
void decoding();
int count_occchar(char *codingstring, int *appear_times);