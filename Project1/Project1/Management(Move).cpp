#include "Management.h"
#include <iostream>
void  Management::setMove(User& user, int step)
{
	std::cout << "輸入移動：" << std::endl;
	std::string moveCommand;
	while (std::cin >> moveCommand)
	{
		if (moveCommand.size() <= step && Move(user, moveCommand))
			break;
		std::cout << "不合規範" << std::endl;
	}
}

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
			if ((checkSpace({ tmp.x , tmp.y + 1 }) || (checkDoor({ tmp.x , tmp.y - 1 }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x, tmp.y + 1 }, creature.Camp) == 0)
				tmp.y++;
			else if (creature.Camp == 0)
				return false;
		}	
		else if (command[i] == 'a')
		{
			if((checkSpace({ tmp.x - 1 , tmp.y }) || (checkDoor({ tmp.x , tmp.y - 1 }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x - 1, tmp.y }, creature.Camp) == 0)
				tmp.x--;
			else if (creature.Camp == 0)
				return false;
		}
		else if (command[i] == 'd')
		{
			if ((checkSpace({ tmp.x + 1, tmp.y }) || (checkDoor({ tmp.x , tmp.y - 1 }) && creature.Camp == 0)) && enemyOnPoint({ tmp.x + 1, tmp.y }, creature.Camp) == 0)
				tmp.x++;
			else if (creature.Camp == 0)
				return false;
		}
		point.push_back(tmp);
	}
	for (i = point.size(); i > 0; i--)
	{
		if (creatureOnPoint(point[i - 1]) == 0)
		{
			creature.P = point[i - 1];
			break;
		}
	}
	getxy(tmp);
	printMap(tmp);
	printEnemy(tmp);
	printUser(tmp);
	return true;
}

bool Management::checkDoor(Point p)
{
	if (p.x < 0 || p.x >= width || p.x < 0 || p.x >= height)
		return false;
	else if (map[p.y][p.x] == '3')
		return true;
	else
		return false;
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