#include <bios.h>
#include <conio.h>
#include <fstream.h>
#include "version.h"

#define MAXMENU 300
struct M {
		int X;
		int Color;
		int Head;
		int Grade;
		int Close;
		int RunNo;
		char Index[7];
		char Title[21];
		char Type[9];
		char Go[9];
		char AnsiFile[9];
		char SysId[9];
		char Level[5];
		char Point[5];
		char Pass[9];
		unsigned f2,f3,f4,f5,f6: 1;
} Menu[MAXMENU+1];

void LoadMenuOf10B()
{
	 int i,j,count;
	 char ch,number[7];
	 fstream  InFile("MENUDATA.DAT",ios::in);
	 if (!InFile) return;

	 count = -1; MaxNo=0;
	 while (InFile.get(ch), ch != '\n') number[++count] = ch;
	 for (j=0; j<=count; j++)
		 MaxNo += (number[j]-48)*multi(10, (count-j));

	 for (i=1; i<= MaxNo; i++)
	 {
		 count = -1; Menu[i].X = 0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].X += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].Color =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].Color += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].Head =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].Head += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].Grade =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].Grade += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].Close = 0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].Close += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].RunNo = 0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].RunNo += (number[j]-48)*multi(10, (count-j));

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Index[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Title[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Type[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Go[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].AnsiFile[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].SysId[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Level[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Point[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].Pass[++count]=ch;

		 while (InFile.get(ch), ch != FS) Menu[i].f2= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f3= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f4= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f5= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != '\n') Menu[i].f6= (ch=='1') ? 1 : 0;
	 }
	 InFile.close();
}
void SaveMenuFile()
{
	 long version;
	 version = IVER;
	 FILE* mfile = fopen("MENUDATA.DAT", "wb");
	 fwrite(&version, sizeof(version), 1, mfile);
	 fwrite(&MaxNo, sizeof(MaxNo), 1, mfile);
	 fwirte(&Menu[1], sizeof(struct M), MaxNo, mfile);
	 fclose(mfile);
}

void main()
{
	  printf("DATA FILE CONVERTER from mighty 1.0B to mighty 1.0 beta1.5\n");
	  printf("Program by KIM KANG MO 1996.6.15.\n\n"
	  printf("Converting menu datum.....");
	  LoadMenuOf10B();
	  printf("OK\n");
}
