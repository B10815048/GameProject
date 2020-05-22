#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Management.h"

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

void Management::enemyPlayCards()
{
	int i, j;
	int minIndex, position;
	std::vector <std::string> nameExist;
	bool exist;
	nameExist.clear();
	CompairCardDex tmp;
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
				for (j = i + 1; j < enemyDeck.size(); j++)
				{
					if (enemyDeck[j].name == enemyDeck[i].name)
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

void Management::sort_card(int index)
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

	std::cout << "生物行動執行順序:" << std::endl;
	for (i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z')
			std::cout << compairList[i].Icon << " ";
		else
		{
			for (int j = 0; j < enemyDeck.size(); j++)
			{
				if (compairList[i].Icon == enemyDeck[j].Icon)
					std::cout << enemyDeck[j].name << " ";
			}
		}

		if (compairList[i].Dex[0] < 10)
			std::cout << "0";
		std::cout << compairList[i].Dex[0] << " ";
		if(compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z')
			std::cout << compairList[i].Index[0] << " " << compairList[i].Index[1] << std::endl;
		else
		{
			int position = 0;
			for (int j = 0; j < enemyDeck.size(); j++)
			{
				if (compairList[i].Icon == enemyDeck[j].Icon)
				{
					for (int k = 0; k < enemyDeck[j].Card.size(); k++)
					{
						if (enemyDeck[j].Card[i].Order == compairList[i].Index[0])
							position = k;
					}

					for (int k = 0; k < enemyDeck[j].Card[position].Type.size(); k++)
					{
						if (enemyDeck[j].Card[position].Type[k] == 0)
							std::cout << "move ";
						else if (enemyDeck[j].Card[position].Type[k] == 1)
							std::cout << "heal ";
						else if (enemyDeck[j].Card[position].Type[k] == 2)
							std::cout << "shield ";
						else if (enemyDeck[j].Card[position].Type[k] == 3)
							std::cout << "attack ";
						else if (enemyDeck[j].Card[position].Type[k] == 4)
							std::cout << "range ";
						std::cout << enemyDeck[j].Card[position].AbilityValue[k] << " ";
					}
					std::cout << std::endl;
					break;
				}
			}
		}
		
	}	
}	

void Management::usingEffect(User& userDeck, int index, int part)
{
	int i, j;
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	for (i = 0; i < userDeck.Card.size(); i++)
	{
		if (userDeck.Card[i].Order == index)
		{
			if (part == 1) //卡牌下半部效果
			{
				for (j = 0; j < userDeck.Card[i].BelowType.size(); j++)
				{
					std::cout << "發動角色" << userDeck.Icon << "技能卡下方效果：" << skill[userDeck.Card[i].BelowType[j]] << std::endl;
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
					std::cout << "發動角色" << userDeck.Icon << "技能卡上方效果：" << skill[userDeck.Card[i].TopType[j]] << std::endl;
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
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	for (i = 0; i < enemyDeck.Card.size(); i++)
	{
		if (enemyDeck.Card[i].Order == index)
		{
			for (j = 0; j < enemyDeck.Card[i].Type.size(); j++)
			{
				std::cout << "發動敵人" << enemyDeck.Icon << "技能卡效果：" <<  skill[enemyDeck.Card[i].Type[j]] << std::endl;
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
			if (enemyDeck.Card[i].Shuffle)
			{
				enemyDeck.Card.insert(enemyDeck.Card.end(), enemyDeck.disCardDeck.begin(), enemyDeck.disCardDeck.end());
				enemyDeck.disCardDeck.clear();
			}
			else
			{
				enemyDeck.disCardDeck.push_back(enemyDeck.Card[i]);
				enemyDeck.Card.erase(enemyDeck.Card.begin() + i);
			}			
		}
	}
}


int  Management::findCreaturePosition(int camp, std::string name)
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
		}
		std::cout << "重新選擇：" << std::endl;
	}
}