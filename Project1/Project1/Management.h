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
};

class Management
{
private:
	//////////////////////////////////////////////////////////////////////
	int width, height;
	std::vector <std::vector<char> > map;
	std::vector <std::vector<int> >checkMap;
	std::vector <User> user; // 弄郎计
	std::vector <Enemy> enemy;
	std::vector <User> userDeck; // 初计
	std::vector <Enemy> enemyDeck;
	std::vector<CompairCardDex> compairList;
	void gotoxy(Point p);
	void getxy(Point& p);
public:
	//////////////////////////////////////////////////////////////////////
	//print : 
	void printMap(Point p);//Yo
	void printEnemy(Point p); //c7
	void printUser(Point p);
	//////////////////////////////////////////////////////////////////////
	//loadFile : 
	void loadUserfile();//c7
	void loadEnemyfile();//c7
	void loadMapfile();//Yo
	//////////////////////////////////////////////////////////////////////
	//Attack:
	void Attack(Creature& creature, std::string command); // Τrange return 1; 礚range return 0
	void Range(User& user, std::string command);
	void Range(Enemy& enemy, std::string command);
	void resetRange();
	void resetShield();
	bool viewableRange(Point start, Point end);
	bool oneGapCheck(int x, float y1, float y2);
	bool shootRange(Point start, Point end, int n,int camp, int maxRange);
	int getStep(Point start, Point end, int camp,int maxRange);
	int viewR(Point start,int n);
	int viewU(Point start, int n);
	int viewD(Point start, int n);
	int viewL(Point start, int n);
	//////////////////////////////////////////////////////////////////////
	void rest(User& user);
	//////////////////////////////////////////////////////////////////////
	void setMove(User& user, int step);
	bool Move(Creature &creature,std::string command);
	void Heal(User& user, std::string command);
	void Heal(Enemy& enemy, std::string command);
	void Shield(Creature& creature, std::string command);
	//////////////////////////////////////////////////////////////////////
	//gameAction : 
	void runGAME();
	void seletUser();//c7
	void seletPoint();
	void playCard();
	void userPlayCards();
	void enemyPlayCards();
	void sort_compairList();
	void usingEffect(User& user,int index, int part); //part 0:礟场part 1:礟场
	void usingEffect(Enemy& enemy, int index);
	//////////////////////////////////////////////////////////////////////
	//playCard : 
	bool cardExist(User& user, int index);
	bool cardExist(Enemy& enemy, int index);
	bool cardExist(CompairCardDex& compairCardDex, int index);
	bool creatureExist(char icon);
	//template < typename T>
	//bool inputCheck(T, string type, int base, int top , int n);
	bool victoryCheck();
	void survivalCheck();
	void doorOpenCheck();
	char Search(std::vector<std::vector<char> >& map, int x, int y);
	//////////////////////////////////////////////////////////////////////
	bool checkSpace(Point p);
	bool checkDoor(Point p);
	int creatureOnPoint(Point p);
	int enemyOnPoint(Point p,int Camp);
	int getAbilityType(std::string Type);
	int findCreaturePosition(int camp, std::string name);
	int findCardPosition(User& user, int index);
	int findCardPosition(Enemy& enemy, int index);
	int findCreatureDeckPosition(int camp, char icon);
};

