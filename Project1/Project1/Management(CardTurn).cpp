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
	// ���a�X�P
	userPlayCards();
	//�ĤH�X�P
	enemyPlayCards();
	//�Ҧ��P�Ƨ�
	sort_compairList();
	//�̧ǥX�P 
	string skill[] = { "move", "heal", "shield", "attack","range" };
	round_count += 1;
	cout << "--------------------------------------------" << endl <<
		"round " << round_count << ":" << endl;
	for (i = 0; i < compairList.size(); i++)
	{
		if (!compairList[i].skip)
		{
			if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //�D����
			{
				position = findCreatureDeckPosition(0, compairList[i].Icon);
				if (compairList[i].Index[0] != -1)
				{
					cout << "����" << userDeck[position].Icon << "�X�P" << endl;
					while (getline(cin, command))
					{
						if (std::regex_match(command, creatureCheck)) //��ܩҦ��ͪ����A
						{

							for (j = 0; j < userDeck.size(); j++)
								cout << userDeck[j].Icon << "-hp: " << userDeck[j].HP << ", shield: " << userDeck[j].Shield << endl;
							for (j = 0; j < enemyDeck.size(); j++)
							{
								if (checkSpace(enemyDeck[j].P))
									cout << enemyDeck[j].Icon << "-hp: " << enemyDeck[j].HP[enemyDeck[j].Type] << ", shield: " << enemyDeck[j].Shield << endl;
							}
						}
						else if (std::regex_match(command, userCheck) && findCreatureDeckPosition(0, command[0]) != -1) //��ܫ��wuser���A
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
						else if (std::regex_match(command, play) && compairList[i].cardExist(command[0]-'0')) //��ܥd��
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
							std::cout << "���X�W�d�G" << std::endl;
					}

				}
				else
				{
					cout << "�^��" << userDeck[position].Icon << "����" << endl;
					rest(userDeck[position]);
				}

			}
			else if (compairList[i].Icon >= 'a' && compairList[i].Icon <= 'z') //�ĤH��
			{
				position = findCreatureDeckPosition(1, compairList[i].Icon);
				cout << "�ĤH" << enemyDeck[position].Icon << "�X�P" << endl;
				usingEffect(enemyDeck[position], compairList[i].Index[0]);
			}
		}
		// �C�Ӫ����ʵ����p��
		survivalCheck();
	}
	// �C�������p��
	doorOpenCheck();
}