#include "hanbgi.h"
#include "han240.h"
#include "danbi.h"
#include "version.h"
#include "filebox.h"
#include "auxil.h"
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
int  multi(int, int );
void kmPuts(int ,int ,char *);
void CutOffSpace(unsigned char *str);

char *MNAME[21] = {
							"[§¡ÑÂ¸÷]",
							"[¬á§a¡A“A]",
							"[‰A¯¡Ìe]",
							"[¸aža¯©]",
							"[‰·ˆÍe»¡]",
							"[Íe»¡·ª‹¡]",
							"[Íe»¡³a‹¡]",
							"[Íe»¡¥¡‰ÅÐq]",
							"[”ÑÁ¯©]",
							"[ˆa·³¡A“A]",
							"[ÒA¶¥ˆñ¬‚]",
							"[¸a‹¡¸÷¥¡‰ÅŸ¡]",
							"[¯¡ˆe·eÐ—] ",
							"[•·Ñ¡ÒA‰ÅŸ¡]",
							"[‰·»¡¬aÐw]",
							"[¯aÇaŸ³Ëa]",
							"[CD-ROM ¸aža¯©]",
							"[RDN ¸aža¯©]" ,
							"[”q”w¸a®¯¥Íe»¡]",
							"[¥¡…Íe»¡ÑÂ·¥]",
							""};

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
struct Proto {
		char Exec[13];
		char Up[31];
		char Dn[31];
		};


menu_t Menu[MAXMENU+1];
Proto Protocol[10];

char sName[11]="‹±ˆw¡¡",sId[9]="SYSOP",bName[11]="HAHA",
		 InstDir[41]="C:\\MIGHTY",
		 DownDir[41]="C:\\MIGHTY\\DOWN", AnsiDir[41]="C:\\MIGHTY\\ANSI",
		 ArcDir[41]="C:\\UTIL\\ARC", WaitInit[61]="ATZ", LocalInit[61]="ATZ",
		 LoginId[11]=" a·¡Ë¡",
		 VirOrder[41]="C:\\UTIL\\VACCINE\\TV.EXE",
		 HackWord[41]="hack Hack HACK troy Troy TROY",
		 SmPass[9]="puhaha", SonnimLev[5]="30  ", JoinLev[5]="50  ",
		 BbsPoint[4]="3  ", UpPoint[4]="5  ", UpSizeRate[2]="2",
		 UpTimeRate[2]="1", InputLimTime[2]="5",
		 OpStart[9]="23¯¡30¦…", OpEnd[9]="06¯¡00¦…",  // for converting previous version.
		 OpStartHour[3]="23", OpStartMin[3]="00",
		 OpEndHour[3]="06", OpEndMin[3]="00",
		 InitGab[2]="5";
int    Version=100,port=2, speed=6, parity=0, data=1, stop=0,
		 HanFontType=1, EngFontType=1, VirDetect=0,
		 HackDetect=0, OpMode=0, PeopleNum=0,
		 HanBoard=0,LevelNo,DoNullModem=0,Sound=1,SysopExist=1,
		 FirstGrade=0, GiveDnableSize=0, SuccDnLoad=1, Fifo=2, Flow=0;
char   MinBbsSize[5]="0   ", MinPdsSize[5]="0   ",
		 MinSpeed[6]="0    ";
int    UsePartTime=0;
int    bExitPro =0;
char   EmulPro[41]="c:\\i\\i.exe";
char   EditPro[41]="c:\\utlt\\u.exe";
// empty objects for CFileSelect
class  _SCR SCR;
class  _rCOLOR rCOLOR;
int    st=0; // state of menu option. if st==0 -> Limit menu state.
				 //                       if st==1 -> UnLimit menu state.
             // This is used in EditMenu() function.
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
void SaveDatum(void)
{
	int i;
	int version;
	if (access("MIGHTY.cfg",0)!=-1)
		if (remove("MIGHTY.cfg")==-1)
		{
			closehan();
			printf("ERROR : Can't over write to mighty.cfg");
			exit(0);
		}
	version=IVER;
	fstream OutFile("Mighty.cfg",ios::out);
	for (i=0; i<15; i++)
		if ( !strcmp( Level[LevelNo=i], "    /    /    /    ") ) break;
	if ( strcmp( Level[14], "    /    /    /    ") ) LevelNo=15;
	OutFile<< version<< char(FS)<< port<< char(FS)<< speed<< char(FS)<< parity<< char(FS);
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
	OutFile<< InputLimTime<< char(FS)<< OpStartHour << char(FS);
	OutFile<< OpStartMin<<char(FS)<<OpEndHour<< char(FS);
	OutFile<< OpEndMin<< char(FS)<< InitGab<<char(FS)<< DoNullModem << char(FS);
	OutFile<< Sound<< char(FS)<< SysopExist<< char(FS)<< FirstGrade<< char(FS);
	OutFile<< GiveDnableSize << char(FS)<< SuccDnLoad<< char(FS);
	OutFile<< Fifo<<char(FS)<< Flow<< char(FS);
	OutFile<< MinBbsSize<< char(FS)<< MinPdsSize<< char(FS);
	OutFile<< MinSpeed<< char(FS)<<UsePartTime<<char(FS);
	OutFile<< EmulPro<<char(FS)<< EditPro<<char(FS)<<'\n';

	for (i=0; i<15; i++)  OutFile<< Level[i] <<'\n';
	OutFile.close();
}

void Read10BDatum(void)
{
	 int j,count;
	 char ch, number[7];

	 fstream InFile("Mighty.cfg",ios::in);
	 if (!InFile) return;

	 count = -1; Version;
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
		 while (InFile.get(ch), ch != FS)
			  if (count < 2) BbsPoint[++count]=ch;
		 BbsPoint[3]=0;

		 count = -1;
		 while (InFile.get(ch), ch != FS)
			  if (count < 2) UpPoint[++count]=ch;
		 UpPoint[3]=0;

		 count = -1;
		 while (InFile.get(ch), ch != FS) UpSizeRate[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS)
			 if (count < 0) UpTimeRate[++count]=ch;
		 UpTimeRate[1]=0;

		 count = -1;
		 while (InFile.get(ch), ch != FS)
			 if (count < 0) InputLimTime[++count]=ch;
		 InputLimTime[1]=0;

		 count = -1;
		 while (InFile.get(ch), ch != FS) OpStart[++count]=ch;
		 OpStart[2]=OpStart[6]=0;
		 strcpy(OpStartHour,OpStart);
		 strcpy(OpStartMin, OpStart+4);

		 count = -1;
		 while (InFile.get(ch), ch != FS) OpEnd[++count]=ch;
		 OpEnd[2]=OpEnd[6]=0;
		 strcpy(OpEndHour,OpEnd);
		 strcpy(OpEndMin, OpEnd+4);

		 count = -1;
		 while (InFile.get(ch), ch != FS)
			  if (count<0) InitGab[++count]=ch;
		 InitGab[1] = 0;

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
		 while (InFile.get(ch), ch != FS)
			 if (count < 4) MinSpeed[++count]=ch;
		 MinSpeed[5]=0;

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
		 // Do other initialization of new data.
	 InFile.close();
}
void Convert10BCfg()
{
		  char *pWin[] = {
					 "  a·¡Ë¡ 1.0B¤á¹e· mighty.cfg ",
					 " ÑÁ·©·i ¯¥¤á¹e· mighty.cfg¡ ",
					 " ¥eÑÅÐs“¡”a.                  ",
					 "" };

	  Scr.SetSaveOn();
		  spMessageWin( -1, -1, "¬é¸÷ÑÁ·© ¥eÑÅº—", pWin, WWHITE, WLIGHTRED);
	  Scr.SetSaveOff();

		  Read10BDatum();
		  SaveDatum();

		  delay(4000);
	  Scr.Restore();
}

