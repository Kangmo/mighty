#include "headers.h"

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
//   WILL BE PERISHED BY COPY RIGHT LAW.            1995.11.1 KIM KANGMO   //
//                                                                         //
//-------------------------------------------------------------------------//
char *Grade[] = {
			  "¬a¶wº—»¡ÒA¶¥",
			  "§¡ÒA¶¥",
			  "ÒA¶¥3",
			  "ÒA¶¥2",
			  "ÒA¶¥1",
			  "¸÷ÒA¶¥",
			  "¦¶…µw¸a",
			  "¶…µw¸a",
			  ""};

char *SigGrade[] = {
			  "­¥“±",
			  "§¡ÒA¶¥",
			  "ÒA¶¥3",
			  "ÒA¶¥2",
			  "ÒA¶¥1",
			  "¸÷ÒA¶¥",
			  "¦¶…µw¸a",
			  "¶…µw¸a",
			  ""};

//----------------------------------------------------------------------------
char sName[11], sId[9], bName[11], InstDir[51], DownDir[51], AnsiDir[51],
		 ArcDir[51], WaitInit[61], LocalInit[41],
		 LoginId[11], VirOrder[41], HackWord[41], SmPass[9];
int  port=-1, speed, parity, data, stop, HanFontType, EngFontType, VirDetect,
		 HackDetect, OpMode, PeopleNum, HanBoard, InitGab, SonnimLev,
		 JoinLev, BbsPoint, UpPoint, UpSizeRate, UpTimeRate, InputLimTime,
		 LevelNo, DoNullModem;

int FirstGrade, GiveDnableSize, SuccDnLoad, Fifo, Flow;
int MinBbsSize, MinPdsSize;
unsigned MinSpeed;
char EmulPro[41];
char EditPro[41];

long SPEED;
int nTodayLogin=0, nNewJoin=0, nSonnimLogin=0;
unsigned long nAllLogin;
char LastUserID[9]="´ô·q";
char LastUserNAME[9]="´ô·q";

int  NowTop, All;
int  MenuNo, MaxUserNo,nAcc, RealGrade;
unsigned char UserStr[max_line];
unsigned char SysopStr[max_line];
int u_idx=1, s_idx=1;
int MaxGetln;
int ERROR_NO=0;
int escstep=0,ScrollTime=onNORMAL;
char *temp_str, strPartTime[12];
char timestr[15],etimestr[6];
unsigned long first_core;
unsigned char LOGIN[11];
char  existSysop, bLocal, bUsePartT=1,bSound=1,
		bAutoHan,bTBank=1,STAT,aliveUSER=0,bPDrun=0,bWaiting,
		bDosScrSaved=0,bUserNotExist=0,bTempSysopOn = 0,
		bSysopHangUp, bPdRan=0, bChatMode, bInputId=0,
		bUserTypeEnter=0, bPassInput=0, bChatting=0;
char bDontSendComm=0, bFrameExist=0,bUserStringActive=0;
int bHanjaLoaded=ERR_NOTFOUND, bEgrLoaded=ERR_NOTFOUND,
	bKssLoaded=ERR_NOTFOUND, bHgrLoaded=ERR_NOTFOUND;
struct _time OpStart, OpEnd;
struct time NOW;
struct _AllTime tLogin;
struct date Today;
struct _level LEVEL[15];
struct _Proto PROTO[10];
struct _IdIndex far *IdIndex;
struct menu_t far *MENU;
struct menudata_t *MENUDATA;
window_t statwin, hanjabox, chatwin;
//unsigned char far *bufCUR;
//int  bxC,byC;
class _SCR SCR;
class _rCOLOR rCOLOR;
class UserClass USER;
class _PD *PD;
class SuperClass* runOBJ;
class CDataFile *DF;
class CFileStack sFILE;
//class _TempQueue *TRASH;
//----------------------------------------------------------------------------



int main()
{
	 first_core = farcoreleft();
	 PrintLogo();
	 MemoryManagerInit();
	 readCfg();
	 varInit();
	 readHostInfo();
	 readMenuData();
	 readProtocol();
	 DIRprocess();
	 commInit();
	 SaveDosScr();
	 hanInit();
	 ConfigInit();
	 InitLogData();

	 PD = new _PD(1, 2, 3, 15, 4, 3, 11, 15, 7, 14, 7, 9, 13, 15, 8);
	 bPdRan=1;
	 appObject(WAIT, NULL);
	 for(;;) runObject();
}
