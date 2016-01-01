// Map.c
#include <memory.h>
#include <assert.h>
#include <conio.h>

#define MaxDimension 100
#define InvalidLocation -1
const int LargeNumber = 100000000;
int path[MaxDimension][MaxDimension];
int search[MaxDimension][MaxDimension];
int highestCity;

void	ClearPath()
{
	memset( path, InvalidLocation, sizeof(int)* MaxDimension*MaxDimension );
	for ( int i = 0; i < MaxDimension; i++ )
	{
		path[i][i] = 0;
	}
	highestCity = 0; 
}

void	ClearSearch()
{
	memset( search, -1, sizeof(int)* MaxDimension*MaxDimension );
}

void	AddValue( int x, int y, int dist )
{
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

void	AddDistancePath(int x, int y, int dist)
{
	AddValue(x, y, dist);
}

void	InitPath()
{
	highestCity = 0;
	ClearPath();
}

struct BeginEnd
{
	int begin, end, dist;
};

int	Walk1()
{
	int i, j;
	int totalPath;// a big number
	int shortestPath;
	int index;
	int whichPathChosen;
	struct BeginEnd be[100];

	index = 0; 
	totalPath = 0;
	whichPathChosen = 0;
	for ( i = 0; i < highestCity; i++ )
	{
		shortestPath = LargeNumber;
		//shortestPath = path[i][0];
		for ( j = 0; j <= highestCity; j++ )
		{
			if ( i == j )
				continue;
			if ( path[i][j] != InvalidLocation )
			{
				if ( path[i][j] < shortestPath )
					shortestPath = path[i][j];
				whichPathChosen = j;
			}

		/*	if ( path[j][i] != InvalidLocation )
			{
				if ( path[j][i] < shortestPath )
					shortestPath = path[j][i];
			}*/
		}
		if ( shortestPath == LargeNumber )
			return -1;// major problem.. no path
		be[index].dist = shortestPath;
		be[index].begin = i;
		be[index++].end = whichPathChosen;
		totalPath += shortestPath;
	}
	return totalPath;
}

int	IsAlreadyInList( struct BeginEnd be[MaxDimension], int index, int b, int e )
{
	for ( int i = 0; i < index; i++ )
	{
		if ( be[i].begin == b && be[i].end == e )
			return 1;
		if ( be[i].begin == e && be[i].end == b )
			return 1;
	}
	return 0;
}

int  Walk2()
{
	int i, j;
	int totalPath;
	int shortestPath;
	int whichPathChosen;
	int beIndex;
	struct BeginEnd be[MaxDimension];

	beIndex = 0;
	totalPath = 0;
	whichPathChosen = 0;

	for ( i = highestCity-1; i >= 0; i-- )
	{
		shortestPath = LargeNumber;
		for ( j = 0; j <= highestCity; j++ )
		{
			if ( i == j )
				continue;
			if ( path[i][j] != InvalidLocation )
			{
				if ( path[i][j] < shortestPath )
				{
					if ( IsAlreadyInList( be, beIndex, i, j ) == 0 )
					{
						shortestPath = path[i][j];
						whichPathChosen = j;
					}
				}
			}
		}
		if ( shortestPath == LargeNumber )
			return -1;// major problem.. no path to one node
		be[beIndex].dist = shortestPath;
		be[beIndex].begin = i;
		be[beIndex++].end = whichPathChosen;
	}

	// now that we have a list of shortes paths between cities, we should be able to add them
	// first, we need to collapse nodes that originate at the same location
	return totalPath;
}

int Walk3( int previousCity, int currentCity, int distancesFromFirstCity[MaxDimension], int trackingDistance ) // struct BeginEnd be[MaxDimension], 
{
	// calculate the distance from the currentCity to other cities plus the trackingDistance
	for( int i=0; i<=highestCity; ++i )
	{
		if (i == previousCity || i == currentCity || path[currentCity][i] == -1)
			continue;
		int testDistance = trackingDistance + path[currentCity][i];
		if ( testDistance <= distancesFromFirstCity[i] )
		{
			distancesFromFirstCity[i] = testDistance;
			Walk3(currentCity, i, distancesFromFirstCity, testDistance);
		}
	}
	return 0;
}

int	StartWalk()
{
	int i; 
	int biggestNumber;
	int distancesFromFirstCity[MaxDimension];
	for (i = 0; i<MaxDimension; ++i )
		distancesFromFirstCity[i] = LargeNumber;

	// first we calculate the shortest distance between the first node and the rest
	for ( i = 0; i<=highestCity; ++i )
	{
		distancesFromFirstCity[i] = path[0][i];
	}
	for (i = 1; i <= highestCity; ++i)// don't start at 0
	{
		Walk3(0, i, distancesFromFirstCity, distancesFromFirstCity[i]);
	}

	// now we have identified all of the distances, first we look for nodes not visited for an error.
	for (i = 0; i <= highestCity; ++i)
	{
		if (LargeNumber == distancesFromFirstCity[i])
			assert ( 0 );
	}
		
	// and then we find the largest integer which is the minimum distance to visit all nodes.
	
	biggestNumber = -1;
	for (i = 0; i <= highestCity; ++i)
	{
		if (biggestNumber < distancesFromFirstCity[i])
			biggestNumber = distancesFromFirstCity[i];
	}

	return biggestNumber;
}


void	Init()
{
	int shortestPathLength;
	ClearPath();
	ClearSearch();

	AddDistancePath( 0, 1, 50 );

	AddDistancePath( 0, 2, 30 );
	AddDistancePath( 1, 2, 5 );

	AddDistancePath( 0, 3, 100 );
	AddDistancePath( 1, 3, 20 );
	AddDistancePath( 2, 3, 50 );

	AddDistancePath( 0, 4, 10 );
	//AddDistancePath( 1, 4, 20 );
	//AddDistancePath( 2, 4, 50 );
	AddDistancePath( 3, 4, 10 );

	//shortest = Walk2();

	shortestPathLength = StartWalk();
	printf("path = %d long", shortestPathLength);
	getch();
}