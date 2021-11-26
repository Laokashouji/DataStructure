#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "myios.h"

using namespace std;

//读入运行模式
int read_runmode()
{
    cout << "请选择运行模式, '1'表示编码, '2'表示解码, 请输入:";
    int mode = 1;
    cin >> mode;
    return mode;
}
//读入输出模式
int read_printmode()
{
    cout << "请选择输出模式, '1'表示输出字符串, '2'表示输出为比特流, 请输入:";
    int mode = 1;
    cin >> mode;
    return mode;
}
//读取输入文件和输出文件名
bool read_filename(char *infile, char *outfile)
{
    bool format_flag = 0;
    cout << "\n请输入输入文件名:";
    cin >> infile;
    //判断文件名是否合法
    for (int i = 0; infile[i] != '\0'; i++)
        if (infile[i] == '.')
        {
            format_flag = 1;
            break;
        }
    if (!format_flag)
    {
        cout << "文件格式错误!";
        return false;
    }
    cout << "\n请输入输出文件名:";
    cin >> outfile;
    format_flag = 0;
    for (int i = 0; outfile[i] != '\0'; i++)
        if (outfile[i] == '.' && i != 0)
        {
            format_flag = 1;
            break;
        }
    if (!format_flag)
    {
        cout << "文件格式错误!";
        return false;
    }
    return true;
}
//输入待编码字符串
bool read_string(char *str, char *infile)
{
    ifstream in(infile, ios::in | ios::binary); //以二进制输入格式打开
    if (!in)
    {
        cout << "文件打开失败!";
        return false;
    }

    ostringstream tmp;
    tmp << in.rdbuf();
    string ss = tmp.str();
    strcpy(str, ss.c_str());

    in.close();
    return true;
}
bool read_string(char *str, char *info, char *infile)
{
    ifstream in(infile, ios::in | ios::binary); //以二进制输入格式打开
    if (!in)
    {
        cout << "文件打开失败!";
        return false;
    }

    ostringstream tmp;
    tmp << in.rdbuf();
    string ss = tmp.str();
    strcpy(str, ss.c_str());

    in.close();
    return true;
}
//输出编码结果
void print_codes(char *codingstring, char (*map)[MaxTreeDepth], char *outfile, int mode)
{
    ofstream out;
    if (mode == 1)
    {
        out.open(outfile, ios::out | ios::trunc);
        for (int i = 0; codingstring[i] != '\0'; i++)
            out << map[codingstring[i]];
    }
    else if (mode == 2)
    {
        out.open(outfile, ios::out | ios::trunc | ios::binary);
    }
    out.close();
}
//输出还原信息
void print_msg(int *appear_times, char *outfile, int mode)
{
    ofstream out;
    if (mode == 1)
    {
        out.open(outfile, ios::out | ios::trunc);
        for (int i = 0; i < MaxCharSize; i++)
        {
            if (appear_times[i])
                cout << appear_times[i] << (char)i;
        }

    }
    else if (mode == 2)
    {
        out.open(outfile, ios::out | ios::binary | ios::trunc);
        out.write((char *)appear_times, MaxCharSize * sizeof(int));
    }
    out.close();
}
//输出某个字符串或者数组
void show(char *str)
{
    cout << str << endl;
}
void show(int *a, int l)
{
    for (int i = 0; i < 256; i++)
        if (a[i])
            cout << (char)i << " : " << a[i] << endl;
}

//输出哈夫曼树
void showTree(Node *t)
{
    if (t->left())
    {
        cout << '(' << t->left()->w() << ") ---> ";
    }
    cout << t->w();
    if (t->data())
        cout << " " << t->data();
    if (t->right())
    {
        cout << " <--- (" << t->right()->w() << ")";
    }
    cout << endl;
    if (t->left())
        showTree(t->left());
    if (t->right())
        showTree(t->right());
}
