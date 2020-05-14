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
		enemyDeck[i].Camp = 1;
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
	/*for (int i = 0; i <userDeck.size(); i++)
	{
		this->map[userDeck[i].P.y][userDeck[i].P.x] = userDeck[i].Icon;
	}*/
	this->width = width;
	this->height = height;	
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