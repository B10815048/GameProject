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
	int i, p1;
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	p1 = findCardPosition(userDeck, index);
	if (part == 1) //卡牌下半部效果
	{
		for (i = 0; i < userDeck.Card[p1].BelowType.size(); i++)
		{
			if (debugMode == 0)
			{
				msg = std::string("發動角色 ") + userDeck.Icon + std::string(" 技能卡下方效果：") + std::string(skill[userDeck.Card[p1].BelowType[i]]);
				addBattleMsg(msg);
			}
			if (userDeck.Card[p1].BelowType[i] == 0)
				setMove(userDeck, stoi(userDeck.Card[p1].BelowAbilityValue[i]));
			else if (userDeck.Card[p1].BelowType[i] == 1)
				Heal(userDeck, userDeck.Card[p1].BelowAbilityValue[i]);
			else if (userDeck.Card[p1].BelowType[i] == 2)
				Shield(userDeck, userDeck.Card[p1].BelowAbilityValue[i]);
			else if (userDeck.Card[p1].BelowType[i] == 3)
			{
				if (i != userDeck.Card[p1].BelowType.size() - 1)
				{
					if (userDeck.Card[p1].BelowType[i + 1] == 4)
						Range(userDeck, userDeck.Card[p1].BelowAbilityValue[i + 1]);

				}
				Attack(userDeck, userDeck.Card[p1].BelowAbilityValue[i]);
				if (i != userDeck.Card[p1].BelowType.size() - 1)
				{
					if (userDeck.Card[p1].BelowType[i + 1] == 4)
						i++;
				}
			}
			if (debugMode == 0)
				rePrint();
			// 執行一次動作判斷敵人死亡
			survivalCheck();
		}
	}
	else if (part == 0) //卡牌上半部技能
	{
		for (i = 0; i < userDeck.Card[p1].TopType.size(); i++)
		{
			if (debugMode == 0)
			{
				msg = std::string("發動角色 ") + userDeck.Icon + std::string(" 技能卡上方效果：") + std::string(skill[userDeck.Card[p1].TopType[i]]);
				addBattleMsg(msg);
			}
			if (userDeck.Card[p1].TopType[i] == 0)
				setMove(userDeck, stoi(userDeck.Card[p1].TopAbilityValue[i]));
			else if (userDeck.Card[p1].TopType[i] == 1)
				Heal(userDeck, userDeck.Card[p1].TopAbilityValue[i]);
			else if (userDeck.Card[p1].TopType[i] == 2)
				Shield(userDeck, userDeck.Card[p1].TopAbilityValue[i]);
			else if (userDeck.Card[p1].TopType[i] == 3)
			{
				if (i != userDeck.Card[p1].TopType.size() - 1)
				{
					if (userDeck.Card[p1].TopType[i + 1] == 4)
						Range(userDeck, userDeck.Card[p1].TopAbilityValue[i + 1]);
				}
				Attack(userDeck, userDeck.Card[p1].TopAbilityValue[i]);
				if (i != userDeck.Card[p1].TopType.size() - 1)
				{
					if (userDeck.Card[p1].TopType[i + 1] == 4)
						i++;
				}
			}
			else if (userDeck.Card[p1].TopType[i] == 0)
				setMove(userDeck, stoi(userDeck.Card[p1].TopAbilityValue[i]));
			if (debugMode == 0)
				rePrint();
			// 執行一次動作判斷敵人死亡
			survivalCheck();
		}
	}
	//棄牌
	userDeck.disCardDeck.push_back(userDeck.Card[p1]);
	userDeck.Card.erase(userDeck.Card.begin() + p1);
}
////////////////////////////////////////////////////////////
//怪物發動卡牌能力：
void Management::usingEffect(Enemy& enemyDeck, int index)
{
	std::string msg;
	int i, p1;
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	p1 = findCardPosition(enemyDeck, index);
	if (checkSpace(enemyDeck.P))
	{
		for (i = 0; i < enemyDeck.Card[p1].Type.size(); i++)
		{
			if (debugMode == 0)
			{
				msg = std::string("發動敵人 ") + enemyDeck.Icon + std::string(" 技能卡效果：") + std::string(skill[enemyDeck.Card[p1].Type[i]]);
				std::cout << msg << std::endl;
				addBattleMsg(msg);
			}
			if (enemyDeck.Card[p1].Type[i] == 0)
				Move(enemyDeck, enemyDeck.Card[p1].AbilityValue[i]);
			else if (enemyDeck.Card[p1].Type[i] == 1)
				Heal(enemyDeck, enemyDeck.Card[p1].AbilityValue[i]);
			else if (enemyDeck.Card[p1].Type[i] == 2)
				Shield(enemyDeck, enemyDeck.Card[p1].AbilityValue[i]);
			else if (enemyDeck.Card[p1].Type[i] == 3)
			{
				if (i != enemyDeck.Card[p1].Type.size() - 1)
				{
					if (enemyDeck.Card[p1].Type[i + 1] == 4)
						Range(enemyDeck, enemyDeck.Card[p1].AbilityValue[i + 1]);
				}
				Attack(enemyDeck, enemyDeck.Card[p1].AbilityValue[i]);
				if (i != enemyDeck.Card[p1].Type.size() - 1)
				{
					if (enemyDeck.Card[p1].Type[i + 1] == 4)
						i++;
				}
			}
			survivalCheck();
			if (!debugMode)
			{
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
			}
		}
	}
	if (enemyDeck.Card[p1].Shuffle)
	{
		enemyDeck.Card.insert(enemyDeck.Card.end(), enemyDeck.disCardDeck.begin(), enemyDeck.disCardDeck.end());
		enemyDeck.disCardDeck.clear();
	}
	else
	{
		enemyDeck.disCardDeck.push_back(enemyDeck.Card[p1]);
		enemyDeck.Card.erase(enemyDeck.Card.begin() + p1);
	}
}
////////////////////////////////////////////////////////////

