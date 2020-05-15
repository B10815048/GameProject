#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"

void Management::seletPoint()
{
	Point p;
	Point tmp;
	int count;
	std::vector <Point> point;
	std::string command;

	for (int i = 0; i < this->userDeck.size(); i++)
	{
		std::cout << "¿ï¾Ü¨¤¦â¦ì¸m: " << std::endl;
		std::cin >> command;
		point.clear();
		bool haveFind = false;

		for (int j = 0; j < this->height; j++)
		{
			for (int k = 0; k < this->width; k++)
			{
				if (this->map[j][k] == '*')
				{
					tmp.x = k;
					tmp.y = j;
					haveFind = true;
					break;
				}
			}
			if (haveFind)
				break;
		}
		userDeck[i].P = tmp;
		for (int j = 0; j < command.size(); j++)
		{
			if (command[j] == 'w' && (map[tmp.y - 1][tmp.x] == '_' || map[tmp.y - 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y - 1 })
						count++;
				}
				if (count == 0)
					tmp.y--;
			}

			else if (command[j] == 's' && (map[tmp.y + 1][tmp.x] == '_' || map[tmp.y + 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y + 1 })
						count++;
				}
				if (count == 0)
					tmp.y++;
			}
			else if (command[j] == 'a' && (map[tmp.y][tmp.x - 1] == '_' || map[tmp.y][tmp.x - 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x - 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x--;
			}
			else if (command[j] == 'd' && (map[tmp.y][tmp.x + 1] == '_' || map[tmp.y - 1][tmp.x + 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x + 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x++;
			}
			point.push_back(tmp);
		}

		for (int j = point.size(); j > 0; j--)
		{
			count = 0;
			for (int k = 0; k <= i; k++)
			{
				if (userDeck[k].P == point[j - 1])
					count++;
			}
			if (count == 0)
			{
				tmp = point[j - 1];
				break;
			}
		}
		if (userDeck[i].P == tmp)
		{
			haveFind = false;
			map[tmp.y][tmp.x] = '1';
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '_')
					{
						this->map[j][k] = '*';
						tmp.x = k;
						tmp.y = j;
						haveFind = true;
						break;
					}
				}
				if (haveFind)
					break;
			}
		}
		else
		{
			userDeck[i].P = tmp;
		}
		if (i == userDeck.size() - 1)
		{
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '*' || this->map[j][k] == '_')
						map[j][k] = '1';
				}
			}
		}
		getxy(p);
		printMap(p);
		printEnemy(p);
		for (int k = 0; k <= i; k++)
		{
			gotoxy(userDeck[k].P + p);
			std::cout << userDeck[k].Icon;
		}
		gotoxy({ p.x,p.y + height });

	}

}