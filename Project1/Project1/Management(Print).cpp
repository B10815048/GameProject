#include "Management.h"
#include <algorithm>
////////////////////////////////////////////////////////////
//�o���X��Ц�m�G
void Management::getxy(Point& p)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	p.x = csbi.dwCursorPosition.X;
	p.y = csbi.dwCursorPosition.Y;
};
////////////////////////////////////////////////////////////
//��ʿ�X��Ц�m�G
void Management::gotoxy(Point p)
{
	COORD point;
	point.X = p.x, point.Y = p.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
};
////////////////////////////////////////////////////////////
//���L�a�ϡG
void Management::printMap(Point p)
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (map[i][j] == '0' || map[i][j] == 'x' || map[i][j] == 'y' || map[i][j] == '4')
				std::cout << " ";
			else
				std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
////////////////////////////////////////////////////////////
//���L�ϥΪ̡G
void Management::printUser(Point p)
{
	for (int i = 0; i < userDeck.size(); i++)
	{
		if (map[userDeck[i].P.y][userDeck[i].P.x] == '1'|| checkDoor(userDeck[i].P))
		{
			gotoxy({ p.x + userDeck[i].P.x,p.y + userDeck[i].P.y });
			std::cout << userDeck[i].Icon;
		}
	}
	gotoxy({ p.x,p.y + height });
}
////////////////////////////////////////////////////////////
bool SortByIndex(CardTable& a, CardTable& b);
////////////////////////////////////////////////////////////
//���L��e���⪺�d�P�G
void Management::printUserCard(int position)
{
	std::string skill[] = { "move", "heal", "shield", "attack","range" };
	std::sort(userDeck[position].Card.begin(), userDeck[position].Card.end(), SortByIndex);
	for (int j = 0; j < userDeck[position].Card.size(); j++)
	{
		std::cout << "�s��: " << userDeck[position].Card[j].Order << " ; �ӱ�: ";
		if (userDeck[position].Card[j].DEX < 10)
			std::cout << "0";
		std::cout << userDeck[position].Card[j].DEX << " ; ";
		std::cout << "�W�ޯ�: ";
		for (int k = 0; k < userDeck[position].Card[j].TopType.size(); k++)
			std::cout << skill[userDeck[position].Card[j].TopType[k]] << " " << userDeck[position].Card[j].TopAbilityValue[k] << " ";
		std::cout << "; �U�ޯ�: ";
		for (int k = 0; k < userDeck[position].Card[j].BelowType.size(); k++)
			std::cout << skill[userDeck[position].Card[j].BelowType[k]] << " " << userDeck[position].Card[j].BelowAbilityValue[k] << " ";
		std::cout << std::endl;
	}
}
////////////////////////////////////////////////////////////
//���L�Ǫ��G
void Management::printEnemy(Point p)
{
	for (int i = 0; i < enemyDeck.size(); i++)
	{
		if (map[enemyDeck[i].P.y][enemyDeck[i].P.x] == '1' || checkDoor(enemyDeck[i].P))
		{
			gotoxy({ p.x + enemyDeck[i].P.x,p.y + enemyDeck[i].P.y });
			std::cout << enemyDeck[i].Icon;
		}
	}
	gotoxy({ p.x,p.y + height });
}
////////////////////////////////////////////////////////////
//���L�ͪ����A��G
void Management::printCreatureCheck()
{
	int i;
	for (i = 0; i < userDeck.size(); i++)
		std::cout << userDeck[i].Icon << "-hp: " << userDeck[i].HP << ", shield: " << userDeck[i].Shield << std::endl;
	for (i = 0; i < enemyDeck.size(); i++)
	{
		if (checkSpace(enemyDeck[i].P))
			std::cout << enemyDeck[i].Icon << "-hp: " << enemyDeck[i].HP[enemyDeck[i].Type] << ", shield: " << enemyDeck[i].Shield << std::endl;
	}
}
////////////////////////////////////////////////////////////
//���L�ϥΪ̪��A��G
void Management::printUserCheck(char icon)
{
	int position;
	position = findCreatureDeckPosition(0, icon);
	sort_Usercard(position);
	sort_discard(position);
	std::cout << "hand: ";
	for (int j = 0; j < userDeck[position].Card.size(); j++)
	{
		std::cout << userDeck[position].Card[j].Order;
		if (j != userDeck[position].Card.size() - 1)
			std::cout << ", ";
	}
	std::cout << "; discard: ";
	for (int j = 0; j < userDeck[position].disCardDeck.size(); j++)
	{
		std::cout << userDeck[position].disCardDeck[j].Order;
		if (j != userDeck[position].disCardDeck.size() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}
////////////////////////////////////////////////////////////
//���L�ͪ����涶�ǡG
void Management::printExecutionOrder()
{
	Point p;
	int i, position;
	bool haveSameName = false;
	std::vector<std::string> enemyNameList;
	for (i = 0; i < compairList.size(); i++)
	{
		if (compairList[i].skip)
			continue;
		if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z')
		{
			std::cout << compairList[i].Icon << " ";
			position = findCreatureDeckPosition(0, compairList[i].Icon);
			sort_Usercard(position);
			sort_discard(position);
		}			
		else
		{			
			haveSameName = false;
			position = findCreatureDeckPosition(1, compairList[i].Icon);
			for (int j = 0; j < enemyNameList.size(); j++)
			{
				if (enemyNameList[j] == enemyDeck[position].name)
					haveSameName = true;
			}
			if (!haveSameName)
				enemyNameList.push_back(enemyDeck[position].name);
			else
				continue;
			//sort_Enemycard();
			position = findCreatureDeckPosition(1, compairList[i].Icon);
			std::cout << enemyDeck[position].name << " ";
		}
		if (compairList[i].Dex[0] < 10)
			std::cout << "0";
		std::cout << compairList[i].Dex[0] << " ";
		if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z' && compairList[i].Index[1]!=-1)
			std::cout << compairList[i].Index[0] << " " << compairList[i].Index[1] << std::endl;
		else if (compairList[i].Icon >= 'A' && compairList[i].Icon <= 'Z')
			std::cout << compairList[i].Index[0] << std::endl;
		else
		{
			int p1, p2;
			p1 = findCreatureDeckPosition(1, compairList[i].Icon);
			p2 = findCardPosition(enemyDeck[p1], compairList[i].Index[0]);
			if (p2 == -1)
			{
				std::cout << std::endl;
				continue;
			}
			for (int k = 0; k < enemyDeck[p1].Card[p2].Type.size(); k++)
			{
				if (enemyDeck[p1].Card[p2].Type[k] == 0)
					std::cout << "move ";
				else if (enemyDeck[p1].Card[p2].Type[k] == 1)
					std::cout << "heal ";
				else if (enemyDeck[p1].Card[p2].Type[k] == 2)
					std::cout << "shield ";
				else if (enemyDeck[p1].Card[p2].Type[k] == 3)
					std::cout << "attack ";
				else if (enemyDeck[p1].Card[p2].Type[k] == 4)
					std::cout << "range ";
				std::cout << enemyDeck[p1].Card[p2].AbilityValue[k] << " ";
			}
			std::cout << std::endl;
		}
	}
}
////////////////////////////////////////////////////////////
