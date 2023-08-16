#include "Header/common.h"

using namespace std;

int main() 
{
	srand((unsigned int)time(0));

	/*-----------[INITIATE DEFAULT MAP]-----------*/
	Map maps[MAX_MAP_NUMBER] = {};

	Vector2 mapPos1(1, 1);
	Vector2 mapPos2(1, 2);
	Vector2 mapPos3(1, 3);
	Vector2 mapPos4(1, 4);
	Vector2 mapPos5(2, 4);
	Vector2 mapPos6(3, 4);

	maps[1] = CreateMap(1, mapPos1, maps);
	maps[2] = CreateMap(2, mapPos2, maps);
	maps[3] = CreateMap(3, mapPos3, maps);
	maps[4] = CreateMap(4, mapPos4, maps);
	maps[5] = CreateMap(5, mapPos5, maps);
	maps[6] = CreateMap(6, mapPos6, maps);
	LoadAllMapToFile(maps);


	/*-----------[MENU]-----------*/

	int option = 0;
	while (option != 3)
	{
		system("cls");
		cout << "MENU:" << endl;
		cout << "1. Create a new map" << endl;
		cout << "2. Play" << endl;
		cout << "3. Find path" << endl;
		cout << "4. Edit map" << endl;
		cout << "5. Checking" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your option: ";
		cin >> option;

		switch (option)
		{
			//create new map
			case 1:
			{
				if (CountMap() >= MAX_MAP_NUMBER)
				{
					cout << "Full map!!";
					break;
				}
				system("cls");
				Vector2 position;
				bool isExistMap = true;

				while (isExistMap)
				{
					cout << "Enter map position x,y: ";
					cin >> position.x >> position.y;

					if (MAPOVERVIEW[position.x][position.y] == 0)
						isExistMap = false;
					else
					{
						cout << "Exist map at position " << position.x << " " << position.y << endl;
						PrintMapOverview();
					}
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
						else if ( c == 'a')
						{

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

				vector<int> path;
				vector<int> visited;

				PrintMapOverview();
				cout << "Enter map index you want to start: "; cin >> startMapIndex;
				cout << "Enter map index you want to come: "; cin >> endMapIndex;

				FindPath(startMapIndex, path, visited, maps, endMapIndex);

				for (int i = 0; i < path.size(); i++)
					cout << path[i] << " ";

				break;
			}

			case 4:
			{

			}

			case 5:
			{

			}

			case 6:
			{
				system("cls");
				cout << "goodbye!";
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