void ReadDatum(void)
{
	 int j,count;
	 char ch, number[7];
	 int version;

	 fstream InFile("Mighty.cfg",ios::in);
	 if (!InFile) return;

	 count = -1; version=0;
	 while (InFile.get(ch), ch != FS) number[++count] = ch;
	 for (j=0; j<=count; j++)
	 version += (number[j]-48)*multi(10, (count-j));
	 if (version==IVER)  // mighty 1.0 beta1.5 reading routine.
	 {
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
			  while (InFile.get(ch), ch != FS) OpStartHour[++count]=ch;

			  count = -1;
			  while (InFile.get(ch), ch != FS) OpStartMin[++count]=ch;

			  count = -1;
			  while (InFile.get(ch), ch != FS) OpEndHour[++count]=ch;

			  count = -1;
			  while (InFile.get(ch), ch != FS) OpEndMin[++count]=ch;

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
	 // insert any other version reading routine
	 else
	 {
			  InFile.close();
			  Convert10BCfg();
	 }
}

class PullDown_ far * PD;
//---------------------------------------------------------------------------


void PullDownRtn(void);
void userinithan(void);

void MightyIs()
{
	char *pWin[] = {
		" ¬¡¶… Ñ¡¯aËa  a·¡Ë¡“e ˆ‚ÁA»¡Ð· ",
		" ‹¡¤ó·i ¬a¶w, ¹A¸b –A´ö·a£a¡ Ð· ",
		" Ò ÑÉ¤iÐe ¤á¹e´ó·¡ ˆa“wÐs“¡”a.  ",
		"  a·¡Ë¡“e ‰·ˆ ­¡ÏaËa¶Á´á·¡¡a, ¬w",
		" ´ó¸â ¡¢¸â·a¡ ³a·© ® ´ô¯s“¡”a. ",
		"                                 ",
		"   Mighty Host   ver 1.0 beta1.5 ",
		"     (¸á) REFINED  SOFTWARE      ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, " a·¡Ë¡“e..", pWin, WWHITE, WLIGHTBLUE);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}
// Path Buffer is in FILEBOX module.
extern char PathBuffer[200];
void InitData()
{
	 CutOffSpace(AnsiDir);
	 sprintf( PathBuffer, "%s\\*.*",AnsiDir);
}
void main(int argc, char* argv[])
{
	 if (argc >= 2)
		 if (!stricmp(argv[1], "/a")) st =1;
	 if (spDanbiInit(0L) == -1) return;
	 userinithan();
	 meq_init (MOU_ARROW16);
	 meq_show();
	 ReadDatum();
	 ReadProtoFile();
	 InitData();
	 PullDownRtn();
	 mou_close();
}
void userinithan()
{
		 LINK_EGA_hputfont8x16();
		 LINK_EGA_hputfont16x16();
		 // debug - HANVGA --> HANDETECT
		 inithanlib( BGIMODE, HANVGA, HAN8GD1, ENGMD1);
		 SELECT_hputfont8x16(AUTOSELECT);
		 SELECT_hputfont16x16(AUTOSELECT);
		 hsetallcolormap();
		 hsetwindowspalette(0);
}
/*
void Mighty()
{
	int 	x = 315 - 151,
		y = 240 - 110,
		handle = Scr.GetImage( x, y, x+312, y+220 );

	if( handle > 0)
		spPcxView16( x, y, "danbi35.pcx" );
	if( handle > 0)
	{
		spWait();

		Scr.PutImage( handle, x, y );
		Scr.HanFree( handle );
	}
}*/

void PullDownRtn()
{
		 PD = new PullDown_(0, hgetmaxpx(), 0, WBLACK, WWHITE);
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
							 "¶…µw¯¡¸b¯¡ˆb",
							 "¶…µw¹·ža¯¡ˆb",
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
		 PD->TopMenu = PopTitle;
		 PD->TopX = PopX;
		 PD->TopState = PopState;

		 for ( int i=0; i < 7; i++) {
				PD->PopMenuSet( PopMenu[i], i);
				PD->PopStateSet( PopMenuState[i], i);
		 }
		 ScreenInit();
		 PD->TopMenuInit(0);
		 MightyIs();
		 int flag;
		 _cuttail=true;  // for cutting space. this is hanlapro global variable.
		 for (;;) {
							 flag=PD->TopMenuSelect();
							 pd_x = PD->X();
							 pd_y = PD->Y();
							 if ( flag != -1)
							 {
								 (*Embank[pd_x][pd_y])();
								 PD->TopMenuInit(PD->X());
								 if (bExitPro) break;
							 }
		 };
		 delete PD;
}

void spmyGetMunja(int x, int y, char* str, char* prt, char* pic, char* spec)
{
	hgotopxy(x+strlen(pic)*8,y);
	hputs(prt);
	spGetMunja(x, y, str, pic, spec);
}

void MailTo()
{
	char *pWin[] = {
		"                                    ",
		"    Mighty HOST  ver 1.0 beta1.5    ",
		"         e  —e  ·¡ : ‹±ˆw¡¡         ",
		"        Ða·¡ÉI  Id : Capcom         ",
		"        a¶Å±  Id : refined        ",
		"                                    ",
		"     ‰¡a”ÐbŠa ÄñÏAÈáÐb‰Á '95      ",
		"                                    ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "¹A ¸b ¸a", pWin, WWHITE, WLIGHTBLUE);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

void ScreenInit()
{
	spPcxView16(0, 0, "screen.pcx");
	spBar3d1(0,DNBARSTARTY,639,475);
	kmPuts(3,29,"#7@1 MIGHTY @10ver 1.0 beta1.5  [ Ð·Ò ¶å95¶w  éË¡¡ ¥eÑÅ µ¸÷ ]       @9(¸á) @4‹±ˆw¡¡");
}
void DosShell()
{
	mou_hide();
	hrestorecrtmode();
	textcolor( WLIGHTGREEN );
	cputs( "<<<<");
	textcolor( WWHITE );
	cputs( "  MIGHTY  Ver 1.0 beta1.5");
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
										bExitPro =1;
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


	spmyGetMunja( x+10, y+29, InitGab,"¦…", "9", "%-1s" );
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

	spmyGetMunja(x+10, y+29, BbsPoint, "¸ñ", "999", "%-3s");
	Scr.Restore();
}
void GetUpPoint()
{
	int x=280,y=166;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+186, y+50, "¸aža ´ó¡—a ¸ñ®" );
	Scr.SetSaveOff();

	spmyGetMunja( x+10, y+29, UpPoint,"¸ñ","999", "%-3s" );
	Scr.Restore();
}
void GetUpSizeRate()
{
	int x=280,y=182;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+210, y+50, "´ó¡—a ¶wœ· ¥¡¬w§¡" );
	Scr.SetSaveOff();
	hprintfpxy( x+10+8, y+29, "¤");
	spGetMunja( x+10, y+29, UpSizeRate,"9", "%-1s" );
	Scr.Restore();
}
void GetUpTimeRate()
{
	int x=280,y=198;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+210, y+50, "´ó¡—a ¯¡ˆe ¥¡¬w§¡" );
	Scr.SetSaveOff();

	spmyGetMunja( x+10, y+29, UpTimeRate,"¤", "9", "%-1s" );
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

	spmyGetMunja( x+10, y+29, InputLimTime,"¦…", "9", "%-1s" );
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

	char far *pMenu[3] = {
				 "        ¯¡ˆe        ",
				 "         ¦…         ",
				 ""};
	Scr.SetSaveOn();
	int flag=spPopUpWin( x-60, y-60, 2, "¶…µw¯¡¸b ¯¡ˆb", pMenu, 0);
	Scr.SetSaveOff();

	switch( flag )
	{
		case 0 :
				Scr.SetSaveOn();
				spBoxWin( x, y, x+100, y+50, "¯¡ˆe" );
				Scr.SetSaveOff();

				spmyGetMunja( x+20, y+29, OpStartHour, "¯¡", "99", "%-2s" );
				Scr.Restore();
				break;
		case 1 :
				Scr.SetSaveOn();
				spBoxWin( x, y, x+100, y+50, "¦…" );
				Scr.SetSaveOff();

				spmyGetMunja( x+20, y+29, OpStartMin, "¦…", "99", "%-2s" );
				Scr.Restore();
				break;
	}

	Scr.Restore();

}
void GetOpEnd()
{
	int x=460,y=130;

	char far *pMenu[3] = {
				 "        ¯¡ˆe        ",
				 "         ¦…         ",
				 ""};
	Scr.SetSaveOn();
		  int flag=spPopUpWin( x-60, y-60, 2, "¶…µw¹·ža ¯¡ˆb", pMenu, 0);
	Scr.SetSaveOff();

	switch( flag )
	{
		case 0 :
				Scr.SetSaveOn();
				spBoxWin( x, y, x+100, y+50, "¯¡ˆe" );
				Scr.SetSaveOff();

				spmyGetMunja( x+20, y+29, OpEndHour, "¯¡", "99", "%-2s" );
				Scr.Restore();
				break;
		case 1 :
				Scr.SetSaveOn();
				spBoxWin( x, y, x+100, y+50, "¦…" );
				Scr.SetSaveOff();

				spmyGetMunja( x+20, y+29, OpEndMin, "¦…", "99", "%-2s" );
				Scr.Restore();
				break;
	}

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
	spmyGetMunja( x+10, y+29, MinSpeed, "BPS", "99999", "%-5s" );
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

void CutOffSpace(unsigned char *str)
{
	 int index=0;
	 for (index=strlen(str)-1; index>=0; index--)
		if ( str[index] == ' ') str[index]=0;
		else break;
}
void CopyString( char *cp1, char *cp2)
{
	while (*cp1++ = *cp2++);
}
int multi(int x1,int x2)
{
	 int tx1=x1;
	 if (x2==0) return 1;
	 while (x2-- > 1) x1 *=tx1;
	 return x1;
}
void LoadMenuOf10B()
{
	 int i,j,count;
	 char ch,number[7], tmpstr[10];
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

		 count = -1; Menu[i].color =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].color += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].head =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].head += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].grade =0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].grade += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].close = 0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].close += (number[j]-48)*multi(10, (count-j));

		 count = -1; Menu[i].run = 0;
		 while (InFile.get(ch), ch != FS) number[++count] = ch;
		 for (j=0; j<=count; j++)
				Menu[i].run += (number[j]-48)*multi(10, (count-j));

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].index[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].title[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) tmpstr[++count]=ch;
		 tmpstr[++count] = 0;

		 Menu[i].type = 0;
		 if (!strcmp(tmpstr,"SUBMENU")) Menu[i].type = SUB;
		 if (!strcmp(tmpstr,"BBSMENU")) Menu[i].type = BBS;
		 if (!strcmp(tmpstr,"PDSMENU")) Menu[i].type = PDS;
		 if (!strcmp(tmpstr,"WMAIL")) Menu[i].type = WMAIL;
		 if (!strcmp(tmpstr,"RMAIL")) Menu[i].type = RMAIL;
		 if (!strcmp(tmpstr,"CHAT")) Menu[i].type = CHAT;
		 if (!strcmp(tmpstr,"JOIN")) Menu[i].type = JOIN;
		 if (!strcmp(tmpstr,"USERSEE")) Menu[i].type = VUSER;
		 if (!strcmp(tmpstr,"TIME")) Menu[i].type = TBANK;
		 if (!strcmp(tmpstr,"GROUP")) Menu[i].type = MSIG;
		 if (!strcmp(tmpstr,"NOTICE")) Menu[i].type = NOTICE;
		 if (!strcmp(tmpstr,"SCRIPT")) Menu[i].type = SCRIPT;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].go[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].ansifile[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].sysid[++count]=ch;

		 count = -1;
		 while (InFile.get(ch), ch != FS) tmpstr[++count]=ch;
		 tmpstr[++count] = 0;
		 Menu[i].level = atoi(tmpstr);

		 count = -1;
		 while (InFile.get(ch), ch != FS) tmpstr[++count]=ch;
		 tmpstr[++count] = 0;
		 Menu[i].point = atoi(tmpstr);

		 count = -1;
		 while (InFile.get(ch), ch != FS) Menu[i].pass[++count]=ch;

		 while (InFile.get(ch), ch != FS) Menu[i].f2= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f3= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f4= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != FS) Menu[i].f5= (ch=='1') ? 1 : 0;
		 while (InFile.get(ch), ch != '\n') Menu[i].f6= (ch=='1') ? 1 : 0;
		 Menu[i].readlevel = 0;
		 Menu[i].writelevel = 0;
		 Menu[i].lowbirth = 0;
		 Menu[i].highbirth = 0;
		 Menu[i].bSecret =0;
	 }
	 InFile.close();
}

