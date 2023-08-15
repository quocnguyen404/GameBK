#include "Header/common.h"

using namespace std;

int main() 
{
	srand((unsigned int)time(0));
	Map maps[MAXMAPNUMBER] = {};

	// Initiate default maps
	Vector2 mapPos1(1, 1);
	Vector2 mapPos2(1, 2);
	Vector2 mapPos3(1, 3);

	//ofstream file;
	//file.open(mapPath, ofstream::trunc);
	//file.close();

	maps[1] = CreateMap(1, mapPos1, maps);
	maps[2] = CreateMap(2, mapPos2, maps);
	maps[3] = CreateMap(3, mapPos3, maps);
	LoadAllMapToFile(maps);

	int option = 0;
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
			{
				if (CountMap() >= MAXMAPNUMBER)
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
						cout << "Exist map at position " << position.x << " " << position.y << endl;
				}

				maps[CountMap()+1] = CreateMap(CountMap() + 1, position, maps);
				cout << "you created a new map!" << endl;
				LoadAllMapToFile(maps);
				Sleep(1000);
				break;
			}
				
			case 2:
			{
				system("cls");
				int modulType;
				int preMapIndex;
				int mapIndex;//the map that character in
				modulType = 0;
				int mapAroundIndex = 0;
				mapIndex = 0;
				preMapIndex = 0;

				//show map
				bool isPlaying = true;
				cout << "Press m to move" << endl;
				cout << "Press e to exit to menu" << endl;
				cout << "Press a to add modul in map" << endl;

				while (isPlaying)
				{
					if (_kbhit()) 
					{
						system("cls");
						char c = _getch();
						if (c == 'm') 
						{
							cout << "Enter the map that you want to go to: ";
							cin >> mapIndex;

							bool enterMapCanGo = false;

							for (int i = 0; i < 4; i++)
							{
								if (preMapIndex == 0)
									break;

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
						else if (c == 'a')
						{
							cout << "Enter map index to add modul" << endl;
							cin >> mapIndex;
							cout << "Enter modul type 1:Tree, 2:House, 3:Car" << endl;
							cin >> modulType;
						}
						else if (c == 'e') 
							isPlaying = false;
					}
				}
				break;
			}

			case 3:
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
