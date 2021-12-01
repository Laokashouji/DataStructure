#include <cstring>
#include <iostream>
#include <fstream>
#include "coding.h"
using namespace std;

//根据哈夫曼树生成字符对应的编码表
void encoding(Node *root, char (*coding_table)[MaxTreeDepth], char code[], int t)
{
    if (root->is_leave()) //如果已经走到了叶子节点, 将当前code中保存的字符串作为该叶子节点保存字符的编码
    {
        code[t] = '\0';
        strcpy(coding_table[(unsigned char)root->data()], code);
        return;
    }
    if (root->left() != NULL) //往左走, 编码加一位0
    {
        code[t] = '0';
        encoding(root->left(), coding_table, code, t + 1);
    }
    if (root->right() != NULL) //往右走, 编码加一位1
    {
        code[t] = '1';
        encoding(root->right(), coding_table, code, t + 1);
    }
}
//统计待编码文件中所有字符的出现次数
bool count_occchar_group(unsigned long long *appear_times, char *infile)
{
    ifstream in(infile, ios::binary | ios::in); //以二进制输入格式打开
    if (!in)
    {
        cout << "Failed to open file!";
        return false;
    }
    memset(appear_times, 0, sizeof(appear_times));
    unsigned char ch;
    in.seekg(0, ios::end);
    unsigned long long l = in.tellg(); //找到文件的结尾, 确定读入范围
    in.seekg(0, ios::beg);
    for (int i = 0; i < l; i++) //边读边求, 避免保存待编码文件
    {
        in.read((char *)&ch, sizeof(char));
        appear_times[ch]++;
    }
    in.close();
    return true;
}
//释放哈夫曼树
void release(Node *root)
{
    if (root->left())//释放左子树
        release(root->left());
    if (root->right())//释放右子树
        release(root->right());
    free(root);//释放根节点
}