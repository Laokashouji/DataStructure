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
    /*
    if (mode == 1) //输入文件为文本文件
    {
        //将文件内容全部读入, 并分为还原信息和解码内容
        in.read((char *)&ch, sizeof(char));
        while (in >> t && t < INF)
        {
            msg[ch] = t;
            in.read((char *)&ch, sizeof(char));
        }
        int begin = in.tellg();
        in.seekg(0, ios::end);
        int end = in.tellg();
        in.seekg(begin, ios::beg);
        in.read(str, end - begin);
    }
    */
    if (mode == 1 || mode == 2) //输入文件为二进制文件
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
        begin++;
        in.seekg(begin, ios::beg);
        in.read(str, end - begin);
        str[MaxStringLength - 1] = (end - begin) >> 4;
        str[MaxStringLength - 2] = (end - begin) % 256;
    }
    in.close();
    return true;
}
//和别小组统一格式后的读入
bool read_string_group(char *str, int *msg, char *infile, int mode)
{
}

//输出编码或解码结果
void print_codes(char *codingstring, char (*map)[MaxTreeDepth], char *outfile, int mode) //编码结果
{
    ofstream out(outfile, ios::out | ios::binary | ios::app);
    if (mode == 1) //输出为字符串
    {
        int l = strlen(codingstring);
        for (int i = 0; i < l; i++)
            out << map[codingstring[i]];
    }
    else if (mode == 2) //输出为比特流
    {
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
    Node *root = HT.root();
    ofstream out(outfile, ios::out | ios::binary | ios::trunc);
    if (mode == 1) //从文本文件解码
    {
        int l = strlen(codedstring);
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
        int l = (codedstring[MaxStringLength - 1] << 4) + codedstring[MaxStringLength - 2];
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
//与其他小组统一格式后的输出
void print_codes_group()
{
}

//输出还原信息
void print_msg(int *appear_times, char *outfile, int mode)
{
    ofstream out(outfile, ios::out | ios::binary | ios::trunc);
    if (mode == 1 || mode == 2)
    {
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
        out << '\n';
    }
    out.close();
}
void print_msg_group(int *appear_times, char *outfile, int mode)
{
    ostream out(outfile, ios::out | ios::trunc | ios::binary);
    out.write((char *)&FILE_MAGIC_NUMBER, sizeof(int));
    bool flag = (mode == 1 ? 0 : 1);
    out.write((char *)&flag, sizeof(bool));
    unsigned long long a;
    for (int i = 0; i < MaxCharSize; i++)
    {
        a = appear_times[i];
        out.write((char *)&a, sizeof(unsigned long long));
    }
    if (flag == 0) //文本
    {
        int l = strlen(codedstring);
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
