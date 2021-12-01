#include "Frost.h"
#include "coding.h"
#include "myios.h"
#include <cstdio>

int main()
{

    // freopen("in_encode.txt", "r", stdin); //编码
    // freopen("in_decode.txt", "r", stdin);//解码

    int mode;//表示运行模式和输出模式
    if (!(mode = read_runmode())) //读入运行模式, 1为编码, 2为解码
        return 0;
    char infile[100], outfile[100];
    if (!read_filename(infile, outfile)) //读入输入输出文件
        return 0;

    unsigned long long appear_times[MaxCharSize]; //存储字符出现次数
    if (mode == 1)                                //代表编码
    {
        if (!count_occchar_group(appear_times, infile)) //边读入边计算, 避免大文件保存不下
            return 0;

        //根据统计得到的出现次数数组建立哈夫曼树
        HuffmanTree HT = HuffmanTree::BuildHT(appear_times);
        // showTree(HT.root());

        //根据哈夫曼树对字符进行编码得到编码表
        char map[MaxCharSize][MaxTreeDepth], mapCode[MaxTreeDepth]; // map表示每个字符对应的编码, mapCode用于保存求编码时的01串
        memset(map, 0, sizeof(map));
        memset(mapCode, 0, sizeof(mapCode));
        encoding(HT.root(), map, mapCode, 0); //编码

        //读入输出模式, '1'表示编码为文本文件, '2'表示编码为二进制文件
        mode = read_printmode();

        //和其他小组统一后的输出格式
        print_msg_group(appear_times, outfile, mode); // 输出信息
        if (mode == 2)
            print_bits(appear_times, map, outfile);    //如果编码为二进制文件, 额外输出有效二进制位的个数作为辅助信息
        print_codes_group(infile, map, outfile, mode); //边读入边输出, 避免大文件保存不下
        //释放哈夫曼树的空间
        release(HT.root());
    }
    else if (mode == 2) // 代表解码
    {
        //读取辅助信息
        if (!read_string_group(appear_times, infile, mode))
            return 0;
        //根据提示信息还原哈夫曼树
        HuffmanTree HT = HuffmanTree::BuildHT(appear_times);

        //根据还原得到的哈夫曼树逆推出原文件并输出
        print_codes_group(HT, infile, outfile, mode);
        //释放哈夫曼树的空间
        release(HT.root());
    }

    return 0;
}
