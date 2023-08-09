#pragma once
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <map>
using namespace std;

////////////////
///  DEFINE ///
//////////////
const int MAP_WIDTH = 11;
const int MAP_LENGTH = 11;
int MAP[MAP_WIDTH][MAP_LENGTH] = {};
const string mapPath = "map.txt";
const string modulPath = "C:\\projects\\Cpp\\GameBKProject\\gameBK\\modul\\";
const string objSubfix = ".obj";

enum ModulType
{
	NONE,
	TREE,
	HOUSE,
	CAR,
	GOTO,
};

map<ModulType, string> ModulTypeConvert
{
	{NONE, "NONE"},
	{ TREE, "TREE" },
	{ HOUSE, "HOUSE" },
	{ CAR, "CAR" },
	{ GOTO, "GOTO" },
};



//////////////////////////
/// VECTOR3 STRUCTURE ///
////////////////////////
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



////////////////////
/// MODUL CLASS ///
//////////////////
class Modul
{
public:
	ModulType modulType;
	int byte;
	string name;
	string path;
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

public:
	Modul() {}

	Modul(ModulType modulType, Vector3 position, Vector3 scale, Vector3 rotation);

public:
	void GenerateFile();

	void AddToMap(string mapPath);
};

//modul constructor
Modul::Modul(ModulType modulType, Vector3 position, Vector3 scale, Vector3 rotation)
{
	Modul::modulType = modulType;
	Modul::name = ModulTypeConvert[modulType] + to_string(modulType);
	Modul::position = position;
	Modul::scale = scale;
	Modul::rotation = rotation;
	Modul::path = modulPath + Modul::name + objSubfix;
	Modul::byte = sizeof(byte) + sizeof(this) + sizeof(modulType) + sizeof(name) + sizeof(position) + sizeof(rotation) + sizeof(path);
	Modul::GenerateFile();
}

// generate object file
void Modul::GenerateFile()
{
	ofstream modulFile;
	modulFile.open(path, ios::out);

	if (!modulFile.is_open())
	{
		cout << "Open generate obj unsuccess" << endl;
		return;
	}

	modulFile << name << endl;
	modulFile << byte << endl;

	for (int i = 0; i < name.length(); i++)
		modulFile << int(name[i]);

	modulFile << position.x << position.y << position.z;
	modulFile << scale.x << scale.y << scale.z;
	modulFile << rotation.x << rotation.y << rotation.z;
	modulFile << endl;

	modulFile.close();
}

//print modul to map
void Modul::AddToMap(string mapPath)
{
	ofstream modulFile;
	modulFile.open(mapPath, ios::app);

	if (!modulFile.is_open())
	{
		cout << "Open object file unsuccess" << endl;
		return;
	}

	modulFile << "OBJ" << modulType << endl;
	modulFile << name << endl;
	modulFile << position.x << ',' << position.y << ',' << position.z << endl;
	modulFile << scale.x << ',' << scale.y << ',' << scale.z << endl;
	modulFile << rotation.x << ',' << rotation.y << ',' << rotation.z << endl;

	modulFile.close();
}


/////////////////////////
/// FUNCTION DECLARE ///
///////////////////////

void CreateMap(int); //creat a map
void CreateModul(ModulType); //input the information about object
void Play(); //play game
void Move(int t); //move character
int CountMap(); // count map exist in file map.txt
Vector3 CheckSpawn(Vector3); //chech position in map that exist modul yet
int RandomInRange(int, int); //random int number in range
Vector3 RandomVector3(int, int);  //random vector3 on ground


//////////////////////
/// FUNCTION BODY ///
////////////////////

void CreateMap(int mapIndex)
{
	//srand((unsigned int)time(0));
	int numberOfModul = RandomInRange(4, 7);
	int numberOfTree = rand() % (numberOfModul + 1);
	int numberOfHouse = rand() % (numberOfModul - numberOfTree + 1);
	int numberOfCar = numberOfModul - numberOfTree - numberOfHouse;
	int numberOfGoTo;

	fstream output;

	output.open(mapPath, ios::app);
	output << "MAP" << mapIndex << endl;
	output.close();

	for (int i = 0; i < numberOfTree; i++)
		CreateModul(TREE);

	for (int i = 0; i < numberOfHouse; i++)
		CreateModul(HOUSE);

	for (int i = 0; i < numberOfCar; i++)
		CreateModul(CAR);

}

void CreateModul(ModulType modulType)
{
	Vector3 modPos = RandomVector3(0, MAP_WIDTH);
	Vector3 modScale(1, 1, 1);
	Vector3 modRotate = RandomVector3(0, 360);

	Modul modul(modulType, modPos, modScale, modRotate);
	modul.AddToMap(mapPath);
}

void Play() {

	int mapIndex;//the map that character in

	mapIndex = 1;

	//show map
	bool p = true;

	cout << "press m to move" << endl;
	cout << "press e to exit to menu" << endl;
	while (p) {

		//move the character
		if (_kbhit()) {
			char c = _getch();
			if (c == 'm') {
				Move(m);
			}
			else if (c == 'e') {
				p = false;
			}
		}
	}
}

void Move(int t)
{
	cout << "Where you want to go?" << endl;
	cout << "Enter the map that you want to go to:";
	cin >> t;
	cout << "You are in the map " << t << endl;;
}

int CountMap()
{
	string line;
	ofstream output;
	ifstream input;
	input.open("map.txt");

	int mapCountVar = 0;

	if (input.peek() == ifstream::traits_type::eof())
		return 0;

	while (!input.eof())
	{
		getline(input, line);

		if (line.find("MAP", 0) != string::npos)
			mapCountVar++;
	}

	input.close();
	return mapCountVar;
}

Vector3 CheckSpawn(Vector3 checkVec)
{
	while (!(MAP[checkVec.x][checkVec.y] == 0))
	{
		srand((int)time(0));
		checkVec.x = rand() % 10 + 1;
		checkVec.y = rand() % 10 + 1;
	}

	return checkVec;
}

int RandomInRange(int min, int max)
{
	return rand() % max + min;
}

Vector3 RandomVector3(int min, int max)
{
	Vector3 ranVec;
	ranVec.x = rand() % max + min;
	ranVec.y = rand() % max + min;
	ranVec.z = 1;
	return ranVec;
}
