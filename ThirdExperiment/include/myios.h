#pragma once

#include <cstring>
#include "HuffmanTree.h"
const int FILE_MAGIC_NUMBER = 'MZPS';

int read_runmode();                              //读入运行模式,即编码或解码
int read_printmode();                            //读入编码模式, 即字符串或比特流
bool read_filename(char *infile, char *outfile); //读入输入输出文件名

//读入编码后文件的辅助信息
bool read_string_group(unsigned long long *msg, char *infile, int &mode);

void print_bits(unsigned long long *appear_times, char (*map)[MaxTreeDepth], char *outfile); //输出接下来编码文件中有多少个有效的二进制比特位
void print_msg_group(unsigned long long *appear_times, char *outfile, int mode);             //输出编码的辅助信息
void print_codes_group(char *infile, char (*map)[MaxTreeDepth], char *outfile, int mode);    //一边读入待编码内容一边输出编码的结果
void print_codes_group(HuffmanTree &HT, char *infile, char *outfile, int mode);              //一边读入带解码内容一边输出解码的结果

//打印变量便于调试
void showTree(Node *t);
