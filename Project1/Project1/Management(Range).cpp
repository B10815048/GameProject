#include "Management.h"
#include <cmath>
#include <string>
////////////////////////////////////////////////////////////
//Range���[�G
void  Management::Range(Creature& creature, std::string command)
{
	creature.Range = creature.Range + stoi(command);
}
////////////////////////////////////////////////////////////
//�����T�{�G
bool  Management::oneGapCheck(int x, float y1, float y2)
{
	int j;
	float tmp;
	if (y2 < y1) //��y2�û��j��y1
	{
		tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	if (floor(y1) == ceil(y2)) //��y1=y2�ɰ��Ӯ�T�{
	{
		if (map[floor(y1)][x] == '0')
			return true;
	}
	for (j = floor(y1); j != ceil(y2); j = j + (ceil(y2) - floor(y1)) / abs(ceil(y2) - floor(y1))) //��y1�¦Vy2�T�{
	{
		if (map[j][x] == '0')
			return true;
	}
	return false; //�d�򤺬ҨS���ɦ^��
}
////////////////////////////////////////////////////////////
//�����T�{�G
bool Management::viewableRange(Point start, Point end)
{
	int i;
	float a, gap;
	if (start.x != end.x)
	{
		a = (float)(end.y - start.y) / abs(end.x - start.x);
		gap = 0.5 + start.y;
		if (oneGapCheck(start.x, gap + (a / 2), gap))
			return false;
		gap = gap + (a / 2);
		i = start.x;
		while (i != end.x - (end.x - start.x) / abs(end.x - start.x)) //�ϰ_�Ix�����Ix����
		{
			if (oneGapCheck(i + (end.x - start.x) / abs(end.x - start.x), gap + a, gap)) //�v�檺�����T�{
				return false;
			i = i + (end.x - start.x) / abs(end.x - start.x);
			gap = a + gap; 
		}
		if (oneGapCheck(end.x, gap + (a / 2), gap))
			return false;
	}
	else
	{
		for (i = start.y; i != end.y; i = i + (end.y - start.y) / abs(end.y - start.y)) //��̫����ɶi��T�{
		{
			if (oneGapCheck(end.x, i, i))
				return false;
		}
		if (oneGapCheck(end.x, i, i))
			return false;
	}
	return true; //�d�򤺬ҨS���ɫh�^�ǥi���T�{
}
////////////////////////////////////////////////////////////
//�g�{�B�ơG
int Management::shootRange(Point start, Point end, int maxRange)
{
	/*return abs(end.x- start.x)+ abs(end.y-start.y);*/
	int i, j;
	checkMap.resize(height);
	for (i = 0; i < checkMap.size(); i++)
		checkMap[i].resize(width);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == '0')
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
	if (n > maxRange)
		return maxRange + 1;
	return checkMap[end.y][end.x];
}
////////////////////////////////////////////////////////////
//�٭�Ҧ��H���g�{
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
		enemyDeck[i].Range = enemy[position].RGE[enemy[position].Type];
	}
}
////////////////////////////////////////////////////////////
//���X�k�� : 
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
//���X�W�� : 
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
//���X�U�� : 
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
//���X���� : 
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