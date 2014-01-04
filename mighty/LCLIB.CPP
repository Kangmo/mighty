/***** Internal Library Functions *****/

/* Add more of your own, here. */
#include "lc.h"
#include "debug.h"

#ifdef DEBUG
  #include <string.h>
  #include <conio.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <dos.h>
  #include <dir.h>
  #include "..\pcl\pcl4c.h"
#else
  #include "headers.h"
#endif

enum tok_types {DELIMITER, IDENTIFIER, NUMBER, COMMAND, TEMP,
		QUOTE, VARIABLE, BLOCK, FUNCTION};
enum tokens {ARG, CHAR, INT, STRING, File, IF, ELSE, FOR, DO, WHILE,
				 SWITCH, RETURN, EOL, FINISHED, BUFF, END};

extern char *prog;  /* points to current location in program */
extern char token[80];  /* holds string representation of token */
extern char token_type;  /* contains type of token */
extern char tok;  /* holds the internal representation of token */

int get_token(void);
void sntx_err(int error);
void eval_exp(CVar &var);
void putback(void);
CVar* find_var(char *name);


CVar* AddrOfVar()
{
	get_token();
	return find_var(token);
}

void TypeTest(CVar* Var, int type)
{
	if (Var->var_type != type) sntx_err(TYPE_MISMATCH);
}

/* A built-in console output function. */
int print(void)
{
	CVar* var;
	int i;

	OpenParen();
	do {
		 var = new CVar();
		 eval_exp(*var);
		 if (var->var_type == STRING)
		 {
				i=0;
				for (i=0; i<strlen(var->string); i++)
				{
					if (var->string[i]=='|')
					{
						 #ifdef DEBUG
							printf("\n");
						 #else
							c_hputs("\n\r");
						 #endif
					}
					else c_hputch(var->string[i]);
				}
		 }
		 else if (var->var_type == CHAR) c_hprintf("%c", var->value);
		 else c_hprintf("%d", var->value);
		 get_token();
		 delete var;
	} while (*token==',');

	if (*token != ')') sntx_err(PAREN_EXPECTED);


	return 0;
}
func_getln(void)
{
	CVar* pSrcBuf;
	CVar ExitStr;
	char* string;

	OpenParen();

	pSrcBuf = AddrOfVar();

	Comma();

	ExitStr.var_type = STRING;
	eval_exp(ExitStr);

	CloseParen();

	string = new char[MAXSTRLEN];
	#ifdef DEBUG
		gets(string);
		//printf("<%s>",ExitStr.string);
	#else
		c_hgetln(string, ExitStr.string, MAXSTRLEN-1);
	#endif
	TypeTest( pSrcBuf, STRING);
	pSrcBuf->SetString(string);
	delete string;
	return 0;
}
func_getline(void)
{
	CVar* pSrcBuf;
	CVar ExitStr,Max;
	char* string;

	OpenParen();

	pSrcBuf = AddrOfVar();

	Comma();

	ExitStr.var_type = STRING;
	eval_exp(ExitStr);

	Comma();

	Max.var_type = INT;
	eval_exp(Max);

	CloseParen();

	string = new char[Max.value+1];
	#ifdef DEBUG
		gets(string);
		//printf("<%s>",ExitStr.string);
	#else
		c_hgetln(string, ExitStr.string, Max.value);
	#endif
	TypeTest( pSrcBuf, STRING);
	pSrcBuf->SetString(string);
	delete string;
	return 0;
}

func_gettime(void)
{
	CVar* pHour;
	CVar* pMin;
	CVar* pSec;

	OpenParen();
	pHour = AddrOfVar();

	Comma();

	pMin = AddrOfVar();

	Comma();

	pSec = AddrOfVar();

	CloseParen();


	struct time t;
	gettime(&t);

	TypeTest(pHour, INT);
	TypeTest(pMin, INT);
	TypeTest(pSec, INT);

	pHour->SetValue(t.ti_hour);
	pMin->SetValue(t.ti_min);
	pSec->SetValue(t.ti_sec);
	return 0;
}

func_getdate(void)
{
	CVar* pYear;
	CVar* pMonth;
	CVar* pDay;

	OpenParen();

	pYear = AddrOfVar();

	Comma();

	pMonth = AddrOfVar();

	Comma();

	pDay = AddrOfVar();

	CloseParen();

	struct date d;
	getdate(&d);

	TypeTest(pYear, INT);
	TypeTest(pMonth, INT);
	TypeTest(pDay, INT);

	pYear->SetValue(d.da_year);
	pMonth->SetValue(d.da_mon);
	pDay->SetValue(d.da_day);
	return 0;
}

