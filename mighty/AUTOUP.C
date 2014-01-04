#include <dir.h>
#include <io.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "constdef.h"
#define MAXFILES 2048
#define PATH 0
#define MOVE 1
#define COPY 2
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

struct FileStruct {
	char name[13];
	long size;
};

struct FileStruct FileData[MAXFILES];
char DestName[300];

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


void getInteger(FILE *ifp, int *var, char ch1, char ch2, int mode )
{
	 int count=-1,j;
	 char ch,number[6];
	 *var=0;

	 while (ch=fgetc(ifp), (ch != ch1) && (ch != ch2 ) )
	 {
			 if (feof(ifp)) halt("enountered EOF");
			 if ( (mode == 4) && (ch == ' ') ) continue;
			 number[++count] = ch;
	 }
	 for (j=0; j<= count; j++)
			 *var += (number[j]-48)*pow(10, (count-j));
	 if ( mode == 1 ) while (ch != FS ) ch=fgetc(ifp);
	 if ( mode == 2 ) while (ch != '\n') ch=fgetc(ifp);
	 if ( mode == 3 ) ch=fgetc(ifp);
}

void CutOffSpace(unsigned char *str)
{
	 int index=0;
	 for (index=strlen(str)-1; index>=0; index--)
		if ( str[index] == ' ') str[index]=0;
		else break;
}

void getString(FILE *ifp, char *str, char ch1)
{
	 int count = -1;
	 unsigned char ch;
	 while (ch = fgetc(ifp), ch != ch1)
	 {
			str[++count]=ch;
	 }
	 str[++count]='\0';
	 CutOffSpace(str);
}

void GetDownPath(char *path)
{
	 FILE *InFile= fopen("C:\\MIGHTY.CFG","rt");
	 int tmpi;
	 char tmps[1000];

	 if (InFile == NULL )
			 halt("Can't find MIGHTY.CFG  -  BE SURE TO COPY \"MIGHTY.CFG\" TO C:\\");
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);
	 getInteger(InFile,&tmpi,FS,FS,0);

	 getString(InFile,tmps, FS);
	 getString(InFile,tmps, FS);
	 getString(InFile,tmps, FS);
	 getString(InFile,tmps, FS);
	 getString(InFile,tmps, FS);
	 strcpy (path, tmps);
	 fclose (InFile);
}
void AutoUp(char *path, int index)
{
		struct MenuIndex_t IDX;
		char pathfilename[13], CurPath[300], FileName[13];
		struct _AllTime write;
		FILE *BbsIdx, *BbsDat, *fPdsPath;

		if ( getcwd(CurPath,299) == NULL ) halt("Internal error\n");
		if ( chdir(DestName) ==-1 ) halt("No valid index path directory.\n");

		if (access("MENUDATA.IDX",0)==-1) IDX.n=1;
		else IDX.n = getmaxdatano()+1;
		if (IDX.alive == 0) IDX.alive=1;

		strcpy ( IDX.subject, "¶…µw¸a ¸a•·—w¢" );
		strcpy ( IDX.id, "AUTOUP");
		strcpy ( IDX.name, "¸a•·´ó");

		strcpy ( IDX.FileName, FileData[index].name);
		IDX.size = FileData[index].size;

		sprintf( pathfilename, "%i.P_T",IDX.n);
		fPdsPath=fopen(pathfilename,"wt");
		fprintf(fPdsPath,"%s\\\n",path);
		fclose(fPdsPath);


		GetAllTime(&write);
		IDX.year = write.year;
		IDX.month = write.month;
		IDX.day = write.day;
		IDX.hour = write.hour;
		IDX.min = write.min;
		IDX.page = 1;
		IDX.look=0;
		IDX.down=0;

		BbsIdx=fopen("MENUDATA.IDX","ab");
		if (BbsIdx == NULL) halt("Not Enough Memory : Can't open BBS index file..");
		fwrite(&IDX, sizeof(struct MenuIndex_t), 1, BbsIdx);
		fclose(BbsIdx);

		sprintf(FileName, "TXT%i.DAT",IDX.n);
		BbsDat = fopen(FileName,"wb");
		if (BbsDat==NULL) halt("Not enough memory");
		fprintf(BbsDat, "¶…µw¸a ¸a•· ¸aža—w¢‹¡ ¬a¶w\n.\n");
		fclose(BbsDat);

		if ( chdir(CurPath) ==-1) halt("Can't change directory to original directory.\n");
}


int FileNameRead(char *pathname)
{
	struct ffblk ffblk;
	int count=0, done = findfirst(pathname,&ffblk,FA_DIREC);

	while(!done)
	{
		if (ffblk.ff_attrib != FA_DIREC)
		{
			strcpy( FileData[count].name, ffblk.ff_name);
			FileData[count].size = ffblk.ff_fsize;
			if (++count >= MAXFILES) break;
		}
		done = findnext(&ffblk);
	}
	return count;
}

void main (int argc, char *argv[])
{
		int nFileFound, nFile, i, option=PATH;
		char order[100], PathName[300];
		char DownDir[100];
		printf("\n   Auto up utility ver 1.0 for mighty host.           Program by Kim Kang-Mo\n\n");
		if (
			  ( argc !=3 && argc !=4 ) ||
			  ( argc == 3 && !stricmp(argv[1], "m") && !stricmp(argv[1], "c") ) ||
			  ( argc == 4 && stricmp(argv[1],"m") && stricmp(argv[1],"c") )
			)
		{
			 printf("   USAGE : autoup [option] <source path\\filename> <index path>\n");
			 printf("           option \"c\" : copy file\n");
			 printf("           option \"m\" : move file\n");
			 printf("           default option : no operation with the file.\n\n");
			 printf("       ex> autoup c:\\i\\*.zip 420000\n");
			 printf("           autoup c:\\config.sys c:\\mighty\\210000\n");
			 printf("           autoup m c:\\i\\*.arj 421000\n");
			 printf("           autoup c c:\\i\\*.rar 421000\n\n");
			 printf("   CAUTION : Use Only to PDS Menu, or new data file will be broken.\n");
			 printf("             At the first example, if 420000 is a MAIL Menu index number,\n");
			 printf("             new data files(c:\\i\\*.zip) in 420000 will be broken.\n\n");
			 printf("   [!] Before you use AUTOUP utility, you have to copy \"mighty.cfg\" to c:\\\n");
			 halt("");
		}

		GetDownPath( DownDir );

		if (argc == 3)
		{
			 strcpy(PathName, argv[1]);
			 strcpy(DestName, argv[2]);
		}
		else
		{
			 strcpy(PathName, argv[2]);
			 strcpy(DestName, argv[3]);
			 if (!stricmp(argv[1],"m")) option = MOVE;
			 if (!stricmp(argv[1],"c")) option = COPY;
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

		for (nFile=1; nFile<=nFileFound; nFile++)
		{
			 printf("%4i> Doing UP %s to %s\n", nFile, FileData[nFile-1].name, DestName);

			 switch ( option )
			 {
				  case PATH : AutoUp(PathName, nFile-1);
								  break;
				  case MOVE : sprintf(order, "move %s\\%s %s > tmp",
													  PathName, FileData[nFile-1].name,
													  DownDir);
								  system( order );
								  AutoUp(DownDir, nFile-1);
								  break;
				  case COPY : sprintf(order, "copy %s\\%s %s > tmp",
													  PathName, FileData[nFile-1].name,
													  DownDir);
								  system( order );
								  AutoUp(DownDir, nFile-1);
			 }

		}
}