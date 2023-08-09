#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Read_Map(int x)
{
    fstream inputFile;
    inputFile.open("map.txt", ios::in);
    int mapCount = 0;
    string line;
    string content;

    while (getline(inputFile, line))
    {
        if (line.find("MAP") != string::npos)
        {
            mapCount++;
            if (mapCount >= x && mapCount < x + 1)
            {
                content += line + "\n";
            }
            if (mapCount > x + 1)
            {
                break;
            }
        }
        else if (mapCount >= x && mapCount < x + 1)
        {
            content += line + "\n";
        }
    }

    inputFile.close();

    cout << content;

}