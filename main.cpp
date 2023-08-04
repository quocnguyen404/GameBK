#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <string>

using namespace std;

enum ModulType
{
	TREE,
	HOUSE,
	CAR,
	GOTO,
};

struct Vector3
{
	int x, y, z;

	Vector3();

	Vector3(int x, int y, int z);
};

Vector3::Vector3()
{
	Vector3::x = 0;
	Vector3::y = 0;
	Vector3::z = 0;
}

Vector3::Vector3(int x, int y, int z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}

void Menu();
void CreateMap(int);//creat a map
void Modul(ModulType);//input the information about object
void Play();
void Move(int t);//move the character
int CountMap();
Vector3 CheckSpawn(Vector3);
Vector3 RandomVector3();

int map[11][11];



int main() 
{
	Menu();

	return 0;
}


void Menu()
{
	int option = 0;
	int countMapInFile = CountMap();

	while (option != 3) 
	{
		system("cls");
		cout << "MENU:" << endl;
		cout << "1. Create a new map" << endl;
		cout << "2. Play" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your option: ";
		cin >> option;

		switch (option) 
		{
			case 1:
				system("cls");
				CreateMap(countMapInFile + 1);
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
				return;

			default:
				cout << "Doesn't exist that option" << endl;
				system("pause");
				break;
		}
	}

	Menu();
}

void Modul(ModulType modulType) 
{
	Vector3 objPos;
	
	objPos.x = RandomInt().x;
	objPos.y = RandomInt().y;
	objPos.z = 1;
	
	objPos.x = CheckSpawn(objPos).x;
	objPos.y = CheckSpawn(objPos).y;
	map[objPos.x][objPos.y] = 1;

	ifstream input;
	fstream output;
	string objName;

	output.open("map.txt",ios::app);
	output << "OBJ" << modulType << endl;

	switch (modulType) 
	{
		case 1: objName = "tree";//name of the object
			output << objName << endl;
			output << "C:/Users/GIGABYTE/source/repos/gameBK/tree.obj" << endl;//the path of the file object
			output << objPos.x << "," << objPos.y << "," << 1 << endl;//location
			output << 1 << "," << 1 << "," << 1 << endl;//size
			output << 0 << "," << 0 << "," << 0 << endl;//swivel angle
			break;

		case 2: objName = "house";
			output << objName << endl;
			output << "C:/Users/GIGABYTE/source/repos/gameBK/house.obj" << endl;//the path of the file object
			output << objPos.x << "," << objPos.y << "," << 1 << endl;//location
			output << 1 << "," << 1 << "," << 1 << endl;//size
			output << 0 << "," << 0 << "," << 0 << endl;//swivel angle
			break;

		case 3: objName = "car";
			output << objName << endl;
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
	Modul(TREE);
	Modul(HOUSE);
	Modul(CAR);
}


void Move(int t) 
{
	cout << "Where you want to go?" << endl;
	cout << "Enter the map that you want to go to:";
	cin >> t;
	cout << "You are in the map " << t << endl;;
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


int CountMap() 
{
	ofstream output;
	ifstream input;
	input.open("map.txt");
	
	int mapCountVar = 0;

	if (!input.eof())
		return 0;

	while (!input.eof())
	{
		string line;

		getline(input, line);

		line.erase(line.length() - 1);

		if (line == "MAP")
			mapCountVar++;
		//cout << line << endl;
	}

	input.close();
	return mapCountVar;
}
