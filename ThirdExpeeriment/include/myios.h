#pragma once

#include <cstring>
#include "HuffmanTree.h"

int read_runmode();
int read_printmode();
bool read_filename(char *infile, char *outfile);
bool read_string(char *str, char *infile);
void print_codes(char *condingstring, char (*map)[MaxTreeDepth], char *outfile, int mode);
void show(char *str);
void show(int *a, int l);
void showTree(Node *t);

