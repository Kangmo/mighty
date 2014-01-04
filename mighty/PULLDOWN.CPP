#include "hanbgi.h"
#include "han240.h"
#include "hanmeq.h"
#include "hanmou.h"
#include "danbi.h"
#include <bios.h>
#include <conio.h>
#include <fstream.h>
#define SCRX 15
#define SCRY 10
#define SMX 4
#define SMY 5
#define MBC WLIGHTGREEN
#define MBKC WLIGHTGRAY
#define MAXMENU 300
#define GABX 4
#define MLINES 24
#define MAXX 7
#define SMEY 9
#define SMEX 40
#define NCDLINECOLOR WDARKGRAY
#define UPBARSTARTY 44
#define DNBARSTARTY 435
#define FS 127
#define VER 100
void Tempfunc()
{}

void MightyIs(), MailTo(), DosShell(), ExitPro(), Getport(), Getspeed(),
	  Getparity(), Getdata(), Getstop(), GetWaitInit(), GetLocalInit(),
	  GetInitGab(), GetsName(), GetsId(), GetbName(), GetInstDir(),
	  GetDownDir(), GetAnsiDir(),GetArcDir(),
	  GetLoginId(), GetSonnimLev(), GetJoinLev(), GetBbsPoint(),
	  GetUpPoint(), GetUpSizeRate(), GetUpTimeRate(), GetHanFontType(),
	  GetEngFontType(),GetHanBoard(), GetPeopleNum(), GetInputLimTime(),
	  GetVirDetect(), GetVirOrder(), GetHackDetect(), GetHackWord(),
	  GetOpMode(), GetDoNullModem(), GetOpStart(), GetOpEnd(), GetSmPass(),
	  MenuMake(), ProtoMake(), LevelMake(), GetSound(), GetSysopExist(),
	  GetFirstGrade(), GetGiveDnableSize(), GetSuccDnLoad(), GetFifo(),
	  GetFlow(), GetMinBbsSize(), GetMinPdsSize(), GetMinSpeed(),
	  GetUsePartTime(), GetEmulPro(), GetEditPro();
void ScreenInit();
void EditLevel( struct EditBox_ far *, int, int);
void ProtoEditBox(int );
void EditProto( struct EditBox_ far *, int, int, int );
void CopyString( char *, char *);
void EditMenu(void);
void ReadProtoFile();
int multi(int, int );
void kmPuts(int ,int ,char *);


void (*Embank[7][16])()={
				{MightyIs,MailTo,DosShell,Tempfunc,ExitPro,0},
				{Getport,Getspeed,Getparity,Getdata,Getstop,GetFifo,
				 GetFlow,Tempfunc, GetWaitInit,GetLocalInit,GetInitGab,
				 Tempfunc,GetMinSpeed,0},
				{GetsName,GetsId,GetbName,Tempfunc,GetSysopExist,
				 GetSound,Tempfunc,GetInstDir,GetDownDir,
				 GetAnsiDir,GetArcDir,0},
				{GetLoginId, GetSonnimLev, GetJoinLev, GetFirstGrade, Tempfunc,
				 GetBbsPoint, GetUpPoint, GetMinBbsSize, GetMinPdsSize, GetUpSizeRate,
				 GetUpTimeRate, GetGiveDnableSize, 0},
				{GetHanFontType, GetEngFontType, GetHanBoard, GetPeopleNum,
				 GetInputLimTime, Tempfunc, GetVirDetect, GetVirOrder,
				 GetHackDetect, GetHackWord, GetEmulPro, GetEditPro, Tempfunc,
				 GetSuccDnLoad, 0},
				{GetOpMode, GetDoNullModem, GetUsePartTime, GetOpStart, GetOpEnd, Tempfunc, GetSmPass,0},
				{MenuMake,ProtoMake,LevelMake,0}
};

//---------------------------------------------------------------------------
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
};

struct Proto {
		char Exec[13];
		char Up[31];
		char Dn[31];
		};


M Menu[MAXMENU+1];
Proto Protocol[10];

char sName[11]="‹±ˆw¡¡",sId[9]="SYSOP",bName[11]="HAHA",
		 InstDir[41]="C:\\MIGHTY",
		 DownDir[41]="C:\\MIGHTY\\DOWN", AnsiDir[41]="C:\\MIGHTY\\ANSI",
		 ArcDir[41]="C:\\UTIL\\ARC", WaitInit[61]="ATZ", LocalInit[61]="ATZ",
		 LoginId[11]=" a·¡Ë¡",
		 VirOrder[41]="C:\\UTIL\\VACCINE\\TV.EXE",
		 HackWord[41]="hack Hack HACK troy Troy TROY",
		 SmPass[9]="puhaha", SonnimLev[5]="30  ", JoinLev[5]="50  ",
		 BbsPoint[6]="3  ¸ñ", UpPoint[6]="5  ¸ñ", UpSizeRate[4]="2¤",
		 UpTimeRate[4]="1¤", InputLimTime[4]="5¦…",
		 OpStart[9]="23¯¡30¦…", OpEnd[9]="06¯¡00¦…",InitGab[4]="5¦…";
int    Version=100,port=2, speed=6, parity=0, data=1, stop=0,
		 HanFontType=1, EngFontType=1, VirDetect=0,
		 HackDetect=0, OpMode=0, PeopleNum=0,
		 HanBoard=0,LevelNo,DoNullModem=0,Sound=1,SysopExist=1,
		 FirstGrade=0, GiveDnableSize=0, SuccDnLoad=1, Fifo=2, Flow=0;
char   MinBbsSize[5]="0   ", MinPdsSize[5]="0   ",
		 MinSpeed[9]="0    BPS";
int    UsePartTime=0;
char   EmulPro[41]="c:\\i\\i.exe";
char   EditPro[41]="c:\\utlt\\u.exe";
char Level[15][24]  = {
											"   0/  30/  20/   0",
											"   0/  50/  30/ 200",
											"  10/ 100/  35/ 300",
											"  20/ 200/  40/ 350",
											"  40/ 300/  45/ 400",
											"  60/ 400/  50/ 450",
											"  80/ 500/  55/ 500",
											" 100/ 600/  60/ 550",
											" 130/ 700/  65/ 600",
											" 200/ 800/  70/ 650",
											" 300/ 900/  75/ 700",
											" 400/1000/ 120/1000",
											"5000/2000/ 180/2000",
											"6000/5000/ 180/4000",
											"9000/9000/1000/9000"
											};

void ReadDatum(void)
{
	int j,count;
	char ch, number[7];

	fstream InFile("Mighty.cfg",ios::in);
	if (!InFile) return;

	 count = -1; Version=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 Version += (number[j]-48)*multi(10, (count-j));

	 count = -1; port=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 port += (number[j]-48)*multi(10, (count-j));

	 count = -1; speed=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 speed += (number[j]-48)*multi(10, (count-j));

	 count = -1; parity=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		parity += (number[j]-48)*multi(10, (count-j));

	 count = -1; data=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 data += (number[j]-48)*multi(10, (count-j));

	 count = -1; stop=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 stop += (number[j]-48)*multi(10, (count-j));

	 count = -1; HanFontType=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 HanFontType += (number[j]-48)*multi(10, (count-j));

	 count = -1; EngFontType=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 EngFontType += (number[j]-48)*multi(10, (count-j));

	 count = -1; VirDetect=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 VirDetect += (number[j]-48)*multi(10, (count-j));

	 count = -1; HackDetect=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 HackDetect += (number[j]-48)*multi(10, (count-j));

	 count = -1; OpMode=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 OpMode += (number[j]-48)*multi(10, (count-j));

	 count = -1; PeopleNum=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 PeopleNum += (number[j]-48)*multi(10, (count-j));

	 count = -1; HanBoard=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 HanBoard += (number[j]-48)*multi(10, (count-j));

	 count = -1; LevelNo=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
		 LevelNo += (number[j]-48)*multi(10, (count-j));

		 count = -1;
		 while (InFile.get(ch), ch != FS) sName[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) sId[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) bName[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) InstDir[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) DownDir[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) AnsiDir[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) ArcDir[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) WaitInit[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) LocalInit[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) LoginId[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) VirOrder[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) HackWord[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) SmPass[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) SonnimLev[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) JoinLev[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) BbsPoint[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) UpPoint[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) UpSizeRate[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) UpTimeRate[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) InputLimTime[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) OpStart[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) OpEnd[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) InitGab[++count]=ch;

		 count = -1; DoNullModem=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 DoNullModem += (number[j]-48)*multi(10, (count-j));

		 count = -1; Sound=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 Sound += (number[j]-48)*multi(10, (count-j));

		 count = -1; SysopExist=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 SysopExist += (number[j]-48)*multi(10, (count-j));

		 count = -1; FirstGrade=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 FirstGrade += (number[j]-48)*multi(10, (count-j));

		 count = -1; GiveDnableSize=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 GiveDnableSize += (number[j]-48)*multi(10, (count-j));

		 count = -1; SuccDnLoad=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 SuccDnLoad += (number[j]-48)*multi(10, (count-j));

		 count = -1; Fifo=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 Fifo += (number[j]-48)*multi(10, (count-j));

		 count = -1; Flow=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 Flow += (number[j]-48)*multi(10, (count-j));

		 count = -1;
		 while (InFile.get(ch), ch != FS) MinBbsSize[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) MinPdsSize[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) MinSpeed[++count]=ch;

		 count = -1; UsePartTime=0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
		 UsePartTime += (number[j]-48)*multi(10, (count-j));

		 count = -1;
		 while (InFile.get(ch), ch != FS) EmulPro[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) EditPro[++count]=ch;

		 while( InFile.get(ch), ch!='\n');

		 for (int i=0; i<15; i++)
		 {
			 count = -1;
			 while (InFile.get(ch), ch != '\n') Level[i][++count]=ch;
		 }

	 InFile.close();
}
void SaveDatum(void)
{
	int i;
	if (access("MIGHTY.cfg",0)!=-1)
		if (remove("MIGHTY.cfg")==-1)
		{
			closehan();
			printf("ERROR : Can't over write to mighty.cfg");
			exit(0);
		}
	Version=VER;
	fstream OutFile("Mighty.cfg",ios::out);
	for (i=0; i<15; i++)
		if ( !strcmp( Level[LevelNo=i], "    /    /    /    ") ) break;
	if ( strcmp( Level[14], "    /    /    /    ") ) LevelNo=15;
	OutFile<< Version<< char(FS)<< port<< char(FS)<< speed<< char(FS)<< parity<< char(FS);
	OutFile<< data<< char(FS)<< stop<< char(FS)<< HanFontType<< char(FS);
	OutFile<< EngFontType<< char(FS)<< VirDetect<< char(FS);
	OutFile<< HackDetect<< char(FS)<< OpMode<< char(FS)<< PeopleNum<< char(FS);
	OutFile<< HanBoard<< char(FS)<<LevelNo<<char(FS)<< sName<< char(FS)<< sId<< char(FS);
	OutFile<< bName<< char(FS)<< InstDir<< char(FS)<< DownDir<<char(FS) ;
	OutFile<< AnsiDir<< char(FS)<< ArcDir<< char(FS)<< WaitInit<< char(FS);
	OutFile<< LocalInit<< char(FS);
	OutFile<< LoginId<< char(FS)<< VirOrder<< char(FS);
	OutFile<< HackWord<< char(FS)<< SmPass<< char(FS)<< SonnimLev<< char(FS);
	OutFile<< JoinLev<< char(FS)<< BbsPoint << char(FS);
	OutFile<< UpPoint<< char(FS)<< UpSizeRate <<char(FS)<< UpTimeRate<< char(FS);
	OutFile<< InputLimTime<< char(FS)<< OpStart << char(FS);
	OutFile<< OpEnd<< char(FS)<< InitGab<<char(FS)<< DoNullModem << char(FS);
	OutFile<< Sound<< char(FS)<< SysopExist<< char(FS)<< FirstGrade<< char(FS);
	OutFile<< GiveDnableSize << char(FS)<< SuccDnLoad<< char(FS);
	OutFile<< Fifo<<char(FS)<< Flow<< char(FS);
	OutFile<< MinBbsSize<< char(FS)<< MinPdsSize<< char(FS);
	OutFile<< MinSpeed<< char(FS)<<UsePartTime<<char(FS);
	OutFile<< EmulPro<<char(FS)<< EditPro<<char(FS)<<'\n';

	for (i=0; i<15; i++)  OutFile<< Level[i] <<'\n';
	OutFile.close();
}
class PullDown_ far * PD;

