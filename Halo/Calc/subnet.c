#include <iostream>
#include <math.h>

int
szamolas (int a)
{
	double bits = log2(a)+1;
	int b = bits;

	return (ip_length - mask_length) - b;
}

int 
main(int argc,char* argv[])
{
	double mask_length = atoi(argv[1]);
	int ip_length = 32;
	int hostnum = atoi(argv[2]);
	std::cout<<szamolas(hostnum)<<std::endl;
	return 0;
}