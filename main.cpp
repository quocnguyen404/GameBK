#include <stdio.h>
#include<windows.h>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include<conio.h>

using namespace std;

void CreateMap(int a);//creat a map
void OBJ(int b);//input the information about object
void Play();
void Move(int x, int y, int z, int t);//move the character


struct Vector3
{
	int x, y, z;
	Vector3() {};
};

Vector3 CheckSpawn(Vector3);

Vector3 RandomInt();

int map[10][10];

int main() {
	int choose;
	while (true) {
		system("cls");
		cout << "MENU:" << endl;
		cout << "Choose what you want to do:" << endl;
		cout << "1. Create a new map" << endl;
		cout << "2. Play" << endl;
		cout << "3. Exit" << endl;
		cin >> choose;
		switch (choose) {
		case 1:
			system("cls");
			CreateMap(1);
			cout << "you created a new map!" << endl;
			Sleep(2000);
			
			break;
		case 2: 
			system("cls");
			Play();
			break;
		case 3:
			system("cls");
			cout << "goodbye!";
			return false;
		default:
			cout << "there are no that option! pls choose again!";
			break;
		}
	}

	
	return 0;
}
void OBJ(int b) {
	
	Vector3 objPos;
	objPos.x = RandomInt().x;
	objPos.y = RandomInt().y;
	objPos.z = 1;
	
	objPos.x = CheckSpawn(objPos).x;
	objPos.y = CheckSpawn(objPos).y;

	map[objPos.x][objPos.y] = 1;

	ifstream input;
	fstream output;
	string OJname;
	output.open("map.txt",ios::app);
	output << "OBJ" << b << endl;
	switch (b) {
	case 1: OJname = "tree";//name of the object
		output << OJname << endl;
		output << "C:/Users/GIGABYTE/source/repos/gameBK/tree.obj" << endl;//the path of the file object
		output << objPos.x << "," << objPos.y << "," << 1 << endl;//location
		output << 1 << "," << 1 << "," << 1 << endl;//size
		output << 0 << "," << 0 << "," << 0 << endl;//swivel angle
		break;
	case 2: OJname = "house";
		output << OJname << endl;
		output << "C:/Users/GIGABYTE/source/repos/gameBK/house.obj" << endl;//the path of the file object
		output << objPos.x << "," << objPos.y << "," << 1 << endl;//location
		output << 1 << "," << 1 << "," << 1 << endl;//size
		output << 0 << "," << 0 << "," << 0 << endl;//swivel angle
		break;
		
	}
	output.close();

}
void Play() {
	int x, y, z;//coordinates of the character
	int m;//the map that character in
	x = 1;
	y = 1;
	z = 0;
	m = 1;
	
	//show map
	bool p = true;

	cout << "press m to move" << endl;
	cout << "press e to exit to menu" << endl;
	while (p) {
		
		//move the character
		if (_kbhit()) {
			char c = _getch();
			if (c == 'm') {
				Move(x, y, z, m);

			}
			else if (c == 'e') {
				p = false;
			}
		}
	}
	
}

void CreateMap(int a) {
	
	ifstream input;
	fstream output;
	
	output.open("map.txt", ios::app);
	output << "MAP" << a << endl;
	output.close();
	OBJ(1);
	OBJ(2);
}


void Move(int x, int y, int z, int t) {
	cout << "where you want to go?" << endl;
	cout << "enter the map that you want to go to:";
	cin >> t;
	cout << "enter the coordinates x in that map:";
	cin >> x;
	cout << "enter the coordinates y in that map:";
	cin >> y;
	cout << "enter the coordinates z in that map:";
	cin >> z;
	cout << "you are in location " << x << "," << y << "," << z << " in the map " << t << endl;;
}



Vector3 RandomInt()
{
	srand(time(0));
	Vector3 ranVec;
	ranVec.x = rand() % 10 + 1;
	ranVec.y = rand() % 10 + 1;
	ranVec.z = 1;
	return ranVec;
}


Vector3 CheckSpawn(Vector3 checkVec)
{
	int x, y;

	x = checkVec.x;
	y = checkVec.y;

	while (map[x][y] != 0)
	{
		srand((int)time(0));
		x = rand() % 10 + 1;
		y = rand() % 10 + 1;
	}

	Vector3 ran;
	ran.x = x;
	ran.y = y;
	return ran;
}


//void LogVector3(Vector3 logVec)
//{
//	cout << logVec.x << ',';
//	cout << logVec.y << ',';
//	cout << logVec.z;
//}
