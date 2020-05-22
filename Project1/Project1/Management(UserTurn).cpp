#include <iostream>
#include <vector>
#include <string>
#include "Management.h"
#include <sstream>
#include <regex>
using namespace std;

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
	std::cout << "出牌:" << endl;
	bool haveDie = false;
	for (int i = 0; i < userDeck.size(); i++)
	{
		// 檢查角色是否不能選擇長休或出牌
		if (userDeck[i].Card.size() < 2 && userDeck[i].disCardDeck.size() < 2)
		{
			std::cout << userDeck[i].Icon << " is killed!!" << std::endl;
			userDeck.erase(userDeck.begin() + i);
			haveDie = true;
			i--;
			continue;
		}
		while (getline(cin,input))
		{
			if (std::regex_match(input, creatureCheck)) //顯示所有生物狀態
			{

				for (j = 0; j < userDeck.size(); j++)
					cout << userDeck[j].Icon << "-hp: " << userDeck[j].HP << ", shield: " << userDeck[j].Shield << endl;
				for (j = 0; j < enemyDeck.size(); j++)
				{
					if (checkSpace(enemyDeck[j].P))
						cout << enemyDeck[j].Icon << "-hp: " << enemyDeck[j].HP[enemyDeck[j].Type] << ", shield: " << enemyDeck[j].Shield << endl;
				}
			}
			else if (std::regex_match(input, userCheck) && findCreatureDeckPosition(0, input[0])!=-1) //顯示指定user狀態
			{
				position = findCreatureDeckPosition(0, input[0]);
				sort_card(position);
				sort_discard(position);
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
					std::cout << "手牌張數小於2,請選擇長休";
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
				p2 = findCardPosition(userDeck[position], index1);
				if (p2 != -1)
				{
					tmp.Index.push_back(userDeck[position].Card[p2].Order);
					tmp.Dex[0] = userDeck[position].Card[p2].DEX;
				}
				else
				{
					std::cout << "不合規範：" << std::endl;
					continue;
				}
				p2 = findCardPosition(userDeck[position], index2);
				if (p2 != -1)
				{
					tmp.Index.push_back(userDeck[position].Card[p2].Order);
					tmp.Dex[1] = userDeck[position].Card[p2].DEX;
				}
				else
				{
					std::cout << "不合規範：" << std::endl;
					continue;
				}
				compairList.push_back(tmp);
				break;
			}
			else if (std::regex_match(input, rest) && findCreatureDeckPosition(0, input[0]) != -1)
			{
				position = findCreatureDeckPosition(0, input[0]);
				if (userDeck[position].disCardDeck.size() < 2)
				{
					std::cout << "棄牌堆張數小於2,請選擇出牌";
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
	if (haveDie)
	{
		Point p;
		getxy(p);
		printMap(p);
		printEnemy(p);
		printUser(p);
	}
}