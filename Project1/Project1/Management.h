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
	std::string roundStatue = "";
	std::vector<std::string> battleMsg; 
	int round_count = 0;
	int width, height;
	bool debugMode = false;
	std::vector <std::vector<char> > map;
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
	int shootRange(Point start, Point end);
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
	void printExecutionOrder();
	void printUserCard(User user);
	//////////////////////////////////////////////////////////////////////
	//File : 
	void loadUserfile(std::string fileName);
	void loadEnemyfile(std::string fileName);
	void loadMapfile();
	void setDebugMode(bool input);
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
	void sort_Enemycard();
	void sort_Usercard(int index);
	void sort_compairList();
	void sort_discard(int index);
	//////////////////////////////////////////////////////////////////////
	//cardExecution : 
	void usingEffect(User& user, int index, int part); //礟场part=0礟场part=1
	void usingEffect(Enemy& enemy, int index);
	//////////////////////////////////////////////////////////////////////
	//gameAction : 
	void resetGame();
	void runGAME();
	void seletUser();
	void seletPoint();
	void playCard();
	//////////////////////////////////////////////////////////////////////
	//turnCheck : 
	void survivalCheck();
	void doorOpenCheck();
	bool victoryCheck();
	char Search(std::vector<std::vector<char> >& map, int x, int y);
	//////////////////////////////////////////////////////////////////////
	//math : 
	bool havePlayed(char icon);
	int creatureOnPoint(Point p);
	int enemyOnPoint(Point p,int Camp);
	int getAbilityType(std::string Type);
	int findCreaturePosition(int camp, std::string name);
	int findCardPosition(User& user, int index);
	int findCardPosition(Enemy& enemy, int index);
	int findCardPosition(CompairCardDex& compairCardDex, int index);
	int findCreatureDeckPosition(int camp, char icon);
	int findCompairCardDexPosition(char icon);
	void positiveValue(int& num);
	//////////////////////////////////////////////////////////////////////
	//debugmode :
	void rePrint();
	void printBattleMsg();
	void addBattleMsg(std::string msg);
	void printGUI(int position);
};

