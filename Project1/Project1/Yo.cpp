#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"
using namespace std;

void Management::playCard()
{
	vector<CompairCardDex> compairList;
	int position;
	int i, j, k, l, m, index, index1, index2;
	CompairCardDex tmp;
	char icon;

	// 玩家出牌
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
		cin >> index;		
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
		tmp.Icon = icon;
		compairList.push_back(tmp);
	}
	
	//敵人出牌
	int minIndex;
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
	//所有牌排序
	for(i = compairList.size()-1; i > 0; i--)
	{
		for(j = 0; j <= i-1; j++)
		{
			if( compairList[j].Dex[0] > compairList[j+1].Dex[0])
			{
				tmp = compairList [j];
				compairList[j] = compairList[j+1];
				compairList[j+1] = tmp;
			}
			else if (compairList[j].Dex[0] == compairList[j + 1].Dex[0])
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
	string command;
	//依序出牌 
	string skill[] = { "move", "heal", "shield", "attack","range" };
	for(i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].Icon >='A' &&compairList[i].Icon <='Z') //主角方
		{
			for (j=0;j<userDeck.size();j++)
			{
				if (userDeck[j].Icon == compairList[i].Icon)
					position = j;
			}
			cout << "英雄牌兩張牌出牌(3d)" << endl;
			cin >> command;
			if (command[1] == 'd')
			{
				for (k=0;k<compairList[i].Index.size();k++)
				{
					if (compairList[i].Index[k]==command[0]-'0')
					{
						for (l=0;l<userDeck[position].Card.size();l++)
						{
							if (userDeck[position].Card[l].Order == command[0]-'0')
							{
								for (m=0;m<userDeck[position].Card[l].BelowType.size();m++)
								{
									//呼叫命令
									cout << "使用英雄技能卡下方：" << skill[userDeck[position].Card[l].BelowType[m]] << endl;
								}
								//棄牌
								userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
								userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
							}
						}
						compairList[i].Index.erase(compairList[i].Index.begin()+k);
					}
				}
				
				for (l=0;l<userDeck[position].Card.size();l++)
				{
					if (userDeck[position].Card[l].Order == compairList[i].Index[0])
					{
						for (m=0;m<userDeck[position].Card[l].TopType.size();m++)
						{
							cout << "使用英雄技能卡上方：" << skill[userDeck[position].Card[l].TopType[m]] << endl;
						}
						//棄牌
						userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
						userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
					}
				}
				compairList[i].Index.clear();
			}
			else if (command[1] == 'u')
			{
				for (k=0;k<compairList[i].Index.size();k++)
				{
					if (compairList[i].Index[k]==command[0]-'0')
					{
						for (l=0;l<userDeck[position].Card.size();l++)
						{
							if (userDeck[position].Card[l].Order == compairList[i].Index[0])
							{
								for (m = 0; m < userDeck[position].Card[l].TopType.size(); m++)
								{
									cout << "使用英雄技能卡上方：" << skill[userDeck[position].Card[l].TopType[m]] << endl;
								}
							}
							//棄牌
							userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
							userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
						}
					}
						compairList[i].Index.erase(compairList[i].Index.begin()+k);
				}
				for (l=0;l<userDeck[position].Card.size();l++)
				{
					if (userDeck[position].Card[l].Order == command[0]-'0')
					{
						for (m=0;m<userDeck[position].Card[l].BelowType.size();m++)
						{
							//呼叫命令
							cout << "使用英雄技能卡下方：" << skill[userDeck[position].Card[l].BelowType[m]] << endl;
						}
					//棄牌
					userDeck[position].disCardDeck.push_back(userDeck[position].Card[l]);
					userDeck[position].Card.erase(userDeck[position].Card.begin() + l);
					}
				}
				compairList[i].Index.clear();
			}
		}
		else if (compairList[i].Icon >='a' &&compairList[i].Icon <='z') //敵人方
		{
			for (j=0;j<enemyDeck.size();j++)
			{
				if (enemyDeck[j].Icon == compairList[i].Icon)
					position = j;
			}
			cout << "敵人出牌" << endl;
			for (l = 0; l < enemyDeck[position].Card.size(); l++)
			{
				if (enemyDeck[position].Card[l].Order == compairList[i].Index[0])
				{
					for (m = 0; m < enemyDeck[position].Card[l].Type.size(); m++)
					{
						//呼叫命令
						cout << "使用敵人下方：" << skill[enemyDeck[position].Card[l].Type[m]] << endl;
					}
					//棄牌
					enemyDeck[position].disCardDeck.push_back(enemyDeck[position].Card[l]);
					enemyDeck[position].Card.erase(enemyDeck[position].Card.begin() + l);
				}
			}		
		}
	}
}

