#define m_t_(a) { printf("<[%i]%ld>",a,farcoreleft()); getch(); }
#define  MAXSUBMENU  35  // a submenu can have 35 menus
#define  ForAppend    1
#define  ForReadWrite 2
#define  CBOXLINES  2
#define  NOTAPPLIED 1
#define  APPLIED  2
#define  ACCEPTED 3
#define  DENIED   4
#define  USER_OUT		-100
#define  HanjaCurColor    9
#define  HangulCurColor   10
#define  EnglishCurColor  14
#define  LogDataBufSize   20000
#define  MAXLEN 40
#define  BOX_CPL 10  /* Characters Per Line */
#define  onANSI   1
#define  onNORMAL 0
#define  MAX_MACRO_LEN   10
#define  SYSOP           7
#define  SUBSYSOP        6
#define  REALMEMBER      5
#define  MEMBER1         4
#define  MEMBER2         3
#define  MEMBER3         2
#define  NONEMEMBER      1
#define  DELETED         0
#define  UserLevel       1
#define  UserPoint       2
#define  UserLoginNo     3
#define  UserDnableSize  4
#define  UserPdsAct      5
#define  UserBbsAct      6
#define  NotRead -1   // in mail class, at first, written year is NotRead
#define  TXTtype 1
#define  BINtype 2
#define  MAX_MAIL_ID  50 //  maximum number of MAIL WRITING ID.
#define  max_line	  MAX_MAIL_ID*8+1
#define  TEMP_STR_LEN  320  // maximum number of strcat return character;
#define  MAX_FILE_STACK 20
#define  MAX_DN_NUM  15 // maximum number of down loading at a time.
#define  MAX_SEL_ITEM 15 // maximum number of items - dd, mv, tr... ans do on.
#define  TAB 9        // defines for fileselector
#define  FILES 15     // files printed on each
#define  RECOVER 1    // Drawing bar mode.
#define  DRAW    2    //     ""
#define  FILESELOK 50 // when file is selected, OnEnterKey returns this value.
#define  NOQUIT  40
#define  DSHELL -50
#define  QUIT   -40
#define  SS_ERR -30  //  Screen save error
#define  M_ERR  -20  //  not enough memory error
#define  FS 127     //  Ï©—a ¦…Ÿ¡
#define  sFS     "" //  Ï©—a ¦…Ÿ¡¸a (ÑÁ·©)  - string type
#define  pKEY     77   //  ´qÑ¡ÑÁ·©· XORµe¬e Ç¡
#define  scWTX    5
#define  scWTY    5
#define  sWTX    71
#define  sWTY	 5
#define  scWGX    (scWTX-1) * 8
#define  scWGY    (scWTY-1) * 16
#define  sWGX    sWTX * 8
#define  sWGY    sWTY * 16
#define  scSGX	(scWTX-1) * 8 + 8
#define  scSGY   (scWTY+ sWTY ) * 16 + 16*2
#define  bkW     1
#define  lW      15
#define  barW    4
#define  CURcolor 12
#define  maxGETLN 80    // Max get char number of CMD order
#define  nREGIST 1
#define  nGUEST  -1
#define  ELINES  1000   // Max line num - internal editor
#define  ECHARS  70     // Max char num of line  - internal editor
#define  M_SCHARS  35     // Max char num of subject -MAIL
#define  B_SCHARS  37     // Max char num of subject - BBS
#define  P_SCHARS  32     // Max char num of subject - PDS
#define  N_SCHARS  53     // Max char num of subject - NOTICE
#define  MAX_SCHARS 53
#define  L_SCR   16     // Lines of title of one screen.
#define  L_TEXT  15     // Lines of text viewing screen.
#define  MAX_TEMP  10   // the maimun number of object to be deleted
#define  mTITLE     1   // mode of TEXTMenu class
#define  mTEXT      2   // determines Title printing mode or Text printing mode.
#define  mUPLOAD    1   // mode of PdsMenu::ExecuteProtocol
#define  mDOWNLOAD  2   // determines DOWNLOAD mode or UPLOAD mode.
#define  SCRWIDTH 80
#define  SCRHEIGHT 29
#define  STATWIN   (&statwin)
#define  CHATWIN   (&chatwin)
#define  HANJABOX  (&hanjabox)
#define  HOST_STAT 1
#define  USER_STAT 2
#define  NEXT -1
#define  ASCEND 1
#define  edit_sx  9
#define  edit_sy  5
#define  edit_ex  79
#define  edit_ey  19
#define  UPARR_   72
#define  DNARR_   80
#define  RTARR_   77
#define  LTARR_   75
#define  C_PGUP_  132
#define  C_PGDN_  118
#define  HOME_    71
#define  END_     79
#define  CS   _CW->charspace
#define  LS   _CW->linespace
#define  mCHANGE  0        // mode of EditOrder()  used to print ReadDataFile(m1+mode)
#define  mINSERT  1        //         ""
#define  mDELETE  2        //         ""
#define  AfterEdit 1       // mode of TEXTMenu::SaveIdx()
#define  OnceRead  2       //         ""
#define  NewWrite  3       //         ""
#define  Normal    4       //         ""
#define  NotSaved  1       // return value of EditOrder.
#define  Saved     2       // determines whether Bbs Data is saved or not.
#define  CONTINUE  3
#define  ALIVE     10      // Menu index file is alive or
#define  DEAD      20      //                    dead
#define  maxPARAM  10      // maximum parameter numbers of MakeParam function
#define  lenPARAM  10      // maximum parameter length of MakeParam function
#define  ReadDataFile(n) DF->Read(n) // DF is instance of CDataFile class
#define  TOO_MANY_PARAM 10           // Error message of MakeParam function