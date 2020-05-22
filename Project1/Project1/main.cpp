#include <iostream>
#include "Management.h"
using namespace std;
int main()
{
    Management management;
	string input;
    //////////////////////////////////////////////////////
	while (cin >> input)
	{
		if (input == "play")
			management.runGAME();
		else if (input == "exit")
			return 0;
		else
			std::cout << "¿é¤J¿ù»~" << std::endl;
	}
    /////////////////////////////////////////////////////
}