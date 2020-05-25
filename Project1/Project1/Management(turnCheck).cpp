#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
////////////////////////////////////////////////////////////
//�ӧQ�T�{�G
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
				if (checkDoor({ j,i })) //�T�{���W���S����
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
////////////////////////////////////////////////////////////
//�T�{�Ӧ^�X���L�ͪ����`�G
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
	if (check) //���ͪ����`�ɫh���s���L�a��
	{
		getxy(tmp);
		printMap(tmp);
		printEnemy(tmp);
		printUser(tmp);
	}
}
////////////////////////////////////////////////////////////
//�T�{�Ӧ^�X���L�ͪ����`�G
void Management::doorOpenCheck()
{
	bool haveOpen = false;
	bool haveEnemy = false;
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1')
			haveEnemy = true;
	}
	if (!haveEnemy)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// ���Ҧ������ýT�{���S�����⯸�b�W��
				if (map[i][j] == '3')
				{
					for (int k = 0; k < userDeck.size(); k++)
					{
						if (userDeck[k].P == Point{j,i})
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
////////////////////////////////////////////////////////////
//�j�M�a�ϥi���ϰ�G
char Management::Search(std::vector<std::vector<char> >& map, int x, int y)
{
	if (map[y][x] != 'x' || map[y][x] == 'y' || map[y][x] == '4')
	{
		if (map[y][x] == '4')
			map[y][x] = '3';
		else if (map[y][x] == 'y')
			map[y][x] = '2';
		return 'x';
	}
	else
		map[y][x] = '1';
	if (Search(map, x + 1, y) != 'x' || Search(map, x - 1, y) != 'x' || Search(map, x, y + 1) != 'x' || Search(map, x, y - 1) != 'x')
		return 'x';
}
////////////////////////////////////////////////////////////
