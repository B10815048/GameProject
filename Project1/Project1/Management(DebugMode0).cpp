#include "Management.h"
#include <conio.h>
#include <iomanip>
#include <algorithm>
using namespace std;
void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
////////////////////////////////////////////////////////////
//顯示主介面(debugmode 0 專用)
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
		std::cout << "生物行動執行順序:" << std::endl;
		printExecutionOrder();
	}
	std::cout << "============================================" << std::endl;
}
////////////////////////////////////////////////////////////
//印出戰鬥訊息(debugmode 0 專用)
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
	std::cout << "【戰鬥訊息紀錄 Battle Message Record】";
	// 清除舊的BattleMsg
	for (int i = 0; i < battleMsg.size(); i++)
	{
		gotoxy({ p.x,p.y + height - i + 1});
		for (int j = 0; j < battleMsg[battleMsg.size() - i - 1].size() + 2; j++)
			std::cout << " ";
	}
	gotoxy(p);
	std::cout << "【戰鬥訊息紀錄 Battle Message Record】";
	// 重印新的BattleMsg
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
//新增戰鬥訊息(debugmode 0 專用)
void Management::addBattleMsg(string msg)
{
	battleMsg.push_back(msg);
	if (battleMsg.size() > height)
		battleMsg.erase(battleMsg.begin());
	printBattleMsg();
}
////////////////////////////////////////////////////////////
//選擇卡牌上下技能的GUI介面(debugmode 0 專用)
void Management::printUseCardGUI(int position)
{
	int index = 0;
	char input = ' ';
	Point p;
	getxy(p);
	do {
		gotoxy(p);
		std::cout << "角色 " << userDeck[position].Icon << " 的行動回合:" << endl;
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
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
				std::cout << "角色 " << userDeck[position].Icon << " 的行動回合:" << endl;
			}
			else if (index == 5)
			{
				rePrint();
				int target = chooseUser(0);				
				printUserCard(target);
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
				std::cout << "角色 " << userDeck[position].Icon << " 的行動回合:" << endl;
			}
		}
		if (index < 0) index = 5;
		if (index > 5) index = 0;
		int j = findCompairCardDexPosition(userDeck[position].Icon);
		std::cout << (index == 0 ? ">> " : "   ");
		std::cout << "編號 " << compairList[j].Index[0] << " 上技能" << endl;
		std::cout << (index == 1 ? ">> " : "   ");
		std::cout << "編號 " << compairList[j].Index[0] << " 下技能" << endl;
		std::cout << (index == 2 ? ">> " : "   ");
		std::cout << "編號 " << compairList[j].Index[1] << " 上技能" << endl;
		std::cout << (index == 3 ? ">> " : "   ");
		std::cout << "編號 " << compairList[j].Index[1] << " 下技能" << endl;
		std::cout << (index == 4 ? ">> " : "   ");
		std::cout << "查看所有生物狀態" << endl;
		std::cout << (index == 5 ? ">> " : "   ");
		std::cout << "搜尋指定角色卡片" << endl;
	} while (input = _getch());
	rePrint();
}
////////////////////////////////////////////////////////////
//每回合開始時的GUI介面(debugmode 0 專用)
void Management::printRoundGUI()
{
	int index = 0;
	char input = ' ';
	bool match = false;
	int target;
	Point p;
	std::string menu[3] = { "查看所有生物狀態","搜尋指定角色卡片","選擇角色和卡牌" };
	getxy(p);
	do {
		gotoxy(p);
		std::cout << "選擇角色行動的回合:" << std::endl;
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
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
				std::cout << "選擇角色行動的回合:" << std::endl;
			}
			else if (index == 1)
			{
				target = chooseUser(0);
				printUserCard(target);
				std::cout << "按下任意鍵以繼續" << std::endl;
				_getch();
				rePrint();
				std::cout << "選擇角色行動的回合:" << std::endl;
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
bool SortByIndex(CardTable& a, CardTable& b)
{
	return a.Order < b.Order;
}
////////////////////////////////////////////////////////////
//選擇兩張卡片的GUI介面(debugmode 0 專用)
void Management::printCardGUI(int position)
{
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	std::sort(userDeck[position].Card.begin(), userDeck[position].Card.end(), SortByIndex);
	int index = 0;
	int colorIndex = -1;
	char input = ' ';
	Point p, p2;
	getxy(p);
	do {
		gotoxy(p);
		// 玩家動作
		if (input == 'a' || input == 'A')
			index -= 1;
		else if (input == 'd' || input == 'D')
			index += 1;
		if (input == 13)
		{
			// 長休
			if (index == userDeck[position].Card.size())
			{
				if (userDeck[position].disCardDeck.size() < 2)
				{
					gotoxy(p2);
					std::cout << setw(160) << " " << endl;
					gotoxy(p2);
					std::cout << "棄牌堆張數小於2,請選擇出牌" << std::endl;
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
					std::cout << "手牌張數小於2,請選擇長休" << std::endl;
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
		// 印出卡片		
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << "■■■  ";
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "■卡■  " : "■長■  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << (i < userDeck[position].Card.size() ? "■牌■  " : "■休■  ");
		}
		std::cout << endl;
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == colorIndex)
				SetColor(10);
			else
				SetColor();
			std::cout << "■■■  ";
		}
		std::cout << endl;
		SetColor();
		// 顯示卡片資料
		for (int i = 0; i < userDeck[position].Card.size() + 1; i++)
		{
			if (i == index)
			{
				std::cout << "------" << endl;
				getxy(p2);
				std::cout << setw(160) << " " << endl;
				gotoxy(p2);
				if (i == userDeck[position].Card.size())
					std::cout << "長休";
				else
				{
					std::cout << "編號: " << userDeck[position].Card[index].Order << " 敏捷: " << userDeck[position].Card[index].DEX << " 效果: " << "上技能: ";
					for (int k = 0; k < userDeck[position].Card[index].TopType.size(); k++)
						std::cout << skill[userDeck[position].Card[index].TopType[k]] << " " << userDeck[position].Card[index].TopAbilityValue[k] << " ";
					std::cout << "; 下技能: ";
					for (int k = 0; k < userDeck[position].Card[index].BelowType.size(); k++)
						std::cout << skill[userDeck[position].Card[index].BelowType[k]] << " " << userDeck[position].Card[index].BelowAbilityValue[k] << " ";
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
//選擇角色(debugmode 0 專用)
int Management::chooseUser(int mode)
{
	// mode 0 = 檢查卡片, mode 1 = 出牌
	rePrint();
	int index = 0;
	char input = ' ';	
	Point p;
	getxy(p);
	do {		
		gotoxy(p);
		std::cout << "選擇角色:" << std::endl;
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
				std::cout << "此角色已經選完卡牌,請換別隻角色行動!";
				continue;
			}				
			return index;
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
////////////////////////////////////////////////////////////
//起始角色(debugmode 0 專用)
void Management::selectUserGUI(int n)
{
	system("cls");
	int index = 0, position;
	char input;
	int i, j, k;
	Point p;
	getxy(p);
	for (i = 0; i < n; i++)
	{
		input = ' ';
		do 
		{
			gotoxy(p);
			if (input == 'a' || input == 'A')
				index -= 1;
			else if (input == 'd' || input == 'D')
				index += 1;
			if (index < 0) index = user.size() - 1;
			if (index >= user.size()) index = 0;
			for (j = 0; j < user.size(); j++)
			{
				if (j == index) std::cout << ">> ";
				else std::cout << "   ";
				std::cout << user[j].name << " ";
			}
			cout << endl;
			if (input == 13)
			{
				cout << "選擇" << user[index].name << endl;
				position = index;
				index = 0;
				break;
			}
		} while (input = _getch());
		system("cls");
		printCardInfo(position);
	}
}
////////////////////////////////////////////////////////////
//顯示可選手牌(debugmode 0 專用)
void Management::printCardInfo(int position)
{
	system("cls");
	int index = 0;
	char input;
	int i, j, k;
	Point p;
	getxy(p);
	User tmp = user[position];
	User putIn = user[position];
	putIn.Card.clear();
	putIn.Camp = 0;
	putIn.Icon = 65 + userDeck.size();
	for (i = 0; i < tmp.CardOnHand; i++)
	{
		input = ' ';
		index = 0;
		do
		{
			gotoxy(p);
			if (input == 'w' || input == 'W')
				index -= 1;
			else if (input == 's' || input == 'S')
				index += 1;
			if (index < 0) index = tmp.Card.size() - 1;
			if (index >= tmp.Card.size()) index = 0;
			gotoxy(p);
			cout << "可選擇卡牌：" << endl;
			for (j = 0; j < tmp.Card.size(); j++)
			{
				std::cout << "   " << "Index：" << tmp.Card[j].Order;
				for (k = 0; k < tmp.Card[j].TopType.size(); k++)
				{
					std::cout << " " << getTypeName(tmp.Card[j].TopType[k]) << " " << tmp.Card[j].TopAbilityValue[k];
				}
				cout << " -";
				for (k = 0; k < tmp.Card[j].BelowType.size(); k++)
				{
					std::cout << " " << getTypeName(tmp.Card[j].BelowType[k]) << " " << tmp.Card[j].BelowAbilityValue[k];
				}
				cout << endl;
			}
			cout << "以選擇卡牌：" << endl;
			for (j = 0; j < tmp.disCardDeck.size(); j++)
			{
				std::cout << "   " << "Index：" << tmp.disCardDeck[j].Order;
				for (k = 0; k < tmp.disCardDeck[j].TopType.size(); k++)
				{
					std::cout << " " << getTypeName(tmp.disCardDeck[j].TopType[k]) << " " << tmp.disCardDeck[j].TopAbilityValue[k];
				}
				cout << "-";
				for (k = 0; k < tmp.disCardDeck[j].BelowType.size(); k++)
				{
					std::cout << " " << getTypeName(tmp.disCardDeck[j].BelowType[k]) << " " << tmp.disCardDeck[j].BelowAbilityValue[k];
				}
				cout << endl;
			}
			gotoxy({ p.x, p.y + 1 });
			for (k = 0; k < tmp.Card.size(); k++)
			{
				if (k == index) std::cout << ">> " << endl;
				else std::cout << "   " << endl;
			}
			cout << endl;
			if (input == 13)
			{
				system("cls");
				putIn.Card.push_back(tmp.Card[index]);
				tmp.disCardDeck.push_back(tmp.Card[index]);
				tmp.Card.erase(tmp.Card.begin() + index);
				break;
			}
		} while (input = _getch());
	}
	userDeck.push_back(putIn);
}
////////////////////////////////////////////////////////////
//回傳技能名稱
string Management::getTypeName(int input)
{
	if (input == 0)
		return "move";
	else if (input == 1)
		return "heal";
	else if (input == 2)
		return "shield";
	else if (input == 3)
		return "attack";
	else if (input == 4)
		return "range";
}
////////////////////////////////////////////////////////////
//選擇開始遊戲
void Management::startGame()
{
	system("cls");
	int index = 0;
	char input;
	int i, j;
	input = ' ';
	do
	{
		if (input == 'w' || input == 'W')
			index -= 1;
		else if (input == 's' || input == 'S')
			index += 1;
		if (index < 0) index = 1;
		if (index > 1) index = 0;
		gotoxy({0 ,0});
		cout << "****************" << endl;
		cout << "*   開始遊戲   *" << endl;
		cout << "*   離開遊戲   *" << endl;
		cout << "****************" << endl;
		for (i = 0; i < 2; i++)
		{
			gotoxy({ 1 ,i+1 });
			if (i == index) std::cout << ">> " << endl;
			else std::cout << "   " << endl;
		}
		cout << endl;
		if (input == 13 && index==0)
		{
			runGAME();
		}
		else if (input == 13 && index == 1)
		{
			return;
		}
	} while (input = _getch());
}
////////////////////////////////////////////////////////////
//回傳遊戲模式
bool Management::getMode()
{
	return debugMode;
}