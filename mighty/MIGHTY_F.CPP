#include "headers.h"
#include <STDARG.H>

//-------------------------------------------------------------------------//
//                       READ  THIS  RIGHT NOW !!                          //
//-------------------------------------------------------------------------//
//   MIGHTY HOST SOURCE       WRITTEN BY KIM KANG MO     (C)REFINED SOFT   //
//                                                                         //
//   MIGHTY IS A SHAREWARE PROGRAM. I DISTRIBUTE THIS SOURCE ONLY TO KOREA //
//   UNIVERSITY COMPUTER SCIENCE. THIS HOST IS COMMERCIAL PROGRAM, SO COM- //
//   PILE AND SELLING THIS PROGRAM IS ILLEGAL. AND DISTRIBUTING THIS SOUR- //
//   CE TO ANOTHER PERSON IS ALSO ILLEGAL,EVEN HE IS KOREA UNIV, COMPUTER  //
//   SCIENCE STUDENT. ANYONE WHO IS KOREA UNIV.'CS STUDENT AND WHO TELLS ME//
//   "GIVE ME YOUR HOST SOURCE" CAN HAVE THIS SOURCE.                      //
//                                                                         //
//   ANYONE WHO GIVES THIS SOURCE TO OTHERS,                               //
//   ANYONE WHO SELLS TRANSFORMED PROGRAM BY COMPILING THIS SOURCE,        //
//   ANYONE WHO SELLS THIS SOURCE,                                         //
//   ANYONE WHO USES THIS PROGRAM AND THIS SOURCE FOR COMMECIAL PURPOSE    //
//                                                                         //
//   WILL BE PERISHED BY COPY RIGHT LAW.                                   //
//                                                                         //
//-------------------------------------------------------------------------//

// THIS DECLARATION IS FOR DOS SCREEN SAVING FUNCTIONS.
char far *video = (char *)0xb8000000l;
int hndDosScr;
int DosCursorX, DosCursorY;
char bVarInit=0, bMenuRead=0, bIdRead=0, bDataRead=0;

void puthanja(int curchar, byte *hanjalist);
int cnvthangul(byte *s);

//------------------------------------------------------------------------//
//                     LOW LEVEL FUNTIONS                                 //
//------------------------------------------------------------------------//
void CutOffSpace(unsigned char *str)
{
	 int index=0;
	 for (index=strlen(str)-1; index>=0; index--)
		if ( str[index] == ' ') str[index]=0;
		else break;
}
bool isRealId(char* ID)
{
		bool bRealId=false;
		UserClass* mU;
		for (int find=1; find<=MaxUserNo; find++)
		{
			mU=new UserClass(find);
			mU->ReadData();
			if ( !strcmp(mU->stU.ID, ID) ) bRealId = true;
			delete mU;
		}
		return bRealId;
}

int DS_INDEX(int x,int y) {  return (x-1)*2 + (y-1)*160;  }
void PutCharXY(int x,int y,char ch,char attrib)
{
	  *( video + (x-1)*2 + (y-1)*160  ) = ch;
	  *( video + (x-1)*2 + (y-1)*160 + 1 ) = attrib;
}
void WaitForWhile(int dly)
{
	for(int time=1; time<=dly; time++);
}
Le2I(int Lev)
{
		int i;
		for (i=0; i<LevelNo; i++) if ( LEVEL[i].level >= Lev ) return i;
		return 14;
}

Me2I(char *index)
{
	 int i;
	 for (i=0; i<MenuNo; i++)
			if(!strcmp(index,MENU[i].index)) return i;
	 return ERR;
}
Type2I(int type)
{
	 int i;
	 for (i=0; i<MenuNo; i++)
		if ( MENU[i].type == type ) return i;
	 return ERR;
}

int strnch(unsigned char *str, char ch)
{
	 int i,sum=0;
	 for (i=0; i< strlen(str); i++)
		 if ( *(str+i) == ch ) sum++;
	 return sum;
}

int IntNo(int dat)
{
		int k;
		for (k=1; k<=5; k++)
			if ( dat/pow(10,k) == 0 )  return k;
		return ERR;
}

