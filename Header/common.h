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
#include <list>

using namespace std;

/*-----------[CONSTANTS]-----------*/
const int MAP_WIDTH_OVERVIEW = 5;
const int MAP_LENGTH_OVERVIEW = 5;
const int MAX_MAP_NUMBER = MAP_WIDTH_OVERVIEW * MAP_LENGTH_OVERVIEW;
const int MAP_WIDTH = 11;
const int MAP_LENGTH = 11;
const int MAX_MAP_AROUND_NUMBER = 4;
const int NUMBER_OF_MODULTYPE = 5;
const int MAX_MODUL_NUM_IN_MAP = 7;
const int MIN_MODUL_NUM_IN_MAP = 4;
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


/*----------------[CLASS IDENTIFY]----------------*/
//[MAP]
class Map
{
public:
	int index;
	int MAP[MAP_WIDTH][MAP_LENGTH] = {};
	int numberOfModul;
	int numberOfGoto;
	Vector2 position;
	int mapAround[NUMBER_OF_MODULTYPE] = {};
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

//[MODUL]
class Modul
{
public:
	int id;
	ModulType modulType;
	int byte;
	string name;
	string path;
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
	Modul* ptr = this;
public:
	Modul();

	Modul(ModulType modulType, Vector3 position, Vector3 scale, Vector3 rotation);

public:
	void GenerateFile();
};


/*----------------[PROTOTYPE]----------------*/
Map CreateMap(int, Vector2, Map(&)[MAX_MAP_NUMBER]); //creat a map 1

void CreateModul(ModulType, Map&, int);		// 2
Modul InitiateModul(ModulType, Map&); //input the information about object 3

int CountMap(); // count map exist in file map.txt 4
void ReadMap(Map&); // read map 5
Vector3 CheckSpawn(Vector3, Map); //chech position in map that exist modul yet 6

int RandomInRange(int, int); //random int number in range
Vector3 RandomVector3(int, int);  //random vector3 on ground
Vector2 RandomVector2(int, int); // random vector2

void PrintMapOverview(); //print 2d matrix overview of maps
void LoadMapAround(Map&); //load map around of a map 7

int Up(Map&); //the map above;
int Down(Map&); //the map below
int Right(Map&); //the map right
int Left(Map&); //the map left

void FindPath(int, int, vector<vector<int>>&, Map(&)[MAX_MAP_NUMBER]); //find path from start to end
void FindPathRecursion(int, int, vector<bool>&, vector<int>&, vector<vector<int>>&, Map(&)[MAX_MAP_NUMBER]); //
void PrintPath(vector<int>&, Map(&)[MAX_MAP_NUMBER]);

void LoadAllMapToFile(Map(&)[MAX_MAP_NUMBER]); //load all map file to map.txt file 8
void EditMap(Map&);

/*----------------[CLASS IMPLEMENT]----------------*/
//[MAP]
Map::Map()
{
	Map::index = 0;
	Map::numberOfModul = 0;
	Map::numberOfGoto = 0;
	Map::position.x = 0;
	Map::position.y = 0;
	//Map::name = "MAP" + to_string(Map::index);
	//Map::path = mapFilePath + Map::name + ".txt";
}

Map::Map(int index, Vector2 mapPosition)
{
	Map::index = index;
	Map::position = mapPosition;
	Map::numberOfModul = RandomInRange(MIN_MODUL_NUM_IN_MAP, MAX_MODUL_NUM_IN_MAP);
	Map::numberOfGoto = 0;
	Map::moduls[TREE] = RandomInRange(0, Map::numberOfModul);
	Map::moduls[HOUSE] = RandomInRange(0, (numberOfModul - Map::moduls[TREE]));
	Map::moduls[CAR] = numberOfModul - Map::moduls[TREE] - Map::moduls[HOUSE];
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
Modul::Modul()
{
}

Modul::Modul(ModulType modulType, Vector3 position, Vector3 scale, Vector3 rotation)
{
	static int uniqueId = 0;
	Modul::id = uniqueId++;
	Modul::modulType = modulType;
	Modul::name = ModulTypeConvert[modulType] + to_string(Modul::id);
	Modul::position = position;
	Modul::scale = scale;
	Modul::rotation = rotation;
	Modul::path = modulPath + Modul::name + objSubfix;
	Modul::byte = sizeof(id) + sizeof(Modul::modulType) + sizeof(Modul::name) + sizeof(Modul::scale) + sizeof(Modul::rotation) + sizeof(Modul::path);
	Modul::GenerateFile();
}

void Modul::GenerateFile()
{
	ofstream modulFile;
	modulFile.open(path, ios::trunc);

	if (!modulFile.is_open())
		cout << "Open obj file unsuccess!" << endl;

	modulFile << Modul::ptr << endl;
	modulFile << Modul::name << " " << &Modul::name << endl;
	modulFile << Modul::byte << endl;
	modulFile << &Modul::id << &Modul::position << &Modul::scale << &Modul::rotation << &Modul::path;

	modulFile.close();
}


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
} //Khanh

void CreateModul(ModulType modulType, Map& map, int numberOfModulToCreate)
{
	ofstream mapFile;
	mapFile.open(map.path, ios::app);

	for (int i = 0; i < numberOfModulToCreate; i++)
	{
		Modul modul = InitiateModul(modulType, map);
		mapFile << "OBJ" << modul.id << endl;
		mapFile << modul.name << endl;
		mapFile << modul.position.x << "," << modul.position.y << "," << modul.position.z << endl;
		mapFile << modul.scale.x << "," << modul.scale.y << "," << modul.scale.z << endl;
		mapFile << modul.rotation.x << "," << modul.rotation.y << "," << modul.rotation.z << endl;
		mapFile << modul.path << endl;
	}

	mapFile.close();
} //Nhat

Modul InitiateModul(ModulType modulType, Map &map)
{
	Vector3 modPos = RandomVector3(0, MAP_WIDTH); //initiate random position for modul
	modPos = CheckSpawn(modPos, map); // checking on map position is exist any modul
	Vector3 modScale(1, 1, 1); //initiate scale
	Vector3 modRotate = RandomVector3(0, 360); //initiate rotation
	map.MAP[modPos.x][modPos.y] = modulType; //update modul position to map
	Modul modul(modulType, modPos, modScale, modRotate);

	return modul;
} //Nhat

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
} //Phong

