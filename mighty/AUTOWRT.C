#include <dir.h>
#include <io.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constdef.h"
#define MAXFILES 4096
struct _AllTime
{
	 int year;
	 char month, day;
	 unsigned char hour, min;
};

struct MenuIndex_t
{
		int n, alive, look, down, page, year, month, day, hour, min;
		long size;
		unsigned char name[9],id[9],toid[9],subject[MAX_SCHARS+1];
		char FileName[13];
};

void halt(char * msg)
{
	  printf("%s\n", msg);
	  exit(0);
}
int getmaxdatano()		// get start of title.
{
		int max = 0;
		if ( !access("MENUDATA.IDX" ,0) )
		{
			  FILE *IdxFile=fopen("MENUDATA.IDX","rb");
			  if (IdxFile==NULL) halt("Not Enough Memory : getting start number");
			  fseek(IdxFile,0L,SEEK_END);
			  max = ftell(IdxFile)/sizeof(struct MenuIndex_t);
			  fclose(IdxFile);
		}
		return max;
}

void GetAllTime(struct _AllTime *TM)
{
		struct time nowtime;
		struct date nowday;

		getdate( &nowday );
		gettime( &nowtime );
		TM->year = nowday.da_year;
		TM->month = nowday.da_mon;
		TM->day = nowday.da_day;
		TM->hour = nowtime.ti_hour;
		TM->min = nowtime.ti_min;
}


void AutoWrite()
{
		char ch,FileName[13];
		int count;
		long fcount,filelen;
		struct _AllTime write;
		struct MenuIndex_t BI;
		FILE *BbsIdx, *BbsDat;

		if (access("MENUDATA.IDX",0)==-1) BI.n=1;
		else BI.n = getmaxdatano()+1;
		if (BI.alive == 0) BI.alive=1;
		strcpy( BI.id, "AUTOWRT");
		strcpy( BI.name, "¸a•·—w¢");
		strcpy( BI.subject, "¶…µw¸a ¸a•·—w¢");
		GetAllTime(&write);
		BI.year = write.year;
		BI.month = write.month;
		BI.day = write.day;
		BI.hour = write.hour;
		BI.min = write.min;

		// file line counting routine.
		sprintf(FileName, "TXT%i.DAT",BI.n);
		BbsDat = fopen(FileName,"a+b");
		if (BbsDat==NULL) { printf("File not found - %s",FileName); return; }

		fseek(BbsDat,0L,SEEK_END);
		fwrite("\n.\n",3,1,BbsDat);
		filelen = ftell(BbsDat);
		fseek(BbsDat,0L,SEEK_SET);
		fcount=0;
		count=0;
		while( fcount++ < filelen)
		{
			ch = fgetc(BbsDat);
			if (ch=='\n') count++;
		}
		fclose(BbsDat);
		//at last.. BbsData::iE-1 has "." so.. count -1 is right.
		BI.page = (count-1) /L_TEXT +1;
		BI.look=0;
		BI.down=0;

		BbsIdx=fopen("MENUDATA.IDX","ab");
		if (BbsIdx == NULL) halt("Not Enough Memory : Can't open BBS index file..");
		fwrite(&BI, sizeof(struct MenuIndex_t), 1, BbsIdx);
		fclose(BbsIdx);

}

struct FileStruct {
	char name[13];
};

struct FileStruct FileData[MAXFILES];

int FileNameRead(char *pathname)
{
	struct ffblk ffblk;
	int count=0, done = findfirst(pathname,&ffblk,FA_DIREC);

	while(!done)
	{
		if (ffblk.ff_attrib != FA_DIREC)
		{
			strcpy( FileData[count].name, ffblk.ff_name);
			if (++count >= MAXFILES) break;
		}
		done = findnext(&ffblk);
	}
	return count;
}

void main (int argc, char *argv[])
{
		int nFileFound, nFile, bMove=0, i, BbsNum;
		char order[100], CurPath[300],PathName[300], DestName[300];
		printf("\n   Auto writer utility ver 1.0 for mighty host.       Program by Kim Kang-Mo\n\n");
		if (
			  ( argc !=3 && argc !=4 ) ||
			  ( argc == 3 && !stricmp(argv[1], "m") ) ||
			  ( argc == 4 && stricmp(argv[1],"m") )
			)
		{
			 printf("   USAGE : autowrt [option] <source path\\filename> <index path>\n");
			 printf("           option \"m\" : move file ( default : copy file )\n\n");
			 printf("       ex> autowrt c:\\i\\*.cap 420000\n");
			 printf("           autowrt c:\\config.sys c:\\mighty\\210000\n");
			 printf("           autowrt m c:\\i\\*.txt 421000\n\n");
			 printf("   CAUTION : Use Only to BBS Menu, or new data file will be broken.\n");
			 printf("             At the first example, if 420000 is a PDS Menu index number,\n");
			 printf("             new data files(c:\\i\\*.cap) in 420000 will be broken.\n");
			 halt("");
		}
		if (argc == 3)
		{
			 strcpy(PathName, argv[1]);
			 strcpy(DestName, argv[2]);
		}
		else
		{
			 strcpy(PathName, argv[2]);
			 strcpy(DestName, argv[3]);
			 bMove =1;
		}

		nFileFound = FileNameRead(PathName);
		if (nFileFound <= 0)
			 printf("\n   There is no file satisfies \"%s\"", PathName);

		for (i=strlen(PathName); i>=1; i--)
		{
			 if (PathName[i-1]=='\\')
			 {
				  if (i==strlen(PathName)) halt("ERROR : There is no file name.\n");
				  PathName[i-1]='\0';
				  break;
			 }
			 if (i==1) strcpy(PathName,".");
		}
		if (DestName[strlen(DestName)-1] == '\\') DestName[strlen(DestName)-1]=0;

		if ( getcwd(CurPath,299) == NULL ) halt("Internal error\n");
		if ( chdir(DestName) ==-1 ) halt("No valid index path directory.\n");

		for (nFile=1; nFile<=nFileFound; nFile++)
		{
			 printf("%4i> Writing %s to %s\n", nFile, FileData[nFile-1].name, DestName);

			 BbsNum =  getmaxdatano()+1;

			 if ( chdir(CurPath) ==-1) halt("Can't change directory to original directory.\n");

			 if (bMove) sprintf(order, "move %s\\%s %s\\txt%i.dat > tmp",
												 PathName, FileData[nFile-1].name,
												 DestName, BbsNum);
			 else sprintf(order, "copy %s\\%s %s\\txt%i.dat > tmp",
												 PathName, FileData[nFile-1].name,
												 DestName, BbsNum);

			 system( order );

			 if ( chdir(DestName) ==-1) halt("Can't change directory to index directory.\n");

			 AutoWrite();
		}
		if ( chdir(CurPath) ==-1) halt("Can't change directory to original directory.\n");
}