void SaveMenuFile()
{
	 int version;
	 int MenuNo;
	 FILE* mfile;

	 for(MenuNo=1; MenuNo<=MaxNo; MenuNo++)
	 {
			CutOffSpace( Menu[MenuNo].index);
			CutOffSpace( Menu[MenuNo].title);
			CutOffSpace( Menu[MenuNo].go);
			CutOffSpace( Menu[MenuNo].ansifile);
			CutOffSpace( Menu[MenuNo].sysid);
			CutOffSpace( Menu[MenuNo].pass);
	 }

	 version = IVER;
	 mfile = fopen("MENUDATA.DAT", "wb");
	 fwrite(&version, sizeof(version), 1, mfile);
	 fwrite(&MaxNo, sizeof(int), 1, mfile);
	 fwrite(&Menu[1], sizeof(struct menu_t), MaxNo, mfile);
	 fclose(mfile);
	 delay(2000); // wait for disk cash delay
	 system("copy mighty.cfg c:\\ > null");
}
void Convert10BMenuFile()
{
		  char *pWin[] = {
					 "   a·¡Ë¡ 1.0B¤á¹e· ¡A“AÑÁ·©·i   ",
					 " ¯¥¤á¹e· ¡A“AÑÁ·©¡ ¥eÑÅÐs“¡”a. ",
					 "" };

	Scr.SetSaveOn();
		  spMessageWin( -1, -1, "¡A“AÑÁ·© ¥eÑÅº—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();

		  LoadMenuOf10B();
		  SaveMenuFile();

		  delay(4000);
	Scr.Restore();
}

void LoadMenuFile()
{
	 int version;
	 FILE* mfile = fopen("MENUDATA.DAT", "rb");
	 if (mfile)
	 {
		  fread(&version, sizeof(version), 1, mfile);
		  if (version==IVER)
		  {
				fread(&MaxNo, sizeof(int), 1, mfile);
				fread(&Menu[1], sizeof(struct menu_t), MaxNo, mfile);
				fclose(mfile);
		  }
		  // insert any other version reading routine
		  else
		  {
				fclose(mfile);
				Convert10BMenuFile();
		  }
	 }
}

void MenuScreenInit()
{
	spBar3d1(0,0,639,62);
	spBar3d1(0,63,639,475);
	kmPuts(4,2,"#7@15 a·¡Ë¡ Ñ¡¯aËa ver 1.0 beta1.5  @13¡A“A Íe»³‹¡        @15 (@14C@15)@1 REFINED SOFTWARE ");
	kmPuts(4,3,"#7@10INSERT@15 : @9¡A“AÂˆa   @11DEL @15:@9 ¡A“A¬b¹A   @12ENTER @15: @9¡A“AÍe»³  @14 ÑÁ¬iÎaÇ¡ @15: ·¡•· ");
}
void TopMenuInit()
{

			 Menu[1].X = 1;
			 Menu[1].color = WYELLOW ;
			 Menu[1].run = 0;
			 Menu[1].type = SUB;
			 Menu[1].level =0;
			 Menu[1].point =0;
			 Menu[1].readlevel=0;
			 Menu[1].writelevel=0;
			 Menu[1].lowbirth=0;
			 Menu[1].highbirth=0;
			 Menu[1].bSecret = 0;
			 CopyString( Menu[1].index ,"000000");
			 CopyString( Menu[1].title ,"É³ ¡A “A");
			 CopyString( Menu[1].go , "TOP");
			 Menu[1].grade = 0;
			 Menu[1].close = 0;
			 no++;
			 MaxNo++;

}

void InitMenu(int fr, int to)
{
		for (int i=fr; i <= to; i++) {
			 Menu[i].X = 0;
			 for (int j=0; j<6; j++) Menu[i].index[j] = '0';
			 Menu[i].index[6] = 0;
			 Menu[i].head = 0;
			 Menu[i].type = 0;
			 for (j=0; j< 21; j++) Menu[i].title[j] = 0;
			 for (j=0; j< 9; j++)
			 {
					 Menu[i].go[j] = 0;
					 Menu[i].ansifile[j] = 0;
					 Menu[i].sysid[j] = 0;
					 Menu[i].pass[j]=0;
			 }
			 Menu[i].level = 0;
			 Menu[i].point = 0;
			 Menu[i].readlevel=0;
			 Menu[i].writelevel=0;
			 Menu[i].lowbirth=0;
			 Menu[i].highbirth=0;
			 Menu[i].bSecret =0;
			 Menu[i].grade = 0;
			 Menu[i].close = 0;
			 Menu[i].color = 0;
			 Menu[i].run = 0;
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
	else return 0;
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
	 for (i=0; i<10; i++)
	 {
		  CutOffSpace(Protocol[i].Exec);
		  CutOffSpace(Protocol[i].Up);
		  CutOffSpace(Protocol[i].Dn);
		  fwrite(&Protocol[i],sizeof(Proto),1,fProto);
	 }
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
	getch();
	//spWait();
	if ( MaxNo <= 2 ) return false;
	int i,fr,to;
	i = no;
	while ( Menu[i--].X == Menu[no].X );  fr = i ;
	i = fr;
	while ( Menu[i++].X == Menu[no].X );  to = i ;
	hgotoxy(60,25); hprintf("from %d to %d",fr,to);
	getch();
	//spWait();
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
	getch();
	//spWait();
	Scr.Restore();
}
*/
int	GetMenuRunNum()
{
	char RunNo[3];
	int x=220, y=215, ReadKey, ret=0;
	Scr.SetSaveOn();
	spBoxWin( x, y, x+244, y+50, "¡A“A¯©Ð—¤åÑ¡( 1 ~ 35 )" );
	Scr.SetSaveOff();
	if (Menu[no].run == 0) strcpy(RunNo,"  ");
	else itoa(Menu[no].run, RunNo, 10);
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

void NotPrepared()
{
	char *pWin[] = {
                " ¬åÈ‚Ða¯¥ ¡A“A Ñw¯¢·e ´a»¢ ",
                " »¡¶¥Ða»¡ ´g“e ¡A“A·³“¡”a. ",
                " ”a·q ¤á¹e·¥ 1.0¸÷¯¢¤á¹e   ",
					 " µA¬á »¡¶¥Ðs“¡”a.          ",
		"" };

	Scr.SetSaveOn();
	spMessageWin( -1, -1, "ºA­·Ðs“¡”a", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

void GetMenuType(void)
{
		int Color[19] = { WYELLOW,    // SUB
								CYAN,       // BBS
								WLIGHTBLUE, // PDS
								WDARKGREEN, // OMAIL
								WDARKGREEN, // WMAIL
								WDARKGREEN, // RMAIL
								WDARKGREEN, // MBOX
								WMAGENTA  , // CHAT
								WLIGHTRED,  // JOIN
								WLIGHTRED,  // VUSER
								WLIGHTRED,  // EDITSELF
								3,          // TBANK
								WDARKBLUE,  // MSIG
								WDARKRED,   // NOTICE
								WLIGHTGREEN, // SCRIPT
								WLIGHTBLUE, // CDROMPDS
								WLIGHTBLUE, // RDNPDS
								WLIGHTBLUE, // PDSSEARCH
								WDARKGREEN // MSEE

								};

			char far *pMenu[20] = {
											"   ¬á§a  ¡A“A   ",
											"   ‰A  ¯¡  Ìe   ",
											"   ¸a  ža  ¯©   ",
											"   ‰·ˆ  Íe»¡   ",
											"   Íe»¡  ·ª‹¡   ",
											"   Íe»¡  ³a‹¡   ",
											"   Íe»¡¥¡‰ÅÐq   ",
											"   ”  ÑÁ  ¯©   ",
											"   ˆa·³  ¡A“A   ",
											"   ÒA¶¥  ˆñ¬‚   ",
											"  ¸a‹¡¸÷¥¡‰ÅŸ¡  ",
											"   ¯¡ˆe  ·eÐ—   ",
											"   •·Ñ¡ÒA‰ÅŸ¡   ",
											"   ‰·»¡  ¬aÐw   ",
											"   ¯aÇa  Ÿ³Ëa   ",
											"  CD-ROM¸aža¯©  ",
											"   RDN ¸aža¯©   ",
											" ”q”w¸a®¯¥Íe»¡ ",
											"  ¥¡…Íe»¡ÑÂ·¥  ",
											""};


	Scr.SetSaveOn();
	int flag=spPopUpWin( 100, -1, 19, "¡A“A ¹·ŸA", pMenu, 0);
	Scr.SetSaveOff();
	Scr.Restore();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) )
	{
		switch(flag+1)
		{
			case RDNPDS:
			case EDITSELF:
				  NotPrepared();
				  break;
			default:
				  Menu[no].type = flag+1; // definition starts from 1
				  Menu[no].color = Color[flag];
		}
	}
}
int isExistGoOrder()
{
	int bExist=0, MenuItem;
	for(MenuItem=1; MenuItem<=MaxNo; MenuItem++)
	{
		 if (MenuItem != no)
		 {
			  CutOffSpace(Menu[no].go);
			  CutOffSpace(Menu[MenuItem].go);
			  if ( !stricmp(Menu[no].go, Menu[MenuItem].go) )
			  {
				  bExist=1;
				  break;
			  }
		 }

	}
	return bExist;
}
void GoOrderExist()
{
	char *pWin[] = {
					 "  ·¡£¡ ”aŸe ¡A“AµA¬á ¬a¶wÐe  ",
					 "  GO Ð—¬å»¡·³“¡”a.  ”aŸe Ð—  ",
					 "  ¬å»¡Ÿi ·³bÐa­A¶a.         ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}
void GetGoOrder()
{
	int x=263,y=200;
	int bExistGo=0, flag;
	char PreviousGoOrder[9];
	bool temp = _hangulmode;
	_hangulmode = false;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+114, y+50, "GO Ð—¬å»¡" );
	Scr.SetSaveOff();

	strcpy(PreviousGoOrder, Menu[no].go);
	do
	{
		 flag=spGetMunja( x+10, y+29, Menu[no].go, "XXXXXXXX", "%-8s" );
		 if (flag==27)
		 {
			  strcpy(Menu[no].go, PreviousGoOrder);
			  break;
		 }
		 else if (bExistGo=isExistGoOrder()) GoOrderExist();
	} while(bExistGo);
	Scr.Restore();
	_hangulmode = temp;
}
void GetSysId()
{
	int x=200,y=200;

	Scr.SetSaveOn();
	spBoxWin( x, y, x+140, y+50, "”q”w ´a·¡—¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].sysid, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}

int GetPass()
{
	int x=215,y=200,flag;
	bool temp = _hangulmode;
	_hangulmode = false;

	Scr.SetSaveOn();
	flag = spBoxWin( x, y, x+122, y+50, "¬a¶w ´qÑ¡" );
	Scr.SetSaveOff();

	spGetMunja( x+10, y+29, Menu[no].pass, "XXXXXXXX", "%-8s" );
	Scr.Restore();
	_hangulmode = temp;
	if (flag==0) return -1;
}
void CopyFailed()
{
	char *pWin[] = {
													  "  ´e¯¡ÑÁ·©·i ¥¢¬aÐa“e•A  ",
                                         "  ¯©ÌÐaµv¯s“¡”a.  DOS   ",
													  "  µAœá ·³“¡”a.           ",
		"" };

	Scr.SetSaveOn();
		spMessageWin( -1, -1, "µAœá  ¤i¬—", pWin, WWHITE, WLIGHTRED);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}

void CopySuccess()
{
	char *pWin[] = {
							"  ´e¯¡ÑÁ·©·i ¥¢¬aÐa“e•A  ",
							"  ¬÷‰·Ðaµv¯s“¡”a.        ",
							"" };

	Scr.SetSaveOn();
					 spMessageWin( -1, -1, "¥¢¬a ¬÷‰·", pWin, WWHITE, WLIGHTBLUE);
	Scr.SetSaveOff();
	spWait();
	Scr.Restore();
}
int WantCopy()
{
	char far *pMessage[] = {
									  "   ¬åÈ‚Ðe ÑÁ·©·e ´e¯¡ —¡BÉ¡Ÿ¡µA   ",
									  "   ¹¥¸Ðaµa´¡ Ðs“¡”a. ´e¯¡ÑÁ·©·i   ",
									  "   ´e¯¡ —¡BÉ¡Ÿ¡¡  ¥¢¬aÐa¯¡‰V¯s   ",
									  "   “¡Œa? ˆ{·e ·¡Ÿq· ÑÁ·©·¡ ·¶·i   ",
									  "   ‰w¶ ¶¥œ ÑÁ·©µA ”ü´á³s“¡”a.    ",
									  ""};
	char far *pItem[] = {
								"´a“¡µ¡",
								"  µ  ",
								""};

	Scr.SetSaveOn();
		  int flag = spChoiceItemWin( -1, -1,"¥¢¬a Ða¯¡‰V¯s“¡Œa?", pMessage, pItem, 1);
	Scr.SetSaveOff();
	Scr.Restore();
	if (flag==-1) return 0;
	else return flag;
}
// cut the extension of file name.
void CutExtName(char* fname)
{
	  int i;
	  for (i=strlen(fname)-1; i>=0; i--)
			if (fname[i]=='.')
			{
				 fname[i]=NULL;
				 break;
			}
}
void GetAnsiFile()
{
	int x=120,y=80;
	char fname[13];
	char path[200];
	long fsize;
	CFileSelector* FBox=new CFileSelector(x, y, WLIGHTGRAY, WDARKBLUE, 5);

	Scr.SetSaveOn();
	spBoxWin( x-5, y-25, FBox->maxx()+5, FBox->maxy()+5, "´e¯¡/¯aÇaŸ³Ëa ÑÁ·© ·¡Ÿq" );
	Scr.SetSaveOff();

	int ret = FBox->SelectFile( path, fname, fsize);
	if (ret != CANCEL)
	{
		 if (AnsiDir[strlen(AnsiDir)-1]=='\\') AnsiDir[strlen(AnsiDir)-1]=NULL;
		 path[strlen(path)-1]=0;  // remove last char '\\'
		 if (!stricmp(AnsiDir, path)) // the file in AnsiDir ?
		 {
			  CutExtName(fname);
			  strcpy(Menu[no].ansifile, fname);
		 }
		 else
		 {
			  if (WantCopy()) // do you want to copy it?
			  {
					char doscmd[200];
					sprintf(doscmd, "copy /y %s\\%s %s\\%s >null",path, fname, AnsiDir, fname);
					if (system(doscmd)==0)  // success??
					{
						 CutExtName(fname);
						 strcpy(Menu[no].ansifile, fname);
						 CopySuccess();
					}
					else CopyFailed();
			  }
		 }
	}
	delete FBox;
	//spGetMunja( x+10, y+29, Menu[no].ansifile, "XXXXXXXX", "%-8s" );
	Scr.Restore();
}
void GetPoint()
{
	int x=230,y=200;
	char point[10];
	Scr.SetSaveOn();
	spBoxWin( x, y, x+180, y+50, "ÑÉ•·¯¡ ´è“e ¸ñ®" );
	Scr.SetSaveOff();

	itoa(Menu[no].point, point, 10);
		  spGetMunja( x+10, y+29, point, "9999", "%-4s" );
	Menu[no].point = atoi(point);

	Scr.Restore();
}

void GetLevel()
{
	int x=225,y=200;
	char level[10];
	Scr.SetSaveOn();
	spBoxWin( x, y, x+190, y+50, "¬a¶w ˆa“wÐe A¥I" );
	Scr.SetSaveOff();

	itoa(Menu[no].level, level, 10);
		  spGetMunja( x+10, y+29, level, "9999", "%-4s" );
	Menu[no].level = atoi(level);

	Scr.Restore();
}

void GetGrade()
{
	char far *pItem[] = {
																					 "   ¬a¶wº—»¡,­¥“±(•·Ñ¡ÒA) ",
																					 "         §¡ ÒA ¶¥        ",
																					 "         ÒA ¶¥  3        ",
																					 "         ÒA ¶¥  2        ",
																					 "         ÒA ¶¥  1        ",
																					 "         ¸÷ ÒA ¶¥        ",
																					 "         ¦¶…µw¸a        ",
																					 "         ¶… µw ¸a        ",
																					 ""};

	Scr.SetSaveOn();
	int flag=spPopUpWin( -1, -1, 8, "¬a¶w ˆa“w —w‹s", pItem, Menu[no].grade);
	Scr.SetSaveOff();

	if ( (flag != -1) && (flag != LEFTARROW) && (flag != RIGHTARROW) ) Menu[no].grade=flag;
	Scr.Restore();
}
void GetWriteLevel()
{
		  int x=100,y=200;
	char level[10];
	Scr.SetSaveOn();
		  spBoxWin( x, y, x+460, y+50, "‹i³a‹¡/´ó¡—a ˆa“wÐe A¥I (A¥I 0 : ’Ša ˆa“w)" );
	Scr.SetSaveOff();

		  itoa(Menu[no].writelevel, level, 10);
		  spGetMunja( x+200, y+29, level, "9999", "%-4s" );
		  Menu[no].writelevel = atoi(level);

	Scr.Restore();
}

void GetReadLevel()
{
		  int x=100,y=200;
	char level[10];
	Scr.SetSaveOn();
		  spBoxWin( x, y, x+460, y+50, "‹i·ª‹¡/”a¶…¡—a ˆa“wÐe A¥I (A¥I 0: ’Ša ˆa“w)" );
	Scr.SetSaveOff();

		  itoa(Menu[no].readlevel, level, 10);
		  spGetMunja( x+200, y+29, level, "9999", "%-4s" );
		  Menu[no].readlevel = atoi(level);

	Scr.Restore();
}
void GetLowBirth()
{
		  int x=120,y=200;
		  char birth[3];
	Scr.SetSaveOn();
		  spBoxWin( x, y, x+420, y+50, "??‘e ·¡Ò Â‰¬—¸a Â‰·³ˆa“w( 00‘e : ¹AÐe ´eÐq )" );
	Scr.SetSaveOff();

		  itoa(Menu[no].lowbirth, birth, 10);
		  spmyGetMunja( x+200, y+29, birth, "‘e", "99", "%-2s" );
		  Menu[no].lowbirth = atoi(birth);

	Scr.Restore();
}
void GetHighBirth()
{
		  int x=120,y=200;
		  char birth[3];
	Scr.SetSaveOn();
		 spBoxWin( x, y, x+420, y+50, "??‘e ·¡¸å Â‰¬—¸a Â‰·³ˆa“w( 00‘e : ¹AÐe ´eÐq )" );
	Scr.SetSaveOff();

		  itoa(Menu[no].highbirth, birth, 10);
		  spmyGetMunja( x+200, y+29, birth, "‘e","99", "%-2s" );
		  Menu[no].highbirth = atoi(birth);

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
        int flag = spChoiceItemWin(-1, -1, "‰·ˆ / §¡‰·ˆ", pMessage, pItem, Menu[no].close);
	if ( mode == 1 ) Scr.SetSaveOff();
	mode = 0;

	if ( flag != -1 ) Menu[no].grade = flag;
	if ( flag == 1 )
		if ( GetPass() == -1 ) goto PrintGetClose;
		else
		{
			Scr.Restore();
			Menu[no].close = flag;
			return;
		}
	Menu[no].close = flag;
	Scr.Restore();
}
void GetSecret()
{
	char far *pMessage[] = {
							 " ·¡ ¡A“AµA ¸ažaŸi ¹A‰·Ðe ¬aœq·  ",
							 " ´a·¡—¡Ÿi ‰·ˆÐi ˆõ·¥»¡ ‰·ˆÐa»¡ ",
							 " ´g·iˆõ·¥»¡ ‰i¸÷Ða¯³¯¡µ¡.        ",
							 ""};
	char far *pItem[] = {
								" ‰·ˆ ",
								"§¡‰·ˆ",
								""};

		  Scr.SetSaveOn();
		  int flag = spChoiceItemWin(-1, -1, "‰·ˆ / §¡‰·ˆ", pMessage, pItem, Menu[no].bSecret);
		  Scr.SetSaveOff();

		  if ( flag != -1 )
				if (flag) Menu[no].bSecret = 1;
				else Menu[no].bSecret = 0;
		  Scr.Restore();
}
void AutoWrite()
{
	int x=120,y=80, ret;
	char fname[13];
	char path[200];
	long fsize;
	CFileSelector* FBox=new CFileSelector(x, y, WLIGHTGRAY, WDARKBLUE, 5);

	Scr.SetSaveOn();
		  spBoxWin( x-5, y-25, FBox->maxx()+5, FBox->maxy()+5, "—w¢Ði ÑÁ·©·i ‰¡Ÿa­A¶a" );
	Scr.SetSaveOff();

	// end of path is '\\'
	ret = FBox->SelectFile( path, fname, fsize);
	delete FBox;
	CutOffSpace(InstDir);
	char doscmd[200];
	while(ret != CANCEL)
	{
		 switch( Menu[no].type )
		 {
			 case PDS:
			 case CDROMPDS:
				 sprintf(doscmd, "autoup %s%s %s\\%s > null",path, fname, InstDir, Menu[no].index);
				 break;
			 case OMAIL:
			 case NOTICE:
			 case BBS:
				 sprintf(doscmd, "autowrt %s%s %s\\%s > null",path, fname, InstDir, Menu[no].index);
				 break;
		 }
		 system(doscmd);

		 FBox=new CFileSelector(x, y, WLIGHTGRAY, WDARKBLUE, 5);
		 ret = FBox->SelectFile( path, fname, fsize);
		 delete FBox;
	}
	//spGetMunja( x+10, y+29, Menu[no].ansifile, "XXXXXXXX", "%-8s" );
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
			 if (Menu[num].run != 0)
					hprintf( "[%i]",Menu[num].run );
	 }
	 else
	 {
			 if (Menu[num].run != 0)
					{
						hsetcolor( WWHITE );  hputs("[");
						hsetcolor( WLIGHTBLUE ); hprintf( "%i",Menu[num].run );
						hsetcolor( WWHITE );  hputs("]");
					}
			 hsetcolor(Menu[num].color);
	 }
	 hputs(Menu[num].title);
	 hsetbkcolor(MBKC);
	 hsetcolor(WLIGHTBLUE);
	 hgotoxy(65,6);
	 hputs("·¥•B¯a¤åÑ¡");
	 hgotoxy(69,7);
	 hputs(Menu[no].index);
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

	 switch (Menu[num].head) {
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
void PrintMenu( int start )
{

	 int end;
	 if (MaxNo == 0) return;
	 if (MaxNo - start < MLINES ) end = MaxNo;
	 else end = start + MLINES -1 ;

	 spFill( 10, 73, 620, 465 , WLIGHTGRAY);
	 for (int i = start; i <= end ;i++ ) PrintBar(i,MBKC);
}

void GetRunNo()
{
	 int i;
	 if ( no==1 )
	 {
		  CanNotGetRunNo();
		  return;
	 }
	 Menu[no].run = GetMenuRunNum();

	 if (no > 2)

	 for (i=2; i<  Menu[no].X ; i++)
	 {
		 for (int j=no-1; j>=2; j-- )
		 {
				if ( i == Menu[j].X )
					 if ( Menu[no].index[i-2] == '0')
					 {
						  if (Menu[j].run <= 9 )
							 Menu[no].index[i-2] = Menu[j].run + '0';
						  else  Menu[no].index[i-2] = Menu[j].run - 10 + 'A';
					 }
		 }
	 }

	 if (Menu[no].run <= 9 )
		 Menu[no].index[Menu[no].X -2] = Menu[no].run + '0';
	 else  Menu[no].index[Menu[no].X -2] = Menu[no].run - 10 + 'A';

	 int diff;
	 if ( no%MLINES==0 ) diff = MLINES;
	 else diff = no%MLINES;

	 char doscmd[200];
	 CutOffSpace(InstDir);
	 sprintf(doscmd, "%s\\%s", InstDir, Menu[no].index);
	 mkdir(doscmd);

	 PrintMenu( no - diff + 1 );
	 PrintBar( no, MBC);
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
		 CopyString(temp,Menu[no].title);
		 for (int i=0; i<=20; i++) Menu[no].title[i]=0;
	}
	flag = spGetMunja( x+10, y+29, Menu[no].title,
													"XXXXXXXXXXXXXXXXXXXX", "%-20s" );
	if (mode && (flag==27)) CopyString(Menu[no].title,temp);
	Scr.Restore();
	hsetcolor(WWHITE);
	return flag;
}


void InsMenu()
{
	 char NewTitle[21],OriTitle[21];
	 if ( MaxNo >= MAXMENU ) { OutOfMenuMax(); return; }
	 if ( Menu[no].X == MAXX ) { OutOfX(); return; }
	 no++;
	 MaxNo++;

	 CopyString ( OriTitle, Menu[no].title);
	 if (  GetTitle(1) == 27 ) {
			no--;
			MaxNo--;
			return;
	 }
	 else {
				 CopyString (NewTitle, Menu[no].title);
				 CopyString (Menu[no].title, OriTitle);
				}
	 for (int i = MaxNo-1 ; i >= no ; i--) Menu[i+1]=Menu[i];
	 InitMenu(no, no);
	 CopyString (Menu[no].title,NewTitle);

	 Menu[no].X = Menu[no-1].X + 1;
	 if ( Menu[no].X == Menu[no+1].X ) Menu[no].head = 1;
	 else Menu[no].head = 2;

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
		 if (flag) Menu[toModify].head = 1;
		 else Menu[toModify].head = 2;
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
		char far *pMenu[20] = {
					 "  ¡A“A ¯©Ð— ¤åÑ¡  ",
					 "  ¡A  “A  ·¡  Ÿq  ",
					 "  ¡A  “A  ¹·  ŸA  ",
					 "  Go Ð—¬å»¡ ”e´á  ",
					 "  ´e  ¯¡  ÑÁ  ·©  ",
					 "  ÑÉ •· ¯¡ ¸ñ ®  ",
					 "LINE",
					 "  ¬a¶w ˆa“w A¥I  ",
					 "  ¬a¶w ˆa“w —w‹s  ",
					 "  ·ª‹¡ ˆa“w A¥I  ",
					 "  ³a‹¡ ˆa“w A¥I  ",
					 "  ??‘e ·¡Ò ˆa“w  ",
					 "  ??‘e ·¡¸å ˆa“w  ",
					 "LINE",
					 "  ”q ”w ´a ·¡ —¡  ",
					 "  ‰·  ˆ  µa  ¦  ",
					 "  ´a ·¡ —¡ ‰· ˆ  ",
					 "LINE",
					 "  ¸a  •·  —w  ¢  ",
					 ""};


						int PopMenuState[2][20][20] =
					{
						{
							{ 1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0 }, // UNDEFINED
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // SUBMENU
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1, 1, 0 }, // BBSMENU
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1, 1, 0 }, // PDSMENU
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1, 1, 0 }, // OPENMAIL
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // READMAIL
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // WRITEMAIL
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // MBOX
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // CHAT MENU
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // JOIN IN MENU
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // VIEW USER
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // SELF INFO
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // TIME BANK
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1, 1, 1,-1,-1,-1, 0 }, // MSIG
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1, 1, 0 }, // NOTICE
							{ 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // SCRIPT
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1,-1, 1, 0 }, // CD-ROM PDS
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1, 1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }, // RDN PDS
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1, 1, 1,-1, 1, 1,-1,-1,-1, 0 }, // SEND MAIL
							{ 1, 1, 1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 0 }  // MSEE
						},
						{
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // UNDEFINED
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // SUBMENU
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 0 }, // BBSMENU
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 0 }, // PDSMENU
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 0 }, // OPENMAIL
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // READMAIL
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // WRITEMAIL
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // MBOX
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // CHAT MENU
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // JOIN IN MENU
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // VIEW USER
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // SELF INFO
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // TIME BANK
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // MSIG
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 0 }, // NOTICE
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // SCRIPT
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 0 }, // CD-ROM PDS
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // RDN PDS
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }, // SEND MAIL
						  { 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1,-1, 0 }  // MSEE
						}
					};
		if (mode ) Scr.SetSaveOn();
			  spWin( 305, 123, 543, 405, "");
		if (mode ) Scr.SetSaveOff();

