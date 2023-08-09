#include "Header/common.h"

using namespace std;


int main() 
{
	srand(time(0));


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
			system("cls");
			CreateMap(CountMap()+1);
			cout << "you created a new map!" << endl;
			Sleep(1000);
			break;

		case 2:
			system("cls");
			Play();
			break;

		case 3:
			system("cls");
			cout << "goodbye!";
			return 0;

		default:
			cout << "Doesn't exist that option" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}
