#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
////////////////////////////////////////////////////////////
//�T�{�ӥd�O�_�s�b��ϥΪ̡G
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
//�T�{�ӥd�O�_�s�b��Ǫ��G
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
//�T�{�ӥd�O�_�s�b��X�P���G
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
//��M�d�P��m�G
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
//�T�{�O�_�w�g�X�P�G
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
//��M�ͪ��ɮצ�m�G
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
//��M�C���ͪ���m�G
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
//��M�d�P��m�G
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
//��M�d�P��m�G
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
//�����ȵ���G
void Management::positiveValue(int& num)
{
	if (num < 0)
		num = 0;
	return;
}
////////////////////////////////////////////////////////////
//�^�ǧޯ�N���G
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
//Point�����G
Point operator+(Point a,Point b)
{
	Point tmp;
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	return tmp;
}
////////////////////////////////////////////////////////////
//Point�����G
bool Point::operator==(Point b)
{
	return (this->x == b.x && this->y == b.y);
}
////////////////////////////////////////////////////////////
//�p���I�W�ͪ��ƶq�G
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
//�p���I�W�ĤH�ƶq�G
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