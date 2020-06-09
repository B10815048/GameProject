#include <iostream>
#include <vector>
#include <string>
#include "Management.h"
#include <sstream>
#include <regex>
#include <conio.h>
using namespace std;
////////////////////////////////////////////////////////////
//使用者出牌：
void Management::userPlayCards()
{
	int position;
	int i, j, index, index1, index2;
	int p2;
	CompairCardDex tmp;
	char icon;
	string input;
	std::regex play("^[A-D]{1} [0-9]+ [0-9]+$");
	std::regex userCheck("^[A-D]{1} check$");
	std::regex creatureCheck("check");
	std::regex rest("^[A-D]{1} \-1$");
	for (int i = 0; i < userDeck.size(); i++) // 檢查角色是否不能選擇長休或出牌
	{
		if (userDeck[i].Card.size() < 2 && userDeck[i].disCardDeck.size() < 2)
		{
			std::cout << userDeck[i].Icon << " is killed!!" << std::endl;		
			if (debugMode == 0)
			{
				addBattleMsg(std::string("角色 ") + userDeck[i].Icon + std::string(" 死亡"));
				userDeck.erase(userDeck.begin() + i);
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
				i--;
				continue;
			}	
			userDeck.erase(userDeck.begin() + i);
			Point p;
			getxy(p);
			printMap(p);
			printEnemy(p);
			printUser(p);
			i--;
			continue;
		}
	}	
	for (int i = 0; i < userDeck.size(); i++)
	{
		if (debugMode == 0)
		{
			printRoundGUI();
			continue;
		}
		while (getline(cin,input))
		{
			if (std::regex_match(input, creatureCheck)) //顯示所有生物狀態
				printCreatureCheck();
			else if (std::regex_match(input, userCheck) && findCreatureDeckPosition(0, input[0]) != -1) //顯示指定user狀態
				printUserCheck(input[0]);
			else if (std::regex_match(input, play) && findCreatureDeckPosition(0, input[0])!=-1)
			{
				position = findCreatureDeckPosition(0, input[0]);
				if (havePlayed(userDeck[position].Icon))
				{
					std::cout << "不合規範：" << std::endl;
					continue;
				}
				if (userDeck[position].Card.size() < 2)
				{
					std::cout << "手牌張數小於2,請選擇長休" << std::endl;
					continue;
				}
				tmp.Index.clear();
				tmp.Icon = userDeck[position].Icon;
				stringstream ss(input);
				ss >> input;
				ss >> index1;
				ss >> index2;
				if (index2 == index1)
				{
					std::cout << "不合規範：" << std::endl;
					continue;
				}
				else if (findCardPosition(userDeck[position], index1) == -1 || findCardPosition(userDeck[position], index2) == -1)
				{
					std::cout << "不合規範：" << std::endl;
					continue;
				}
				p2 = findCardPosition(userDeck[position], index1);
				tmp.Index.push_back(userDeck[position].Card[p2].Order);
				tmp.Dex[0] = userDeck[position].Card[p2].DEX;
				p2 = findCardPosition(userDeck[position], index2);
				tmp.Index.push_back(userDeck[position].Card[p2].Order);
				tmp.Dex[1] = userDeck[position].Card[p2].DEX;
				compairList.push_back(tmp);
				break;
			}
			else if (std::regex_match(input, rest) && findCreatureDeckPosition(0, input[0]) != -1)
			{
				position = findCreatureDeckPosition(0, input[0]);
				if (userDeck[position].disCardDeck.size() < 2)
				{
					std::cout << "棄牌堆張數小於2,請選擇出牌" << std::endl;
					continue;
				}
				tmp.Index.clear();
				tmp.Icon = userDeck[position].Icon;
				tmp.Dex[0] = 99;
				tmp.Dex[1] = 99;
				tmp.Index.push_back(-1);
				tmp.Index.push_back(-1);
				compairList.push_back(tmp);
				break;
			}
			else
			{
				if (input.size() != 0)
				std::cout << "不合規範：" << std::endl;
			}
		}
	}
}
////////////////////////////////////////////////////////////
//使用者整理牌：
void Management::sort_Usercard(int index)
{
	UserCard tmp;
	for (int i = 0; i < userDeck[index].Card.size(); i++)
	{
		for (int j = 0; j < userDeck[index].Card.size() - i - 1; j++)
		{
			if (userDeck[index].Card[j].Order > userDeck[index].Card[j + 1].Order)
			{
				tmp = userDeck[index].Card[j];
				userDeck[index].Card[j] = userDeck[index].Card[j + 1];
				userDeck[index].Card[j + 1] = tmp;
			}
		}
	}
}
////////////////////////////////////////////////////////////
//使用者整理棄牌堆：
void Management::sort_discard(int index)
{
	UserCard tmp;
	for (int i = 0; i < userDeck[index].disCardDeck.size(); i++)
	{
		for (int j = 0; j < userDeck[index].disCardDeck.size() - i - 1; j++)
		{
			if (userDeck[index].disCardDeck[j].Order > userDeck[index].disCardDeck[j + 1].Order)
			{
				tmp = userDeck[index].disCardDeck[j];
				userDeck[index].disCardDeck[j] = userDeck[index].disCardDeck[j + 1];
				userDeck[index].disCardDeck[j + 1] = tmp;
			}
		}
	}
}
////////////////////////////////////////////////////////////
//怪物整理牌：
void Management::sort_Enemycard()
{
	int i, j, k;
	EnemyCard tmp;
	for (i = 0; i < enemyDeck.size(); i++)
	{
		for (j = 0; j < enemyDeck[i].Card.size(); j++)
		{
			for ( k = 0; k < enemyDeck[i].Card.size() - j - 1; k++)
			{
				if (enemyDeck[i].Card[k].Order > enemyDeck[i].Card[k + 1].Order)
				{
					tmp = enemyDeck[i].Card[k];
					enemyDeck[i].Card[k] = enemyDeck[i].Card[k + 1];
					enemyDeck[i].Card[k + 1] = tmp;
				}
			}
		}
	}
}
////////////////////////////////////////////////////////////
//怪物出牌：
void Management::enemyPlayCards()
{
	int i, j;
	std::vector <std::string> nameExist;
	bool exist;
	nameExist.clear();
	CompairCardDex tmp;
	sort_Enemycard();
	for (i = 0; i < enemyDeck.size(); i++)
	{
		if (checkSpace(enemyDeck[i].P))
		{
			exist = false;
			for (j = 0; j < nameExist.size(); j++)
			{
				if (enemyDeck[i].name == nameExist[j])
					exist = true;
			}
			if (!exist)
			{
				tmp.Index.clear();
				tmp.Index.push_back(enemyDeck[i].Card[0].Order);
				tmp.Dex[0] = enemyDeck[i].Card[0].DEX;
				tmp.Dex[1] = 99;
				for (j = i; j < enemyDeck.size(); j++)
				{
					if (enemyDeck[j].name == enemyDeck[i].name /*&& checkSpace(enemyDeck[j].P)*/)
					{
						tmp.Icon = enemyDeck[j].Icon;
						compairList.push_back(tmp);
					}
				}
				nameExist.push_back(enemyDeck[i].name);
			}
		}
	}
}
////////////////////////////////////////////////////////////
//依照敏捷值排序：
void Management::sort_compairList()
{
	int i, j;
	int position;
	CompairCardDex tmp;
	for (i = compairList.size() - 1; i > 0; i--)
	{
		for (j = 0; j <= i - 1; j++)
		{
			if (compairList[j].Dex[0] > compairList[j + 1].Dex[0]) //較快的敏捷度比較
			{
				tmp = compairList[j];
				compairList[j] = compairList[j + 1];
				compairList[j + 1] = tmp;
			}
			else if (compairList[j].Dex[0] == compairList[j + 1].Dex[0]) //第二張敏捷度比較
			{
				if (compairList[j].Dex[1] > compairList[j + 1].Dex[1])
				{
					tmp = compairList[j];
					compairList[j] = compairList[j + 1];
					compairList[j + 1] = tmp;
				}
				else if (compairList[j].Dex[1] == compairList[j + 1].Dex[1])
				{
					//都是怪物時
					if ((compairList[j].Icon >= 'a' && compairList[j].Icon <= 'z')&& compairList[j+1].Icon >= 'a' && compairList[j+1].Icon <= 'z')
					{
						if (enemyDeck[findCreatureDeckPosition(1, compairList[j].Icon)].name > enemyDeck[findCreatureDeckPosition(1, compairList[j + 1].Icon)].name)
						{
							tmp = compairList[j];
							compairList[j] = compairList[j + 1];
							compairList[j + 1] = tmp;
						}
					}
					else if (compairList[j].Icon > compairList[j + 1].Icon)
					{
						tmp = compairList[j];
						compairList[j] = compairList[j + 1];
						compairList[j + 1] = tmp;
					}
				}
			}
		}
	}


}
////////////////////////////////////////////////////////////