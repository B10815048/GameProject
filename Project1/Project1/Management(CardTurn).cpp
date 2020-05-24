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

bool  Management::havePlayed(char icon)
{
	int i;
	for (i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon == icon)
			return true;
	}
	return false;
}
void Management::playCard()
{
	int position;
	int p1;
	int i, j, k, l, index, index1, index2;
	string command;
	CompairCardDex tmp;
	std::regex play("^[0-9]{1}[ud]{1}$");
	std::regex userCheck("^[A-D]{1} check$");
	std::regex creatureCheck("check");
	char icon;
	// �C���}�l
	round_count += 1;
	std::cout << "--------------------------------------------" << std::endl <<
		"round " << round_count << ":" << std::endl;
	compairList.clear();
	// ���a�X�P
	userPlayCards();
	//�ĤH�X�P
	enemyPlayCards();
	//�Ҧ��P�Ƨ�
	sort_compairList();
	//�̧ǥX�P 
	for (i = 0; i < compairList.size(); i++)
	{
		if (!compairList[i].skip)
		{
			if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //�D����
			{
				position = findCreatureDeckPosition(0, compairList[i].Icon);
				if (compairList[i].Index[0] != -1)
				{
					std::cout << "���쨤��" << userDeck[position].Icon << "�ϥεP���^�X (u/d/check)" << std::endl;
					while (getline(cin , command))
					{
						if (std::regex_match(command, creatureCheck)) //��ܩҦ��ͪ����A
							printCreatureCheck();
						else if (std::regex_match(command, userCheck) && findCreatureDeckPosition(0, command[0]) != -1) //��ܫ��wuser���A
							printUserCheck(command[0]);
						else if (std::regex_match(command, play) && compairList[i].cardExist(command[0]-'0')) //��ܥd��
						{
							p1 = findCardPosition(compairList[i], command[0] - '0');
							position = findCreatureDeckPosition(0, compairList[i].Icon);
							std::cout << userDeck[position].Icon << "'s turn: card " << compairList[i].Index[0] << " " << compairList[i].Index[1] << std::endl;
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
						{
							if (command.size() != 0)
								std::cout << "���X�W�d�G" << std::endl;
						}
					}

				}
				else
				{
					cout << "�^��" << userDeck[position].Icon << "����" << endl;
					Heal(userDeck[position], "2");
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