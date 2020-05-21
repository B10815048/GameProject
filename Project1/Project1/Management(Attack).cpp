#include "Management.h"
#include <cmath>
#include <iomanip>
#include <string>
/////////
void  Management::Range(User& user, std::string command)
{
	user.Range = user.Range +stoi(command);
}

void Management::Range(Enemy& enemy, std::string command)
{
	enemy.Range = enemy.Range + stoi(command);
}

void Management::Attack(Creature& creature, std::string command)
{
	char Icon;
	int i, j;
	int position;
	int enemyX, enemyY;
	int damage = creature.Attack + stoi(command);
	if (damage < 0)
		damage = 0;
	if (creature.Range == 0)
		creature.Range = 1;
	if (creature.Camp == 0) //¥D¨¤¤è
	{
		std::cout << "¿ï¾Ü§ðÀ»¼Ä¤H : " << std::endl;
		while (std::cin >> Icon)
		{
			if (Icon == '0')
			{
				std::cout << "©ñ±ó§ðÀ»..." << std::endl;
				return;
			}
			else if (position = findCreatureDeckPosition(1, Icon)!=-1)
			{
				position = findCreatureDeckPosition(1, Icon);
				if (shootRange(creature.P, enemyDeck[position].P, creature.Range, 0, creature.Range) && viewableRange(enemyDeck[position].P, creature.P))
				{
					if (damage > enemyDeck[position].Shield)
						enemyDeck[position].HP[enemyDeck[position].Type] -= damage - enemyDeck[position].Shield;
					std::cout << creature.Icon << " attack " << enemyDeck[position].Icon << " " << damage << " damage, " << enemyDeck[position].Icon << " shield " << enemyDeck[position].Shield
						<< " , " << enemyDeck[position].Icon << " remain " << enemyDeck[position].HP[enemyDeck[position].Type] << " hp" << std::endl;

					return;
				}
			}
			std::cout << "error target!!!" << std::endl;
		}
	}
	else if (creature.Camp == 1) //¼Ä¤H¤è
	{
		int step = 0, minStep = 99, count = 0;
		int userIndex[4] = { 0,0,0,0 };
		for (int j = 0; j < 4; j++)
			userIndex[j] = 0;
		for (i = 0; i < userDeck.size(); i++)
		{
			if (shootRange(creature.P, userDeck[i].P, creature.Range, 1, creature.Range) && viewableRange(userDeck[i].P, creature.P))
			{
				step = getStep(creature.P, userDeck[i].P, 1, creature.Range);
				if (step < minStep)
				{
					for (int j = 0; j < 4; j++)
						userIndex[j] = 0;

					minStep = step;
					userIndex[i] = 1;
					count = 1;
				}
				else if (step == minStep)
				{
					userIndex[i] = 1;
					count += 1;
				}
			}	
		}
		if (count == 1)
		{
			for (int i = 0; i < userDeck.size(); i++)
			{
				if (userIndex[i] == 1)
				{
					if (damage > userDeck[i].Shield)
						userDeck[i].HP -= damage - userDeck[i].Shield;
					std::cout << creature.Icon << " attack " << userDeck[i].Icon << " " << damage << " damage, " << userDeck[i].Icon << " shield " << userDeck[i].Shield
						<< " , " << userDeck[i].Icon << " remain " << userDeck[i].HP << " hp" << std::endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < compairList.size(); i++)
			{
				for (int j = 0; j < userDeck.size(); j++)
				{
					if (compairList[i].Icon == userDeck[j].Icon && userIndex[j] == 1)
					{
						if (damage > userDeck[j].Shield)
							userDeck[j].HP -= damage - userDeck[j].Shield;
						std::cout << creature.Icon << " attack " << userDeck[j].Icon << " " << damage << " damage, " << userDeck[j].Icon << " shield " << userDeck[j].Shield
							<< " , " << userDeck[j].Icon << " remain " << userDeck[j].HP << " hp" << std::endl;
						return;
					}
				}
			}
		}
	}
	resetRange();
}

bool  Management::oneGapCheck(int x, float y1, float y2)
{
	int j;
	for (j = ceil(y1); j != floor(y2); j = j + (floor(y2) - ceil(y1)) / abs(floor(y2) - ceil(y1)))
	{
		if (map[j - 1][x] == '3')
			return true;
	}
	return false;
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
			if (map[i][start.x] == '3')
				return false;
		}	
		if (map[i][start.x] == '3')
			return false;
	}
	return true;
}
int Management::getStep(Point start, Point end, int camp,int maxRange)
{
	std::cout << start.x << " " << start.y << std::endl;
	std::cout << end.x << " " << end.y << std::endl;
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
			if (map[i][j] == '0' || (enemyOnPoint({ j,i }, camp) != 0 && !(end == Point{ j, i })))
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
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			std::cout << checkMap[i][j] << " " ;
		}
		std::cout << std::endl;
	}
	int n = 0;
	while (checkMap[end.y][end.x] <= 0 && n <= maxRange)
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
	if (n > maxRange)
		return maxRange + 1;
	checkMap[start.y][start.x] = 0;
	return checkMap[end.y][end.x];
}
bool Management::shootRange(Point start, Point end, int step, int camp, int maxRange)
{
	int i, j;
	if (map[end.y][end.x] != '1' && map[end.y][end.x] !='3')
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
	while (checkMap[end.y][end.x] <= 0 && n <= maxRange)
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
	if (n > maxRange)
		return false;
	else if (checkMap[end.y][end.x] <= step)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////
//«ô³X¥k°¼ : 
int Management::viewR(Point start, int n)
{
	if (checkMap[start.y][start.x + 1] == -2)
	{
		checkMap[start.y][start.x + 1] = n + 1;
		return viewR({ start.x + 1,start.y }, n + 1);
	}
	else
	return 0;
}
//////////////////////////////////////////////////////////////
//«ô³X¤W¤è : 
int Management::viewU(Point start, int n)
{
	if (checkMap[start.y - 1][start.x] == -2)
	{
		checkMap[start.y - 1][start.x] = n + 1;
		return viewU({ start.x,start.y - 1 }, n + 1);
	}
	else
		return 0;
}
//////////////////////////////////////////////////////////////
//«ô³X¤U¤è : 
int Management::viewD(Point start, int n)
{

	if (checkMap[start.y + 1][start.x] == -2)
	{
		checkMap[start.y + 1][start.x] = n + 1;
		return viewD({ start.x,start.y + 1 }, n + 1);
	}
	else 
		return 0;
}
//////////////////////////////////////////////////////////////
//«ô³X¥ª°¼ : 
int Management::viewL(Point start, int n)
{
	if (checkMap[start.y][start.x - 1] == -2)
	{
		checkMap[start.y][start.x - 1] = n + 1;
		return viewL({ start.x - 1,start.y }, n + 1);
	}
	else
		return 0;
}
//////////////////////////////////////////////////////////////
void  Management::resetShield()
{
	int i, j;
	int position;
	for (i = 0; i < userDeck.size(); i++)
	{
		position = findCreaturePosition(0, userDeck[i].name);
		userDeck[i].Shield = user[position].Shield;
	}
	for (i = 0; i < enemyDeck.size(); i++)
	{
		position = findCreaturePosition(1, enemyDeck[i].name);
		enemyDeck[i].Shield = enemy[position].Shield;
	}
}

void  Management::resetRange()
{
	int i, j;
	int position;
	for (i = 0; i < userDeck.size(); i++)
	{
		position = findCreaturePosition(0, userDeck[i].name);
		userDeck[i].Range = user[position].Range;
	}
	for (i = 0; i < enemyDeck.size(); i++)
	{
		position = findCreaturePosition(1, enemyDeck[i].name);
		enemyDeck[i].Range = enemy[position].Range;
	}
}