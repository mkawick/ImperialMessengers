// ImperialMessengers.cpp : Defines the entry point for the console application.
//


extern "C"
{
	void	Init( const char* pathToAdjacencyMatrix );
}

int main(int argc, char* argv[])
{
	Init( "input.txt" );
	return 0;
}

