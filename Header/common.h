#pragma once
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

/*-----------[CONSTANTS]-----------*/
const int MAP_WIDTH_OVERVIEW = 5;
const int MAP_LENGTH_OVERVIEW = 5;
const int MAX_MAP_NUMBER = MAP_WIDTH_OVERVIEW * MAP_LENGTH_OVERVIEW;
const int MAP_WIDTH = 11;
const int MAP_LENGTH = 11;
const int MAX_MAP_AROUND_NUMBER = 4;
const string mapPath = "map.txt";
const string modulPath = "C:\\projects\\Cpp\\GameBKProject\\gameBK\\modul\\";
const string mapFilePath = "C:\\projects\\Cpp\\GameBKProject\\gameBK\\map\\";
const string objSubfix = ".obj";


/*-----------[GOLBAL VARIABLE]-----------*/
int MAPOVERVIEW[MAP_WIDTH_OVERVIEW][MAP_LENGTH_OVERVIEW] = 
{
	{ {0}, {0}, {0}, {0}, {0} },
	{ {0}, {0}, {0}, {0}, {0} },
	{ {0}, {0}, {0}, {0}, {0} },
	{ {0}, {0}, {0}, {0}, {0} },
	{ {0}, {0}, {0}, {0}, {0} }
};

/*----------------[ENUM]----------------*/
enum ModulType
{
	NONE,
	TREE,
	HOUSE,
	CAR,
	GOTO,
};

enum MapAround
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
};


/*----------------[MAP IN C++]----------------*/
map<ModulType, string> ModulTypeConvert
{
	{NONE, "NONE"},
	{ TREE, "TREE" },
	{ HOUSE, "HOUSE" },
	{ CAR, "CAR" },
	{ GOTO, "GOTO" },
};


/*----------------[STRUCTURE]----------------*/
//[VECTOR2]
struct Vector2 
{
	int x, y;

	Vector2();
	Vector2(int x, int y);
};

Vector2::Vector2()
{
	Vector2::x = 0;
	Vector2::y = 0;
}

Vector2::Vector2(int x, int y)
{
	Vector2::x = x;
	Vector2::y = y;
}

//[VECTOR3]
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


/*----------------[CLASS]----------------*/
//[MAP]
class Map
{
public:
	int index;
	int MAP[MAP_WIDTH][MAP_LENGTH] = {};
	int numberOfModul;
	int numberOfGoto;
	Vector2 position;
	int mapAround[4] = {};
	string name;
	string path;

	map <ModulType, int> moduls
	{
		{TREE, 0},
		{ HOUSE, 0 },
		{ CAR, 0 },
		{ GOTO, 0 },
	};

public:
	Map();

	Map(int index, Vector2 mapPosition);

public: 
	void GenerateFile();
};

Map::Map()
{
	Map::index = 0;
	Map::numberOfModul = 0;
	Map::numberOfGoto = 0;
	Map::position.x = 0;
	Map::position.y = 0;
	Map::name = "MAP" + to_string(Map::index);
	Map::path = mapFilePath + Map::name + ".txt";
}

Map::Map(int index, Vector2 mapPosition)
{
	Map::index = index;
	Map::position = mapPosition;
	Map::numberOfModul = rand() % 7 + 4;
	Map::numberOfGoto = 0;
	Map::moduls[TREE] = rand() % (numberOfModul + 1);
	Map::moduls[HOUSE] = rand() % (numberOfModul - Map::moduls[TREE] + 1);
	Map::moduls[CAR] = numberOfModul - Map::moduls[CAR] - Map::moduls[HOUSE];
	Map::name = "MAP" + to_string(Map::index);
	Map::path = mapFilePath + Map::name + ".txt";
	GenerateFile();
}

void Map::GenerateFile()
{
	ofstream mapFile;
	mapFile.open(path, ios::out);

	if (!mapFile.is_open())
		cout << "Open generate obj unsuccess" << endl;

	mapFile << "MAP" + to_string(Map::index) << endl;
	mapFile.close();
}


