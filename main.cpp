#include <stdio.h>
#include<windows.h>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include<conio.h>
#include<string>
using namespace std;

void CreateMap(int a);//creat a map
void OBJ(int b);//input the information about object
void Play();
void Move(int t);//move the character
int CountMap();

struct Vector3
{
	int x, y, z;
	Vector3() 
	{
		x = 0;
		y = 0;
		z = 0;
	};

	Vector3(int x, int y, int z);
};

Vector3::Vector3(int x, int y, int z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}


Vector3 CheckSpawn(Vector3);

Vector3 RandomInt();

int map[11][11];

int main() {
	int choose;
	int cm = CountMap();
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
			
			CreateMap(cm+1);
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
	
	int m;//the map that character in
	
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
				Move( m);

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


void Move( int t) {
	cout << "where you want to go?" << endl;
	cout << "enter the map that you want to go to:";
	cin >> t;
	
	cout << "you are in the map " << t << endl;;
}



Vector3 RandomInt()
{
	srand((unsigned int)time(0));
	Vector3 ranVec;
	ranVec.x = rand() % 10 + 1;
	ranVec.y = rand() % 10 + 1;
	ranVec.z = 1;
	return ranVec;
}


Vector3 CheckSpawn(Vector3 checkVec)
{
	while (!(map[checkVec.x][checkVec.y] == 0))
	{
		srand((int)time(0));
		checkVec.x = rand() % 10 + 1;
		checkVec.y = rand() % 10 + 1;
	}

	return checkVec;
}
int CountMap() {
	ofstream output;
	ifstream input;
	input.open("map.txt");
	int a = 0;
	while (!input.eof())
	{
		char temp[255];
		input.getline(temp, 255);
		string line = temp;
		char b[3];
		for (int i = 0; i < 3; i++) {
			b[i] = line[i];
		}
		if (b[0] == 'M' && b[1] == 'A' && b[2] == 'P')
		{
			a++;
		}
		//cout << line << endl;
	}
	input.close();
	return a;
}

//void LogVector3(Vector3 logVec)
//{
//	cout << logVec.x << ',';
//	cout << logVec.y << ',';
//	cout << logVec.z;
//}'

