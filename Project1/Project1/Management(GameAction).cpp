#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Management.h"
#include <regex>
#include <conio.h>
using namespace std;
////////////////////////////////////////////////////////////
//選擇使用角色：
void Management::seletUser()
{
	int int_buffer;
	std::string string_buffer;
	int i, j, k;
	int p1, p2;
	////////////////////////////////////////////////////////////
	//防呆處理：
	std::regex form("^[2-4]{1}$");
	std::string input;
	std::cout << "請輸入出場角色數量:" << std::endl;
	while (getline (cin,input))
	{
		if (std::regex_match(input, form))
			break;
		else
			std::cout << "重新輸入：" << std::endl;
	}
	int_buffer = stoi(input);
	userDeck.resize(int_buffer);
	////////////////////////////////////////////////////////////
	if (debugMode == 0)
	{
		userDeck.clear();
		selectUserGUI(int_buffer);
		return;
	}
	for (i = 0; i < userDeck.size(); i++)
	{
		while (getline(cin,string_buffer))
		{			
			if (string_buffer.size() == 0)
				continue;
			stringstream ss(string_buffer);
			ss >> string_buffer;
			p1 = findCreaturePosition(0, string_buffer);
			if (p1 == -1)
			{
				std::cout << "重新輸入：" << std::endl;
			}
			else
			{
				userDeck[i] = user[p1];
				userDeck[i].Camp = 0;
				userDeck[i].Icon = 65 + i;
				userDeck[i].Card.clear();
				string_buffer = "^";
				for (j = 0; j < userDeck[i].CardOnHand; j++)
						string_buffer = string_buffer + " [0-9]+";
				string_buffer = string_buffer + "$";
				getline(ss, input);
				form = (string_buffer);
				if (!std::regex_match(input, form))
				{
					std::cout << "卡牌數量不合" << std::endl;
					continue;
				}
				else
				{
					stringstream s1(input);
					for (j = 0; j < userDeck[i].CardOnHand; j++)
					{
						s1 >> input;
						int_buffer = stoi(input);
						p2 = -1;
						for (k = 0; k < user[p1].Card.size(); k++)
						{
							if (user[p1].Card[k].Order == int_buffer)
								p2 = k;
						}
						if (p2 == -1)
						{
							std::cout << "卡牌不存在" << std::endl;
							break;
						}
						else
						{
							if (findCardPosition(userDeck[i], int_buffer) == -1)
							{
								userDeck[i].name = user[p1].name;
								userDeck[i].Card.push_back(user[p1].Card[p2]);
							}
							else
							{
								std::cout << "重複的卡牌" << std::endl;
								break;
							}
						}
					}
					if (userDeck[i].Card.size() != userDeck[i].CardOnHand)
						continue;
				}
				break;
			}
		}	
	}
}
////////////////////////////////////////////////////////////
//執行遊戲：
void Management::runGAME()
{
	Point p;
	seletUser();
	loadMapfile();
	if (debugMode == 0)
		system("cls");		
	getxy(p);
	printMap(p);
	printEnemy(p);
	seletPoint();
	resetRange();
	while (!victoryCheck() && userDeck.size() > 0)
	{
		playCard();
		resetShield();
	}
	if (victoryCheck())
		std::cout << "character win~" << std::endl;
	else
		std::cout << "monster win~" << std::endl;
	resetGame();
}
////////////////////////////////////////////////////////////
//選擇起始點：
void Management::seletPoint()
{
	Point p;
	Point tmp;
	int count;
	std::vector <Point> point;
	std::string command;
	std::regex form1("^[wasd]+$");
	std::regex form2("^e$");
	for (int i = 0; i < this->userDeck.size(); i++)
	{
		if(debugMode == 0)
			std::cout << "選擇角色位置：" << std::endl;
		while (getline(cin , command))
		{
			if (std::regex_match(command, form1) || std::regex_match(command, form2))
				break;
			else
				std::cout << "錯誤輸入：" << std::endl;
		}
		point.clear();
		bool haveFind = false;

		for (int j = 0; j < this->height; j++)
		{
			for (int k = 0; k < this->width; k++)
			{
				if (this->map[j][k] == '*')
				{
					tmp.x = k;
					tmp.y = j;
					haveFind = true;
					break;
				}
			}
			if (haveFind)
				break;
		}
		userDeck[i].P = tmp;
		for (int j = 0; j < command.size(); j++)
		{
			if (command[j] == 'w' && (map[tmp.y - 1][tmp.x] == '_' || map[tmp.y - 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y - 1 })
						count++;
				}
				if (count == 0)
					tmp.y--;
			}

			else if (command[j] == 's' && (map[tmp.y + 1][tmp.x] == '_' || map[tmp.y + 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y + 1 })
						count++;
				}
				if (count == 0)
					tmp.y++;
			}
			else if (command[j] == 'a' && (map[tmp.y][tmp.x - 1] == '_' || map[tmp.y][tmp.x - 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x - 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x--;
			}
			else if (command[j] == 'd' && (map[tmp.y][tmp.x + 1] == '_' || map[tmp.y - 1][tmp.x + 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x + 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x++;
			}
			point.push_back(tmp);
		}

		for (int j = point.size(); j > 0; j--)
		{
			count = 0;
			for (int k = 0; k <= i; k++)
			{
				if (userDeck[k].P == point[j - 1])
					count++;
			}
			if (count == 0)
			{
				tmp = point[j - 1];
				break;
			}
		}
		if (userDeck[i].P == tmp)
		{
			haveFind = false;
			map[userDeck[i].P.y][userDeck[i].P.x] = '1';
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '_')
					{
						this->map[j][k] = '*';
						tmp.x = k;
						tmp.y = j;
						haveFind = true;
						break;
					}
				}
				if (haveFind)
					break;
			}
		}
		else
		{
			userDeck[i].P = tmp;
			map[userDeck[i].P.y][userDeck[i].P.x] = '1';
		}
		if (i == userDeck.size() - 1)
		{
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '*' || this->map[j][k] == '_')
						map[j][k] = '1';
				}
			}
		}
		if(debugMode == 0)
			system("cls");
		getxy(p);
		printMap(p);
		printEnemy(p);
		for (int k = 0; k <= i; k++)
		{
			gotoxy(userDeck[k].P + p);
			std::cout << userDeck[k].Icon;
		}
		gotoxy({ p.x,p.y + height });

	}

}
////////////////////////////////////////////////////////////
//執行一輪出牌：
void Management::playCard()
{
	int position;
	int p1;
	int i, j;
	string command;
	CompairCardDex tmp;
	std::regex play("^[0-9]+[ud]{1}$");
	std::regex userCheck("^[A-D]{1} check$");
	std::regex creatureCheck("check");
	char icon;
	// 每輪開始
	roundStatue = "角色出牌階段";
	round_count += 1;
	compairList.clear();
	if (debugMode == 0)
		rePrint();
	else
		std::cout << "round " << round_count << ":" << std::endl;
	// 玩家出牌
	userPlayCards();
	//敵人出牌
	enemyPlayCards();
	//所有牌排序
	sort_compairList();
	//輸出敏捷排序
	printExecutionOrder();
	//依序出牌 
	for (i = 0; i < compairList.size(); i++)
	{		
		if (!compairList[i].skip)
		{
			if (debugMode == 0)
			{
				roundStatue = std::string("生物 ") + compairList[i].Icon + std::string(" 使用技能階段");
				rePrint();
			}			
			if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //主角方
			{				
				position = findCreatureDeckPosition(0, compairList[i].Icon);
				if (compairList[i].Index[0] != -1)
				{
					if (debugMode == 0)
					{
						printUseCardGUI(position);
						continue;
					}										
					else
						std::cout << compairList[i].Icon << "'s turn: card " << compairList[i].Index[0] << " " << compairList[i].Index[1] << std::endl;
					while (getline(cin, command))
					{
						if (std::regex_match(command, creatureCheck)) //顯示所有生物狀態
							printCreatureCheck();
						else if (std::regex_match(command, userCheck) && findCreatureDeckPosition(0, command[0]) != -1) //顯示指定user狀態
							printUserCheck(command[0]);
						else if (std::regex_match(command, play) && compairList[i].cardExist(command[0] - '0')) //選擇卡片
						{
							p1 = findCardPosition(compairList[i], command[0] - '0');
							position = findCreatureDeckPosition(0, compairList[i].Icon);
							if (command[1] == 'd')
							{
								usingEffect(userDeck[position], compairList[i].Index[p1], 1);
								usingEffect(userDeck[position], compairList[i].Index[1 - p1], 0);
							}
							else if (command[1] == 'u')
							{
								usingEffect(userDeck[position], compairList[i].Index[p1], 0);
								usingEffect(userDeck[position], compairList[i].Index[1 - p1], 1);
							}
							break;
						}
						else
						{
							if (command.size() != 0)
								std::cout << "不合規範：" << std::endl;
						}
					}					
				}
				else
				{
					if (debugMode == 1)
						cout << userDeck[position].Icon << "'s turn: card -1" << endl;
					rest(userDeck[position]);
					if (!debugMode)
						rePrint();
				}
			}
			else if (compairList[i].Icon >= 'a' && compairList[i].Icon <= 'z') //敵人方
			{
				position = findCreatureDeckPosition(1, compairList[i].Icon);
				if(debugMode == 0)
					cout << "敵人" << enemyDeck[position].Icon << "出牌" << endl;
				usingEffect(enemyDeck[position], compairList[i].Index[0]);
			}
		}
	}
	// 每輪結束計算
	doorOpenCheck();
}
////////////////////////////////////////////////////////////
//重設遊戲資料
void Management::resetGame()
{
	userDeck.clear();
	enemyDeck.clear();
	compairList.clear();
	map.clear();
	round_count = 0;
	battleMsg.clear();	
	if (debugMode == 0)
	{
		std::cout << "按下任意鍵以繼續" << std::endl;
		_getch();
		system("cls");
	}		
}