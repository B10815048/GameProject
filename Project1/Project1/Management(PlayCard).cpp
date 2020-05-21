#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Management.h"
using namespace std;

int Management::findCardPosition(User& user, int index)
{
	int i;
	for (i = 0; i < user.Card.size(); i++)
	{
		if (user.Card[i].Order == index)
			return i;
	}
	return -1;
}

int Management::findCardPosition(Enemy& enemy, int index)
{
	int i;
	for (i = 0; i < enemy.Card.size(); i++)
	{
		if (enemy.Card[i].Order == index)
			return i;
	}
	return -1;
}

void Management::userPlayCards()
{
	int position;
	int i, j, k, l, m, index, index1, index2;
	CompairCardDex tmp;
	char icon;
	string input;
	std::cout << "出牌:" << endl;
	for (int i = 0; i < userDeck.size(); i++)
	{
		cin >> input;
		if (input == "check")
		{
			for (int j = 0; j < userDeck.size(); j++)
			{
				cout << userDeck[j].Icon << "-hp: " << userDeck[j].HP << ", shield: " << userDeck[j].Shield << endl;
			}
			for (int j = 0; j < enemyDeck.size(); j++)
			{
				if(checkSpace(enemyDeck[j].P))
					cout << enemyDeck[j].Icon << "-hp: " << enemyDeck[j].HP[enemyDeck[j].Type] << ", shield: " << enemyDeck[j].Shield << endl;
			}
			i--;
			continue;
		}
		else
			icon = input[0];
		tmp.Index.clear();
		position = findCreatureDeckPosition(0, icon);
		tmp.Icon = userDeck[position].Icon;
		cin >> input;
		if (input == "check") // check指令
		{
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
			i--;
			continue;
		}
		else
			index = stoi(input);
		if (index == -1) //長休指令
		{
			tmp.Dex[0] = 99;
			tmp.Dex[1] = 99;
			tmp.Index.push_back(-1);
			tmp.Index.push_back(-1);
		}
		else //出牌指令
		{
			////////////////////////////
			index1 = findCardPosition(userDeck[position], index);
			tmp.Index.push_back(userDeck[position].Card[index1].Order);
			cin >> index;
			index2 = findCardPosition(userDeck[position], index);
			tmp.Index.push_back(userDeck[position].Card[index2].Order);
			////////////////////////////
			tmp.Dex[0] = userDeck[position].Card[index1].DEX;
			tmp.Dex[1] = userDeck[position].Card[index2].DEX;
		}
		compairList.push_back(tmp);
	}
}

void Management::enemyPlayCards()
{
	int i, j;
	int minIndex, position;
	CompairCardDex tmp;
	for (i = 0; i < enemyDeck.size(); i++)
	{
		if (checkSpace(enemyDeck[i].P))
		{
			tmp.Index.clear();
			minIndex = enemyDeck[i].Card[0].Order;
			position = 0;
			for (j = 0; j < enemyDeck[i].Card.size(); j++)
			{
				if (enemyDeck[i].Card[j].Order < minIndex)
				{
					minIndex = enemyDeck[i].Card[j].Order;
					position = j;
				}
			}
			tmp.Index.push_back(minIndex);
			tmp.Dex[0] = enemyDeck[i].Card[position].DEX;
			tmp.Dex[1] = 99;
			tmp.Icon = enemyDeck[i].Icon;
			compairList.push_back(tmp);
		}
	}
}

