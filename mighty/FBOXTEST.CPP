#include "han240.h"
#include "filebox.h"
#include "auxil.h"
#include <conio.h>
#include <string.h>
#define TAB 9
#define FILES 15
#define RECOVER 1
#define DRAW    2
#define DEBUG(n)  { hprintf("DEBUG %i DEBUG",(n)); getch(); }

void CutOffSpace(unsigned char *str)
{
	 int index=0;
	 for (index=strlen(str)-1; index>=0; index--)
		if ( str[index] == ' ') str[index]=0;
		else break;
}
_SCR SCR;
_rCOLOR rCOLOR;
char PathBuffer[300];
void main(void)
{
		char filename[13];
		long filesize;
		char path[300];
		inithanlib( BGIMODE, HANDETECT, HAN8GD1, ENGGD5);
		hsetcursormode(CM_DIRECTUNDER);
		hsetundercursor(-1,-1,WYELLOW);
		hrestartcursor();
		_showcursor = true;
		hallowautoscroll(true);
		CFileSelector *FSEL=new CFileSelector(2,3,5,4,3);
		FSEL->SelectFile(path,filename,filesize);
		hprintfxy(10,10,"%s %ld",filename,filesize);
		getch();
		delete FSEL;
}
