#include <iostream>
#include <fstream>
#include <algorithm>
#include "Frost.h"
using namespace std;
int main()
{
    ifstream in;
    ofstream out;
    char infile[100], outfile[100];
    cout << "请输入输入文件名:";
    cin >> infile;
    in.open(infile);
    cout << "\n请输入输出文件名:";
    cin >> outfile;
    out.open(outfile);

    

    in.close();
    out.close();
    return 0;
}