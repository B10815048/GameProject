#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

bool  Management::victoryCheck()
{
	int i, j;
	int count = 0;
	if (enemyDeck.size() == 0)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (checkDoor({ j,i }))
					count++;
			}
		}
		if (count==0)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Management::survivalCheck()
{
	int i, j;
	bool check = false;
	Point tmp;
	for (i = userDeck.size(); i > 0; i--)
	{
		if (userDeck[i-1].HP <= 0)
		{
			std::cout << userDeck[i].Icon << " is killed!!" << std::endl;
			check = true;
			for (j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == userDeck[i - 1].Icon)
					compairList[j].skip = true;
			}
			userDeck.erase(userDeck.begin() + i-1);
			
		}
	}
	for (i = enemyDeck.size(); i > 0; i--)
	{
		if (enemyDeck[i - 1].HP[enemyDeck[i-1].Type] <= 0)
		{
			std::cout << enemyDeck[i-1].Icon << " is killed!!" << std::endl;
			check = true;
			for (j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == enemyDeck[i - 1].Icon)
					compairList[j].skip = true;
			}
			enemyDeck.erase(enemyDeck.begin() + i - 1);

		}
	}
	if (check)
	{
		getxy(tmp);
		printMap(tmp);
		printEnemy(tmp);
		printUser(tmp);
	}
}

void Management::doorOpenCheck()
{
	bool haveOpen = false;
	bool haveEnemy = false;
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1' && enemyDeck[i].HP > 0)
			haveEnemy = true;
	}
	if (!haveEnemy)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// 找到所有的門並確認有沒有角色站在上面
				if (map[i][j] == '3')
				{
					for (int k = 0; k < userDeck.size(); k++)
					{
						if (userDeck[k].P.x == j && userDeck[k].P.y == i)
						{
							map[i][j] = 'x';
							haveOpen = true;
							Search(map, j, i);
						}
					}
				}
			}
		}
	}
	if (haveOpen)
	{
		Point p;
		getxy(p);
		printMap(p);
		printEnemy(p);
		printUser(p);
	}
}