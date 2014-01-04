struct MailIndex_t
{
	  int MailNo;
	  unsigned bRead, bSaved:1;
	  struct _AllTime ReadTime;
};
struct MSeeIndex_t
{
	  char id[9];
	  char name[9];
	  unsigned bRead, bSaved:1;
	  struct _AllTime ReadTime;
};
struct MenuIndex_t
{
		int n, alive, look, down, page, year, month, day, hour, min;
		long size;
		unsigned char name[9],id[9],toid[9],subject[MAX_SCHARS+1];
		char FileName[13];
};

class BaseMenu : public SuperClass{
protected:
		char index[7];
		void H_(),T_(),BYE_(),NEW_(),TM_(),OP_();
		void HT_(),NCD_(),PF_(),V_(),X_();
		void SM_();
		void GO_(int n, char param[maxPARAM][lenPARAM]);
		void MEMO_(int n, char param[maxPARAM][lenPARAM]);
		void PF_(int n, char param[maxPARAM][lenPARAM]);
		virtual void Z_()=0,F_(),B_(),A_(),N_();

public:
		virtual void P_();
		void MEM_();
		void BaseProcess(char *str);
		BaseMenu();
		virtual ~BaseMenu() {}
};

class BaseExec : public SuperClass{
public:
		void P_();
		char index[7];
		BaseExec();
		virtual ~BaseExec() {}
		virtual void BYE_();
};
class Chat : public BaseExec {
private:
		unsigned char UserName[9],SysName[9];
		void CallSysop();
		void ScreenInit();
public:
		Chat(char *_index);
		~Chat();
		void run();
};

class SubMenu : public BaseMenu {
private:
		int nSUB[MAXSUBMENU+10],SubNo;
		void PrintCMD();
		void Z_();
		void NewProcess(char *str);
public:
		SubMenu(char *_index);
		void run();
};

class BbsData {
private:
		int iE,Tpage,y,PrintedLines,DataNum, ViewingLine;
		unsigned char *EDIT[ELINES];
		char index[7];
		GetLine(int mode);
		void Change(),Delete(),Insert();
		void View();
		void RealEdit();
		void PrintEDIT(int page);
		ReallyQuit();
		bool ProcessScanKey(char ch);
		ORDERprocess(char *ORDER);
public :
		void PR_();
		int GetDataNum() {return DataNum; }
		BbsData(int num);
		~BbsData();
		make();
		long getsize();
		void LoadData(),SaveData();
		EditOrder();
		void PrintText(int page);
};


class TEXTMenu : public BaseMenu {
protected:
		char path[9];
		int page, start,end;
		int title_start, title_page, text_page, mode, first, bbs_number;
		struct MenuIndex_t IDX;
		class BbsData *TEXT;
		virtual void P_(); // for deleting or saving of mail menu
		void S_();
		void Z_(),A_(),N_(),F_(),B_(),BYE_();
		void E_(int no, char param[maxPARAM][lenPARAM]);
		void DD_(int no, char param[maxPARAM][lenPARAM]);
		void PR_(int no, char param[maxPARAM][lenPARAM]);
		void PRprocess(int n);
		virtual void DDprocess(int n);  // for mail ddprocess
		void setend();
		void setstart();		// set start of title.
		int getmaxdatano();		// get start of title.
		int isBBSnum(char *CMD);
		void SaveIdx(struct MenuIndex_t& BI, int SaveMode);
		int LoadIdx(struct MenuIndex_t& BI, int num);
		virtual void PrintData(int num, int page);
		void PrintTitle(int page);
		void ConvertSize(float& filesize, char& postchar);
		int CalculateFileSize();
		void SetMode(int m);
		void TextProcess(char *CMD);
		virtual int EditAccess(int n);
		virtual int ReadAccess(int n);
		virtual int DelAccess(int n);
		virtual int WriteAccess();
		virtual void PrintNoData();
		virtual void PrintCMD() =0;
		virtual void NewProcess(char *CMD)=0;
		virtual void PrintFirstTitle()=0;
		void PrintLastTitle(int UP, int DOWN);
		virtual int OtherEditProcess()=0;
		virtual void PrintOneLine()=0;
		virtual void PrintIdx()=0;
		virtual void W_()=0;
public:
		TEXTMenu(char* _index, char* _path);
		virtual ~TEXTMenu();
		void run();
};

