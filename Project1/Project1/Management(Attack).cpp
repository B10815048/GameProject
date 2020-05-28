#include "Management.h"
#include <string>
#include <regex>
////////////////////////////////////////////////////////////
//�����\��G
void Management::Attack(Creature& creature, std::string command)
{
	int i, j;
	int position;
	std::string input;
	std::regex attack("^[a-z]{1}$");
	std::regex giveUp("0");
	int damage = creature.Attack + stoi(command);
	positiveValue(creature.Range);
	positiveValue(damage);
	if (creature.Range == 0)
		creature.Range = 1;
	if (creature.Camp == 0) //�D����
	{
		std::cout << "��ܧ����ĤH : " << std::endl;
		while (getline(std::cin , input))
		{
			if (std::regex_match(input, attack) && findCreatureDeckPosition(1, input[0]) != -1) //�ŦX�����ؼФΦb�����d��
			{
				position = findCreatureDeckPosition(1, input[0]);
				if (shootRange(creature.P, enemyDeck[position].P, 0, creature.Range) <= creature.Range && viewableRange(enemyDeck[position].P, creature.P))
				{
					damage = damage - enemyDeck[position].Shield; //��ڶˮ`
					positiveValue(damage);
					enemyDeck[position].HP[enemyDeck[position].Type] -= damage;
					std::cout << creature.Icon << " attack " << enemyDeck[position].Icon << " " << damage << " damage, " << enemyDeck[position].Icon << " shield " << enemyDeck[position].Shield
						<< " , " << enemyDeck[position].Icon << " remain " << enemyDeck[position].HP[enemyDeck[position].Type] << " hp" << std::endl;
					return;
				}
				else //�W�X�����d��
					std::cout << "error target!!!" << std::endl;

			}
			else if (std::regex_match(input, giveUp))
			{
				std::cout << "������..." << std::endl;
				return;
			}
			else  //�S�����ĤH
			std::cout << "error target!!!" << std::endl;
		}
	}
	else if (creature.Camp == 1) //�ĤH��
	{
		int step = 0, minStep = 99, count = 0;
		int userIndex[4] = { 0,0,0,0 };
		for (int j = 0; j < 4; j++)
			userIndex[j] = 0;
		for (i = 0; i < userDeck.size(); i++)
		{
			if (shootRange(creature.P, userDeck[i].P, 1, creature.Range) <= creature.Range && viewableRange(userDeck[i].P, creature.P))
			{
				step = shootRange(creature.P, userDeck[i].P, 1, creature.Range);
				if (step < minStep)
				{
					for (int j = 0; j < 4; j++)
						userIndex[j] = 0;

					minStep = step;
					userIndex[i] = 1;
					count = 1;
				}
				else if (step == minStep)
				{
					userIndex[i] = 1;
					count += 1;
				}
			}	
		}
		if (count == 0) //�����d�򤺨S���ĤH
		{
			std::cout << "no one lock" << std::endl;
		}
		else if (count == 1)
		{
			for (int i = 0; i < userDeck.size(); i++)
			{
				if (userIndex[i] == 1)
				{
					std::cout << creature.Icon << " lock " << userDeck[i].Icon << " in distance " << minStep << std::endl;
					if (damage > userDeck[i].Shield)
						userDeck[i].HP -= damage - userDeck[i].Shield;
					std::cout << creature.Icon << " attack " << userDeck[i].Icon << " " << damage << " damage, " << userDeck[i].Icon << " shield " << userDeck[i].Shield
						<< " , " << userDeck[i].Icon << " remain " << userDeck[i].HP << " hp" << std::endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < compairList.size(); i++)
			{
				for (int j = 0; j < userDeck.size(); j++)
				{
					if (compairList[i].Icon == userDeck[j].Icon && userIndex[j] == 1)
					{
						std::cout << creature.Icon << " lock " << userDeck[i].Icon << " in distance " << minStep << std::endl;
						if (damage > userDeck[j].Shield)
							userDeck[j].HP -= damage - userDeck[j].Shield;
						std::cout << creature.Icon << " attack " << userDeck[j].Icon << " " << damage << " damage, " << userDeck[j].Icon << " shield " << userDeck[j].Shield
							<< " , " << userDeck[j].Icon << " remain " << userDeck[j].HP << " hp" << std::endl;
						return;
					}
				}
			}
		}
	}
	resetRange();
}
////////////////////////////////////////////////////////////
