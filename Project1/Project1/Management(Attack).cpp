#include "Management.h"
#include <cmath>
#include <iomanip>
bool  Management::oneGapCheck(int x, float y1, float y2)
{
	int j;
	for (j =ceil(y1); j != floor(y2); j = j + (floor(y2) - ceil(y1)) / abs(floor(y2) - ceil(y1)))
		map[j-1][x] = '2';
	return true;
}
bool Management::viewableRange(Point start, Point end)
{
	start = {5,7};
	end = { 4,10};
	int i,j;
	float a, gap;
	if (start.x != end.x)
	{
		a = (float)(end.y-start.y)/ abs(end.x-start.x);
		gap = 0.5 + start.y;
		oneGapCheck(start.x, gap+ (a/2),gap );
		gap = gap + (a/2) ;
		i = start.x;
		while (i != end.x - (end.x - start.x) / abs(end.x - start.x))
		{
			oneGapCheck(i + (end.x - start.x) / abs(end.x - start.x), gap+a, gap);
			i = i + (end.x - start.x) / abs(end.x - start.x);
			gap = a + gap;
		}
		oneGapCheck(end.x, gap + (a / 2), gap);
	}
	else
	{
		for (i = start.y; i != end.y; i = i + (end.y - start.y) / abs(end.y - start.y))
			oneGapCheck(start.x, i + (end.y - start.y) / abs(end.y - start.y), i);
		oneGapCheck(start.x, i + (end.y - start.y) / abs(end.y - start.y), i);
	}
	printMap(start);
	return true;
}

bool Management::shootRange(Point start, Point end, int step, int camp)
{
	int i, j;
	if (map[end.y][end.x] != '1')
		return false;

	checkMap.resize(height);
	for (i = 0; i < checkMap.size(); i++)
		checkMap[i].resize(width);
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == '3' || map[i][j] == '0' || (enemyOnPoint({ j,i }, camp)!=0 && !(end == Point{ j, i })))
			{
				checkMap[i][j] = -1;
			}
			else
				checkMap[i][j] = -2;
		}
	}
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			std:: cout << std::setw(3) << checkMap[i][j];
		}
		std::cout << std::endl;
	}
	checkMap[start.y][start.x] = 0;
	viewR(start, 0);
	viewU(start, 0);
	viewD(start, 0);
	viewL(start, 0);
	int n = 0;
	while (checkMap[end.y][end.x] <= 0)
	{
		n++;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (checkMap[i][j] == n)
				{
					viewR({ j, i }, n);
					viewU({ j, i }, n);
					viewD({ j, i }, n);
					viewL({ j, i }, n);
				}
			}
		}
	}
	std::cout << std::endl;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			std::cout << std::setw(3) << checkMap[i][j];
		}
		std::cout << std::endl;
	}
	checkMap[start.y][start.x] = 0;
	std::cout << checkMap[end.y][end.x] << std::endl;
}
//////////////////////////////////////////////////////////////
//«ô³X¥k°¼ : 
int Management::viewR(Point start, int n)
{
	if (checkMap[start.y][start.x + 1] == -1)
		return 0;
	else if (checkMap[start.y][start.x + 1] == -2)
	{
		checkMap[start.y][start.x + 1] = n + 1;
		return viewR({ start.x + 1,start.y }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//«ô³X¤W¤è : 
int Management::viewU(Point start, int n)
{
	if (checkMap[start.y - 1][start.x] == -1)
		return 0;
	else if (checkMap[start.y - 1][start.x] == -2)
	{
		checkMap[start.y - 1][start.x] = n + 1;
		return viewU({ start.x,start.y - 1 }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//«ô³X¤U¤è : 
int Management::viewD(Point start, int n)
{
	if (checkMap[start.y + 1][start.x] == -1)
		return 0;
	else if (checkMap[start.y + 1][start.x] == -2)
	{
		checkMap[start.y + 1][start.x] = n + 1;
		return viewD({ start.x,start.y + 1 }, n + 1);
	}
}
//////////////////////////////////////////////////////////////
//«ô³X¥ª°¼ : 
int Management::viewL(Point start, int n)
{
	if (checkMap[start.y][start.x - 1] == -1)
		return 0;
	else if (checkMap[start.y][start.x - 1] == -2)
	{
		checkMap[start.y][start.x - 1] = n + 1;
		return viewL({ start.x - 1,start.y }, n + 1);
	}
}
//////////////////////////////////////////////////////////////