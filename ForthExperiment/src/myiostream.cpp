#include "myiostream.h"
#include <cstdio>
//输出最短路
void print_path(int path[], const Graph &G, int s)
{
    if(path[s] != -1)
    {
        print_path(path, G, path[s]);
        printf("->");
    }
    printf("%s", G.data[s]);
}

//选择输入源
bool read_mode(char *filename)
{
    printf("please select read mode, '1' represents stdin, '2' represents read from file:");
    int mode;
    scanf("%d", &mode);
    if(mode == 2)
    {
        printf("please input read file name:");
        scanf("%s", filename);
        return true;
    }
    return false;
}