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
	for (int i = 0; i < n; i++)
	{
		cout << "Enter postion: ";
		cin >> x >> y;
		CharaterPos.push_back({ x,y });
	}
	char block;
	for (int i = 0; i < height; i++)
	{	
		for (int j = 0; j < width; j++)
		{
			file.get(block);
			if (block == '0')
				this->map[i][j] = '0';
			else if (block == '1')
				this->map[i][j] = '1';
			else if (block == '3')
				this->map[i][j] = '3';
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << this->map[i][j];
		}
		cout << endl;
	}
}