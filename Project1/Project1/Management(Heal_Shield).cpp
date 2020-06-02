#include "Management.h"
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
////////////////////////////////////////////////////////////
//使用者治療技能：
void Management::Heal(User& user, std::string command)
{
	int value, position;
	std::stringstream ss;
	ss << command;
	ss >> value;
	user.HP += value;
	position = findCreaturePosition(0, user.name);
	if (this->user[position].HP < user.HP)//超出血量最大值時	
		user.HP = this->user[position].HP;
	std::cout << user.Icon << " heal " << value << ", now hp is " << user.HP << std::endl;
	if (debugMode == 0)
	{
		std::string msg = user.Icon + std::string(" 回復 ") + std::to_string(value) + " 點, 現在血量: " + std::to_string(user.HP);
		addBattleMsg(msg);
	}
}
////////////////////////////////////////////////////////////
//怪物治療技能：
void Management::Heal(Enemy& enemy, std::string command)
{
	int value, position;
	std::stringstream ss;
	ss << command;
	ss >> value;
	enemy.HP[enemy.Type] = value + enemy.HP[enemy.Type];
	position = findCreaturePosition(1, enemy.name);
	if (this->enemy[position].HP[enemy.Type] < enemy.HP[enemy.Type]) //超出血量最大值時
		enemy.HP[enemy.Type] = this->enemy[position].HP[enemy.Type];
	std::cout << enemy.Icon << " heal " << value << ", now hp is " << enemy.HP[enemy.Type] << std::endl;
	if (debugMode == 0)
	{
		std::string msg = enemy.Icon + std::string(" 回復 ") + std::to_string(value) + " 點, 現在血量: " + std::to_string(enemy.HP[enemy.Type]);
		addBattleMsg(msg);
	}
}
////////////////////////////////////////////////////////////
//生物護甲技能：
void Management::Shield(Creature& creature, std::string command)
{
	int value;
	std::stringstream ss;
	ss << command;
	ss >> value;
	creature.Shield += value;
	std::cout << creature.Icon << " shield " << value << " this turn" << std::endl;
	if (debugMode == 0)
	{
		std::string msg = creature.Icon + std::string(" 獲得 ") + std::to_string(value) + " 點護甲";
		addBattleMsg(msg);
	}
}
////////////////////////////////////////////////////////////
//使用者長休技能：
void Management::rest(User& user)
{
	std::string input;
	int index;
	int i;
	std::regex deleteCheck("^[0-9]+$");
	if(debugMode == 0)
		std::cout << "選擇一張牌刪除：" << std::endl;
	while (getline(std::cin,input))
	{
		if (std::regex_match(input, deleteCheck))
		{
			index = stoi(input);
			for (i = 0; i < user.disCardDeck.size(); i++)
			{
				if (user.disCardDeck[i].Order == index)
				{
					Heal(user, "2");
					std::cout << "remove card: " << index << std::endl;
					user.disCardDeck.erase(user.disCardDeck.begin() + i);
					if (debugMode == 0)
						addBattleMsg("刪除了 " + std::to_string(index) + std::string(" 號卡"));
					user.Card.insert(user.Card.end(), user.disCardDeck.begin(), user.disCardDeck.end());
					user.disCardDeck.clear();
					return;
				}
			}
		}
		std::cout << "重新選擇：" << std::endl;
	}
}
////////////////////////////////////////////////////////////
//還原護甲數值：
void  Management::resetShield()
{
	int i, j;
	int position;
	for (i = 0; i < userDeck.size(); i++)
	{
		position = findCreaturePosition(0, userDeck[i].name);
		userDeck[i].Shield = user[position].Shield;
	}
	for (i = 0; i < enemyDeck.size(); i++)
	{
		position = findCreaturePosition(1, enemyDeck[i].name);
		enemyDeck[i].Shield = enemy[position].Shield;
	}
}
////////////////////////////////////////////////////////////