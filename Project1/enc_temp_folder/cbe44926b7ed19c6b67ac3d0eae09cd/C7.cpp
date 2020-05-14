#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

std::vector <std::vector<char> > map;

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
				enemy[i].Card[j].Type.push_back(getAbilityType(string_buffer));
				lineString >> string_buffer;
				enemy[i].Card[j].AbilityValue.push_back(string_buffer);
			}
		}
	}
	file.close();
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
}

void Creature::Move(std::string command)
{
	int i, j;
	for (i = 0; i < command.size(); i++)
	{
		if (command[i] == 'w'&& map[this->P.y-1][this->P.x]==1 )
		{

		}

	}
}

void Management::printEnemy(Point p)
{
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1')
		{

			gotoxy({ p.x + enemyDeck[i].P.x,p.y + enemyDeck[i].P.y });
			std::cout << enemyDeck[i].Icon;
		}
	}
	gotoxy({ p.x,p.y + height });
}