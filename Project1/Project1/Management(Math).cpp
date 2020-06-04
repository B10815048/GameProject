#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
////////////////////////////////////////////////////////////
//確認該卡是否存在於使用者：
bool User::cardExist(int index)
{
	int i;
	for (i = 0; i < Card.size(); i++)
	{
		if (Card[i].Order == index)
			return true;
	}
	return false;
}
////////////////////////////////////////////////////////////
//確認該卡是否存在於怪物：
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
////////////////////////////////////////////////////////////
//確認該卡是否存在於出牌中：
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
////////////////////////////////////////////////////////////
//找尋卡牌位置：
int  Management::findCardPosition(CompairCardDex& compairCardDex, int index)
{
	int i;
	for (i = 0; i < compairCardDex.Index.size(); i++)
	{
		if (compairCardDex.Index[i] == index)
			return i;
	}
	return -1;
}
////////////////////////////////////////////////////////////
//確認是否已經出牌：
bool  Management::havePlayed(char icon)
{
	int i;
	for (i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon == icon)
			return true;
	}
	return false;
}
////////////////////////////////////////////////////////////
//找尋生物檔案位置：
int  Management::findCreaturePosition(int camp, std::string name)
{
	int i;
	if (camp == 0)
	{
		for (i = 0; i < user.size(); i++)
		{
			if (user[i].name == name)
				return i;
		}
	}
	else if (camp == 1)
	{
		for (i = 0; i < enemy.size(); i++)
		{
			if (enemy[i].name == name)
				return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////
//找尋遊玩生物位置：
int  Management::findCreatureDeckPosition(int camp, char icon)
{
	int i;
	if (camp == 0)
	{
		for (i = 0; i < userDeck.size(); i++)
		{
			if (userDeck[i].Icon == icon)
				return i;
		}
	}
	else if (camp == 1)
	{
		for (i = 0; i < enemyDeck.size(); i++)
		{
			if (enemyDeck[i].Icon == icon)
				return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////
//找尋卡牌位置：
int Management::findCardPosition(User& user, int index)
{
	int i;
	for (i = 0; i < user.Card.size(); i++)
	{
		if (user.Card[i].Order == index)
			return i;
	}
	return -1;
}
////////////////////////////////////////////////////////////
//找尋卡牌位置：
int Management::findCardPosition(Enemy& enemy, int index)
{
	int i;
	for (i = 0; i < enemy.Card.size(); i++)
	{
		if (enemy.Card[i].Order == index)
			return i;
	}
	return -1;
}
////////////////////////////////////////////////////////////
//取正值結算：
void Management::positiveValue(int& num)
{
	if (num < 0)
		num = 0;
	return;
}
////////////////////////////////////////////////////////////
//回傳技能代號：
int Management::getAbilityType(std::string Type)
{
	if (Type == "move")
		return 0;
	else if (Type == "heal")
		return 1;
	else if (Type == "shield")
		return 2;
	else if (Type == "attack")
		return 3;
	else if (Type == "range")
		return 4;
}
////////////////////////////////////////////////////////////
//Point重載：
Point operator+(Point a,Point b)
{
	Point tmp;
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	return tmp;
}
////////////////////////////////////////////////////////////
//Point重載：
bool Point::operator==(Point b)
{
	return (this->x == b.x && this->y == b.y);
}
////////////////////////////////////////////////////////////
//計算點上生物數量：
int  Management::creatureOnPoint(Point p)
{
	int count;
	count = 0;
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (enemyDeck[i].P == p)
			count++;
	}
	for (int i = 0; i < userDeck.size(); i++)
	{
		if (userDeck[i].P == p)
			count++;
	}
	return count;
}
////////////////////////////////////////////////////////////
//計算點上敵人數量：
int  Management::enemyOnPoint(Point p, int Camp)
{
	int count = 0;
	if (Camp == 0)
	{
		for (int i = 0; i < enemyDeck.size(); i++)
		{
			if (enemyDeck[i].P == p)
				count++;
		}
	}
	else if (Camp == 1)
	{
		for (int i = 0; i < userDeck.size(); i++)
		{
			if (userDeck[i].P == p)
				count++;
		}
	}
	return count;
}
////////////////////////////////////////////////////////////
int Management::findCompairCardDexPosition(char icon)
{
	int i;
	for (i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon == icon)
			return i;
	}
	return -1;
}