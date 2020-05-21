#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

void Management::survivalCheck()
{
	int i, j;
	for (i = userDeck.size(); i > 0; i++)
	{
		if (userDeck[i-1].HP <= 0)
		{
			std::cout << userDeck[i].Icon << " is killed!!" << std::endl;
			userDeck.erase(userDeck.begin() + i-1);
			for (j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == userDeck[i - 1].Icon)
				{
					compairList[j].skip = true;
				}
			}
		}
	}
	for (i = enemyDeck.size(); i > 0; i++)
	{
		if (enemyDeck[i - 1].HP <= 0)
		{
			std::cout << enemyDeck[i].Icon << " is killed!!" << std::endl;
			enemyDeck.erase(enemyDeck.begin() + i - 1);
			for (j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == enemyDeck[i - 1].Icon)
					compairList[j].skip = true;
			}
		}
	}
}