void ReadMap(Map &map)
{
	ifstream inputFile;
	inputFile.open(map.path);
	
	int mapCount = 0;
	string line;

	while (getline(inputFile, line))
		cout << line << endl;

	inputFile.close();
} //Phong

Vector3 CheckSpawn(Vector3 checkVec, Map map)
{
	while (!(map.MAP[checkVec.x][checkVec.y] == 0))
	{
		srand((int)time(0));
		checkVec = RandomVector3(0, MAP_LENGTH);
	}
	return checkVec;
} //Phong

int RandomInRange(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}

Vector3 RandomVector3(int min, int max)
{
	Vector3 ranVec;
	ranVec.x = RandomInRange(min, max);
	ranVec.y = RandomInRange(min, max);
	ranVec.z = 1;
	return ranVec;
}

Vector2 RandomVector2(int min, int max)
{
	Vector2 ranVec;
	ranVec.x = RandomInRange(min, max);
	ranVec.y = RandomInRange(min, max);
	return ranVec;
}

void PrintMapOverview()
{
	for (int i = 0; i < MAP_WIDTH_OVERVIEW; i++)
	{
		for (int j = 0; j < MAP_LENGTH_OVERVIEW; j++)
		{
			if (MAPOVERVIEW[i][j] < 10)
				cout << 0 << MAPOVERVIEW[i][j] << " ";
			else
				cout << MAPOVERVIEW[i][j] << " ";
		}

		cout << endl;
	}
}

void LoadMapAround(Map& map)
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
} //Ba

int Up(Map& map)
{
	if (map.position.x <= 0)
		return 0;

	return MAPOVERVIEW[map.position.x - 1][map.position.y]; //up
}

