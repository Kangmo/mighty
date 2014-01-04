// MIGHTY.H
struct _time
{
	 unsigned char hour;
	 unsigned char min;
};
struct _AllTime
{
	 int year;
	 char month, day;
	 unsigned char hour, min;
};
struct _level
{
	 int point;
	 int level;
	 int time;
	 int sizeDN;
};
struct _IdIndex {
	 int  OK;
	 char ID[9];
	 char PASS[9];
};
struct menudata_t {
	 int alldata;
	 int newdata;
	 char month;
	 char day;     // both signum and siginnum starts from index 0 ( have to use like this : MENU[MENU[nAcc].signum] )
	 char signum;  // index number of MSIG MENU. if this is 0, this is not SIG
	 char siginnum; // index number of Entrance of MSIG MENU.
};
struct _Proto {
	 char Exec[13];
	 char Up[31];
	 char Dn[31];
};

//----------------------------------------------------------------------------
extern char sName[11], sId[9], bName[11], InstDir[51], DownDir[51], AnsiDir[51],
		 ArcDir[51], WaitInit[61], LocalInit[41],
		 LoginId[11], VirOrder[41], HackWord[41], SmPass[9];
extern int  port, speed, parity, data, stop, HanFontType, EngFontType, VirDetect,
		 HackDetect, OpMode, PeopleNum, HanBoard, InitGab, SonnimLev,
		 JoinLev, BbsPoint, UpPoint, UpSizeRate, UpTimeRate, InputLimTime,
		 LevelNo, DoNullModem;


extern int nTodayLogin, nNewJoin, nSonnimLogin;
extern unsigned long nAllLogin;
extern char LastUserID[9];
extern char LastUserNAME[9];
extern char *Grade[];
extern char *SigGrade[];
extern long SPEED;

extern unsigned char UserStr[max_line];
extern unsigned char SysopStr[max_line];
extern int u_idx, s_idx;
extern int MaxGetln;
extern int ERROR_NO;
extern int escstep,ScrollTime;

extern char *temp_str, strPartTime[12];
extern char timestr[15],etimestr[6];
extern int  NowTop, All;
extern int  MenuNo,MaxUserNo,nAcc,RealGrade;
extern char  existSysop, bLocal,bUsePartT,bSound,
			 bAutoHan,bTBank,STAT,aliveUSER,bPDrun,bWaiting,
			 bDosScrSaved,bUserNotExist, bTempSysopOn,
			 bSysopHangUp,bPdRan, bChatMode, bInputId,
			 bUserTypeEnter, bPassInput, bChatting;
extern char bDontSendComm, bFrameExist,bUserStringActive;
extern int FirstGrade, GiveDnableSize, SuccDnLoad, Fifo, Flow;
extern int MinBbsSize, MinPdsSize;
extern unsigned MinSpeed;
extern char EmulPro[41];
extern char EditPro[41];
extern int bHanjaLoaded, bEgrLoaded, bKssLoaded, bHgrLoaded;

extern unsigned long first_core;
extern unsigned char LOGIN[11];
extern struct _time OpStart, OpEnd;
extern struct time NOW;
extern struct _AllTime tLogin;
extern struct date Today;
extern struct _level LEVEL[15];
extern struct _Proto PROTO[10];
extern struct _IdIndex far *IdIndex;
extern struct menu_t far *MENU;
extern struct menudata_t *MENUDATA;
extern window_t statwin, hanjabox, chatwin;

