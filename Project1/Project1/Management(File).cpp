#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

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
	std::regex form(".+txt$");
	std::cout << "��ܦa�� : " << std::endl;
	while (std::cin >> fileName)
	{
		if (std::regex_match(fileName, form))
		{
			file.open(fileName, std::ios::in);
			if (file.is_open())
				break;
			else
				std::cout << "���s��J�G" << std::endl;
		}
		else
			std::cout << "���s��J�G" << std::endl;
	}
	file >> height >> width;
	map.resize(height);
	for (int i = 0; i < height; i++)
		map[i].resize(width);

	char block;
	for (int i = 0; i < height; i++)
	{
		file.get(block); // �Y������
		for (int j = 0; j < width; j++)
		{
			file.get(block);
			if (block == '0') //�~��
				map[i][j] = '0';
			else if (block == '1') //�i�����ϰ�
				map[i][j] = 'x';
			else if (block == '2') //��ê��
				map[i][j] = 'y';
			else if (block == '3') //��
				map[i][j] = '4';
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
			enemyDeck.erase(enemyDeck.begin() + i);//i����
			count++;
		}
		else if (int_buffer == 1)
		{
			enemyDeck[i].Attack = enemyDeck[i].STR[0];
			enemyDeck[i].Type = 0;
			enemyDeck[i].Range = enemyDeck[i].RGE[enemyDeck[i].Type];
			i++;
		}
		else if (int_buffer == 2)
		{
			enemyDeck[i].Attack = enemyDeck[i].STR[1];
			enemyDeck[i].Type = 1;
			enemyDeck[i].Range = enemyDeck[i].RGE[enemyDeck[i].Type];
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

void Management::loadEnemyfile() //���J�Ǫ����
{
	std::fstream file;
	int enemynum;
	std::string string_buffer;
	int i, j;
	file.open("monster1.txt", std::ios::in); //�}�ҫ��w���Ǫ��ɮ�
	file >> enemynum; //Ū���Ǫ��ƶq
	enemy.resize(enemynum);
	for (i = 0; i < enemynum; i++)
	{
		file >> enemy[i].name;
		for (j = 0; j < 2; j++)
		{
			file >> enemy[i].HP[j];
			file >> enemy[i].STR[j];
			file >> enemy[i].RGE[j];
		}
		enemy[i].Card.resize(6);
		for (j = 0; j < 6; j++)
		{
			file >> string_buffer;
			file >> enemy[i].Card[j].Order;
			file >> enemy[i].Card[j].DEX;
			getline(file, string_buffer);
			if (string_buffer.substr(string_buffer.size() - 1, 1) == "r")
				enemy[i].Card[j].Shuffle = true;
			else if (string_buffer.substr(string_buffer.size() - 1, 1) == "d")
				enemy[i].Card[j].Shuffle = false;
			string_buffer = string_buffer.substr(0, string_buffer.size() - 1);
			std::stringstream lineString(string_buffer);
			while (lineString >> string_buffer)
			{
				enemy[i].Card[j].Type.push_back(getAbilityType(string_buffer));
				lineString >> string_buffer;
				enemy[i].Card[j].AbilityValue.push_back(string_buffer);
			}
		}
	}
	file.close();
}