func_getlevel(void)
{
	OpenParen();
	CloseParen();

	return USER.stU.Level;
}

func_getpoint(void)
{
	OpenParen();
	CloseParen();

	return USER.stU.Point;
}

func_getlefttime(void)
{
	OpenParen();
	CloseParen();

	return USER.stU.LeftTime;
}


func_getdown(void)
{
	OpenParen();
	CloseParen();

	return USER.stU.DnableSize;
}

func_gettimebank(void)
{
	OpenParen();
	CloseParen();

	return USER.stU.TimeBank;
}
func_setinfo(void)
{
	CVar Point, Level, LeftTime, TimeBank, DnableSize;

	Point.var_type =
	Level.var_type =
	LeftTime.var_type =
	TimeBank.var_type =
	DnableSize.var_type = INT;

	OpenParen();

	eval_exp( Point );
	Comma();
	eval_exp( Level );
	Comma();
	eval_exp( LeftTime );
	Comma();
	eval_exp( TimeBank );
	Comma();
	eval_exp( DnableSize );

	CloseParen();

	USER.stU.Point += Point.value;
	USER.stU.Level += Level.value;
	USER.stU.LeftTime += LeftTime.value;
	USER.stU.TimeBank += TimeBank.value;
	USER.stU.DnableSize += DnableSize.value;

	return 0;
}

func_getid(void)
{
	CVar* pId;


	OpenParen();

	pId = AddrOfVar();

	CloseParen();

	TypeTest(pId, STRING);
	pId->SetString(USER.stU.ID);
	return 0;
}

func_getname(void)
{
	CVar* pName;


	OpenParen();

	pName = AddrOfVar();

	CloseParen();


	TypeTest(pName, STRING);
	pName->SetString(USER.stU.NAME);
	return 0;
}

func_atoi(void)
{
	CVar String;

	String.var_type = STRING;


	OpenParen();

	eval_exp(String);

	CloseParen();

	return atoi(String.string);
}
func_itoa(void)
{
	CVar Value, Radix;
	CVar* pString;

	Value.var_type = INT;
	Radix.var_type = INT;

	OpenParen();

	eval_exp( Value );

	Comma();

	pString = AddrOfVar();

	Comma();

	eval_exp( Radix );

	CloseParen();

	char tmp[MAXSTRLEN];
	itoa(Value.value, tmp, Radix.value);

	TypeTest(pString, STRING);
	pString->SetString(tmp);
	return 0;
}

func_delay(void)
{
	CVar Milliseconds;

	Milliseconds.var_type = INT;

	OpenParen();

	eval_exp( Milliseconds );

	CloseParen();

	delay(Milliseconds.value);
	return 0;
}
func_randomize()
{
	OpenParen();
	CloseParen();

	randomize();
	return 0;
}
func_random(void)
{
	CVar Num;

	Num.var_type = INT;

	OpenParen();

	eval_exp( Num );

	CloseParen();

	return random(Num.value);
}
func_execprotocol(void)
{
	CVar PNum, PMode;

	PNum.var_type = PMode.var_type = INT;

	OpenParen();

	eval_exp( PNum );

	Comma();

	eval_exp( PMode );

	CloseParen();

	int ret;
	#ifdef DEBUG;
	  printf("protocol number : %i, mode : %i\n", PNum.value, PMode.value);
	  ret=0;
	#else
	  ret=ExecuteProtocol(PNum.value, PMode.value);
	#endif
	return ret;
}
func_selectprotocol(void)
{
	CVar* pPNum;

	OpenParen();

	pPNum = AddrOfVar();

	CloseParen();

	int ret;
	#ifdef DEBUG
	  printf("selecting protocol number 1 as default\n");
	  TypeTest(pPNum, INT);
	  pPNum->SetValue( 1 );
	  ret = 0;
	#else
	  int ProtoNum;
	  ret=SelectProtocol( ProtoNum );
	  TypeTest(pPNum, INT);
	  pPNum->SetValue( ProtoNum );
	#endif

	return ret;
}
func_filepush(void)
{
	CVar File;

	File.var_type = STRING;

	OpenParen();

	eval_exp( File );

	CloseParen();

	#ifdef DEBUG
	  printf("pushing file name : %s\n", File.string);
	#else
	  sFILE.Push(File.string);
	#endif
	return 0;
}
func_clearstack()
{
	OpenParen();
	CloseParen();

	#ifdef DEBUG
		printf("clearing file stack\n");
	#else
		sFILE.clearstack();
	#endif
	return 0;
}

