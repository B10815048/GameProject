#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Management.h"
////////////////////////////////////////////////////////////
//使用者發動卡牌能力：
void Management::usingEffect(User& userDeck, int index, int part)
{
	std::string msg;
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
					if (debugMode == 0)
					{
						msg = std::string("發動角色 ") + userDeck.Icon + std::string(" 技能卡下方效果：") + std::string(skill[userDeck.Card[i].BelowType[j]]);
						addBattleMsg(msg);
					}										
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
					if (debugMode == 0)
						rePrint();
				}
			}
			else if (part == 0) //卡牌上半部技能
			{
				for (j = 0; j < userDeck.Card[i].TopType.size(); j++)
				{
					if (debugMode == 0)
					{
						msg = std::string("發動角色 ") + userDeck.Icon + std::string(" 技能卡上方效果：") + std::string(skill[userDeck.Card[i].TopType[j]]);
						addBattleMsg(msg);
					}						
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
					if (debugMode == 0)
						rePrint();
				}
			}
			//棄牌
			userDeck.disCardDeck.push_back(userDeck.Card[i]);
			userDeck.Card.erase(userDeck.Card.begin() + i);
		}
	}
}
////////////////////////////////////////////////////////////
//怪物發動卡牌能力：
void Management::usingEffect(Enemy& enemyDeck, int index)
{
	std::string msg;
	int i, j;
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	for (i = 0; i < enemyDeck.Card.size(); i++)
	{
		if (enemyDeck.Card[i].Order == index)
		{
			for (j = 0; j < enemyDeck.Card[i].Type.size(); j++)
			{
				if (debugMode == 0)
				{
					msg = std::string("發動敵人 ") + enemyDeck.Icon + std::string(" 技能卡效果：") + std::string(skill[enemyDeck.Card[i].Type[j]]);
					addBattleMsg(msg);
				}					
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
				if (debugMode == 0)
					rePrint();
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
////////////////////////////////////////////////////////////

