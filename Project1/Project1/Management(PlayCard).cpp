#include <iostream>
#include <vector>
#include <string>
#include "Management.h"
#include <sstream>
#include <regex>
using namespace std;
////////////////////////////////////////////////////////////
//�ϥΪ̥X�P�G
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
	std::cout << "�X�P:" << endl;
	for (int i = 0; i < userDeck.size(); i++) // �ˬd����O�_�����ܪ���ΥX�P
	{
		if (userDeck[i].Card.size() < 2 && userDeck[i].disCardDeck.size() < 2)
		{
			std::cout << userDeck[i].Icon << " is killed!!" << std::endl;
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
		while (getline(cin,input))
		{
			if (std::regex_match(input, creatureCheck)) //��ܩҦ��ͪ����A
				printCreatureCheck();
			else if (std::regex_match(input, userCheck) && findCreatureDeckPosition(0, input[0]) != -1) //��ܫ��wuser���A
				printUserCheck(input[0]);
			else if (std::regex_match(input, play) && findCreatureDeckPosition(0, input[0])!=-1)
			{
				position = findCreatureDeckPosition(0, input[0]);
				if (havePlayed(userDeck[position].Icon))
				{
					std::cout << "���X�W�d�G" << std::endl;
					continue;
				}
				if (userDeck[position].Card.size() < 2)
				{
					std::cout << "��P�i�Ƥp��2,�п�ܪ���";
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
					std::cout << "���X�W�d�G" << std::endl;
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
					std::cout << "���X�W�d�G" << std::endl;
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
					std::cout << "���X�W�d�G" << std::endl;
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
					std::cout << "��P��i�Ƥp��2,�п�ܥX�P";
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
				std::cout << "���X�W�d�G" << std::endl;
			}
		}
	}
}