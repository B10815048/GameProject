#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

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
			for (j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == userDeck[i - 1].Icon)
					compairList[j].skip = true;
			}
			userDeck.erase(userDeck.begin() + i-1);
			check = true;
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