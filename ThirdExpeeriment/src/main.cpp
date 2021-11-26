#include "Frost.h"
#include "coding.h"
#include "myios.h"

#define MaxStringLength 100000
int main()
{
    int mode = read_runmode(); //读入运行模式, 1为编码, 2为解码
    //读入输入输出文件
    char infile[50], outfile[50];
    if (!read_filename(infile, outfile))
        return 0;

    if (mode == 1)
    {
        //读入待编码字符串
        char codingstring[MaxStringLength];
        if (!read_string(codingstring, infile))
            return 0;

        //统计各字符出现次数
        int appear_times[MaxCharSize];
        int leaves = count_occchar(codingstring, appear_times);
        // show(appear_times, leaves);

        //根据统计得到的出现次数数组建立哈夫曼树
        HuffmanTree HT;
        HT = HT.BuildHT(appear_times, leaves);
        // showTree(HT.root());

        //根据哈夫曼树对字符进行编码得到编码表
        char map[MaxCharSize][MaxTreeDepth], mapCode[MaxTreeDepth];
        memset(map, 0, sizeof(map));
        memset(mapCode, 0, sizeof(mapCode));
        encoding(HT.root(), map, mapCode, 0);

        //读入输出模式
        mode = read_printmode();
        print_leaves(appear_times, outfile, mode);              //输出各字符串出现次数数组便于还原哈夫曼树
        print_codes(codingstring, map, outfile, mode); //输出编码结果
    }
    else if (mode == 2)
    {
        //读入待还原字符串
        char codedstring[MaxStringLength], info[MaxCharSize * 2];
        if (!read_string(codedstring, info, infile))
            return 0;

        //根据提示信息还原哈夫曼树
        HuffmanTree HT = build_tree(codedstring);


        //根据还原得到的哈夫曼树逆推出原文件并输出
        print_codes(HT, codedstring, outfile);


    }

    return 0;
}
