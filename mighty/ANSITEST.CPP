#include "headers.h"
#include <process.h>
int escstep=0,ScrollTime=onNORMAL;
_SCR::~_SCR() {}
class _SCR SCR;
class _rCOLOR rCOLOR;
void c_hputch(unsigned char ch)
{
	 if (ch == ESC || escstep > 0) process_vt100(ch);
	 else hputch(ch);
}

int ReadAnsiFile(char far* filename)
{
		char ch;
		long fsize,fnow=0;
		if ( access(filename,0)==-1 ) return 0;
		FILE *fANSI=fopen(filename,"rb");
		if (fANSI==NULL) hprintf("ERROR : Can't open ANSI file.");
		fseek(fANSI,0L,SEEK_END);
		fsize = ftell(fANSI);
		fseek(fANSI,0L,SEEK_SET);

		while( ++fnow <= fsize )
		{
			 ch=fgetc(fANSI);
			 c_hputch(ch);
			 if (ch=='\n') hputch('\r');
		}
		fclose(fANSI);

		return 1;
}

//
void CutOffSpace(unsigned char *str)
{
	 int index=0;
	 for (index=strlen(str)-1; index>=0; index--)
		if ( str[index] == ' ') str[index]=0;
		else break;
}

void main(void)
{
	 char path[200], FileName[20];
	 int ret;
	 long size;
	 unsigned long bf, af;
	 inithanlib( BGIMODE, HANDETECT, HAN8GD1, ENGGD5);

		int bHgrLoaded = loadhgrfont(1, "HGRMGT.FNT");
		if (bHgrLoaded != NOERR)
		{
			 printf("HGRMGT.FNT");
			 exit(0);
		}
		int bKssLoaded = loadkssfont(1, "KSSMGT.FNT");
		if (bKssLoaded != NOERR)
		{
			 printf("KSSMGT.FNT");
			 exit(0);
		}
		int bEgrLoaded = loadegrfont(1, "EGRMGT.FNT");
		if (bEgrLoaded != NOERR)
		{
			 printf("EGRMGT.FNT");
			 exit(0);
		}
		changehgrfont(1);
		changekssfont(1);
		changeegrfont(1);

	 hwindow(1,1,hgetmaxx(),hgetmaxy()-1);
	 hallowautoscroll(true);
	 /*_hookscroll*/
	 hsetcolor(15);
	 hsetbkcolor(1);
	 hclrscr();
	 do {
			 CFileSelector *FSEL=new CFileSelector(160,100, 7, 1, 5);//uses PathBuffer
			 ret = FSEL->SelectFile(path,FileName,size);
			 delete FSEL;

			 if (ret!=CANCEL)
			 {
				  hclrscr();
				  chdir(path);
				  bf = farcoreleft();
				  ReadAnsiFile(FileName);
				  hputch('_');
				  af = farcoreleft();
				  getch();
				  printf("%lu  -->  %lu",bf, af);
				  getch();
			 }
			 printf("%i",ret);
	 } while(ret != CANCEL);
}