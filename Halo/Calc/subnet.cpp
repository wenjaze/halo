#include <iostream>
#include <math.h>

int
szamolas (int *hostnum,int *mask_length,int *ip_length)
{
	double bits = log2(*hostnum)+1;
	int b = bits;
	return (*ip_length - *mask_length) - b;
}

int 
main(int argc,char* argv[])
{
	int mask_length = atoi(argv[1]);
	int ip_length = 32;
	int hostnum = atoi(argv[2]);
	std::cout<<szamolas(&hostnum,&mask_length,&ip_length)<<" bit(s) of Host ID needed."<<std::endl;
	return 0;
}