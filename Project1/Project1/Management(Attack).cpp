#include "Management.h"
#include <cmath>
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
bool Management::shootRange(Point start, Point end, int n, int camp)
{

}
