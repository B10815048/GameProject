#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

char Search(std::vector<std::vector<char> >& map, int x, int y)
{
	if (map[y][x] != 'x' || map[y][x] == '3')
		return 'x';
	else
		map[y][x] = '1';
	if (Search(map, x + 1, y) != 'x' || Search(map, x - 1, y) != 'x' || Search(map, x, y + 1) != 'x' || Search(map, x, y - 1) != 'x')
		return 'x';
}

void Management::loadUserfile()
{
	std::fstream file;
	int position;
	int usernum, cardnum;
	int int_buffer;
	std::string string_buffer, topbuffer, belowbuffer;
	int i, j, k, l;
	file.open("character1.txt", std::ios::in);
	file >> usernum;
	user.resize(usernum);
	for (i = 0; i < usernum; i++)
	{
		file >> user[i].name;
		file >> user[i].HP;
		file >> user[i].CardOnHand;
		file >> cardnum;
		user[i].Card.resize(cardnum);
		for (j = 0; j < cardnum; j++)
		{
			file >> user[i].Card[j].Order;
			file >> user[i].Card[j].DEX;
			getline(file, string_buffer);
			for (k = 0; k < string_buffer.size(); k++)
			{
				if (string_buffer[k] == '-')
				{
					topbuffer = string_buffer.substr(0, k);
					belowbuffer = string_buffer.substr(k + 1, string_buffer.size() - k);
					break;
				}
			}
			std::stringstream topString(topbuffer);
			std::stringstream belowString(belowbuffer);
			while (topString >> string_buffer)
			{
				user[i].Card[j].TopType.push_back(getAbilityType(string_buffer));
				topString >> string_buffer;
				user[i].Card[j].TopAbilityValue.push_back(string_buffer);
			}
			while (belowString >> string_buffer)
			{
				user[i].Card[j].BelowType.push_back(getAbilityType(string_buffer));
				belowString >> string_buffer;
				user[i].Card[j].BelowAbilityValue.push_back(string_buffer);
			}
		}
	}
}

void Management::loadMapfile()
{
	std::vector <Point> CharaterPos;
	int width, height;
	std::fstream file;
	std::string fileName;
	int count = 0;
	int enemyCount;
	std::cout << "選擇地圖 : " << std::endl;
	std::cin >> fileName;
	file.open(fileName, std::ios::in);
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
	CharaterPos.resize(4);
	for (int i = 0; i < 4; i++)
		file >> CharaterPos[i].x >> CharaterPos[i].y;

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
		file >> enemyDeck[i].P.x >> enemyDeck[i].P.y;
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

	Search(map, CharaterPos[0].x, CharaterPos[0].y);
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