//---------------------------------------------------------------------------


void PullDownRtn(void);
void userinithan(void);


void main(void)
{
		 if (spDanbiInit(0L) == -1) return;
		 userinithan();
		 meq_init (MOU_ARROW16);
		 meq_show();
	 ReadDatum();
		 ReadProtoFile();
		 PullDownRtn();
		 mou_close();
}

void userinithan()
{
		 LINK_EGA_hputfont8x16();
		 LINK_EGA_hputfont16x16();
		 inithanlib( BGIMODE, HANDETECT, HAN8GD1, ENGGD5);
		 SELECT_hputfont8x16(AUTOSELECT);
		 SELECT_hputfont16x16(AUTOSELECT);
		 hsetallcolormap();
		 hsetwindowspalette(0);
}


void PullDownRtn()
{
		 PD = new PullDown_(SCRX-5,hgetmaxpx()-5-SCRX, SCRY);
		 int pd_x, pd_y;

		 char far *PopTitle[] = {
								" a·¡Ë¡",
								"¡¡•Q­U´ó",
								"¶…µw­U´ó",
								"BBS ­U´ó",
								"¦ˆa­U´óI",
								"¦ˆa­U´óII",
								"Íe»³‹¡",
								""};
		 int PopX[] = {SCRX, SCRX+90, SCRX+180, SCRX+270, SCRX+360,
									 SCRX+450, SCRX+540, 0};
		 int PopState[] = { 1, 1, 1, 1, 1, 1, 1, 0};

		 char far *PopMenu[7][16] = {
						 {
							 " a·¡Ë¡“e..",
							 "¹A  ¸b  ¸a",
							 "•¡  ¯a  ®É",
							 "LINE",
							 "{    ‹¡",
							 ""},
						 {
							 "¡¡ •Q  Í¡ Ëa",
							 "¡¡ •Q  ­¢ •¡",
							 "ÌŸ¡Ë¡  §¡Ëa",
							 "•A·¡Èa  §¡Ëa",
							 "¸÷ »¡  §¡ Ëa",
							 " 16550 FIFO ",
							 "Óa Ÿq  ¹A ´á",
							 "LINE",
							 "”‹¡º—Á¡‹¡ÑÁ",
							 "¡Äé  Á¡‹¡ÑÁ",
							 "Á¡‹¡ÑÁ  ˆe‰b",
							 "LINE",
							 "ÂA¸á¸ó­¢­¢•¡",
							 ""},
						 {
							 "¶…µw¸a   ·¡Ÿq",
							 "¶…µw¸a ´a·¡—¡",
							 "§¡§¡µA¯a ·¡Ÿq",
							 "LINE",
							 "¶…µw¸a   ·A¢",
							 "Ñ¡¯aËa   ­¡Ÿ¡",
							 "LINE",
							 "¬éÃ¡–E   ‰w¡",
							 "¸aža¯©   ‰w¡",
							 "´e¯¡ÑÁ·© ‰w¡",
							 "´sÂ‚ÑÁ·© ‰w¡",
							 ""},
						 {
							 "¡‹a·¥  ´a·¡—¡",
							 "­¥  “±  A  ¥I",
							 "—w ¢ ¯¡  A¥I",
							 "—w ¢ ¯¡  —w‹s",
							 "LINE",
							 "‰A¯¡Ìe¸b¬÷¸ñ®",
							 "¸aža´ó¡—a¸ñ®",
							 "‰A¯¡¢‰ÂA¸áÇa‹¡",
							 "¸aža ÂA¸á Ça‹¡",
							 "´ó¡—a¶wœ·¥¡¬w",
							 "´ó¡—a¯¡ˆe¥¡¬w",
							 "·©·©    ”a¶…¹A",
							 ""},
						 {
							 "Ðe‹i  ‹i©  »¡¸÷",
							 "µw¢…  ‹i©  »¡¸÷",
							 "Ðe‹i  ¸aÌe  »¡¸÷",
							 "º£¥—w¢¤åÑ¡ÑÂ·¥",
							 "·³b  ¹AÐe  ¯¡ˆe",
							 "LINE",
							 "¤a·¡œá¯aˆñ¬aµa¦",
							 "¤a·¡œá¯aˆñ¬a¡ww",
							 "ÐÇ·¸ažaˆñ¬aµa¦",
							 "ÐÇ·¸aža  ˆñ¬‚´á",
							 "É·¯¥  µA£IA·¡Èá",
							 "µA     —¡     Èá",
							 "LINE",
							 "µe­¢  ”a¶…  ¡—a",
							 ""},
						 {
							 "¶… µw  ¡¡ —a",
							 "é¡¡•Q  ¶…µw",
							 "ÌaËaÈa·±¬a¶w",
							 "¶…µw¯¡¸b¯¡ˆe",
							 "¶…µw¹·ža¯¡ˆe",
							 "LINE",
							 "¯¡¬s¡A“A´qÑ¡",
							 ""},
						 {
							 "¡A    “A",
							 "Ïa¡É¡Å©",
							 "A    ¥I",
							 ""},
		 };

		 int PopMenuState[7][16] = {
								 { 1, 1, 1,-1, 1, 0},
								 { 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1, 1, 0},
								 { 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 0},
								 { 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 0},
								 { 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 0},
								 { 1, 1, 1, 1, 1,-1, 1, 0},
								 { 1, 1, 1, 0},
		 };
//PD->PD_( SCRX, 630, SCRY, WWHITE, WLIGHTBLUE );
		 PD->TopMenu = PopTitle;
		 PD->TopX = PopX;
		 PD->TopState = PopState;

		 for ( int i=0; i < 7; i++) {
				PD->PopMenuSet( PopMenu[i], i);
				PD->PopStateSet( PopMenuState[i], i);
		 }

		 ScreenInit();
		 int flag;
		 for (;;) {
							 flag = PD->TopMenuSelect();
							 pd_x = PD->X();
							 pd_y = PD->Y();
							 if ( flag != -1) (*Embank[pd_x][pd_y])();
		 };
}

