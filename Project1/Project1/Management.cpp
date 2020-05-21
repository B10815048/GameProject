#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

void Management::runGAME()
{
	Point p;
	loadUserfile();
	loadEnemyfile();
	seletUser();
	loadMapfile();
	getxy(p);
	printMap(p);
	printEnemy(p);
	seletPoint();
	while (!victoryCheck() && userDeck.size()>0)
	{
		playCard();
		resetShield();
	}
	if (victoryCheck())
		std::cout << "character win~" << std::endl;
	else
		std::cout << "monster win~" << std::endl;
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

Point operator+(Point a,Point b)
{
	Point tmp;
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	return tmp;
}

bool Point::operator==(Point b)
{
	return (this->x == b.x && this->y == b.y);
}

void Management::seletUser()
{
	int int_buffer;
	std::string string_buffer;
	int i, j;
	int Point;
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
				Point = j;
			}
		}
		userDeck[i].Camp = 0;
		userDeck[i].Icon = 65 + i;
		userDeck[i].Card.clear();
		for (j = 0; j < userDeck[i].CardOnHand; j++)
		{
			std::cin >> int_buffer;
			userDeck[i].Card.push_back(user[Point].Card[int_buffer]);
		}
	}
}

int  Management::creatureOnPoint(Point p)
{
	int count;
	count = 0;
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (enemyDeck[i].P == p)
			count++;
	}
	for (int i = 0; i < userDeck.size(); i++)
	{
		if (userDeck[i].P == p)
			count++;
	}
	return count;
}

int  Management::enemyOnPoint(Point p, int Camp)
{
	int count = 0;
	if (Camp == 0)
	{
		for (int i = 0; i < enemyDeck.size(); i++)
		{
			if (enemyDeck[i].P == p)
				count++;
		}
	}
	else if (Camp == 1)
	{
		for (int i = 0; i < userDeck.size(); i++)
		{
			if (userDeck[i].P == p)
				count++;
		}
	}
	return count;
}

