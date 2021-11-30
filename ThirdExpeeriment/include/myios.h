#pragma once

#include <cstring>
#include "HuffmanTree.h"
#define INF 2147483647
#define MaxStringLength 100000
const int FILE_MAGIC_NUMBER = 'MZPS';

int read_runmode();                              //读入运行模式,即编码与解码
int read_printmode();                            //读入编码模式, 即字符串与比特流
int read_readmode();                             //读入解码模式, 即字符串与比特流
bool read_filename(char *infile, char *outfile); //读入输入输出文件名

//重载读入字符串函数以在编码和解码时都能使用
bool read_string(char *str, char *infile);                     //对应编码
bool read_string(char *str, int *msg, char *infile, int mode); //对应解码

//重载输出编码函数以在编码和解码时都能使用
void print_codes(char *condingstring, char (*map)[MaxTreeDepth], char *outfile, int mode); //对应编码
void print_codes(HuffmanTree &HT, char *codedstring, char *outfile, int mode);                       //对应解码
//输出哈夫曼树的信息
void print_msg(int *appear_times, char *outfile, int mode);
void print_msg_group(int *appear_times, char *outfile, int mode);

//打印变量便于调试
void show(char *str);
void show(int *a, int l);
void showTree(Node *t);
