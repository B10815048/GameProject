#pragma once
#include <vector>
#include <iostream>

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
	char Icon;
	int HP;
	int CardOnHand;
	std::vector < UserCard> Card;
};

struct Enemy
{
	std::string name;
	char Icon;
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
public:
	void loadUserfile();//c7
	void loadEnemyfile();//c7
	void seletUser();//c7
	void loadMapfile(int n);//Yo
	void runGAME();
	void printMap();//Yo
	int getAbilityType(std::string Type);

};