void MightyIs()
{
	char *pWin[] = {
		" ¬¡¶… Ñ¡¯aËa  a·¡Ë¡“e ˆ‚ÁA»¡Ð· ",
		" ‹¡¤ó·i ¬a¶w, ¹A¸b –A´ö·a£a¡ Ð· ",
		" Ò ÑÉ¤iÐe ¤á¹e´ó·¡ ˆa“wÐs“¡”a.  ",
		"  a·¡Ë¡“e ‰·ˆ ­¡ÏaËa¶Á´á·¡¡a, ¬w",
		" ´ó¸â ¡¢¸â·a¡ ³a·© ® ´ô¯s“¡”a. ",
		"                                 ",
		"   Mighty Host   ver 0.02        ",
		"     (¸á) REFINED  SOFTWARE      ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, " a·¡Ë¡“e..", pWin, WWHITE, WLIGHTBLUE);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();

}

void MailTo()
{
	char *pWin[] = {
		"                             ",
		"    Mighty HOST  ver 1.00b   ",
		"      e  —e  ·¡ : ‹±ˆw¡¡     ",
		"     Ða·¡ÉI  Id : Capcom     ",
		"     a¶Å±  Id : refined    ",
		"                             ",
		"  ‰¡a”ÐbŠa ÄñÏAÈáÐb‰Á '95  ",
		"                             ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "¹A ¸b ¸a", pWin, WWHITE, WLIGHTBLUE);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

void ScreenInit()
{
	spBar3d1(0,0,630,UPBARSTARTY-1);
	spBar3d1(0,UPBARSTARTY,630,DNBARSTARTY-1);
	PD->TopMenuInit(PD->X());
	spBar3d1(0,DNBARSTARTY,630,475);
	kmPuts(3,29,"#7@1¯¥ˆ‘q Ñ¡¯aËa MIGHTY @10ver 1.00b [ Ð·Ò ¶å95¶w  éË¡¡ ¥eÑÅ µ¸÷ ] @9(¸á) @4‹±ˆw¡¡");
}
void DosShell()
{
	mou_hide();
	hrestorecrtmode();
	textcolor( WLIGHTGREEN );
	cputs( "<<<<");
	textcolor( WWHITE );
	cputs( "  MIGHTY  Ver 0.02 ...  ");
	textcolor( WLIGHTGREEN );
	cputs( " >>>>" );
	system("");
	hsetgraphmode();
	hsetwindowspalette(0);
	ScreenInit();
	mou_show();
}

void ExitPro()
{
	char far *pMessage[] = {
							 "                      ",
							 ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"µ",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "¹·ža Ða¯¡‰V¯s“¡Œa?",
																			pMessage, pItem, 0);
	Scr.SetSaveOff();
	Scr.Restore();

	if ( flag ==  1 ) {
										SaveDatum();
										delete PD;
										exit(0);
										}
}
void Getport()
{
	char far *pMenu[5] = {
				 "    1  ¤å    ",
				 "    2  ¤å    ",
				 "    3  ¤å    ",
				 "    4  ¤å    ",
				 ""};


	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 4, "¡¡•Q Í¡Ëa", pMenu, port);
	Scr.SetSaveOff();

	if ( flag != -1 ) port=flag;
	Scr.Restore();
}
void Getspeed()
{
	char far *pMenu[11]= {
				 "      300    ",
				 "      600    ",
				 "     1200    ",
				 "     2400    ",
				 "     4800    ",
				 "     9600    ",
				 "    19200    ",
				 "    38400    ",
				 "    57600    ",
				 "   115200    ",
				 ""};


	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 10, "¡¡•Q­¢•¡", pMenu, speed);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) speed=flag;
	Scr.Restore();
}
void Getparity()
{
	char far *pMessage[] = {
							 "                       ",
							 ""};
	char far *pItem[] = {
								"´ô”a",
								" ODD",
								"EVEN",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "ÌŸ¡Ë¡ §¡Ëa", pMessage, pItem, parity);
	Scr.SetSaveOff();
	if ( flag != -1 ) parity = flag;
	Scr.Restore();
}

void Getdata()
{
	char far *pMessage[] = {
							 "                  ",
							 ""};
	char far *pItem[] = {
								"7 §¡Ëa",
								"8 §¡Ëa",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "•A·¡Èá §¡Ëa", pMessage, pItem, data);
	Scr.SetSaveOff();
	if ( flag != -1 ) data = flag;
	Scr.Restore();
}
void Getstop()
{
	char far *pMessage[] = {
							 "                  ",
							 ""};
	char far *pItem[] = {
								"1 §¡Ëa",
								"2 §¡Ëa",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "¯aÉ³ §¡Ëa", pMessage, pItem, stop);
	Scr.SetSaveOff();
	if ( flag != -1 ) stop =flag;
	Scr.Restore();
}

void GetWaitInit()
{
	int x=100,y=200;
	bool temp = _hangulmode;
	_hangulmode = false;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+502, y+50, "¸ó­¢ ”‹¡º— Á¡‹¡ÑÁ¡ww" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, WaitInit,
			 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-60s" );
	_hangulmode = temp;

	Scr.Restore();
}
void GetLocalInit()
{
	int x=100,y=220;
	bool temp=_hangulmode;
	_hangulmode=false;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+342, y+50, "¡Äé ¸ó­¢¯¡ Á¡‹¡ÑÁ¡ww" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, LocalInit,
			 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	_hangulmode = temp;
	Scr.Restore();
}
void GetInitGab()
{
	int x=190,y=198;
	Scr.SetSaveOn();
	spBoxWin( x, y, x+136, y+50, "Á¡‹¡ÑÁ ˆe‰b" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, InitGab,"9¦…", "%-3s" );
	Scr.Restore();
}

void GetsName()
{
	int x=190,y=140;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+120, y+50, "¯¡¬s ·¡Ÿq" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, sName,"XXXXXXXXXX", "%-10s" );
	Scr.Restore();
}
void GetsId()
{
	int x=190,y=156;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+136, y+50, "¯¡¬s ´a·¡—¡");
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, sId,"XXXXXXXX", "%-8s" );
	Scr.Restore();
}
void GetbName()
{
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+120, y+50, "BBS ·¡Ÿq" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, bName,"XXXXXXXXXX", "%-10s" );
	Scr.Restore();
}
void GetInstDir()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, " a·¡Ë¡ˆa ¬éÃ¡–E ‰w¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, InstDir,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();
	_hangulmode=temp;

	/*
	spBoxWin( 221, 210, 561, 264, " a·¡Ë¡ˆa ¬éÃ¡–E ‰w¡");
	Scr.SetSaveOff();

	kmPuts(30,16,"#10                                        ");
	hgotoxy(30,16);
	hgetln(InstDir, 40);

	_hangulmode = temp;
	Scr.Restore();
	*/
}
void GetDownDir()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "¸aža¯© ‰w¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, DownDir,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();

}
void GetAnsiDir()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "´e¯¡ÑÁ·©·¡ ·¶“e ‰w¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, AnsiDir,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();

}
void GetArcDir()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "´sÂ‚ÑÁ·©·¡ ·¶“e ‰w¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, ArcDir,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();

}
void GetLoginId()
{
	int x=280,y=102;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+150, y+50, "¡‹a·¥ ´a·¡—¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, LoginId,"XXXXXXXXXX", "%-10s" );
	Scr.Restore();
}
void GetSonnimLev()
{
	int x=280,y=118;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+126, y+50, "­¥“± A¥I" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, SonnimLev,"9999", "%-4s" );
	Scr.Restore();
}
void GetJoinLev()
{
	int x=280,y=134;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+150, y+50, "—w¢¯¡ A¥I" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, JoinLev,"9999", "%-4s" );
	Scr.Restore();
}
void GetBbsPoint()
{
	int x=280,y=150;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+180, y+50, "‰A¯¡Ìe ¸b¬÷¸ñ®" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, BbsPoint,"999¸ñ", "%-5s" );
	Scr.Restore();
}
void GetUpPoint()
{
	int x=280,y=166;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+186, y+50, "¸aža ´ó¡—a ¸ñ®" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, UpPoint,"999¸ñ", "%-5s" );
	Scr.Restore();
}
void GetUpSizeRate()
{
	int x=280,y=182;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+210, y+50, "´ó¡—a ¶wœ· ¥¡¬w§¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, UpSizeRate,"9¤", "%-3s" );
	Scr.Restore();
}
void GetUpTimeRate()
{
	int x=280,y=198;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+210, y+50, "´ó¡—a ¯¡ˆe ¥¡¬w§¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, UpTimeRate,"9¤", "%-3s" );
	Scr.Restore();
}
void GetHanFontType()
{
	 loadhanfont(1, "han8gd1.fnt", HINFO8X4X4);
	 loadhanfont(2, "han10md1.fnt", HINFO10X4X4);
	 loadhanfont(3, "han8gd2.fnt", HINFO8X4X4);
	 loadhanfont(4, "han8gd3.fnt", HINFO8X4X4);
	 loadhanfont(5, "han8gs1.fnt", HINFO8X4X4);
	 loadhanfont(6, "han8gs2.fnt", HINFO8X4X4);

		class PopUp_  SelectingFont;
		int flag;
		char far *pMenu[7] = {
					 "  Ðe‹i ‹i© 1¤å  ",
					 "  Ðe‹i ‹i© 2¤å  ",
					 "  Ðe‹i ‹i© 3¤å  ",
					 "  Ðe‹i ‹i© 4¤å  ",
					 "  Ðe‹i ‹i© 5¤å  ",
					 "  Ðe‹i ‹i© 6¤å  ",
					 ""};



		int PopMenuState[7] = { 1, 1, 1, 1, 1, 1, 0 };

		Scr.SetSaveOn();
			 spWin( 305, 139, 421, 245, "");
		Scr.SetSaveOff();

			 spBoxFill( 305, 139, 421, 245 , WLIGHTBLUE);
			 spBoxLine( 305, 139, 421, 245 , WWHITE,WDARKBLUE);

			 changehanfont(1);
			 kmPuts(40,10,"#9@15Ðe‹i‹i© 1¤å");
			 changehanfont(2);
			 kmPuts(40,11,"#9@15Ðe‹i‹i© 2¤å");
			 changehanfont(3);
			 kmPuts(40,12,"#9@15Ðe‹i‹i© 3¤å");
			 changehanfont(4);
			 kmPuts(40,13,"#9@15Ðe‹i‹i© 4¤å");
			 changehanfont(5);
			 kmPuts(40,14,"#9@15Ðe‹i‹i© 5¤å");
			 changehanfont(6);
			 kmPuts(40,15,"#9@15Ðe‹i‹i© 6¤å");

		Scr.SetSaveOn();
			 SelectingFont.PopUp( 150, 139, WWHITE, WBLACK, pMenu, PopMenuState);
		Scr.SetSaveOff();

		flag = SelectingFont.PopUpSelect();

		if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) )
		{
			 HanFontType = flag + 1;
			 changehanfont( HanFontType ) ;
			 int count = 1;
			 while (count ++ <= 6)
					if ( count != HanFontType ) releasehanfont(count);
			 ScreenInit();
		}
		else {
			 Scr.Restore();
			 Scr.Restore();
		}
}

