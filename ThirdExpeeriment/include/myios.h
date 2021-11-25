#pragma once

#include <cstring>
#include "HuffmanTree.h"

int read_mode();                                 //读入运行模式,即编码与解码
bool read_filename(char *infile, char *outfile); //读入输入输出文件名

//重载读入字符串函数以在编码和解码时都能使用
bool read_string(char *str, char *infile);                //对应编码
bool read_string(char *str, char *info, char *infile); //对应解码

//重载输出编码函数以在编码和解码时都能使用
void print_codes(char *condingstring, char (*map)[MaxTreeDepth], char *outfile); //对应变慢
void print_codes(HuffmanTree &HT, char *codedstring, char *outfile);             //对应解码

//打印变量便于调试
void show(char *str);
void show(int *a, int l);
void showTree(Node *t);
