//#define DEBUG     // if DEBUG is define, this module can be run alone.

#ifdef DEBUG

  #define c_hputch      putch
  #define c_hputs       puts
  #define c_hprintf     printf
  #define ReadDataFile  DFmessage
  #define MEMTEST mem_left=farcoreleft();

  extern unsigned long mem_left;

  struct  UserClone_t{
		int OK;
		unsigned char ID[9],NAME[9],PASS[9],PEOPLENO[15],MAILNO[8];
		unsigned char ADDRESS[51],TELNO[15],BBNO[15],WORKPLACE[31];
		unsigned char MEMO[3][51];
		int BbsAct,PdsAct,UpDataSize,DnDataSize,LoginNo,Point,Level;
		int LeftTime,TimeBank,DnableSize,UsedTime;
  };
  typedef struct
  {
	  struct UserClone_t stU;
  }UserClass_t;

  extern UserClass_t USER;
  extern char* prog;
  extern char InstDir[51], DownDir[51], AnsiDir[51], ArcDir[51];
  void DFmessage(int msg);
#else
  #define MEMTEST
#endif

