// Map.c
#include <memory.h>

#define MaxDimension 100
int path[MaxDimension][MaxDimension];
int highestCity;

void	ClearPath()
{
	memset( path, 0, sizeof(int)* MaxDimension*MaxDimension );
}

void	AddValue( int x, int y, int dist )
{
	if ( x < 0 || x >= MaxDimension )
		return;
	if ( y < 0 || y >= MaxDimension )
		return;

	path[x][y] = dist;
	path[y][x] = dist;

	if ( x > highestCity )// hill climbing
		highestCity = x;
	if ( y > highestCity )
		highestCity = y;
}

void	InitPath()
{
	highestCity = 0;
	ClearPath();
}

void	AddDistancePath( int betweenStart, int betweenDest, int dist )
{

}