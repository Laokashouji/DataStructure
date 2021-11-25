#include <algorithm>
#include "myio.h"

#define MaxBytes 100000
#define OK 1
#define ERROR -1


using namespace std;

int main()
{
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
