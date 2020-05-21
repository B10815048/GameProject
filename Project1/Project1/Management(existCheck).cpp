#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>

bool User:: cardExist(int index)
{
	int i;
	for (i = 0; i < Card.size(); i++)
	{
		if (Card[i].Order == index)
			return true;
	}
	return false;
}

bool Enemy::cardExist(int index)
{
	int i;
	for (i = 0; i < Card.size(); i++)
	{
		if (Card[i].Order == index)
			return true;
	}
	return false;
}

bool CompairCardDex::cardExist(int index)
{
	int i;
	for (i = 0; i < Index.size(); i++)
	{
		if (Index[i] == index)
			return true;
	}
	return false;
}

bool Management::userExist(char icon)
{
	int i;
	if (findCreatureDeckPosition(0, icon) == -1)
		return false;
	else
		return true;
}

bool Management::enemyExist(char icon)
{
	int i;
	if (findCreatureDeckPosition(1, icon) == -1)
		return false;
	else
		return true;
}