int pow(int x1,int x2)
{
	 int tx1=x1;
	 if (x2==0) return 1;
	 while (x2-- > 1) x1 *=tx1;
	 return x1;
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
void getUI(FILE *ifp, unsigned *var, char ch1, char ch2, int mode )
{
	 int count=-1,j;
	 char ch,number[6];
	 *var=0;

	 while (ch=fgetc(ifp), (ch != ch1) && (ch != ch2 ) )
	 {
			 if ( (mode == 4) && (ch == ' ') ) continue;
			 number[++count] = ch;
	 }
	 for (j=0; j<= count; j++)
			 *var += (number[j]-48)*pow(10, (count-j));
	 if ( mode == 1 ) while (ch != FS ) ch=fgetc(ifp);
	 if ( mode == 2 ) while (ch != '\n') ch=fgetc(ifp);
	 if ( mode == 3 ) ch=fgetc(ifp);
}

void getUC(FILE *ifp, unsigned char *var, char ch1, char ch2, int mode )
{
	 int count=-1,j;
	 unsigned char ch,number[6];
	 *var=0;

	 while (ch=fgetc(ifp), (ch != ch1) && (ch != ch2 ) )
	 {
			 if ( (mode == 4) && (ch == ' ') ) continue;
			 number[++count] = ch;
	 }
	 for (j=0; j<= count; j++)
			 *var += (number[j]-48)*pow(10, (count-j));
	 if ( mode == 1 ) while (ch != FS ) ch=fgetc(ifp);
	 if ( mode == 2 ) while (ch != '\n') ch=fgetc(ifp);
	 if ( mode == 3 ) ch=fgetc(ifp);
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

bool is_int(char *str)
{
	 int t;
	 t=0;
	 if (str[0]==0) return false;
	 while( str[t] != 0 )
		if (  ( str[t] > '9' ) || ( str[t++] <'0' )  )
		 return false;
	 return true;
}
//puts a character to modem(when not local state) and moniter
char *strcat2(char *des, const char *sor)
{
	 // temp_str is defined as extern value
	 strcpy(temp_str,des);
	 strcat(temp_str,sor);
	 return temp_str;
}
// returns whether first hangul character or not
int ishangul1st_(unsigned char ch)
{
		unsigned char tmp[2];
		tmp[0]=ch;
		tmp[1]=0;
		return ishangul1st(tmp,0);
}
//gets string from modem and if the string is paramiter 1(str) return true
int findStr(unsigned char *str)
{
	 int i;
	 int ch;
	 for (i=0; i<strlen(str); i++)
	 {
			 ch=SioGetc(port,6);
			 if ( ch<0 )
			 {
				  if (i!=0) for (int j=i-1; j>=0; j--) SioUnGetc(port, str[j]);
				  return 0;
			 }
			 if ( ch != str[i] )
			 {
				  SioUnGetc(port, ch);
				  if (i!=0) for (int j=i-1; j>=0; j--) SioUnGetc(port, str[j]);
				  return 0;
			 }
	 }
	 hputs(str);
	 return 1;
}

int min(int x,int y) { return x<=y ? x : y; }
void GetFileName(int num, char *FileName)
{
		 char strnum[6];
		 itoa( num, strnum, 10);
		 strcpy( FileName, strcat2(strcat2("TXT",strnum),".DAT"));
}
void box3d(int x1, int y1, int x2, int y2, int c, int ul, int dr)
{
		setfillstyle(1,c);
		bar(x1,y1,x2,y2);
		setcolor(ul);
		line(x1,y1,x2,y1);
		line(x1,y1,x1,y2);
		setcolor(dr);
		line(x2,y1,x2,y2);
		line(x1,y2,x2,y2);
}
void SetHanMode(bool mode)
{
	if (bAutoHan)
	{
		hookhangulmodetoggle( _hangulmode=mode );
		if (bLocal == 0 && !bDontSendComm)
		switch( mode )
		{
			case true  : SioPuts(port,"[?85h");
						 break;
			case false : SioPuts(port,"[?85l");
						 break;
		}
	}
}
int AnswerIs(char ch, char OnUserOut, bool OnEnter)
{
	char uStr[2],lStr[2],OnUO[2],ans[2];
	uStr[0]=toupper(ch);  uStr[1]=0;
	lStr[0]=tolower(ch);  lStr[1]=0;
	OnUO[0]=OnUserOut;    OnUO[1]=0;
	if (OnEnter)
	{
		 if (ch=='Y' || ch=='y') c_hputs("[Y/n]");
		 else c_hputs("[y/N]");
	}
	else
	{
		 if (ch=='Y' || ch=='y') c_hputs("[y/N]");
		 else c_hputs("[Y/n]");
	}
	SetHanMode(false);
	c_hgetln(ans,OnUO,1);
	if ( !strcmp(ans,"") ) return OnEnter;
	if ( !strcmp(ans, uStr) || !strcmp(ans,lStr) ) return true;
	return false;
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

int ElapseTime(unsigned char hour1, unsigned char min1,
							 unsigned char hour2, unsigned char min2)
{
		if (hour1 < hour2)
				return (hour2-hour1)*60 - min1 + min2;
		if ( (hour1 == hour2) && (min1 <= min2) )
				return min2-min1;
		if ( (hour1 == hour2) && (min1 > min2) ) return 1440 - min1 + min2;
		if (hour1 > hour2) return (hour2 - (hour1 - 24)) * 60 -min1 + min2;
		return -1;
}
int isValidPeopleNo(char* PeopleNo)
{
	int i, sum=0;
	if ( !PeopleNum ) return 1;

	for (i=1; i<=6; i++) sum += (PeopleNo[i-1]-'0')*(i+1);
	for (i=8; i<=9; i++) sum += (PeopleNo[i-1]-'0')*i;
	for (i=10; i<=13; i++) sum += (PeopleNo[i-1]-'0')*(i-8);

	if ( (sum%11) == 0 )
		if ( PeopleNo[13] == '1' ) return 1;
		else return 0;

	if ( (sum%11) == 1 )
		if ( PeopleNo[13] == '0' ) return 1;
		else return 0;

	if ( (PeopleNo[13]-'0') == (11-(sum%11)) ) return 1;
	else return 0;
}

void cursor_display()
{
		setcolor(hgetcolor());
		rectangle((x2ax(hwherex())-1)*8+_CW->charspace-8,(y2ay(hwherey())-1)*16+_CW->linespace-2,
							(x2ax(hwherex())-1)*8+_CW->charspace-1,(y2ay(hwherey())-1)*16+_CW->linespace-1);
		if ( (!SioTxQue(port) && !SioRxQue(port)) && !kbhit() ) time_process();
		setcolor(hgetbkcolor());
		rectangle((x2ax(hwherex())-1)*8+_CW->charspace-8,(y2ay(hwherey())-1)*16+_CW->linespace-2,
							(x2ax(hwherex())-1)*8+_CW->charspace-1,(y2ay(hwherey())-1)*16+_CW->linespace-1);
}
int hndLogData;
int errLogData=1;
int LastDoff;

void InitLogData()
{
		if (XMMcoreleft() < LogDataBufSize) halt("ERROR : Not eough XMS memory for log data");
		hndLogData = XMMalloc(LogDataBufSize);
		errLogData = _XMMerror;
		if (_XMMerror != 0) halt("ERROR : XMMalloc error in initlogdata.");
		LastDoff = 0;

		struct _AllTime tm;
		GetAllTime(&tm);
		WriteLogData_("‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ‘Õ\n");
		WriteLogData_("∂Öµw Ø°∏b : %iëe %i∂© %i∑© %iØ° %i¶Ö\n",
						  tm.year, tm.month, tm.day, tm.hour, tm.min);

}
//if _ exist, do not cat time. but cat '\n' char.
int WriteLogData_(const char *format, ...)
{
		char buffer[256];
		int cnt;
		va_list arglist;
		va_start(arglist, format);
		cnt = vsprintf(buffer, format, arglist);
		if (cnt==EOF) ErrMsg("ERROR : vsprintf routine");

		//hprintf("%s, %i",buffer, LastDoff);
		//getch();

		XMMcopyto( strlen(buffer),
					  buffer,
					  hndLogData, LastDoff );

		LastDoff += strlen(buffer);

		va_end(arglist);
		return cnt;
}
int WriteLogData(const char *format, ...)
{
		char buffer[512],timebuf[80];
		int cnt;
		va_list arglist;
		va_start(arglist, format);

		cnt = vsprintf(buffer, format, arglist);
		if (cnt==EOF) ErrMsg("ERROR : vsprintf routine");
		gettime( &NOW );
		sprintf(timebuf,"  [%2iØ°%2i¶Ö%2i¡°]\n",
							 NOW.ti_hour, NOW.ti_min, NOW.ti_sec);
		strcat( buffer, timebuf );
		//hprintf("%s, %i",buffer,LastDoff);
		//getch();
		XMMcopyto( strlen(buffer),
					  buffer,
					  hndLogData, LastDoff );

		LastDoff += strlen(buffer);

		va_end(arglist);
		return cnt;
}
void SaveLogData()
{
		if ( LastDoff > 0 )
		{
			 char* logbuf;
			 FILE* fLD;
			 chdir(InstDir);
			 logbuf = (char*) malloc ( LastDoff );
			 if (logbuf == NULL) halt("ERROR : not enough Memory for saving log data");
			 XMMcopyfrom (LastDoff, hndLogData, 0, logbuf);
			 fLD = fopen("LOGFILE.DAT","a+t");
			 if (fLD == NULL) halt("ERROR : Can't save Log Data File.");
			 //buffer[LastDoff]=0;
			 //hputs("buffer:");
			 //hputs(buffer); getch();
			 fwrite(logbuf, LastDoff, 1, fLD);
			 fclose(fLD);
			 free( logbuf );
			 LastDoff = 0;
		}
}
void DeInitLogData()
{
		if (errLogData==0) XMMfree(hndLogData);
}
int SpawnProg(int mode, char* path, char* argv[], int GiveTimeRate)
{
	rCOLOR.push();

	int ret1 = SCR.push(ax2apx(1),ay2apy(1),ax2apx(80)+CS-1,ay2apy(29)+LS-1);

	hrestorecrtmode();

	time_t first=time(NULL);
	int ret2 = spawnv( P_WAIT, argv[0], argv);
	time_t second=time(NULL);
	int elapsed = difftime(second, first);
	USER.stU.LeftTime -= elapsed/60;
	USER.stU.UsedTime += elapsed/60;
	USER.stU.LeftTime += elapsed * GiveTimeRate/60;

	hsetgraphmode();
	if (ret1 == NOERR) SCR.pop();

	STAT_display();
	rCOLOR.pop();
	return ret2;
}
//----------------------------------------------------------------------
//                           HOOK FUNTIONS
//----------------------------------------------------------------------
void hookhangulmodetoggle(bool hangulmode)
{
	if (hangulmode) hsetundercursor(-1, -1, HangulCurColor);
	else hsetundercursor(-1, -1, EnglishCurColor);
	wputsxy(STATWIN, 2, 1, hangulmode ? "–eãi" : "µw¥·");
}

void hookhanjamodetoggle(bool hanjamode)
{
	if (hanjamode) hsetundercursor(-1, -1, HanjaCurColor);
	else hsetundercursor(-1, -1, HangulCurColor);

	wputsxy(STATWIN, 2, 1, hanjamode ? "˜”ÒÆ" : "    ");
}

void hookmistyping(void)
{
	sound(1000);
	delay(80);
	nosound();
}
void hookhanjabox(int *keycodep, byte *hanjalist, int *curcharp)
{
	int i, n, w, h;
	int curchar = *curcharp;
	long size;
	static void far *image;  /* Must be static! */

	/* Adjust the box size */

	n = strlen(hanjalist) / 2;
	w = min(BOX_CPL, n) * 3;
	h = (n + 9) / 10;
	hsetwindow(HANJABOX, 31, 4, -(w + 1), -(h + 1), HYELLOW, HRED,
				HANJABOX);

	/* Open the box */

	htempcurwindow(HANJABOX);

	if (keycodep == NULL) {
		size = himagesize(0, 0, hgetpwidth(), hgetpheight());
		if ((image = farmalloc(size)) == NULL)
			puterr("Out of memory!", 1);
		hgetimage(0, 0, hgetpwidth(), hgetpheight(), image);

		hclrscr();
		hrectangle(0, 0, hgetmaxpx(), hgetmaxpy(), HWHITE);

		for (i = 0; i < n; i++) puthanja(i, hanjalist);

		hsetreverse(!isreverse());
		puthanja(curchar, hanjalist);
		hsetreverse(!isreverse());
		hlastcurwindow();
		return;
	}

	/* Close the box */

	if (*keycodep == ENTER || *keycodep == ESC) {
		if (*keycodep == ESC) *curcharp = 0, *keycodep = ENTER;
		hputimage(0, 0, image);
		farfree(image);
		hlastcurwindow();
		return;
	}

	/* Output the last character */

	puthanja(curchar, hanjalist);

	/* Move the cursor */

	switch (*keycodep) {
	case LEFTARROW:
		if (curchar > 0) curchar--;
		break;
	case RIGHTARROW:
		if (curchar < n - 1) curchar++;
		break;
	case UPARROW:
		if (curchar >= BOX_CPL) curchar -= BOX_CPL;
		break;
	case DOWNARROW:
		if (curchar < n - BOX_CPL) curchar += BOX_CPL;
		break;
	case HOMEKEY:
		curchar = 0;
		break;
	case ENDKEY:
		curchar = n - 1;
		break;
	}

	/* Output the current character */

	hsetreverse(!isreverse());
	puthanja(curchar, hanjalist);
	hsetreverse(!isreverse());

	/* Update *curcharp */

	*curcharp = curchar;

	hlastcurwindow();
}

bool hookhgetline(int *keycodep, byte *string, int *curpp, int *lastpp,
				  size_t n)
{
	static bool first;
	bool reprint;
	byte *curpos = string + *curpp;

	lastpp = lastpp;  /* Dummy */

	/* Output the default string */

	if (keycodep == NULL) {
		first = true;
		hsetcolor(HLIGHTCYAN);
		hprintfxy(hwherex() - *curpp, hwherey(), "%-*s", n, string);
		return true;
	} else if (first) {
		first = false;
		hsetcolor(HWHITE);
		hprintfxy(hwherex() - *curpp, hwherey(), "%-*s", n, string);
		return true;
	}

	/* Check if the key code is F8 or F9 */

	if (*keycodep != F8 && *keycodep != F9) return false;

	/* If the character is not a Hangul or a Hanja, */
	/* move the cursor and return                   */

	if (!ishangul1st(curpos, 0)) {
		if (*curpos) (*curpp)++;
		return false;  /* Do not update the input field */
	}

	/* Convert a Hangul to a Hanja or a Hanja to a Hangul */

	reprint = true;
	*curpp += 2;
	switch (*keycodep) {
	case F8:
		if (code_ishanja(curpos))
			code_cnvthanja(curpos, curpos[0], curpos[1]);
		if (ishangul1st(curpos, 0))
			if (cnvthangul(curpos) == ERROR)
				reprint = false;  /* If it was not converted */
		break;
	case F9:
		if (code_ishanja(curpos))
			code_cnvthanja(curpos, curpos[0], curpos[1]);
		else if (ishangul1st(curpos, 0))
			if (cnvthangul(curpos) == ERROR)
				reprint = false;
		break;
	}

	return reprint;  /* Update the input field if reprint is true */
}
// error_no becomes zero in c_hgetln
// error_no makes ungetxch to only once called to one c_hgetln()
void hookwaitkey(void)
{
		int ch;
		if ( bWaiting || bPDrun) return;
		if ( ( bLocal || ( !SioTxQue(port) && !SioRxQue(port) ) ) && !kbhit() )
		{
			 if (bUserNotExist && ERROR_NO==0 )
			 {
				  ungetxch(13);
				  ERROR_NO = USER_OUT;
				  return;
			 }
			 time_process();
		}
		if (bLocal) return;
		if (!SioDCD( port ) && ERROR_NO ==0)
		{
			 ungetxch(13);
			 bUserNotExist=1;
			 ERROR_NO = USER_OUT;
			 if (bSysopHangUp) WriteLogData("‘ê ∂Öµw∏aàa àwπAù° ∏Û≠¢ èg∑q ‘ë");
			 else WriteLogData("‘ê ∑°∂w∏aàa àwπAù° ∏Û≠¢ èg∑q ‘ë");
			 return; // at last str is copyied to second param of c_hgetln
		}   		if (bChatMode) hlastcurwindow();
		if (u_idx==1) UserStr[0]=0;
		while( SioRxQue(port) )
		{
			 ch = SioGetc(port, 0);
			 if (ch<0) continue;
					if (ch == 8)
					{
						 if ( (u_idx >= 3) && (ishangul1st(UserStr,u_idx-3)==true) )
						 {
								u_idx-=2;
								UserStr[u_idx-1]=0;
								UserStr[u_idx]=0;
								// when chatting host must not print anything about user
								// when user type "go chat", then nChatting becomes true
								if (!bChatting)
								{
									hremovecursor();
									hputs("\b\b");
									hrestartcursor();
								}
								SioPuts(port, "[2D  [2D");
								continue;
						 }
						 if (u_idx > 1)
						 {
								UserStr[--u_idx -1]=0;
								if (!bChatting)
								{
									hremovecursor();
									hputs("\b");
									hrestartcursor();
								}
								SioPuts(port, "[1D [1D");
						 }
						 continue;
					}
					if ( ch==13 )
					{
						 ungetxch(13);
						 u_idx=1;
						 bUserTypeEnter=1;
						 break;
					}
					if (ch==27)
					{
						 if ( findStr("[A") )
						 {
								strcpy(UserStr,"B");
								ungetxch(13);
								break;
						 }
						 if ( findStr("[B") )
						 {
								strcpy(UserStr,"F");
								ungetxch(13);
								break;
						 }
					}
					else if ( u_idx <= MaxGetln )
					{
						 if (ch!=26)  // this is ctrl-z (eof) ascii code.
						 {            // for patching bbs data is broken error.
								UserStr[u_idx++ -1]=ch;
								UserStr[u_idx-1]=0;
								if (!bChatting)
								{
									  hremovecursor();
									  if (bPassInput) c_hputch('*');
									  else c_hputch(ch);
									  hrestartcursor();
								}
								else SioPutc(port, ch);
						 }
					}
		}
		if (bChatMode) htempcurwindow(CHATWIN);
}
//--------------------------------------------------------------------------
//                       IYAGI GRIM LETTER SELECTOR
//--------------------------------------------------------------------------
#define BOXxSIZE 5
#define BOXySIZE 5
#define BOXyMAX  26
#define GBOXWIN &gboxwin
void GrimBox(int x1, int y1)
{
 char* GrimLst[BOXyMAX+1] = { "‘Ä‘Å‘Ç‘É‘Ñ",
									 "‘Ö‘Ü‘á‘à‘â",
									 "‘ä‘ã‘å‘ç‘é",
									 "‘è‘ê‘ë‘í‘ì",
									 "‘î‘ï‘ñ‘ó‘ò",
									 "‘ô‘ö‘õ‘ú‘ù",
									 "‘û‘ü‘†‘°‘¢",
									 "‘£‘§‘•‘¶‘ß",
									 "‘®‘©‘™‘´‘¨",
									 "‘≠‘Æ‘Ø‘∞‘±",
									 "‘≤‘≥‘¥‘µ‘∂",
									 "‘∑‘∏‘π‘∫‘ª",
									 "‘º‘Ω‘æ‘ø‘¿",
									 "‘¡‘¬‘√‘ƒ‘≈",
									 "‘∆‘«‘»‘…‘ ",
									 "‘À‘Ã‘Õ‘Œ‘œ",
									 "‘–‘—‘“‘”‘‘",
									 "‘’‘÷‘◊‘ÿ‘Ÿ",
									 "‘⁄‘€‘‹‘›‘ﬁ",
									 "‘ﬂ‘‡‘·‘‚‘„",
									 "‘‰‘Â‘Ê‘Á‘Ë",
									 "‘È‘Í‘Î‘Ï‘Ì",
									 "‘Ó‘Ô‘‘Ò‘Ú",
									 "‘Û‘Ù‘ı‘ˆ‘˜",
									 "‘¯‘˘‘˙‘˚‘¸",
									 "‘˝‘˛",
									 "" };
		window_t gboxwin;
		int bx, by, x, y, scrolled=0, ch, x2, y2;
		char cur[3],repaint, first=1,ch1, ch2, doprint=0;
		x2= x1+BOXxSIZE*2-1;
		y2= y1+BOXySIZE-1;
		rCOLOR.push();
		int ret=SCR.push(ax2apx(x1)-8, ay2apy(y1)-8, ax2apx(x1+BOXxSIZE*2)+8, ay2apy(y1+BOXySIZE)+8);
		hsetwindow(GBOXWIN, x1, y1, x2, y2, 7, 0, DEFWIN);
		//wsetreverse(STATWIN, false);
		wsetcolor(GBOXWIN,0);
		wsetbkcolor(GBOXWIN,7);
		wallowautoscroll(GBOXWIN, false);
		box3d(ax2apx(x1)-8, ay2apy(y1)-8, ax2apx(x1+BOXxSIZE*2)+8, ay2apy(y1+BOXySIZE)+8, 7, 15, 8);
		for (y=1; y<=5; y++) wputsxy(GBOXWIN, 1, y, GrimLst[y-1]);
		bx=by=x=y=1;
		while(1)
		{
			ch = getxch();
			repaint=0;
			if (ch >= 0x100 )
			{
				 repaint=1;

				 switch(ch)
				 {
					 case UPARROW:
							 if (y>1) y--;
							 break;
					 case DOWNARROW:
							 if (y<BOXyMAX) y++;
							 if (y==BOXyMAX && x>2) x=2;
							 break;
					 case LEFTARROW:
							 if (x>1) x--;
							 else if (y>1)
							 {
								 y--;
								 x=BOXxSIZE;
							 }
							 break;
					 case RIGHTARROW:
							 if (x<BOXxSIZE)
							 {
								 if (y<BOXyMAX) x++;
								 else if (x < 2) x++;
							 }
							 else if (y<BOXyMAX)
							 {
								 y++;
								 x=1;
							 }
							 break;
					 default:
							 repaint=0;
				 }
			}
			else if (ch==13)
			{
				  if (s_idx-1 < MaxGetln)
				  {
						 ch1=SysopStr[s_idx++ -1]=GrimLst[y-1][(x-1)*2];
						 ch2=SysopStr[s_idx++ -1]=GrimLst[y-1][(x-1)*2+1];
						 SysopStr[s_idx-1]=0;
						 doprint = 1;
				  }
				  break;
			}
			else if (ch==27) break;
			if (repaint || first)
			{
				 first=0;
				 cur[0]=GrimLst[by-1][(bx-1)*2];
				 cur[1]=GrimLst[by-1][(bx-1)*2+1];
				 cur[2]=0;
				 wputsxy(GBOXWIN, (bx-1)*2+1 , by-scrolled, cur);

				 if ( y-scrolled > BOXySIZE && y > by )
				 {
					  wscroll(GBOXWIN);
					  wputsxy(GBOXWIN, 1, BOXySIZE, GrimLst[y-1]);
					  scrolled++;
				 }
				 if ( y-scrolled <= 0 && y < by)
				 {
					  wbackscroll(GBOXWIN);
					  wputsxy(GBOXWIN, 1, 1, GrimLst[y-1]);
					  scrolled--;
				 }

				 cur[0]=GrimLst[y-1][(x-1)*2];
				 cur[1]=GrimLst[y-1][(x-1)*2+1];
				 cur[2]=0;
				 wsetbkcolor(GBOXWIN, 12);
				 wsetcolor(GBOXWIN, 7);
				 wputsxy(GBOXWIN, (x-1)*2+1 , y-scrolled, cur);
				 wsetbkcolor(GBOXWIN, 7);
				 wsetcolor(GBOXWIN, 0);
				 bx=x;
				 by=y;
			}
		}
		if (ret!=-1) SCR.pop();
		rCOLOR.pop();

		if (doprint)
		{
			if (bChatMode)
			{
					wputch(CHATWIN, ch1);
					wputch(CHATWIN, ch2);
			}
			else if (bChatting)
			{
					hputch(ch1);
					hputch(ch2); // when chatting, chatting string must not send to comm port
			}
			else
			{
					c_hputch(ch1);
					c_hputch(ch2);
			}
		}
}
//--------------------------------------------------------------------------
//                       HANJA RELATED FUNCTIONS
//--------------------------------------------------------------------------
void puthanja(int curchar, byte *hanjalist)
{
	int x, y;

	x = 3 * (curchar % BOX_CPL);
	y = curchar / BOX_CPL;
	hputsnpxy(8 + x * hgetcharspace(), 8 + y * hgetlinespace(), 2,
			  hanjalist + curchar * 2);
}

int cnvthangul(byte *s)
{
	byte *hanjalist;
	int curchar;
	int keycode;

	hanjalist = code_gethanjalist(s, &curchar);
	if (hanjalist == NULL) return ERROR;

	hookhanjabox(NULL, hanjalist, &curchar);
	do {
		keycode = getxch();
		hookhanjabox(&keycode, hanjalist, &curchar);
	} while (keycode != ENTER);

	code_setcurhanja(s, curchar);  /* s must be Hangul */

	s[0] = hanjalist[curchar * 2];
	s[1] = hanjalist[curchar * 2 + 1];

	code_freehanjalist(hanjalist);  /* hanjalist must be freed */

	return NOERROR;
}
void loadhanjatbl(void)
{
	FILE *hjtbl;
	int curchars[N_HANJATBL];

	hjtbl = fopen("hanja.tbl", "rb");
	if (hjtbl == NULL) return;

	if (fread(curchars, sizeof(*curchars), N_HANJATBL, hjtbl) != N_HANJATBL)
		return;

	fclose(hjtbl);

	code_sethanjatbl(curchars);
}

void savehanjatbl(void)
{
	FILE *hjtbl;
	int curchars[N_HANJATBL];

	hjtbl = fopen("hanja.tbl", "wb");
	if (hjtbl == NULL) return;

	code_gethanjatbl(curchars);

	if (fwrite(curchars, sizeof(*curchars), N_HANJATBL, hjtbl) != N_HANJATBL)
		return;

	fclose(hjtbl);
}

//--------------------------------------------------------------------------
//                    NEWLY MADE HANLA FUNCTIONS                          //
//--------------------------------------------------------------------------


void kmPuts(int x1,int y1,char *String)
{
	 int change=0,mode,col,temp1=hgetbkcolor(), temp2=hgetcolor();
	 hgotoxy(x1,y1);

	 while ( *String ) {
		 if ( ( *String == '@' ) || ( *String == '#') )
		 {
			 if ( *String++ == '@' ) mode = 1; else mode =0;
			 if ( ( *String == '1' ) && *(String+1) >= '0' && *(String+1) <='5' )
			 {
					col=*(++String)-38;
					change = 1;
					String++;
			 }
			 else
			 if ( ( *String  >= '0') && ( *String <= '9') )
			 {
					col = *String++ -48;
					change = 1;
			 }
			 if ( change == 1 ) {
				 if ( mode == 1 )  hsetcolor(col);
				 if ( mode == 0 )  hsetbkcolor(col);
				 change = 0;
			 }
		 }
		 else hputch(*String++);
	 }
	 hsetbkcolor(temp1);  hsetcolor(temp2);
}

void c_hgetln(unsigned char *str,unsigned char *OnUserOut, int no)
{
		int ch;
		if (s_idx==1) SysopStr[0]=0;
		if (!bChatting && u_idx!=1)
			 c_hputs(UserStr);   // if UserString is not empty, then print it
		str[0]=0;
		if (no > max_line) return;
		MaxGetln=no;
		ERROR_NO=0;
		while(1)
		{
			 if (bChatMode) htempcurwindow(CHATWIN);

			 ch = hgetxch();

			 if (bChatMode) hlastcurwindow();
			 if (ch >= 0x100)
			 {
				  if (ch==UPARROW)
				  {
						 strcpy(str,"B");
						 c_hputs("\n\r");
						 break;
				  }
				  else if (ch==DOWNARROW)
				  {
						 strcpy(str,"F");
						 c_hputs("\n\r");
						 break;
				  }
				  else process_ctrlkey(ch);
				  continue;
			 }
			 if ( ch!=NUL )
			 {
					if (ch == 8)
					{
						 if ( (s_idx >= 3) && (ishangul1st(SysopStr,s_idx-3)==true) )
						 {
								s_idx-=2;
								SysopStr[s_idx-1]=0;
								SysopStr[s_idx]=0;
								if (bChatMode) wputs(CHATWIN, "\b\b");
								else
								{
									hputs("\b\b");
									if (!bLocal && !bChatting) SioPuts(port, "[2D  [2D");
								}
								continue;
						 }
						 if (s_idx > 1)
						 {
								SysopStr[--s_idx -1]=0;
								if (bChatMode)	wputs(CHATWIN, "\b");
								else
								{
									 hputs("\b");
									 if (!bLocal && !bChatting) SioPuts(port, "[1D [1D");
								}
						 }
						 continue;
					}
					if ( ch==13 )
					{
						 if (bUserTypeEnter)
						 {
							  bUserStringActive=1; // used for chat object.
							  bUserTypeEnter=0;
							  strcpy(str,UserStr);
							  //WriteLogData("%sµA¨· \"%s\"∑≥ùb [%luB] ",MENU[nAcc].title, UserStr, farcoreleft());
						 }
						 else
						 {
							  bUserStringActive=0;
							  strcpy(str,SysopStr);
							  if (bChatMode)
							  {
									wputs(CHATWIN, "\n\r");
									if (!bChatting)
									{
										 if (bPassInput)
											 for (int i=1; i<=strlen(str); i++) c_hputch('*');
										 else c_hputs(str);
									}
							  }
							  s_idx=1;
						 }
						 if (!bChatting) c_hputs("\n\r");
						 break;
					}
					if ( s_idx <= no )
					{
						 if (ch!=26)  // this is ctrl-z (eof) ascii code.
						 {                 // for patching bbs data is broken error.
								SysopStr[s_idx++ -1]=ch;
								SysopStr[s_idx-1]=0;
								if (bChatMode) wputch(CHATWIN, ch);
								else if (bChatting) hputch(ch); // when chatting, chatting string must not send to comm port
									  else
									  {
										  if (bPassInput) c_hputch('*');
										  else c_hputch(ch);
									  }
						 }
					}
			 }
		}
		if (bUserNotExist) strcpy(str,OnUserOut);
}
//-------------------------------------------------------------------------
//                  DATAFILE / ANSIFILE LOADING FUNCTIONS
//-------------------------------------------------------------------------
int ReadAnsiFile(char* filename)
{
		int bRead=0, ReadLen, ProcessedLen;
		long fsize,fnow=0;
		char ch, str[MAX_MACRO_LEN+1],dir_str[200];
		getcwd(dir_str,199);
		if ( chdir(AnsiDir) ==-1 ) halt("ERROR : Ansi diectory is invalid.");
		//hprintf("filename->%s",filename);getch();
		if ( access(filename,0) == 0 )
		{
			  FILE *fANSI=fopen(filename,"rb");
			  if (fANSI==NULL) halt("ERROR : Can't open ANSI file.");

			  fseek(fANSI,0L,SEEK_END);
			  fsize = ftell(fANSI);
			  fseek(fANSI,0L,SEEK_SET);
			  while( ++fnow <= fsize )
			  {
				  ch=fgetc(fANSI);
				  if ( ch == '$' )
				  {
						ch=fgetc(fANSI);
						if (++fnow > fsize) break;
						if (ch=='$')
						{
							  memset(str, 0, MAX_MACRO_LEN+1);
							  ReadLen=strlen( fgets(str, MAX_MACRO_LEN, fANSI) );
							  ProcessedLen = ProcessMacro(str);
							  fnow += ProcessedLen;
							  fseek(fANSI, (long)(ProcessedLen-ReadLen), SEEK_CUR);
						}
						else
						{
							  c_hputch(ch);
							  if (ch=='\n') c_hputch('\r');
						}
				  }
				  else
				  {
						c_hputch(ch);
						if (ch=='\n') c_hputch('\r');
				  }
			 }
			 bRead=1;
			 fclose(fANSI);
		}
		if ( chdir(dir_str)==-1) halt("Mighty was not able to change directory");
		return bRead;
}
void readProtocol()
{
	 int i;
	 if (access("PROTOCOL.DAT",0)) // in case of not existing protocol file
		 halt("Can't find MIGHTY.CFG  -  Please Run SETUP first.");
	 else printf("Reading protocol.dat from HARD DISK....");

	 FILE *fProto=fopen("PROTOCOL.DAT","rb");
	 if (fProto==NULL) halt("ERROR : NOT ENOUGH MEMORY WHILE READING PROTOCOL.DAT");
	 fseek(fProto,0L,SEEK_SET);
	 for (i=0; i<10; i++)
		 fread(&PROTO[i],sizeof(_Proto),1,fProto);
	 fclose( fProto );
	 printf("OK !\n");
}

void readCfg()
{
	 FILE *InFile= fopen("MIGHTY.CFG","rt");
	 if (InFile == NULL )
			 halt("Can't find MIGHTY.CFG  -  Please Run SETUP first.");
	 else printf("Reading mighty.cfg from HARD DISK....");
	 int version;
	 getInteger(InFile,&version,FS,FS,0);
	 if (version != IVER) halt("FATAL ERROR : \"MIGHTY.CFG\" is old version type. Run SETUP first.");
	 getInteger(InFile,&port,FS,FS,0);
	 getInteger(InFile,&speed,FS,FS,0);
	 getInteger(InFile,&parity,FS,FS,0);
	 getInteger(InFile,&data,FS,FS,0);
	 getInteger(InFile,&stop,FS,FS,0);
	 getInteger(InFile,&HanFontType,FS,FS,0);
	 getInteger(InFile,&EngFontType,FS,FS,0);
	 getInteger(InFile,&VirDetect,FS,FS,0);
	 getInteger(InFile,&HackDetect,FS,FS,0);
	 getInteger(InFile,&OpMode,FS,FS,0);
	 getInteger(InFile,&PeopleNum,FS,FS,0);
	 getInteger(InFile,&HanBoard,FS,FS,0);
	 getInteger(InFile,&LevelNo,FS,FS,0);

	 getString(InFile,sName, FS);
	 getString(InFile,sId, FS);
	 getString(InFile,bName, FS);
	 getString(InFile,InstDir, FS);
	 getString(InFile,DownDir, FS);
	 getString(InFile,AnsiDir, FS);
	 getString(InFile,ArcDir, FS);
	 getString(InFile,WaitInit, FS);
	 getString(InFile,LocalInit, FS);
	 getString(InFile,LoginId, FS);
	 getString(InFile,VirOrder, FS);
	 getString(InFile,HackWord, FS);
	 getString(InFile,SmPass, FS);
	 getInteger(InFile,&SonnimLev, FS, ' ', 1 );
	 getInteger(InFile,&JoinLev, FS, ' ', 1 );
	 getInteger(InFile,&BbsPoint, FS, ' ', 1 );
	 getInteger(InFile,&UpPoint, FS, ' ', 1 );
	 getInteger(InFile,&UpSizeRate, FS, ' ', 1 );
	 getInteger(InFile,&UpTimeRate, FS, ' ', 1 );
	 getInteger(InFile,&InputLimTime, FS, ' ', 1 );
	 getUC(InFile,&OpStart.hour, FS, ' ', 1 );
	 getUC(InFile,&OpStart.min, FS, ' ', 1 );
	 getUC(InFile,&OpEnd.hour, FS, ' ', 1 );
	 getUC(InFile,&OpEnd.min, FS, ' ', 1 );
	 getInteger(InFile,&InitGab, FS, ' ', 1 );
	 getInteger(InFile,&DoNullModem,FS,FS,1);
	 getUC(InFile,(unsigned char*)&bSound,FS,FS,1);
	 getUC(InFile,(unsigned char*)&existSysop,FS,FS,1);
	 getInteger(InFile,&FirstGrade,FS,FS,1);
	 getInteger(InFile,&GiveDnableSize,FS,FS,1);
	 getInteger(InFile,&SuccDnLoad,FS,FS,1);
	 getInteger(InFile,&Fifo,FS,FS,1);
	 getInteger(InFile,&Flow,FS,FS,1);
	 getInteger(InFile,&MinBbsSize,FS,' ',1);
	 getInteger(InFile,&MinPdsSize,FS,' ',1);
	 getUI(InFile, &MinSpeed, FS, ' ',1);
	 getUC(InFile,(unsigned char*)&bUsePartT,FS,FS,0);
	 getString( InFile, EmulPro, FS);
	 getString( InFile, EditPro, FS);

	 char ch;
	 while(ch=fgetc(InFile), ch != '\n');

	 for (int i=0; i<LevelNo; i++)
	 {
			getInteger(InFile,&(LEVEL[i].point), '/', '/', 4 );
			getInteger(InFile,&(LEVEL[i].level), '/', '/', 4 );
			getInteger(InFile,&(LEVEL[i].time), '/', '/', 4 );
			getInteger(InFile,&(LEVEL[i].sizeDN), '\n', '\n', 4 );
	 }
	 /*
	 printf( "port : %d   ",port);
	 printf( "speed : %d   ",speed);
	 printf( "parity : %d   ",parity);
	 printf( "data : %d   ",data);
	 printf( "stop : %d   \n",stop);
	 printf( "HanFont : %d   ",HanFontType);
	 printf( "EngFont : %d   ",EngFontType);
	 printf( "VirDetect : %d   ",VirDetect);
	 printf( "HackDetect : %d   \n",HackDetect);
	 printf( "OpMode : %d   ",OpMode);
	 printf( "PeopleNum : %d   ",PeopleNum);
	 printf( "HanBoard : %d  \n",HanBoard);
	 printf( "sName : %s   ",sName);
	 printf( "sId : %s   ",sId);
	 printf( "bName : %s   ",bName);
	 printf( "InstDir : %s   \n",InstDir);
	 printf( "DownDir : %s   ",DownDir);
	 printf( "AnsiDir : %s   \n",AnsiDir);
	 printf( "ArcDir : %s   ",ArcDir);
	 printf( "WaitInit : %s   ",WaitInit);
	 printf( "LocalInit : %s   \n",LocalInit);
	 //printf( "SonnimId : %s   ",SonnimId);
	 //printf( "SysopId : %s   ",SysopId);
	 printf( "LoginId : %s   \n",LoginId);
	 printf( "VirOrder : %s   ",VirOrder);
	 printf( "HackOrder : %s   \n",HackWord);
	 printf( "SmPass : %s   ",SmPass);
	 printf( "SonnimLev : %d   ",SonnimLev);
	 printf( "JoinLevel : %d   ",JoinLev);
	 printf( "BbsPoint : %d   ",BbsPoint);
	 printf( "UpPoint : %d   \n",UpPoint);
	 printf( "UpSizeRate : %d   ",UpSizeRate);
	 printf( "UpTimeRate : %d   ",UpTimeRate);
	 printf( "InputLimTime : %d   ",InputLimTime);
	 printf( "OpStart.hour : %d   \n",OpStart.hour);
	 printf( "OpStart.min : %d   ",OpStart.min);
	 printf( "OpEnd.hour : %d   ",OpEnd.hour);
	 printf( "OpEnd.min : %d   ",OpEnd.min);
	 printf( "InitGab : %d   \n",InitGab);
	 printf( "bSound : %i \n",bSound);
	 printf( "existSysop : %i\n",existSysop);
	 printf( "FirstGrade : %i\n",FirstGrade);
	 printf( "GiveDnableSize : %i\n",GiveDnableSize);
	 printf( "SuccDnLoad : %i\n",SuccDnLoad);
	 printf( "Fifo : %i\n",Fifo);
	 printf( "Flow : %i\n",Flow);
	 printf( "MinBbsSize : %i\n",MinBbsSize);
	 printf( "MinPdsSize : %i\n",MinPdsSize);
	 printf( "MinSpeed : %i\n",MinSpeed);
	 printf( "bUsePartT : %i\n",bUsePartT);
	 printf( "EmulPro : %s\n",EmulPro);
	 printf( "EditPro : %s\n",EditPro);

	 getch();
	 for (i=0; i<15; i++)
	 {
			printf("%4d/",LEVEL[i].point);
			printf("%4d/",LEVEL[i].level);
			printf("%4d/",LEVEL[i].time);
			printf("%4d/\n",LEVEL[i].sizeDN);
	 }
	 getch();
	 */
	 printf("OK !\n");
	 fclose(InFile);
}
void readMenuData()
{
	 int version;
	 FILE* mfile = fopen("MENUDATA.DAT", "rb");
	 if (mfile==NULL) halt("Can't find MENUDATA.DAT  -  Please Run SETUP first.");
	 else
	 {
		  printf("Reading menudata.dat from HARD DISK....");
		  fread(&version, sizeof(version), 1, mfile);
		  if (version==IVER)
		  {
				fread(&MenuNo, sizeof(int), 1, mfile);
				MENU = (menu_t*) farmalloc ( MenuNo * sizeof(menu_t) );
				MENUDATA = (menudata_t*) malloc( MenuNo * sizeof(menudata_t) );
				if (MENU == NULL || MENUDATA == NULL)
					  halt("ERROR : Not Enough Memory to allocate Menu data.");
				fread(&MENU[0], sizeof(struct menu_t), MenuNo, mfile);
				fclose(mfile);
				printf("OK !\n");
				bMenuRead=1;
		  }
		  else
		  {
				fclose(mfile);
				halt("FATAL ERROR : \"MENUDATA.DAT\" is old version type. Run SETUP first.");
		  }
	 }
	 /*	 printf("MenuNo : %d \n",MenuNo);
		 for (int i=0;i<MenuNo;i++)
		 {
				printf("MENU[%d].grade : %d\n",i,MENU[i].grade);
				printf("MENU[%d].close : %d\n",i,MENU[i].close);
				printf("MENU[%d].index : %s\n",i,MENU[i].index);
				printf("MENU[%d].title : %s\n",i,MENU[i].title);
				printf("MENU[%d].type  : %d\n",i,MENU[i].type);
				printf("MENU[%d].go    : %s\n",i,MENU[i].go);
				printf("MENU[%d].ansifile : %s\n" ,i,MENU[i].ansifile);
				printf("MENU[%d].sysid : %s\n",i,MENU[i].sysid);
				printf("MENU[%d].level : %d\n",i,MENU[i].level);
				printf("MENU[%d].point : %d\n",i,MENU[i].point);
				printf("MENU[%d].pass  : %s\n",i,MENU[i].pass);
				printf("MENU[%d].run   : %c\n",i,MENU[i].run);
				getch();
		 }*/
}
void makeIdIndex()
{
		User_t tmpU;
		if (access("USERDATA.DAT",0)) return;

		FILE *InFile = fopen("USERDATA.DAT","rb");
		if ( InFile == NULL )
				halt("ERROR : Happend while making ID Index table");


		fseek(InFile, 0L, SEEK_END);
		MaxUserNo = ftell(InFile) / sizeof(struct User_t);
		if (IdIndex != NULL) farfree(IdIndex);
		IdIndex = (_IdIndex *)farmalloc( MaxUserNo * sizeof(_IdIndex));
		if (IdIndex == NULL)
		{
				fclose(InFile);
				halt("Not Enough Memory : while making Id index. Make more XMS memory.");
		}
		for (int i=0; i<MaxUserNo; i++ )
		{
			 fseek(InFile, (long)( sizeof(struct User_t)*i), SEEK_SET);
			 fread(&tmpU, sizeof(struct User_t), 1, InFile);
			 IdIndex[i].OK=tmpU.OK;
			 strcpy(IdIndex[i].ID, tmpU.ID);
			 strcpy(IdIndex[i].PASS, tmpU.PASS);
		}
		bIdRead=1;
		fclose(InFile);
}
//-----------------------------------------------------------------------
//                       ERROR MESSAGE FUNCTION                        //
//-----------------------------------------------------------------------
void ErrMsg(char *title)
{
		rCOLOR.push();
		char *tmpbuf = (char *)
		malloc( himagesize(318 - strlen(title) * _CW->charspace /2, 210,
						322 + strlen(title) * _CW->charspace /2, 230) );
		htempwindow(1,1,SCRWIDTH,SCRHEIGHT);

		if (tmpbuf != NULL)
			 hgetimage( 318 - strlen(title) *_CW->charspace /2, 210,
									322 + strlen(title) *_CW->charspace /2, 230, tmpbuf );
		hsetbkcolor(12);
		hsetcolor(14);
		box3d( 318 - strlen(title) *_CW->charspace /2, 210,
					 322 + strlen(title) *_CW->charspace /2, 230, 12, 15, 8);
		hputspxy( 320 - strlen(title) *_CW->charspace /2, 212, title);
		delay(1200);
		if (tmpbuf != NULL) hputimage(318 - strlen(title) *_CW->charspace / 2, 210, tmpbuf);
		if (tmpbuf != NULL) free(tmpbuf);
		rCOLOR.pop();
		hlastwindow();
}

void FontError(int err, char* fontfile)
{
	 char message[80];
	 switch( err )
	 {
		 case ERR_OUTOFMEM   :
			  sprintf(message,"Õ•ÀaÃa∑©(%s)∑i ∑™ìeïA °A°°ü°àa ¶Åπ¢–sì°îa",fontfile);
			  ErrMsg(message);
			  break;
		 case ERR_OUTOFRANGE :
			  sprintf(message,"Õ•Àa—¡∑©(%s)∑Å –Öói µ°üA",fontfile);
			  ErrMsg(message);
			  break;
		 case ERR_NOTFOUND   :
			  sprintf(message,"ERROR : Fontfile(%s) does not exist.",fontfile);
			  halt( message );
		 case ERR_READERROR  :
			  sprintf(message,"ERROR : Fontfile(%s) is broken.",fontfile);
			  halt( message );
		 case ERR_WRONGSIZE  :
			  sprintf(message,"ERROR : Size of fontfile(%s) is illegal.",fontfile);
			  halt( message );
	 }
}
//------------------------------------------------------------------------
//                         INITIALIZING FUNCTIONS                       //
//------------------------------------------------------------------------
void PrintLogo()
{
	 textcolor(15);
	 textbackground(1);
	 cprintf(" MIGHTY HOST ver 1.0 beta1.5 (second test version)    (c) REFINED SOFT , 1996 ");
	 textcolor(7);
	 textbackground(0);
	 cprintf("\n\r");
}

void MemoryManagerInit()
{
		init_SPAWNO(getenv(InstDir),SWAP_XMS);

		printf("Testing XMS for mighty....");
		switch ( XMMlibinit() )
		{
			case NOXMM:
				 halt("Can't find an Extended Memory Manager.\n");
				 break;
			case 0:
				 printf("OK!\n");
				 break;
			case XMMOOPS:
			default:
				 printf("XMS initializing error - code 0x%X.\n",
									(unsigned int) _XMMerror);
				 halt("");
				 break;
		}
}
// Path Buffer is in FILEBOX module.
extern char PathBuffer[200];
void varInit()
{
//    TRASH = new _TempQueue();
		existSysop = 1;
		tLogin.year=0;
		timestr[0]=0;

		temp_str=(char *)malloc(TEMP_STR_LEN+1);
		strcpy(PathBuffer,"C:\\*.*");
		DF=new CDataFile("MIGHTY.DAT");
		bVarInit=1;
		IdIndex=NULL;
}
struct HostInfo_t
{
		unsigned long nAllLogin;
};
void readHostInfo()
{
		if ( access("MIGHTY.INF",0) == -1 )
		{
			  nAllLogin = 0ul;
		}
		else
		{
			  HostInfo_t HI;
			  FILE* fHI = fopen("MIGHTY.INF","rb");
			  if (fHI==NULL) halt("ERROR : Not enough memory - Reading MIGHTY.INF");
			  fread (&HI, sizeof(HostInfo_t), 1, fHI);
			  nAllLogin = HI.nAllLogin;
			  fclose (fHI);
		}
}
void saveHostInfo()
{
		HostInfo_t HI;
		FILE* fHI = fopen("MIGHTY.INF","wb");
		if (fHI==NULL) halt("ERROR : Not enough memory - Reading MIGHTY.INF");
		HI.nAllLogin = nAllLogin;
		fwrite (&HI, sizeof(HostInfo_t), 1, fHI);
		fclose (fHI);
}
void DIRprocess()
{
	 int i;
	 if ( chdir(InstDir)==-1 ) halt("Mighty installation directory is invalid.");
	 if ( access("dsz.exe",0) == -1)
		 halt("There isn't dsz.exe. Please Copy it to Mighty installed directory");
	 printf("Making menu directories....");
	 for (i=0; i<MenuNo; i++)
	 {
			switch(MENU[i].type)
			{
				/* menu which not needs submenu
				SUB :
				WMAIL :
				RMAIL :
				SMAIL :
				CHAT :
				JOIN :
				EDITSELF :
				VUSER	:
				TBANK	:
				*/
				case BBS :
				case PDS :
				case CDROMPDS :
				case RDNPDS :
				case OMAIL :
				case MBOX :
				case MSEE :
				case MSIG :
				case NOTICE :
				case SCRIPT :
					mkdir( MENU[i].index );
			}
	 }
	 mkdir(DownDir);
	 mkdir(AnsiDir);
	 mkdir( strcat2(InstDir,"\\MAIL") );
	 printf("OK !\n");
}
void commInit()
{
	 data=data+2;
	 if (parity ==2) parity =3;

	 char far* Ptr1 = (char far *) farmalloc(16384+16);
	 char far* Ptr2 = (char far *) farmalloc(32768L+16);

	 if (Ptr1==NULL || Ptr2==NULL) halt("ERROR:Not enough memory for comm buffers.");
	 int RxSeg = FP_SEG(Ptr1) + ((FP_OFF(Ptr1)+15)>>4);
	 int TxSeg = FP_SEG(Ptr2) + ((FP_OFF(Ptr2)+15)>>4);
	 printf("Initializing comm port %i ....",port+1);
	 ErrChk( SioRxBuf(port,RxSeg,Size16K) );
	 ErrChk( SioTxBuf(port,TxSeg,Size32K) );
	 ErrChk( SioParms( port, parity, stop, data) );
	 ErrChk( SioReset(port,speed) );
	 ErrChk( SioDTR(port,'S') );
	 ErrChk( SioRTS(port,'S') );
	 printf("OK !\n");
	 printf("Setting FIFO level ....");
	 if (SioFIFO(port, Fifo-1) < 0) printf("UART in not 16550 !\n");
	 else printf("OK !\n");
	 if (Flow != 0)
	 {
		  printf("Setting Flow control ....");
		  if (Flow==1 || Flow==3) ErrChk( SioFlow(port,18) );
		  printf("OK !\n");
	 }
}

void SaveDosScr()
{
	int chars, x, y;
	char* dosscr = (char*)malloc(25*80*2);
	if (dosscr==NULL) halt("NOT enough memory - saving screen.");

	DosCursorX=wherex();
	DosCursorY=wherey();
	_setcursortype(_NOCURSOR);
	gettext (1,1,80,25,dosscr);
	for(chars=39; chars>=1; chars--)
	{
		for (y=1; y<=25; y++)
		{
			for (x=1; x<=chars; x++)
			{
				PutCharXY(x,y,dosscr[DS_INDEX(40-chars+x,y)],dosscr[DS_INDEX(40-chars+x,y)+1]);
				PutCharXY(81-x,y,dosscr[DS_INDEX(41+chars-x,y)],dosscr[DS_INDEX(41+chars-x,y)+1]);
			}
			PutCharXY(chars+1,y,0,0);
			PutCharXY(80-chars,y,0,0);
			if (!kbhit()) WaitForWhile(3500);
			if (chars==1)
			{
				PutCharXY(1,y,0,0);
				PutCharXY(80,y,0,0);
			}
		}
	}
	bDosScrSaved=1;
	while (kbhit()) getch();
	if ( XMMcoreleft() < 25*80*2 ) halt("Not enough XMS memory -saving screen");
	hndDosScr = XMMalloc( 25*80*2 );
	XMMcopyto(25*80*2,dosscr,hndDosScr,0L);
	free(dosscr);
}

void hanInit()
{
		inithanlib( BGIMODE, HANDETECT, HAN8GD1, ENGMD1);
		int err;
		if ( (err=hgraphresult()) < NOERROR)
		{
			 printf("%i, %i",err,NOERROR); getch();
			 halt("ERROR : Mighty do not bring up MDA, CGA or EGA.");
		}
		bHanjaLoaded=loadhanjafont("hanja.fnt");
		if ( bHanjaLoaded != NOERROR) halt("ERROR : HANJA.FNT is not in Mighty directory.");
		loadhanjatbl();

		_stklen = 4096*4;

		_hookhwaitkey = hookwaitkey;
		_hookhangulmodetoggle = hookhangulmodetoggle;
		_hookhanjamodetoggle = hookhanjamodetoggle;
		_hookmistyping = hookmistyping;
		_hookhanjabox = hookhanjabox;
		_hookhgetline = hookhgetline;

		_islinefeednewline=false;
		_allowmistyping = false;
		_allowfirstdelline = true;
		_endcursor = true;
		_showcursor = true;
		_restoreline = true;
		_hangulmode=false;
		_hanjamode=false;

		_key.delafter = CTRL_G;

		hsetcursormode(CM_DIRECTUNDER);
		hsetundercursor(-1,-1,EnglishCurColor);
		hrestartcursor();

		bHgrLoaded = loadhgrfont(1, "HGRMGT.FNT");
		if (bHgrLoaded != NOERR) FontError(bHgrLoaded, "HGRMGT.FNT");

		bKssLoaded = loadkssfont(1, "KSSMGT.FNT");
		if (bKssLoaded != NOERR) FontError(bKssLoaded, "KSSMGT.FNT");

		bEgrLoaded = loadegrfont(1, "EGRMGT.FNT");
		if (bEgrLoaded != NOERR) FontError(bEgrLoaded, "EGRMGT.FNT");

		changehgrfont(1);
		changekssfont(1);
		changeegrfont(1);

		hallowautoscroll(true);
		hsetwindow(STATWIN, 1, hgetmaxay(), 80, hgetmaxay(), HMAGENTA, HWHITE,
							 DEFWIN);
		hsetwindow(HANJABOX, 31, 4, -(BOX_CPL * 3 + 1), -8, HYELLOW, HRED,
					DEFWIN);
		//wsetreverse(STATWIN, false);
		wsetcolor(STATWIN,15);
		wsetbkcolor(STATWIN,5);
		wregisterhanfont(STATWIN, HAN8GD1);
		wallowautoscroll(STATWIN, false);
		hsetwindow(CHATWIN, 1, hgetmaxay()-CBOXLINES, 80, hgetmaxay()-1, 15, 0,
							 DEFWIN);
		wsetbkcolor(CHATWIN, 0);
		wsetcolor(CHATWIN,15);
		wregisterhanfont(CHATWIN, HAN8GD1);
		wallowautoscroll(CHATWIN, true);
}
void hanDeinit()
{
	 if (bHanjaLoaded == NOERR) savehanjatbl();
	 if (bHgrLoaded == NOERR) releasehgrfont(1);
	 if (bKssLoaded == NOERR) releasekssfont(1);
	 if (bEgrLoaded == NOERR) releaseegrfont(1);
	 closehan();
}
void ConfigInit()
{
	 int ret;
	 if ( HanBoard == 0 )
	 {
		 hsethan389board( false );
		 hsethan2board( true );
	 }
	 else if ( HanBoard == 1 )
	 {
		 hsethan2board( false );
		 hsethan389board( true );
	 }
	 switch( HanFontType)
	 {
		case 1 : break;
		//case 1 : ret=loadhanfont(1, "han8gd1.fnt", HINFO8X4X4);
	   //     	  if (ret != NOERR) FontError(err,"han8gd1.fnt");
		//		  break;
	   case 2 : ret=loadhanfont(1, "han10md1.fnt", HINFO10X4X4);
				if (ret != NOERR) FontError(ret,"han10md1.fnt");
				changehanfont(1);
				break;
		case 3 : ret=loadhanfont(1, "han8gd2.fnt", HINFO8X4X4);
				if (ret != NOERR) FontError(ret,"han8gd2.fnt");
				changehanfont(1);
				break;
		case 4 : ret=loadhanfont(1, "han8gd3.fnt", HINFO8X4X4);
				if (ret != NOERR) FontError(ret,"han8gd3.fnt");
				changehanfont(1);
				break;
		case 5 : ret=loadhanfont(1, "han8gs1.fnt", HINFO8X4X4);
				if (ret != NOERR) FontError(ret,"han8gs1.fnt");
				changehanfont(1);
				break;
	   case 6 : ret=loadhanfont(1, "han8gs2.fnt", HINFO8X4X4);
				if (ret != NOERR) FontError(ret,"han8gs2.fnt");
				changehanfont(1);
				break;
		default : halt ("ERROR : Hangul font setting is invalid. run SETUP.");
	 }

	 switch( EngFontType)
	 {
		case 1 : break;
		// case 1 : loadengfont(1, "engmd2.fnt");
		//		if (ret != NOERR) FontError(err,"engmd2.fnt");
		//		  break;
		case 2 : loadengfont(1, "engmd1.fnt");
				if (ret != NOERR) FontError(ret,"engmd1.fnt");
				changeengfont(1);
				break;
		case 3 : loadengfont(1, "engmd3.fnt");
				if (ret != NOERR) FontError(ret,"engmd3.fnt");
				changeengfont(1);
				break;
		case 4 : loadengfont(1, "engmd4.fnt");
				if (ret != NOERR) FontError(ret,"engmd4.fnt");
				changeengfont(1);
				break;
		case 5 : loadengfont(1, "engmd6.fnt");
				if (ret != NOERR) FontError(ret,"engmd6.fnt");
				changeengfont(1);
				break;
		case 6 : loadengfont(1, "enggd5.fnt");
				if (ret != NOERR) FontError(ret,"enggd5.fnt");
				changeengfont(1);
				break;
		case 7 : loadengfont(1, "enggs6.fnt");
				if (ret != NOERR) FontError(ret,"enggs6.fnt");
				changeengfont(1);
				break;
		default : halt ("ERROR : English font setting is invalid. run SETUP.");
	 }
}
// MenuNo starts from 1
void HostInitialize()
{
	 int nMenu, alldata, data, newdata;
	 MenuIndex_t IDX;
	 FILE* IdxFile;
	 if (!aliveUSER) halt("ERROR : USER object is not alive while initializing host.");
	 USER.stU.LoginTime = tLogin;
	 ReadDataFile(295); //doing host initialization. percent :
	 // at first, set all menu is not sig menu.
	 for (nMenu=1; nMenu<=MenuNo; nMenu++)
	 {
		  MENUDATA[nMenu-1].signum = MENUDATA[nMenu-1].siginnum = 0;
	 }
	 for (nMenu=1; nMenu<=MenuNo; nMenu++)
	 {
		  c_hprintf("\b\b\b\b%3i\%",nMenu*100/MenuNo);
		  switch(MENU[nMenu-1].type)
		  {
			 case BBS    :
			 case PDS    :
			 case CDROMPDS :
			 case OMAIL  :
			 case NOTICE :

				  sprintf(temp_str,"%s\\%s\\MENUDATA.IDX",InstDir, MENU[nMenu-1].index);
				  if (access(temp_str,0)!=0)
				  {
						MENUDATA[nMenu-1].alldata = MENUDATA[nMenu-1].newdata = 0;
						MENUDATA[nMenu-1].day     = MENUDATA[nMenu-1].month   = 0;
						break;
				  }
				  IdxFile=fopen(temp_str,"rb");
				  if (IdxFile==NULL) halt("Not Enough Memory : Initializing host");
				  fseek(IdxFile,0L,SEEK_END);
				  alldata=MENUDATA[nMenu-1].alldata = ftell(IdxFile)/sizeof(MenuIndex_t);
				  newdata=0;
				  for (data=alldata; data>=1; data--)
				  {
						 fseek(IdxFile, (long)((data-1)*sizeof(IDX)), SEEK_SET);
						 fread(&IDX, sizeof(IDX), 1, IdxFile);
						 if (data == alldata) // when this is the first(latest) data.
						 {
							 MENUDATA[nMenu-1].month = IDX.month;
							 MENUDATA[nMenu-1].day = IDX.day;
						 }
						 // if this data is written before User's logout time, then break;
						 if (IDX.year < USER.stU.LogoutTime.year ) break;
						 else if (IDX.year == USER.stU.LogoutTime.year)
									if (IDX.month < USER.stU.LogoutTime.month) break;
									else if (IDX.month == USER.stU.LogoutTime.month)
											  if (IDX.day < USER.stU.LogoutTime.day) break;
											  else if (IDX.day == USER.stU.LogoutTime.day)
															if (IDX.hour < USER.stU.LogoutTime.hour) break;
															else if (IDX.hour == USER.stU.LogoutTime.hour)
																	 if (IDX.min < USER.stU.LogoutTime.min) break;
						 // otherwise, this is written after User's logout time.
						 newdata++;
				  }
				  MENUDATA[nMenu-1].newdata = newdata;
				  fclose(IdxFile);
				  break;
			 default :
				  MENUDATA[nMenu-1].newdata = MENUDATA[nMenu-1].alldata = -1;
		  }
		  // if MENU is MSIG, then set signum and siginnum.
		  if (MENU[nMenu-1].type == MSIG)
		  {
				  int  i, j, siginnum;
				  char MsigIndex[7];
				  strcpy(MsigIndex, MENU[nMenu-1].index);
				  // if index is "711000" then MsigIndex becomes "71"
				  for (i=5; i>=0; i--)
				  {
						if (MsigIndex[i]!='0')
						{
							 MsigIndex[i]=NULL;
							 break;
						}
				  }
				  // MENU index 0 is top menu, so SIG Entrance index can't be 0
				  // find SIG Enterance Menu
				  // if MSIG index is "711000", SIG Entrance index is "710000"
				  // This routine determine SIG Entrance with "71"(MSigIndex)+"0000"
				  // But such index that is like "710100" do not exist.
				  // So, a menu whose index[strlen(MsigIndex)] is '0' is Entrance of MSIG
				  for (i=1; i<=MenuNo; i++)
				  {
						// if SIG menu
						if (!strncmp(MENU[i-1].index, MsigIndex, strlen(MsigIndex)))
						{
							 // if last character of index is '0'
							 if (MENU[i-1].index[strlen(MsigIndex)]=='0')
							 {
								  siginnum = i-1; // siginnum starts from index 0
								  break;
							 }
						}
				  }

				  for (i=1; i<=MenuNo; i++)
				  {
						//find menu whose index starts with MsigIndex (this is Sig menu)
						if (!strncmp(MENU[i-1].index, MsigIndex, strlen(MsigIndex)))
						{
							 MENUDATA[i-1].signum = nMenu-1;
							 MENUDATA[i-1].siginnum = siginnum;
						}
				  }
		  }
	 }
	 ReadDataFile(296);
}
//--------------------------------------------------------------------------
//                 DEINITIALIZING FUNCTIONS                               //
//--------------------------------------------------------------------------

void LoadDosScr()
{
	int chars, x, y;

	if (!bDosScrSaved) return;

	char* dosscr = (char*)malloc(25*80*2);
	if (dosscr==NULL) halt("NOT enough memory - saving screen.");

	XMMcopyfrom(25*80*2,hndDosScr,0L,dosscr);

	if (XMMfree(hndDosScr) != 0) halt("ERROR : failed to free XMS - Loading Dos screen");

	gotoxy(DosCursorX, DosCursorY);
	for(chars=1; chars<=40; chars++)
	{
		for (y=1; y<=25; y++)
		{
			for (x=1; x<=chars; x++)
			{
				PutCharXY(x,y,dosscr[DS_INDEX(40-chars+x,y)],dosscr[DS_INDEX(40-chars+x,y)+1]);
				PutCharXY(81-x,y,dosscr[DS_INDEX(41+chars-x,y)],dosscr[DS_INDEX(41+chars-x,y)+1]);
			}
			if (!kbhit()) WaitForWhile(3500);
		}
	}
	free(dosscr);
	while (kbhit()) getch();
	_setcursortype(_NORMALCURSOR);
}

void delVar()
{
	 if (bVarInit)
	 {
			free(temp_str);
			delete DF;
	 }
	 if (bMenuRead)
	 {
		  farfree(MENU);
		  free(MENUDATA);
	 }
	 if (bIdRead) farfree(IdIndex);
	 //delete TRASH;
	 if (bPdRan) delete PD;
}

void delComm()
{
	 SioDone(port);
}
void halt(const char *error)
{
		closehan();
		LoadDosScr();
		printf("\n%s\n", error);
		//printf("MEMORY TEST : %lu bytes --> %lu bytes.",first_core,farcoreleft());

		chdir(InstDir);
		saveHostInfo();

		if (errLogData==0)
		{
			 struct _AllTime tm;
			 GetAllTime(&tm);
			 WriteLogData_("∂Öµw π∑ûa : %iëe %i∂© %i∑© %iØ° %i¶Ö\n",
								  tm.year, tm.month, tm.day, tm.hour, tm.min);
			 WriteLogData_("∏Û≠¢ —e—◊ : %i°w / %i°w (≠•ì± / ∏Â¡A) ,  Ø•ãA àa∑≥ %i°w\n",
									 nSonnimLogin, nTodayLogin, nNewJoin );
			 WriteLogData_("π∑ûa ¨w»Å : %s\n", error);

			 SaveLogData();
			 DeInitLogData();
		}
		delVar();
		delComm();
		hanDeinit();
		exit(0);
}

//------------------------------------------------------------------------
//                          HIGH LEVEL FUNCTIONS
//------------------------------------------------------------------------
void STAT_display()
{
	 char mins[8];
	 box3d(0,ay2apy(30),639,ay2apy(30)+_CW->linespace,5,5,5);
	 setcolor(15);
	 rectangle(ax2apx(7)-1, ay2apy(30),
						 ax2apx(7), ay2apy(30)+_CW->linespace);
	 rectangle(ax2apx(19)-1, ay2apy(30),
						 ax2apx(19), ay2apy(30)+_CW->linespace);
	 rectangle(ax2apx(69)-1, ay2apy(30),
						 ax2apx(69), ay2apy(30)+_CW->linespace);

	 hookhangulmodetoggle(_hangulmode);

	 if (bLocal==1) wputsxy(STATWIN, 8, 1, "ù°ƒÈ      ");
	 else
	 if ( SioDCD(port) )
	 {
		  if (DoNullModem) wputsxy(STATWIN, 8, 1, "COM1 	 ");
		  else wputsxy(STATWIN, 8, 1, "∑A∏·      ");
	 }
	 else wputsxy(STATWIN, 8, 1,"∏Û≠¢îÅã°∫ó");

	 if ( (bWaiting==0) && ( (bLocal==1) || (SioDCD( port ) ) ) )
	 {
			time_process();
			itoa(USER.stU.UsedTime,mins,10);
			strcat(mins,"¶Ö");
			wputsxy(STATWIN, 16-strlen(etimestr), 1, mins);
	 }
	 if (STAT==HOST_STAT || (STAT==USER_STAT && USER.UserNo==nGUEST) )
	 {
			 rectangle(ax2apx(32)-1, ay2apy(30),
								 ax2apx(32), ay2apy(30)+_CW->linespace);
			 rectangle(ax2apx(41)-1, ay2apy(30),
								 ax2apx(41), ay2apy(30)+_CW->linespace);
			 rectangle(ax2apx(54)-1, ay2apy(30),
								 ax2apx(54), ay2apy(30)+_CW->linespace);
			 wputsxy(STATWIN, 20, 1, "∂Öµw∏a:");
			 wputsxy(STATWIN, 27, 1, existSysop ? "∑∂∑q":"¥Ù∑q");
			 wputsxy(STATWIN, 33, 1, "≠°ü°:");
			 wputsxy(STATWIN, 38, 1, bSound ? "≈q":"èq");
			 wputsxy(STATWIN, 42, 1, bUsePartT ? strPartTime:"ÃaÀa ß°¨a∂w");
			 wputsxy(STATWIN, 55, 1, "Ø°àe∑e–ó:");
			 wputsxy(STATWIN, 64, 1, bTBank ? "µiü±":"îh”±");
	 }
	 else if (STAT==USER_STAT)
	 {
			 char tPN[15],sSPEED[10],tWP[12];
			 rectangle(ax2apx(30)-1, ay2apy(30),
								 ax2apx(30), ay2apy(30)+_CW->linespace);
			 rectangle(ax2apx(40)-1, ay2apy(30),
								 ax2apx(40), ay2apy(30)+_CW->linespace);
			 rectangle(ax2apx(48)-1, ay2apy(30),
								 ax2apx(48), ay2apy(30)+_CW->linespace);
			 rectangle(ax2apx(61)-1, ay2apy(30),
								 ax2apx(61), ay2apy(30)+_CW->linespace);
			 wputsxy(STATWIN, 20+4-strlen(USER.stU.NAME)/2, 1, USER.stU.NAME);
			 wputsxy(STATWIN, 31+4-strlen(USER.stU.ID)/2, 1, USER.stU.ID);
			 strcpy(tPN,USER.stU.PEOPLENO);
			 tPN[6]=0;
			 wputsxy(STATWIN, 41, 1, tPN);
			 strncpy(tWP, USER.stU.WORKPLACE, 11);
			 tWP[11]=0;
			 if (ishangul1st(tWP,10)) tWP[10]=0;
			 wputsxy(STATWIN, 49, 1, tWP);
			 ltoa(SPEED,sSPEED,10);
			 sSPEED[9]=0;
			 wputsxy(STATWIN, 62 + 3-strlen(sSPEED)/2, 1, sSPEED);
	 }
}
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
				case ',':
				case ' ':
						if (iPARA!=-1)
						{
							param[num][++iPARA]=0;
							exitloop=true;
						}
						break;
				case '-':
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
						if (iPARA!=-1) param[num][++iPARA]=0;
						else --now; // in end, if a new param is NULL, --now;
						exitloop=true;
						end_of_loop=true;
						break;
				default :
						if (iPARA <= lenPARAM-3) param[num][++iPARA] = now;

			}

		}
	}
	++num;
	return NOERR;
}
bool GoOnWithSelectedNum(int no, char param[maxPARAM][lenPARAM], int Help, int Qst, int max_items)
{
	 int paramc=0,j, iStart=0,iEnd=0,items=0;
	 if (!strcmp(param[1],"-"))
	 {
		 ReadDataFile(Help);// HELP...
		 return false;
	 }
	 for (paramc=1; paramc<no; paramc++)
	 {
		 if ( !is_int(param[paramc]) || strlen(param[paramc]) > 5 ||
			  atol(param[paramc]) > 32767  )
		 {
			  ReadDataFile(Help);
			  return false;
		 }

		 if (  (paramc<=no-3) && !strcmp(param[paramc+1],"-") )
		 {
			  if ( is_int(param[paramc+2]) )
			  {
				  iStart = atoi( param[paramc] );
				  iEnd = atoi( param[paramc+2] );
				  if ( iStart >= iEnd )
				  {
					  ReadDataFile(Help);// help
					  return false;
				  }
				  for(j=iStart; j<=iEnd; j++) {c_hprintf("%i ",j); ++items;}
				  paramc+=2;
			  } else { ReadDataFile(Help); return false; }
		 }
		 else {c_hprintf("%s ",param[paramc]); ++items;}
	 }
	 ReadDataFile(54); // You selected these line..
	 if (items > max_items)
	 {
		c_hprintf("–eå·§ÂµA %iàÅ åaª°†e ¨Â»Ç–i ÆÅ ∑∂Øsì°îa.\n\r",max_items);
		return false;
	 }
	 if (Qst) // when Qst is zero, Do not give any question.
	 {
		ReadDataFile(Qst); // question? [y/n]
		if ( AnswerIs('N','N',false) ) return false; // ans is not Y , y
	 }
	 return true;
}
int SelectProtocol(int& nProto)
{
	int i;
	char ans[3];
	// DEBUG : Protocol ansi File output routine should be here.
	do
	{
		 if (!ReadAnsiFile("PROTOCOL.MSG") )
		 {
				for (i=1; i<=10; i++)
				{
					if (PROTO[i-1].Exec[0]!=0)
					c_hprintf("\n\r [%i] %s", i, PROTO[i-1].Exec);
				}
				ReadDataFile(73); // select protocol
		 }
		 c_hgetln(ans,"P",2);
		 nProto=atoi(ans);
	} while(  (nProto<1 ||  nProto>10 || PROTO[nProto-1].Exec[0]==0) &&
			  ( strcmp(ans,"P") && strcmp(ans,"p") )  );
	if ( !strcmp(ans,"P") || !strcmp(ans,"p") ) return CANCEL;
	return NOERR;
}

