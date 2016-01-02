// Map.c
#include "global.h"
#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 

const int LargeNumber = 100000000;
int path[MaxDimension][MaxDimension];
int highestCity;

//-------------------------------------------------------

void	ClearPath()
{
	memset( path, InvalidLocation, sizeof(int)* MaxDimension*MaxDimension );
	for ( int i = 0; i < MaxDimension; ++i )
	{
		path[i][i] = 0;
	}
	highestCity = 0; 
}

//-------------------------------------------------------

void	AddDistancePath(int x, int y, int dist)
{
	if ( LargeNumber < dist )
	{
		printf("ERROR: input value is too large, please adjust the LargeNumber\n");
		assert(0);
	}
	if( dist < 0 )
	{
		printf("ERROR: input value is too small, nothing under 0 is allowable\n");
		assert(0);
	}
	if ( x < 0 || x >= MaxDimension ) // basic error prevention
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

//-------------------------------------------------------

void	InitPath()
{
	highestCity = 0;
	ClearPath();
}

//-------------------------------------------------------

void  WalkToNextTowns( int previousCity, int currentCity, int distancesFromFirstCity[MaxDimension], int trackingDistance ) // struct BeginEnd be[MaxDimension], 
{
	int testDistance;
	// calculate the distance from the currentCity to other cities plus the trackingDistance
	for ( int i=0; i<=highestCity; ++i )
	{
		if (i == previousCity ||
			i == currentCity ||
			path[currentCity][i] == InvalidLocation)
		{
			continue;
		}

		testDistance = trackingDistance + path[currentCity][i];
		if ( testDistance <= distancesFromFirstCity[i] )
		{
			distancesFromFirstCity[i] = testDistance;
			WalkToNextTowns(currentCity, i, distancesFromFirstCity, testDistance);
		}
	}
}

//-------------------------------------------------------

int	StartWalk()
{
	int i; 
	int biggestNumber;
	int distancesFromFirstCity[MaxDimension];
	for ( i = 0; i<MaxDimension; ++i )
		distancesFromFirstCity[i] = LargeNumber;

	// first we calculate the shortest distance between the first node and the rest
	for ( i = 0; i<=highestCity; ++i )
	{
		distancesFromFirstCity[i] = path[0][i];
	}
	for (i = 1; i <= highestCity; ++i)// don't start at 0
	{
		WalkToNextTowns(0, i, distancesFromFirstCity, distancesFromFirstCity[i]);
	}

	// now we have identified all of the distances, first we look for nodes not visited for an error.
	for ( i = 0; i <= highestCity; ++i )
	{
		if (LargeNumber == distancesFromFirstCity[i] ||
			distancesFromFirstCity[i] == InvalidLocation)
		{
			printf( "ERROR: not all cities are reachable\n");
			assert(0);
			return -1;
		}
	}
		
	// and then we find the largest integer which is the minimum distance to visit all nodes.
	
	biggestNumber = -1;
	for ( i = 1; i <= highestCity; ++i )// no need to test he first city
	{
		if (biggestNumber < distancesFromFirstCity[i])
			biggestNumber = distancesFromFirstCity[i];
	}

	return biggestNumber;
}

//-------------------------------------------------------

void	Init( const char* pathToAdjacencyMatrix )
{
	int shortestPathLength;
	if (ReadInFile( pathToAdjacencyMatrix ) == -1)
	{
		return;
	}
	// testing and validation
	//InitializeMapWithDefaultValues();
	//InitializeMapWithIsolatedIslandValues();

	shortestPathLength = StartWalk();
	printf("%d\n", shortestPathLength);
}