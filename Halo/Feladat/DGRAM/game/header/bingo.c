#include "bingo.h"

int
main(int argc,char* argv[])
{
	
	srand(time(NULL));
	int petak = atof(argv[1]);
	Jatek(petak);
	return 0;
}