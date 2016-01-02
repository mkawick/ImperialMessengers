#include "Global.h"
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <assert.h>

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
int	InterpretLineAndAddDistances(char* line, int lineNo, int numConnectionsExpected)
{
	int connectionId;
	char* ptr;
	char* end;
	int dist;
	connectionId = 0;

	for (ptr = line, end = ptr;; ptr = end, connectionId++) {

		while (*ptr == ' ' && *ptr != 0)// remove any spaces
			ptr++;
		if (*ptr == 'x' || *ptr == 'X')// normal
		{
			ptr += 2;// pass the x and the space following
			end += 2;
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

int 	ReadInFile(const char* name)
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
		if (numCities < 1 || numCities > MaxDimension)
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
		if (countLines > MaxDimension)
		{
			printf("ERROR: incorrect value for the number of connections\n");
			fclose(ptr_file);
			assert(0);
			return -1;
		}
		//printf("%s", buff);// testing only
		// actually handle the line and fill in the map
		numConnections = InterpretLineAndAddDistances(buff, countLines, countLines);
		if (countLines != numConnections)
		{
			printf("ERROR: incorrect number of connections on a single line of text, line: %s\n", buff);
			fclose(ptr_file);
			assert(0);
			return -1;
		}
	}
	fclose(ptr_file);
	if (countLines == 0)
	{
		printf("ERROR: incorrect value for the number of connections\n");
		assert(0);
		return -1;
	}

	if (countLines != numCities - 1)// number of lines of connections sould be less than the number of cities
	{
		printf("ERROR: incorrect number of connections\n");
		assert(0);
		return -1;
	}

	return 0;
}

//-------------------------------------------------------