void GetEngFontType()
{
	 loadengfont(1, "engmd2.fnt");
	 loadengfont(2, "engmd1.fnt");
	 loadengfont(3, "engmd3.fnt");
	 loadengfont(4, "engmd4.fnt");
	 loadengfont(5, "engmd6.fnt");
	 loadengfont(6, "enggd5.fnt");
	 loadengfont(7, "enggs6.fnt");


		class PopUp_  SelectingFont;
		int flag;
		char far *pMenu[8] = {
					 "  µw¢… ‹i© 1¤å  ",
					 "  µw¢… ‹i© 2¤å  ",
					 "  µw¢… ‹i© 3¤å  ",
					 "  µw¢… ‹i© 4¤å  ",
					 "  µw¢… ‹i© 5¤å  ",
					 "  µw¢… ‹i© 6¤å  ",
					 "  µw¢… ‹i© 7¤å  ",
					 ""};



		int PopMenuState[8] = { 1, 1, 1, 1, 1, 1, 1, 0 };

		Scr.SetSaveOn();
			 spWin( 305, 139, 421, 261, "");
		Scr.SetSaveOff();

			 spBoxFill( 305, 139, 421, 261 , WLIGHTBLUE);
			 spBoxLine( 305, 139, 421, 261 , WWHITE,WDARKBLUE);

			 changeengfont(1);
			 kmPuts(40,10,"#9@15ENGLISH NO 1");
			 changeengfont(2);
			 kmPuts(40,11,"#9@15ENGLISH NO 2");
			 changeengfont(3);
			 kmPuts(40,12,"#9@15ENGLISH NO 3");
			 changeengfont(4);
			 kmPuts(40,13,"#9@15ENGLISH NO 4");
			 changeengfont(5);
			 kmPuts(40,14,"#9@15ENGLISH NO 5");
			 changeengfont(6);
			 kmPuts(40,15,"#9@15ENGLISH NO 6");
			 changeengfont(7);
			 kmPuts(40,16,"#9@15ENGLISH NO 7");

		Scr.SetSaveOn();
			 SelectingFont.PopUp( 150, 139, WWHITE, WBLACK, pMenu, PopMenuState);
		Scr.SetSaveOff();

		flag = SelectingFont.PopUpSelect();

		if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) )
		{
			 EngFontType = flag + 1;
			 changeengfont( EngFontType ) ;
			 int count = 1;
			 while (count ++ <= 7) if ( count != EngFontType ) releaseengfont(count);
			 ScreenInit();
		}
		else {
			 Scr.Restore();
			 Scr.Restore();
		}


}
void GetHanBoard()
{
	char far *pMessage[] = {
							 " ¬a¶wÐa‰¡¸a Ða“e Ðe‹i ",
							 " ¸aÌe·i ‰i¸÷Ð º­A¶a ",
							 ""};
	char far *pItem[] = {
								"2¤é¯¢",
								"3¤é¯¢",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "Ðe‹i ¸aÌe",pMessage, pItem, HanBoard);
	Scr.SetSaveOff();

	if ( flag != -1)
	{
		 HanBoard = flag;
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
	}
	Scr.Restore();


}

void GetPeopleNum()
{
	char far *pMessage[] = {
							 "                    ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "º£¥—w¢¤åÑ¡ ˆñ¬a",
																		pMessage, pItem, PeopleNum);
	Scr.SetSaveOff();
	if ( flag != -1 ) PeopleNum = flag;
	Scr.Restore();
}

void GetInputLimTime()
{
	int x=350,y=220;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+144, y+50, "·³b¹AÐe¯¡ˆe" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, InputLimTime,"9¦…", "%-3s" );
	Scr.Restore();
}
void GetVirDetect()
{
	char far *pMessage[] = {
							 "                      ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "¤a·¡œá¯a ˆñ¬a", pMessage, pItem, VirDetect);
	Scr.SetSaveOff();
	if ( flag != -1 ) VirDetect = flag;
	Scr.Restore();
}

void GetVirOrder()
{

	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "¤a·¡œá¯a ˆñ¬a ¡ww" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, VirOrder,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();
	_hangulmode = temp;
}
void GetHackDetect()
{
	char far *pMessage[] = {
							 "                      ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "ÐÇ·,Ëa¡·¡ ¸ažaˆñ¬a",
																			pMessage, pItem, HackDetect);
	Scr.SetSaveOff();
	if ( flag != -1 ) HackDetect = flag;
	Scr.Restore();
}

void GetHackWord()
{
	int x=145,y=220;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+342, y+50, "ÐÇ·¸aža ˆñ¬a ”e´á" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, HackWord,
			 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();
}
void GetOpMode()
{
	char far *pMessage[] = {
							 "                             ",
							 ""};
	char far *pItem[] = {
								"‰·ˆ",
								"¤e‰·ˆ",
								"§¡‰·ˆ",
								""};

	Scr.SetSaveOn();

	int flag = spChoiceItemWin(-1, -1, "¶…µw ¡¡—a", pMessage, pItem, OpMode);
	Scr.SetSaveOff();
	if ( flag != -1 ) OpMode = flag;
	Scr.Restore();
}
void GetDoNullModem()
{
	char far *pMessage[] = {
							 "é¡¡•QÉ·¯¥·e ¡¡•Q´ô·¡ Ða“e É·¯¥·³“¡”a",
							 "¸åÑÁ¬å·i ·¡¶wÐaµa ¶…µwÐi¯¡ \"´eÐe”a\"¡",
							 "¬é¸÷Ða­a´¡ Ðs“¡”a.",
							 "é¡¡•Q·a¡ Ñ¡¯aËaŸi ¶…µwÐa¯¡‰V¯s“¡Œa?",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();

	int flag = spChoiceItemWin(-1, -1, "é¡¡•Q ¶…µw", pMessage, pItem, DoNullModem);
	Scr.SetSaveOff();
	if ( flag != -1 ) DoNullModem = flag;
	Scr.Restore();

}
void GetOpStart()
{
	int x=460,y=120;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+144, y+50, "¶…µw¯¡¸b¯¡ˆb" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, OpStart, "99¯¡99¦…", "%-8s" );
	Scr.Restore();
}
void GetOpEnd()
{
	int x=460,y=116;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+144, y+50, "¶…µw{‘¯¡ˆb" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, OpEnd, "99¯¡99¦…","%-8s" );
	Scr.Restore();
}
void GetSmPass()
{
	int x=460,y=140;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+120, y+50, "RDS ´qÑ¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, SmPass, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}
void GetSound()
{
	char far *pMessage[] = {
							 "BBS ¶…µw¯¡ Ñ¡¯aËa· ­¡Ÿ¡",
							 "Ÿi Œá‘½‰V¯s“¡Œa?  Åa‘½‰V",
							 "¯s“¡Œa?",
							 ""};
	char far *pItem[] = {
								"q",
								"Åq",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "Ñ¡¯aËa ­¡Ÿ¡",
																			pMessage, pItem, Sound);
	Scr.SetSaveOff();
	if ( flag != -1 ) Sound = flag;
	Scr.Restore();
}
void GetSysopExist()
{
	char far *pMessage[] = {
							 "                  ",
							 ""};
	char far *pItem[] = {
								"´ô·q",
								"·¶·q",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "¶…µw¸a ·A¢",
																			pMessage, pItem, SysopExist);
	Scr.SetSaveOff();
	if ( flag != -1 ) SysopExist = flag;
	Scr.Restore();
}
void GetFirstGrade()
{
	char far *pMenu[11]= {
								"   ¬a¶wº—»¡ÒA¶¥   ",
								"     §¡ ÒA ¶¥     ",
								"     ÒA ¶¥  3     ",
								"     ÒA ¶¥  2     ",
								"     ÒA ¶¥  1     ",
								"     ¸÷ ÒA ¶¥     ",
								"     ¦¶…µw¸a     ",
								"     ¶… µw ¸a     ",
								""};

	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 8, "—w¢¯¡  —w‹s", pMenu, FirstGrade);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) FirstGrade=flag;
	Scr.Restore();
}
void GetGiveDnableSize()
{
	char far *pMessage[] = {
							 "                  ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "·©·© ”a¶…¹A ¬a¶w",
																			pMessage, pItem, GiveDnableSize);
	Scr.SetSaveOff();
	if ( flag != -1 ) GiveDnableSize = flag;
	Scr.Restore();
}
void GetSuccDnLoad()
{
	char far *pMessage[] = {
							 "                      ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "µe­¢ ”a¶…¡—a ¬a¶w",
																			pMessage, pItem, SuccDnLoad);
	Scr.SetSaveOff();
	if ( flag != -1 ) SuccDnLoad = flag;
	Scr.Restore();
}
void GetFifo()
{
	char far *pMenu[11]= {
								"   ¬a¶w ´eÐq   ",
								"    1 byte     ",
								"    4 bytes    ",
								"    8 bytes    ",
								"   14 bytes    ",
								""};

	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 5, "16550 FIFO", pMenu, Fifo);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) Fifo=flag;
	Scr.Restore();
}
void GetFlow()
{
	char far *pMenu[11]= {
								"         ¬a¶w  ´eÐq          ",
								"     Ða—a ¶Á´á  ÓaŸq¹A´á     ",
								"     ­¡ÏaËa¶Á´á ÓaŸq¹A´á     ",
								"         –‰”a  ¬a¶w          ",
								""};

	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 4, "ÓaŸq ¹A´á(Flow Control)", pMenu, Flow);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) Flow=flag;
	Scr.Restore();
}
void GetMinBbsSize()
{
	int x=250,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+240, y+50, "ÂA¸á‰A¯¡¢‰Ça‹¡ (‹i¸a®)" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, MinBbsSize,"9999", "%-4s" );
	Scr.Restore();
}
void GetMinPdsSize()
{
	int x=250,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+240, y+50, "ÂA¸á ¸aža Ça‹¡ (KB”e¶á)" );
	Scr.SetSaveOff();
	spGetMunja( x+10, y+29, MinPdsSize,"9999", "%-4s" );
	Scr.Restore();
}
void GetMinSpeed()
{
	int x=250,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+160, y+50, "ÂA¸á ¸ó­¢­¢•¡" );
	Scr.SetSaveOff();
	spGetMunja( x+10, y+29, MinSpeed,"99999BPS", "%-8s" );
	Scr.Restore();
}
void GetUsePartTime()
{
	char far *pMessage[] = {
							 "                      ",
							 ""};
	char far *pItem[] = {
								"´eÐe”a",
								"Ðe”a",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "ÌaËaÈa·± ¬a¶wµa¦",
																			pMessage, pItem, UsePartTime);
	Scr.SetSaveOff();
	if ( flag != -1 ) UsePartTime = flag;
	Scr.Restore();
}
void GetEmulPro()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "É·¯¥ µA£IA·¡Èá ( PATHŒa»¡ ¡¡–)" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, EmulPro,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();
	_hangulmode=temp;
}
void GetEditPro()
{
	bool temp = _hangulmode;
	_hangulmode = false;
	int x=190,y=172;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+360, y+50, "¶A¦ µA—¡Èá ( PATHŒa»¡ ¡¡–)" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, EditPro,
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "%-40s" );
	Scr.Restore();
	_hangulmode=temp;
}
//----------------------------------------------------------------------
//                MENU  MAKE   PART
	 int no=0, MaxNo = 0;

