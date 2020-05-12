#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

void Management::loadUserfile()
{
	std::fstream file;
	int position;
	int usernum, cardnum;
	int int_buffer;
	std::string string_buffer, topbuffer, belowbuffer;
	int i, j, k, l;
	file.open("character1.txt", std::ios::in);
	file >> usernum;
	user.resize(usernum);
	for (i = 0; i < usernum; i++)
	{
		file >> user[i].name;
		file >> user[i].HP;
		file >> user[i].CardOnHand;
		file >> cardnum;
		user[i].Card.resize(cardnum);
		for (j = 0; j < cardnum; j++)
		{
			file >> user[i].Card[j].Order;
			file >> user[i].Card[j].DEX;
			getline(file, string_buffer);
			for (k = 0; k < string_buffer.size(); k++)
			{
				if (string_buffer[k] == '-')
				{
					topbuffer = string_buffer.substr(0, k);
					belowbuffer = string_buffer.substr(k + 1, string_buffer.size() - k);
					break;
				}
			}
			std::stringstream topString(topbuffer);
			std::stringstream belowString(belowbuffer);
			while (topString >> string_buffer)
			{
				std::cout << string_buffer << std::endl;
				user[i].Card[j].TopType.push_back(getAbilityType(string_buffer));
				topString >> string_buffer;
				std::cout << string_buffer << std::endl << std::endl;
				user[i].Card[j].TopAbilityValue.push_back(string_buffer);
			}
			while (belowString >> string_buffer)
			{
				std::cout << string_buffer << std::endl;
				user[i].Card[j].BelowType.push_back(getAbilityType(string_buffer));
				belowString >> string_buffer;
				std::cout << string_buffer << std::endl << std::endl;
				user[i].Card[j].BelowAbilityValue.push_back(string_buffer);
			}
		}
	}
}

void Management::runGAME()
{
	int n;
	loadUserfile();
	loadEnemyfile();
	seletUser();
	loadMapfile(n);
	printMap();
}

int Management::getAbilityType(std::string Type)
{
	if (Type == "move")
		return 0;
	else if (Type == "heal")
		return 1;
	else if (Type == "shield")
		return 2;
	else if (Type == "attack")
		return 3;
	else if (Type == "range")
		return 4;

}