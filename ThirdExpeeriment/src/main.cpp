#include "Frost.h"
#include "coding.h"
#include "myios.h"

#define MaxStringLength 100000
int main()
{
    int mode = read_mode();//读入运行模式, 1为编码, 2为解码
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

        //统计字符出现次数
        int appear_times[MaxCharSize];
        int leaves = count_occchar(codingstring, appear_times);
        // show(appear_times, leaves);

        //根据统计得到的数组建立哈夫曼树
        HuffmanTree HT;
        HT = HT.BuildHT(appear_times, leaves);
        // showTree(HT.root());

        //根据哈夫曼树对字符进行编码
        char map[MaxCharSize][MaxTreeDepth], mapCode[MaxTreeDepth];
        memset(map, 0, sizeof(map));
        memset(mapCode, 0, sizeof(mapCode));
        encoding(HT.root(), map, mapCode, 0);

        //输出编码结果
        print_codes(codingstring, map, outfile);
    }
    else if (mode == 2)
    {
        //读入待编码字符串
        char codingstring[MaxStringLength];
        if (!read_string(codingstring, infile))
            return 0;

        //统计字符出现次数
        int appear_times[MaxCharSize];
        int leaves = count_occchar(codingstring, appear_times);
        // show(appear_times, leaves);

        //根据统计得到的数组建立哈夫曼树
        HuffmanTree HT;
        HT = HT.BuildHT(appear_times, leaves);
        // showTree(HT.root());

        //根据哈夫曼树对字符进行编码
        char map[MaxCharSize][MaxTreeDepth], mapCode[MaxTreeDepth];
        memset(map, 0, sizeof(map));
        memset(mapCode, 0, sizeof(mapCode));
        encoding(HT.root(), map, mapCode, 0);

        //输出编码结果
        print_codes(codingstring, map, outfile);
    }
    return 0;
}