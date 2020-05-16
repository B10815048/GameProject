#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

bool Management::viewableRange(Point start, Point end)
{
	int i;
	if (start.x != end.x)
	{
		for (i = start.x; i != end.x; i = i + (end.x - start.x) / abs(end.x - start.x))
		{

		}
	}
}
void Management::runGAME()
{
	Point p;
	loadUserfile();
	loadEnemyfile();
	/*for (int i = 0; i < user.size(); i++)
	{
		std::cout << "名稱：" << user[i].name << " 最大血量：" << user[i].HP << std::endl;
		for (int j = 0; j < user[i].Card.size(); j++)
		{
			std::cout << "代號：" << user[i].Card[j].Order  << " 敏捷：" << user[i].Card[j].DEX << " " << std::endl;
			for (int k = 0; k < user[i].Card[i].TopType.size(); k++)
			{
				std::cout << "上方技能類型：" << user[i].Card[j].TopType[k] << " 上方技能值：" << user[i].Card[j].TopAbilityValue[k] << " " << std::endl;
			}
			for (int k = 0; k < user[i].Card[i].BelowType.size(); k++)
			{
				std::cout << "下方技能類型：" << user[i].Card[j].BelowType[k] << " 下方技能值：" << user[i].Card[j].BelowAbilityValue[k] << " " << std::endl;
			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		std::cout << "名稱："<< enemy[i].name << std::endl;
		std::cout << "一般血量："<< enemy[i].HP[0] << " 一般範圍："<< enemy[i].Range[0] << " 一般傷害："<< enemy[i].STR[0] << std::endl;
		std::cout << "菁英血量："<< enemy[i].HP[1] << " 菁英範圍："<< enemy[i].Range[1] << " 菁英傷害："<< enemy[i].STR[1] << std::endl;
		for (int j = 0; j < enemy[i].Card.size(); j++)
		{
			std::cout << "代號：" << enemy[i].Card[j].Order  << " 敏捷：" << enemy[i].Card[j].DEX << " ";
			for (int k = 0; k < enemy[i].Card[j].Type.size(); k++)
			{
				std::cout << "技能類型：" << enemy[i].Card[j].Type[k] << " 技能數值：" << enemy[i].Card[j].AbilityValue[k]<< std::endl;
			}
		}
		std::cout << std::endl;
	}
	seletUser();
	std::cout << std::endl;
	for (int i = 0; i < userDeck.size(); i++)
	{
		std::cout << "名稱：" << userDeck[i].name << " 最大血量：" << userDeck[i].HP << " Icon：" << userDeck[i].Icon << std::endl;
		for (int j = 0; j < userDeck[i].Card.size(); j++)
		{
			std::cout << "代號：" << userDeck[i].Card[j].Order << " 敏捷：" << userDeck[i].Card[j].DEX << " " << std::endl;
			for (int k = 0; k < userDeck[i].Card[j].TopType.size(); k++)
			{
				std::cout << "上方技能類型：" << userDeck[i].Card[j].TopType[k] << " 上方技能值：" << userDeck[i].Card[j].TopAbilityValue[k] << " " << std::endl;
			}
			for (int k = 0; k < userDeck[i].Card[i].BelowType.size(); k++)
			{
				std::cout << "下方技能類型：" << userDeck[i].Card[j].BelowType[k] << " 下方技能值：" << userDeck[i].Card[j].BelowAbilityValue[k] << " " << std::endl;
			}
		}
		std::cout << std::endl;
	}*/
	while (1)
	{
		loadMapfile();
		getxy(p);
		printMap(p);
		printEnemy(p);

	}
	

	seletPoint();
	playCard();
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

bool Management::checkSpace(Point p)
{
	if (p.x < 0 || p.x >= width || p.x < 0 || p.x >= height)
		return false;
	else if (map[p.y][p.x] == '1')
		return true;
	else
		return false;
}