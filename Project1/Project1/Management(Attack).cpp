#include "Management.h"
#include <cmath>
#include <iomanip>
#include <string>

void  Management::Range(User& user, std::string command)
{
	user.Range = user.Range +stoi(command);
}

void Management::Range(Enemy& enemy, std::string command)
{
	enemy.Range[enemy.Type] = enemy.Range[enemy.Type] + stoi(command);
}

void Management::Attack(Creature& creature, std::string command)
{
	char Icon;
	int i, j;
	int position;
	int enemyX, enemyY;
	if (creature.Camp == 0) //主角方
	{
		std::cout << "媽的選角拉 : " << std::endl;
		while (std::cin >> Icon)
		{
			if (Icon == '0')
			{
				std::cout << "媽的不公及 : " << std::endl;
				return;
			}
			else
			{
				for (i = 0; i < enemyDeck.size(); i++)
				{
					if (Icon == enemyDeck[i].Icon)
						position = i;
				}

				if (shootRange(creature.P, enemyDeck[position].P, creature.Range, 0) && viewableRange(enemyDeck[position].P, creature.P))
				{
					if (stoi(command) > enemyDeck[position].Shield)
						enemyDeck[position].HP[enemyDeck[position].Type] -= stoi(command) - enemyDeck[position].Shield;
					std::cout << creature.Icon << " attack " << enemyDeck[position].Icon << " " << stoi(command) << " damage, " << enemyDeck[position].Icon << " shield " << enemyDeck[position].Shield
						<< " , " << enemyDeck[position].Icon << " remain " << enemyDeck[position].HP[enemyDeck[position].Type] << " hp" << std::endl;
					return;
				}
				else
				{
					std::cout << "error target!!!" << std::endl;
				}
			}
		}
	}
	else if (creature.Camp ==1) //敵人方
	{

	}
}

bool  Management::oneGapCheck(int x, float y1, float y2)
{
	int j;
	for (j = ceil(y1); j != floor(y2); j = j + (floor(y2) - ceil(y1)) / abs(floor(y2) - ceil(y1)))
	{
		if (map[j - 1][x] == '2')
			return false;
	}
	return true;
}
bool Management::viewableRange(Point start, Point end)
{
	int i,j;
	float a, gap;
	if (start.x != end.x)
	{
		a = (float)(end.y-start.y)/ abs(end.x-start.x);
		gap = 0.5 + start.y;
		if(oneGapCheck(start.x, gap+ (a/2),gap ))
			return false;
		gap = gap + (a/2) ;
		i = start.x;
		while (i != end.x - (end.x - start.x) / abs(end.x - start.x))
		{
			if (oneGapCheck(i + (end.x - start.x) / abs(end.x - start.x), gap + a, gap))
				return false;
			i = i + (end.x - start.x) / abs(end.x - start.x);
			gap = a + gap;
		}
		if(oneGapCheck(end.x, gap + (a / 2), gap))
			return false;
	}
	else
	{
		for (i = start.y; i != end.y; i = i + (end.y - start.y) / abs(end.y - start.y))
		{
			if (map[i][start.x] == '2')
				return false;
		}	
		if (map[i][start.x] == '2')
			return false;
	}
	printMap(start);
	return true;
}

bool Management::shootRange(Point start, Point end, int step, int camp)
{
	int i, j;
	if (map[end.y][end.x] != '1')
		return false;

	checkMap.resize(height);
	for (i = 0; i < checkMap.size(); i++)
		checkMap[i].resize(width);
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == '3' || map[i][j] == '0' || (enemyOnPoint({ j,i }, camp)!=0 && !(end == Point{ j, i })))
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
	while (checkMap[end.y][end.x] <= 0)
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
	checkMap[start.y][start.x] = 0;
	std::cout << checkMap[end.y][end.x] << std::endl;
	if (checkMap[end.y][end.x] <= step)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////
//拜訪右側 : 
int Management::viewR(Point start, int n)
{
	if (checkMap[start.y][start.x + 1] == -1)
		return 0;
	else if (checkMap[start.y][start.x + 1] == -2)
	{
		checkMap[start.y][start.x + 1] = n + 1;
		return viewR({ start.x + 1,start.y }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//拜訪上方 : 
int Management::viewU(Point start, int n)
{
	if (checkMap[start.y - 1][start.x] == -1)
		return 0;
	else if (checkMap[start.y - 1][start.x] == -2)
	{
		checkMap[start.y - 1][start.x] = n + 1;
		return viewU({ start.x,start.y - 1 }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//拜訪下方 : 
int Management::viewD(Point start, int n)
{
	if (checkMap[start.y + 1][start.x] == -1)
		return 0;
	else if (checkMap[start.y + 1][start.x] == -2)
	{
		checkMap[start.y + 1][start.x] = n + 1;
		return viewD({ start.x,start.y + 1 }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//拜訪左側 : 
int Management::viewL(Point start, int n)
{
	if (checkMap[start.y][start.x - 1] == -1)
		return 0;
	else if (checkMap[start.y][start.x - 1] == -2)
	{
		checkMap[start.y][start.x - 1] = n + 1;
		return viewL({ start.x - 1,start.y }, n + 1);
	}
}
//////////////////////////////////////////////////////////////