#include "Management.h"
#include <iostream>
void  Management::setMove(User& user, int step)
{
	std::cout << "¿é¤J²¾°Ê¡G" << std::endl;
	std::string moveCommand;
	while (std::cin >> moveCommand)
	{
		if (moveCommand.size() <= step)
			break;
	}
	Move(user, moveCommand);
}

void Management::Move(Creature& creature, std::string command)
{
	int i, j;
	Point tmp;
	std::vector <Point> point;
	tmp = creature.P;
	for (i = 0; i < command.size(); i++)
	{
		if (command[i] == 'w' && (checkSpace({ tmp.x , tmp.y - 1 }) || checkDoor({ tmp.x , tmp.y - 1 })) && enemyOnPoint({ tmp.x, tmp.y-1 }, creature.Camp) == 0)
			tmp.y--;
		else if (command[i] == 's' && (checkSpace({ tmp.x , tmp.y + 1 }) || checkDoor({ tmp.x , tmp.y + 1 })) && enemyOnPoint({ tmp.x, tmp.y+1 }, creature.Camp) == 0)
			tmp.y++;
		else if (command[i] == 'a' && (checkSpace({ tmp.x-1 , tmp.y  }) || checkDoor({ tmp.x-1 , tmp.y })) && enemyOnPoint({ tmp.x-1, tmp.y }, creature.Camp) == 0)
			tmp.x--;
		else if (command[i] == 'd' && (checkSpace({ tmp.x +1, tmp.y  }) || checkDoor({ tmp.x +1, tmp.y })) && enemyOnPoint({ tmp.x+1, tmp.y }, creature.Camp) == 0)
			tmp.x++;
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
	std::cout << creature.P.x << " " << creature.P.y << std::endl;
	getxy(tmp);
	printMap(tmp);
	printEnemy(tmp);
	printUser(tmp);
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