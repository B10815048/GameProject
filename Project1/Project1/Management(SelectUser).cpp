#include "Management.h"
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

void Management::seletUser()
{
	int int_buffer;
	std::string string_buffer;
	int i, j, k;
	int p1, p2;
	////////////////////////////////////////////////////////////
	//防呆處理：
	std::regex form("^[2-4]{1}$");
	std::string input;
	std::cout << "請輸入出場角色數量:" << std::endl;
	while (std::cin>>input)
	{
		if (std::regex_match(input, form))
			break;
		else
			std::cout << "重新輸入：" << std::endl;
	}
	int_buffer = stoi(input);
	userDeck.resize(int_buffer);
	////////////////////////////////////////////////////////////
	for (i = 0; i < userDeck.size(); i++)
	{
		while (std::cin >> string_buffer)
		{
			p1 = findCreaturePosition(0, string_buffer);
			if (p1 == -1)
			{
				std::cout << "重新輸入：" << std::endl;
			}
			else
			{
				userDeck[i] = user[p1];
				break;
			}	
		}
		userDeck[i].Camp = 0;
		userDeck[i].Icon = 65 + i;
		userDeck[i].Card.clear();
		form = ("^[0-9]+$");
		for (j = 0; j < userDeck[i].CardOnHand; j++)
		{
			while (std::cin >> input)
			{
				if (std::regex_match(input, form))
				{
					int_buffer = stoi(input);
					p2 = -1;
					for (k = 0; k < user[p1].Card.size(); k++)
					{
						if (user[p1].Card[k].Order == int_buffer)
							p2 = k;
					}
					if (p2 == -1)
						std::cout << "找不到該牌" << std::endl;
					else
					{
						if (findCardPosition(userDeck[i], int_buffer) == -1)
						{
							userDeck[i].name = user[p1].name;
							userDeck[i].Card.push_back(user[p1].Card[p2]);
							break;
						}
						else
							std::cout << "重複的牌組" << std::endl;
					}
				}
				else
					std::cout << "輸入錯誤" << std::endl;
			}
		}
	}
}