#pragma once
#include <vector>
#include <iostream>
#include <windows.h>

struct Point
{
	int x;
	int y;
	Point operator+(Point b);
	bool operator==(Point b);
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

struct Creature
{
	std::string name;
	Point P;
	char Icon;
	int CardOnHand = 6;
};

struct User : public Creature
{
	int HP;
	std::vector < UserCard> Card;
	std::vector < UserCard> disCardDeck;
};

struct Enemy : public Creature
{
	int Type;
	int HP[2];
	int STR[2];
	int Range[2];
	std::vector <EnemyCard> Card;
	std::vector <EnemyCard> disCardDeck;
};

class Management
{
private:
	int width, height;
	std::vector <std::vector<char> > map;
	std::vector <User> user;
	std::vector <Enemy> enemy;
	std::vector <User> userDeck;
	std::vector <Enemy> enemyDeck;
	void gotoxy(Point p);
	void getxy(Point& p);
public:
	void loadUserfile();//c7
	void loadEnemyfile();//c7
	void seletUser();//c7
	void loadMapfile(int n);//Yo
	void runGAME();
	void printMap(Point p);//Yo
	void printEnemy(Point p); //c7
	void printUser(Point p);
	void seletPoint();
	void Move(Creature &creature, std::string command);
	int creatureOnPoint(Point p);
	int getAbilityType(std::string Type);
};