// multi file downloading ...
// by communication with class CFileStack 's instance, sFILE
int ExecuteProtocol(int nProto, int mode)
{
	int iOri=0,iTmp=0,argc=0,ret,i;
	char numstr[20],OriginParam[31],*argv[31],TmpArg[31];
	switch(mode)
	{
		case mUPLOAD   : strcpy(OriginParam, PROTO[nProto-1].Up);  break;
		case mDOWNLOAD : strcpy(OriginParam, PROTO[nProto-1].Dn);
	}
	argv[argc]=(char*)malloc(strlen(InstDir)+strlen(PROTO[nProto-1].Exec)+3);
	strcpy(argv[argc], strcat2(strcat2(InstDir,"\\"), PROTO[nProto-1].Exec));
	++argc;
	memset(TmpArg, 0, 31);

	while( 1 )
	{

		while( OriginParam[iOri] == '%')
		{
			switch( OriginParam[++iOri] )
			{
				case 's' :
				case 'S' :
					ltoa(SPEED, numstr, 10);
					strcat(TmpArg, numstr);
					iTmp=strlen(TmpArg);  // iNew always points 0
					++iOri;
					break;
				case 'p' :
				case 'P' :
					itoa(port+1, numstr, 10);
					strcat(TmpArg, numstr);
					iTmp=strlen(TmpArg);
					++iOri;
					break;

				case 'f' :
				case 'F' :
					if (!sFILE.Empty())
					{



						argv[argc] = (char*)malloc(sFILE.TopSize()+1);
						if (argv[argc]==NULL) halt("ERROR : NOT ENOUGH MEMORY WHILE EXECUTING PROTOCOL.-F");
						sFILE.Pop(argv[argc]);
						//hprintf("\n\rargv[%i] --> %s",argc, argv[argc]);  getch();
						++argc;
						--iOri; // go back to '%'
					} else ++iOri;
			 }
		}
		if ( OriginParam[iOri]==' ' || OriginParam[iOri]==0 )
		{
			  if (iTmp!=0)
			  {
				 TmpArg[iTmp]=0;
				 argv[argc] = (char*) malloc(strlen(TmpArg)+1);
				 if (argv[argc]==NULL) halt("ERROR : NOT ENOUGH MEMORY WHILE EXECUTING PROTOCOL.");
				 strcpy(argv[argc], TmpArg);
				 ++argc;
				 iTmp=0;
				 memset(TmpArg, 0, 31);
			  }
			  if ( (OriginParam[iOri]==0) || (argc >=30) )
			  {
				 argv[argc]=NULL;
				 break;
			  }
			  ++iOri;
		}
		else TmpArg[iTmp++]=OriginParam[iOri++];
	}
	i=-1;
	/*while(argv[++i] != NULL) hprintf("\n\rargv[%i] : \'%s\'",i,argv[i]);
	printf("\ni-->%i, argc--->%i",i,argc);
	getch();*/

	if ( chdir( DownDir )  ) halt("ERROR : Can't find download directory.");
	ReadDataFile(72); // run your protocol.

	ret=SpawnProg(P_WAIT, argv[0], argv, UpTimeRate);

	for (i=0; i<argc; i++) free(argv[i]);

	if (ret==0)
	{
		if (mode==mUPLOAD) ReadDataFile(66); // upload completed
		if (mode==mDOWNLOAD) ReadDataFile(67); // download completed
	}
	else
	if (ret == -1)
	{
		switch (errno)
		{
		  case   ENOENT : ReadDataFile(68);   break;
		  case  ENOEXEC : ReadDataFile(69);   break;
		  case   ENOMEM : ReadDataFile(70);   break;
		}
		ReadDataFile(71);
	}                                         //DEBUG - Can be runtime err.
	if ( chdir( strcat2(strcat2(InstDir,"\\"),MENU[nAcc].index ) ) )
		halt("ERROR : Can't change directory to pds directory.");
	return ret;
}
//--------------------------------------------------------------------------
//                   PROCESS RELATED FUNCTION
//--------------------------------------------------------------------------
int Process7CharMacro(const char* macro)
{
	 char tMacro[MAX_MACRO_LEN+1];
	 char mode;
	 int nMenu;
	 mode = macro[0];
	 strcpy(tMacro, macro+1);
	 tMacro[6]=0;
	 while(1)
	 {
		  if (mode =='A' || mode == 'a' || mode == 'N'|| mode=='n'|| mode=='D' || mode =='d')
		  {
				 for (nMenu=1; nMenu<=MenuNo; nMenu++)
				 {
					  if(!stricmp(tMacro, MENU[nMenu-1].index))
					  {
							  if (MENUDATA[nMenu-1].alldata >=0)
							  switch( mode )
							  {
								  case 'n' :
								  case 'N' : c_hprintf("%5i", MENUDATA[nMenu-1].newdata);
												 break;
								  case 'a' :
								  case 'A' : c_hprintf("%5i", MENUDATA[nMenu-1].alldata);
												 break;
								  case 'd' :
								  case 'D' : c_hprintf("%2i-%2i",MENUDATA[nMenu-1].month, MENUDATA[nMenu-1].day);
							  }
							  return 1;
					  }
				 }
		  }
		  return 0;
	 }
	 return 1;
}
int Process6CharMacro(const char* macro)
{
	 char tMacro[MAX_MACRO_LEN+1];
	 strcpy(tMacro, macro);

	 tMacro[6]=0;
	 while(1)
	 {
		 if (!strcmp(tMacro,"–ó¨Âª°"))  {strcpy(temp_str,MENU[nAcc].go); break;}
		 return 0;
	 }
	 c_hputs(temp_str);
	 return 1;
}
int Process4CharMacro(const char* macro)
{
	 char tMacro[MAX_MACRO_LEN+1];
	 strcpy(tMacro, macro);

	 tMacro[4]=0;

	 while(1)
	 {
		 if (!strcmp(tMacro,"¥a∑°") )  { c_hputs(USER.stU.ID); break;}
		 if (!strcmp(tMacro,"∑°üq") )  { c_hputs(USER.stU.NAME); break; }
		 if (!strcmp(tMacro,"∫Å£•") )  { c_hputs(USER.stU.PEOPLENO); break; }
		 if (!strcmp(tMacro,"∫Å≠°") )  { c_hputs(USER.stU.ADDRESS); break; }
		 if (!strcmp(tMacro,"∂ÅÕe") )  { c_hputs(USER.stU.MAILNO); break; }
		 if (!strcmp(tMacro,"∏Â—¡") )  { c_hputs(USER.stU.TELNO); break; }
		 if (!strcmp(tMacro,"´°´°") )  { c_hputs(USER.stU.BBNO); break; }
		 if (!strcmp(tMacro,"∑©»·") )  { c_hputs(USER.stU.WORKPLACE); break; }
		 if (!strcmp(tMacro,"°A∑©") )  { c_hputs(USER.stU.MEMO[0]); break; }
		 if (!strcmp(tMacro,"°A∑°") )  { c_hputs(USER.stU.MEMO[1]); break; }
		 if (!strcmp(tMacro,"°A¨q") )  { c_hputs(USER.stU.MEMO[2]); break; }
		 if (!strcmp(tMacro,"âAØ°") )  { itoa(USER.stU.BbsAct, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∏aûa") )  { itoa(USER.stU.PdsAct, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∏a¥Û") )  { itoa(USER.stU.UpDataSize, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∏aîa") )  { itoa(USER.stU.DnDataSize, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¨aØ°") )  { itoa(USER.stU.UsedTime, temp_str, 10); break; }
		 if (!strcmp(tMacro,"êqØ°") )  { itoa(USER.stU.LeftTime, temp_str, 10); break; }
		 if (!strcmp(tMacro,"Ø°∑e") )  { itoa(USER.stU.TimeBank, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∏ÒÆÅ") )  { itoa(USER.stU.Point, temp_str, 10); break; }
		 if (!strcmp(tMacro,"î·∏Ò") )
		 {
				 if ( Le2I(USER.stU.Level) < LevelNo-1 )
						 itoa(LEVEL[Le2I(USER.stU.Level)+1].point -
								USER.stU.Point,temp_str,10);
				 else  strcpy(temp_str, "¶âàaìw");
				 break;
		 }
		 if (!strcmp(tMacro,"ùA•I") )  { itoa(USER.stU.Level, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∂wú∑") )  { itoa(USER.stU.DnableSize, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∏Û≠¢") )  { itoa(USER.stU.LoginNo, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∑•ëe") )  { itoa(USER.stU.LoginTime.year, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∑•∂©") )  { itoa(USER.stU.LoginTime.month, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∑•∑©") )  { itoa(USER.stU.LoginTime.day, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∑•Ø°") )  { itoa(USER.stU.LoginTime.hour, temp_str, 10); break; }
		 if (!strcmp(tMacro,"∑•¶Ö") )  { itoa(USER.stU.LoginTime.min, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¥aëe") )  { itoa(USER.stU.LogoutTime.year, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¥a∂©") )  { itoa(USER.stU.LogoutTime.month, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¥a∑©") )  { itoa(USER.stU.LogoutTime.day, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¥aØ°") )  { itoa(USER.stU.LogoutTime.hour, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¥a¶Ö") )  { itoa(USER.stU.LogoutTime.min, temp_str, 10); break; }
		 if (!strcmp(tMacro,"àaëe") )  { itoa(USER.stU.JoinTime.year, temp_str, 10); break; }
		 if (!strcmp(tMacro,"àa∂©") )  { itoa(USER.stU.JoinTime.month, temp_str, 10); break; }
		 if (!strcmp(tMacro,"àa∑©") )  { itoa(USER.stU.JoinTime.day, temp_str, 10); break; }
		 if (!strcmp(tMacro,"àaØ°") )  { itoa(USER.stU.JoinTime.hour, temp_str, 10); break; }
		 if (!strcmp(tMacro,"àa¶Ö") )  { itoa(USER.stU.JoinTime.min, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¬ÅØ°") )  { itoa(LEVEL[Le2I(USER.stU.Level)].time, temp_str, 10); break; }
		 if (!strcmp(tMacro,"¬Åîa") )  { itoa(LEVEL[Le2I(USER.stU.Level)].sizeDN, temp_str, 10); break; }
		 if (!strcmp(tMacro,"œ©ùA") )  { itoa(MENU[nAcc].level,temp_str,10); break; }
		 if (!strcmp(tMacro,"πA°¢") )  { strcpy(temp_str, MENU[nAcc].title); break; }
		 if (!strcmp(tMacro,"ß°ß°") )  { c_hputs(bName); break; }
		 if (!strcmp(tMacro,"ª°∂ë") )  { c_hclrscr(); break; }
		 if (!strcmp(tMacro,"†Ò¬ë") )
		 {
			 char tc[2];
			 c_hputs("[ENTER] üi íÅüa≠A∂a");
			 c_hgetln(tc,"",1);
			 break;
		 }
		 if (!strcmp(tMacro,"—e∏Å") )  { itoa(NowTop,temp_str,10); break; }
		 if (!strcmp(tMacro,"∏Â¡A") )  { itoa(All,temp_str,10); break; }
		 if (!strcmp(tMacro,"îqîw") )
		 {
			if ( MENU[nAcc].sysid[0] == 0 ) strcpy(temp_str, "¥Ù∑q");
			else strcpy(temp_str, MENU[nAcc].sysid);
			break;
		 }
		 if (!strcmp(tMacro,"êq°A") ) { ultoa(farcoreleft(),temp_str,10); break; }
		 if (!strcmp(tMacro,"¡∑∏Û") ) { ultoa(nAllLogin,temp_str,10); break;}
		 if (!strcmp(tMacro,"ówãs") )
		 {
				if (MENUDATA[nAcc].signum!=0) strcpy(temp_str, SigGrade[USER.GetGrade()]);
				else strcpy(temp_str, Grade[USER.GetGrade()] );
				break;
		 }
		 return 0;
	 }
	 // when macro is found.
	 c_hprintf("%s",temp_str);
	 return 1;
}

int ProcessMacro(const char* macro)
{
	 memset(temp_str,0,TEMP_STR_LEN+1);
	 if ( Process7CharMacro(macro) ) return 7;
	 if ( Process6CharMacro(macro) ) return 6;
	 if ( Process4CharMacro(macro) ) return 4;
	 return 0;
}

void time_process()
{
		time_t now_time;
		char tmptime[15],etime[8];
		int usingT;
		gettime(&NOW);
		usingT= ElapseTime(tLogin.hour, tLogin.min,
												NOW.ti_hour, NOW.ti_min);
		if ( aliveUSER )
		{
			 itoa( usingT, etime,10 );
			 if (strcmp(etimestr,etime))
			 {
					 if ( (usingT!=0) && (USER.stU.LeftTime>0) )
							USER.stU.LeftTime-=1;
					 USER.stU.UsedTime=usingT;
					 strcpy(etimestr,etime);
					 strcat(etime, "¶Ö");
					 wputsxy(STATWIN, 16-strlen(etimestr), 1, etime);
					 if ( !bPDrun && (USER.stU.LeftTime <= 5) && (USER.stU.LeftTime >= 1) )
					 {
							 ReadDataFile(41); // c_hgetln function must be ended.
					 }
			 }
			 if (!bWaiting && !bPDrun && ( USER.stU.LeftTime<=0 ) )
			 {
					 bUserNotExist=1;  // c_hgetln function must be ended.
					 if (!bInputId)
					 {
							ReadDataFile(42);  // you used all time.. now running artifitial inteligence.
							WriteLogData("‘ê Ø°àe∑i ¢ÅñÅ ¨a∂w–aµa —°ØaÀaàa àwπAù° ∏Û≠¢ èg∑q ‘ë");
					 }
			 }
		}
		time(&now_time);
		strcpy(tmptime, ctime(&now_time)+11);
		tmptime[8]=0;
		if (strcmp(timestr,tmptime))
		{
			 strcpy(timestr,tmptime);
			 wputsxy(STATWIN, 71, 1, timestr);
		}
}



// c == 0 : getch() function's first return value
// c != 0 : hgetch() function's return vlaue
// _ALT_S : getch() return value macro constant
//  ALT_S : hgetch() return value macro constant
bool process_ctrlkey(int& ch)
{
		if (ch==0) ch = getch();
		switch (ch) {
		case _ALT_D :
		case  ALT_D :
				DoDosShell();
				break;

		case _ALT_X :
		case  ALT_X :
				halt();
				break;

		case _ALT_M :
		case  ALT_M :
				SioHayes(port, WaitInit);
				break;
  //  case _CTRL_I :
		case  CTRL_I :
				getLocalInit();
				break;
		case _ALT_I :
		case  ALT_I :
				getWaitInit();
				break;
		case _ALT_C :
		case  ALT_C :
				ChatBox();
				break;
		case _ALT_L :
		case  ALT_L :
				LocalConnect();   // detect bLocal and processing routine is included
				break;
		case _ALT_K :
		case  ALT_K :
				SendFile();
				break;
		case  ALT_G :
		case _ALT_G :
				GrimBox(35, 12);
				break;
		case  ALT_S :
		case _ALT_S :
				SysopMenu();
				break;
//		case _CTRL_S :
		case  CTRL_S :
				TemporarySysop();
				break;
//		case _CTRL_U :
		case  CTRL_U :
				UserSet();
				break;
		case _F2 :
		case  F2 :
				if (existSysop) existSysop=0;
				else existSysop = 1;
				if (STAT==HOST_STAT)
				wputsxy(STATWIN, 27, 1, existSysop ? "∑∂∑q":"¥Ù∑q");
				break;
		case _F3 :
		case  F3 :
				if (bUsePartT) bUsePartT=0;
				else bUsePartT=1;
				if (STAT==HOST_STAT)
				wputsxy(STATWIN, 42, 1, bUsePartT ? strPartTime:"ÃaÀa ß°¨a∂w");
				break;
		case _F4 :
		case  F4 :
				if (bSound) bSound=0;
				else bSound=1;
				if (STAT==HOST_STAT)
				wputsxy(STATWIN, 38, 1, bSound ? "≈q":"èq");
				break;
		case _F5 :
		case  F5 :
				if (bTBank) bTBank=0;
				else bTBank=1;
				if (STAT==HOST_STAT)
				wputsxy(STATWIN, 64, 1, bTBank ? "µiü±":"îh”±");
				break;
		case _F6 :
		case  F6 :
				HangUp();
				break;

		case _F7 :
		case  F7 :
				RunCommProg();
				break;

		case _F8 :
		case  F8 :
				RunEditProg();
				break;
		case _F9 :
		case  F9 :
				InviteChat();
				break;
		case _F10   :
		case  F10   :
				PD->run();
				break;
		default : return false;
		}
}
