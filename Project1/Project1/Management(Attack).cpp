#include "Management.h"
#include <sstream>
#include <string>
#include <regex>
////////////////////////////////////////////////////////////
//攻擊功能：
void Management::Attack(Creature& creature, std::string command)
{
	int i, j;
	int position;
	std::string input, msg;
	std::regex attack("^[a-z]{1}$");
	std::regex giveUp("0");
	int damage = creature.Attack + stoi(command);
	positiveValue(creature.Range);
	positiveValue(damage);
	if (creature.Range == 0)
		creature.Range = 1;
	if (creature.Camp == 0) //主角方
	{
		if (debugMode == 0)
			std::cout << "選擇攻擊敵人 : (範圍 "  << creature.Range << " 步,傷害 " << stoi(command) << " 點)" << std::endl;
		while (getline(std::cin, input))
		{
			if (std::regex_match(input, attack) && findCreatureDeckPosition(1, input[0]) != -1) //符合攻擊目標及在攻擊範圍內
			{
				position = findCreatureDeckPosition(1, input[0]);
				if (shootRange(creature.P, enemyDeck[position].P, creature.Range) <= creature.Range && viewableRange(enemyDeck[position].P, creature.P))
				{
					if (damage > enemyDeck[position].Shield)
						enemyDeck[position].HP[enemyDeck[position].Type] -= damage - enemyDeck[position].Shield;
					std::cout << creature.Icon << " attack " << enemyDeck[position].Icon << " " << damage << " damage, " << enemyDeck[position].Icon << " shield " << enemyDeck[position].Shield
						<< ", " << enemyDeck[position].Icon << " remain " << enemyDeck[position].HP[enemyDeck[position].Type] << " hp" << std::endl;
					if (debugMode == 0)
					{
						msg = creature.Icon + std::string(" attack ") + enemyDeck[position].Icon + std::string(" ") + std::to_string(damage) + std::string(" damage, ")
							+ enemyDeck[position].Icon + std::string(" shield ") + std::to_string(enemyDeck[position].Shield) + std::string(", ")
							+ enemyDeck[position].Icon + std::string(" remain ") + std::to_string(enemyDeck[position].HP[enemyDeck[position].Type]) + std::string(" hp");						
						addBattleMsg(msg);
					}
					resetRange();
					return;
				}
				else //超出攻擊範圍
					std::cout << "error target!!!" << std::endl;
			}
			else if (std::regex_match(input, giveUp))
			{
				if (debugMode == 0)
					addBattleMsg(creature.Icon + std::string(" 放棄攻擊..."));
				resetRange();
				return;
			}
			else  //沒有此敵人
				std::cout << "error target!!!" << std::endl;
		}
	}
	else if (creature.Camp == 1) //敵人方
	{
		int step = 0, minStep = 99;
		int comP;
		std::vector <CompairCardDex > attackChoice;
		CompairCardDex aTmp;
		for (i = 0; i < userDeck.size(); i++)
		{
			if (shootRange(creature.P, userDeck[i].P, creature.Range) <= creature.Range && viewableRange(userDeck[i].P, creature.P))
			{
				step = shootRange(creature.P, userDeck[i].P, creature.Range);
				if (step < minStep)
				{
					attackChoice.clear();
					comP = findCompairCardDexPosition(userDeck[i].Icon);
					aTmp = compairList[comP];
					attackChoice.push_back(aTmp);
					minStep = step;
				}
				else if (step == minStep)
				{
					comP = findCompairCardDexPosition(userDeck[i].Icon);
					aTmp = compairList[comP];
					attackChoice.push_back(aTmp);
				}
			}
		}
		if (attackChoice.size() == 0) //攻擊範圍內沒有敵人
		{
			if (debugMode == 0)
				addBattleMsg(creature.Icon + std::string("找不到目標"));
			std::cout << "no one lock" << std::endl;
			resetRange();
			return;
		}
		else
		{
			for (i = 0; i < compairList.size(); i++)
			{
				for (j = 0; j < attackChoice.size(); j++)
				{
					if (compairList[i].Icon == attackChoice[j].Icon)
					{
						i = findCreatureDeckPosition(0, compairList[i].Icon);
						std::cout << creature.Icon << " lock " << userDeck[i].Icon << " in distance " << minStep << std::endl;
						if (damage > userDeck[i].Shield)
							userDeck[i].HP -= damage - userDeck[i].Shield;
						std::cout << creature.Icon << " attack " << userDeck[i].Icon << " " << damage << " damage, " << userDeck[i].Icon << " shield " << userDeck[i].Shield
							<< ", " << userDeck[i].Icon << " remain " << userDeck[i].HP << " hp" << std::endl;
						if (debugMode == 0)
						{
							msg = creature.Icon + std::string(" lock ") + userDeck[i].Icon + std::string(" in distance ") + std::to_string(minStep);
							addBattleMsg(msg);
							msg = creature.Icon + std::string(" attack ") + userDeck[i].Icon + std::string(" ") + std::to_string(damage) + std::string(" damage, ") + userDeck[i].Icon + std::string(" shield ")
								+ std::to_string(userDeck[i].Shield) + std::string(", ") + userDeck[i].Icon + std::string(" remain ") + std::to_string(userDeck[i].HP) + std::string(" hp");
							addBattleMsg(msg);
						}
						resetRange();
						return;
					}
				}

			}
		}
	}
}
////////////////////////////////////////////////////////////