void CopyString( char *cp1, char *cp2)
{
	while (*cp1++ = *cp2++);
}

void MenuScreenInit()
{
	spBar3d1(0,0,630,62);
	spBar3d1(0,63,630,475);
	kmPuts(4,2,"#7@15 a·¡Ë¡ Ñ¡¯aËa ver 0.02  @13¡A“A Íe»³‹¡               @15 (@14C@15)@1 REFINED SOFTWARE ");
	kmPuts(4,3,"#7@10INSERT@15 : @9¡A“AÂˆa   @11DEL @15:@9 ¡A“A¬b¹A   @12ENTER @15: @9¡A“AÍe»³  @14 ÑÁ¬iÎaÇ¡ @15: ·¡•· ");
}
void TopMenuInit()
{

			 Menu[1].X = 1;
			 Menu[1].Color = WYELLOW ;
			 Menu[1].RunNo = 0;
			 CopyString( Menu[1].Index ,"000000");
			 CopyString( Menu[1].Title ,"É³ ¡A “A            ");
			 CopyString( Menu[1].Type ,"SUBMENU");
			 CopyString( Menu[1].Go , "TOP     ");
			 CopyString( Menu[1].Level ,"0000");
			 CopyString( Menu[1].Point ,"0000");
			 Menu[1].Grade = 0;
			 Menu[1].Close = 0;
			 no++;
			 MaxNo++;

}

void InitMenu(int fr, int to)
{
		for (int i=fr; i <= to; i++) {
			 Menu[i].X = 0;
			 for (int j=0; j<6; j++) Menu[i].Index[j] = '0';
			 Menu[i].Index[6] = 0;
			 Menu[i].Head = 0;
			 for (j=0; j< 21; j++) Menu[i].Title[j] = 0;
			 for (j=0; j< 9; j++)
			 {
					 Menu[i].Type[j] = 0;
					 Menu[i].Go[j] = 0;
					 Menu[i].AnsiFile[j] = 0;
					 Menu[i].SysId[j] = 0;
					 Menu[i].Pass[j]=0;
			 }
			 for (j=0; j< 5; j++) {
					 Menu[i].Level[j] = 0;
					 Menu[i].Point[j] = 0;
			 }
			 Menu[i].Grade = 1;
			 Menu[i].Close = 0;
			 Menu[i].Color = 0;
			 Menu[i].RunNo = 0;
			 Menu[i].f2 = 0;
			 Menu[i].f3 = 0;
			 Menu[i].f4 = 0;
			 Menu[i].f5 = 0;
			 Menu[i].f6 = 0;
		}

}

