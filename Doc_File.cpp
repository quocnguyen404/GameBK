#include <iostream>
#include <fstream>
using namespace std;
string tenfile;     // nhap tenfile vao`
void docfile(string tenfile)
{
    ifstream t(tenfile);
    string str;
    t.seekg(0, ios::end);
    str.reserve(t.tellg());
    t.seekg(0,ios::beg);
    str.assign((istreambuf_iterator<char>(t)),
        istreambuf_iterator<char>());
    cout << str;
}
