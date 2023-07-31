#include <stdio.h>
#include<windows.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
struct map {
	int x, y, z = 100;

};
void CreateMap(int a);//creat a map
void OBJ(int b);//input the information about object
void play();
int main() {
	CreateMap(1);
	CreateMap(2);
	return 0;
}
void OBJ(int b) {
	ifstream input;
	fstream output;
	string OJname;
	output.open("map.txt");
	output << "OBJ" << b << endl;
	switch (b) {
	case 1: OJname = "tree";//name of the object
		output << OJname << endl;
		output << "C:/Users/GIGABYTE/source/repos/gameBK/tree.obj" << endl;//the path of the file object
		output << "0,0,0" << endl;//location
		output << "0,0,0" << endl;//size
		output << "1,1,1" << endl;//swivel angle
		break;
	case 2: OJname = "house";
		output << OJname << endl;
		output << "C:/Users/GIGABYTE/source/repos/gameBK/house.obj" << endl;//the path of the file object
		output << "0,1,0" << endl;//location
		output << "0,0,0" << endl;//size
		output << "1,1,1" << endl;//swivel angle
		break;
		
	}
	output.close();


}
void play() {

}
void CreateMap(int a) {
	
	ifstream input;
	fstream output;
	
	output.open("map.txt");
	
	output << "MAP"<<a<<endl;
	
	output.close();
	

}
