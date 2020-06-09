#include <iostream>
#include <string>
#include "Management.h"
using namespace std;
void main(int argc, char* argv[])
{
    Management management;
	string input;
	/*if (argc != 4)
	{
		cout << "Testing" << endl;
		return;
	}
	management.loadUserfile(argv[1]);
	management.loadEnemyfile(argv[2]);
	management.setDebugMode(stoi(argv[3]));*/
	management.loadUserfile("E:\\GameProject\\Project1\\x64\\Release\\character.txt");
	management.loadEnemyfile("E:\\GameProject\\Project1\\x64\\Release\\monster.txt");
	management.setDebugMode(0);
    //////////////////////////////////////////////////////
	while (getline(cin, input))
	{
		if (input == "play")
			management.runGAME();
		else if (input == "exit")
			return;
		else
			std::cout << "¿é¤J¿ù»~" << std::endl;
	}
    /////////////////////////////////////////////////////
}