// ImperialMessengers.c : Defines the entry point for the console application.
//

void	Init( const char* pathToAdjacencyMatrix );

int main(int argc, char* argv[])
{
	Init( "input.txt" );
	// I could easily pass one of the commandline args here
	// but this was not part of the design.

	//getch();
	return 0;
}