class BbsMenu : public TEXTMenu {
protected:
		void PrintOneLine();
		void PrintFirstTitle();
		void PrintCMD();
		int OtherEditProcess();
		void NewProcess(char *CMD);
		void PrintIdx();
		void W_();
public:
		BbsMenu(char *_index);
};

class NoticeMenu : public TEXTMenu {
private :
	 void PrintOneLine();
	 void PrintFirstTitle();
	 void PrintCMD();
	 void NewProcess(char *CMD);
	 void PrintIdx();
	 void W_();
	 void PrintNoData();
	 int OtherEditProcess();
	 int EditAccess(int n);
	 int DelAccess(int n);
	 int WriteAccess();
	 void R_();
public :
	 NoticeMenu(char* _index);
};

class CMail
{
  private:
	  int MaxItem;
	  FILE* fMIDX;
  public:
	  MailIndex_t MIDX;
	  int isUserMailNum(int n);
	  int FindItem(int n);
	  void WriteItem();
	  void SetRead(int n);
	  int SetSaved(int n, int bSaved);
	  int ValidItems();

	  CMail(unsigned char* ID, int mode);
	  ~CMail();
};

class CMailSee
{
  private:
	  FILE* fMIDX;
  public:
	  int MaxItem;
	  MSeeIndex_t MIDX;
	  void Open(int n, int mode);
	  int FindItem();
	  void FindItem(int DataNum);
	  void SetRead();
	  int SetSaved(int bSaved);
	  void WriteItem();
	  void ReadItem();
	  int ValidItems(); // returns number of mails read.
	  CMailSee();
	  ~CMailSee();
};

class MailMenu : public TEXTMenu{
protected:
		CMail*       Mail;
		CMailSee* MailSee;
		char MailSendID[9]; // for "S" or "RE" command.
		void SendMail(unsigned char *IDs, int BbsNo );
		int ConfirmID( unsigned char *IDs );
		void W_();
		virtual void DDprocess(int n);
		int OtherEditProcess();
public:
		MailMenu(char* _index);
		MailMenu(char*_index, unsigned char* ID);
		virtual ~MailMenu();
};
class CheckMail : public MailMenu {
private:
		void PrintCMD() {};
		void NewProcess(char *CMD) {};
		void PrintFirstTitle() {};
		void PrintOneLine() {};
		void PrintIdx() {};
public:
		void run();
		CheckMail();
};
class WMailMenu : public MailMenu {
private:
		void PrintCMD() {};
		void NewProcess(char *CMD) {};
		void PrintFirstTitle() {};
		void PrintOneLine() {};
		void PrintIdx() {};

public:
		void run();
		WMailMenu(char* _index);
		WMailMenu(char* _index, unsigned char* ID);
};

class RMailMenu : public MailMenu {
private:
		void PrintOneLine();
		void PrintFirstTitle();
		void PrintCMD();
		void NewProcess(char *CMD);
		void PrintIdx();
		void PrintNoData();
		int DelAccess(int n);
		int ReadAccess(int n);
		void MailSaveOrDelete();
		void P_();
public:
		RMailMenu(char *_index);
		~RMailMenu();
};

class MBox : public MailMenu {
private:
		void PrintOneLine();
		void PrintFirstTitle();
		void PrintCMD();
		void NewProcess(char *CMD);
		void PrintIdx();
		void PrintNoData();
		int DelAccess(int n);
		int ReadAccess(int n);
public:
		MBox(char *_index);
};

