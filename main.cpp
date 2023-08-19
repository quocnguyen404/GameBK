#include "Header/common.h"

int main() 
{
	srand((unsigned int)time(0));

	/*-----------[REMOVE ALL .OBJ IN MODUL FOLDER]-----------*/


	/*-----------[INITIATE DEFAULT MAP]-----------*/
	Map maps[MAX_MAP_NUMBER] = {};

	Vector2 mapPos1(1, 1);
	Vector2 mapPos2(1, 2);
	Vector2 mapPos3(1, 3);
	/*Vector2 mapPos4(1, 4);
	Vector2 mapPos5(2, 4);
	Vector2 mapPos6(3, 4);*/
  /*Vector2 mapPos7(2, 1);
	Vector2 mapPos8(2, 2);
	Vector2 mapPos9(2, 3);
	Vector2 mapPos10(3, 1);
	Vector2 mapPos11(3, 2);*/

	maps[1] = CreateMap(1, mapPos1, maps);
	maps[2] = CreateMap(2, mapPos2, maps);
	maps[3] = CreateMap(3, mapPos3, maps);

	/*maps[4] = CreateMap(4, mapPos4, maps);
	maps[5] = CreateMap(5, mapPos5, maps);
	maps[6] = CreateMap(6, mapPos6, maps);*/

	//maps[7] = CreateMap(7, mapPos7, maps);
	//maps[8] = CreateMap(8, mapPos8, maps);
	//maps[9] = CreateMap(9, mapPos9, maps);
	//maps[10] = CreateMap(10, mapPos10, maps);
	//maps[11] = CreateMap(11, mapPos11, maps);

	LoadAllMapToFile(maps);


	/*-----------[MENU]-----------*/

	int option = 0;
	while (option != 6)
	{
		system("cls");
		std::cout << "MENU:" << endl;
		std::cout << "1. Create a new map" << endl;
		std::cout << "2. Play" << endl;
		std::cout << "3. Find path" << endl;
		std::cout << "4. Edit map" << endl;
		std::cout << "5. Checking" << endl;
		std::cout << "6. Exit" << endl;
		std::cout << "Enter your option: ";
		std::cin >> option;

		switch (option)
		{
			//create new map
			case 1:
			{
				system("cls");
				if (CountMap() >= MAX_MAP_NUMBER)
				{
					std::cout << "Full map!!";
					break;
				}
				Vector2 position;
				bool isExistMap = true;

				while (isExistMap)
				{
					PrintMapOverview();
					std::cout << "Enter map position x,y: ";
					std::cin >> position.x >> position.y;

					if (MAPOVERVIEW[position.x][position.y] == 0)
						isExistMap = false;
					else
						std::cout << "Exist map at position " << position.x << " " << position.y << endl;
				}

				maps[CountMap()+1] = CreateMap(CountMap() + 1, position, maps);
				cout << "You created a new map!" << endl;
				LoadAllMapToFile(maps);
				Sleep(1000);
				break;
			}
			
			//Play mode: move play
			case 2:
			{
				system("cls");
				int modulType = 0;
				int preMapIndex = 0;
				int mapIndex = 0;
				bool isPlaying = true;

				cout << "Press m to move" << endl;
				cout << "Press e to exit to menu" << endl;

				while (isPlaying)
				{
					if (_kbhit()) 
					{
						system("cls");
						char c = _getch();
						if (c == 'm') 
						{
							//Set first map to map 1
							if (mapIndex != 0)
							{
								cout << "Enter the map that you want to go to: ";
								cin >> mapIndex;
							}
							else
								mapIndex = 1;

							bool enterMapCanGo = false;

							//checking map can go
							for (int i = 0; i < 4; i++)
							{
								if (preMapIndex == 0)
									break;

								if (preMapIndex == mapIndex)
									enterMapCanGo = true;

								if (preMapIndex != 0 && maps[preMapIndex].mapAround[i] == mapIndex)
									enterMapCanGo = true;
							}

							//first time move to any map
							if (preMapIndex == 0)
								enterMapCanGo = true;
							
							if (enterMapCanGo)
							{
								ReadMap(maps[mapIndex]);

								cout << "You are in the map " << mapIndex << endl;
								preMapIndex = mapIndex;
							}
							else
							{
								cout << "You can't go to " << mapIndex << endl;
								mapIndex = preMapIndex;
							}

							cout << "Map you can go to: ";
							for (int i = 0; i < 4; i++)
							{
								int map = maps[mapIndex].mapAround[i];
								if (map != 0)
									cout << map << " ";
							}
							cout << endl;

							PrintMapOverview();
						}
						else if (c == 'e') 
							isPlaying = false;
					}
				}
				break;
			}

			case 3:
			{
				int startMapIndex = 0;
				int endMapIndex = 0;
				bool foundPath = false;

				PrintMapOverview();
				cout << "Enter map index you want to start: "; cin >> startMapIndex;
				cout << "Enter map index you want to come: "; cin >> endMapIndex;

				//adjancy list
				vector<vector<int>> graph; //dynamic 2d array

				//initiate graph[0] vector which empty
				graph.push_back({});

				for (int i = 1; i <= CountMap(); i++)
				{
					//initiate graph[i] vector
					graph.push_back({});
					for (int j = 0; j < MAX_MAP_AROUND_NUMBER; j++)
					{
						int mapAround = maps[i].mapAround[j];
						if (mapAround != 0)
							graph[i].push_back(mapAround);
					}
				}

				FindPath(startMapIndex, endMapIndex, graph, maps);
				system("pause");
				break;
			}

			case 4:
			{
				int editMapIndex = 0;
				cout << "Enter map index you want to edit: ";
				cin >> editMapIndex;

				EditMap(maps[editMapIndex]);
				LoadAllMapToFile(maps);
				break;
			}

			case 5:
			{
				int mapNumber = CountMap();

				vector<vector<string>> modulInMap;
				string line = "";
				bool getModulName = false;

				//create empty modulInMap[0]
				modulInMap.push_back({});

				for (int i = 1; i <= mapNumber; i++)
				{
					modulInMap.push_back({});
					ifstream mapFile;
					mapFile.open(maps[i].path);

					while (getline(mapFile, line))
					{
						if (getModulName)
						{
							modulInMap[i].push_back(line);
							getModulName = false;
						}

						if (line.find("OBJ") != string::npos)
							getModulName = true;
						else
							getModulName = false;
					}

					mapFile.close();
				}

				vector<string> conflictModul;
				string modulName;

				for (int i = 1; i < modulInMap.size(); i++)
				{
					for (int j = 0; j < modulInMap[i].size(); j++)
					{
						modulName = modulPath + modulInMap[i][j] + ".obj";
						ifstream modulFile;
						modulFile.open(modulName, ios::out);
						if (modulFile.is_open())
							cout << modulName << " exist in map " << i << endl;
						else
							cout << modulName << " doesn't exist in map " << i << endl;

						modulFile.close();
					}
				}

				system("pause");
				break;
			}

			case 6:
			{
				system("cls");
				cout << "Goodbye!";
				return 0;
			}

			default:
			{
				cout << "Doesn't exist that option" << endl;
				break;
			}
		}
	}
	return 0;
}
