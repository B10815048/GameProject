#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"
using namespace std;

void Management::userPlayCards()
{
	int position;
	int i, j, k, l, m, index, index1, index2;
	CompairCardDex tmp;
	char icon;
	for (i = 0; i < userDeck.size(); i++)
	{
		cin >> icon;
		tmp.Index.clear();
		for (j = 0; j < userDeck.size(); j++)
		{
			if (userDeck[j].Icon == icon)
			{
				position = j;
			}
		}
		tmp.Icon = userDeck[position].Icon;
		cin >> index;
		if (index == -1) //������O
		{
			tmp.Dex[0] = 99;
			tmp.Dex[1] = 99;
			tmp.Index.push_back(-1);
			tmp.Index.push_back(-1);
		}
		else //�X�P���O
		{
			for (j = 0; j < userDeck[position].Card.size(); j++)
			{
				if (userDeck[position].Card[j].Order == index)
				{
					index1 = j;
					tmp.Index.push_back(userDeck[position].Card[j].Order);
				}
			}
			cin >> index;
			for (j = 0; j < userDeck[position].Card.size(); j++)
			{
				if (userDeck[position].Card[j].Order == index)
				{
					index2 = j;
					tmp.Index.push_back(userDeck[position].Card[j].Order);
				}
			}
			if (userDeck[position].Card[index1].DEX > userDeck[position].Card[index2].DEX)
			{
				tmp.Dex[0] = userDeck[position].Card[index2].DEX;
				tmp.Dex[1] = userDeck[position].Card[index1].DEX;
			}
			else
			{
				tmp.Dex[0] = userDeck[position].Card[index1].DEX;
				tmp.Dex[1] = userDeck[position].Card[index2].DEX;
			}
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
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1')
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
			if (compairList[j].Dex[0] > compairList[j + 1].Dex[0]) //���֪��ӱ��פ��
			{
				tmp = compairList[j];
				compairList[j] = compairList[j + 1];
				compairList[j + 1] = tmp;
			}
			else if (compairList[j].Dex[0] == compairList[j + 1].Dex[0]) //�ĤG�i�ӱ��פ��
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
			if (part == 1) //�d�P�U�b���ĪG
			{
				for (j = 0; j < userDeck.Card[i].BelowType.size(); j++)
				{
					//�I�s�R�O
					if (userDeck.Card[i].BelowType[j] == 3)
					{
						if (j != userDeck.Card[i].BelowType.size() - 1)
						{
							if (userDeck.Card[i].BelowType[j + 1] == 4)
							{
								Range(userDeck, userDeck.Card[i].BelowAbilityValue[j + 1]);
								std::cout << "            " << userDeck.Card[i].BelowAbilityValue[j + 1] << std::endl;
							}

						}
						Attack(userDeck, userDeck.Card[i].BelowAbilityValue[j]);
						if (j != userDeck.Card[i].BelowType.size() - 1)
						{
							if (userDeck.Card[i].BelowType[j + 1] == 4)
								j++;
						}
					}
					cout << "�ϥέ^���ޯ�d�U��G" << skill[userDeck.Card[i].BelowType[j]] << endl;
				}
			}
			else if (part == 0) //�d�P�W�b���ޯ�
			{
				for (j = 0; j < userDeck.Card[i].TopType.size(); j++)
				{
					//�I�s�R�O
					if (userDeck.Card[i].TopType[j] == 3)
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
					cout << "�ϥέ^���ޯ�d�W��G" << skill[userDeck.Card[i].TopType[j]] << endl;
				}
			}
			//��P
			userDeck.disCardDeck.push_back(userDeck.Card[i]);
			userDeck.Card.erase(userDeck.Card.begin() + i);
		}
	}
	
}

void Management::playCard()
{
	int position;
	int i, j, k, l, index, index1, index2;
	string command;
	CompairCardDex tmp;
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
	for(i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z') //�D����
		{
			for (j = 0; j < userDeck.size(); j++)
			{
				if (userDeck[j].Icon == compairList[i].Icon)
					position = j;
			}
			if (compairList[i].Index[0] != -1)
			{
				cout << "�^��" << userDeck[position].Icon << "�X�P" << endl;
				cin >> command;
				if (command[1] == 'd')
				{
					//////////////////////////////////////////
					//�o�ʤU�b���ĪG:
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
					//�o�ʤW�b���ĪG:
					usingEffect(userDeck[position], compairList[i].Index[0], 0);
					compairList[i].Index.clear();
					//////////////////////////////////////////
				}
				else if (command[1] == 'u')
				{
					//////////////////////////////////////////
					//�o�ʤW�b���ĪG:
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
					//�o�ʤU�b���ĪG:
					usingEffect(userDeck[position], compairList[i].Index[0], 1);
					compairList[i].Index.clear();
					//////////////////////////////////////////
				}
			}
			else
			{
				cout << "�^��" << userDeck[position].Icon << "����" << endl;
			}
			
		}
		else if (compairList[i].Icon >='a' &&compairList[i].Icon <='z') //�ĤH��
		{
			for (j=0;j<enemyDeck.size();j++)
			{
				if (enemyDeck[j].Icon == compairList[i].Icon)
					position = j;
			}
			cout << "�ĤH�X�P" << endl;
			/*for (l = 0; l < enemyDeck[position].Card.size(); l++)
			{
				if (enemyDeck[position].Card[l].Order == compairList[i].Index[0])
				{
					for (m = 0; m < enemyDeck[position].Card[l].Type.size(); m++)
					{
						//�I�s�R�O
						cout << "�ϥμĤH�U��G" << skill[enemyDeck[position].Card[l].Type[m]] << endl;
					}
					//��P
					enemyDeck[position].disCardDeck.push_back(enemyDeck[position].Card[l]);
					enemyDeck[position].Card.erase(enemyDeck[position].Card.begin() + l);
				}
			}		*/
		}
	}
}

