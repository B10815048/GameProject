#include "Management.h"
#include <cmath>
#include <iomanip>
#include <string>
#include <regex>

void  Management::Range(User& user, std::string command)
{
	user.Range = user.Range + stoi(command);
}

void Management::Range(Enemy& enemy, std::string command)
{
	enemy.Range = enemy.Range + stoi(command);
}
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
	if (creature.Camp == 0) //�D����
	{
		std::cout << "��ܧ����ĤH : " << std::endl;
		while (std::cin >> input)
		{
			if (std::regex_match(input, attack) && findCreatureDeckPosition(1, input[0]) != -1) //�ŦX�����ؼФΦb�����d��
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
				std::cout << "������..." << std::endl;
				return;
			}
			else
			std::cout << "error target!!!" << std::endl;
		}
	}
	else if (creature.Camp == 1) //�ĤH��
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

int Management::shootRange(Point start, Point end, int camp,int maxRange)
{
	int i, j;
	checkMap.resize(height);
	for (i = 0; i < checkMap.size(); i++)
		checkMap[i].resize(width);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == '0' || (enemyOnPoint({ j,i }, camp) != 0 && !(end == Point{ j, i })))
			{
				checkMap[i][j] = -1;
			}
			else
				checkMap[i][j] = -2;
		}
	}
	checkMap[start.y][start.x] = 0;
	viewR(start, 0);
	viewU(start, 0);
	viewD(start, 0);
	viewL(start, 0);
	int n = 0;
	while (checkMap[end.y][end.x] <= 0 && n <= maxRange)
	{
		n++;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (checkMap[i][j] == n)
				{
					viewR({ j, i }, n);
					viewU({ j, i }, n);
					viewD({ j, i }, n);
					viewL({ j, i }, n);
				}
			}
		}
	}
	if (n > maxRange)
		return maxRange + 1;
	return checkMap[end.y][end.x];
}
//////////////////////////////////////////////////////////////
//���X�k�� : 
int Management::viewR(Point start, int n)
{
	if (checkMap[start.y][start.x + 1] == -2)
	{
		checkMap[start.y][start.x + 1] = n + 1;
		return viewR({ start.x + 1,start.y }, n + 1);
	}
	else
	return 0;
}
//////////////////////////////////////////////////////////////
//���X�W�� : 
int Management::viewU(Point start, int n)
{
	if (checkMap[start.y - 1][start.x] == -2)
	{
		checkMap[start.y - 1][start.x] = n + 1;
		return viewU({ start.x,start.y - 1 }, n + 1);
	}
	else
		return 0;
}
//////////////////////////////////////////////////////////////
//���X�U�� : 
int Management::viewD(Point start, int n)
{
	if (checkMap[start.y + 1][start.x] == -2)
	{
		checkMap[start.y + 1][start.x] = n + 1;
		return viewD({ start.x,start.y + 1 }, n + 1);
	}
	else 
		return 0;
}
//////////////////////////////////////////////////////////////
//���X���� : 
int Management::viewL(Point start, int n)
{
	if (checkMap[start.y][start.x - 1] == -2)
	{
		checkMap[start.y][start.x - 1] = n + 1;
		return viewL({ start.x - 1,start.y }, n + 1);
	}
	else
		return 0;
}
//////////////////////////////////////////////////////////////
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