class MSee : public MailMenu {
private:
		int  allpage;
		void PrintOneLine();
		void PrintFirstTitle();
		void PrintCMD();
		void NewProcess(char *CMD);
		void PrintIdx();
		void PrintNoData();
		void PrintMailSee(int page);
		void PrintData(int num, int page);
		int DelAccess(int n);
		int ReadAccess(int n);
public:
		MSee(char *_index);
};
// this is CD-ROM PDS
class DnPdsMenu : public TEXTMenu {
protected:
		int nProto,index;
		void PrintOneLine();
		void PrintFirstTitle();
		void PrintCMD();
		void NewProcess(char *CMD);
		void PrintIdx();
		void PrintNoData();
		void W_() {}
		void DN_(int no, char param[maxPARAM][lenPARAM]);
		void RDN_(int no, char param[maxPARAM][lenPARAM]);
		void SaveRdn(struct MenuIndex_t& BI);
		void DNprocess(int n);
		void OnceDownLoaded(int n);
		void RDNprocess(int n);
		int OtherEditProcess();
public:
		DnPdsMenu(char *_index);
};

class PdsMenu : public DnPdsMenu {
private:
		void NewProcess(char *CMD);
		void W_(); // this is equal to up.
		int FileExist();
public:
		PdsMenu(char *_index);
};


class JoinIn : public BaseExec {
private:
		User_t joinU;
		InputField(unsigned char *title,unsigned char *str,int max, int min, int hanmode, int mode);
		int InputData();
		int ExistSpecialLetter(char* str);
		int UsingID();
		int UsingPeopleNo();

public:
		JoinIn(char *_index);
		void run();
};

class ViewUserMenu : public BaseExec {
private :
		void SortWithSomething(int toSort);
		void FindWithId();
		void FindWithName();
public :
		ViewUserMenu(char *_index);
		void run();
};
class TimeBankMenu : public BaseExec {
private :
		void DrawBackTime();
		void SaveTime();
		void SaveAllTime();
public :
		TimeBankMenu(char* _index);
		void run();
};
class CircleID
{
public :

	 struct circle_user_t
	 {
		 int grade;
		 int status;
		 unsigned char ID[9];
	 };

	 circle_user_t CID;
	 FILE * fMF;
	 int MaxItem;

	 CircleID(char* path);
	 ~CircleID();
	 bool isApplied()
	 {
		  if (CID.status==APPLIED) return true;
		  else return false;
	 }
	 bool isAccepted()
	 {
		  if (CID.status==ACCEPTED) return true;
		  else return false;
	 }
	 bool isNotApplied()
	 {
		  if (CID.status==NOTAPPLIED) return true;
		  else return false;
	 }
	 bool isDenied()
	 {
		  if (CID.status==DENIED) return true;
		  else return false;
	 }
	 int FindItem(char* ID);
	 void ReadItem();
	 void WriteItem();
	 void Seek(long offset, int whence);
	 void Apply(char* ID);
	 void Del();
	 void SetStatus(int st);
	 void SetGrade(int gr);
	 void Accept() { SetStatus(ACCEPTED); }
	 void Deny() { SetStatus(DENIED); }
};

class CircleMenu : public BaseMenu
{
private :
	 class CircleID* CID;
	 char path[7];
	 void PrintApplyId();
	 void PrintMemberId();
	 void MakeMember();
	 void DenyMember();
	 void DelMember();
	 void MakeMemberAll();
	 void SetMemberGrade();
	 void SetAllMemberGrade();
	 void ApplySelf();
	 void ConfirmJoin();
	 void DelSelf();
	 void PrintCMD();
	 void NewProcess(char *str);
	 void Z_();
public :
	 CircleMenu(char* _index);
	 ~CircleMenu();
	 void run();
};

class SendMail : public BaseExec {
public :
		SendMail(char* _index);
		void run();
};

class ScriptMenu : public BaseExec {
public :
		ScriptMenu(char* _index);
		void run();
};
