struct  User_t{
		int OK;
		unsigned char ID[9],NAME[9],PASS[9],PEOPLENO[15],MAILNO[8];
		unsigned char ADDRESS[51],TELNO[15],BBNO[15],WORKPLACE[31];
		unsigned char MEMO[3][51];
		int BbsAct,PdsAct,UpDataSize,DnDataSize,LoginNo,Point,Level;
		int LeftTime,TimeBank,DnableSize,UsedTime;
		struct _AllTime JoinTime, LoginTime, LogoutTime;
};

class	SuperClass {
public:
		int ExitLoop;
		SuperClass();
		virtual ~SuperClass() {}
};
/*
class _TempQueue {
private :
	 SuperClass *tempObject[MAX_TEMP+1];
	 int rear,front;
public :
	 void store(SuperClass *object);
	 SuperClass *retrieve();
	 void Murder();
	 _TempQueue();
};*/
class CFileStack
{
  private :
	 int files;
	 char* FileName[MAX_FILE_STACK];
  public :
	 CFileStack();
	 ~CFileStack();
	 bool Push(char* newfile);
	 bool Pop(char* oldfile);
	 int TopSize() { return strlen(FileName[files-1]); }
	 bool Empty() { return (files<=0); }
	 void clearstack();
};

class UserClass {
public:
		int UserNo,RDNfiles,bRealUser;
		struct User_t stU;
		int SigGrade;
		int GetGrade();
		void AddPoint(int n);
		void SetLevel();
		void ViewPf();
		void GuestData();
		void ReadData();
		void SaveData();
		void ViewInfo();
		void ReadData(int UserNo_);
		void UserExit();
		UserClass();
		UserClass(int UserNo_);
};

class WaitConnect : public SuperClass {
private:
		struct time LastInit;
		void screenInit();
		void modemInit();
		void hostInit();
		int  SetModemSpeed(int& spd);
		void PrintValue(int px, int py, const char* title, unsigned long value);
		void PrintValue(int px, int py, const char* title, int value);
		void PrintValue(int px, int py, const char* title, char* value);
public:
		WaitConnect();
		~WaitConnect();
		void run();
};
class CutConnect : public SuperClass
{
public :
		void run();
};
class InputID : public SuperClass
{
		void GiveTimeAndDnableSize();
public:
		InputID();
		~InputID();
		void run();
};

class SMorder {
private :
	 char direc[100];
	 int bUpdated;
	 class UserClass *appU;
	 void PrintUserData();
	 void FindWithName();
	 void FindWithId();
	 void FindWithNumber();
	 void InputData(char* title, unsigned char* str, int len);
	 void InputData(char* title, int& var);
	 void InputOK();
	 void AppUserData(int num);
	 int RealAppUserData(int num); // used in AppUserData.
	 void ReindexMenuData(int type);

	 void AppUserData();       // used in run function.
	 void ReindexUserData();
	 void BackupUserData();
	 void RecoverUserData();
	 void MakeUserData2Txt();
	 void ReindexNowMenuData();
	 void ReindexAllMenuData();
	 void BackupMenuData();
	 void RecoverMenuData();
	 void RemoteDosShell();
public :
	 SMorder();
	 ~SMorder();
	 void run();
};

class RDS {
private :
	char OrderStr[257];
	int PossibleRun();
	void ScrFile2Comm();
	void PrintPrompt();
public :
	RDS();
	~RDS();
	void run();
};
class CWndFrame
{
  private :
	 int x1, y1, x2, y2, bkcol;
	 char* title;
	 window_t framewin;
  public :
	 CWndFrame(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep);
	 virtual void DoSpecial() {}
	 void Run();
};
class CSMWin : public CWndFrame
{
  public:
	 CSMWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep);
	 void DoSpecial();
};

class CLogoWin : public CWndFrame
{
  public:
	 CLogoWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep);
	 void DoSpecial();
};
/*
class CEmulWin : public CWndFrame
{
  public:
	 CEmulWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep);
	 void DoSpecial();
};*/

void appObject(int oID, char* index);
void runObject();

