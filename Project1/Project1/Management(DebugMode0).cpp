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
		std::cout << "�ͪ���ʰ��涶��:" << std::endl;
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
	std::cout << "�i�԰��T������ Battle Message Record�j";
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + 15 - i });
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
	Point p, orginalP;
	getxy(orginalP);
	if (width < 47)
		p.x = 47;
	else
		p.x = width + 2;
	p.y = 3;
	gotoxy(p);
	std::cout << "�i�԰��T������ Battle Message Record�j";
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + 15 - i });
		for (int j = 0; j < battleMsg[battleMsg.size() - i - 1].size() + 2; j++)
			std::cout << " ";
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
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	int index = 0;
	int colorIndex = -1;
	int cardIndex = 0;
	char input = ' ';
	bool match = false;
	Point p, p2;
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
			if (index == 0 || index == 3)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[0]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 0);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 1);
				break;
			}
			else if (index == 1 || index == 2)
			{
				int i = findCompairCardDexPosition(userDeck[position].Icon);
				int p1 = findCardPosition(compairList[i], compairList[i].Index[1]);
				rePrint();
				usingEffect(userDeck[position], compairList[i].Index[p1], 1);
				usingEffect(userDeck[position], compairList[i].Index[1 - p1], 0);
				break;
			}
		}
		if (index < 0) index = 3;
		if (index > 3) index = 0;
		int j = findCompairCardDexPosition(userDeck[position].Icon);
		std::cout << (index == 0 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[0] << " �W�ޯ�" << endl;
		std::cout << (index == 1 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[0] << " �U�ޯ�" << endl;
		std::cout << (index == 2 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[1] << " �W�ޯ�" << endl;
		std::cout << (index == 3 ? ">> " : "   ");
		std::cout << "�s�� " << compairList[j].Index[1] << " �U�ޯ�" << endl;

	} while (input = _getch());
	rePrint();
}
////////////////////////////////////////////////////////////
//�s�WGUI����(debugmode 0 �M��)
void Management::printGUI()
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
				target = chooseUser();
				printUserCard(target);
				std::cout << "���U���N��H�~��" << std::endl;
				_getch();
				rePrint();
				std::cout << "��ܨ����ʪ��^�X:" << std::endl;
			}
			else if (index == 2)
			{
				target = chooseUser();
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
//��ܥd��(debugmode 0 �M��)
void Management::printCardGUI(User &user)
{
	int position = findCreatureDeckPosition(0, user.Icon);	
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	int index = 0;
	int colorIndex = -1;
	char input = ' ';
	bool match = false;
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
				colorIndex = index;
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
				SetColor(4);
			else
				SetColor();
			std::cout << "������  ";
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(4);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "���d��  " : "������  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(4);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "���P��  " : "����  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(4);
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
// �Ʈ�
/*void Management::printCardGUI(User& user)
{
	int position = findCreatureDeckPosition(0, user.Icon);
	for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		std::cout << "������  ";
	std::cout << endl;
	for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		std::cout << (i < userDeck[position].Card.size() ? "���d��  " : "������  ");
	std::cout << endl;
	for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		std::cout << (i < userDeck[position].Card.size() ? "���P��  " : "����  ");
	std::cout << endl;
	for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		std::cout << "������  ";
	std::cout << endl;
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	int index = 0;
	char input = ' ';
	bool match = false;
	Point p, p2;
	getxy(p);
	do {
		gotoxy(p);
		if (input == 'a' || input == 'A')
			index -= 1;
		else if (input == 'd' || input == 'D')
			index += 1;
		if (input == 13)
		{

		}
		if (index < 0) index = userDeck[position].Card.size();
		if (index > userDeck[position].Card.size()) index = 0;
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
}*/
////////////////////////////////////////////////////////////
//��ܨ���(debugmode 0 �M��)
User Management::chooseUser()
{
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
			if (match)
				continue;
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
	} while (input = _getch());
	rePrint();
}