//[MODUL]
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
};

Modul::Modul(ModulType modulType, Vector3 position, Vector3 scale, Vector3 rotation)
{
	Modul::modulType = modulType;
	Modul::name = ModulTypeConvert[modulType] + to_string(modulType);
	Modul::position = position;
	Modul::scale = scale;
	Modul::rotation = rotation;
	Modul::path = modulPath + Modul::name + objSubfix;
	Modul::byte = sizeof(this);
	Modul::GenerateFile();
}

void Modul::GenerateFile()
{
	ofstream modulFile;
	modulFile.open(path, ios::out);

	if (!modulFile.is_open())
		cout << "Open generate obj unsuccess" << endl;

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


/*----------------[PROTOTYPE]----------------*/
Map CreateMap(int, Vector2, Map(&)[MAX_MAP_NUMBER]); //creat a map
void CreateModul(ModulType, Map&, int);
Modul InitiateModul(ModulType, Map&); //input the information about object
int CountMap(); // count map exist in file map.txt
void ReadMap(Map&); // read map
Vector3 CheckSpawn(Vector3, Map); //chech position in map that exist modul yet
int RandomInRange(int, int); //random int number in range
Vector3 RandomVector3(int, int);  //random vector3 on ground
Vector2 RandomVector2(int, int); // random vector2
void PrintMapOverview(); //print 2d matrix overview of maps
void LoadMapAround(Map&); //load map around of a map
int Up(Map&); //the map above;
int Down(Map&); //the map below
int Right(Map&); //the map right
int Left(Map&); //the map left
void LoadAllMapToFile(Map(&)[MAX_MAP_NUMBER]); //load all map file to map.txt file



/*----------------[FUNCTION]----------------*/
Map CreateMap(int index, Vector2 position, Map (&maps)[MAX_MAP_NUMBER])
{
	Map map(index, position);

	MAPOVERVIEW[map.position.x][map.position.y] = index;
	

	CreateModul(TREE, map, map.moduls[TREE]);
	CreateModul(HOUSE, map, map.moduls[HOUSE]);
	CreateModul(CAR, map, map.moduls[CAR]);

	////Load map around of this map (is creating)
	LoadMapAround(map);

	//Load map near by this map (is creating)
	int mapAroundIndex = 0;
	for (int i = 0; i < MAX_MAP_AROUND_NUMBER; i++)
	{
		mapAroundIndex = map.mapAround[i];
		if (mapAroundIndex != 0)
			LoadMapAround(maps[mapAroundIndex]);
	}
	return map;
}

void CreateModul(ModulType modulType, Map& map, int numberOfModulToCreate)
{
	ofstream mapFile;
	mapFile.open(map.path, ios::app);

	for (int i = 0; i < numberOfModulToCreate; i++)
	{
		Modul modul = InitiateModul(modulType, map);
		mapFile << "OBJ" << modulType << endl;
		mapFile << modul.name << endl;
		mapFile << modul.position.x << "," << modul.position.y << "," << modul.position.z << endl;
		mapFile << modul.scale.x << "," << modul.scale.y << "," << modul.scale.z << endl;
		mapFile << modul.rotation.x << "," << modul.rotation.y << "," << modul.rotation.z << endl;
		mapFile << modul.path << endl;
	}

	mapFile.close();
}

Modul InitiateModul(ModulType modulType, Map &map)
{
	Vector3 modPos = RandomVector3(0, MAP_WIDTH); //initiate random position for modul
	modPos = CheckSpawn(modPos, map); // checking on map position is exist any modul
	Vector3 modScale(1, 1, 1);
	Vector3 modRotate = RandomVector3(0, 360);
	map.MAP[modPos.x][modPos.y] = modulType;
	Modul modul(modulType, modPos, modScale, modRotate);
	//modul.AddToMap(mapPath);
	return modul;
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

void ReadMap(Map &map)
{

	ifstream inputFile;
	inputFile.open(map.path);
	
	int mapCount = 0;
	string line;
	string content;

	while (getline(inputFile, line))
		cout << line << endl;

	inputFile.close();

	cout << content;
}

Vector3 CheckSpawn(Vector3 checkVec, Map map)
{
	while (!(map.MAP[checkVec.x][checkVec.y] == 0))
	{
		srand((int)time(0));
		checkVec = RandomVector3(0, MAP_LENGTH);
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

Vector2 RandomVector2(int min, int max)
{
	Vector2 ranVec;
	ranVec.x = rand() % max + min;
	ranVec.y = rand() % max + min;
	return ranVec;
}

void PrintMapOverview()
{
	for (int i = 0; i < MAP_WIDTH_OVERVIEW; i++)
	{
		for (int j = 0; j < MAP_LENGTH_OVERVIEW; j++)
			cout << MAPOVERVIEW[i][j] << " ";

		cout << endl;
	}
}

void LoadMapAround(Map &map)
{
	int currentMapAround = 0;
	map.mapAround[UP] = Up(map);
	map.mapAround[DOWN] = Down(map);
	map.mapAround[RIGHT] = Right(map);
	map.mapAround[LEFT] = Left(map);

	for (int i = 0; i < MAX_MAP_AROUND_NUMBER; i++)
	{
		if (map.mapAround[i] != 0)
			currentMapAround++;
	}

	int gotoLoadYet = abs(map.numberOfGoto - currentMapAround);

	for (int i = 0; i < gotoLoadYet; i++)
		map.numberOfGoto++;

	if (gotoLoadYet == 0)
		return;

	CreateModul(GOTO, map, gotoLoadYet);
}

int Up(Map &map)
{
	if (map.position.x <= 0)
		return 0;
	
	return MAPOVERVIEW[map.position.x - 1][map.position.y]; //up
}

int Down(Map& map)
{
	if (map.position.x >= MAP_WIDTH_OVERVIEW-1)
		return 0;

	return MAPOVERVIEW[map.position.x + 1][map.position.y]; //down
}

int Right(Map& map)
{
	if (map.position.y >= MAP_WIDTH_OVERVIEW - 1)
		return 0;

	return MAPOVERVIEW[map.position.x][map.position.y + 1]; //right
}

int Left(Map& map)
{
	if (map.position.y <= 0)
		return 0;

	return MAPOVERVIEW[map.position.x][map.position.y - 1]; //left
}

int FindPath(int mapIndex, vector<int> &path, vector<int> visited, Map (&maps)[MAX_MAP_NUMBER], int endMapIndex)
{
	Map map = maps[mapIndex];
	int mapAroundIndex = 0;
	for (int i = 0; i < MAX_MAP_AROUND_NUMBER; i++)
	{
		mapAroundIndex = map.mapAround[i];

		if (mapAroundIndex == endMapIndex)
			return 1;

		if (mapAroundIndex != 0 && !(find(visited.begin(), visited.end(), mapAroundIndex) != visited.end()))
		{
			path.push_back(mapAroundIndex);
			break;
		}
		else if (i >= MAX_MAP_AROUND_NUMBER)
		{
			visited.push_back(mapAroundIndex);
			FindPath(*path.end(), path, visited, maps, endMapIndex);
		}
	}

	FindPath(mapAroundIndex, path, visited, maps, endMapIndex);

	return 0;
}

void LoadAllMapToFile(Map(&maps)[MAX_MAP_NUMBER])
{
	ofstream allMap(mapPath, ios::trunc);

	for (int i = 0; i < MAX_MAP_NUMBER; i++)
	{
		if (maps[i].index != 0)
		{
			ifstream currentMap(maps[i].path);

			for (string content; getline(currentMap, content);)
				allMap << content << endl;

			currentMap.close();
		}
	}

	allMap.close();

}