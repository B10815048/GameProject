#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Management.h"
#include <regex>
using namespace std;
////////////////////////////////////////////////////////////
//��ܨϥΨ���G
void Management::seletUser()
{
	int int_buffer;
	std::string string_buffer;
	int i, j, k;
	int p1, p2;
	////////////////////////////////////////////////////////////
	//���b�B�z�G
	std::regex form("^[2-4]{1}$");
	std::string input;
	std::cout << "�п�J�X������ƶq:" << std::endl;
	while (std::cin >> input)
	{
		if (std::regex_match(input, form))
			break;
		else
			std::cout << "���s��J�G" << std::endl;
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
				std::cout << "���s��J�G" << std::endl;
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
						std::cout << "�䤣��ӵP" << std::endl;
					else
					{
						if (findCardPosition(userDeck[i], int_buffer) == -1)
						{
							userDeck[i].name = user[p1].name;
							userDeck[i].Card.push_back(user[p1].Card[p2]);
							break;
						}
						else
							std::cout << "���ƪ��P��" << std::endl;
					}
				}
				else
					std::cout << "��J���~" << std::endl;
			}
		}
	}
}
////////////////////////////////////////////////////////////
//����@�^�X�G
void Management::runGAME()
{
	userDeck.clear();
	enemyDeck.clear();
	user.clear();
	enemy.clear();
	map.clear();
	checkMap.clear();
	std::string input = "";
	Point p;
	round_count = 0;
	loadUserfile();
	loadEnemyfile();
	seletUser();
	loadMapfile();
	getxy(p);
	printMap(p);
	printEnemy(p);
	seletPoint();
	while (!victoryCheck() && userDeck.size() > 0)
	{
		playCard();
		resetShield();
	}
	if (victoryCheck())
		std::cout << "character win~" << std::endl;
	else
		std::cout << "monster win~" << std::endl;
}
////////////////////////////////////////////////////////////
//��ܰ_�l�I�G
void Management::seletPoint()
{
	Point p;
	Point tmp;
	int count;
	std::vector <Point> point;
	std::string command;
	std::regex form1("^[wasd]+$");
	std::regex form2("e");
	for (int i = 0; i < this->userDeck.size(); i++)
	{
		std::cout << "��ܨ����m�G" << std::endl;
		while (std::cin >> command)
		{
			if (std::regex_match(command, form1) || std::regex_match(command, form2))
				break;
			else
				std::cout << "���~��J�G" << std::endl;
		}
		point.clear();
		bool haveFind = false;

		for (int j = 0; j < this->height; j++)
		{
			for (int k = 0; k < this->width; k++)
			{
				if (this->map[j][k] == '*')
				{
					tmp.x = k;
					tmp.y = j;
					haveFind = true;
					break;
				}
			}
			if (haveFind)
				break;
		}
		userDeck[i].P = tmp;
		for (int j = 0; j < command.size(); j++)
		{
			if (command[j] == 'w' && (map[tmp.y - 1][tmp.x] == '_' || map[tmp.y - 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y - 1 })
						count++;
				}
				if (count == 0)
					tmp.y--;
			}

			else if (command[j] == 's' && (map[tmp.y + 1][tmp.x] == '_' || map[tmp.y + 1][tmp.x] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x, tmp.y + 1 })
						count++;
				}
				if (count == 0)
					tmp.y++;
			}
			else if (command[j] == 'a' && (map[tmp.y][tmp.x - 1] == '_' || map[tmp.y][tmp.x - 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x - 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x--;
			}
			else if (command[j] == 'd' && (map[tmp.y][tmp.x + 1] == '_' || map[tmp.y - 1][tmp.x + 1] == '*'))
			{
				count = 0;
				for (int k = 0; k <= i; k++)
				{
					if (userDeck[k].P == Point{ tmp.x + 1, tmp.y })
						count++;
				}
				if (count == 0)
					tmp.x++;
			}
			point.push_back(tmp);
		}

		for (int j = point.size(); j > 0; j--)
		{
			count = 0;
			for (int k = 0; k <= i; k++)
			{
				if (userDeck[k].P == point[j - 1])
					count++;
			}
			if (count == 0)
			{
				tmp = point[j - 1];
				break;
			}
		}
		if (userDeck[i].P == tmp)
		{
			haveFind = false;
			map[tmp.y][tmp.x] = '1';
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '_')
					{
						this->map[j][k] = '*';
						tmp.x = k;
						tmp.y = j;
						haveFind = true;
						break;
					}
				}
				if (haveFind)
					break;
			}
		}
		else
		{
			userDeck[i].P = tmp;
		}
		if (i == userDeck.size() - 1)
		{
			for (int j = 0; j < this->height; j++)
			{
				for (int k = 0; k < this->width; k++)
				{
					if (this->map[j][k] == '*' || this->map[j][k] == '_')
						map[j][k] = '1';
				}
			}
		}
		getxy(p);
		printMap(p);
		printEnemy(p);
		for (int k = 0; k <= i; k++)
		{
			gotoxy(userDeck[k].P + p);
			std::cout << userDeck[k].Icon;
		}
		gotoxy({ p.x,p.y + height });

	}

}
////////////////////////////////////////////////////////////
//����@���X�P�G
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
	//��X�ӱ��Ƨ�
	printExecutionOrder();
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
					while (getline(cin, command))
					{
						if (std::regex_match(command, creatureCheck)) //��ܩҦ��ͪ����A
							printCreatureCheck();
						else if (std::regex_match(command, userCheck) && findCreatureDeckPosition(0, command[0]) != -1) //��ܫ��wuser���A
							printUserCheck(command[0]);
						else if (std::regex_match(command, play) && compairList[i].cardExist(command[0] - '0')) //��ܥd��
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
////////////////////////////////////////////////////////////
