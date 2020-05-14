#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"
using namespace std;

char Search(vector<vector<char> >& map, int x, int y)
{
	if (map[y][x] != 'x' || map[y][x] == '3')
		return 'x';
	else
		map[y][x] = '1';

	if (Search(map, x + 1, y) != 'x' || Search(map, x - 1, y) != 'x' || Search(map, x, y + 1) != 'x' || Search(map, x, y - 1) != 'x')
		return 'x';
}

void Management::loadMapfile()
{
	vector<Point> CharaterPos;
	int x, y;
	int width, height;
	fstream file;
	string fileName;
	int count = 0;
	int enemyCount;
	cout << "選擇地圖 : " << endl;
	cin >> fileName;
	file.open(fileName, ios::in);
	file >> height >> width;
	map.resize(height);
	for (int i = 0; i < height; i++)
		map[i].resize(width);

	char block;
	for (int i = 0; i < height; i++)
	{
		file.get(block); // 吃掉換行
		for (int j = 0; j < width; j++)
		{
			file.get(block);
			if (block == '0') //外側
				map[i][j] = '0';
			else if (block == '1') //可走的區域
				map[i][j] = 'x';
			else if (block == '2') //障礙物
				map[i][j] = '2';
			else if (block == '3') //門
				map[i][j] = '3';
		}
	}

	for (int i = 0; i < 4; i++)
	{
		file >> x >> y;
		CharaterPos.push_back({ x,y });
	}

	file >> enemyCount;
	enemyDeck.resize(enemyCount);
	for (int i = 0; i < enemyDeck.size(); i)
	{
		
		int int_buffer;
		std::string string_buffer;
		int j;
		int position;
		file >> string_buffer;
		for (j = 0; j < enemy.size(); j++)
		{
			if (enemy[j].name == string_buffer)
			{
				enemyDeck[i] = enemy[j];
				position = j;
			}
		}
		enemyDeck[i].Icon = 97 + i + count;
		file >> x >> y; //x and y
		enemyDeck[i].P = { x,y };
		for (j = 1; j < userDeck.size(); j++)
			file >> int_buffer;
		if (int_buffer == 0)
		{
			enemyDeck.erase(enemyDeck.begin() + i);//i不變
			count++;
		}
		else if (int_buffer == 1)
		{
			enemyDeck[i].Type = 0;			
			i++;
		}
		else if (int_buffer == 2)
		{
			enemyDeck[i].Type = 1;			
			i++;
		}
		for (j = userDeck.size(); j < 4; j++)
			file >> int_buffer;
		
	}

	char C = Search(map, CharaterPos[0].x, CharaterPos[0].y);
	for (int i = 0; i < CharaterPos.size(); i++)
	{
		this->map[CharaterPos[i].y][CharaterPos[i].x] = '_';
	}
	bool haveFind = false;
	this->width = width;
	this->height = height;	
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->map[i][j] == '_')
			{
				this->map[i][j] = '*';
				haveFind = true;
				break;
			}
		}
		if (haveFind)
			break;
	}
	file.close();
}


void Management::printMap(Point p)
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (map[i][j] == '0' || map[i][j] == 'x')
				cout << " ";
			else
				cout << map[i][j];
		}
		cout << endl;
	}
}

void Management::seletPoint()
{
	Point p;
	Point tmp;
	
	int count;
	std::vector <Point> point;
	string command;
	
	for (int i = 0; i < this->userDeck.size(); i++)
	{
		cout << "選擇角色位置: " << endl;
		cin >> command;
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
				if (count==0)
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
			else if (command[j] == 'a' && (map[tmp.y][tmp.x - 1] == '_' || map[tmp.y][tmp.x-1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x-1, tmp.y })
						count++;
				}
				if (count == 0)
				tmp.x--;
			}
			else if (command[j] == 'd' && (map[tmp.y][tmp.x + 1] == '_' || map[tmp.y - 1][tmp.x+1] == '*'))
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
			else
				break;
			point.push_back(tmp);
		}
		
		for (int j = point.size(); j >0; j--)
		{
			count = 0;
			for (int k = 0; k <= i; k++)
			{
				if (userDeck[k].P == point[j-1])
					count++;
			}
			if (count == 0)
			{
				tmp = point[j-1];
				break;
			}	
		}
		cout << userDeck[0].P.y << endl;
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
			cout << userDeck[0].P.y << endl;
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
		for (int k = 0; k <= i; k++)
		{
			gotoxy(userDeck[k].P + p);
			cout << userDeck[k].Icon;
		}
		gotoxy({ p.x,p.y + height });

	}

}