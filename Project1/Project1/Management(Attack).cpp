#include "Management.h"
#include <cmath>
#include <iomanip>
#include <string>
#include <regex>

void Management::positiveValue(int& num)
{
	if (num < 0)
		num = 0;
	return;
}

void Management::Attack(Creature& creature, std::string command)
{
	int i, j;
	int position;
	int enemyX, enemyY;
	std::string input;
	std::regex attack("^[a-z]{1}$");
	std::regex giveUp("0");
	int damage = creature.Attack + stoi(command);
	positiveValue(creature.Range);
	positiveValue(damage);
	if (creature.Range == 0)
		creature.Range = 1;
	if (creature.Camp == 0) //主角方
	{
		std::cout << "選擇攻擊敵人 : " << std::endl;
		while (std::cin >> input)
		{
			if (std::regex_match(input, attack) && findCreatureDeckPosition(1, input[0]) != -1) //符合攻擊目標及在攻擊範圍內
			{
				position = findCreatureDeckPosition(1, input[0]);
				if (shootRange(creature.P, enemyDeck[position].P, 0, creature.Range) <= creature.Range && viewableRange(enemyDeck[position].P, creature.P))
				{
					if (damage > enemyDeck[position].Shield)
						enemyDeck[position].HP[enemyDeck[position].Type] -= damage - enemyDeck[position].Shield;
					std::cout << creature.Icon << " attack " << enemyDeck[position].Icon << " " << damage << " damage, " << enemyDeck[position].Icon << " shield " << enemyDeck[position].Shield
						<< " , " << enemyDeck[position].Icon << " remain " << enemyDeck[position].HP[enemyDeck[position].Type] << " hp" << std::endl;
					return;
				}
				else
					std::cout << "error target!!!" << std::endl;

			}
			else if (std::regex_match(input, giveUp))
			{
				std::cout << "放棄攻擊..." << std::endl;
				return;
			}
			else
			std::cout << "error target!!!" << std::endl;
		}
	}
	else if (creature.Camp == 1) //敵人方
	{
		int step = 0, minStep = 99, count = 0;
		int userIndex[4] = { 0,0,0,0 };
		for (int j = 0; j < 4; j++)
			userIndex[j] = 0;
		for (i = 0; i < userDeck.size(); i++)
		{
			if (shootRange(creature.P, userDeck[i].P, 1, creature.Range) <= creature.Range && viewableRange(userDeck[i].P, creature.P))
			{
				step = shootRange(creature.P, userDeck[i].P, 1, creature.Range);
				if (step < minStep)
				{
					for (int j = 0; j < 4; j++)
						userIndex[j] = 0;

					minStep = step;
					userIndex[i] = 1;
					count = 1;
				}
				else if (step == minStep)
				{
					userIndex[i] = 1;
					count += 1;
				}
			}	
		}
		if (count == 0)
		{
			std::cout << "no one lock" << std::endl;
		}
		else if (count == 1)
		{
			for (int i = 0; i < userDeck.size(); i++)
			{
				if (userIndex[i] == 1)
				{
					std::cout << creature.Icon << " lock " << userDeck[i].Icon << " in distance " << minStep << std::endl;
					if (damage > userDeck[i].Shield)
						userDeck[i].HP -= damage - userDeck[i].Shield;
					std::cout << creature.Icon << " attack " << userDeck[i].Icon << " " << damage << " damage, " << userDeck[i].Icon << " shield " << userDeck[i].Shield
						<< " , " << userDeck[i].Icon << " remain " << userDeck[i].HP << " hp" << std::endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < compairList.size(); i++)
			{
				for (int j = 0; j < userDeck.size(); j++)
				{
					if (compairList[i].Icon == userDeck[j].Icon && userIndex[j] == 1)
					{
						std::cout << creature.Icon << " lock " << userDeck[i].Icon << " in distance " << minStep << std::endl;
						if (damage > userDeck[j].Shield)
							userDeck[j].HP -= damage - userDeck[j].Shield;
						std::cout << creature.Icon << " attack " << userDeck[j].Icon << " " << damage << " damage, " << userDeck[j].Icon << " shield " << userDeck[j].Shield
							<< " , " << userDeck[j].Icon << " remain " << userDeck[j].HP << " hp" << std::endl;
						return;
					}
				}
			}
		}
	}
	resetRange();
}

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

void  Management::resetRange()
{
	int i, j;
	int position;
	for (i = 0; i < userDeck.size(); i++)
	{
		position = findCreaturePosition(0, userDeck[i].name);
		userDeck[i].Range = user[position].Range;
	}
	for (i = 0; i < enemyDeck.size(); i++)
	{
		position = findCreaturePosition(1, enemyDeck[i].name);
		enemyDeck[i].Range = enemy[position].Range;
	}
}