func_midstr(void)
{
	CVar  String;
	CVar  Index;

	String.var_type = STRING;
	Index.var_type = INT;


	OpenParen();

	eval_exp( String );

	Comma();

	eval_exp( Index );

	CloseParen();

	// script programer can access the last null character.
	if (Index.value > strlen(String.string) || Index.value < 0 )
		  sntx_err( OUT_OF_INDEX );
	return String.string[Index.value];  //Index.value is 0-based
}

func_setstr(void)
{
	CVar* pString;
	CVar  Index;
	CVar  Letter;

	Index.var_type = INT;
	Letter.var_type = CHAR;


	OpenParen();

	pString = AddrOfVar();

	Comma();

	eval_exp(Index);

	Comma();

	eval_exp(Letter);

	CloseParen();


	TypeTest(pString, STRING);


	if (Index.value < 0 ) sntx_err( OUT_OF_INDEX );
	else if (Index.value >= strlen(pString->string) || pString->string == NULL)
		  {
			  char* s = new char[Index.value+2];  //Index.value is 0-based

			  strcpy( s, pString->string);

			  if (Index.value>=1)
			  for(int i=strlen(pString->string); i<Index.value; i++) s[i]=' ';

			  s[Index.value] = Letter.value;
			  s[Index.value+1] = '\0';
			  pString->SetString( s );

			  delete s;
		  }
		  else pString->string[Index.value] = Letter.value;
	return 0;
}

func_strlen(void)
{
	CVar String;

	String.var_type = STRING;

	OpenParen();

	eval_exp( String );

	CloseParen();

	return strlen(String.string);
}

func_fopen(void)
{
	CVar *file;
	CVar Name, Mode;

	Name.var_type = Mode.var_type = STRING;

	OpenParen();

	file = AddrOfVar();

	Comma();

	eval_exp( Name );

	Comma();

	eval_exp( Mode );

	CloseParen();


	TypeTest(file, File); // CVar* Var, int type


	FILE* fp = fopen(Name.string, Mode.string);
	if (fp == NULL) return -1;

	file->SetFile(fp);
	return 0;
}

func_fclose(void)
{
	CVar* pfile;

	OpenParen();

	pfile = AddrOfVar();

	CloseParen();

	if (fclose( pfile->file )) sntx_err(FILE_CLOSE_ERROR);
	return 0;
}

func_fgets(void)
{
	CVar* pString;
	CVar* pfile;
	CVar  n;

	n.var_type = INT;

	OpenParen();

	pString = AddrOfVar();
	Comma();
	eval_exp(n);
	Comma();
	pfile = AddrOfVar();

	CloseParen();

	TypeTest(pString, STRING);
	TypeTest(pfile, File);

	char* s = new char[n.value+1];
	// fgets returns 0 when encountered eof.

	int ret;
	if ( fgets(s, n.value, pfile->file)<=0 ) ret = -1;
	else ret = strlen(s);
	pString->SetString( s );
	//printf("<fgets ret:%i>",ret);
	delete s;
	return ret;
}

func_fputs(void)
{
	CVar String;
	CVar* pfile;

	String.var_type = STRING;

	OpenParen();

	eval_exp(String);
	Comma();
	pfile = AddrOfVar();

	CloseParen();

	TypeTest(pfile, File);

	int ret = fputs( String.string, pfile->file );
	return ret;
}

// returns 0 on success.
func_system(void)
{
	CVar Command;
	Command.var_type = STRING;

	OpenParen();

	eval_exp( Command );

	CloseParen();

	return system(Command.string);
}

func_getdir(void)
{
	CVar* pInstDir;
	CVar* pDownDir;
	CVar* pAnsiDir;
	CVar* pArcDir;
	//extern char InstDir[51], DownDir[51], AnsiDir[51], ArcDir[51];

	OpenParen();

	pInstDir = AddrOfVar();
	Comma();
	pDownDir = AddrOfVar();
	Comma();
	pAnsiDir = AddrOfVar();
	Comma();
	pArcDir = AddrOfVar();

	CloseParen();

	TypeTest( pInstDir, STRING);
	TypeTest( pDownDir, STRING);
	TypeTest( pAnsiDir, STRING);
	TypeTest( pArcDir, STRING);

	pInstDir->SetString(InstDir);
	pDownDir->SetString(DownDir);
	pAnsiDir->SetString(AnsiDir);
	pArcDir->SetString(ArcDir);
	return 0;
}

