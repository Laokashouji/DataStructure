#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream in("in.dat", ios::in | ios::binary);
    char p[100];
    int l = in.tellg();
    in.seekg(0, ios::end);
    int m = in.tellg();
    in.seekg(0, ios::beg);
    in.read(p, m-l);
    ofstream out("test.dat", ios::out | ios::binary);
    out.write(p, m-l);
    cout << p;
    return 0;
}