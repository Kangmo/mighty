#include <stdio.h>
#include <io.h>
#include <process.h>
#define np1 17
#define np2 11
char pass1[]="@%MS_AQ>Z)#JD(XMQ";
char pass2[]="+\|/*&zmO~`";
void main(void)
{
		long count,filelen;
		char ch;
		printf("Converting mighty.dat from Hard disk....");
		if ( access("mighty.dat",0) )
		{
			printf("Data file does not exist ");
			exit(1);
		}
		FILE *InFile = fopen("mighty.dat","rb");
		if ( InFile == NULL )
		{
			printf("Not enough memory");
			exit(1);
		}

		fseek(InFile,0L,SEEK_END);
		filelen = ftell(InFile);
		fseek(InFile,0L,SEEK_SET);

		FILE *fp = tmpfile();

		if (fp == NULL)
		{
			printf("Not enough memory");
			exit(1);
		}

		count = 0;
		while( count++ < filelen )
		{
			ch=fgetc(InFile);
			fputc( ch^pass1[count % np1], fp );
		}
		fclose (InFile);

		FILE *OutFile = fopen("mighty.dat","wb");
		if ( OutFile == NULL )
		{
			printf("Not enough memory");
			exit(1);
		}

		rewind(fp);

		count =0;

		while( count++ < filelen )
		{
			ch=fgetc(fp);
			fputc( ch^pass2[count % np2], OutFile );
		}
		fclose (OutFile);
		fclose (fp);

}