func_getcwd(void)
{
	CVar* pCwd;

	OpenParen();
	pCwd = AddrOfVar();
	CloseParen();

	TypeTest(pCwd, STRING);

	char* cwd = getcwd(NULL,0);
	pCwd->SetString(cwd);
	free(cwd);
	return 0;
}

func_getch(void)
{
	OpenParen();
	CloseParen();

	#ifdef DEBUG
		return getch();
	#else
		return hgetxch();
	#endif
}
func_putch(void)
{
	CVar Char;
	Char.var_type = INT;
	OpenParen();

	eval_exp( Char );

	CloseParen();


	c_hprintf("%c", Char.value );

	return 0;
}
/*
  +------------+-------------------------------------------------------------+
  |   SioGetc  |  Reads the next character from the serial line.             |
  +------------+-------------------------------------------------------------+


	 Syntax    int SioGetc(int Port,int Tics)
					Port: Port selected (COM1 thru COM20)
					Tics: Timeout

	Remarks    The SioGetc function reads a byte from the selected serial port.
				  The  function  will  wait for the number of system tics given by
				  the 'Tics' argument before returning  'timed  out'.   There  are
				  18.2 tics to the second.

	Returns    -2 : Port not enabled. Call SioReset first.
				  -4 : No such port. Expect 0 to MaxPort.
				  -1 : If timed out.
				  >0 : Character read.

  See Also    SioUnGetc and SioPutc.
*/

// on error - returns -1, else read_character.
func_comgetch(void)
{
	OpenParen();
	CloseParen();

	#ifdef DEBUG
		printf("Getting a char \'A\' from comm port\n");
		return 'A';
	#else
		int ret = SioGetc(port, 6);
		if (ret<0) return -1;
		else return ret;
	#endif
}
/*

  +-------------+------------------------------------------------------------+
  |   SioPutc   |  Transmit a character over a serial line.                  |
  +-------------+------------------------------------------------------------+


	 Syntax    int SioPutc(int Port,char Ch)
					//Port: Port selected (COM1 thru COM20)
					//Ch:   Character to send

	Remarks    The SioPutc function transmits one character  over the  selected
				  serial line.

				  If  flow  control has been enabled, then SioPutc may return a -1
				  (time out) if the  number  of  tics  specified  in  the  SioFlow
				  function was exceeded waiting for the modem to raise CTS.

				  Refer to the User's Manual for a discussion of flow control.

				  If  transmitter  interrupts  are  enabled  (there  are  separate
				  versions of the library  for  transmitter  interrupts  enabled),
				  then  the  byte  is  placed  in  the  transmit  buffer, awaiting
				  transmission by the PCL4C interrupt service routine.

	Returns    -2 : Port not enabled. Call SioReset first.
				  -4 : No such port. Expect 0 to MaxPort.
				  -1 : Timed out waiting for CTS (flow control enabled)

  See Also    SioGetc and SioFlow.
*/

/* returns -1 on error, otherwise returns 0 */
func_computch(void)
{
	 CVar Char;

	 Char.var_type = INT;

	 OpenParen();

	 eval_exp( Char );

	 CloseParen();


	 #ifdef DEBUG
		  printf("putting a character \'%c\' onto com port\n", Char.value);
		  return 0;
	 #else
		  int ret = SioPutc(port, Char.value);
		  if (ret < 0) return -1;
		  else return 0;
	 #endif
}

// if hangup success, returns 1.
// otherwise, returns 0.
func_hangup(void)
{
	 OpenParen();
	 CloseParen();
	 #ifdef DEBUG
		 return 1;
	 #else
		 return SioHangUp(port);
	 #endif
}
// if not online, returns 0.
// otherwise returns any value except 0.
func_isonline(void)
{
	 OpenParen();
	 CloseParen();
	 #ifdef DEBUG
		 return 0;
	 #else
		 return SioDCD(port);
	 #endif
}

func_commsendready(void)
{
	 OpenParen();
	 CloseParen();
	 #ifdef DEBUG
		 return 0;
	 #else
		 return SioTxReady(port);
	 #endif
}
func_commrecvready(void)
{
	 OpenParen();
	 CloseParen();
	 #ifdef DEBUG
		 return 0;
	 #else
		 return SioRxQue(port);
	 #endif
}
func_siohayes(void)
{
	 CVar Command;
	 Command.var_type=STRING;
	 OpenParen();
	 eval_exp( Command );
	 CloseParen();

	 #ifndef DEBUG
	 SioHayes(port, Command.string);
	 #endif
}