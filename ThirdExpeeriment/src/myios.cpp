#include <iostream>
#include <fstream>
#include <cstring>
#include "myios.h"

using namespace std;

//读入运行模式, 编码模式, 解码模式
int read_runmode()
{
    cout << "Please select run mode, '1' represents coding, '2' represents decoding, please enter:";
    int mode = 1;
    cin >> mode;
    return mode;
}
int read_printmode()
{
    cout << "\nPlease select output format, '1' represents strings, '2'represents bits, please enter:";
    int mode = 1;
    cin >> mode;
    return mode;
}
//读取输入文件和输出文件名
bool read_filename(char *infile, char *outfile)
{
    bool format_flag = 0;
    cout << "\nPlease enter input file:";
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
        cout << "File name error!";
        return false;
    }
    cout << "\nPlease enter output file:";
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
        cout << "File name error!";
        return false;
    }
    return true;
}

//和别小组统一格式后的读入
bool read_string_group(unsigned long long *msg, char *infile, int &mode)
{
    ifstream in(infile, ios::in | ios::binary);
    if (!in)
    {
        cout << "Failed to open file";
        return false;
    }
    int fmn;
    bool flag = 0;
    in.read((char *)&fmn, sizeof(int));
    in.read((char *)&flag, sizeof(bool));
    mode = flag + 1;
    for (int i = 0; i < MaxCharSize; i++)
        in.read((char *)&msg[i], sizeof(unsigned long long));

    in.close();
    return true;
}

//小组统一格式
void print_msg_group(unsigned long long *appear_times, char *outfile, int mode)
{
    ofstream out(outfile, ios::out | ios::trunc | ios::binary);
    out.write((char *)&FILE_MAGIC_NUMBER, sizeof(int));
    bool flag = (mode == 1 ? 0 : 1);
    out.write((char *)&flag, sizeof(bool));
    unsigned long long a;
    for (int i = 0; i < MaxCharSize; i++)
    {
        a = appear_times[i];
        out.write((char *)&a, sizeof(unsigned long long));
    }
    out.close();
}
void print_bits(unsigned long long *appear_times, char (*map)[MaxTreeDepth], char *outfile)
{
    unsigned long long tot = 0;
    for (int i = 0; i < MaxCharSize; i++)
        if (appear_times[i])
            tot += appear_times[i] * strlen(map[i]);
    ofstream out(outfile, ios::out | ios::binary | ios::app);
    out.write((char *)&tot, sizeof(tot));
    out.close();
}
void print_codes_group(char *infile, char (*map)[MaxTreeDepth], char *outfile, int mode)
{
    ifstream in(infile, ios::in | ios::binary);
    ofstream out(outfile, ios::out | ios::binary | ios::app);
    in.seekg(0, ios::end);
    unsigned long long l = in.tellg();
    in.seekg(0, ios::beg);
    unsigned char ch;
    if (mode == 1) //输出为字符串
    {
        for (int i = 0; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));
            out << map[ch];
        }
    }
    else if (mode == 2) //输出为比特流
    {
        //组装字节
        char cnt = 7, code = 0;
        for (int i = 0; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));
            for (int j = 0; map[ch][j] != '\0'; j++, cnt--)
            {
                code = code | ((map[ch][j] - '0') << cnt);
                if (cnt == 0)
                {
                    out.write((char *)&code, sizeof(code));
                    cnt = 8;
                    code = 0;
                }
            }
        }
        if (cnt < 7)
            out.write((char *)&code, sizeof(char));
    }
    in.close();
    out.close();
}
void print_codes_group(HuffmanTree &HT, char *infile, char *outfile, int mode)
{
    Node *root = HT.root();
    ofstream out(outfile, ios::out | ios::binary | ios::trunc);
    ifstream in(infile, ios::in | ios::binary);
    in.seekg(0, ios::end);
    unsigned long long l = in.tellg(), st = sizeof(int) + sizeof(bool) + MaxCharSize * sizeof(unsigned long long);
    in.seekg(st);
    char ch;
    if (mode == 1) //从文本文件解码
    {
        for (int i = st; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));
            if (ch == '0' && root->left() != NULL)
            {
                root = root->left();
                if (root->is_leave())
                {
                    out << root->data();
                    root = HT.root();
                }
            }
            else if (ch == '1' && root->right() != NULL)
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
        unsigned long long tot;
        in.read((char *)&tot, sizeof(tot));
        for (int i = st + sizeof(tot); i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));
            for (int j = 7; j >= 0; j--)
                if ((i - 8) * 8 + (7 - j) == tot)
                    break;
                else if (ch & (1 << j) && root->right() != NULL)
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
    in.close();
    out.close();
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
