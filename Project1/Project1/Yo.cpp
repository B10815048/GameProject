#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"
using namespace std;

struct Position
{
	int x;
	int y;
};

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
	for (int i = 0; i < n; i++)
	{
		file >> x >> y;
		CharaterPos.push_back({ x,y });
	}

	string name;
	int enemyCount;
	int level[3];
	file >> enemyCount;
	for (int i = 0; i < enemyCount; i++)
	{
		file >> name >> x >> y >> level[0] >> level[1] >> level[2];
		if (level[n - 2] == 0)
			continue;
		// 建構怪物 type = n - 2
	}

	char C = Search(this->map, CharaterPos[1].x, CharaterPos[1].y);
	char c[4] = { 'A','B','C','D' };
	for (int i = 0; i < CharaterPos.size(); i++)
	{
		this->map[CharaterPos[i].y][CharaterPos[i].x] = c[i];
	}
	this->width = width;
	this->height = height;	
}


void Management::printMap()
{
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
}