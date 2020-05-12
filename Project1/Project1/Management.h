#pragma once
#include <vector>
#include <iostream>
#include <windows.h>

struct Position
{
	int x;
	int y;
};


struct CardTable
{
	int Order;
	int DEX;
};

struct UserCard : public CardTable
{
	std::vector <int> TopType;
	std::vector <std::string> TopAbilityValue;
	std::vector <int> BelowType;
	std::vector <std::string> BelowAbilityValue;
};

struct EnemyCard : public CardTable
{
	std::vector <int> Type;
	std::vector <std::string> AbilityValue;
	bool Shuffle;
};

struct User
{
	std::string name;
	Position P;
	char Icon;
	int HP;
	int CardOnHand;
	std::vector < UserCard> Card;
};

struct Enemy
{
	std::string name;
	char Icon;
	Position P;
	int Type;
	int HP[2];
	int STR[2];
	int Range[2];
	int CardOnHand = 6;
	std::vector <EnemyCard> Card;
};

class Management
{
private:
	int width, height;
	std::vector <User> user;
	std::vector <Enemy> enemy;
	std::vector <User> userDeck;
	std::vector <Enemy> enemyDeck;
	std::vector <std::vector<char> > map;
	void gotoxy(Position p)
	{
		COORD point;
		point.X = p.x, point.Y = p.y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	};
	void getxy(Position& p)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		p.x = csbi.dwCursorPosition.X;
		p.y = csbi.dwCursorPosition.Y;
	};
public:
	void loadUserfile();//c7
	void loadEnemyfile();//c7
	void seletUser();//c7
	void loadMapfile(int n);//Yo
	void runGAME();
	void printMap();//Yo
	int getAbilityType(std::string Type);

};