int Down(Map& map)
{
	if (map.position.x >= MAP_WIDTH_OVERVIEW - 1)
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

void FindPath(int start, int end, vector<vector<int>> &graph, Map(&maps)[MAX_MAP_NUMBER])
{
	int size = graph.size();
	vector<bool> visited(size+1, false);
	vector<int> path;
	FindPathRecursion(start, end, visited, path, graph, maps);
}

void FindPathRecursion(int start, int end, vector<bool>& visited, vector<int> &path, vector<vector<int>> &graph, Map(&maps)[MAX_MAP_NUMBER]) {
	visited[start] = true;
	path.push_back(start);

	if (start == end) 
		PrintPath(path, maps);
	else 
	{
		for (int i = 0; i < graph[start].size(); i++) 
		{
			int next = graph[start][i];
			if (!visited[next]) 
				FindPathRecursion(next, end, visited, path, graph, maps);
		}
	}

	// Backtrack: remove the current node from the path and mark it as unvisited
	path.pop_back();
	visited[start] = false;
}

void PrintPath(vector<int>& path, Map(&maps)[MAX_MAP_NUMBER])
{
	int numberOfModulOnPath[NUMBER_OF_MODULTYPE] = {};

	numberOfModulOnPath[NONE] = 0;
	for (int i = 0; i < path.size(); i++) 
	{
		numberOfModulOnPath[TREE] += maps[path[i]].moduls[TREE];
		numberOfModulOnPath[HOUSE] += maps[path[i]].moduls[HOUSE];
		numberOfModulOnPath[CAR] += maps[path[i]].moduls[CAR];
		numberOfModulOnPath[GOTO] += maps[path[i]].moduls[GOTO];

		cout << path[i];
		if (i != path.size() - 1) 
			cout << "->";
	}

	int biggestNum = 0;
	ModulType mostAppearModul = NONE; //NONE
	for (int i = 0; i < NUMBER_OF_MODULTYPE; i++)
	{
		if (numberOfModulOnPath[i] > biggestNum)
		{
			biggestNum = numberOfModulOnPath[i];
			mostAppearModul = (ModulType)i;
		}
	}

	cout << "\t " << "Most appear modul is " << ModulTypeConvert[mostAppearModul] << ": " << biggestNum << endl;
}

void LoadAllMapToFile(Map(&maps)[MAX_MAP_NUMBER])
{
	ofstream allMap;
	allMap.open(mapPath, ios::trunc);

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

} //Ba

void EditMap(Map &map)
{
	int choice = 0;

	do
	{
		cout << "1. Add modul." << endl;
		cout << "2. Change modul position." << endl;
		cout << "3. Exit." << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
			case 1:
			{
				int input = 0;
				int quantity = 0;

				cout << "1. Tree" << endl;
				cout << "2. House" << endl;
				cout << "3. Car" << endl;
				cout << "Choose the modul you want to add: ";
				cin >> input;

				ModulType modulType = (ModulType)input;

				cout << "How many " << ModulTypeConvert[modulType] << " you want to add: ";
				cin >> quantity;

				CreateModul(modulType, map, quantity);
				map.moduls[modulType] += quantity;
				system("cls");
				cout << "Add new modul success!" << endl;
				break;
			}

			case 2:
			{
				system("cls");
				
				ReadMap(map);
				
				string editModulName = "";
				Vector3 customsPos;
				
				cout << "Enter modul name you want to change position: "; cin.ignore();
				getline(cin, editModulName);

				cout << "Enter modul position(x, y, z): ";
				cin >> customsPos.x >> customsPos.y >> customsPos.z;
				
				string updateLine = to_string(customsPos.x) + "," + to_string(customsPos.y) + "," + to_string(customsPos.z);
				string line = "";
				vector<string> content;
				bool ableToEdit = false;
				bool isExistModul = false;

				ifstream mapIn;
				mapIn.open(map.path, ios::in);

				if (!mapIn.is_open())
					cout << "Open file fail." << endl;

				while (getline(mapIn, line))
				{
					if (ableToEdit)
					{
						content.push_back(updateLine);
						ableToEdit = false;
						isExistModul = true;
					}
					else
						content.push_back(line);

					if (line == editModulName)
						ableToEdit = true;
					else
						ableToEdit = false;
				}

				if (!isExistModul)
					cout << "Doesn't exist " << editModulName << endl;

				mapIn.close();

				ofstream mapOut;
				mapOut.open(map.path, ios::out);

				if (!mapOut.is_open())
					cout << "Open file fail." << endl;

				for (int i = 0; i < content.size(); i++)
					mapOut << content[i] << endl;

				mapOut.close();

				break;
			}

			default:
				system("cls");
				cout << "Doesn't exist function.";
				choice = 3;
				break;
		}
	} while (choice != 3);
}