#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Management.h"
#include <regex>
#include <conio.h>
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
	while (getline (cin,input))
	{
		if (std::regex_match(input, form))
			break;
		else
			std::cout << "���s��J�G" << std::endl;
	}
	int_buffer = stoi(input);
	userDeck.resize(int_buffer);
	////////////////////////////////////////////////////////////
	if (debugMode == 0)
		cout << "��J�X�����⪺�d�P,�榡:<�W��> <�d�P�N�X1> <�d�P�N�X2> <�d�P�N�X3>...." << endl;
	for (i = 0; i < userDeck.size(); i++)
	{
		while (getline(cin,string_buffer))
		{			
			if (string_buffer.size() == 0)
				continue;
			stringstream ss(string_buffer);
			ss >> string_buffer;
			p1 = findCreaturePosition(0, string_buffer);
			if (p1 == -1)
			{
				std::cout << "���s��J�G" << std::endl;
			}
			else
			{
				userDeck[i] = user[p1];
				userDeck[i].Camp = 0;
				userDeck[i].Icon = 65 + i;
				userDeck[i].Card.clear();
				string_buffer = "^";
				for (j = 0; j < userDeck[i].CardOnHand; j++)
						string_buffer = string_buffer + " [0-9]+";
				string_buffer = string_buffer + "$";
				getline(ss, input);
				form = (string_buffer);
				if (!std::regex_match(input, form))
				{
					std::cout << "�d�P�ƶq���X" << std::endl;
					continue;
				}
				else
				{
					stringstream s1(input);
					for (j = 0; j < userDeck[i].CardOnHand; j++)
					{
						s1 >> input;
						int_buffer = stoi(input);
						p2 = -1;
						for (k = 0; k < user[p1].Card.size(); k++)
						{
							if (user[p1].Card[k].Order == int_buffer)
								p2 = k;
						}
						if (p2 == -1)
						{
							std::cout << "�d�P���s�b" << std::endl;
							break;
						}
						else
						{
							if (findCardPosition(userDeck[i], int_buffer) == -1)
							{
								userDeck[i].name = user[p1].name;
								userDeck[i].Card.push_back(user[p1].Card[p2]);
							}
							else
							{
								std::cout << "���ƪ��d�P" << std::endl;
								break;
							}
						}
					}
					if (userDeck[i].Card.size() != userDeck[i].CardOnHand)
						continue;
				}
				break;
			}
		}	
	}
}
////////////////////////////////////////////////////////////
//����C���G
void Management::runGAME()
{
	Point p;
	seletUser();
	loadMapfile();
	if (debugMode == 0)
		system("cls");		
	getxy(p);
	printMap(p);
	printEnemy(p);
	seletPoint();
	resetRange();
	while (!victoryCheck() && userDeck.size() > 0)
	{
		playCard();
		resetShield();
	}
	if (victoryCheck())
		std::cout << "character win~" << std::endl;
	else
		std::cout << "monster win~" << std::endl;
	resetGame();
}
////////////////////////////////////////////////////////////
//���L����(debugmode 0 �M��)
void Management::rePrint()
{
	Point p;
	system("cls");
	std::cout << "============================================" << std::endl;
	std::cout << "                 GloomHaven                 " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;	
	getxy(p);
	printBattleMsg();
	gotoxy(p);
	printMap(p);
	printEnemy(p);
	printUser(p);	
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Round " << round_count << " " << roundStatue << std::endl;
	if (compairList.size() != 0)
	{
		std::cout << "�ͪ���ʰ��涶��:" << endl;
		printExecutionOrder();
	}		
	std::cout << "============================================" << std::endl;
}
////////////////////////////////////////////////////////////
//�L�X�԰��T��(debugmode 0 �M��)
void Management::printBattleMsg()
{
	int battleMsg_count = 0;
	Point p;
	Point orginalP;
	getxy(orginalP);
	if (width < 47)
		p.x = 47;
	else
		p.x = width + 2;
	p.y = 3;
	gotoxy(p);
	cout << "�i�԰��T������ Battle Message Record�j";
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + 15 - i });
		if(i == 0)
			cout << "> " << battleMsg[battleMsg.size() - i - 1];
		else
			cout << "| " << battleMsg[battleMsg.size() - i - 1];
	}	
	gotoxy(orginalP);
}
////////////////////////////////////////////////////////////
//�s�W�԰��T��(debugmode 0 �M��)
void Management::addBattleMsg(string msg)
{
	Point p, orginalP;
	getxy(orginalP);
	if (width < 47)
		p.x = 47;
	else
		p.x = width + 2;
	p.y = 3;
	gotoxy(p);
	cout << "�i�԰��T������ Battle Message Record�j";
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + 15 - i });
		for (int j = 0; j < battleMsg[battleMsg.size() - i - 1].size()+2; j++)
			cout << " ";
	}
	gotoxy(orginalP);
	battleMsg.push_back(msg);
	if (battleMsg.size() > 15)
		battleMsg.erase(battleMsg.begin());
	printBattleMsg();
}
////////////////////////////////////////////////////////////
//�s�WGUI����(debugmode 0 �M��)
void Management::printGUI(int position)
{
	int index = 0;
	char input = ' ';
	Point p;
	std::string menu[3] = { "�d�ݩҦ�������","�d�ݷ�e����d�P","���O��J�Ҧ�       " };
	getxy(p);
	do {
		gotoxy(p);
		std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
		for (int j = 0; j < 3; j++)
			cout << "   " << menu[j] << endl;
		gotoxy({ p.x,p.y + 1 });
		if (input == 'w' || input == 'W')
			index -= 1;
		else if (input == 's' || input == 'S')
			index += 1;
		if (input == 13)
		{
			if (index == 0)
			{
				printCreatureCheck();
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
			}
			else if (index == 1)
			{
				printUserCard(userDeck[position]);
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
			}
			else if (index == 2)
			{
				rePrint();
				break;
			}
		}
		if (index < 0) index = 2;
		if (index > 2) index = 0;
		for (int j = 0; j < 3; j++)
		{
			if (j == index) cout << ">> ";
			else cout << "   ";
			cout << menu[j] << endl;
		}
	} while (input = _getch());
	rePrint();
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
	std::regex form2("^e$");
	for (int i = 0; i < this->userDeck.size(); i++)
	{
		if(debugMode == 0)
			std::cout << "��ܨ����m�G" << std::endl;
		while (getline(cin , command))
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
		if(debugMode == 0)
			system("cls");
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
	int i, j;
	string command;
	CompairCardDex tmp;
	std::regex play("^[0-9]{1}[ud]{1}$");
	std::regex userCheck("^[A-D]{1} check$");
	std::regex creatureCheck("check");
	char icon;
	// �C���}�l
	roundStatue = "����X�P���q";
	round_count += 1;
	compairList.clear();
	if (debugMode == 0)
		rePrint();
	else
		std::cout << "round " << round_count << ":" << std::endl;
	// ���a�X�P
	userPlayCards();
	//�ĤH�X�P
	enemyPlayCards();
	//�Ҧ��P�Ƨ�
	sort_compairList();
	//��X�ӱ��Ƨ�
	printExecutionOrder();
	if (debugMode == 0)
		rePrint();
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
					if (debugMode == 0)
					{
						printGUI(position);
						std::cout << "���� "<< userDeck[position].Icon << " ��� " << compairList[i].Index[0] << " �M " << compairList[i].Index[1] << " ���d���ĪG,�榡:<�d���N�X><u/d>" << std::endl;
					}										
					else
						std::cout << compairList[i].Icon << "'s turn: card " << compairList[i].Index[0] << " " << compairList[i].Index[1] << std::endl;
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
					if(debugMode == 0)
						cout << "�^��" << userDeck[position].Icon << "����" << endl;
					if (debugMode == 1)
						cout << userDeck[position].Icon << "'s turn: card -1" << endl;
					rest(userDeck[position]);
					if (!debugMode)
						rePrint();
				}
			}
			else if (compairList[i].Icon >= 'a' && compairList[i].Icon <= 'z') //�ĤH��
			{
				position = findCreatureDeckPosition(1, compairList[i].Icon);
				if(debugMode == 0)
					cout << "�ĤH" << enemyDeck[position].Icon << "�X�P" << endl;
				usingEffect(enemyDeck[position], compairList[i].Index[0]);
			}
		}
	}
	// �C�������p��
	doorOpenCheck();
}
////////////////////////////////////////////////////////////
//���]�C�����
void Management::resetGame()
{
	userDeck.clear();
	enemyDeck.clear();
	compairList.clear();
	map.clear();
	round_count = 0;
	battleMsg.clear();	
	if (debugMode == 0)
	{
		std::cout << "���U���N��H�~��" << std::endl;
		_getch();
		system("cls");
	}		
}