PrintEditMenu :

	char Close[21];
	char    *Grade[] = {
								"[¬a¶wº—»¡][­¥“±(•·Ñ¡ÒA)]",
								"[§¡ÒA¶¥]",
								"[ÒA¶¥3]",
								"[ÒA¶¥2]",
								"[ÒA¶¥1]",
								"[¸÷ÒA¶¥]",
								"[¦¶…µw¸a]",
								"[¶…µw¸a]",
								""};
		switch (Menu[no].close) {
			case 0 : CopyString(Close,"[‰·ˆ]");  break;
			case 1 : CopyString(Close,"[§¡‰·ˆ] / ");
						CopyString(Close+11, Menu[no].pass);
						break;
			default : CopyString(Close+11, "   ");
		}
						spBoxFill( 305, 123, 543, 405 , WLIGHTBLUE);
						spBoxLine( 305, 123, 543, 231 , WWHITE,WDARKBLUE);
						spBoxLine( 305, 232, 543, 343 , WWHITE,WDARKBLUE);
						spBoxLine( 305, 344, 543, 405 , WWHITE,WDARKBLUE);

				 hsetbkcolor (WLIGHTBLUE);
				 hsetcolor (WWHITE);

		int type = Menu[no].type;
		if (PopMenuState[st][type][0]>0) {hgotoxy(40,9); hprintf("%2i",Menu[no].run);}
		if (PopMenuState[st][type][1]>0) {hgotoxy(40,10); hputs(Menu[no].title); }
		if (PopMenuState[st][type][2]>0) {hgotoxy(40,11); hputs(MNAME[ Menu[no].type ]);}
		if (PopMenuState[st][type][3]>0) {hgotoxy(40,12); hputs(Menu[no].go); }
		if (PopMenuState[st][type][4]>0) {hgotoxy(40,13); hputs(Menu[no].ansifile); }
		if (PopMenuState[st][type][5]>0) {hgotoxy(40,14); hprintf("%i (¸ñ)", Menu[no].point); }
		if (PopMenuState[st][type][7]>0) {hgotoxy(40,16); hprintf("%i", Menu[no].level);}
		if (PopMenuState[st][type][8]>0) {hgotoxy(40,17); hputs(Grade[Menu[no].grade]);}
		if (PopMenuState[st][type][9]>0)
		{
			 hgotoxy(40,18);
			 if (Menu[no].readlevel) hprintf("A¥I %i·¡¬w ·ª‹¡/”a¶… ˆa“w",Menu[no].readlevel);
				 else hputs("´a¢a ˆa“w");
		}
		if (PopMenuState[st][type][10]>0)
		{
			 hgotoxy(40,19);
			 if (Menu[no].writelevel) hprintf("A¥I %i·¡¬w ³a‹¡/´ó ˆa“w",Menu[no].writelevel);
				  else hputs("´a¢a ˆa“w");
		}
		if (PopMenuState[st][type][11]>0)
		{
			 hgotoxy(40,20);
			 if (Menu[no].lowbirth) hprintf("%i‘e ·¡Ò Â‰¬—¸a e É·‰Á", Menu[no].lowbirth);
				  else hputs("¹AÐeÐa»¡ ´g·q");
		}
		if (PopMenuState[st][type][12]>0)
		{
			 hgotoxy(40,21);
			 if (Menu[no].highbirth) hprintf("%i‘e ·¡¸å Â‰¬—¸a e É·‰Á", Menu[no].highbirth);
				 else hputs("¹AÐeÐa»¡ ´g·q");
		}
		if (PopMenuState[st][type][14]>0)
		{
			 hgotoxy(40,23);
			 CutOffSpace(Menu[no].sysid);
			 if (Menu[no].sysid[0]!=0) hputs(Menu[no].sysid);
				 else hputs("[”q”w¸a ´ô·q]");
		}
		if (PopMenuState[st][type][15]>0) { hgotoxy(40,24); hputs(Close); }
					 if (PopMenuState[st][type][16]>0)
					 {
							  hgotoxy(40,25);
							  if (Menu[no].bSecret) hputs("[´a·¡—¡ §¡‰·ˆ]");
							  else hputs("[´a·¡—¡ ‰·ˆ]");
					 }
				 hsetbkcolor (MBKC);
		if (mode) Scr.SetSaveOn();
				 MenuMaking.PopUp( 150, 123, WWHITE, WBLACK, pMenu, PopMenuState[st][Menu[no].type]);
		if (mode) Scr.SetSaveOff();
		mode = 0;

		// Warning! Never change about MenuMaking instance.
		// I made a new function SetState.
		// MenuMaking.PopUp( 150, 123, WWHITE, WBLACK, pMenu, PopMenuState[st][Menu[no].type]);
		MenuMaking.SetState(PopMenuState[st][Menu[no].type]);
		MenuMaking.PopUp( 150, 123, WWHITE, WBLACK, pMenu, PopMenuState[st][Menu[no].type]);

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
			case 9 : GetReadLevel(); break;
			case 10: GetWriteLevel(); break;
			case 11: GetLowBirth(); break;
			case 12: GetHighBirth(); break;
			case 14: GetSysId();  break;
			case 15: GetClose();  break;
			case 16: GetSecret(); break;
			case 18: AutoWrite(); break;
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
		LoadMenuFile();
	}
	PrintMenu(1);
	no=1;
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
  
