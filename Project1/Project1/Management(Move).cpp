#include "Management.h"
#include <iostream>
#include <regex>
#include <string>
////////////////////////////////////////////////////////////
//輸入移動命令：
void  Management::setMove(User& user, int step)
{
	if(debugMode == 0)
		std::cout << "輸入移動：" << "(上限 "  << step << " 步)" << std::endl;
	std::string moveCommand;
	std::regex form1("^[wasd]+$");
	std::regex form2("^e$"); //輸入只有一個e
	while (getline(std::cin , moveCommand))
	{
		if (std::regex_match(moveCommand, form1) || std::regex_match(moveCommand, form2))
		{
			if (moveCommand.size() <= step && Move(user, moveCommand))
				break;
			else
				std::cout << "error move!!!" << std::endl;
		}
		else
		std::cout << "error move!!!" << std::endl;
	}
}
////////////////////////////////////////////////////////////
//生物移動功能：
bool Management::Move(Creature& creature, std::string command)
{
	int i, j;
	Point tmp;
	std::vector <Point> point;
	tmp = creature.P;
	for (i = 0; i < command.size(); i++)
	{
		if (command[i] == 'w')
		{
			if ((checkSpace({ tmp.x , tmp.y - 1 }) || (checkDoor({ tmp.x , tmp.y - 1 }) && creature.Camp== 0)) && enemyOnPoint({ tmp.x, tmp.y - 1 }, creature.Camp) == 0)
				tmp.y--;
			else if (creature.Camp == 0)
				return false;
		}
		else if (command[i] == 's')
		{
			if ((checkSpace({ tmp.x , tmp.y + 1 }) || (checkDoor({ tmp.x , tmp.y + 1 }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x, tmp.y + 1 }, creature.Camp) == 0)
				tmp.y++;
			else if (creature.Camp == 0)
				return false;
		}	
		else if (command[i] == 'a')
		{
			if((checkSpace({ tmp.x - 1 , tmp.y }) || (checkDoor({ tmp.x-1 , tmp.y }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x - 1, tmp.y }, creature.Camp) == 0)
				tmp.x--;
			else if (creature.Camp == 0)
				return false;
		}
		else if (command[i] == 'd')
		{
			if ((checkSpace({ tmp.x + 1, tmp.y }) || (checkDoor({ tmp.x +1, tmp.y }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x + 1, tmp.y }, creature.Camp) == 0)
				tmp.x++;
			else if (creature.Camp == 0)
				return false;
		}
		point.push_back(tmp);
	}
	if (point.size() > 0)
	{
		if (creature.Camp == 0 && creatureOnPoint(point[point.size() - 1]) == 1 && !(creature.P == point[point.size() - 1]))
			return false;
	}

	for (i = point.size(); i > 0; i--)
	{
		if (creatureOnPoint(point[i - 1]) == 0 || (creatureOnPoint(point[i - 1]) == 1 && creature.P == point[i - 1])) //不能與生物重疊
		{
			creature.P = point[i - 1];
			break;
		}
	}
	if (debugMode == 0)
		return true;
	getxy(tmp);
	printMap(tmp);
	printEnemy(tmp);
	printUser(tmp);
	return true;
}
////////////////////////////////////////////////////////////
//確認該位置是否為門：
bool Management::checkDoor(Point p)
{
	if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
		return false;
	else if (map[p.y][p.x] == '3')
		return true;
	else
		return false;
}
////////////////////////////////////////////////////////////
//確認該位置是否為空地：
bool Management::checkSpace(Point p)
{
	if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
		return false;
	else if (map[p.y][p.x] == '1')
		return true;
	else
		return false;
}
////////////////////////////////////////////////////////////