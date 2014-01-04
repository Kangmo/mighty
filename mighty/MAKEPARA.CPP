#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include "constdef.h"
// prefix 'i' means index.
// return value means validity

enum bool {false,true};
int MakeParam(char* COMMAND, int& num, char param[maxPARAM][lenPARAM])
{
	int iCMD=-1, iPARA;
	char now;
	bool end_of_loop=false, exitloop;
	num = -1;

	while ( !end_of_loop )
	{
		if (++num > maxPARAM) return TOO_MANY_PARAM;
		iPARA=-1;
		exitloop=false;
		while( !exitloop )
		{
			now=COMMAND[++iCMD];
			switch( now )
			{
			   case ' ':
						if (iPARA!=-1)
						{
						   param[num][++iPARA]=0;
						   exitloop=true;
						}
						break;
			   case '-':
			   case ',':
						if (iPARA!=-1)
						{
						   param[num][++iPARA]=0;
						   param[++num][0]=now;
						   param[num][1]=0;
						}
						else
						{
						   param[num][0]=now;
						   param[num][1]=0;
						}
						exitloop=true;
						break;

			   case  0 :

						param[num][++iPARA]=0;
						exitloop=true;
						end_of_loop=true;
						break;
			   default :
						param[num][++iPARA] = now;

			}

		}
	}
	++num;
	return NOERR;
}
void getln(char* str)
{
	int i=-1;
	str[i]=0;
	do {
		 str[++i] = getche();
	   } while(str[i] != 13);
	str[i]=0;
}
void main(void)
{
	int n,i;
	char str[100],*par[maxPARAM];
	clrscr();
	//for (i=1; i<=maxPARAM; i++) par[i-1]=(char *)malloc(10);
	while(1)
	{
		getln(str);
		MakeParam(str,n,par);
		printf("%i",n);

		for (i=1; i<=n; i++)
			printf("\nparam[%i]--> %s\n",i,par[i-1]);
	}
}
