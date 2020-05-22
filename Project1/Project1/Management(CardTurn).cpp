#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Management.h"
#include <regex>
using namespace std;

int  Management::findCardPosition(CompairCardDex& compairCardDex, int index)
{
	int i;
	for (i = 0; i < compairCardDex.Index.size(); i++)
	{
		if (compairCardDex.Index[i] == index)
			return i;
	}
	return -1;
}

void Management::playCard()
{
	static int round_count = 0;
	int position;
	int p1;
	int i, j, k, l, index, index1, index2;
	string command;
	CompairCardDex tmp;
	std::regex play("^[0-9]{1}[ud]{1}$");
	std::regex userCheck("^[A-D]{1} check$");
	std::regex creatureCheck("check");
	char icon;
	compairList.clear();
	// 玩家出牌
	userPlayCards();
	//敵人出牌
	enemyPlayCards();
	//所有牌排序
	sort_compairList();
	//依序出牌 
	string skill[] = { "move", "heal", "shield", "attack","range" };
	round_count += 1;
	cout << "--------------------------------------------" << endl <<
		"round " << round_count << ":" << endl;
	for (i = 0; i < compairList.size(); i++)
	{
		if (!compairList[i].skip)
		{
			if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //主角方
			{
				position = findCreatureDeckPosition(0, compairList[i].Icon);
				if (compairList[i].Index[0] != -1)
				{
					cout << "角色" << userDeck[position].Icon << "出牌" << endl;
					while (getline(cin, command))
					{
						if (std::regex_match(command, creatureCheck)) //顯示所有生物狀態
						{

							for (j = 0; j < userDeck.size(); j++)
								cout << userDeck[j].Icon << "-hp: " << userDeck[j].HP << ", shield: " << userDeck[j].Shield << endl;
							for (j = 0; j < enemyDeck.size(); j++)
							{
								if (checkSpace(enemyDeck[j].P))
									cout << enemyDeck[j].Icon << "-hp: " << enemyDeck[j].HP[enemyDeck[j].Type] << ", shield: " << enemyDeck[j].Shield << endl;
							}
						}
						else if (std::regex_match(command, userCheck) && findCreatureDeckPosition(0, command[0]) != -1) //顯示指定user狀態
						{
							position = findCreatureDeckPosition(0, command[0]);
							cout << "hand: ";
							for (int j = 0; j < userDeck[position].Card.size(); j++)
							{
								if (j == userDeck[position].Card.size() - 1)
									cout << userDeck[position].Card[j].Order << "; ";
								else
									cout << userDeck[position].Card[j].Order << ", ";
							}
							cout << "discard: ";
							for (int j = 0; j < userDeck[position].disCardDeck.size(); j++)
							{
								cout << userDeck[position].disCardDeck[j].Order;
								if (j != userDeck[position].disCardDeck.size() - 1)
									cout << ", ";
							}
							cout << endl;
						}
						else if (std::regex_match(command, play) && compairList[i].cardExist(command[0]-'0')) //選擇卡片
						{
							p1 = findCardPosition(compairList[i], command[0] - '0');
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
							std::cout << "不合規範：" << std::endl;
					}

				}
				else
				{
					cout << "英雄" << userDeck[position].Icon << "長休" << endl;
					rest(userDeck[position]);
				}

			}
			else if (compairList[i].Icon >= 'a' && compairList[i].Icon <= 'z') //敵人方
			{
				position = findCreatureDeckPosition(1, compairList[i].Icon);
				cout << "敵人" << enemyDeck[position].Icon << "出牌" << endl;
				usingEffect(enemyDeck[position], compairList[i].Index[0]);
			}
		}
		// 每個物件行動結束計算
		survivalCheck();
	}
	// 每輪結束計算
	doorOpenCheck();
}