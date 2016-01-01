// Map.c
#include <memory.h>
#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <direct.h>

#pragma warning (disable:4996) // ms warning disable
#define MaxDimension 100
#define InvalidLocation -1
#define BufferSize 5000

const int LargeNumber = 100000000;
int path[MaxDimension][MaxDimension];
int highestCity;

//-------------------------------------------------------

void	ClearPath()
{
	memset( path, InvalidLocation, sizeof(int)* MaxDimension*MaxDimension );
	for ( int i = 0; i < MaxDimension; i++ )
	{
		path[i][i] = 0;
	}
	highestCity = 0; 
}

//-------------------------------------------------------

void	AddDistancePath(int x, int y, int dist)
{
	if (LargeNumber < dist)
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
	for( int i=0; i<=highestCity; ++i )
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
	for (i = 0; i<MaxDimension; ++i )
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
	for (i = 0; i <= highestCity; ++i)
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
	for (i = 0; i <= highestCity; ++i)
	{
		if (biggestNumber < distancesFromFirstCity[i])
			biggestNumber = distancesFromFirstCity[i];
	}

	return biggestNumber;
}

//-------------------------------------------------------

void	InitializeMapWithDefaultValues()
{
	ClearPath();

	AddDistancePath(0, 1, 50);

	AddDistancePath(0, 2, 30);
	AddDistancePath(1, 2, 5);

	AddDistancePath(0, 3, 100);
	AddDistancePath(1, 3, 20);
	AddDistancePath(2, 3, 50);

	AddDistancePath(0, 4, 10);
	//AddDistancePath( 1, 4, 20 );
	//AddDistancePath( 2, 4, 50 );
	AddDistancePath(3, 4, 10);
}

//-------------------------------------------------------

void	InitializeMapWithIsolatedIslandValues()
{
	ClearPath();

	AddDistancePath(0, 1, 50);

	AddDistancePath(0, 2, 30);
	AddDistancePath(1, 2, 5);

	AddDistancePath(0, 3, 100);
	AddDistancePath(1, 3, 20);
	AddDistancePath(2, 3, 50);

	AddDistancePath(0, 4, 10);
	AddDistancePath(3, 4, 10);

	AddDistancePath(5, 6, 10);
	AddDistancePath(6, 7, 10);

	AddDistancePath(8, 9, 10);
}

//-------------------------------------------------------

// string parsing routine looks for invalid characters and distances
int	InterpretLineAndAddDistances( const char* line, int lineNo, int numConnectionsExpected )
{
	int connectionId;
	const char* ptr;
	const char* end;
	int dist;
	connectionId = 0;
	
	for (ptr = line, end=ptr;; ptr = end, connectionId++) {
		
		while (*ptr == ' ' && *ptr != 0)// remove any spaces
			ptr++;
		if (*ptr == 'x' || *ptr == 'X')// normal
		{
			ptr+=2;// pass the x and the space following
			end+=2;
			dist = InvalidLocation;
			continue;
		}
		else
		{
			dist = strtol(ptr, &end, 10);
		}
		
		if (ptr == end)
			break;
		
		if (dist != InvalidLocation && 
			dist != 0)
		{
			AddDistancePath(lineNo, connectionId, dist);
		}
	}
	return connectionId;
}

//-------------------------------------------------------

int 	ReadInFile( const char* name )
{
	ClearPath();

	FILE *ptr_file;
	char buff[BufferSize];
	int numCities;
	int countLines;
	int numConnections;
	//getcwd(buff, BufferSize); // testing only
	if (strlen(name) < 5)// filename + extension
	{
		printf("ERROR: incorrect file name\n");
		assert(0);
		return -1;
	}

	ptr_file = fopen(name, "r");
	if (!ptr_file)
	{
		printf("ERROR: incorrect file name\n");
		assert(0);
		return -1;
	}

	if (fgets(buff, BufferSize, ptr_file) != NULL)
	{
		// interpet the first line as a count of the number of lines to come minus one.
		numCities = atoi(buff);
		if (numCities < 1 || numCities > MaxDimension )
		{
			printf("ERROR: incorrect value for the number of connections\n");
			fclose(ptr_file);
			assert(0);
			return -1;
		}
	}

	countLines = 0;
	while (fgets(buff, BufferSize, ptr_file) != NULL)
	{
		countLines++;
		if (countLines > MaxDimension )
		{
			printf("ERROR: incorrect value for the number of connections\n");
			fclose(ptr_file);
			assert(0);
			return -1;
		}
		//printf("%s", buff);// testing only
		// actually handle the line and fill in the map
		numConnections = InterpretLineAndAddDistances(buff, countLines, countLines);
		if (countLines != numConnections )
		{
			printf("ERROR: incorrect number of connections on a single line of text, line: %s\n", buff);
			fclose(ptr_file);
			assert(0);
			return -1;
		}
	}
	fclose(ptr_file);
	if( countLines == 0 )
	{
		printf("ERROR: incorrect value for the number of connections\n");
		assert(0);
		return -1;
	}

	if( countLines != numCities - 1 )// number of lines of connections sould be less than the number of cities
	{
		printf("ERROR: incorrect number of connections\n");
		assert(0);
		return -1;
	}
	
	return 0;
}

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