#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

void Management::loadEnemyfile() //載入怪物資料
{
	std::fstream file;
	int enemynum;
	std::string string_buffer;
	int i, j;
	file.open("monster1.txt", std::ios::in); //開啟指定的怪物檔案
	file >> enemynum; //讀取怪物數量
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
			file >> string_buffer;
			file >> enemy[i].Card[j].Order;
			file >> enemy[i].Card[j].DEX;
			getline(file, string_buffer);
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
		if (enemyDeck[i].P == p )
			count++;
	}
	for (int i = 0; i < userDeck.size(); i++)
	{
		if (userDeck[i].P == p)
			count++;
	}
	return count;
}

int  Management::enemyOnPoint(Point p,int Camp)
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

void Management::Move(Creature& creature, std::string command)
{
	int i, j;
	Point tmp;
	std::vector <Point> point;
	tmp = creature.P;
	for (i = 0; i < command.size(); i++)
	{
		if (command[i] == 'w' && checkSpace({ tmp.x , tmp.y - 1 }) && enemyOnPoint({ tmp.x, tmp.y }, creature.Camp) == 0)
			tmp.y--;
		else if (command[i] == 's' && checkSpace({ tmp.x , tmp.y - 1 }) && enemyOnPoint({ tmp.x, tmp.y }, creature.Camp) == 0)
			tmp.y++;
		else if (command[i] == 'a' && checkSpace({ tmp.x , tmp.y - 1 }) && enemyOnPoint({ tmp.x, tmp.y }, creature.Camp) == 0)
			tmp.x--;
		else if (command[i] == 'd' && checkSpace({ tmp.x , tmp.y - 1 }) && enemyOnPoint({ tmp.x, tmp.y }, creature.Camp) == 0)
			tmp.x++;
		point.push_back(tmp);
	}
	for (i = point.size(); i > 0; i--)
	{
		if (creatureOnPoint(point[i-1])== 0 )
		{
			creature.P = point[i - 1];
			break;
		}
	}
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


