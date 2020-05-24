#include "Management.h"
////////////////////////////////////////////////////////////
//得到輸出游標位置：
void Management::getxy(Point& p)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	p.x = csbi.dwCursorPosition.X;
	p.y = csbi.dwCursorPosition.Y;
};
////////////////////////////////////////////////////////////
//改動輸出游標位置：
void Management::gotoxy(Point p)
{
	COORD point;
	point.X = p.x, point.Y = p.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
};
////////////////////////////////////////////////////////////
//打印地圖：
void Management::printMap(Point p)
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (map[i][j] == '0' || map[i][j] == 'x' || map[i][j] == 'y' | map[i][j] == '4')
				std::cout << " ";
			else
				std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
////////////////////////////////////////////////////////////
//打印使用者：
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
//打印怪物：
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
//打印生物狀態表：
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
//打印使用者狀態表：
void Management::printUserCheck(char icon)
{
	int position;
	position = findCreatureDeckPosition(0, icon);
	sort_card(position);
	sort_discard(position);
	std::cout << "hand: ";
	for (int j = 0; j < userDeck[position].Card.size(); j++)
	{
		if (j == userDeck[position].Card.size() - 1)
			std::cout << userDeck[position].Card[j].Order << "; ";
		else
			std::cout << userDeck[position].Card[j].Order << ", ";
	}
	std::cout << "discard: ";
	for (int j = 0; j < userDeck[position].disCardDeck.size(); j++)
	{
		std::cout << userDeck[position].disCardDeck[j].Order;
		if (j != userDeck[position].disCardDeck.size() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}
////////////////////////////////////////////////////////////