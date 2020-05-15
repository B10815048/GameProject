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
		if (index == -1)
		{
			tmp.Dex[0] = 99;
			tmp.Dex[1] = 99;
			tmp.Index.push_back(-1);
			tmp.Index.push_back(-1);
		}
		else
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

int Management::getCamp(char Icon)
{
	if (Icon >= 'A' && Icon <= 'Z') //���a��
		return 0;
	else if (Icon >= 'a' && Icon <= 'z') //�ĤH��
		return 1;
}

void Management::playCard()
{
	int position;
	int i, j, k, l, m, index, index1, index2;
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
					for (k = 0; k < compairList[i].Index.size(); k++)
					{
						if (compairList[i].Index[k] == command[0] - '0')
						{
							for (l = 0; l < userDeck[position].Card.size(); l++)
							{
								if (userDeck[position].Card[l].Order == command[0] - '0')
								{
									for (m = 0; m < userDeck[position].Card[l].BelowType.size(); m++)
									{
										//�I�s�R�O
										cout << "�ϥέ^���ޯ�d�U��G" << skill[userDeck[position].Card[l].BelowType[m]] << endl;
									}
									//��P
									userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
									userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
								}
							}
							compairList[i].Index.erase(compairList[i].Index.begin() + k);
						}
					}

					for (l = 0; l < userDeck[position].Card.size(); l++)
					{
						if (userDeck[position].Card[l].Order == compairList[i].Index[0])
						{
							for (m = 0; m < userDeck[position].Card[l].TopType.size(); m++)
							{
								cout << "�ϥέ^���ޯ�d�W��G" << skill[userDeck[position].Card[l].TopType[m]] << endl;
							}
							//��P
							userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
							userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
						}
					}
					compairList[i].Index.clear();
				}
				else if (command[1] == 'u')
				{
					for (k = 0; k < compairList[i].Index.size(); k++)
					{
						if (compairList[i].Index[k] == command[0] - '0')
						{
							for (l = 0; l < userDeck[position].Card.size(); l++)
							{
								if (userDeck[position].Card[l].Order == command[0] - '0')
								{
									for (m = 0; m < userDeck[position].Card[l].TopType.size(); m++)
									{
										cout << "�ϥέ^���ޯ�d�W��G" << skill[userDeck[position].Card[l].TopType[m]] << endl;
									}
									//��P
									userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
									userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
								}
							}
							compairList[i].Index.erase(compairList[i].Index.begin() + k);
						}
					}
					for (l = 0; l < userDeck[position].Card.size(); l++)
					{
						if (userDeck[position].Card[l].Order == compairList[i].Index[0])
						{
							for (m = 0; m < userDeck[position].Card[l].BelowType.size(); m++)
							{
								//�I�s�R�O
								cout << "�ϥέ^���ޯ�d�U��G" << skill[userDeck[position].Card[l].BelowType[m]] << endl;
							}
							//��P
							userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
							userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
						}
					}
					compairList[i].Index.clear();
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
			for (l = 0; l < enemyDeck[position].Card.size(); l++)
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
			}		
		}
	}
}

