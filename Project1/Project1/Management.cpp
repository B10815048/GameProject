#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

////////////////////////////////////////////////////////////
//±´³X¥iµø°Ï°ì¡G
char Management::Search(std::vector<std::vector<char> >& map, int x, int y)
{
	if (map[y][x] != 'x' || map[y][x] == 'y' || map[y][x] == '4')
	{
		if (map[y][x] == '4')
			map[y][x] = '3';
		else if (map[y][x] == 'y')
			map[y][x] = '2';
		return 'x';
	}
	else
		map[y][x] = '1';
	if (Search(map, x + 1, y) != 'x' || Search(map, x - 1, y) != 'x' || Search(map, x, y + 1) != 'x' || Search(map, x, y - 1) != 'x')
		return 'x';
}

void Management::positiveValue(int& num)
{
	if (num < 0)
		num = 0;
	return;
}

void Management::runGAME()
{
	userDeck.clear();
	enemyDeck.clear();
	user.clear();
	enemy.clear();
	map.clear();
	checkMap.clear();
	std::string input = "";
	Point p;
	round_count = 0;
	loadUserfile();
	loadEnemyfile();
	seletUser();
	loadMapfile();
	getxy(p);
	printMap(p);
	printEnemy(p);
	seletPoint();
	while (!victoryCheck() && userDeck.size() > 0)
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