void BitFieldInit_Ins()
{
	 if (no<=2) return;
	 int m,i,j,k,flag=0;
	 k=no;
	 for ( i=2; i <= Menu[k].X -1; i++) {
			 for ( j=k; j <= MaxNo; j++)
			 {
					if (Menu[j].X == i ) flag=1;
					if (flag==1) break;
			 }
			 for (m = j; m >= k; m--) if (Menu[j].X > Menu[m].X) flag=0;
			 switch ( i ) {
				 case 2 : Menu[k].f2= flag?1:0;  break;
				 case 3 : Menu[k].f3= flag?1:0;  break;
				 case 4 : Menu[k].f4= flag?1:0;  break;
				 case 5 : Menu[k].f5= flag?1:0;  break;
				 case 6 : Menu[k].f6= flag?1:0;
			 }
			 flag=0;
		}
}
void BitFieldInit_Del()
{
	 if (no<=2) return;
	 int m,i,j,k,flag=0;
	 for ( j=no-1;j>=2;j--) if (Menu[no].X==Menu[j].X) break;
	 for (k=j; k<=no; k++) {
		 for ( i=2; i <= Menu[k].X -1; i++) {
			 for ( j=k; j <= MaxNo; j++)
			 {
					if (Menu[j].X == i ) flag=1;
					if (flag==1) break;
			 }
			 for (m = j; m >= k; m--) if (Menu[j].X > Menu[m].X) flag=0;
			 switch ( i ) {
				 case 2 : Menu[k].f2= flag?1:0;  break;
				 case 3 : Menu[k].f3= flag?1:0;  break;
				 case 4 : Menu[k].f4= flag?1:0;  break;
				 case 5 : Menu[k].f5= flag?1:0;  break;
				 case 6 : Menu[k].f6= flag?1:0;
			 }
			 flag=0;
		 }
	 }
}
void NotSavedOnHard()
{
	char *pWin[] = {
		" Ða—a —¡¯aÇaµA“e ¸á¸wÐa»¡ ",
		" ´g‰¡ ¡A¡¡Ÿ¡µA e  q‰a ‘½ ",
		" ´v¯s“¡”a.                ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "´ia —aŸ³“¡”a", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

int multi(int x1,int x2)
{
	 if (x2==0) return 1;
	 while (x2-- > 1) x1 *=x1;
	 return x1;
}

void ReadMenuFile()
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
	 int i;
	 fstream  OutFile("MENUDATA.DAT",ios::out);

	 OutFile << MaxNo << '\n';

	 for (i=1; i<= MaxNo; i++)
	 {
		 OutFile << Menu[i].X;
		 OutFile.put(FS);
		 OutFile << Menu[i].Color;
		 OutFile.put(FS);
		 OutFile << Menu[i].Head;
		 OutFile.put(FS);
		 OutFile << Menu[i].Grade;
		 OutFile.put(FS);
		 OutFile << Menu[i].Close;
		 OutFile.put(FS);
		 OutFile << Menu[i].RunNo;
		 OutFile.put(FS);
		 OutFile << Menu[i].Index;
		 OutFile.put(FS);
		 OutFile << Menu[i].Title;
		 OutFile.put(FS);
		 OutFile << Menu[i].Type;
		 OutFile.put(FS);
		 OutFile << Menu[i].Go;
		 OutFile.put(FS);
		 OutFile << Menu[i].AnsiFile;
		 OutFile.put(FS);
		 OutFile << Menu[i].SysId;
		 OutFile.put(FS);
		 OutFile << Menu[i].Level;
		 OutFile.put(FS);
		 OutFile << Menu[i].Point;
		 OutFile.put(FS);
		 OutFile << Menu[i].Pass;
		 OutFile.put(FS);
		 OutFile << ( (Menu[i].f2 == 1) ? '1':'0');
		 OutFile.put(FS);
		 OutFile << ( (Menu[i].f3 == 1) ? '1':'0');
		 OutFile.put(FS);
		 OutFile << ( (Menu[i].f4 == 1) ? '1':'0');
		 OutFile.put(FS);
		 OutFile << ( (Menu[i].f5 == 1) ? '1':'0');
		 OutFile.put(FS);
		 OutFile << ( (Menu[i].f6 == 1) ? '1':'0');
		 OutFile.put('\n');

	 }
	 OutFile.close();
}
void qSaveMenu()
{
	char far *pMessage[] = {
							 "   »¡‹qŒa»¡ ¸b´óÐe   ",
							 "   ¡A“AŸi   ÑÁ·©¡   ",
							 "   ¸á¸wÐa‰V¯s“¡Œa?   ",
							 ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"  µ  ",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(310, 230,
							"¸á¸wÐa¯¡‰V¯s“¡Œa?", pMessage, pItem, 1);
	Scr.SetSaveOff();
	Scr.Restore();

	if ( flag == 1 ) SaveMenuFile();
	if ( flag == 0 ) NotSavedOnHard();

}

int ReallyEnd()
{
	char far *pMessage[] = {
							 " ¡A“A  e—i‹¡Ÿi ‹a e ",
							 " Ða¯¡‰V¯s“¡Œa?      ",
							 ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"  µ  ",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1,
							"¡A“A  e—i‹¡", pMessage, pItem, 0);
	Scr.SetSaveOff();
	if ( flag == 1 ) qSaveMenu();
	Scr.Restore();
	if ( flag != -1 ) return flag;

}
int ReallyDel()
{
	char far *pMessage[] = {
							 "                     ",
							 ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"  µ  ",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1,
							"¸÷ i »¡¶‰V¯s“¡Œa?", pMessage, pItem, 0);
	Scr.SetSaveOff();
	Scr.Restore();
	if ( flag != -1 ) return flag;

}


void ReadProtoFile()
{
	 int i;
	 FILE *fProto=fopen("PROTOCOL.DAT","rb");
	 if (fProto==NULL) return;
	 fseek(fProto,0L,SEEK_SET);
	 for (i=0; i<10; i++) fread(&Protocol[i],sizeof(Proto),1,fProto);
	 fclose( fProto );
}

void SaveProtoFile()
{
	 int i;
	 FILE *fProto=fopen("PROTOCOL.DAT","wb");
	 if (fProto==NULL) return;
	 fseek(fProto,0L,SEEK_SET);
	 for (i=0; i<10; i++) fwrite(&Protocol[i],sizeof(Proto),1,fProto);
	 fclose( fProto );
}

void SaveProto()
{
	char far *pMessage[] = {
							 "   »¡‹qŒa»¡ ¸b´óÐe   ",
							 "   Ïa¡É¡Å© ÑÁ·©·i   ",
							 "   ¸á¸wÐa‰V¯s“¡Œa?   ",
							 ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"  µ  ",
								""};

	Scr.SetSaveOn();
	int flag = spChoiceItemWin(390, 170,
							"¸á¸wÐa¯¡‰V¯s“¡Œa?", pMessage, pItem, 1);
	Scr.SetSaveOff();
	Scr.Restore();

	if ( flag == 1 ) SaveProtoFile();
	if ( flag == 0 ) NotSavedOnHard();

}
/*
bool IsSameRunNum()
{
	hgotoxy(10,25); hprintf("max num--> %d",MaxNo);
	spWait();
	if ( MaxNo <= 2 ) return false;
	int i,fr,to;
	i = no;
	while ( Menu[i--].X == Menu[no].X );  fr = i ;
	i = fr;
	while ( Menu[i++].X == Menu[no].X );  to = i ;
	hgotoxy(60,25); hprintf("from %d to %d",fr,to);
	spWait();
	for (i=fr; i<=to; i++)
		 if ( Menu[no].RunNo == Menu[i].RunNo)
			 if (no != i) return true;
	return false;
}

void SameRunNum()
{
	char *pWin[] = {
		" »¡‹q ·³bÐa¯¥ Ç¡“e ·¡£¡ ·³b ",
		" –E Ç¡ ·³“¡”a. ”aŸeÇ¡Ÿi ’‰œá  ",
		" º¯¡‹¡ ¤aœs“¡”a.             ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}
	*/
int	GetMenuRunNum()
{
	bool same=false;
	char RunNo[3];
	int x=220, y=215, ReadKey, ret=0;
	Scr.SetSaveOn();
	spBoxWin( x, y, x+244, y+50, "¡A“A¯©Ð—¤åÑ¡( 1 ~ 35 )" );
	Scr.SetSaveOff();
	if (Menu[no].RunNo == 0) strcpy(RunNo,"  ");
	else itoa(Menu[no].RunNo, RunNo, 10);
	while( !ret || ReadKey < 1 || ReadKey > 35 )
	{
	   ret = spGetMunja( x+108, y+29, RunNo, "99", "%-2s" );
		ReadKey = atoi(RunNo);
	}

	Scr.Restore();

	/*if ( same = IsSameRunNum() ) SameRunNum();*/
	return ReadKey;
}
void OutOfMenuMax()
{
	char *pWin[] = {
		" Ñe¸ ¡A“A®ˆa ¬a¶w ˆa“wÐe  ",
		" Ðe‰Ÿi ñ´á ¬ö¯s“¡”a.      ",
		" ”aŸe ¡A“AŸi ¬b¹AÐe Ò ¡A“A ",
		" Ÿi Âˆa Ða¯³¯¡µ¡.          ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();

}

void OutOfX()
{
	char *pWin[] = {
		" É³¡A“A Ða¶áµA ¹¥¸Ði ® ",
		" ·¶“e ¡A“A®· ¤ñ¶áŸi ¤õ ",
		" ´áv¯s“¡”a.             ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();

}

void CanNotDel1()
{
	char *pWin[] = {
		" Ñe¸ »¡¶a‰¡ Ða“e ¡A“A“e ",
		" ¬á§a¡A“A·¡£a¡ »¡¶‰ ® ´ô ",
		" ¯s“¡”a.  å¸á Ða¶á ¡A“AŸi  ",
		" »¡¶¯¡‹¡ ¤aœs“¡”a.        ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

void CanNotDel2()
{
	char *pWin[] = {
		" Ñe¸ »¡¶a‰¡ Ða“e ¡A“A“e  ",
		" É³¡A“A ·¡£a¡ »¡¶‰® ´ô¯s  ",
		" “¡”a.                      ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();

}


void GetMenuType(void)
{
	 char far *pMenu[12] = {
				 "  ¬á§a  ¡A“A  ",
				 "  ‰A  ¯¡  Ìe  ",
				 "  ¸a  ža  ¯©  ",
				 "  Íe»¡  ³a‹¡  ",
				 "  Íe»¡  ·ª‹¡  ",
				 "  ”  ÑÁ  ¯©  ",
				 "  ˆa·³  ¡A“A  ",
				 "  ÒA¶¥  ˆñ¬‚  ",
				 "  ¯¡ˆe  ·eÐ—  ",
				 "  •·Ñ¡ÒA‰ÅŸ¡  ",
				 "  ‰·»¡  ¬aÐw  ",
				 ""};


	Scr.SetSaveOn();
	int flag=spPopUpWin( 100, -1, 14, "¡A“A ¹·ŸA", pMenu, 0);
	Scr.SetSaveOff();
	Scr.Restore();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) )
		switch (flag) {
			 case 0 : CopyString(Menu[no].Type,"SUBMENU");
								Menu[no].Color = WYELLOW;   break;
			 case 1 : CopyString(Menu[no].Type,"BBSMENU");
								Menu[no].Color = WCYAN;     break;
			 case 2 : CopyString(Menu[no].Type,"PDSMENU");
								Menu[no].Color = WLIGHTBLUE;     break;
			 case 3 : CopyString(Menu[no].Type,"WMAIL");
								Menu[no].Color = WDARKGREEN;     break;
			 case 4 : CopyString(Menu[no].Type,"RMAIL");
								Menu[no].Color = WDARKGREEN;     break;
			 case 5 : CopyString(Menu[no].Type,"CHAT");
								Menu[no].Color = WMAGENTA;     break;
			 case 6 : CopyString(Menu[no].Type,"JOIN");
								Menu[no].Color = WLIGHTRED;     break;
			 case 7 : CopyString(Menu[no].Type,"USERSEE");
								Menu[no].Color = WBLACK;     break;
			 case 8 : CopyString(Menu[no].Type,"TIME");
								Menu[no].Color = WBLACK;     break;
			 case 9 : CopyString(Menu[no].Type,"GROUP");
								Menu[no].Color = WDARKBLUE;     break;
			 case 10 : CopyString(Menu[no].Type,"NOTICE");
								Menu[no].Color = WDARKRED;     break;

		}
}
void GetGoOrder()
{
	int x=263,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+114, y+50, "GO Ð—¬å»¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].Go, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}
void GetSysId()
{
	int x=200,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+140, y+50, "”q”w ´a·¡—¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].SysId, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}
int GetPass()
{
	int x=215,y=200,flag;

	Scr.SetSaveOn();
	flag = spBoxWin( x, y, x+122, y+50, "¬a¶w ´qÑ¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].Pass, "XXXXXXXX", "%-8s" );
	Scr.Restore();
	if (flag==0) return -1;
}

void GetAnsiFile()
{
	int x=239,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+162, y+50, "´e¯¡ ÑÁ·© ·¡Ÿq" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].AnsiFile, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}

void GetLevel()
{
	int x=225,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+190, y+50, "¬a¶w ˆa“wÐe A¥I" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].Level, "9999", "%-8s" );
	Scr.Restore();
}
void GetPoint()
{
	int x=230,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+180, y+50, "ÑÉ•·¯¡ ´è“e ¸ñ®" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].Point, "9999", "%-8s" );
	Scr.Restore();
}

void GetGrade()
{
	char far *pMessage[] = {
							 " ·¡ ¡A“AŸi ¬a¶w Ði ® ·¶“e ÒA¶¥· ",
							 " ¸a‰b·i ‰i¸÷Ðaµa º¯³¯¡µ¡.        ",
							 ""};
	char far *pItem[] = {
								"   ¬a¶wº—»¡ÒA¶¥   ",
								"     §¡ ÒA ¶¥     ",
								"     ÒA ¶¥  3     ",
								"     ÒA ¶¥  2     ",
								"     ÒA ¶¥  1     ",
								"     ¸÷ ÒA ¶¥     ",
								"    ¦  ¶…µw¸a    ",
								"     ¶… µw ¸a     ",
								""};

	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 8, "¬a¶w ˆa“w —w‹s", pItem, Menu[no].Grade);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) Menu[no].Grade=flag;
	Scr.Restore();
}

void GetClose()
{
	int mode =1;
	char far *pMessage[] = {
							 " ·¡ ¡A“AŸi ‰·ˆÐi ˆõ·¥»¡ ´a“¡¡e ",
							 " §¡‰·ˆ¡ ¶…µwÐi ˆõ·¥»¡  ‰i¸÷Ða ",
							 " µa º¯³¯¡µ¡.                   ",
							 ""};
	char far *pItem[] = {
								" ‰·ˆ ",
								"§¡‰·ˆ",
								""};

PrintGetClose :
	if ( mode == 1 ) Scr.SetSaveOn();
	int flag = spChoiceItemWin(-1, -1, "‰·ˆ / §¡‰·ˆ",
													pMessage, pItem, Menu[no].Close);
	if ( mode == 1 ) Scr.SetSaveOff();
	mode = 0;

	if ( flag != -1 ) Menu[no].Grade = flag;
	if ( flag == 1 )
		if ( GetPass() == -1 ) goto PrintGetClose;
		else
		{
			Scr.Restore();
			Menu[no].Close = flag;
			return;
		}
	Menu[no].Close = flag;
	Scr.Restore();
}
void PrintBar(int num, int c)
{

	 int tempbkcolor,tempcolor;
	 int Mx = SMX + (Menu[num].X - 1) * GABX;
	 int My = SMY + (num % MLINES);
		 if (num % MLINES == 0) My += MLINES;
	 tempbkcolor = hgetbkcolor();
	 tempcolor = hgetcolor();
	 hsetbkcolor(c);
	 hgotoxy (Mx,My);
	 hputs("                    ");
	 hgotoxy (Mx,My);
	 if (c==MBC) {
			 hsetcolor(WBLACK);
			 if (Menu[num].RunNo != 0)
					hprintf( "[%i]",Menu[num].RunNo );
	 }
	 else
	 {
			 if (Menu[num].RunNo != 0)
					{
						hsetcolor( WWHITE );  hputs("[");
						hsetcolor( WLIGHTBLUE ); hprintf( "%i",Menu[num].RunNo );
						hsetcolor( WWHITE );  hputs("]");
					}
			 hsetcolor(Menu[num].Color);
	 }
	 hputs(Menu[num].Title);
	 hsetbkcolor(MBKC);
	 hsetcolor(WLIGHTBLUE);
	 hgotoxy(65,6);
	 hputs("·¥•B¯a¤åÑ¡");
	 hgotoxy(69,7);
	 hputs(Menu[no].Index);
	 hsetcolor(WBLACK);
	 hsetbkcolor(MBC);

	 if (Menu[num].f2 )
			rectangle( (SMX+GABX) *8 -17 , (My-1)*16, (SMX+GABX) *8 -16 , My*16-1 );
	 if (Menu[num].f3 )
			rectangle( (SMX+2*GABX) *8 -17 , (My-1)*16, (SMX+2*GABX) *8 -16 , My*16-1 );
	 if (Menu[num].f4 )
			rectangle( (SMX+3*GABX) *8 -17 , (My-1)*16, (SMX+3*GABX) *8 -16 , My*16-1 );
	 if (Menu[num].f5 )
			rectangle( (SMX+4*GABX) *8 -17 , (My-1)*16, (SMX+4*GABX) *8 -16 , My*16-1 );
	 if (Menu[num].f6 )
			rectangle( (SMX+5*GABX) *8 -17 , (My-1)*16, (SMX+5*GABX) *8 -16 , My*16-1 );

	 switch (Menu[num].Head) {
		 case 0 : break;
		 case 1 : rectangle(Mx*8-17,(My-1)*16,Mx*8-16,My*16-1);
							line(Mx*8-16,My*16-8,Mx*8+7-16,My*16-8);
							break;

		 case 2 : rectangle(Mx*8-17,(My-1)*16,Mx*8-16,My*16-8);
							line(Mx*8-16,My*16-8,Mx*8+7-16,My*16-8);

							break;
	 }
	 hsetbkcolor(tempbkcolor);
	 hsetcolor(tempcolor);


}
void CanNotGetRunNo()
{
	char *pWin[] = {
		" É³¡A“A· ¡A“A¯©Ð—¤åÑ¡“e ",
		" ¤aŽ‰ ® ´ô¯s“¡”a",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "´ia —aŸ³“¡”a", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}
void GetRunNo()
{
	 int i;
	 if ( no==1 )
	 {
		  CanNotGetRunNo();
		  return;
	 }
	 Menu[no].RunNo = GetMenuRunNum();

	 if (no > 2)

	 for (i=2; i<  Menu[no].X ; i++)
	 {
		 for (int j=no-1; j>=2; j-- )
		 {
				if ( i == Menu[j].X )
					 if ( Menu[no].Index [i-2] == '0')
					 {
						  if (Menu[j].RunNo <= 9 )
							 Menu[no].Index[i-2] = Menu[j].RunNo + '0';
						  else  Menu[no].Index[i-2] = Menu[j].RunNo - 10 + 'A';
					 }
		 }
	 }

	 if (Menu[no].RunNo <= 9 )
		 Menu[no].Index[Menu[no].X -2] = Menu[no].RunNo + '0';
	 else  Menu[no].Index[Menu[no].X -2] = Menu[no].RunNo - 10 + 'A';
}
int GetTitle(int mode=0)
{
	int x=233,y=200,flag=0;
	char temp[21];

	hsetcolor(WBLACK);
	Scr.SetSaveOn();
	spBoxWin( x, y, x+182, y+50, "¡A“A· ¹A¡¢" );
	Scr.SetSaveOff();
	if (mode) {
		 CopyString(temp,Menu[no].Title);
		 for (int i=0; i<=20; i++) Menu[no].Title[i]=0;
	}
	flag = spGetMunja( x+10, y+29, Menu[no].Title,
													"XXXXXXXXXXXXXXXXXXXX", "%-20s" );
	if (mode && (flag==27)) CopyString(Menu[no].Title,temp);
	Scr.Restore();
	hsetcolor(WWHITE);
	return flag;
}

void PrintMenu( int start )
{

	 int end;
	 if (MaxNo == 0) return;
	 if (MaxNo - start < MLINES ) end = MaxNo;
	 else end = start + MLINES -1 ;

	 spFill( 10, 73, 620, 465 , WLIGHTGRAY);
	 for (int i = start; i <= end ;i++ ) PrintBar(i,MBKC);
}

void InsMenu()
{
	 char NewTitle[21],OriTitle[21];
	 if ( MaxNo >= MAXMENU ) { OutOfMenuMax(); return; }
	 if ( Menu[no].X == MAXX ) { OutOfX(); return; }
	 no++;
	 MaxNo++;

	 CopyString ( OriTitle, Menu[no].Title);
	 if (  GetTitle(1) == 27 ) {
			no--;
			MaxNo--;
			return;
	 }
	 else {
				 CopyString (NewTitle, Menu[no].Title);
				 CopyString (Menu[no].Title, OriTitle);
				}
	 for (int i = MaxNo-1 ; i >= no ; i--) Menu[i+1]=Menu[i];
	 InitMenu(no, no);
	 CopyString (Menu[no].Title,NewTitle);

	 Menu[no].X = Menu[no-1].X + 1;
	 if ( Menu[no].X == Menu[no+1].X ) Menu[no].Head = 1;
	 else Menu[no].Head = 2;

	 GetRunNo();

	 BitFieldInit_Ins();
	 PrintMenu( (no / MLINES) * MLINES + 1 );
	 PrintBar(no,MBC);
	 EditMenu();
}

void DelMenu()
{
	 if ( no < 1 ) return;
	 int temp,toModify;
	 int flag=0;
	 if (no == 1) {
			CanNotDel2();
			return;
	 }
	 if (no < MaxNo)
				if (Menu[no].X < Menu[no+1].X) {
				 CanNotDel1();
				 return;
			}

	 if (ReallyDel() != 1) return;

	 for (int i=no-1; i >= 1; i--) {
		 if (Menu[no].X == Menu[i].X) {
			 flag=1;
			 toModify=i;
			 break;
		 }
	 }
	 if (flag) for (i=toModify + 1; i < no; i++) if (Menu[i].X <Menu[no].X) flag=0;
	 if (flag)
	 {
		 flag=0;
		 for (i=no+1; i <= MaxNo; i++) {
			if (Menu[no].X == Menu[i].X) {
				flag=1;
				temp=i;
				break;
			}
		 }
		 if (flag) for (i=no + 1; i < temp; i++) if (Menu[i].X <Menu[no].X) flag=0;
		 if (flag) Menu[toModify].Head = 1;
		 else Menu[toModify].Head = 2;
	 }
	 for (i=no;i <= MaxNo; i++) Menu[i]=Menu[i+1];
	 InitMenu (MaxNo,MaxNo);
	 MaxNo--;
	 no--;

	 BitFieldInit_Del();
	 if (no % MLINES == 0)
			PrintMenu( ( no / MLINES - 1)* MLINES + 1);
	 else PrintMenu( (no / MLINES)* MLINES + 1);
	 PrintBar(no,MBC);
}

void EditMenu()
{
		class PopUp_  MenuMaking;
		int choonum,flag,mode=1;
		char far *pMenu[12] = {
					 "  ¡A“A ¯©Ð— ¤åÑ¡  ",
					 "  ¡A  “A  ·¡  Ÿq  ",
					 "  ¡A  “A  ¹·  ŸA  ",
					 "  Go Ð—¬å»¡ ”e´á  ",
					 "  ´e  ¯¡  ÑÁ  ·©  ",
					 "  ÑÉ •· ¯¡ ¸ñ ®  ",
					 "LINE",
					 "  ¬a¶w ˆa“w A¥I  ",
					 "  ¬a¶w ˆa“w —w‹s  ",
					 "  ”q ”w ´a ·¡ —¡  ",
					 "  ‰·  ˆ  µa  ¦  ",
					 ""};



	int PopMenuState[12] = { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 0 };


		if (mode ) Scr.SetSaveOn();
			 spWin( 305, 123, 495, 309, "");
		if (mode ) Scr.SetSaveOff();

PrintEditMenu :

	char Close[21];
	char    *Grade[] = {
								"¬a¶wº—»¡ÒA¶¥",
								"  §¡ ÒA ¶¥  ",
								"  ÒA ¶¥  3  ",
								"  ÒA ¶¥  2  ",
								"  ÒA ¶¥  1  ",
								"  ¸÷ ÒA ¶¥  ",
								" ¦  ¶…µw¸a ",
								"  ¶… µw ¸a  ",
								""};
		switch (Menu[no].Close) {
			case 0 : CopyString(Close,"‰·ˆ");  break;
			case 1 : CopyString(Close,"§¡‰·ˆ   / ");
							 CopyString(Close+11, Menu[no].Pass);
							 break;
			default : CopyString(Close+11, "   ");
		}
			 spBoxFill( 305, 123, 495, 309 , WLIGHTBLUE);
			 spBoxLine( 305, 123, 495, 231 , WWHITE,WDARKBLUE);
			 spBoxLine( 305, 232, 495, 309 , WWHITE,WDARKBLUE);

				 hsetbkcolor (WLIGHTBLUE);
				 hsetcolor (WWHITE);
						hgotoxy(40,9); hprintf("%2i",Menu[no].RunNo);
						hgotoxy(40,10); hputs(Menu[no].Title);
						hgotoxy(40,11); hputs(Menu[no].Type);
						hgotoxy(40,12); hputs(Menu[no].Go);
						hgotoxy(40,13); hputs(Menu[no].AnsiFile);
						hgotoxy(40,14); hputs(Menu[no].Point);
						hgotoxy(40,16); hputs(Menu[no].Level);
						hgotoxy(40,17); hputs(Grade[Menu[no].Grade]);
						hgotoxy(40,18); hputs(Menu[no].SysId);
						hgotoxy(40,19); hputs(Close);
				 hsetbkcolor (MBKC);
		if (mode) Scr.SetSaveOn();
			 MenuMaking.PopUp( 150, 123, WWHITE, WBLACK, pMenu, PopMenuState);
		if (mode) Scr.SetSaveOff();
		mode = 0;

		flag = MenuMaking.PopUpSelect();
		if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) choonum = flag;
		else  {
						Scr.Restore();
						Scr.Restore();
						PrintBar(no,MBC);
						return;
					}
		switch (choonum) {
			case 0 : GetRunNo();   break;
			case 1 : GetTitle() ;   break;
			case 2 : GetMenuType() ;   break;
			case 3 : GetGoOrder() ;  break;
			case 4 : GetAnsiFile() ;  break;
			case 5 : GetPoint() ;  break;
			case 7 : GetLevel() ;  break;
			case 8 : GetGrade() ;  break;
			case 9 : GetSysId() ;  break;
			case 10: GetClose();
		}
		goto PrintEditMenu;
}





void UpArr()
{
	if ( no <= 1 ) return;
	no--;

	if ( (( no % MLINES ) == 0 ) && ( no >= MLINES ) )  {
		 PrintMenu( no - MLINES + 1 );
		 PrintBar( no, MBC);
	}
	else {
				PrintBar(no+1,MBKC);
				PrintBar(no,MBC);
			 }
}
void DnArr()
{
	if ( no >= MaxNo )  return;
	no++;

	if ( ((no -1) % MLINES ) == 0 ) {
		 PrintMenu( no );
		 PrintBar( no, MBC);
	}
	else {
				PrintBar(no-1,MBKC);
				PrintBar(no,MBC);
			 }

}

int count=0;

void MenuMake()
{
	char ch;

	MenuScreenInit();
	setcolor(NCDLINECOLOR);
	if (count++==0) {
		InitMenu(0,MAXMENU);
		TopMenuInit();
		ReadMenuFile();
	}
	PrintMenu(1);
	PrintBar(no,MBC);
	int endroutine = 0;
	while ( endroutine == 0 )
		if ( bioskey(1) != 0 ) {
			ch=getch();
			switch(ch) {
				case 0 :
							ch = getch();
							switch(ch) {
								case 82 : InsMenu(); break;
								case 83 : DelMenu(); break;
								case 72 : UpArr();  break;
								case 80 : DnArr();
							}
							break;
				case 13 :  EditMenu();  break;
				case 27 :  if ( ReallyEnd() ) endroutine = 1;
			}
		}
	ScreenInit();
}
void ProtoMake()
{
	int mode = 1;
	char far *pMenu[11] = {
				 "   1 ¤å Ïa¡É¡Å©   ",
				 "   2 ¤å Ïa¡É¡Å©   ",
				 "   3 ¤å Ïa¡É¡Å©   ",
				 "   4 ¤å Ïa¡É¡Å©   ",
				 "   5 ¤å Ïa¡É¡Å©   ",
				 "   6 ¤å Ïa¡É¡Å©   ",
				 "   7 ¤å Ïa¡É¡Å©   ",
				 "   8 ¤å Ïa¡É¡Å©   ",
				 "   9 ¤å Ïa¡É¡Å©   ",
				 "   10¤å Ïa¡É¡Å©   ",
				 ""};

ProtoMenu :

	if ( mode == 1 ) Scr.SetSaveOn();
	int flag=spPopUpWin( 450, 80, 10, "    Ïa¡É¡Å© Íe»³‹¡    ", pMenu, 0);
	if ( mode == 1 ) Scr.SetSaveOff();

	mode = 0;

	if ( flag == -1 ) {
		 SaveProto();
		 Scr.Restore();
		 return;
	}
	else ProtoEditBox(flag);
	goto ProtoMenu;

}
void ProtoEditBox(int Index)
{
	char *Title;
	struct EditBox_ far *EBox;
	if( !(EBox = new EditBox_[4]) ) return;

	char far *FieldTitles[] =
	{
		"¯©Ð—ÑÁ·© ·¡Ÿq",
		"´ó ¡ —a µ³­e",
		"”a¶…¡—a µ³­e",
		"¹·ža",
		""
	};

	switch (Index) {
		case 0 : Title = "1 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 1 : Title = "2 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 2 : Title = "3 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 3 : Title = "4 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 4 : Title = "5 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 5 : Title = "6 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 6 : Title = "7 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 7 : Title = "8 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 8 : Title = "9 ¤å Ïa¡É¡Å© Íe»³"; break;
		case 9 : Title = "10¤å Ïa¡É¡Å© Íe»³";
	}
	EditProto( EBox, Index, 0, 0);

	Scr.SetSaveOn();
	spTitleEditBoxWin( 100, 170,
				 Title, FieldTitles, EBox);
	Scr.SetSaveOff();

	Scr.Restore();

	CopyString(Protocol[Index].Exec, EBox[0].munja);
	CopyString(Protocol[Index].Up, EBox[1].munja);
	CopyString(Protocol[Index].Dn, EBox[2].munja);

	delete[] EBox;

}
void LevelMake()
{
	struct EditBox_ far *EBox;

	if( !(EBox = new EditBox_[16]) ) return;

	EditLevel( EBox, 224, 114);

	Scr.SetSaveOn();
	spBoxWin(216, 85, 386, 396, "A¥I ¬é¸÷",
								 WIN_F_COLOR,WIN_B_COLOR,WLIGHTGRAY );
	Scr.SetSaveOff();

	hgotoxy(29,8);
	hsetbkcolor(WLIGHTGRAY);
	hsetcolor(WYELLOW);
	hputs("¸ñ®/A¥I/¯¡ˆe/”a¶…");
	hsetcolor(WWHITE);
	hsetbkcolor(WLIGHTGREEN);

	int flag = spEditBox( EBox, WLIGHTGRAY );

	Scr.Restore();
	if (flag != -1)
		 for (int i=0;i<=14;i++)
				CopyString (Level[i], EBox[i].munja);
	delete[] EBox;
}
void EditLevel( struct EditBox_ far *EBox, int ScrX, int ScrY)
{
	spEditBoxInit( ScrX, ScrY+=16, EBox[0], Level[0], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[1], Level[1], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[2], Level[2], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[3], Level[3], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[4], Level[4], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[5], Level[5], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[6], Level[6], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[7], Level[7], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[8], Level[8], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[9], Level[9], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[10], Level[10], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[11], Level[11], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[12], Level[12], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[13], Level[13], "9999/9999/9999/9999");
	spEditBoxInit( ScrX, ScrY+=16, EBox[14], Level[14], "9999/9999/9999/9999");
	spEditBoxInit( ScrX+70, ScrY+=20, EBox[15],"¹·ža", "");
}

void EditProto( struct EditBox_ far *EBox, int Index, int ScrX, int ScrY)
{
	spEditBoxInit( ScrX, ScrY, EBox[0], Protocol[Index].Exec,
										"EEEEEEEEEEEE");
	spEditBoxInit( ScrX, ScrY, EBox[1], Protocol[Index].Up,
										"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
	spEditBoxInit( ScrX, ScrY, EBox[2], Protocol[Index].Dn,
										"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
	spEditBoxInit( ScrX, ScrY, EBox[3], "¹·ža", "" );
}

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
					switch ( *(++String) ) {
						case '0' : col = WLIGHTGREEN; break;
						case '1' : col = WCYAN; break;
						case '2' : col = WLIGHTRED; break;
						case '3' : col = WMAGENTA; break;
						case '4' : col = WYELLOW; break;
						case '5' : col = WWHITE;
					}
					change = 1;
					String++;
			 }
			 else
			 if ( ( *String  >= '0') && ( *String <= '9') )
			 {
					switch ( *String++ ) {
						case '0' : col = WBLACK; break;
						case '1' : col = WDARKBLUE; break;
						case '2' : col = WDARKGREEN; break;
						case '3' : break;
						case '4' : col = WDARKRED; break;
						case '5' : break;
						case '6' : break;
						case '7' : col = WLIGHTGRAY; break;
						case '8' : col = WDARKGRAY; break;
						case '9' : col = WLIGHTBLUE;
					}
					change = 1;
			 }
			 if ( change == 1 ) {
				 if ( mode == 1 )  hsetcolor(col);
				 if ( mode == 0 ) hsetbkcolor(col);
				 change = 0;
			 }
		 }
		 else hputch(*String++);
	 }
	 hsetbkcolor(temp1);  hsetcolor(temp2);
}