void Management::sort_compairList()
{
	int i, j;
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
					if (compairList[j].Icon > compairList[j + 1].Icon)
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

void Management::usingEffect(User& userDeck, int index, int part)
{
	int i, j;
	string skill[] = { "move", "heal", "shield", "attack","range" };
	for (i = 0; i < userDeck.Card.size(); i++)
	{
		if (userDeck.Card[i].Order == index)
		{
			if (part == 1) //卡牌下半部效果
			{
				for (j = 0; j < userDeck.Card[i].BelowType.size(); j++)
				{
					cout << "發動角色" << userDeck.Icon << "技能卡下方效果：" << skill[userDeck.Card[i].BelowType[j]] << endl;
					if (userDeck.Card[i].BelowType[j] == 0)
						setMove(userDeck, stoi(userDeck.Card[i].BelowAbilityValue[j]));
					else if (userDeck.Card[i].BelowType[j] == 1)
						Heal(userDeck, userDeck.Card[i].BelowAbilityValue[j]);
					else if (userDeck.Card[i].BelowType[j] == 2)
						Shield(userDeck, userDeck.Card[i].BelowAbilityValue[j]);
					else if (userDeck.Card[i].BelowType[j] == 3)
					{
						if (j != userDeck.Card[i].BelowType.size() - 1)
						{
							if (userDeck.Card[i].BelowType[j + 1] == 4)
								Range(userDeck, userDeck.Card[i].BelowAbilityValue[j + 1]);

						}
						Attack(userDeck, userDeck.Card[i].BelowAbilityValue[j]);
						if (j != userDeck.Card[i].BelowType.size() - 1)
						{
							if (userDeck.Card[i].BelowType[j + 1] == 4)
								j++;
						}
					}
				}
			}
			else if (part == 0) //卡牌上半部技能
			{
				for (j = 0; j < userDeck.Card[i].TopType.size(); j++)
				{
					cout << "發動角色" << userDeck.Icon << "技能卡上方效果：" << skill[userDeck.Card[i].TopType[j]] << endl;
					if (userDeck.Card[i].TopType[j] == 0)
						setMove(userDeck, stoi(userDeck.Card[i].TopAbilityValue[j]));
					else if (userDeck.Card[i].TopType[j] == 1)
						Heal(userDeck, userDeck.Card[i].TopAbilityValue[j]);
					else if (userDeck.Card[i].TopType[j] == 2)
						Shield(userDeck, userDeck.Card[i].TopAbilityValue[j]);
					else if (userDeck.Card[i].TopType[j] == 3)
					{
						if (j != userDeck.Card[i].TopType.size() - 1)
						{
							if (userDeck.Card[i].TopType[j + 1] == 4)
								Range(userDeck, userDeck.Card[i].TopAbilityValue[j + 1]);
						}
						Attack(userDeck, userDeck.Card[i].TopAbilityValue[j]);
						if (j != userDeck.Card[i].TopType.size() - 1)
						{
							if (userDeck.Card[i].TopType[j + 1] == 4)
								j++;
						}
					}
					else if (userDeck.Card[i].TopType[j] == 0)
						setMove(userDeck, stoi(userDeck.Card[i].TopAbilityValue[j]));

				}
			}
			//棄牌
			userDeck.disCardDeck.push_back(userDeck.Card[i]);
			userDeck.Card.erase(userDeck.Card.begin() + i);
		}
	}
	
}

void Management::usingEffect(Enemy& enemyDeck, int index)
{
	int i, j;
	string skill[] = { "move", "heal", "shield", "attack","range" };
	for (i = 0; i < enemyDeck.Card.size(); i++)
	{
		if (enemyDeck.Card[i].Order == index)
		{
			for (j = 0; j < enemyDeck.Card[i].Type.size(); j++)
			{
				cout << "發動敵人" << enemyDeck.Icon << "技能卡效果：" <<  skill[enemyDeck.Card[i].Type[j]] << endl;
				if (enemyDeck.Card[i].Type[j] == 0)
					Move(enemyDeck, enemyDeck.Card[i].AbilityValue[j]);
				else if (enemyDeck.Card[i].Type[j] == 1)
					Heal(enemyDeck, enemyDeck.Card[i].AbilityValue[j]);
				else if (enemyDeck.Card[i].Type[j] == 2)
					Shield(enemyDeck, enemyDeck.Card[i].AbilityValue[j]);
				else if (enemyDeck.Card[i].Type[j] == 3)
				{
					if (j != enemyDeck.Card[i].Type.size() - 1)
					{
						if (enemyDeck.Card[i].Type[j + 1] == 4)
							Range(enemyDeck, enemyDeck.Card[i].AbilityValue[j + 1]);
					}
					Attack(enemyDeck, enemyDeck.Card[i].AbilityValue[j]);
					if (j != enemyDeck.Card[i].Type.size() - 1)
					{
						if (enemyDeck.Card[i].Type[j + 1] == 4)
							j++;
					}
				}

			}
			//棄牌
			enemyDeck.disCardDeck.push_back(enemyDeck.Card[i]);
			enemyDeck.Card.erase(enemyDeck.Card.begin() + i);
		}
	}
}

void Management::playCard()
{
	static int round_count = 0;
	int position;
	int i, j, k, l, index, index1, index2;
	string command;
	CompairCardDex tmp;
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
	for(i = 0; i < compairList.size(); i++)
	{
		if (!compairList[i].skip)
		{
			if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //主角方
			{
				position = findCreatureDeckPosition(0, compairList[i].Icon);
				if (compairList[i].Index[0] != -1)
				{
					cout << "角色" << userDeck[position].Icon << "出牌" << endl;
					cin >> command;
					if (command == "check")
					{
						for (int j = 0; j < userDeck.size(); j++)
						{
							cout << userDeck[j].Icon << "-hp: " << userDeck[j].HP << ", shield: " << userDeck[j].Shield << endl;
						}
						for (int j = 0; j < enemyDeck.size(); j++)
						{
							if (checkSpace(enemyDeck[j].P))
								cout << enemyDeck[j].Icon << "-hp: " << enemyDeck[j].HP[enemyDeck[j].Type] << ", shield: " << enemyDeck[j].Shield << endl;
						}
						i--;
						continue;
					}
					else if (command[1] == 'd')
					{
						//////////////////////////////////////////
						//發動下半部效果:
						for (j = 0; j < compairList[i].Index.size(); j++)
						{
							if (compairList[i].Index[j] == command[0] - '0')
							{
								for (l = 0; l < userDeck[position].Card.size(); l++)
								{
									if (userDeck[position].Card[l].Order == command[0] - '0')
										usingEffect(userDeck[position], command[0] - '0', 1);
								}
								compairList[i].Index.erase(compairList[i].Index.begin() + j);
							}
						}
						//////////////////////////////////////////
						//發動上半部效果:
						usingEffect(userDeck[position], compairList[i].Index[0], 0);
						compairList[i].Index.clear();
						//////////////////////////////////////////
					}
					else if (command[1] == 'u')
					{
						//////////////////////////////////////////
						//發動上半部效果:
						for (j = 0; j < compairList[i].Index.size(); j++)
						{
							if (compairList[i].Index[j] == command[0] - '0')
							{
								for (l = 0; l < userDeck[position].Card.size(); l++)
								{
									if (userDeck[position].Card[l].Order == command[0] - '0')
										usingEffect(userDeck[position], command[0] - '0', 0);
								}
								compairList[i].Index.erase(compairList[i].Index.begin() + j);
							}
						}
						//////////////////////////////////////////
						//發動下半部效果:
						usingEffect(userDeck[position], compairList[i].Index[0], 1);
						compairList[i].Index.clear();
						//////////////////////////////////////////
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

int  Management::findCreaturePosition(int camp, string name)
{
	int i;
	if (camp == 0)
	{
		for (i = 0; i < user.size(); i++)
		{
			if (user[i].name == name)
				return i;
		}
	}
	else if (camp == 1)
	{
		for (i = 0; i < enemy.size(); i++)
		{
			if (enemy[i].name == name)
				return i;
		}
	}
	return -1;
}

int  Management::findCreatureDeckPosition(int camp, char icon)
{
	int i;
	if (camp == 0)
	{
		for (i = 0; i < userDeck.size(); i++)
		{
			if (userDeck[i].Icon == icon)
				return i;
		}
	}
	else if (camp == 1)
	{
		for (i = 0; i < enemyDeck.size(); i++)
		{
			if (enemyDeck[i].Icon == icon)
				return i;
		}
	}
	return -1;
}

void Management::rest(User& user)
{
	int index;
	int i;
	std::cout << "選擇一張牌刪除：" << std::endl;
	while (std::cin >> index)
	{
		for (i = 0; i < user.disCardDeck.size(); i++)
		{
			if (user.disCardDeck[i].Order == index)
			{
				user.disCardDeck.erase(user.disCardDeck.begin() + i);
				
				user.Card.insert(user.Card.end(), user.disCardDeck.begin(), user.disCardDeck.end());
				user.disCardDeck.clear();
				return;
			}
			cout << "重新選擇：" << std::endl;
		}
	}
}