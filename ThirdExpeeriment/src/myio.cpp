#include <iostream>
#include <cstring>
#include <fstream>
#include "myio.h"

using namespace std;

Status read_iofiles(char *infile, char *outfile)
{
    char *cnt = NULL;
    infile = outfile = "";
    cout << "请输入输入文件名:";
    do
    {
        cin >> infile;
        cnt = strchr(infile, '.');
        if (infile == "quit")
            return ERROR;
        if (!cnt)
            cout << "\n输入文件格式名错误, 请重新输入:";
    } while (!cnt);

    cnt = NULL;
    cout << "请输入输入文件名:";
    do
    {
        cin >> outfile;
        cnt = strchr(outfile, '.');
        if (outfile == "quit")
            return ERROR;
        if (!cnt)
            cout << "\n输出文件格式名错误, 请重新输入:";
    } while (!cnt);

    return OK;
}

Status readBytes(char *bytes, char *infile)
{
    ifstream in;
    in.open(infile);

    bytes = "";
    if (in >> bytes)
    {
        in.close();
        return OK;
    }
    in.close();
    return ERROR;
}

