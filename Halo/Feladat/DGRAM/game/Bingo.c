#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_SZLVNY 9
#define MAX_NYSZ_COUNT 30
#define NYSZ_PLAFON 45


int Tet(int petak)
{
	int tet = 0;
	printf("\n\nEgyenleg : %d petak",petak);
	printf("\nTet : ");
	scanf("%d",&tet);
	petak -= tet;
	printf("Uj egyenleg : %d\n",petak );
	return tet;
}


int
CheckBingo(int* Bingo,int *nyeroszamok,int *szelveny,int petak,int tet)
{
	int keret = 0;
	int kep = 0;
	int i,j;
	int bing[MAX_SZLVNY];
	int talal = 0;


	for(i=0;i<MAX_SZLVNY;i++)
	{
		bing[i] = 0;
	}

	for (i =0;i<MAX_SZLVNY;i++)
	{
		for(j = 0;j<MAX_NYSZ_COUNT;j++)
		{
			if (szelveny[i] == nyeroszamok[j])
			{
				bing[i]++;
				talal++;

			}
		}
	}

	for(int i = 0;i < MAX_SZLVNY;i++)
	{
		if (i % 3 == 0)		
		{					// 23 51 12
			printf("\n");	// 35 21 1       -  forma kialakitasa
			printf("\t\t");
		}					// 1 2 34
		printf("%d ",bing[i]);

		if (bing[i] < 10)			// 5  3  24
		{					// 1  12 12
			printf(" ");	// 57 2  4 
		}
	}
	printf("\n");

	if (talal == 9)
	{
		*Bingo = 1;
		printf("\n\tOnnek bingoja van !\n");
		petak += tet*2;
	}

	else if (bing[4] == 1)
	{
		kep = 1;
		printf("\n\tOnnek kepe van !\n");
		petak += tet*1.3;
	}
	else if (bing[0] == 1 && bing[1] == 1 && bing[2] == 1 && bing[3] == 1 && bing[5] == 1 && bing[6] == 1 && bing[7] == 1 && bing[8] == 1 && bing[4] != 1)
	{
		keret = 1;
		printf("\n\tOnnek kerete van !\n");
		petak *= tet*1.4;
	}

	
	printf("Petak : %d\n",petak);
	return petak;
	printf("\n\n\n");

}


void
Varakozas(int mp)
{
	for(int i = mp;i>=1;i--)
	{
		printf("\t->\t");
		printf("%d\t",i);
		printf("<-");
		printf("\n");
		sleep(1);
	}
}

void
Random_Generator(int max,int arraysize,int vektor[arraysize])
{
	srand(time(NULL));
	int list[max];
	for (int i = 0; i < max; i++)
	{
	    list[i] = i+1;
	}
	for (int i = 0; i < max; i++)
	{
	    int j = i + rand() % (max - i);
	    int temp = list[i];
	    list[i] = list[j];
	    list[j] = temp;
	}
	for (int i = 0; i < arraysize; i++)
	{
	    vektor[i] = list[i];
	}
}

void
Sorsolas(int *Bingo,int *nyeroszamok)
{
	printf("Sorsolás : \n");
	Varakozas(3);
	Random_Generator(NYSZ_PLAFON,MAX_NYSZ_COUNT,nyeroszamok);
	printf("\n");

	for(int i = 0;i<MAX_NYSZ_COUNT;i++)
	{
		printf("%d#\t", i+1 );
		// if(i+1 >= 10)
		// {
		// 	printf(" ");
		// }
		printf("Nyeroszam : %d\n",nyeroszamok[i]);
	}
}

void
ShowSzelveny(int * szelveny)
{
	for(int i = 0;i < MAX_SZLVNY;i++)
	{

		if (i % 3 == 0)		
		{					// 23 51 12
			printf("\n");	// 35 21 1       -  forma kialakitasa
			printf("\t\t");
		}					// 1 2 34
		printf("%d ",szelveny[i]);

		if (szelveny[i] < 10)			// 5  3  24
		{					// 1  12 12
			printf(" ");	// 57 2  4 
		}
	}
	printf("\n\n\n");
	sleep(1);// várakoztatás
}


void
Szelveny(int *szelveny)
{
	void
	Kezi()
	{
		int szamok[45];
		memset(szamok,0,NYSZ_PLAFON);
		int pelda[MAX_SZLVNY];
		int valasztott=0;
		printf("\nSegitseg a kitolteshez\nMinta szelveny helyiertekekkel : \n");
		
		for(int i = 0;i < MAX_SZLVNY;i++)
		{
			pelda[i] = i+1;
		}

		ShowSzelveny(pelda);
		memset(szelveny,0,MAX_SZLVNY);
		
		for (int i = 0;i<MAX_SZLVNY;i++)
		{
			printf("%d. szam : \n",i + 1);
			scanf("%d",&valasztott);
			
			szamok[valasztott]++;
			int j = 1;
			szelveny[i] = valasztott;
			while(j < NYSZ_PLAFON+1)
			{
				if (szamok[j] == 2)
				{
					printf("duplicate : %d\n",j);
					i--;
					szamok[j] = 1;
					break;
				}

				if (valasztott > 45)
				{
					printf("A valasztott szamnak 1 es 45 kozott kell lennie.\n");
					i--;
					break;
				}

				j++;
			}
			
		}

	
		printf("Az On szelvenye : \n");

		ShowSzelveny(szelveny);
	}

	void
	Gepi()
	{
		printf("\nGepi kitoltes : \n");
		Random_Generator(45,MAX_SZLVNY,szelveny);
		ShowSzelveny(szelveny);
	}

	printf("\n\n\t-- Szelveny kitoltese ---\n\n");
	short a; // valtozo ahol a random szamokat taroljuk
	sleep(1);
	printf("1 - Kézi kitöltés\n");
	printf("2 - Gépi kitöltés\n");
	printf("Opcio : ");
	scanf("%hd",&a);
	
	if (a == 1)
	{
		Kezi();
	}
	else if (a == 2)
	{
		Gepi();
	}

	
}

void
Jatek(int *gameOver,int *Bingo,int petak)
{
	int szelveny[MAX_SZLVNY];
	int nyeroszamok[MAX_NYSZ_COUNT];
	int jatek = 0;
	while (*gameOver != 1)
	{

		system("clear");
		fflush(stdin);
		//Az ido a random generator seedje, mpnként változik
		// 1000 petákkal indulunk
		printf("\n\nUj jatek !!!\n");
		printf("Uj jatek !!!\n");
		printf("Uj jatek !!!\n");
		printf("\n\n\t--- %d. Karika ---\n\n",jatek+1);
		int tet = Tet(&petak);
		Szelveny(szelveny);
		sleep(1);
		Sorsolas(Bingo,nyeroszamok);
		petak = CheckBingo(Bingo,nyeroszamok,szelveny,petak,tet);
		if (petak < 1)
		{
			printf("\n\n\n\tGAME OVER\n\t(elfogyott a penzed)\n");
			break;
		}
		printf("\n\n\tNyomj [Enter]-t a folytatashoz.\n");
        fflush(stdin); // option ONE to clean stdin
        getchar(); // wait for ENTER
		getchar();
		//Sorsolas(Bingo);
		jatek++;
	}
}

int
main(int argc,char* argv[])
{

	int gameOver = 0;
	int Bingo = 0;
	int petak = atof(argv[1]);
	Jatek(&gameOver,&Bingo,petak);

	return 0;
}