//extern unsigned char far *bufCUR;
//extern int  bxC,byC;
extern class _SCR SCR;
extern class _rCOLOR rCOLOR;
extern class UserClass USER;
extern class _PD *PD;
extern class SuperClass* runOBJ;
extern class CDataFile *DF;
extern class CFileStack sFILE;
//extern class _TempQueue *TRASH;
//---------------------------------------------------------------------------
extern bool isRealId(char* ID);
extern int AnswerIs(char ch, char OnUserOut, bool OnEnter);
extern void PrintLogo();
extern int ReadAnsiFile(char* t);
extern bool is_int(char *str);
extern ishangul1st_(unsigned char ch);
extern findStr(unsigned char *str);
extern void hookwaitkey(void);
extern void c_hgetln(unsigned char *str,unsigned char *OnUserOut, int no);
extern char *strcat2(char *des, const char *sor);
extern void halt(const char *error);
extern int IntNo(int dat);
extern int strnch(unsigned char *str, char ch);
extern int Le2I(int Lev);
extern Me2I(char *index);
extern Type2I(int type);
extern void makeIdIndex(void);
extern void readCfg(void);
extern void readMenuData(void);
extern void readProtocol();
extern void delVar();
extern int pow(int x1,int x2);
extern void GetAllTime(struct _AllTime *TM);
extern int ElapseTime(unsigned char hour1, unsigned char min1,
							 unsigned char hour2, unsigned char min2);
extern void getInteger(FILE *ifp, int *var, char ch1, char ch2, int mode );
// UI : unsigned integer
extern void getUI(FILE *ifp, unsigned *var, char ch1, char ch2, int mode );
// UC : unsigned char type 's integer.
extern void getUC(FILE *ifp, unsigned char *var, char ch1, char ch2, int mode );
extern void getString(FILE *ifp, char *str, char ch1);
extern void hanInit();
extern void hanDeinit();
extern void box3d2(int x1, int y1, int x2, int y2, int c1, int c2);
extern void box3d(int x1, int y1, int x2, int y2, int c, int ul, int dr);
extern void commInit();
extern void delComm();
extern void kmPuts(int x1,int y1,char *String);
extern void cursor_display();
extern void ErrMsg(char *title);
extern void varInit();
extern void ConfigInit();
extern int StdMsg(int x1, int y1, char *title[10]);
extern int BoxGetData(int x1, int y1, unsigned char *data, const char *picture);
extern int ButtonBox(int x1, int y1, char *title[10], char *button[4], char& ret);
extern int SelectBox(int x1, int y1, int bL, int bSL, int bBK, int bSBK, char *title[20], int *ret);
extern int PopupBox(int x1, int y1, int bL, int bSL, int bBK, int bSBK, char *title[20], void(*RunFunc[20])(void));

extern void halt();
extern void LocalConnect();
extern void DIRprocess();
extern void hookhangulmodetoggle(bool hangulmode);
extern void hookhanjamodetoggle(bool hanjamode);
extern void hookputch(window_t *win, byte c, int apx, int apy);
extern void hookscroll(wincoord_t *wc, window_t *win);
extern void execute_vt100(int cmd, int param1, int param2);
extern void process_vt100(int rc);
extern bool process_ctrlkey(int& ch);
extern void STAT_display();
extern void time_process();
extern int MakeParam(char* COMMAND, int& num, char param[maxPARAM][lenPARAM]);
extern void CutOffSpace(unsigned char *str);
extern void LoadDosScr();
extern void SaveDosScr();
extern bool GoOnWithSelectedNum(int no, char param[maxPARAM][lenPARAM], int Help, int Qst, int max_items);
extern int SelectProtocol(int& nProto);
extern int ExecuteProtocol(int nProto, int mode);
extern int appMenuObject(int n);
extern int isValidPeopleNo(char* PeopleNo);
extern void SetHanMode(bool mode);
extern void GetFileName(int num, char *FileName);
extern void MemoryManagerInit();
extern int ProcessMacro(const char* macro);
extern void readHostInfo();
extern void saveHostInfo();
extern void InitLogData();
int WriteLogData(const char *format, ...);
int WriteLogData_(const char *format, ...);
extern void SaveLogData();
extern void DeInitLogData();

//---------------------------------------------------------------------
//   Pull Down fuctions
extern void getWaitInit();
extern void getLocalInit();
extern void DoWaitInit();
extern void HangUp();
extern void LocalConnect();
extern void DoDosShell();
extern void InviteChat();
extern void TemporarySysop();
extern void UserSet();
extern void RunCommProg();
extern void RunEditProg();
extern void SendFile();
extern int SpawnProg(int mode, char* path, char* argv[], int GiveTimeRate);
extern void RunScript(char *fname);
extern int VG();
extern void ChatBox();
extern void SysopMenu();
extern void MightyIs();
extern void HostInitialize();
