#define   SVER "1.0 beta1.5"
#define   IVER  0x1B15
#define	 SUB       1  //  ��a  �A�A
#define	 BBS       2  //  �A  ��  �e
#define	 PDS       3  //  �a  �a  ��
#define	 OMAIL     4  //  ����  �e��
#define	 RMAIL	  5  //  �e��  �a��
#define	 WMAIL     6  //  �e��  ����
#define	 MBOX		  7  //  �e�������q
#define	 CHAT		  8  //  ��  ��  ��
#define	 JOIN		  9  //  �a��  �A�A
#define	 VUSER	  10 //  �A��  ��
#define   EDITSELF  11
#define	 TBANK	  12 //  ���e  �eЗ
#define	 MSIG		  13 //  ��ѡ�A�ş�
#define	 NOTICE	  14 //  ����  �a�w
#define   SCRIPT    15 //
#define   CDROMPDS  16
#define   RDNPDS    17
#define   SMAIL     18
#define   MSEE      19
#define   WAIT      101  //  �� ����
#define   INPUTID   102  //  �a���� ���b
#define   CUT       103
// constant definition.
// these constants are used both in setup and mighty.
#define   CANCEL    -1     // this is for CFileSelector object.
#define   NOERR      0
#define   ERR      -10  //  error
struct menu_t
{
	 int X;
	 int color;
	 int head;
	 int grade;
	 int close;
	 int type;
	 int level;
	 int point;
	 int run;
	 int readlevel;
	 int writelevel;
	 int lowbirth;
	 int highbirth;
	 char index[7];
	 char title[21];
	 char go[9];
	 char ansifile[9];
	 char sysid[9];
	 char pass[9];
	 char bSecret;
	 unsigned f2,f3,f4,f5,f6: 1;
};
