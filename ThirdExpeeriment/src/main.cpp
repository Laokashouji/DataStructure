#include <algorithm>

#include "myio.h"

#define MaxBytes 100000
#define OK 1
#define ERROR -1

using namespace std;

int main()
{
    char infile[100], outfile[100];
    if((read_iofiles(infile, outfile) == ERROR))
        return 1;

    char bytes[MaxBytes];
    readBytes(bytes, infile);
   



    
    return 0;
}
