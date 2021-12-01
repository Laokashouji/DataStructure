#include <iostream>
#include <fstream>
#include <cstring>
#include "myios.h"

using namespace std;

//读入运行模式为编码或解码
int read_runmode()
{
    cout << "Please select run mode, '1' represents coding, '2' represents decoding, please enter:";
    int mode = 0;
    cin >> mode;
    if (mode != 1 && mode != 2)
    {
        cout << "Run mode error!";
        return 0;
    }
    return mode;
}
//读入输出模式为输出字符串或输出比特流
int read_printmode()
{
    cout << "\nPlease select output format, '1' represents strings, '2'represents bits, please enter:";
    int mode = 0;
    cin >> mode;
    if (mode != 1 && mode != 2)
    {
        cout << "Print mode error!";
        return 0;
    }
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

//和别小组统一格式后的读入辅助信息, 辅助信息具体格式为:
//开头四个字节MAGIC_NUMBER为MZPS, 代表文件格式; 接下来一字节为bool变量, 0表示被编码为文本, 1表示被编码为二进制文件
//接下来是256个八字节的unsigned long long变量, 保存每个字符的出现次数
//如果为二进制文件, 接下来还有八位字节的unsigned long long变量保存接下来有多少个有效的二进制比特位(在print_codes_group中读入)
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
    if (fmn != FILE_MAGIC_NUMBER)
    {
        cout << "File format error!";
        return false;
    }
    in.read((char *)&flag, sizeof(bool));
    mode = flag + 1;
    for (int i = 0; i < MaxCharSize; i++)
        in.read((char *)&msg[i], sizeof(unsigned long long));

    in.close();
    return true;
}

//输出辅助信息, 格式如上所述
void print_msg_group(unsigned long long *appear_times, char *outfile, int mode)
{
    ofstream out(outfile, ios::out | ios::trunc | ios::binary);
    out.write((char *)&FILE_MAGIC_NUMBER, sizeof(int)); //输出FILE_MAGIC_NUMBER
    bool flag = (mode == 1 ? 0 : 1);
    out.write((char *)&flag, sizeof(bool)); //输出bool表示是否为二进制
    for (int i = 0; i < MaxCharSize; i++)
        out.write((char *)&appear_times[i], sizeof(unsigned long long)); //输出每个字符出现的次数
    out.close();
}
//输出接下来有多少位有效的二进制比特位
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
//对应编码时的输出
void print_codes_group(char *infile, char (*map)[MaxTreeDepth], char *outfile, int mode)
{
    ifstream in(infile, ios::in | ios::binary);
    ofstream out(outfile, ios::out | ios::binary | ios::app);
    in.seekg(0, ios::end);
    unsigned long long l = in.tellg(); //确定输入文件大小, 以便一边读入一边输出
    in.seekg(0, ios::beg);
    unsigned char ch;
    if (mode == 1) //输出为字符串
    {
        for (int i = 0; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch)); //读入待编码的字符
            out << map[ch];                   //直接输出对应编码的字符串
        }
    }
    else if (mode == 2) //输出为比特流
    {
        //组装字节
        char cnt = 7, code = 0;
        for (int i = 0; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch)); //读入待编码的字符
            for (int j = 0; map[ch][j] != '\0'; j++, cnt--)
            {
                code = code | ((map[ch][j] - '0') << cnt); //组装该字节的第cnt位, 从左到右开始组装
                if (cnt == 0)
                {
                    out.write((char *)&code, sizeof(code)); //输出组装完成的字节
                    cnt = 8;
                    code = 0;
                }
            }
        }
        if (cnt < 7) //如果没有刚好组装成完整的字节, 输出最后一个不完整的字节
            out.write((char *)&code, sizeof(char));
    }
    in.close();
    out.close();
}
//对应解码情况的输出
void print_codes_group(HuffmanTree &HT, char *infile, char *outfile, int mode)
{
    Node *root = HT.root();
    ofstream out(outfile, ios::out | ios::binary | ios::trunc);
    ifstream in(infile, ios::in | ios::binary);
    in.seekg(0, ios::end);
    // l为文件结尾, st为文件除去开头辅助信息后待解码内容的起始位置
    unsigned long long l = in.tellg(), st = sizeof(int) + sizeof(bool) + MaxCharSize * sizeof(unsigned long long);
    in.seekg(st);
    char ch;
    if (mode == 1) //从文本文件解码
    {
        for (int i = st; i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));      //读入待解码字符串, 根据哈夫曼树解码
            if (ch == '0' && root->left() != NULL) //如果字符为0就往左走
            {
                root = root->left();
                if (root->is_leave()) //找到对应的字符, 直接输出字符
                {
                    out << root->data();
                    root = HT.root();
                }
            }
            else if (ch == '1' && root->right() != NULL) //如果字符为1就往右走
            {
                root = root->right();
                if (root->is_leave()) //找到对应的字符, 直接输出字符
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
        in.read((char *)&tot, sizeof(tot)); //读取接下来有效二进制比特位的个数
        for (int i = st + sizeof(tot); i < l; i++)
        {
            in.read((char *)&ch, sizeof(ch));     //读入待解码字节, 拆解为比特位根据哈夫曼树解码
            for (int j = 7; j >= 0; j--)          //从字节的最高一位开始拆起
                if ((i - st - 8) * 8 + (7 - j) >= tot) //读入了所有有效比特位后退出循环
                    break;
                else if (ch & (1 << j) && root->right() != NULL) //对比字节的第j位是否为1
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

//输出哈夫曼树, 调试用
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
