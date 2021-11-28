#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "myios.h"

using namespace std;

//读入运行模式, 编码模式, 解码模式
int read_runmode()
{
    cout << "请选择运行模式, '1'表示编码, '2'表示解码, 请输入:";
    int mode = 1;
    cin >> mode;
    return mode;
}
int read_printmode()
{
    cout << "\n请选择编码模式, '1'表示编码为字符串, '2'表示编码为比特流, 请输入:";
    int mode = 1;
    cin >> mode;
    return mode;
}
int read_readmode()
{
    cout << "\n请选择解码模式, '1'表示待解码文件为文本文件, '2'表示待解码文件为二进制文件, 请输入:";
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

//输入待编码或解码字符串
bool read_string(char *str, char *infile) //输入待编码字符串
{
    ifstream in(infile, ios::in | ios::binary); //以二进制输入格式打开
    if (!in)
    {
        cout << "文件打开失败!";
        return false;
    }
    //以二进制方式读入整个文件
    int begin = in.tellg();
    in.seekg(0, ios::end);
    int end = in.tellg();
    in.seekg(0, ios::beg);

    in.read(str, end - begin);

    in.close();
    return true;
}
bool read_string(char *str, int *msg, char *infile, int mode) //输入哈夫曼树信息和待解码字符串
{

    ifstream in(infile, ios::in | ios::binary); //以二进制输入格式打开
    if (!in)
    {
        cout << "文件打开失败!";
        return false;
    }
    char ch;
    int t;
    if (mode == 1) //输入文件为文本文件
    {
        //将文件内容全部读入, 并分为还原信息和解码内容
        stringstream tmp;
        tmp << in.rdbuf();
        string ss = tmp.str();
        while (tmp >> ch >> t && t != INF)
            msg[ch] = t;
        int pos = ss.find("\n");
        strcpy(str, ss.c_str() + pos + 1);
    }
    else if (mode == 2) //输入文件为二进制文件
    {
        int tot;
        in.read((char *)&tot, sizeof(tot));
        for (int i = 0; i < tot; i++)
        {
            in.read((char *)&ch, sizeof(ch));
            in.read((char *)&t, sizeof(int));
            msg[ch] = t;
        }
        int begin = in.tellg();
        in.seekg(0, ios::end);
        int end = in.tellg();
        in.seekg(begin, ios::beg);
        in.read(str, end - begin);
        str[MaxStringLength - 1] = end - begin;
    }
    in.close();
    return true;
}

//输出编码或解码结果
void print_codes(char *codingstring, char (*map)[MaxTreeDepth], char *outfile, int mode) //编码结果
{
    ofstream out;
    if (mode == 1) //输出为字符串
    {
        out.open(outfile, ios::out | ios::app);
        int l = strlen(codingstring);
        for (int i = 0; i < l; i++)
            out << map[codingstring[i]];
    }
    else if (mode == 2) //输出为比特流
    {
        out.open(outfile, ios::out | ios::binary | ios::app);
        char byte = 0;
        int l = strlen(codingstring);

        //组装字节
        char cnt = 1, code = 0;
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; map[codingstring[i]][j] != '\0'; j++, cnt++)
            {
                code = (code << 1) + map[codingstring[i]][j] - '0';
                if (cnt == 8)
                {
                    out.write((char *)&code, sizeof(code));
                    cnt = 0;
                    code = 0;
                }
            }
        }
        if (--cnt)
            out.write((char *)&code, sizeof(char));
        else
            cnt = 8;
        out.write((char *)&cnt, sizeof(char));
    }
    out.close();
}
void print_codes(HuffmanTree &HT, char *codedstring, char *outfile, int mode) //解码结果
{
    ofstream out;
    Node *root = HT.root();
    if (mode == 1) //从文本文件解码
    {
        int l = strlen(codedstring);
        out.open(outfile, ios::out | ios::trunc);
        for (int i = 0; i < l; i++)
        {
            if (codedstring[i] == '0' && root->left() != NULL)
            {
                root = root->left();
                if (root->is_leave())
                {
                    out << root->data();
                    root = HT.root();
                }
            }
            else if (codedstring[i] == '1' && root->right() != NULL)
            {
                root = root->right();
                if (root->is_leave())
                {
                    out << root->data();
                    root = HT.root();
                }
            }
        }
    }
    else if (mode == 2) //从二进制文件解码
    {
        int l = codedstring[MaxStringLength - 1];
        out.open(outfile, ios::out | ios::trunc | ios::binary);
        char cnt = codedstring[l - 1];
        char ch = 0;
        for (int i = 0; i < l - 1; i++)
        {
            ch = codedstring[i];
            for (int j = (i == l - 2 ? cnt - 1 : 7); j >= 0; j--)
                if (ch & (1 << j) && root->right() != NULL)
                {
                    root = root->right();
                    if (root->is_leave())
                    {
                        out << root->data();
                        root = HT.root();
                    }
                }
                else
                {
                    root = root->left();
                    if (root->is_leave())
                    {
                        out << root->data();
                        root = HT.root();
                    }
                }
        }
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
                out << (char)i << appear_times[i];
        }
        out << '\n';
    }
    else if (mode == 2)
    {
        out.open(outfile, ios::out | ios::binary | ios::trunc);
        int tot = 0;
        for (int i = 0; i < MaxCharSize; i++)
            if (appear_times[i])
                tot++;
        out.write((char *)&tot, sizeof(int));
        for (int i = 0; i < MaxCharSize; i++)
        {
            if (appear_times[i])
            {
                out.write((char *)&i, sizeof(char));
                out.write((char *)&appear_times[i], sizeof(int));
            }
        }
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
