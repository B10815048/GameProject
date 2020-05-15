#include "Management.h"

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
		if (creatureOnPoint(point[i - 1]) == 0)
		{
			creature.P = point[i - 1];
			break;
		}
	}
}