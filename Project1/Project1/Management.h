 #pragma once
#include <vector>
#include <iostream>
#include <windows.h>

struct CompairCardDex
{
	bool skip = false;
	char Icon;
	int Dex[2];
	std::vector <int> Index;
	bool cardExist(int index);
};

struct Point
{
	int x;
	int y;
	friend Point operator+(Point a,Point b);
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

struct Creature
{
	std::string name;
	int Camp;  //0ㄏノ 1寄
	Point P;
	char Icon;
	int CardOnHand = 6;
	int Shield = 0;
	int Range = 0;
	int Attack = 0;
};

struct User : public Creature
{
	int HP;
	std::vector < UserCard> Card;
	std::vector < UserCard> disCardDeck;
	bool cardExist(int index);
};

struct EnemyCard : public CardTable
{
	std::vector <int> Type;
	std::vector <std::string> AbilityValue;
	bool Shuffle;
};

struct Enemy : public Creature
{
	int Type;
	int HP[2];
	int STR[2];
	int RGE[2];
	std::vector <EnemyCard> Card;
	std::vector <EnemyCard> disCardDeck;
	bool cardExist(int index);
};

class Management
{
private:
	//////////////////////////////////////////////////////////////////////
	int round_count = 0;
	int width, height;
	std::vector <std::vector<char> > map;
	std::vector <std::vector<int> >checkMap;
	std::vector <User> user; // 弄郎计
	std::vector <Enemy> enemy;
	std::vector <User> userDeck; // 初计
	std::vector <Enemy> enemyDeck;
	std::vector<CompairCardDex> compairList;
public:
	//////////////////////////////////////////////////////////////////////
	//Range:
	bool viewableRange(Point start, Point end);
	bool oneGapCheck(int x, float y1, float y2);
	void Range(Creature& creature, std::string command);
	int shootRange(Point start, Point end, int camp, int maxRange);
	bool canViewed(Point p);
	void viewR(Point start, int n);
	void viewU(Point start, int n);
	void viewD(Point start, int n);
	void viewL(Point start, int n);
	void resetRange();
	//////////////////////////////////////////////////////////////////////
	//Attack:
	void Attack(Creature& creature, std::string command);
	//////////////////////////////////////////////////////////////////////
	//print :
	void gotoxy(Point p);
	void getxy(Point& p);
	void printMap(Point p);
	void printEnemy(Point p);
	void printUser(Point p);
	void printCreatureCheck();
	void printUserCheck(char icon);
	//////////////////////////////////////////////////////////////////////
	//File : 
	void loadUserfile();
	void loadEnemyfile();
	void loadMapfile();
	//////////////////////////////////////////////////////////////////////
	//Heal_Shield_rest
	void Shield(Creature& creature, std::string command);
	void rest(User& user);
	void resetShield();
	void Heal(User& user, std::string command);
	void Heal(Enemy& enemy, std::string command);
	//////////////////////////////////////////////////////////////////////
	//Move
	void setMove(User& user, int step);
	bool Move(Creature &creature,std::string command);
	bool checkSpace(Point p);
	bool checkDoor(Point p);
	//////////////////////////////////////////////////////////////////////
	//playCard : 
	void userPlayCards();
	void enemyPlayCards();

	//////////////////////////////////////////////////////////////////////
	//gameAction : 
	void runGAME();
	void seletUser();
	void seletPoint();
	void playCard();
	void sort_compairList();
	void sort_card(int index);
	void sort_discard(int index);
	void usingEffect(User& user,int index, int part); //part 0:礟场part 1:礟场
	void usingEffect(Enemy& enemy, int index);
	//////////////////////////////////////////////////////////////////////
	//cardExecution : 
	bool userExist(char icon);
	bool enemyExist(char icon);
	bool victoryCheck();
	void survivalCheck();
	void doorOpenCheck();
	char Search(std::vector<std::vector<char> >& map, int x, int y);
	//////////////////////////////////////////////////////////////////////
	bool havePlayed(char icon);
	int creatureOnPoint(Point p);
	int enemyOnPoint(Point p,int Camp);
	int getAbilityType(std::string Type);
	int findCreaturePosition(int camp, std::string name);
	int findCardPosition(User& user, int index);
	int findCardPosition(Enemy& enemy, int index);
	int findCardPosition(CompairCardDex& compairCardDex, int index);
	int findCreatureDeckPosition(int camp, char icon);
	void positiveValue(int& num);
};

