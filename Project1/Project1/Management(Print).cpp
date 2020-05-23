#include "Management.h"

void Management::getxy(Point& p)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	p.x = csbi.dwCursorPosition.X;
	p.y = csbi.dwCursorPosition.Y;
};

void Management::gotoxy(Point p)
{
	COORD point;
	point.X = p.x, point.Y = p.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
};

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