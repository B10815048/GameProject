#include "Management.h"
#include <conio.h>
#include <iomanip>
using namespace std;
void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
////////////////////////////////////////////////////////////
//��ܥD����(debugmode 0 �M��)
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
	SetColor(12);
	printEnemy(p);
	SetColor(11);
	printUser(p);
	SetColor();
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Round " << round_count << " " << roundStatue << std::endl;
	if (compairList.size() != 0)
	{
		std::cout << "�ͪ���ʰ��涶��:" << std::endl;
		printExecutionOrder();
	}
	std::cout << "============================================" << std::endl;
}
////////////////////////////////////////////////////////////
//�L�X�԰��T��(debugmode 0 �M��)
void Management::printBattleMsg()
{
	Point p, orginalP; // orgionalP = (0,0)
	getxy(orginalP);
	if (width < 47)
		p.x = 47;
	else
		p.x = width + 2;
	p.y = 3;	
	gotoxy(p);
	std::cout << "�i�԰��T������ Battle Message Record�j";
	// �M���ª�BattleMsg
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + height - i + 1});
		for (int j = 0; j < battleMsg[battleMsg.size() - i - 1].size() + 2; j++)
			std::cout << " ";
	}
	gotoxy(p);
	std::cout << "�i�԰��T������ Battle Message Record�j";
	// ���L�s��BattleMsg
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + height - i });
		if (i == 0)
			std::cout << "> " << battleMsg[battleMsg.size() - i - 1];
		else
			std::cout << "| " << battleMsg[battleMsg.size() - i - 1];
	}
	gotoxy(orginalP);
}
////////////////////////////////////////////////////////////
//�s�W�԰��T��(debugmode 0 �M��)
void Management::addBattleMsg(string msg)
{
	battleMsg.push_back(msg);
	if (battleMsg.size() > height)
		battleMsg.erase(battleMsg.begin());
	printBattleMsg();
}
////////////////////////////////////////////////////////////
//��ܥd�P�W�U�ޯ઺GUI����(debugmode 0 �M��)
void Management::printUseCardGUI(int position)
{
	int index = 0;
	char input = ' ';
	Point p;
	getxy(p);
	do {
		gotoxy(p);
		std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
		gotoxy({ p.x,p.y + 1 });
		if (input == 'w' || input == 'W')
			index -= 1;
		else if (input == 's' || input == 'S')
			index += 1;
		if (input == 13)
		{
			if (index == 0)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[0]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 0);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 1);
				break;
			}
			else if (index == 1)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[0]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 1);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 0);
				break;
			}
			else if (index == 2)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[1]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 0);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 1);
				break;
			}
			else if (index == 3)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[1]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 1);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 0);
				break;
			}
			else if (index == 4)
			{
				rePrint();
				printCreatureCheck();
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
			}
			else if (index == 5)
			{
				rePrint();
				User target = chooseUser(0);				
				printUserCard(target);
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "���� " << userDeck[position].Icon << " ����ʦ^�X:" << endl;
			}
		}
		if (index < 0) index = 5;
		if (index > 5) index = 0;
		int j = findCompairCardDexPosition(userDeck[position].Icon);
		std::cout << (index == 0 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[0] << " �W�ޯ�" << endl;
		std::cout << (index == 1 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[0] << " �U�ޯ�" << endl;
		std::cout << (index == 2 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[1] << " �W�ޯ�" << endl;
		std::cout << (index == 3 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[1] << " �U�ޯ�" << endl;
		std::cout << (index == 4 ? ">> " : "   ");
		std::cout << "�d�ݩҦ��ͪ����A" << endl;
		std::cout << (index == 5 ? ">> " : "   ");
		std::cout << "�j�M���w����d��" << endl;
	} while (input = _getch());
	rePrint();
}
////////////////////////////////////////////////////////////
//�C�^�X�}�l�ɪ�GUI����(debugmode 0 �M��)
void Management::printRoundGUI()
{
	int index = 0;
	char input = ' ';
	bool match = false;
	User target;
	Point p;
	std::string menu[3] = { "�d�ݩҦ��ͪ����A","�j�M���w����d��","��ܨ���M�d�P" };
	getxy(p);
	do {
		gotoxy(p);
		std::cout << "��ܨ����ʪ��^�X:" << std::endl;
		for (int j = 0; j < 3; j++)
			std::cout << "   " << menu[j] << endl;
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
				std::cout << "��ܨ����ʪ��^�X:" << std::endl;
			}
			else if (index == 1)
			{
				target = chooseUser(0);
				printUserCard(target);
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "��ܨ����ʪ��^�X:" << std::endl;
			}
			else if (index == 2)
			{
				target = chooseUser(1);
				break;
			}
		}
		if (index < 0) index = 2;
		if (index > 2) index = 0;
		for (int j = 0; j < 3; j++)
		{
			if (j == index) std::cout << ">> ";
			else std::cout << "   ";
			std::cout << menu[j] << endl;
		}
	} while (input = _getch());
	rePrint();
	printCardGUI(target);
}
////////////////////////////////////////////////////////////
//��ܨ�i�d����GUI����(debugmode 0 �M��)
void Management::printCardGUI(User &user)
{
	int position = findCreatureDeckPosition(0, user.Icon);	
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	int index = 0;
	int colorIndex = -1;
	char input = ' ';
	Point p, p2;
	getxy(p);
	do {
		gotoxy(p);
		// ���a�ʧ@
		if (input == 'a' || input == 'A')
			index -= 1;
		else if (input == 'd' || input == 'D')
			index += 1;
		if (input == 13)
		{
			// ����
			if (index == userDeck[position].Card.size())
			{
				if (userDeck[position].disCardDeck.size() < 2)
				{
					gotoxy(p2);
					std::cout << setw(160) << " " << endl;
					gotoxy(p2);
					std::cout << "��P��i�Ƥp��2,�п�ܥX�P" << std::endl;
					continue;
				}
				CompairCardDex tmp;
				tmp.Icon = userDeck[position].Icon;
				tmp.Dex[0] = 99;
				tmp.Dex[1] = 99;
				tmp.Index.push_back(-1);
				tmp.Index.push_back(-1);
				compairList.push_back(tmp);
				break;
			}
			if (colorIndex == index)
				colorIndex = -1;
			else if (colorIndex == -1)
			{
				if (userDeck[position].Card.size() < 2)
				{
					gotoxy(p2);
					std::cout << setw(160) << " " << endl;
					gotoxy(p2);
					std::cout << "��P�i�Ƥp��2,�п�ܪ���" << std::endl;
					continue;
				}
				colorIndex = index;
			}				
			else
			{
				CompairCardDex tmp;
				tmp.Icon = userDeck[position].Icon;
				tmp.Index.push_back(userDeck[position].Card[colorIndex].Order);
				tmp.Dex[0] = userDeck[position].Card[colorIndex].DEX;
				tmp.Index.push_back(userDeck[position].Card[index].Order);
				tmp.Dex[1] = userDeck[position].Card[index].DEX;
				compairList.push_back(tmp);
				break;
			}
		}
		if (index < 0) index = userDeck[position].Card.size();
		if (index > userDeck[position].Card.size()) index = 0;
		// �L�X�d��		
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << "������  ";
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "���d��  " : "������  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "���P��  " : "����  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << "������  ";
		}
		std::cout << endl;
		SetColor();
		// ��ܥd�����
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == index)
			{
				std::cout << "------" << endl;
				getxy(p2);
				std::cout << setw(160) << " " << endl;
				gotoxy(p2);
				if (i == userDeck[position].Card.size())
					std::cout << "����";
				else
				{
					std::cout << "�s��: " << userDeck[position].Card[index].Order << " �ӱ�: " << userDeck[position].Card[index].DEX << " �ĪG: " << "�W�ޯ�: ";
					for (int k = 0; k < user.Card[index].TopType.size(); k++)
						std::cout << skill[user.Card[index].TopType[k]] << " " << user.Card[index].TopAbilityValue[k] << " ";
					std::cout << "; �U�ޯ�: ";
					for (int k = 0; k < user.Card[index].BelowType.size(); k++)
						std::cout << skill[user.Card[index].BelowType[k]] << " " << user.Card[index].BelowAbilityValue[k] << " ";
				}
				std::cout << endl;
			}
			else
			{
				gotoxy({ p2.x + (i * 8),p2.y - 1 });
				std::cout << "      ";
			}
			std::cout << "  ";
		}
	} while (input = _getch());
	rePrint();
}
////////////////////////////////////////////////////////////
//��ܨ���(debugmode 0 �M��)
User Management::chooseUser(int mode)
{
	// mode 0 = �ˬd�d��, mode 1 = �X�P
	rePrint();
	int index = 0;
	char input = ' ';	
	Point p;
	getxy(p);
	do {		
		gotoxy(p);
		std::cout << "��ܨ���:" << std::endl;
		gotoxy({ p.x,p.y + 1 });
		if (input == 'a' || input == 'A')
			index -= 1;
		else if (input == 'd' || input == 'D')
			index += 1;
		if (input == 13)
		{		
			bool match = false;
			for (int j = 0; j < compairList.size(); j++)
			{
				if (compairList[j].Icon == userDeck[index].Icon)
					match = true;
			}
			if (match && mode == 1)
			{
				gotoxy({ p.x,p.y + 2 });
				std::cout << "������w�g�粒�d�P,�д��O��������!";
				continue;
			}				
			return userDeck[index];
		}				
		if (index < 0) index = userDeck.size() - 1;
		if (index >= userDeck.size()) index = 0;
		for (int i = 0; i < userDeck.size(); i++)
		{			
			if (i == index) std::cout << ">> ";
			else std::cout << "   ";
			std::cout << userDeck[i].Icon << " ";						
		}
		gotoxy({ p.x,p.y + 2 });
		std::cout << "                                    ";
	} while (input = _getch());
	rePrint();
}