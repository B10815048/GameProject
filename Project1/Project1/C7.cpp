#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

void Management::loadEnemyfile()
{
	std::fstream file;
	int enemynum;
	std::string string_buffer;
	int i, j;
	file.open("monster1.txt", std::ios::in);
	file >> enemynum;
	enemy.resize(enemynum);
	for (i = 0; i < enemynum; i++)
	{
		file >> enemy[i].name;
		for (j = 0; j < 2; j++)
		{
			file >> enemy[i].HP[j];
			file >> enemy[i].STR[j];
			file >> enemy[i].Range[j];
		}
		enemy[i].Card.resize(6);
		for (j = 0; j < 6; j++)
		{
			file >> string_buffer; //確認是否會有位置交換的可能
			file >> enemy[i].Card[j].Order;
			file >> enemy[i].Card[j].DEX;
			getline(file, string_buffer);
			;
			if (string_buffer.substr(string_buffer.size() - 1, 1) == "r")
				enemy[i].Card[j].Shuffle = true;
			else if (string_buffer.substr(string_buffer.size() - 1, 1) == "d")
				enemy[i].Card[j].Shuffle = false;
			string_buffer = string_buffer.substr(0, string_buffer.size() - 1);
			std::stringstream lineString(string_buffer);
			while (lineString >> string_buffer)
			{
				std::cout << string_buffer << std::endl;
				enemy[i].Card[j].Type.push_back(getAbilityType(string_buffer));
				lineString >> string_buffer;
				std::cout << string_buffer << std::endl << std::endl;
				enemy[i].Card[j].AbilityValue.push_back(string_buffer);
			}
		}
	}
}

void Management::seletUser()
{
	int int_buffer;
	std::string string_buffer;
	int i, j;
	int position;
	std::cout << "請輸入出場角色數量:" << std::endl;
	std::cin >> int_buffer;
	userDeck.resize(int_buffer);
	for (i = 0; i < userDeck.size(); i++)
	{
		std::cin >> string_buffer;
		for (j = 0; j < user.size(); j++)
		{
			if (user[j].name == string_buffer)
			{
				userDeck[i] = user[j];
				position = j;
			}
		}
		userDeck[i].Icon = 65 + i;
		userDeck[i].Card.clear();
		for (j = 0; j < userDeck[i].CardOnHand; j++)
		{
			std::cin >> int_buffer;
			userDeck[i].Card.push_back(user[position].Card[int_buffer]);
		}
	}
	std::cout << userDeck[1].Icon << std::endl;

	int n;
	std::cin >> n;
	enemyDeck.resize(n);
	for (i = 0; i < enemyDeck.size(); i)
	{
		std::cin >> string_buffer;
		for (j = 0; j < enemy.size(); j++)
		{
			if (enemy[j].name == string_buffer)
			{
				enemyDeck[i] = enemy[j];
				position = j;
			}
		}
		std::cin >> int_buffer >> int_buffer; //x and y
		for (j = 1; j < userDeck.size(); j++)
			std::cin >> int_buffer;
		std::cout << int_buffer << std::endl;
		if (int_buffer == 0)
			enemyDeck.erase(enemyDeck.begin()+i);//i不變
		else if (int_buffer == 1)
		{
			enemyDeck[i].Type = 0;
			i++;
		}
		else if(int_buffer == 2)
		{
			enemyDeck[i].Type = 1;
			i++;
		}
		for (j = userDeck.size();j<4; j++)
			std::cin >> int_buffer;
	}
	std::cout << enemyDeck.size() << std::endl;
}