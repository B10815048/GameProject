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
	}*/
	/*management.loadUserfile(argv[1]);
	management.loadEnemyfile(argv[2]);
	management.setDebugMode(stoi(argv[3]));*/
	management.loadUserfile("C:\\Users\\black\\Downloads\\character3.txt");
	management.loadEnemyfile("C:\\Users\\black\\Downloads\\monster3.txt");
	management.setDebugMode(1);
    //////////////////////////////////////////////////////
	//if (management.getMode() == 0)
	//	management.setDebugMode(1);
	if (management.getMode())
	{
		while (getline(cin, input))
		{
			if (input == "play")
				management.runGAME();
			else if (input == "exit")
				return;
			else
				std::cout << "¿é¤J¿ù»~" << std::endl;
		}
	}
	else
	{
		management.startGame();
	}
    /////////////////////////////////////////////////////
}