#pragma once

#define InvalidLocation -1
#define BufferSize 5000
#define MaxDimension 100

// ms warning disable for newer versions of ansi functions
#pragma warning (disable:4996) 

// I decided that since I have only have a few functions that 
// having separate headerswas overkill

// Map.c
void	ClearPath();
void	AddDistancePath(int x, int y, int dist);

// File.c
int 	ReadInFile(const char* name);
void	InitializeMapWithDefaultValues();
void	InitializeMapWithIsolatedIslandValues();