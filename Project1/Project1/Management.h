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
};

struct User
{
	std::string name;
	int HP;
	int CardOnHand;
	std::vector < UserCard> Card;
};

struct Enemy
{
	std::string name;
	int Type;
	int HP[2];
	int STR[2];
	int Range[2];
	int CardOnHand = 7;
	bool Shuffle;
	std::vector <EnemyCard> Card;
};

class Management
{
private:
	std::vector <User> user;
	std::vector <Enemy> enemy;
public:
	void loadUserfile();
	int getAbilityType(std::string Type);
};