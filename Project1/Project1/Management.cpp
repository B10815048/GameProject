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
		std::cout << "�W�١G" << user[i].name << " �̤j��q�G" << user[i].HP << std::endl;
		for (int j = 0; j < user[i].Card.size(); j++)
		{
			std::cout << "�N���G" << user[i].Card[j].Order  << " �ӱ��G" << user[i].Card[j].DEX << " " << std::endl;
			for (int k = 0; k < user[i].Card[i].TopType.size(); k++)
			{
				std::cout << "�W��ޯ������G" << user[i].Card[j].TopType[k] << " �W��ޯ�ȡG" << user[i].Card[j].TopAbilityValue[k] << " " << std::endl;
			}
			for (int k = 0; k < user[i].Card[i].BelowType.size(); k++)
			{
				std::cout << "�U��ޯ������G" << user[i].Card[j].BelowType[k] << " �U��ޯ�ȡG" << user[i].Card[j].BelowAbilityValue[k] << " " << std::endl;
			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		std::cout << "�W�١G"<< enemy[i].name << std::endl;
		std::cout << "�@���q�G"<< enemy[i].HP[0] << " �@��d��G"<< enemy[i].Range[0] << " �@��ˮ`�G"<< enemy[i].STR[0] << std::endl;
		std::cout << "�׭^��q�G"<< enemy[i].HP[1] << " �׭^�d��G"<< enemy[i].Range[1] << " �׭^�ˮ`�G"<< enemy[i].STR[1] << std::endl;
		for (int j = 0; j < enemy[i].Card.size(); j++)
		{
			std::cout << "�N���G" << enemy[i].Card[j].Order  << " �ӱ��G" << enemy[i].Card[j].DEX << " ";
			for (int k = 0; k < enemy[i].Card[j].Type.size(); k++)
			{
				std::cout << "�ޯ������G" << enemy[i].Card[j].Type[k] << " �ޯ�ƭȡG" << enemy[i].Card[j].AbilityValue[k]<< std::endl;
			}
		}
		std::cout << std::endl;
	}
	seletUser();
	std::cout << std::endl;
	for (int i = 0; i < userDeck.size(); i++)
	{
		std::cout << "�W�١G" << userDeck[i].name << " �̤j��q�G" << userDeck[i].HP << " Icon�G" << userDeck[i].Icon << std::endl;
		for (int j = 0; j < userDeck[i].Card.size(); j++)
		{
			std::cout << "�N���G" << userDeck[i].Card[j].Order << " �ӱ��G" << userDeck[i].Card[j].DEX << " " << std::endl;
			for (int k = 0; k < userDeck[i].Card[j].TopType.size(); k++)
			{
				std::cout << "�W��ޯ������G" << userDeck[i].Card[j].TopType[k] << " �W��ޯ�ȡG" << userDeck[i].Card[j].TopAbilityValue[k] << " " << std::endl;
			}
			for (int k = 0; k < userDeck[i].Card[i].BelowType.size(); k++)
			{
				std::cout << "�U��ޯ������G" << userDeck[i].Card[j].BelowType[k] << " �U��ޯ�ȡG" << userDeck[i].Card[j].BelowAbilityValue[k] << " " << std::endl;
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
	std::cout << "�п�J�X������ƶq:" << std::endl;
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