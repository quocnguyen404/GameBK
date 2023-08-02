#include <iostream>
using namespace std;
int check[101][101][101];

int check_spawn(int x, int y, int z)
{
    while (check[x][y][z] != 0)
    {
        srand((int)time(0));


        x, y, z = rand() % 100 + 1;
    }
    cout << "Object da duoc tao";
    return x, y, z;
}