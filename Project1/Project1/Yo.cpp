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


void Management::loadMapfile(int n)
{
	vector<Position> CharaterPos;
	int x, y;
	int width, height;
	fstream file;
	file.open("map1.txt", ios::in);
	file >> height >> width;
	this->map.resize(height);
	for (int i = 0; i < height; i++)
		this->map[i].resize(width);

	char block;
	for (int i = 0; i < height; i++)
	{
		file.get(block); // 吃掉換行
		for (int j = 0; j < width; j++)
		{
			file.get(block);
			if (block == '0')
				this->map[i][j] = '0';
			else if (block == '1')
				this->map[i][j] = 'x';
			else if (block == '2')
				this->map[i][j] = '2';
			else if (block == '3')
				this->map[i][j] = '3';
		}
	}

	for (int i = 0; i < 4; i++)
	{
		file >> x >> y;
		CharaterPos.push_back({ x,y });
	}

	string name;
	int count = 0;
	int enemyCount;
	int level[3];
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

	char C = Search(this->map, CharaterPos[0].x, CharaterPos[0].y);
	/*for (int i = 0; i <userDeck.size(); i++)
	{
		this->map[userDeck[i].P.y][userDeck[i].P.x] = userDeck[i].Icon;
	}*/
	this->width = width;
	this->height = height;	
}


void Management::printMap()
{
	Position p;
	getxy(p);
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->map[i][j] == '0' || this->map[i][j] == 'x')
				cout << " ";
			else
				cout << this->map[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1')
		{
			
			gotoxy({ p.x + enemyDeck[i].P.x,p.y + enemyDeck[i].P.y });
			cout << enemyDeck[i].Icon;
		}
	}
	gotoxy({ p.x + width,p.y + height });
	cout << endl;
}