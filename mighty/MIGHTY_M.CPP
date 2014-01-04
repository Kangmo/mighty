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
//   WILL BE PERISHED BY COPY RIGHT LAW.      1995.11.1 KIM KANGMO         //
//                                                                         //
//-------------------------------------------------------------------------//

/* Ansi Code ---> 	*/


//--------------------------------------------------------------------------
//                          MENU OBJECT MANAGER                           //
//--------------------------------------------------------------------------
appMenuObject(int n)
{
	 int pre, BirthYear;
	 char sBirthYear[3];
	 pre = nAcc;
	 if ( aliveUSER==0) halt("ERROR: happend processing user object-3");
	 if ( MENU[n].level > USER.stU.Level )        // ùA•I∑° êx¥a¨· ¥eñEîaìe êÅ∂w
	 {                                         // 21 : ≠•ì±∂w
			 //printf("%i > %i",MENU[n].level, USER->stU.Level);getch();
			 if ( USER.UserNo == nGUEST )         // 22 : àa∑≥∏a∂w
			 { nAcc = n; ReadDataFile(22); nAcc = pre; }
			 else ReadDataFile(21);
			 //WriteLogData("‘ˇ ùA•I∑° êx¥a¨· %s°AìA ª•∑≥ Ø©ÃÅ",MENU[n].title);
			 return ERR;
	 }
	 // lowbirth  - after ?? year
	 // highbirth - before ?? year
	 sBirthYear[0] = USER.stU.PEOPLENO[0];
	 sBirthYear[1] = USER.stU.PEOPLENO[1];
	 sBirthYear[2] = 0;
	 BirthYear = atoi(sBirthYear);
	 if (MENU[n].lowbirth)
		  if (MENU[n].lowbirth > BirthYear)
		  {
				 c_hprintf("%2i",MENU[n].lowbirth); ReadDataFile(310);
				 return ERR;
		  }
	 if (MENU[n].highbirth)
		  if (MENU[n].highbirth < BirthYear)
		  {
				 c_hprintf("%2i",MENU[n].highbirth); ReadDataFile(311);
				 return ERR;
		  }
	 //printf("<signum:%i, siginnum:%i>", MENUDATA[n].signum, MENUDATA[n].siginnum);  getch();
	 if ( MENUDATA[n].signum != 0 ) // when SIG MENU
	 {
			 if ( MENUDATA[n].signum != MENUDATA[pre].signum ) // is this first enter of SIG
			 {
				  CircleID CID(MENU[MENUDATA[n].signum].index);
				  if (CID.FindItem(USER.stU.ID) && CID.isAccepted()) // when current user is SIG member.
				  {
						 USER.SigGrade = CID.CID.grade;
				  }
				  else // see if this dong ho is close mode.
				  {
						 if ( MENU[MENUDATA[n].siginnum].close )
						 {
								ReadDataFile(306); // this SIG is currently close mode.
								return ERR;
						 }
						 USER.SigGrade = DELETED; // this is sonnim grade in SIG
				  }
			 }

			 if ( n==MENUDATA[n].siginnum )  // when SIG Entrance Menu
			 {
					if ( MENU[n].grade > USER.stU.OK )
					{
						 c_hprintf("∑° °AìAìe %sówãs∑°¨w∑Å “A∂•†e ¨a∂wàaìw–sì°îa.\n\r",
									  Grade[MENU[n].grade]);
						 return ERR;
					}
			 }
			 else
			 {
					if ( MENU[n].grade > USER.SigGrade)// when Not Sig Menu or Sig Entrance Menu
					{
						  c_hprintf("∑° °AìAìe ï∑—°“A ówãs %s∑°¨w∑Å “A∂•†e ¨a∂wàaìw–sì°îa.\n\r",
									  SigGrade[MENU[n].grade]);
						  return ERR;
					}
			 }

			 if ( MENUDATA[n].signum != MENUDATA[pre].signum ) // is this first enter of SIG
			 {
				  // print sig logo
				  ReadAnsiFile( strcat2(MENU[ MENUDATA[n].siginnum ].ansifile, ".LGO") );
				  nAcc = n;
				  ReadDataFile(305); // your grade is ...
			 }
			 if (MENU[n].type == SUB && n!=MENUDATA[n].siginnum)
					if (MENU[n].X > MENU[pre].X) ReadAnsiFile( strcat2( MENU[n].ansifile, ".LGO") );
			 else ReadAnsiFile( strcat2( MENU[n].ansifile, ".LGO") );

	 }
	 else
	 {
			 if ( MENU[n].grade > USER.stU.OK ) // when Not Sig Menu or Sig Entrance Menu
			 {
					 c_hprintf("∑° °AìAìe %sówãs∑°¨w∑Å “A∂•†e ¨a∂wàaìw–sì°îa.\n\r",
								  Grade[MENU[n].grade]);
					 return ERR;
			 }

			 if ( MENU[n].close )
			 {
					 char pass[9];
					 ReadDataFile(20); //ß°â∑àÅù° ∂Öµw–aì°åa ¥q—°üi ∑≥ùb–a≠A∂a
					 c_hputs("¥q  —° : ");

					 bPassInput=1;
					 c_hgetln(pass, "", 8);
					 bPassInput=0;
					 if (strcmp(pass,MENU[n].pass))
					 {
						  //WriteLogData("‘ˇ ¥q—°àa Àiùa¨· %s°AìA ª•∑≥ Ø©ÃÅ",MENU[n].title);
						  return ERR;
					 }
			 }
			 if (MENU[n].type == SUB)
				  if (MENU[n].X > MENU[pre].X) ReadAnsiFile( strcat2( MENU[n].ansifile, ".LGO") );
			 else ReadAnsiFile( strcat2( MENU[n].ansifile, ".LGO") );
	 }
	 //WriteLogData("‘ˇ %s°AìA ª•∑≥ ¨˜â∑",MENU[n].title);
	 switch(MENU[n].type)
	 {
			case TBANK  : if (USER.UserNo==nGUEST)
							  {
									 ReadDataFile(290); // guest can't use time bank menu
									 return ERR;
							  }
			case SMAIL  :
			case MBOX   :
			case MSEE   :
			case WMAIL  :
			case RMAIL  : if (USER.UserNo==nGUEST)
							  {
									 ReadDataFile(289); // guest can't use mail menu
									 return ERR;
							  }
			case SUB    :
			case BBS    :
			case OMAIL  :
			case PDS    :
			case CDROMPDS :
			case CHAT	:
			case JOIN	:
			case VUSER  :
			case MSIG   :
			case NOTICE :
			case SCRIPT : nAcc = n;
							  appObject( MENU[n].type, MENU[n].index );
							  return NOERR;
			default   	: WriteLogData("ERROR: invalid menu type : %i>",MENU[n].type);
							  printf("[%i]%s",MENU[n].run, MENU[n].title); getch();
							  ErrMsg("Not Prepared Menu");
							  return ERR;
	 }
}

//--------------------------------------------------------------------------
//      Setting changes after writting BbsData and PdsData and Notice     //
//--------------------------------------------------------------------------
SetChanges(menudata_t& MD)
{
	 _AllTime alltime;
	 MD.alldata++;
	 MD.newdata++;
	 GetAllTime(&alltime);
	 MD.day = alltime.day;
	 MD.month = alltime.month;
}
//--------------------------------------------------------------------------
//              Menu Base Class Member functions declalaion.              //
//--------------------------------------------------------------------------

BaseMenu::BaseMenu() : SuperClass()
{}
void BaseMenu::BaseProcess(char *str)
{
	 int no;
	 char	 param[maxPARAM][lenPARAM];
	 MakeParam( str, no, param );

	 if (!stricmp(str,"H"))     { H_(); return; }
	 if (!stricmp(str,"T"))     { T_(); return; }
	 if (!stricmp(str,"P"))     { P_(); return; }
	 if (!stricmp(str,"A"))     { A_(); return; }
	 if (!stricmp(str,"N"))     { N_(); return; }
	 if (!stricmp(str,"B"))     { B_(); return; }
	 if (!stricmp(str,"F") || !strcmp(str,"") )     { F_(); return; }
	 if (!stricmp(str,"Z"))     { Z_(); return; }
	 if (!stricmp(str,"NEW")) { NEW_(); return; }
	 if (!stricmp(str,"MEM")) { MEM_(); return; }
	 if (!stricmp(str,"SM"))   { SM_(); return; }
	 if (!stricmp(str,"TM"))   { TM_(); return; }
	 if (!stricmp(str,"OP"))   { OP_(); return; }
	 if (!stricmp(str,"HT"))   { HT_(); return; }
	 if (!stricmp(str,"NCD") )   { NCD_(); return; }
	 if (!stricmp(str,"V") )     { V_(); return; }
	 if (!stricmp(str,"X"))     { X_(); return; }
	 if (!stricmp(str,"BYE"))
	 {
			WriteLogData("‘ê ∏˜¨w∏‚∑aù° ∏Û≠¢π∑ûa ‘ë");
			BYE_();
			return;
	 }

	 if (!stricmp(param[0],"GO"))	{ GO_(no,param); return; }
	 if (!stricmp(param[0],"MEMO")) { MEMO_(no,param); return; }
	 if (!stricmp(param[0],"PF")) { PF_(no,param); return; }
}
void BaseMenu::V_()
{
	 ReadDataFile(19);
}
void BaseMenu::H_()
{
	 char t[3];
	 SetHanMode(false);
	 switch( MENU[nAcc].type )
	 {
		  case SUB   : if (!ReadAnsiFile("BASIC.HLP")) ReadDataFile(4);
							break;
		  case PDS   : if (!ReadAnsiFile("PDS.HLP")) ReadDataFile(5);
							break;
		  case BBS   : if (!ReadAnsiFile("BBS.HLP")) ReadDataFile(6);
							break;
		  case RMAIL :	if (!ReadAnsiFile("MAIL.HLP")) ReadDataFile(7);
							break;
		  default :
		  while( 1 )
		  {
				 if (!ReadAnsiFile("HELP.MNU")) ReadDataFile(3);
				 c_hgetln(t,"Q",2);
				 if ( !strcmp(t,"1") )
						if (!ReadAnsiFile("BASIC.HLP")) ReadDataFile(4);
				 if ( !strcmp(t,"2") )
						if (!ReadAnsiFile("PDS.HLP")) ReadDataFile(5);
				 if ( !strcmp(t,"3") )
						if (!ReadAnsiFile("BBS.HLP")) ReadDataFile(6);
				 if ( !strcmp(t,"4") )
						if (!ReadAnsiFile("MAIL.HLP")) ReadDataFile(7);
				 if ( !strcmp(t,"q") || !strcmp(t,"Q") )
				 {
						  Z_();
						  return;
				 }
		  }
	 }

}
void BaseMenu::T_()
{
		if (strnch(index,'0') ==6) return;
		if (appMenuObject(Me2I("000000"))== ERR) return;
		ExitLoop=1;
}
void BaseMenu::P_()
{
		int nz; char NewIndex[7];
		if (aliveUSER)
		{
			nz = strnch(index,'0');
			if ( nz == 6) return;
			strcpy (NewIndex, index);
			NewIndex[5-nz] = '0';
			if ( Me2I(NewIndex) == ERR ) return;
			if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
			ExitLoop=1;
		} else ErrMsg("User got out.");
}
void BaseMenu::F_() {}
void BaseMenu::B_() {}

void BaseMenu::A_()
{
		int nz; char NewIndex[7];
		nz = strnch(index,'0');
		if ( nz == 6) return;
		strcpy (NewIndex, index);
		NewIndex[5-nz] = NewIndex[5-nz]-1;
		if ( NewIndex[5-nz] == '0') return;
		if ( Me2I(NewIndex) == ERR ) return;
		if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
		ExitLoop = 1;
}
void BaseMenu::N_()
{
		if (strnch(index,'0') == 6) return;
		int nz;
		char NewIndex[7];
		nz=strnch(index,'0');
		if ( nz == 6) return;
		strcpy (NewIndex, index);
		NewIndex[5-nz] = NewIndex[5-nz]+1;
		if ( Me2I(NewIndex) == ERR ) return;
		if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
		ExitLoop = 1;
}
void BaseMenu::SM_()
{
		// if You use GetGrade(), Sig sysop can access Sm order.
		if (USER.stU.OK != SYSOP) ReadDataFile(192);
		else
		{
			  class SMorder *SMO;
			  SMO=new SMorder();
			  SMO->run();
			  delete SMO;
			  Z_();
		}
}
void BaseMenu::GO_(int n, char param[maxPARAM][lenPARAM])
{
		int toGO;
		for (toGO=0; toGO<MenuNo; toGO++)
		{
			if (!stricmp(MENU[toGO].go, param[1]))
			{
				if ( appMenuObject(toGO)== ERR ) return;
				ExitLoop=1;
				break;
			}
		}
}
void BaseMenu::NCD_()
{
		/*
		char* argv[3], dir_str[200];
		argv[0]=(char*)malloc(sizeof(char)*60);
		argv[1]=(char*)malloc(sizeof(char)*10);
		sprintf(argv[0],"%s\\VISUALGO.EXE",InstDir);
		sprintf(argv[1],"%i",port);
		argv[2]=NULL;
		getcwd(dir_str,199);
		if ( chdir(InstDir)==-1) halt("Mighty was not able to change directory - VG1");

		int MenuNum=SpawnProg(P_WAIT, argv[0], argv, 1);

		if ( chdir(dir_str)==-1) halt("Mighty was not able to change directory - VG2");

		free(argv[0]);
		free(argv[1]);
		*/
		SCR.push(0,0,639,479);
		rCOLOR.push();
		htempwindow(1,1,hgetmaxax(), hgetmaxay());  // for chatting box
		int MenuNum = VG();
		rCOLOR.pop();
		c_hclrscr();
		hlastwindow();
		SCR.pop();
		if ( MenuNum != CANCEL )
		{
			if ( appMenuObject(MenuNum-1)== ERR ) return;
			ExitLoop=1;
		} else Z_();
}
void BaseMenu::NEW_()
{
	 int nPrinted=0, nMenu;
	 char GoStr[9];
	 char GoIndex=0;
	 ReadDataFile(297); //doing host initialization. percent :
	 for (nMenu=1; nMenu<=MenuNo; nMenu++)
	 {
			if (MENUDATA[nMenu-1].newdata > 0)
			{
				 c_hprintf("%20s(%8s)µA  [%2iàÅ]∑Å ¨Åù°∂Ö ∏aûaàa ∑∂Øsì°îa.\n\r", MENU[nMenu-1].title, MENU[nMenu-1].go, MENUDATA[nMenu-1].newdata);
				 nPrinted++;
			}
			if ( (nMenu==MenuNo) || ((nPrinted % L_SCR==0)&&nPrinted) )
			{
				 ReadDataFile(299); // input go string.
				 c_hgetln(GoStr, "P", 8);
				 if (!stricmp(GoStr,"P")) break;
				 if (strcmp(GoStr,""))
				 {
					  GoIndex = 1; // if str is not go destination, then Go2I returns -1;
					  break;
				 }
			}
	 }
	 if (GoIndex)
	 {
		  sprintf(temp_str, "go %s", GoStr);
		  BaseProcess(temp_str);
	 }
	 else if (nPrinted==0) ReadDataFile(300); // there is no data.
			else ReadDataFile(298); // data searching is ended.
}
void BaseMenu::MEM_()
{
		ReadDataFile(38);  // System memory is....
}
void BaseMenu::TM_()
{
	 if (!ReadAnsiFile("TIMEINFO.MSG")) ReadDataFile(8);
}
void BaseMenu::OP_()
{
	 if (existSysop)
		  switch (bSound)
		  {
				case 0 : ReadDataFile(13);
							break;
				case 1 : ReadDataFile(12);
							sound(400); delay(500);
							sound(500); delay(500);
							sound(600); delay(500);
							sound(700); delay(500);
							sound(800); delay(500);
							sound(900); delay(500);
							sound(1000); delay(500);
							nosound();
							break;
		  }
	 else ReadDataFile(156);
}
void BaseMenu::HT_()
{
	 switch (bAutoHan)
	 {
			 case 0 : bAutoHan=1;
						 ReadDataFile(14);
						 break;
			 case 1 : bAutoHan=0;
						 ReadDataFile(15);
	 }
}
void BaseMenu::MEMO_(int n, char param[maxPARAM][lenPARAM]) {}
void BaseMenu::PF_(int n, char param[maxPARAM][lenPARAM])
{
	 int find,param_idx=0;
	 class UserClass *pfU;
	 USER.SaveData();
	 if (n==1)
	 {
		  strcpy(param[1],USER.stU.ID);
		  n=2;
	 }
	 while( ++param_idx < n )
	 {
		for (find=1; find<=MaxUserNo; find++)
		{
			pfU=new UserClass(find);
			pfU->ReadData();
			if ( !strcmp(pfU->stU.ID,param[param_idx]) )
			{
				pfU->ViewPf();
				delete pfU;
				break;
			}
			delete pfU;
		}
	 }
}
void BaseMenu::X_()
{
	 ReadDataFile(16);
	 if ( AnswerIs('Y','Y',false))
	 {
		  WriteLogData("‘ê ∏˜¨w∏‚∑aù° ∏Û≠¢π∑ûa ‘ë");
		  BYE_();
	 }
}
void BaseMenu::BYE_()
{
			 appObject(CUT, NULL);
			 ExitLoop=1;
}
//--------------------------------------------------------------------------
//              Exec Base Class Member functions declalaion.              //
//--------------------------------------------------------------------------
BaseExec::BaseExec() : SuperClass()
{ExitLoop=0;}

void BaseExec::P_()
{
		char NewIndex[7];
		if (aliveUSER)
		{
			 strcpy (NewIndex, index);
			 NewIndex[5-strnch(index,'0')] = '0';
			 if ( Me2I(NewIndex) == ERR ) return;
			 if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
			 ExitLoop = 1;
		} else ErrMsg("User got out.");
}
void BaseExec::BYE_()
{
			 appObject(CUT, NULL);
			 ExitLoop=1;
}

//--------------------------------------------------------------------------
//              SubMenu Class Member functions declalaion.                //
//--------------------------------------------------------------------------

SubMenu::SubMenu(char *_index) : BaseMenu()
{

	 strcpy (index,_index);
	 //  SUBMENU INDEXING ROUTINE
	 int i,j,temp,k=0,zn;
	 SubNo=0;
	 zn=strnch(index,'0');
	 if ( zn == 6)    // when the menu is top menu
	 {

			for (i=0; i<MenuNo; i++)
				 if ( strnch(MENU[i].index,'0') == strnch(index,'0')-1 )
						SubNo++;

			for (i=0; i<MenuNo; i++)
					if ( strnch(MENU[i].index,'0') == strnch(index,'0')-1 )
						nSUB[k++]=i;
	 }
	 else
	 {
			for (i=0; i<MenuNo; i++)
			{
				if (   !strncmp(MENU[i].index, index, 6-zn ) &&
						 (strnch(MENU[i].index,'0') == strnch(index,'0')-1) )
								SubNo++;
			}
			for (i=0; i<MenuNo; i++)
				if (   !strncmp(MENU[i].index, index, 6-zn )  &&
						 (strnch(MENU[i].index,'0') == strnch(index,'0')-1) )
								nSUB[k++]=i;
	 }

	 // sort the menu title
	 for (i=0; i<SubNo-1; i++)
		 for (j=i+1; j<SubNo; j++)
			 if (MENU[nSUB[i]].run > MENU[nSUB[j]].run)
			 {
					temp = nSUB[j];
					nSUB[j] = nSUB[i];
					nSUB[i] = temp;
			 }
}

void SubMenu::PrintCMD()
{
	 if (!ReadAnsiFile("SUB.CMD") ) ReadDataFile(9);
}

void SubMenu::Z_()
{
	 int i;
	 //hprintf("%s.mnu",MENU[nAcc].ansifile); getch();
	 c_hclrscr();
	 if  ( strlen(MENU[nAcc].ansifile) == 0  ||
			!ReadAnsiFile( strcat2( MENU[nAcc].ansifile, ".MNU") ))
	 {
		 ReadDataFile(153);
		 for (i=0; i<SubNo; i++)
		 {
			if (MENUDATA[nSUB[i]].alldata!=-1)
				c_hprintf("\n\r     <%2i> %-20s [%5i/%5i] [%2i-%2i]",MENU[nSUB[i]].run,MENU[nSUB[i]].title, MENUDATA[nSUB[i]].newdata, MENUDATA[nSUB[i]].alldata, MENUDATA[nSUB[i]].month, MENUDATA[nSUB[i]].day);
			else
				c_hprintf("\n\r     <%2i> %-20s",MENU[nSUB[i]].run,MENU[nSUB[i]].title);
		 }
		 c_hputs("\n\r\n\r");
	 }
}
void SubMenu::NewProcess(char *str)
{
	 int i;
	 for (i=0; i<SubNo; i++)
			if ( is_int(str) && MENU[nSUB[i]].run == atoi(str) )
			{
				 if (appMenuObject(nSUB[i])==ERR) return;
				 ExitLoop=1;
				 break;
			}
}
void SubMenu::run()
{
	 int i;
	 char CMD[maxGETLN+1];
	 c_hclrscr();
	 Z_();
	 ExitLoop=0;
	 while (ExitLoop!=1)
	 {
			PrintCMD();
			for (i=0; i< maxGETLN+1; i++) *(CMD+i)=0;
			c_hgetln(CMD,"X",maxGETLN);
			BaseProcess(CMD);
			NewProcess(CMD);
	 }
}


//--------------------------------------------------------------------------
//              BbsData Class Member functions declalaion.                 //
//--------------------------------------------------------------------------
BbsData::BbsData(int num)
{
	DataNum = num;
	iE=0;  // iE starts from 1 but... because ++iE will be executed..so..
	y=1;   // iE is zero.
//	printf(" alive ");   getch();
}
long BbsData::getsize()
{
	long size=0;
	int line;
	for (line=1; line<=iE; line++) size += strlen(EDIT[line-1]);
	return size;
}
BbsData::~BbsData()
{
	int k;
	if (iE !=0) for (k=1; k<=iE; k++) free(EDIT[k-1]);
}
void BbsData::RealEdit()
{
		do {
					if ( ++iE >= 1000 ) return;
					c_hprintf("%4i∫â : ",iE);
					EDIT[iE-1]=(char*)malloc(ECHARS+1);
					if ( EDIT[iE-1]==NULL )
					{
						 ReadDataFile(28);
						 break;
					}
					memset(EDIT[iE-1],0,ECHARS+1);
					c_hgetln(EDIT[iE-1],".",ECHARS);
			 } while (strcmp(EDIT[iE-1],".") );
}
BbsData::ReallyQuit()
{
		ReadDataFile(27);   // Really Quit?
		if ( AnswerIs('Y','Y',false) )
		{
			 ReadDataFile(34); //canceled
			 return QUIT;
		}
		return NOQUIT;
}

// page starts from one !!
void BbsData::PrintEDIT(int page)
{
		int PrintingLine;
		PrintedLines=0;
		PrintingLine = (page - 1) * L_TEXT+1;

		while( (PrintedLines < L_TEXT) && (PrintingLine <= iE-1) )
		{
					c_hprintf("%4i∫â : ",PrintingLine);
					c_hputs( EDIT[ PrintingLine++ - 1 ] );
					c_hputs("\n\r");
					PrintedLines++;
		}
		c_hgotoxy(edit_sx, edit_sy+y-1);
		c_hputs(">");
}

// returns true  - when page is changed
// returns false - when page is not changed
// defined constant here is not hanra-pro constant.
// page and y is started from 1
bool BbsData::ProcessScanKey(char scan_code)
{
		bool bMoveCur=false, bReadText=false;
		switch( scan_code )
		{
				case UPARR_     : if (y>1)
													{
														 --y;
														 bMoveCur=true;
														 break;
													}
									if ( (y==1)&&(Tpage!=1) )
													{
														 Tpage--;
														 y = L_TEXT;
														 bReadText=true;
													}
													break;
				case DNARR_   : if (y<PrintedLines)
													{
														 ++y;
														 bMoveCur=true;
														 break;
													}
								if ( (y==L_TEXT) && (Tpage*L_TEXT < iE -1) )
													{
														 Tpage++;
														 y=1;
														 bReadText=true;
													}
													break;
		}
		if (bMoveCur==true)
		{
			c_hputs("\b ");
			c_hgotoxy(edit_sx,edit_sy+y-1);
			c_hputch('>');
		}
		return bReadText;
}
// cc - comm char        sc - sysop char
int BbsData::GetLine(int mode)
{
		char s_page[30];
		int cc=-1,sc=-1;
		Tpage = 1;
		while(1)
		{
				//mode : #define mCHANGE 0   --> ReadDataFile(45);
				//       #define mINSERT 1   --> ReadDataFile(46);
				//       #define mDELETE 2   --> ReadDataFile(47);
				//       in all cases        --> ReadDataFile(45+mode);
				c_hclrscr();
				ReadDataFile(45+mode);  // @[2J Editing a line
				itoa(Tpage, s_page, 10);
				c_hputs(s_page);
				if (!ReadAnsiFile("EDITKEY.HLP")) ReadDataFile(48);  // keys Help
				PrintEDIT(Tpage);
				while(1)
				{
						if ( !kbhit() && ( !SioRxQue(port) && !SioTxQue(port) ) )
						{
							 time_process();
							 if (!bLocal && !SioDCD(port)) return 1;
						}
						if (  kbhit() )
						{
							 sc=getch();
							 if (sc==0)
							 {
								 sc=getch();
								 if ( !process_ctrlkey(sc) )
									  if (ProcessScanKey(sc)==true) // when PgUp or PgDn
								 break;
							 }
							 else if ( sc==ENTER )
							 {
								 c_hgotoxy(1,edit_sy+PrintedLines+1);
								 hprintf("%iÕA∑°ª°, %iºÅ ∫â",Tpage,(Tpage-1)*L_TEXT+y);
								 return (Tpage-1)*L_TEXT+y;
							 }
						}
						if (!bLocal && SioRxQue(port) )
						{
							 cc=SioGetc(port, 18);
							 if (cc==27)
							 {
								 char tmp[3];
								 SioGets(port, tmp, 2, 0);
								 if ( !strcmp( tmp,"[A") ) cc = _UPARR;
								 if ( !strcmp( tmp,"[B") ) cc = _DNARR;
								 if (ProcessScanKey(cc)==true) // when PgUp or PgDn
								 break;
							 }
							 else if (cc=='8' || cc=='2')
							 {
								 switch(cc)
								 {
									  case '8' : cc=_UPARR; break;
									  case '2' : cc=_DNARR;
								 }
								 if (ProcessScanKey(cc)==true) // when PgUp or PgDn
								 break;
							 }
							 else if ( cc==ENTER )
							 {
								 c_hgotoxy(1,edit_sy+PrintedLines+1);
								 hprintf("%iÕA∑°ª°, %iºÅ ∫â",Tpage,(Tpage-1)*L_TEXT+y);
								 return (Tpage-1)*L_TEXT+y;
							 }
						}
				}
		}
}
void BbsData::Change()
{
	char new_string[ECHARS+1];
	int line_num;
	y=1;
	SetHanMode(true);
	while(1)
	{
		 memset(new_string, 0, ECHARS+1);
		 line_num = GetLine(mCHANGE);
		 ReadDataFile(49); // Substitute selected line.
		 c_hputs("\n\r∂•úÅêÅ∂w:");
		 c_hputs( EDIT[ line_num -1 ] );
		 c_hputs("\n\r¨Å  êÅ∂w:");
		 c_hgetln(new_string,"", ECHARS);
		 if ( !strcmp(new_string, "") )
		 { /*ReadDataFile(CANCELED)*/ return; }
		 else strcpy(EDIT[ line_num-1], new_string);
	}
}
void BbsData::Insert()
{
	char new_string[ECHARS+1];
	int line_num,i;
	y=1;

	memset(new_string, 0, ECHARS+1);
	line_num = GetLine( mINSERT );
	ReadDataFile(50); // Input Inserting sentence above selected line.
	c_hputs("\n\r¨s∑≥êÅ∂w:");
	SetHanMode(true);
	c_hgetln(new_string,"", ECHARS);
	if (!strcmp(new_string,""))
	{ /*ReadDataFile(CANCELED)*/ return; }// if new_string is not ""
	else
	{
		EDIT[++iE-1]=(char*)malloc(ECHARS+1);
		if (EDIT[iE-1] == NULL)
		{
			ErrMsg("ERROR : Not enough memory - inserting bbsdat routine");
			return;
		}
		for (i=iE-1; i>=line_num; i--) strcpy( EDIT[ i ], EDIT[ i-1 ] );
		strcpy(EDIT[ line_num-1 ], new_string);
	}
}

void BbsData::Delete()
{
	char ans[2];
	int line_num,i;

	memset(ans, 0, 2);
	line_num = GetLine( mDELETE );

	ReadDataFile(51); // Will you really delete it?.
	if ( AnswerIs('Y', 'N', true) )
	{
		 for (i=line_num; i<=iE-1; i++) strcpy( EDIT[ i - 1 ], EDIT[ i ] );
		 free( EDIT[iE-- -1] );
	}
}
void BbsData::View()
{
	c_hputs("\n\r");
	for (int line=ViewingLine; line < iE && line < (ViewingLine + L_TEXT); line++)
		c_hprintf("%4i∫â : %s\n\r",line, EDIT[line-1]);
	ViewingLine+=L_TEXT;
	if (ViewingLine >= iE) ViewingLine = 1;
	c_hputs("\n\r");
}
void BbsData::PR_()
{
	 for (int line = 1; line < iE; line++) c_hprintf("%s\n\r", EDIT[line-1]);
}
void BbsData::LoadData()
{
	int i, count;
	char ch=0,FileName[13];
	bool exitloop=false;
	GetFileName(DataNum,FileName);
	FILE *fTEXT=fopen(FileName,"rt");
	if (fTEXT == NULL) halt("Not Enough Memory : Loading BBS text");

	if (iE != 0)
	{
		 for (i=1; i<=iE; i++) free( EDIT[i-1] );
		 iE=0; y=1;
	}

	while(exitloop==false)
	{
		EDIT[++iE-1]=(char*)malloc(ECHARS+1);
		if ( EDIT[iE-1]==NULL ) halt("ERROR: NOT ENOUGH MEMORY WHILE LOADING TEXT DATA");
		memset(EDIT[iE-1],0,ECHARS+1);
		count=-1;
		while (1)
		{
			 ch = fgetc(fTEXT);

			 if (count < ECHARS-1 ) ++count;
			 if (ch=='\n')
			 {
					EDIT[iE-1][count]=0;
					if ( count==1 && EDIT[iE-1][count-1]=='.')  exitloop=true;
					break;
			 }
			 if (feof(fTEXT)) halt("ERROR : Bbs Data is broken");
			 EDIT[iE-1][count] = ch;
		}
	}
	fclose(fTEXT);
}

// page starts from one!!
void BbsData::PrintText(int page)
{
	// Text output routine
	int start_line,count=0;
	start_line = (page-1)*L_TEXT + 1;  // start_line start from 1;

	while(count < L_TEXT)
	{
		if ( start_line + count >= iE ) break;   // when start_line+count is iE
		c_hprintf("     %s\n\r",EDIT[start_line+count-1] );  // printing is accepted.
		++count;
	}
}

void BbsData::SaveData()
{
		char FileName[13];
		int iF;
		// routine of getting filename
		GetFileName(DataNum,FileName);
		FILE *BbsDat=fopen(FileName, "wt");
		if (BbsDat == NULL) halt("Not Enough Memory : Can't open BBS data file..");

		iF=1;
		while(iF <= iE)
		{
			 //hprintf("%s\n",EDIT[iF-1]);
			 fputs(EDIT[iF++ -1],BbsDat);
			 fputc('\n',BbsDat);
		}
		//getch();
		// DEBUG  -- poruk debugged.
		//if ( strcmp(EDIT[iE-1],".") )  fputs(".\n",BbsDat);
		fclose(BbsDat);
}
BbsData::ORDERprocess(char *ORDER)
{
		if (!strcmp(ORDER,"S") || !strcmp(ORDER,"s") )
		{
					if (!strcmp(EDIT[0],"."))
					{
							 ReadDataFile(33); // if you do not make text, can't save it.
							 return NotSaved;
					}
					else
					{
							 if ( getsize() < MinBbsSize )
							 {
								  c_hprintf("âAØ°¢â∑e ¬A≠° %ibyte∑°¨wñA¥·¥° ówù¢ –iÆÅ ∑∂Øsì°îa.\n\r");
							 }
							 else
							 {
								  SaveData();
								  ReadDataFile(32); // it is saved just now!!
								  return Saved;
							 }
					}
		}
		if (!stricmp(ORDER,"E") ) Change();
		if (!stricmp(ORDER,"I") ) Insert();
		if (!stricmp(ORDER,"D") ) Delete();
		if (!stricmp(ORDER,"V") ) View();
		if (!stricmp(ORDER,"Q") ) return ReallyQuit();
		if (!stricmp(ORDER,"C") )
		{
			 c_hputch(CR);
			 c_hputch(LF);
			 free( EDIT[ iE-1 ] );  // freemem last line, '.'
			 iE-=1;  // minus frememed line.
			 RealEdit();
		}
		return CONTINUE;
}
BbsData::EditOrder()
{
		int isSaved;
		char ORDER[2];
		ViewingLine = 1;    // Initializing Viewing Line of editor.
		SetHanMode(false);
		while (1)
		{
				if (!ReadAnsiFile("EDIT.CMD")) ReadDataFile(24); // Order of internal editor
				memset(ORDER, 0, 2);
				c_hgetln(ORDER,"Q",1);
				if ((isSaved=ORDERprocess(ORDER)) != CONTINUE)
					 return isSaved;
		}
}
BbsData::make()
{
		int isSaved;
		if (!ReadAnsiFile("EDITLINE.MSG")) ReadDataFile(25);   // internal editor
		RealEdit();
		isSaved=EditOrder();
		return isSaved;
}
// data member BbsData *TEXT gets alive after the first reading of IDX file
// ,and deleted after p command is pressed.
// when writting, TEXT gets alive and gets dead immediately.
//--------------------------------------------------------------------------
//              TEXTMenu Class Member functions declalaion.               //
//              parent Object of BbsMenu, PdsMenu, MailMenu               //
//                                                                        //
//                                                                        //
//--------------------------------------------------------------------------
int TEXTMenu::getmaxdatano()		// get start of title.
{
		int max = 0;
		if ( !access("MENUDATA.IDX" ,0) )
		{
			  FILE *IdxFile=fopen("MENUDATA.IDX","rb");
			  if (IdxFile==NULL) halt("Not Enough Memory : getting start number");
			  fseek(IdxFile,0L,SEEK_END);
			  max = ftell(IdxFile)/sizeof(MenuIndex_t);
			  fclose(IdxFile);
		}
		return max;
}
// REMEMBER.. start is the biggest number of all
void TEXTMenu::setstart()		// set start of title.
{
		int i, no_of_idx;
		struct MenuIndex_t toFIND;
		NowTop = All = start = 0;
		if ( !access("MENUDATA.IDX",0) )
		{
				 FILE *IdxFile=fopen("MENUDATA.IDX","rb");
				 if (IdxFile==NULL) halt("Not Enough Memory : setting start number");
				 fseek(IdxFile,0L,SEEK_END);
				 no_of_idx = ftell(IdxFile)/sizeof(MenuIndex_t);
				 for (i=no_of_idx; i>=1; i--)
				 {
					 fseek(IdxFile,(long)(sizeof(struct MenuIndex_t)*(i-1)),SEEK_SET);
					 fread(&toFIND, sizeof(MenuIndex_t), 1, IdxFile);
					 if ( toFIND.alive != 0 && ReadAccess(toFIND.n) )
					 {
						  All = start = toFIND.n;
						  NowTop = start - (title_page-1) * L_SCR;
						  break;
					 }
				 }
				 fclose(IdxFile);
		}
}
// REMEMBER.. end is the biggest number of all
void TEXTMenu::setend()		// set end of title.
{
		int i, no_of_idx;
		struct MenuIndex_t toFIND;
		end=0;
		if ( !access("MENUDATA.IDX",0) )
		{
				 FILE *IdxFile=fopen("MENUDATA.IDX","rb");
				 if (IdxFile==NULL) halt("Not Enough Memory : setting end number");
				 fseek(IdxFile,0L,SEEK_END);
				 no_of_idx = ftell(IdxFile)/sizeof(MenuIndex_t);
				 fseek(IdxFile,0L,SEEK_SET);
				 for (i=1; i<=no_of_idx; i++)
				 {
					 fread(&toFIND, sizeof(MenuIndex_t), 1, IdxFile);
					 if ( toFIND.alive != 0 && ReadAccess(toFIND.n) )
					 {
						 end=toFIND.n;
						 break;
					 }
				 }
				 fclose(IdxFile);
		}
}

// assume that data number IDX.n is already specified
void TEXTMenu::SaveIdx(struct MenuIndex_t& BI, int SaveMode)
{
		char ch,FileName[13];
		int count;
		long fcount,filelen;
		struct _AllTime write;
		FILE *BbsIdx, *BbsDat;

		if (SaveMode==NewWrite && aliveUSER==0) halt("ERROR:happended processing user object-4");

		switch (SaveMode)
		{
			 case AfterEdit :

				// file line counting routine.
				GetFileName(BI.n,FileName);
				BbsDat = fopen(FileName,"rb");
				fseek(BbsDat,0L,SEEK_END);
				filelen = ftell(BbsDat);
				fseek(BbsDat,0L,SEEK_SET);
				fcount=0;
				count=0;
				while( fcount++ < filelen)
				{
					ch = fgetc(BbsDat);
					if (ch=='\n') count++;
				}
				fclose(BbsDat);
				//at last.. BbsData::iE-1 has "." so.. count -1 is right.
				BI.page = (count-1) /L_TEXT +1;
				BbsIdx = fopen("MENUDATA.IDX","r+b");
				fseek(BbsIdx,(long)( sizeof(struct MenuIndex_t)*(BI.n-1) ),SEEK_SET);
				break;

			 case OnceRead :
				++BI.look;
				GetFileName(BI.n,FileName);
				BbsIdx=fopen("MENUDATA.IDX","r+b");
				fseek(BbsIdx,(long)( sizeof(struct MenuIndex_t)*(BI.n-1) ),SEEK_SET);
				break;

			 case NewWrite :
				if (access("MENUDATA.IDX",0)==-1) BI.n=1;
				else BI.n = getmaxdatano()+1;
				if (BI.alive == 0) BI.alive=1;
				strcpy( BI.id, USER.stU.ID );
				strcpy( BI.name, USER.stU.NAME );
				GetAllTime(&write);
				BI.year = write.year;
				BI.month = write.month;
				BI.day = write.day;
				BI.hour = write.hour;
				BI.min = write.min;

				// file line counting routine.
				GetFileName(BI.n,FileName);
				BbsDat = fopen(FileName,"rb");
				if (BbsDat==NULL) { ErrMsg("°A°°ü°àa ¶Åπ¢–sì°îa"); return; }

				fseek(BbsDat,0L,SEEK_END);
				filelen = ftell(BbsDat);
				fseek(BbsDat,0L,SEEK_SET);
				fcount=0;
				count=0;
				while( fcount++ < filelen)
				{
					ch = fgetc(BbsDat);
					if (ch=='\n') count++;
				}
				fclose(BbsDat);

				//at last.. BbsData::iE-1 has "." so.. count -1 is right.
				BI.page = (count-1) /L_TEXT +1;
				BI.look=0;
				BI.down=0;
				BbsIdx=fopen("MENUDATA.IDX","ab");
				break;
			 case Normal :
				BbsIdx=fopen("MENUDATA.IDX","r+b");
				fseek(BbsIdx,(long)( sizeof(struct MenuIndex_t)*(BI.n-1) ),SEEK_SET);
		}
		if (BbsIdx == NULL) halt("Not Enough Memory : Can't open BBS index file..");
		fwrite(&BI, sizeof(struct MenuIndex_t), 1, BbsIdx);
		fclose(BbsIdx);
		setstart();
		setend();
}
// BI : bbs index data structure parameter.
int TEXTMenu::LoadIdx(struct MenuIndex_t& BI, int num)
{
		FILE *BbsIdx;
		if (!access("MENUDATA.IDX",0))
		{
			 BbsIdx=fopen("MENUDATA.IDX","rb");
			 if (BbsIdx == NULL) halt("Not Enough Memory : Can't open BBS index file..");
		} else return CANCEL;
		fseek(BbsIdx, 0L, SEEK_END);

		if ( num <=0 || ftell(BbsIdx)/sizeof(BI ) < num) return DEAD;

		fseek(BbsIdx, (long)( sizeof(MenuIndex_t)*(num-1) ), SEEK_SET);
		fread(&BI, sizeof(MenuIndex_t), 1, BbsIdx);
		fclose(BbsIdx);

		if ( BI.n != num ) halt("INDEX FILE is gone bad");
		if  ( BI.alive != 0 ) return ALIVE;
		return DEAD;
}
int TEXTMenu::isBBSnum(char *CMD)
{
		struct MenuIndex_t BI;
		int max,num,i;
		if ( strlen(CMD) > 5 ) return 0;
		for (i=0; i< strlen(CMD); i++)
			 if ( ( CMD[i] > '9' ) || ( CMD[i] < '0') ) return 0;
		max = start;
		num = atoi(CMD);
		if ( (num > max) || (num < 1) ) return 0;
		LoadIdx(BI,num);
		if (BI.alive == 0) return 0;
		return 1;
}

/* Ansi Code ---> 	*/
void TEXTMenu::PrintLastTitle(int UP, int DOWN)
{
		if(!ReadAnsiFile("LASTLINE.TIT")) ReadDataFile(188);
		c_hputs("[7m");
		if (UP) c_hputs("‘û"); else c_hputs("  ");
		if (DOWN) c_hputs("‘ü"); else c_hputs("  ");
		c_hputs("[27m");
		c_hputs("\n\r");
}
// page and num starts from 1
void TEXTMenu::PrintTitle(int page)
{
		int nToBeRead,nRead=0;
		setstart();  setend();
		ReadDataFile(29);
		PrintFirstTitle();
		if ( !access("MENUDATA.IDX",0) && start != 0 && end != 0 )
		{
				 nToBeRead = (page-1) * L_SCR;
				 title_start = start - nToBeRead;

				 if ( start - nToBeRead < end )
				 {
						 PrintNoData();
						 PrintLastTitle(false, false);
						 return;
				 }

				 title_start = start - nToBeRead;

				 FILE *BbsIdx=fopen("MENUDATA.IDX","rb");
				 if (BbsIdx==NULL) halt("Not Enough Memory : Processing of order of Z");

				 while(nRead < L_SCR)
				 {
						fseek(BbsIdx, sizeof(IDX)*( title_start-nRead++ -1 ), SEEK_SET);
						fread(&IDX, sizeof(IDX), 1, BbsIdx);
						if ( IDX.alive!=0  && ReadAccess(IDX.n) )
						{
								PrintOneLine();
						}
						if (title_start - nRead <= end -1) break;
				 }
				 PrintLastTitle( page!=1, title_start - L_SCR >= end );
				 fclose(BbsIdx);
		}
		if (nRead == 0)
		{
				 PrintNoData();  // there is no data of BBS
				 PrintLastTitle(false, false);
		}
}

void TEXTMenu::PrintData(int num, int page)
{
		if (first==1)
		{
				first=0;
				SetMode(mTEXT); // deleting before TEXT routine is here.
				TEXT = new BbsData(num);
				if ( LoadIdx(IDX, num) == CANCEL )
				{
					  delete TEXT;
					  mode = mTITLE;
					  return;
				}
				TEXT->LoadData();
		}
		c_hclrscr();
		PrintIdx();
		TEXT->PrintText(page);
		PrintLastTitle(page!=1, page < IDX.page );
		// TEXT is deleted when "P" order is processed.
}
// index : for movement of all menus.
// path : for making menu directory.
TEXTMenu::TEXTMenu(char* _index, char* _path) : BaseMenu()
{
		strcpy(index, _index);
		strcpy(path, _path);
		if ( chdir(InstDir) ) halt("ERROR : Can't change directory to mighty installed directory.");
		if ( chdir(path) ) halt("ERROR : directory is invalid");
		title_page=1;
		text_page=1;
		first = 0;
		mode = mTITLE;
		setstart();
		setend();
}
TEXTMenu::~TEXTMenu()
{
}
void TEXTMenu::P_()
{
		if (mode==mTITLE) BaseMenu::P_();
		if (mode==mTEXT)
		{
				 //Idx is already loaded
				 SetMode(mTITLE);
				 Z_();
		}
}
// I don't know why computer's left memory gets down, when
// BaseMenu::T_() is called before SetMode(mTITLE) is called.
// But I had patched for computer's left memory.
void TEXTMenu::A_()
{
		if (mode == mTITLE)
		{
				int nz; char NewIndex[7];
				nz = strnch(index,'0');
				if ( nz == 6) return;
				strcpy (NewIndex, index);
				NewIndex[5-nz] = NewIndex[5-nz]-1;
				if ( NewIndex[5-nz] == '0') return;
				if ( Me2I(NewIndex) == ERR ) return;
				if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
				ExitLoop = 1;
		}
		/*if (mode == mTEXT)
		{
				PrintData(bbs_number,text_page);
				Don't forget to call SetMode(mTITLE);
		}*/
}

void TEXTMenu::N_()
{
		if (mode==mTITLE)
		{
				if (strnch(index,'0') == 6) return;
				int nz;
				char NewIndex[7];
				nz=strnch(index,'0');
				if ( nz == 6) return;
				strcpy (NewIndex, index);
				NewIndex[5-nz] = NewIndex[5-nz]+1;
				if ( Me2I(NewIndex) == ERR ) return;
				if ( appMenuObject(Me2I(NewIndex)) == ERR ) return;
				ExitLoop = 1;
		}
		/*if (mode==mTEXT)
		{
				Don't forget to call SetMode(mTITLE);
		} */
}
// page starts from 1
void TEXTMenu::Z_()
{
		c_hclrscr();
		if ( first ) PrintData(bbs_number,text_page);
		else
		{
			 if (mode == mTITLE ) PrintTitle(title_page);
			 if (mode == mTEXT ) PrintData(bbs_number,text_page);
		}
}
void TEXTMenu::F_()
{
		if (mode == mTITLE)
		{
				if (title_page - 1 < start / L_SCR )
				{
						title_page++;
						Z_();
				}
				else ReadDataFile(36);  // there is no data !!
		}
		if (mode== mTEXT)
		{
				int page;
				page = IDX.page;
				if (text_page - 1 < page - 1)
				{
						text_page++;
						Z_();
				}
				else ReadDataFile(36);
		}
}
void TEXTMenu::B_()
{
		if (mode == mTITLE)
		{
				if (title_page > 1 )
				{
						title_page--;
						Z_();
				}
				else ReadDataFile(37);  // there is no data !!
		}
		if (mode== mTEXT)
		{
				if (text_page > 1 )
				{
						text_page--;
						Z_();
				}
				else ReadDataFile(37);
		}
}
void TEXTMenu::E_(int no, char param[maxPARAM][lenPARAM])
{
		// append comparing writer and deleter routine here!
		if( no >= 2 )
		{
			ReadDataFile(53); // Now..Read Selected bbs data.
			if( !isBBSnum( param[1] ) || !EditAccess(atoi(param[1])) )
			{
			  ReadDataFile(52); // inputed data can't be edited.
			  return;
			}
			// OtherEditProcess function prints other edit processes and process
			// it. this function returns true when other process is processed.
			// otherwise returns 0
			if(!OtherEditProcess())  // virtual function
			{
				  BbsData *eTMP=new BbsData( atoi(param[1]) );
				  eTMP->LoadData();
				  if( eTMP->EditOrder() == Saved )
				  {
						SaveIdx( IDX, AfterEdit );
						WriteLogData("‘ˇ %s∑Å %i§Â ∏aûa ÆÅ∏˜", MENU[nAcc].title, IDX.n);
				  }
				  delete eTMP;
			}
		}
		else
		if ( mode == mTEXT )
		{
			if ( !EditAccess(TEXT->GetDataNum()) ) ReadDataFile(137); // it 's not yours
			else
			{
				ReadDataFile(53);
				if(!OtherEditProcess())
				{
					 if (TEXT->EditOrder() == Saved)
					 {
						  SaveIdx( IDX, AfterEdit );
						  WriteLogData("‘ˇ %s∑Å %i§Â ∏aûa ÆÅ∏˜", MENU[nAcc].title, IDX.n);
					 }
				}
			}
		}
}

void TEXTMenu::PRprocess(int n)
{
	 char numstr[11];
	 struct MenuIndex_t toPR;
	 itoa(n,numstr,10);

	 if( !isBBSnum( numstr ) )
	 {
			c_hputs(numstr);
			ReadDataFile(56); // invalid number.
			return;
	 }
	 if( !ReadAccess(n) )
	 {
			c_hputs(numstr);
			ReadDataFile(280); // You have no right to pr.
			return;
	 }
	 if (mode==mTEXT) TEXT->PR_();
	 else
	 {
			BbsData *eTMP=new BbsData( n );
			eTMP->LoadData();
			eTMP->PR_();
			delete eTMP;
	 }
	 LoadIdx(toPR, n);
	 SaveIdx(toPR, OnceRead);
}

void TEXTMenu::PR_(int no, char param[maxPARAM][lenPARAM])
{
	 int i=0,j, bDoPrint=1;
	 if( no >= 2 )
	 {
		  if (!GoOnWithSelectedNum(no,param,281,0,MAX_SEL_ITEM)) return;
		  ReadDataFile(278); // do print capture
		  while( ++i<no && bDoPrint)
		  {
			  if (  (i<=no-3) && (atoi(param[i])!=0) &&
					!strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
			  {
					for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
					{
						 PRprocess(j);
						 ReadDataFile(282);
						 if (AnswerIs('N', 'N', true))
						 {
							 bDoPrint=0;
							 break;
						 }
					}
					i+=2;
			  }
			  else
			  {
					PRprocess( atoi(param[i]) );
					ReadDataFile(282);
					if (AnswerIs('N', 'N', true)) break;
			  }
		  }
		  ReadDataFile(279);   // printing ended
	 }
	 else
	 if (mode == mTEXT)
	 {
		  ReadDataFile(278);
		  PRprocess( IDX.n );
		  ReadDataFile(279);
	 }
}
void TEXTMenu::DDprocess(int n)
{
	 char numstr[6];
	 struct MenuIndex_t toDEL;
	 itoa(n,numstr,10);

	 c_hputs(numstr);
	 if( !isBBSnum( numstr ) )
	 {
			ReadDataFile(56); // invalid number.
			return;
	 }
	 if( !DelAccess(n) )
	 {
			ReadDataFile(92); // You have no right to del.
			return;
	 }
	 ReadDataFile(58); // deleted.
	 WriteLogData("‘ˇ %s∑Å %i§Â ∏aûa ¨bπA", MENU[nAcc].title, n);
	 LoadIdx( toDEL, n ); toDEL.alive=0;
	 SaveIdx( toDEL, Normal );
}

void TEXTMenu::DD_(int no, char param[maxPARAM][lenPARAM])
{
	 int i=0,j;
	 if( no >= 2 )
	 {
		  if (!GoOnWithSelectedNum(no,param,57,55,MAX_SEL_ITEM)) return;
		  while( ++i<no )
		  {
			  if (  (i<=no-3) && (atoi(param[i])!=0) &&
					!strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
			  {
					for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
						 DDprocess(j);
					i+=2;
			  }
			  else  DDprocess( atoi(param[i]) );
		  }
	 }
	 else
	 if (mode == mTEXT)
	 {
		  ReadDataFile(59);// deleting now seeing data onto temp.
		  ReadDataFile(55);// Will you really delete? [y/n]
		  if ( AnswerIs('N','N',true) ) return; // ans is not Y , y
		  DDprocess( IDX.n );
	 }
	 setstart();
	 setend();
}
int TEXTMenu::CalculateFileSize()
{
	long size=0l;
	struct ffblk filetype;
	findfirst(strcat2(DownDir,"\\*.*"),&filetype,0);
	while( findnext(&filetype) != -1)
	{
		if ( !stricmp(IDX.FileName,filetype.ff_name) )
		{
			size = filetype.ff_fsize;
			break;
		}
	}                // I can't find uploaded file.
	if (size==0l)
	{
		ReadDataFile(74);
		return ERR;
	}
	//DEBUG : file size limiting routine should be included here.
	IDX.size = size;
	return NOERR;
}

void TEXTMenu::ConvertSize(float& filesize, char& postchar)
{
		if (IDX.size < 1024L)
		{
			 filesize = IDX.size;
			 postchar = 'B';
		}
		else if (IDX.size < 1048576L)
		{
			 filesize = IDX.size/1024.0L;
			 postchar = 'K';
		}
		else
		{
			 filesize = IDX.size/1048576.0L;
			 postchar = 'M';
		}
}
int TEXTMenu::DelAccess(int n)
{
	 MenuIndex_t tMI;
	 if (USER.GetGrade() == SYSOP) return 1;
	 if (USER.UserNo == nGUEST) return 0;
	 LoadIdx(tMI, n);
	 if (!strcmp(USER.stU.ID,tMI.id)) return 1;
	 return 0;
}
int TEXTMenu::EditAccess(int n)
{
	MenuIndex_t tMI;
	if (USER.GetGrade() == SYSOP) return 1;
	if (USER.UserNo == nGUEST) return 0;
	LoadIdx(tMI, n);
	if (!strcmp(USER.stU.ID,tMI.id)) return 1;
	return 0;
}
void TEXTMenu::PrintNoData()
{
	ReadDataFile(31);
}
int TEXTMenu::ReadAccess(int n)
{
	 if (MENU[nAcc].readlevel <= USER.stU.Level)	return 1;
	 return 0;
}
int TEXTMenu::WriteAccess()
{
	 if(USER.UserNo != nGUEST)
		 if (MENU[nAcc].writelevel <= USER.stU.Level) return 1;
	 return 0;
}
void TEXTMenu::run()
{
	 int i;
	 char CMD[maxGETLN+1];
	 // for dos shell, chdir is here.
	 if ( chdir(InstDir) ) halt("ERROR : Can't change directory to mighty installed directory.");
	 if ( chdir(path) ) halt("ERROR : Can't change directory to mighty installed directory.");
	 Z_();
	 ExitLoop=0;
	 while (ExitLoop!=1)
	 {
			 PrintCMD();
			 for (i=0; i< maxGETLN; i++) *(CMD+i)=0;
			 c_hgetln(CMD,"X",maxGETLN);
			 BaseProcess(CMD);
			 TextProcess(CMD);
			 NewProcess(CMD);
	 }
	 SetMode(mTITLE);
}
void TEXTMenu::S_()
{
	 if (USER.UserNo==nGUEST) ReadDataFile(290); // guest can't use wmail
	 else
	 {
		 if (!MENU[nAcc].bSecret)
		 {
			 // mail concerned menu do not have to do with index directory.
			 class WMailMenu WMail("000000", IDX.id);
			 WMail.run();
			 Z_();
			 // temp_str is global variable
			 // path is directory of TEXTMenu
			 sprintf(temp_str, "%s\\%s", InstDir, path);
			 chdir(temp_str);
		 } else ReadDataFile(312);
	 }
}
void TEXTMenu::TextProcess(char *CMD)
{
		int no;
		char param[maxPARAM][lenPARAM];
		MakeParam( CMD, no, param );
		if (!stricmp(param[0],"e") ) E_(no, param);
		if (!stricmp(param[0],"dd") ) DD_(no, param);
		if (!stricmp(param[0],"pr") ) PR_(no, param);
		if (!stricmp(param[0],"s") ) S_();
		if (isBBSnum(CMD) && ReadAccess(atoi(CMD)))
		{
				first=1;
				text_page=1;
				bbs_number=atoi(CMD);
				Z_();
		}
}
void TEXTMenu::SetMode(int m)
{
		if (mode == mTEXT)
		{
			 SaveIdx( IDX, OnceRead );
			 delete TEXT;
		}
		mode = m;
}
//------------------------------------------------------------------------
//
//       BbsMenu Object delived from TEXTMenu Object
//
//------------------------------------------------------------------------

BbsMenu::BbsMenu(char *_index) : TEXTMenu(_index, _index)
{}
void BbsMenu::PrintFirstTitle()
{
	 if (!ReadAnsiFile("BBS.TIT")) ReadDataFile(23);  // BBS's number id name and so on.
}

void BbsMenu::PrintCMD()
{
	 if (!ReadAnsiFile("BBS.CMD")) ReadDataFile(11);  // BBS COMMAND LINE
}

int BbsMenu::OtherEditProcess()
{
	 char str[2];
	 do
	 {
		  ReadDataFile(271);
		  c_hgetln(str, "P", 1);
		  if (!stricmp(str,"1"))
		  {
				char buffer[B_SCHARS+1];
				ReadDataFile(272); // before subject
				c_hprintf("%s\n\r", IDX.subject);
				ReadDataFile(26);   // Subject
				SetHanMode(true);
				c_hgetln(buffer, "", B_SCHARS);
				SetHanMode(false);
				if (!strcmp(buffer,"")) ReadDataFile(34); // It is canceled
				else
				{
					 strcpy(IDX.subject, buffer);
					 SaveIdx(IDX, AfterEdit);
					 ReadDataFile(273);//subject is modified.
				}
				return 1;
		  }
		  if (!stricmp(str,"2")) return 0;
	 } while(stricmp(str,"P"));
	 return 1;
}
void BbsMenu::PrintIdx()
{
		ReadDataFile(35); // line
		int sec = MENU[nAcc].bSecret;
		c_hprintf("  ãi ≥e ∑° : %8s(%8s)                     §Â  —°[∏Â¡A] : %i [%i]\n\r",sec?"????????":IDX.name,sec?"????????":IDX.id,IDX.n,start);
		c_hprintf("  πA    °¢ : %-37s  ÕA∑°ª°[∏Â¡A] : %i [%i]\n\r",IDX.subject,text_page,IDX.page);
		c_hprintf("  ∏b¨˜∑©Ø° : %2iëe %2i∂© %2i∑© %2iØ° %2i¶Ö             π°  “A : %i\n\r",IDX.year,IDX.month,IDX.day,IDX.hour,IDX.min,IDX.look);
		ReadDataFile(35); // line
}
void BbsMenu::PrintOneLine()
{
	int sec = MENU[nAcc].bSecret;
	c_hprintf("%5i %8s %8s %2i/%2i/%2i %4i/%2i  %s\n\r",
	 IDX.n,sec?"????????":IDX.id,sec?"????????":IDX.name,IDX.year-1900,IDX.month,IDX.day,IDX.look,IDX.page,IDX.subject);
}
void BbsMenu::W_()
{
		if ( !WriteAccess() ) return;
		c_hclrscr();
		ReadDataFile(30);   // Bbs Writing.
		ReadDataFile(26);   // Subject
		memset ( IDX.subject, 0, B_SCHARS+1);
		SetHanMode(true);
		c_hgetln(IDX.subject,"", B_SCHARS);
		if (!strcmp(IDX.subject,""))
		{
			ReadDataFile(34); // It is canceled
			return;
		}
		// considering when in TEXT mode...I made a new object.
		BbsData *wTMP=new BbsData( getmaxdatano()+1 );
		if ( wTMP->make() == Saved)
		{
			IDX.size = wTMP->getsize();
			SaveIdx( IDX, NewWrite);
			USER.AddPoint(BbsPoint);
			USER.stU.BbsAct++;
			SetChanges(MENUDATA[nAcc]);
			WriteLogData("‘ˇ %sµA %ldBYTE«aã°∑Å ãi∏b¨˜–q", MENU[nAcc].title, IDX.size);
		}
		else WriteLogData("‘ˇ %sµA ãi∏b¨˜ ¬·≠°", MENU[nAcc].title);
		delete wTMP;
		title_page = 1;
		SetMode(mTITLE);
		Z_();
}

void BbsMenu::NewProcess(char *CMD)
{
		if (!stricmp(CMD,"w") ) W_();
}
//------------------------------------------------------------------------
//
//               Notice Menu object.
//------------------------------------------------------------------------
NoticeMenu::NoticeMenu(char* _index) : TEXTMenu(_index, _index)
{}
void NoticeMenu::PrintFirstTitle()
{
	 if (!ReadAnsiFile("NOTICE.TIT")) ReadDataFile(140);  // Notice's number id name and so on.
}

void NoticeMenu::PrintCMD()
{
	 if (!ReadAnsiFile("NOTICE.CMD")) ReadDataFile(139);  // Notice COMMAND LINE
}

void NoticeMenu::PrintIdx()
{
		ReadDataFile(35); // line
		c_hprintf("  ¥a∑°ó° : %8s  πA°¢ : %s\n\r",MENU[nAcc].bSecret?"????????":IDX.id, IDX.subject);
		ReadDataFile(35); // line
}
void NoticeMenu::PrintOneLine()
{
	 c_hprintf("%5i %8s %2i/%2i %3i  %s\n\r",
	 IDX.n,MENU[nAcc].bSecret?"????????":IDX.id,IDX.month,IDX.day,IDX.look,IDX.subject);
}
int NoticeMenu::OtherEditProcess()
{
	 char str[2];
	 do
	 {
		  ReadDataFile(274);
		  c_hgetln(str, "P", 1);
		  if (!stricmp(str,"1"))
		  {
				char buffer[N_SCHARS+1];
				ReadDataFile(275); // before subject
				c_hprintf("%s\n\r", IDX.subject);
				ReadDataFile(142); // Subject
				SetHanMode(true);
				c_hgetln(buffer, "", N_SCHARS);
				SetHanMode(false);
				if (!strcmp(buffer,"")) ReadDataFile(34); // It is canceled
				else
				{
					 strcpy(IDX.subject, buffer);
					 SaveIdx(IDX, AfterEdit);
					 ReadDataFile(273);//subject is modified.
				}
				return 1;
		  }
		  if (!stricmp(str,"2")) return 0;
	 } while(stricmp(str,"P"));
	 return 1;
}

void NoticeMenu::W_()
{
		if ( !WriteAccess() )
		{
			ReadDataFile(138);  // only sysop can write.
			return;
		}
		c_hclrscr();
		ReadDataFile(141);   // Notice Writing.
		ReadDataFile(142);   // Subject
		memset ( IDX.subject, 0, N_SCHARS+1);
		SetHanMode(true);
		c_hgetln(IDX.subject,"", N_SCHARS);
		if (!strcmp(IDX.subject,""))
		{
			ReadDataFile(34); // It is canceled
			return;
		}
		// considering when in TEXT mode...I made a new object.
		BbsData *wTMP=new BbsData( getmaxdatano()+1 );
		if ( wTMP->make() == Saved)
		{
			IDX.size = wTMP->getsize();
			SaveIdx( IDX, NewWrite);
			USER.AddPoint(BbsPoint);
			USER.stU.BbsAct++;
			SetChanges(MENUDATA[nAcc]);

			WriteLogData("‘ˇ %sµA %ldBYTE«aã°∑Å â∑ª°¨a–w ∏b¨˜–q", MENU[nAcc].title, IDX.size);
		}
		else WriteLogData("‘ˇ %sµA â∑ª°¨a–w ∏b¨˜ ¬·≠°", MENU[nAcc].title);
		delete wTMP;
		title_page = 1;
		SetMode( mTITLE );
		Z_();
}

int NoticeMenu::WriteAccess()
{
	 if (USER.GetGrade() == SYSOP) return 1;
	 else return 0;
}
int NoticeMenu::EditAccess(int n)
{
	 return WriteAccess();
}
int NoticeMenu::DelAccess(int n)
{
	 return WriteAccess();
}
void NoticeMenu::R_()
{
	 if ( appMenuObject( Type2I(RMAIL) ) != ERR) ExitLoop = 1;
}
void NoticeMenu::PrintNoData()
{
	 ReadDataFile(143);
}

void NoticeMenu::NewProcess(char *CMD)
{
		if (!stricmp(CMD,"r") ) R_();
		if (!stricmp(CMD,"w") ) W_();
}

//------------------------------------------------------------------------
//
//       CMail Object for MailMenu Object
//
//------------------------------------------------------------------------


int CMail::FindItem(int n)
{
	  int DataNum;
	  fseek(fMIDX,0L,SEEK_SET);
	  for(DataNum=1; DataNum<=MaxItem; DataNum++)
	  {
			fread(&MIDX, sizeof(MIDX), 1, fMIDX);
			if (MIDX.MailNo==n)
			{
				 fseek(fMIDX, -long(sizeof(MIDX)), SEEK_CUR);
				 return 1;
			}
	  }
	  return 0;
}
int CMail::isUserMailNum(int n)
{
	  if (FindItem(n))
		  if (MIDX.bSaved) return 1;
	  return 0;
}
void CMail::WriteItem()
{
	  fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
}
void CMail::SetRead(int n)
{
	  if (FindItem(n))
	  {
			if (!MIDX.bRead)   // as to skip the case of double getting ReadTime.
			{
				 MIDX.bRead=1;
				 GetAllTime(&MIDX.ReadTime);
				 fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
			}
	  }
}
// return value 0 : bSaved Setting failure.
//              1 : bSaved Setting success.
int CMail::SetSaved(int n, int bSaved)
{
	  if (FindItem(n))
	  {
			if (MIDX.bSaved && bSaved) return 0;
			if (!MIDX.bSaved && !bSaved) return 0;
			if (bSaved) MIDX.bSaved=1;
			else MIDX.bSaved=0;
			fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
			return 1;
	  }
	  return 0;
}
// for check mail.
int CMail::ValidItems()
{
	  int Item, nValid=0;
	  fseek(fMIDX,0L,SEEK_SET);
	  for(Item=1; Item<=MaxItem; Item++)
	  {
			fread(&MIDX, sizeof(MIDX), 1, fMIDX);
			if (!MIDX.bRead && MIDX.bSaved) nValid++;
	  }
	  return nValid;
}

CMail::CMail(unsigned char* ID, int mode)
{
	  char modestr[4];
	  sprintf(temp_str,"%s\\MAIL\\%s.IDX",InstDir, ID);
	  if (mode==ForReadWrite)
	  {
			if ( access(temp_str,0) ) strcpy(modestr, "w+b"); //when not exists.
			else strcpy(modestr, "r+b");
	  }
	  if (mode==ForAppend) strcpy(modestr,"ab");
	  fMIDX = fopen(temp_str, modestr);
	  if (fMIDX==NULL) { halt("ERROR:Not enough memory for mail reading");}
	  long FirstFilePoint = ftell(fMIDX);
	  fseek(fMIDX,0L,SEEK_END);
	  MaxItem = ftell(fMIDX) / sizeof(MIDX);
	  fseek(fMIDX, FirstFilePoint, SEEK_SET);
}
CMail::~CMail()
{
	  fclose(fMIDX);
}
//------------------------------------------------------------------------
//
//       CMailSee Object for MailMenu Object
//
//------------------------------------------------------------------------
CMailSee::CMailSee()
{
	  fMIDX=NULL;
}
// if File handle fMIDX is open, then close it. and open again
void CMailSee::Open(int n, int mode)
{
	  char modestr[4];
	  sprintf(temp_str,"%s\\MAIL\\see%i.IDX",InstDir, n );
	  if (mode==ForReadWrite)
	  {
			if ( access(temp_str,0) ) strcpy(modestr, "w+b"); //when not exists.
			else strcpy(modestr, "r+b");
	  }
	  if (mode==ForAppend) strcpy(modestr,"ab");

	  if (fMIDX!=NULL) fclose(fMIDX);
	  fMIDX = fopen(temp_str, modestr);
	  if (fMIDX==NULL) { halt("ERROR:Not enough memory for mail reading");}

	  long FirstFilePoint = ftell(fMIDX);  // for appending mode
	  fseek(fMIDX,0L,SEEK_END);
	  MaxItem = ftell(fMIDX) / sizeof(MIDX);
	  fseek(fMIDX, FirstFilePoint, SEEK_SET);
}
int CMailSee::FindItem()
{
	  int DataNum;
	  fseek(fMIDX,0L,SEEK_SET);
	  for(DataNum=1; DataNum<=MaxItem; DataNum++)
	  {
			fread(&MIDX, sizeof(MIDX), 1, fMIDX);
			if (!strcmp(USER.stU.ID, MIDX.id))
			{
				 fseek(fMIDX, -long(sizeof(MIDX)), SEEK_CUR);
				 return 1;
			}
	  }
	  return 0;
}
void CMailSee::FindItem(int DataNum)
{
	  long FilePoint;
	  FilePoint = (long)(DataNum * sizeof(MIDX));
	  fseek(fMIDX,FilePoint,SEEK_SET);
}
void CMailSee::WriteItem()
{
	  fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
}
void CMailSee::ReadItem()
{
	  fread(&MIDX, sizeof(MIDX), 1, fMIDX);
}
void CMailSee::SetRead()
{
	  if (FindItem())
	  {
			if (!MIDX.bRead)   // as to skip the case of double getting ReadTime.
			{
				 MIDX.bRead=1;
				 GetAllTime(&MIDX.ReadTime);
				 fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
			}
	  }
}
// return value 0 : bSaved Setting failure.
//              1 : bSaved Setting success.
int CMailSee::SetSaved(int bSaved)
{
	  if (FindItem())
	  {
			if (MIDX.bSaved && bSaved) return 0;
			if (!MIDX.bSaved && !bSaved) return 0;
			if (bSaved) MIDX.bSaved=1;
			else MIDX.bSaved=0;
			fwrite(&MIDX, sizeof(MIDX), 1, fMIDX);
			return 1;
	  }
	  return 0;
}
// returns number of mails read.
int CMailSee::ValidItems()
{
	  int Item, nRead=0;
	  fseek(fMIDX,0L,SEEK_SET);
	  for(Item=1; Item<=MaxItem; Item++)
	  {
			fread(&MIDX, sizeof(MIDX), 1, fMIDX);
			if (MIDX.bRead) nRead++;
	  }
	  return nRead;
}

CMailSee::~CMailSee()
{
	  if (fMIDX) fclose(fMIDX);
}
//------------------------------------------------------------------------
//
//       MailMenu Object delived from TEXTMenu Object
//
//------------------------------------------------------------------------
MailMenu::MailMenu(char* _index) : TEXTMenu(_index, "MAIL")
{
		Mail = new CMail(USER.stU.ID, ForReadWrite);
		MailSee = new CMailSee();
		MailSendID[0]=0;
}
// for "S" and "RE" command.
MailMenu::MailMenu(char*_index, unsigned char* ID) : TEXTMenu(_index, "MAIL")
{
		Mail = new CMail(USER.stU.ID, ForReadWrite);
		MailSee = new CMailSee();
		strcpy(MailSendID, ID);
}
MailMenu::~MailMenu()
{
		delete MailSee;
		delete Mail;
}
int MailMenu::ConfirmID( unsigned char *IDs )
{
	class UserClass *MU;
	int iID,find,bConfirmed=0;
	char ID[9];
	while(*IDs)
	{
		memset(ID,0,9);
		iID=0;
		while( ( *IDs!=' ' || iID==0 ) && *IDs!=0 && iID <=7 )
		{
			 if (*IDs!=' ') ID[iID++] = *IDs;
			 ++IDs;
		}
		ID[iID]=0;
		for (find=1; find<=MaxUserNo; find++)
		{
			MU=new UserClass(find);
			MU->ReadData();
			if ( !strcmp(MU->stU.ID, ID) )
			{
				// GetGrade is not used in temp UserClass object.
				if (MU->stU.OK==0) c_hprintf("%sìe ¨a∂w∫óª°ñE ¥a∑°ó°∑≥ì°îa\n\r",ID);
				else
				{
					c_hprintf("%sì±çA Õeª°üi •°êÅâVØsì°îa.\n\r",ID);
					delete MU;
					bConfirmed=1;
					break;
				}
			}
			delete MU;
		}
		if (find == MaxUserNo+1) c_hprintf("%sìe ówù¢ñAª° ¥g∑e ¥a∑°ó°∑≥ì°îa\n\r",ID);
	}
	return bConfirmed;
}
void MailMenu::SendMail(unsigned char *IDs, int BbsNo )
{
	class UserClass* MU;
	class CMail*     NewMail;
	class CMailSee*  NewMailSee;
	char ID[9];
	int  iID,find;
	while(*IDs)
	{
		iID=0;
		memset(ID,0,9);
		while( ( *IDs!=' ' || iID==0 ) && *IDs!=0 && iID <=7 )
		{
			 if (*IDs!=' ') ID[iID++] = *IDs;
			 ++IDs;
		}
		ID[iID]=0;
		for (find=1; find<=MaxUserNo; find++)
		{
			MU=new UserClass(find);
			MU->ReadData();
			if ( !strcmp(MU->stU.ID,ID) )
			{
				// GetGrade is not used in temp UserClass object.
				if (MU->stU.OK!=0)
				{
					NewMail = new CMail(MU->stU.ID, ForAppend);
					NewMail->MIDX.MailNo = BbsNo;
					NewMail->MIDX.bRead = 0;
					NewMail->MIDX.bSaved = 1;
					NewMail->WriteItem();
					delete NewMail;

					NewMailSee = new CMailSee();
					NewMailSee->Open(BbsNo, ForAppend);
					strcpy(NewMailSee->MIDX.id, MU->stU.ID);
					strcpy(NewMailSee->MIDX.name, MU->stU.NAME);
					NewMailSee->MIDX.bRead = 0;
					NewMailSee->MIDX.bSaved = 1;
					NewMailSee->WriteItem();
					delete NewMailSee;

					c_hprintf("%sì±çA Õeª°üi •°êñØsì°îa.\n\r",ID);
					delete MU;
					break;
				}
			}
			delete MU;
		}
	}
	ReadDataFile(95); // press enter!
}
void MailMenu::DDprocess(int n)
{
	 char numstr[6];

	 itoa(n,numstr,10);
	 c_hputs(numstr);

	 if( !isBBSnum( numstr ) )
	 {
			ReadDataFile(56); // invalid number.
			return;
	 }
	 if( !Mail->isUserMailNum(n) )
	 {
			ReadDataFile(92); // You have no right to del.
			return;
	 }
	 WriteLogData("‘ˇ %i§Â Õeª° ¨bπA", n);
	 Mail->SetRead(n);
	 MailSee->Open(n, ForReadWrite);
	 MailSee->SetRead();
	 MailSee->SetSaved(0);
	 if ( Mail->SetSaved(n, 0) ) ReadDataFile(97); // deleted now..
	 else ReadDataFile(285);
}
// start is determined when re-indexing mail.
void MailMenu::W_()
{
		char MailId[ 8*MAX_MAIL_ID+1 ];

		c_hclrscr();
		ReadDataFile(87);   // Mail Writing.
		ReadDataFile(89);   //MailId
		if (MailSendID[0]==0)
		{
			memset ( MailId, 0, 8*MAX_MAIL_ID+1);
			c_hgetln(MailId,"",8*MAX_MAIL_ID);
			if (!strcmp(MailId,""))
			{
				ReadDataFile(34); // It is canceled
				return;
			}
		} else
		{
			strcpy(MailId, MailSendID);
			c_hprintf("%s\n\r",MailId);
		}
		int bConfirmed = ConfirmID( MailId );
		if (bConfirmed)
		{
			ReadDataFile(88);   // Subject
			memset ( IDX.subject, 0, M_SCHARS+1);
			SetHanMode(true);
			c_hgetln(IDX.subject,"", M_SCHARS);
			if (!strcmp(IDX.subject,""))
			{
				ReadDataFile(34); // It is canceled
				return;
			}
			// considering when in TEXT mode...I made a new object.
			BbsData *wTMP=new BbsData( getmaxdatano()+1 );
			if ( wTMP->make() == Saved)
			{
				IDX.size = wTMP->getsize();
				IDX.alive=TXTtype;     // means not deleted.
				SaveIdx( IDX, NewWrite);
				SendMail( MailId, IDX.n );
				WriteLogData("‘ˇ Õeª° •°êñ∑q");
			}
			else WriteLogData("‘ˇ Õeª° ∏b¨˜ï°∫ó ¬·≠°–q");
			delete wTMP;
		}
}
int MailMenu::OtherEditProcess()
{
	 char str[2];
	 do
	 {
		  ReadDataFile(283);
		  c_hgetln(str, "P", 1);
		  if (!stricmp(str,"1"))
		  {
				char buffer[B_SCHARS+1];
				ReadDataFile(284); // before subject
				c_hprintf("%s\n\r", IDX.subject);
				ReadDataFile(26);  // Subject
				SetHanMode(true);
				c_hgetln(buffer, "", M_SCHARS);
				SetHanMode(false);
				if (!strcmp(buffer,"")) ReadDataFile(34); // It is canceled
				else
				{
					 strcpy(IDX.subject, buffer);
					 SaveIdx(IDX, AfterEdit);
					 ReadDataFile(273);//subject is modified.
				}
				return 1;
		  }
		  if (!stricmp(str,"2")) return 0; // parent function will process.
	 } while(stricmp(str,"P"));
	 return 1;
}

//------------------------------------------------------------------------
//
//       CheckMail Object delived from BaseExec, MailMenu Object
//
//------------------------------------------------------------------------

CheckMail::CheckMail() : MailMenu("000000")
{}
void CheckMail::run()
{
		// After execution of hostinit, CheckMail::run() is excuted.
		int mailnum, openmailnum;
		if (Type2I(OMAIL)!=ERR) openmailnum = MENUDATA[Type2I(OMAIL)].newdata;
		else openmailnum = -1;
		ReadDataFile(99); // I'm reading mail idx.
		mailnum = Mail->ValidItems();
		if ( mailnum !=0 ) c_hprintf("%i…∑∑Å Õeª°àa ï°¿b–Å ∑∂Øsì°îa.\n\r",mailnum);
		else if (openmailnum > 0) c_hprintf("%i…∑∑Å â∑àÅÕeª°(go %s)àa ï°¿b–Å ∑∂Øsì°îa.\n\r", openmailnum, MENU[Type2I(OMAIL)].go);
		else ReadDataFile(100); // No mail.
		ReadDataFile(95); // press enter key;
}
//------------------------------------------------------------------------
//
//       WMailMenu Object delived from BaseExec, MailMenu Object
//
//------------------------------------------------------------------------

WMailMenu::WMailMenu(char* _index) : MailMenu(_index)
{}
WMailMenu::WMailMenu(char* _index, unsigned char* ID) : MailMenu(_index, ID)
{}
void WMailMenu::run()
{
	 W_();
	 if (MailSendID[0]==0) P_(); //when not "S" or "RE" command
}

//------------------------------------------------------------------------
//
//       RMailMenu Object delived from MailMenu Object
//
//------------------------------------------------------------------------
RMailMenu::RMailMenu(char *_index) : MailMenu(_index)
{}
void RMailMenu::PrintNoData()
{
	 ReadDataFile(93);
}
int RMailMenu::ReadAccess(int n)
{
	 //MenuIndex_t toSEE;
	 //LoadIdx(toSEE, n);
	 if (Mail->isUserMailNum(n))
		 if (!Mail->MIDX.bRead) return 1;
	 return 0;
}
// in TEXTMenu class, DelAccess means setting IDX.alive to zero.
// in RMailMenu class, DelAccess means deleting USER's id in the mdi file.
// it is included in MailMenu::DDprocess
int RMailMenu::DelAccess(int n)
{
	 return 0;
}
void RMailMenu::PrintFirstTitle()
{
	 if (!ReadAnsiFile("MAIL.TIT")) ReadDataFile(90);  // Mail's number id name and so on.
}

void RMailMenu::PrintCMD()
{
	 if (!ReadAnsiFile("MAIL.CMD") ) ReadDataFile(91);  // BBS COMMAND LINE
}

void RMailMenu::PrintIdx()
{
		float fsize;
		char pchar;
		ConvertSize(fsize, pchar);
		ReadDataFile(35); // line
		c_hprintf("  •°êÖ∑° : %8s(%8s)                   §Â  —°[∏Â¡A] : %i [%i]\n\r",IDX.name,IDX.id,IDX.n,start);
                c_hprintf("  πA°¢   : %-35s  «a  ã°[—w»Å] : %-6.1f%c[%s]\n\r",IDX.subject,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN");
		c_hprintf("  §i≠∑Ø°àb : %2iëe %2i∂© %2i∑© %2iØ° %2i¶Ö         ÕA∑°ª°[∏Â¡A] : %i [%i]\n\r",IDX.year,IDX.month,IDX.day,IDX.hour,IDX.min,text_page,IDX.page);
		ReadDataFile(35); // line
}
void RMailMenu::MailSaveOrDelete()
{
		char str[2];
		Mail->SetRead(IDX.n);   // save ReadTime and set bRead flag to 1
		MailSee->Open(IDX.n, ForReadWrite);
		MailSee->SetRead();
		while(1)
		{
			 ReadDataFile(286);
			 c_hgetln(str, "1", 1);
			 if (!strcmp(str,"1")) // Save mail
			 {
					MailSee->SetSaved(1);
					if( Mail->SetSaved(IDX.n, 1) ) ReadDataFile(287);
					break;
			 }
			 if (!strcmp(str,"2")) // Delete mail
			 {
					MailSee->SetSaved(0);
					if( Mail->SetSaved(IDX.n, 0) ) ReadDataFile(288);
					break;
			 }
		}
}
void RMailMenu::P_()
{
	 if (mode == mTEXT) MailSaveOrDelete();
	 TEXTMenu::P_();
}
void RMailMenu::PrintOneLine()
{
	 float fsize;
	 char pchar;
	 ConvertSize(fsize, pchar);
	 c_hprintf("%5i %8s %8s %2i/%2i %6.1f%c %s  %s\n\r",
	 IDX.n,IDX.id,IDX.name,IDX.month,IDX.day,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN",IDX.subject);
}
void RMailMenu::NewProcess(char *CMD)
{
	 if (!stricmp(CMD,"w") ) W_();
}
RMailMenu::~RMailMenu()
{
	 if (mode == mTEXT) MailSaveOrDelete();
}
//------------------------------------------------------------------------
//
//       MSee Object delived from MailMenu Object
//
//------------------------------------------------------------------------
MSee::MSee(char *_index) : MailMenu(_index)
{}
void MSee::PrintNoData()
{
	 ReadDataFile(292);  // there is no sended mail.
}

int MSee::ReadAccess(int n)
{
	 MenuIndex_t toSEE;
	 LoadIdx(toSEE, n);
	 if (!strcmp(USER.stU.ID, toSEE.id)) return 1;
	 return 0;
}
// in TEXTMenu class, DelAccess means setting IDX.alive to zero.
// in MSee class, DelAccess means deleting USER's id in the mdi file.
// it is included in MailMenu::DDprocess
int MSee::DelAccess(int n)
{
	 return ReadAccess(n);
}
void MSee::PrintFirstTitle()
{
	 if (!ReadAnsiFile("MSEE.TIT")) ReadDataFile(294);  // Mail's number id name and so on.
}

void MSee::PrintCMD()
{
	 if (!ReadAnsiFile("MSEE.CMD") ) ReadDataFile(91);  // BBS COMMAND LINE
}

void MSee::PrintIdx()
{
	 float fsize;
	 char pchar;
	 MailSee->Open(IDX.n, ForReadWrite);
	 ConvertSize(fsize, pchar);
	 ReadDataFile(35); // line
	 c_hprintf("  ÆÅØ•∏a : %3i/%3i                              §Â  —°[∏Â¡A] : %i [%i]\n\r",MailSee->ValidItems(),MailSee->MaxItem,IDX.n,start);
	 c_hprintf("  πA°¢   : %-35s  «a  ã°[—w»Å] : %-6.1f%c[%s]\n\r",IDX.subject,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN");
	 c_hprintf("  §i≠∑Ø°àb : %2iëe %2i∂© %2i∑© %2iØ° %2i¶Ö         ÕA∑°ª°[∏Â¡A] : %i [%i]\n\r",IDX.year,IDX.month,IDX.day,IDX.hour,IDX.min,text_page,IDX.page);
	 ReadDataFile(35); // line
}
void MSee::PrintOneLine()
{
	 float fsize;
	 char pchar;
	 MailSee->Open(IDX.n, ForReadWrite);
	 ConvertSize(fsize, pchar);
	 c_hprintf("%5i %3i/%3i   %2i/%2i/%2i %6.1f%c %s  %s\n\r",
	 IDX.n,MailSee->ValidItems(),MailSee->MaxItem,IDX.year-1900,IDX.month,IDX.day,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN",IDX.subject);
}
//StartItem, and page starts from 1
//when Mail is written, bSaved is true, bRead is false
void MSee::PrintMailSee(int page)
{
	 int Item=0, StartItem, EndItem;
	 char status[9];
	 MailSee->Open(IDX.n, ForReadWrite);
	 allpage = MailSee->MaxItem/L_TEXT+1;
	 if (MailSee->MaxItem%L_TEXT == 0) allpage--;
	 StartItem = (page-1)*L_TEXT+1;
	 EndItem = StartItem + L_TEXT-1;
	 if (EndItem > MailSee->MaxItem) EndItem = MailSee->MaxItem;
	 MailSee->FindItem(StartItem-1);
	 ReadDataFile(293);
	 for (Item=StartItem; Item<=EndItem; Item++)
	 {
		  MailSee->ReadItem();
		  if (MailSee->MIDX.bRead) strcpy(status, "  ∑™¥ˆ∑q");
		  else if (!MailSee->MIDX.bSaved) strcpy(status, "••∑•¨bπA");
				 else strcpy(status, "¥e∑™¥ˆ∑q");

		  if (MailSee->MIDX.bRead) c_hprintf("       %8s %8s  %8s  %2i/%2i/%2i %2i:%2i\n\r", MailSee->MIDX.id, MailSee->MIDX.name, status, MailSee->MIDX.ReadTime.year-1900, MailSee->MIDX.ReadTime.month, MailSee->MIDX.ReadTime.day, MailSee->MIDX.ReadTime.hour, MailSee->MIDX.ReadTime.min);
		  else c_hprintf("       %8s %8s  %8s\n\r", MailSee->MIDX.id, MailSee->MIDX.name, status);
	 }
}
void MSee::PrintData(int num, int page)
{
		if (first==1)   // not to make bug, I did not deleted first==1 routine.
		{
				first=0;
				SetMode(mTEXT); // deleting before TEXT routine is here.
				TEXT = new BbsData(num);
				if ( LoadIdx(IDX, num) == CANCEL )
				{
					  delete TEXT;
					  mode = mTITLE;
					  return;
				}
				TEXT->LoadData();
				/* this routine is the real routine of MailSee*/
		}
		c_hclrscr();
		PrintIdx();
		PrintMailSee(page);
		PrintLastTitle(page!=1, page < allpage );
		// TEXT is deleted when "P" order is processed.
}
void MSee::NewProcess(char *CMD)
{
	 if (!stricmp(CMD,"w") ) W_();
}

//------------------------------------------------------------------------
//
//       MBox Object delived from MailMenu Object
//
//------------------------------------------------------------------------
MBox::MBox(char *_index) : MailMenu(_index)
{}
void MBox::PrintNoData()
{
	 ReadDataFile(291);
}

int MBox::ReadAccess(int n)
{
	 if (Mail->isUserMailNum(n)) // isUserMailNum returns true if bSaved is true.
		 if (Mail->MIDX.bRead) return 1;
	 return 0;
}
// in TEXTMenu class, DelAccess means setting IDX.alive to zero.
// in MBox class, DelAccess means deleting USER's id in the mdi file.
// it is included in MailMenu::DDprocess
int MBox::DelAccess(int n)
{
	 return 0;
}
void MBox::PrintFirstTitle()
{
	 if (!ReadAnsiFile("MBOX.TIT")) ReadDataFile(90);  // Mail's number id name and so on.
}
void MBox::PrintCMD()
{
	 if (!ReadAnsiFile("MBOX.CMD") ) ReadDataFile(91);  // BBS COMMAND LINE
}

void MBox::PrintIdx()
{
		float fsize;
		char pchar;
		ConvertSize(fsize, pchar);
		ReadDataFile(35); // line
		c_hprintf("  •°êÖ∑° : %8s(%8s)                   §Â  —°[∏Â¡A] : %i [%i]\n\r",IDX.name,IDX.id,IDX.n,start);
		c_hprintf("  πA°¢ : %-35s  «a  ã°[—w»Å] : %-6.1f%c[%s]\n\r",IDX.subject,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN");
		c_hprintf("  §i≠∑Ø°àb : %2iëe %2i∂© %2i∑© %2iØ° %2i¶Ö         ÕA∑°ª°[∏Â¡A] : %i [%i]\n\r",IDX.year,IDX.month,IDX.day,IDX.hour,IDX.min,text_page,IDX.page);
		ReadDataFile(35); // line
}
void MBox::PrintOneLine()
{
	 float fsize;
	 char pchar;
	 ConvertSize(fsize, pchar);
	 c_hprintf("%5i %8s %8s %2i/%2i %6.1f%c %s  %s\n\r",
	 IDX.n,IDX.id,IDX.name,IDX.month,IDX.day,fsize,pchar,(IDX.alive==TXTtype)?"TXT":"BIN",IDX.subject);
}
void MBox::NewProcess(char *CMD)
{
	 if (!stricmp(CMD,"w") ) W_();
}
//------------------------------------------------------------------------
//
//       PdsMenu Object delived from TEXTMenu Object
//
//------------------------------------------------------------------------

DnPdsMenu::DnPdsMenu(char *_index) : TEXTMenu(_index, _index)
{}
void DnPdsMenu::PrintNoData()
{
	 ReadDataFile(94);
}
void DnPdsMenu::PrintFirstTitle()
{
	 if (!ReadAnsiFile("PDS.TIT")) ReadDataFile(61);
}
void DnPdsMenu::PrintCMD()
{
	 if (!ReadAnsiFile("PDS.CMD")) ReadDataFile(10);  // PDS COMMAND LINE
}

void DnPdsMenu::PrintIdx()
{
		float filesize;
		char postchar;
		ConvertSize(filesize,postchar);
		ReadDataFile(35); // line  //DEBUG change getstart() to getalivedatum()
		int sec = MENU[nAcc].bSecret;
		c_hprintf("  µ©ü•¨aúq : %8s(%8s)  §Â—°[∏Â¡A] : %i [%i]   ÕA∑°ª°[∏Â¡A] : %i [%i]\n\r",sec?"????????":IDX.name,sec?"????????":IDX.id,IDX.n,start,text_page,IDX.page);
		c_hprintf("  πA    °¢ : %-32sπ°“A : %i      îa∂Öù°óa : %i\n\r",IDX.subject,IDX.look,IDX.down);
		c_hprintf("  µ© ü• êi : %iëe %2i∂© %2i∑© %2iØ°%2i¶Ö     —¡ ∑© : %s [ %6.1f%c ]\n\r",IDX.year,IDX.month,IDX.day,IDX.hour,IDX.min,IDX.FileName,filesize,postchar);
		ReadDataFile(35); // line
}
void DnPdsMenu::PrintOneLine()
{
	float filesize;
	char postchar;
	ConvertSize(filesize,postchar);
	int sec = MENU[nAcc].bSecret;
	c_hprintf("%5i %8s %12s %6.1f%c %4i/%4i  %s\n\r",
		IDX.n,sec?"????????":IDX.id,IDX.FileName,filesize,postchar,IDX.down,IDX.look,IDX.subject);
}
int DnPdsMenu::OtherEditProcess()
{
	 char str[2];
	 do
	 {
		  ReadDataFile(276);
		  c_hgetln(str, "P", 1);
		  if (!stricmp(str,"1"))
		  {
				char buffer[P_SCHARS+1];
				ReadDataFile(277); // before subject
				c_hprintf("%s\n\r", IDX.subject);
				ReadDataFile(63);   // Subject
				SetHanMode(true);
				c_hgetln(buffer, "", P_SCHARS);
				SetHanMode(false);
				if (!strcmp(buffer,"")) ReadDataFile(34); // It is canceled
				else
				{
					 strcpy(IDX.subject, buffer);
					 SaveIdx(IDX, AfterEdit);
					 ReadDataFile(273);//subject is modified.
				}
				return 1;
		  }
		  if (!stricmp(str,"2")) return 0;
	 } while(stricmp(str,"P"));
	 return 1;
}

void DnPdsMenu::SaveRdn(struct MenuIndex_t& BI)
{
	 int item; struct MenuIndex_t tIdx;
	 if (aliveUSER==0) halt("ERROR:happened Saving Rdn");
	 FILE* fRDN;
	 if ( USER.RDNfiles > 0 )
	 {
		 fRDN=fopen(strcat2(InstDir,"\\TEMP\\RDN.DAT"),"rb");
		 if (fRDN==NULL) halt("ERROR : Not enough memory - while checking rdn data");
		 fseek( fRDN, 0L, SEEK_SET);
		 // before this function, ++(USER->RDNfiles) must NOT be excuted.
		 for ( item=1; item <= USER.RDNfiles; item++)
		 {
			 fread(&tIdx, sizeof(tIdx), 1, fRDN);
			 if (!strcmp(tIdx.FileName, BI.FileName))
			 {
				 ReadDataFile(77);
				 fclose(fRDN);
				 return;
			 }
		 }
		 fclose(fRDN);
	 }
	 fRDN=fopen(strcat2(InstDir,"\\TEMP\\RDN.DAT"),"a+b");
	 if (fRDN==NULL) halt("ERROR : Not enough memory - while saving rdn data");
	 fwrite(&BI, sizeof(BI), 1, fRDN);
	 fclose(fRDN);
	 ReadDataFile(80); // resistered.
}
void DnPdsMenu::DNprocess(int n)
{
	 char numstr[6],path_fname[100],pathfilename[13];
	 struct MenuIndex_t toDN;

	 itoa(n,numstr,10);
	 c_hputs(numstr);
	 if( !isBBSnum( numstr ) )
	 {
		 ReadDataFile(56); // invalid number.
		 return;
	 }

	 LoadIdx( toDN , n );

	 if ( toDN.size/1024 > USER.stU.DnableSize )
	 {
		 ReadDataFile(82); // not enough download size
		 return;
	 }
	 else ReadDataFile(85);

	 /*pathdata file open and write path on it*/
		itoa(toDN.n,pathfilename,10);
		strcat(pathfilename,".P_T");
		memset(path_fname,0,100);
		// current path is InstDir\\path
		if(!access(pathfilename,0))
		{
			FILE* fDataPath=fopen(pathfilename,"rt");
			getString(fDataPath, path_fname, '\n');
			fclose(fDataPath);
			strcat(path_fname, toDN.FileName);
		}
		else strcpy(path_fname, toDN.FileName);
		sFILE.Push(path_fname);
		if (SuccDnLoad)
		{
			  if (ExecuteProtocol(nProto,mDOWNLOAD)!=0) ReadDataFile(84); //not success
			  else
			  {
					ReadDataFile(83); // success
					USER.stU.DnDataSize += toDN.size/1024;
					USER.stU.DnableSize -= toDN.size/1024;
					WriteLogData("‘ˇ %s∑Å %i§Â ∏aûa îa∂Öù°óa ¨˜â∑", MENU[nAcc].title, toDN.n);
					toDN.down++;
					SaveIdx( toDN, OnceRead );
			  }
		}
}

void DnPdsMenu::DN_(int no, char param[maxPARAM][lenPARAM])
{
	 struct MenuIndex_t toDN;
	 unsigned long allsize=0;
	 unsigned NeedTime;
	 int i=0,j;

	 //if (bLocal==1) { ReadDataFile(75); return; }

	 if (mode == mTEXT && no==1)
	 {
			 no=2;
			 itoa(IDX.n, param[1], 10);
	 }

	 if( no >= 2 )
	 {
		  if (!GoOnWithSelectedNum(no,param,79,0,MAX_DN_NUM)) return;

		  while( ++i<no )
		  {
			  if (  (i<=no-3) && (atoi(param[i])!=0) &&
					!strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
			  {
					for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
					{
						LoadIdx(toDN, j);
						allsize+=toDN.size;
					}
					i+=2;
			  }
			  else
			  {

					LoadIdx(toDN, atoi(param[i]));
					allsize+=toDN.size;
			  }
		  }
		  //USER->stU.DnableSize = 1000;
		  //c_hprintf("œ©∂a–e îa∂Ö àaìwú∑ : %i(KB)   —e∏Å îa∂Ö àaìwú∑ : %i(KB)\n\r",
		  //				 allsize/1024, USER->stU.DnableSize );
		  //USER->stU.DnableSize = 1000;
		  if ( allsize/1024 > USER.stU.DnableSize && USER.GetGrade() != SYSOP )
		  {
				ReadDataFile(82);
				return;
		  }
		  NeedTime = allsize/SPEED*9/60;
		  c_hprintf("∏Â≠∑ µÅ¨w Ø°àe : %u¶Ö   —e∏Å êq∑e Ø°àe : %i¶Ö\n\r", NeedTime, USER.stU.LeftTime);
		  if (  NeedTime > USER.stU.LeftTime  )
		  {
				 ReadDataFile(163);
				 return;
		  }
		  if (SuccDnLoad)
			  if ( SelectProtocol(nProto) == CANCEL )
			  {
				  ReadDataFile(34); // It is canceled
				  sFILE.clearstack();
				  return;
			  }
		  sFILE.clearstack();
		  i=0;
		  while( ++i<no )
		  {
			  if (  (i<=no-3) && (atoi(param[i])!=0) &&
					!strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
			  {
					for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
						 DNprocess(j);
					i+=2;
			  }
			  else  DNprocess( atoi(param[i]) );
		  }
	 }
	 if ( !SuccDnLoad && ( no>=2 || mode == mTEXT ) && !sFILE.Empty() )
	 {
		  if ( SelectProtocol(nProto) == CANCEL )
		  {
			  ReadDataFile(34); // It is canceled
			  sFILE.clearstack();
			  return;
		  }
		  if (ExecuteProtocol(nProto,mDOWNLOAD)!=0) ReadDataFile(84); //not success
		  else
		  {
			  ReadDataFile(83); // success
			  USER.stU.DnDataSize += allsize/1024;
			  USER.stU.DnableSize -= allsize/1024;
			  WriteLogData("‘ˇ %s∑Å %i§Â ∏aûa îa∂Öù°óa ¨˜â∑", MENU[nAcc].title, IDX.n);
			  if (mode==mTEXT) OnceDownLoaded(IDX.n);
			  else
			  {
					 i=0;
					 while( ++i<no )
					 {
						 if (  (i<=no-3) && (atoi(param[i])!=0) &&
							  !strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
						 {
							  for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
									OnceDownLoaded(j);
							  i+=2;
						 }
						 else  OnceDownLoaded( atoi(param[i]) );
					 }
			  }
		  }
	 }
}
void DnPdsMenu::OnceDownLoaded(int n)
{
	 struct MenuIndex_t toDN;
	 LoadIdx(toDN,n);
	 toDN.down++;
	 SaveIdx(toDN, OnceRead);
}
void DnPdsMenu::RDNprocess(int n)
{
	 char numstr[6];
	 struct MenuIndex_t toRESISTER;
	 itoa(n,numstr,10);

	 c_hputs(numstr);
	 if( !isBBSnum( numstr ) )
	 {
			ReadDataFile(56); // invalid number.
			return;
	 }

	 if ( USER.RDNfiles >= MAX_DN_NUM )
	 {
			c_hprintf("§Â∑e ¬AîÅ RDN∏aûaÆÅ %iàÅ ¡°â¡ù° ∑•–Å ówù¢ñAª° ¥g¥vØsì°îa.\n",MAX_DN_NUM );
			return;
	 }
	 LoadIdx( toRESISTER , n );
	 SaveRdn( toRESISTER ); //Append to "RDN.TMP" of TEMP directory.
	 ++(USER.RDNfiles);
}

void DnPdsMenu::RDN_(int no, char param[maxPARAM][lenPARAM])
{
	 int i=0,j;
	 if( no >= 2 )
	 {
		  if (!GoOnWithSelectedNum(no,param,76,78,MAX_SEL_ITEM)) return;
		  while( ++i<no )
		  {
			  if (  (i<=no-3) && (atoi(param[i])!=0) &&
					!strcmp(param[i+1],"-") && (atoi(param[i+2])!=0)    )
			  {
					for(j=atoi(param[i]); j<=atoi(param[i+2]); j++)
						 RDNprocess(j);
					i+=2;
			  }
			  else  RDNprocess( atoi(param[i]) );
		  }
	 }
	 else
	 if (mode == mTEXT)
	 {
		  ReadDataFile(81);// resistering now seeing data onto temp.
		  ReadDataFile(78);// Will you really resister?? [y/n]
		  if ( AnswerIs('N','N',false ) ) return; // ans is not Y , y
		  RDNprocess( IDX.n );
	 }
}
void DnPdsMenu::NewProcess(char *CMD)
{
		int no;
		char param[maxPARAM][lenPARAM];
		MakeParam( CMD, no, param );
		// REGISTER VERSION DETERMINE ROUTINE..
		if (!stricmp(param[0],"rdn") ) RDN_(no, param);
		if (!stricmp(param[0],"dn") ) DN_(no, param);
		if (!stricmp(param[0],"up") ) W_();
}

//--------------------------------------------------------------------------
//              PdsMenu Class delived from DnPdsMenu                      //
//--------------------------------------------------------------------------
PdsMenu::PdsMenu(char *_index) : DnPdsMenu(_index)
{}
void PdsMenu::W_()
{
		int ret;
		int bFileExist;
		char path[100],pathfilename[13];

		if ( !WriteAccess() ) return;

		c_hclrscr();
		ReadDataFile(62);   // Pds Writing.
		ReadDataFile(63);   // Subject
		memset ( IDX.subject, 0, P_SCHARS+1);
		SetHanMode(true);
		c_hgetln(IDX.subject,"", P_SCHARS);
		if (!strcmp(IDX.subject,""))
		{
			ReadDataFile(34); // It is canceled
			return;
		}

		if (bLocal==1)
		{
			ReadDataFile(64);   // filename
			CFileSelector *FSEL=new CFileSelector(160,100, 7, 1, 5);//uses PathBuffer
			ret = FSEL->SelectFile(path,IDX.FileName,IDX.size);
			delete FSEL;

			if (ret==CANCEL)
			{
				 ReadDataFile(34);
				 return;
			}
			else hprintf("%s\n\r",IDX.FileName);
		}
		else
		{
			do
			{
				 ReadDataFile(64);   // filename
				 memset ( IDX.FileName, 0, 13);
				 c_hgetln(IDX.FileName,"", 12);
				 if (!stricmp(IDX.FileName,"Q"))
				 {
					 ReadDataFile(34); // It is canceled
					 return;
				 }
				 if (bFileExist=FileExist()) ReadDataFile(193);  // file exist.
			} while ( bFileExist );
			if ( SelectProtocol(nProto) == CANCEL )
			{
				WriteLogData("‘ˇ %sµA ¥Ûù°óa ï°∫óµA œaù°…°≈© â°üaã°µA¨· ¬·≠°", MENU[nAcc].title);
				ReadDataFile(34); // It is canceled
				return;
			}
			if (ExecuteProtocol(nProto,mUPLOAD)!=0)
			{
				WriteLogData("‘ˇ %sµA ¥Ûù°óa ï°∫óµA œaù°…°≈© Ø©–ó–aîaàa ¬·≠°", MENU[nAcc].title);
				return;
			}
			if (CalculateFileSize()==ERR)
			{
				do
				{
					ReadDataFile(64);   // filename
					memset ( IDX.FileName, 0, 13);
					c_hgetln(IDX.FileName,"", 12);
				} while( strcmp(IDX.FileName,"") && CalculateFileSize() == ERR);
				if ( !stricmp(IDX.FileName, "Q") )
				{
					WriteLogData("‘ˇ %sµA ¥Ûù°óa“Å —¡∑©∑° π•∏Å–aª° ¥g¥a¨· ¬·≠°", MENU[nAcc].title);
					return;
				}
			}
		}
		// considering when in TEXT mode...I made a new object.
		BbsData* wTMP= new BbsData( getmaxdatano()+1 );
		if ( wTMP->make() == Saved )
		{
			if (IDX.size/1024 < MinPdsSize )
			{
					c_hprintf("%sµA¨·ìe %i(KB)∑°¨w∑Å ∏aûa†e∑i ówù¢–Å ∫ìì°îa.\n\r");
					c_hprintf("∏aûaówù¢∑° ¬·≠°ñA¥ˆØsì°îa.\n\r");
			}
			else
			{
					SaveIdx( IDX, NewWrite);
					USER.AddPoint(UpPoint);
					USER.stU.PdsAct++;
					USER.stU.UpDataSize += IDX.size/1024;
					USER.stU.DnableSize += IDX.size/1024*UpSizeRate;
					SetChanges(MENUDATA[nAcc]);
					WriteLogData("‘ˇ %sµA %ldBYTE«aã°∑Å ∏aûa ¥Ûù°óa ¨˜â∑", MENU[nAcc].title, IDX.size);
					if (bLocal==1)
					{
					/*pathdata file open and write path on it*/
						itoa(IDX.n,pathfilename,10);
						strcat(pathfilename,".P_T");
						FILE* fPdsPath=fopen(pathfilename,"wt");
						fprintf(fPdsPath,"%s\n",path);
						fclose(fPdsPath);
					}
			}
		}
		delete wTMP;
		title_page = 1;
		SetMode( mTITLE );
		Z_();
}
int PdsMenu::FileExist()
{
	 int bFound=0;
	 struct ffblk filetype;
	 findfirst(strcat2(DownDir,"\\*.*"),&filetype,0);
	 while( findnext(&filetype) != -1)
	 {
		 if ( !stricmp(IDX.FileName,filetype.ff_name) )
		 {
			 bFound=1;
			 break;
		 }
	 }
	 return bFound;
}
void PdsMenu::NewProcess(char *CMD)
{
		int no;
		char param[maxPARAM][lenPARAM];
		MakeParam( CMD, no, param );
		// REGISTER VERSION DETERMINE ROUTINE..
		if (!stricmp(param[0],"rdn") ) RDN_(no, param);
		if (!stricmp(param[0],"dn") ) DN_(no, param);
		if (!stricmp(param[0],"up") ) W_();
}
//--------------------------------------------------------------------------
//              Chat Class Member functions declalaion.                 //
//--------------------------------------------------------------------------
Chat::Chat(char *_index) : BaseExec()
{
		strcpy(index,_index);
		strcpy( SysName, "∂Öµw∏a");
		strcpy( UserName, USER.stU.ID);
}
void Chat::ScreenInit()
{
		c_hclrscr();
		if (ReadAnsiFile(strcat2(MENU[nAcc].ansifile,"CHATIN.MSG"))) ReadDataFile(44);
}
Chat::~Chat()
{
		c_hclrscr();
}
void Chat::CallSysop()
{
	 struct time nowtime;
	 unsigned char oldsec=-1;
	 int count = 10;
	 c_hclrscr();
	 if (!ReadAnsiFile("JOINCHAT.MSG")) ReadDataFile(162); // calling sysop.
	 while(count > 0)
	 {
		  gettime( &nowtime );
		  if ( oldsec != nowtime.ti_sec )
		  {
				oldsec = nowtime.ti_sec;
				count--;
				c_hprintf("%i ",count);
				if (bSound)
				{
					 sound(700);
					 delay(200);
					 nosound();
				}
		  }
		  if (kbhit())
		  {
				getch();
				return;
		  }
	 }
	 if (!ReadAnsiFile("NOCHAT.MSG")) ReadDataFile(161); // calling failed.
	 WriteLogData("‘ˇ ∂Öµw∏aµ¡ ¿ÅÀ∑ ∂a¿˜");
	 ExitLoop = 1;
}
void Chat::run()
{
	 int no;
	 char param[maxPARAM][lenPARAM];
	 char chatstring[201];
	 ExitLoop=0;
	 if (existSysop) CallSysop();
	 else
	 {
			if (!ReadAnsiFile("NOCHAT.MSG")) ReadDataFile(161);
			WriteLogData("‘ˇ ∂Öµw∏aµ¡ ¿ÅÀ∑ ∂a¿˜");
			ExitLoop = 1;
	 }
	 if (!ExitLoop)
	 {
			ScreenInit();
			WriteLogData("‘ˇ ∂Öµw∏aµ¡ ¿ÅÀ∑ Ø°∏b–q");
	 }
	 bChatting=1;
	 while(!ExitLoop)
	 {
			if (u_idx!=1) SioPuts(port, UserStr);
			if (s_idx!=1) hputs(SysopStr);
			c_hgetln(chatstring, "/Q", 200);

			if (bUserStringActive)
			{
				if (s_idx!=1) c_hputs("\n\r");
				else SioPuts(port, "\n\r");
			}
			else if (!bChatMode)
				  {
					  if (u_idx!=1) c_hputs("\n\r");
					  else hputs("\n\r");
				  }
				  else if (u_idx!=1) SioPuts(port, "\n\r");

			MakeParam( chatstring, no, param );
			if ( (!strcmp(param[0],"/nick") || !strcmp(param[0],"/NICK") ||
				  !strcmp(param[0],"/al") || !strcmp(param[0],"/AL")   ) && (no>=2) )
			{
				if ( strlen(param[1]) > 8 )
					  ReadDataFile(60); // too large..
				else
				{
					if (bUserStringActive) strcpy(UserName, param[1]);
					else strcpy( SysName, param[1]);
					c_hprintf( "•i°w∑i %sù° §aéìì°îa\n\r",param[1]);
				}
			}
			else if ( !strcmp(chatstring,"/h") || !strcmp(chatstring,"/H") )
			{
				  if(!ReadAnsiFile("CHAT.HLP")) ReadDataFile(43); // Help message
			}
			else
			{
				  if (bUserStringActive) c_hprintf("[%s] %s\n\r",UserName, chatstring);
				  else c_hprintf("[%s] %s\n\r",SysName, chatstring);
				  if ( !strcmp(chatstring,"/q") || !strcmp(chatstring,"/Q") ) break;
			}
	 }
	 bChatting=0;
	 WriteLogData("‘ˇ ∂Öµw∏aµ¡ ¿ÅÀ∑ è{êë");
	 P_();
}
//--------------------------------------------------------------------------
//              JoinIn Class Member functions declalaion.                 //
//--------------------------------------------------------------------------

JoinIn::JoinIn(char *_index) : BaseExec()
{
		strcpy(index, _index);
}

//  title :  ∑≥ùb œ©óa∑Å πA°¢
//  str   :  ∑≥ùbàt∑° ∏·∏wñI ØaÀaü∑
//  max   :  ¬Aâ° ∑≥ùb àaìw ¢Ö∏aÆÅ
//  min   :  ¬A∏· ã°••∑aù° ∑≥ùb–Å¥° –aìe ¢Ö∏aÆÅ  (µw¢Öîe∂·)
//  hanmode :  do not change if hanmode is 100
//  mode  :  0 ∑°°e "—¬Ø©–sì°åa?<Y/N>"üi  ¢â¥·•°ª° ¥gìeîa.
//           -1 when pass inputing.
JoinIn::InputField(unsigned char *title,unsigned char *str,int max, int min, int hanmode,int mode)
{
	unsigned char t_str[6];
	int i,issure=0;
	do {
				for (i=0; i<max+1; i++) str[i]=0;
				c_hputch(CR);
				c_hputch(LF);

				if (hanmode != 100) SetHanMode(hanmode); // hanmode==10  --> do not convert mode

				c_hputs(title);  c_hputs(" : ");
				for (i=1; i<=max; i++) c_hputch('_');
				c_hputs(" (µw¢Öîe∂· ");
				itoa(max,t_str,10);
				c_hputs(t_str);
				c_hputs("(∏a)");
				c_hputch(CR);
				c_hputs(title); c_hputs(" : ");
				if (mode!=-1) c_hgetln(str,"",max);
				else
				{
					bPassInput=1;
					c_hgetln(str, "", max);
					bPassInput=0;
				}
				// ¨ is cancel value of password.
				if ( (str[0]=='\0' && min !=0) || !strcmp(str,"¨") )
				{
						c_hputch(CR);
						c_hputs(title); c_hputs(" : ");
						for (i=0; i<max; i++)
						{
							 if ( str[i]==0 ) c_hputch('_');
							 else c_hputch(str[i]);
						}
						c_hputch(' ');
						_hangulmode = false;
						if (!bLocal) SioPuts(port,"[?85l");
						c_hputs("°°ñÅ¬·≠°–iåa∂a?");

						if ( AnswerIs('Y','Y',true) )
						{  issure = 1;  return CANCEL;}
				}
				else if (strlen(str) <min)
				{
						c_hputch(CR);
						c_hputch(LF);
						c_hputs(title);
						c_hputs("ìe µw¢Öîe∂·ù° ");
						itoa(min,t_str,10);
						c_hputs(t_str);
						c_hputs("∏a ∑°¨w∑°¥·¥° –sì°îa");
				}
				else if ( mode == 0 || mode == -1 ) issure = 1;
				else
				{
						c_hputch('\r');
						c_hputs(title); c_hputs(" : ");
						for (i=0; i<max; i++)
						{
							 if ( str[i]==0 ) c_hputch('_');
							 else c_hputch(str[i]);
						}
						c_hputch(' ');
						c_hputs("—¬Ø©–sì°åa?");

						if ( AnswerIs('Y','Y',true ))  issure = 1;
				}
		 }  while ( !issure );
		 return NOERR;
}

int JoinIn::UsingID()
{
	  UserClass* cU;
	  int exist=0;
	  for (int nU=1; nU<=MaxUserNo; nU++)
	  {
			 cU=new UserClass(nU);
			 cU->ReadData();
			 if (!strcmp(joinU.ID, cU->stU.ID)) exist=1;
			 delete cU;
			 if (exist) return 1;
	  }
	  return 0;
}
int JoinIn::ExistSpecialLetter(char* str)
{
	  char except[]= " !@#$%^&*()<>,.?/;:\"'|\\{}[]-+=`~";
	  for(int index1=0; str[index1] != NULL; index1++)
	  {
			 for (int index2=0; except[index2] != NULL; index2++)
			 {
				  if (str[index1] == except[index2]) return 1;
			 }
	  }
	  return 0;
}
int JoinIn::UsingPeopleNo()
{
	  UserClass* cU;
	  int exist=0;
	  for (int nU=1; nU<=MaxUserNo && !exist; nU++)
	  {
			 cU=new UserClass(nU);
			 cU->ReadData();
			 if (!strcmp(joinU.PEOPLENO, cU->stU.PEOPLENO)) exist=1;
			 delete cU;
			 if (exist) return 1;
	  }
	  return 0;
}

int JoinIn::InputData()
{
		unsigned char PASS1[9],PASS2[9];
		int bUsingID, bCanNotBeID, bCanNotBeNAME, bValidPN, bUsingPN;
		if (aliveUSER==0) halt("ERROR:happened processing user object-5");
		joinU = USER.stU;

		if (!ReadAnsiFile("JOININ.MSG"))
		c_hputs("¨˜Ø± ¨˜∑Ååı àa∑≥–Å ∫Å≠A∂a~~ –·∂·àa∑≥∑e ªbØ° ¥a∑°ó° ¨bπA!");
		do {
			if ( InputField("¥a∑°ó°", joinU.ID, 8, 4, false, 1) == CANCEL ) return CANCEL;
			if ( bUsingID=UsingID() ) ReadDataFile(307);
			if ( bCanNotBeID=ExistSpecialLetter(joinU.ID) ) ReadDataFile(194);
		} while ( bUsingID || bCanNotBeID );
		do {
			if ( InputField("∑°  üq", joinU.NAME, 8, 4, true, 1) == CANCEL ) return CANCEL;
			if ( bCanNotBeNAME=ExistSpecialLetter(joinU.NAME)) ReadDataFile(309);
		} while (bCanNotBeNAME);
		do {
			if ( InputField("¥q    —°", PASS1, 8, 4, false, -1) == CANCEL ) return CANCEL;
			if ( InputField("¥q—°—¬∑•", PASS2, 8, 4, 100, -1) == CANCEL ) return CANCEL;
			if ( strcmp(PASS1,PASS2) )
			{
					c_hputch(CR);c_hputch(LF);
					c_hputs("¥q—°àa ¨·ù° îaüsì°îa. îaØ° ∑≥ùb–a≠A∂a.");
			}
		}  while ( strcmp(PASS1,PASS2) );
		strcpy(joinU.PASS, PASS1);
		do {
			 if ( InputField("∫Å£•ówù¢§Â—°", joinU.PEOPLENO, 14, 14, false, 1) == CANCEL ) return CANCEL;
			 if ( !(bValidPN=isValidPeopleNo(joinU.PEOPLENO)) ) ReadDataFile(101);
			 if ( bUsingPN=UsingPeopleNo() ) ReadDataFile(308);
		} while ( !bValidPN || bUsingPN );
		if ( InputField("∂ÅÕe§Â—°", joinU.MAILNO, 7, 4, false, 1) == CANCEL) return CANCEL;
		if ( InputField("∫Å≠°", joinU.ADDRESS, 50, 10, true, 1) == CANCEL ) return CANCEL;
		if ( InputField("∏Â—¡§Â—°", joinU.TELNO, 14, 7, false, 1) == CANCEL ) return CANCEL;
		if ( InputField("´°´°§Â—°", joinU.BBNO, 14, 0, false, 1) == CANCEL ) return CANCEL;
		if ( InputField("–bäa/ãe¢Å¿·", joinU.WORKPLACE, 30, 4, true, 1) == CANCEL ) return CANCEL;
		if ( InputField("°A°° 1", joinU.MEMO[0], 50, 0, true, 0) == CANCEL ) return CANCEL;
		if ( InputField("°A°° 2", joinU.MEMO[1], 50, 0, true, 0) == CANCEL ) return CANCEL;
		if ( InputField("°A°° 3", joinU.MEMO[2], 50, 0, true, 0) == CANCEL ) return CANCEL;

		GetAllTime( &joinU.JoinTime );
		joinU.LogoutTime.year = 1970;
		joinU.LogoutTime.month = 1;
		joinU.LogoutTime.day = 1;
		joinU.LogoutTime.hour = 0;
		joinU.LogoutTime.min = 0;
		joinU.OK = FirstGrade;
		joinU.Level = JoinLev;
		joinU.Point = LEVEL[Le2I(JoinLev)].point;
		joinU.LeftTime = LEVEL[Le2I(JoinLev)].time;
		joinU.DnableSize = LEVEL[Le2I(JoinLev)].sizeDN;
		USER.stU = joinU;
		USER.UserNo= ++MaxUserNo;
		USER.SaveData();
		STAT_display();
		nNewJoin++;
		if (OpMode==1) // mid - open
		{
			  if(!ReadAnsiFile("AFTER.MSG") ) ReadDataFile(159);
		}
		else if (!ReadAnsiFile("AFTER.MSG") ) ReadDataFile(86);
		return NOERR;
}
void JoinIn::run()
{
		c_hclrscr();
		ExitLoop=0;
		if (aliveUSER==0) halt("ERROR: happened processing user object-7");
		if (  USER.UserNo == nGUEST )  InputData();
		if ( OpMode==0 ) P_();
		else if (OpMode==1)
		{
			  appObject(CUT, NULL);
		}
}
//-------------------------------------------------------------------------
//
//    ViewUserMenu
//
//-------------------------------------------------------------------------
ViewUserMenu::ViewUserMenu(char* _index) : BaseExec()
{
	strcpy (index, _index);
	USER.SaveData();
}

void ViewUserMenu::run()
{
	char instr[2];
	SetHanMode(false);
	ExitLoop=0;
	while ( !ExitLoop )
	{
		c_hclrscr();
		if (!ReadAnsiFile(strcat2(MENU[nAcc].ansifile,".MSG")))
		ReadDataFile(102); // menu
		c_hgetln(instr,"P",1);
		switch( atoi(instr) )
		{
			case 1:  FindWithName();  break;
			case 2:  FindWithId();    break;
			case 3:  SortWithSomething(UserLevel); break;
			case 4:  SortWithSomething(UserPoint); break;
			case 5:  SortWithSomething(UserLoginNo); break;
			case 6:  SortWithSomething(UserDnableSize); break;
			case 7:  SortWithSomething(UserPdsAct); break;
			case 8:  SortWithSomething(UserBbsAct); break;
		}
		if ( !stricmp(instr,"P") ) break;
	}
	P_();
}
void ViewUserMenu::FindWithId()
{
	int nPrinted=0,i;
	char ID[9];
	UserClass *fU;
	ReadDataFile(108); // input users id
	c_hgetln(ID,"",8);
	if (!strcmp(ID,"")) { ReadDataFile(34); ReadDataFile(95); return; }// canceled.
	ReadDataFile(109); // title.
	for (i=1; i<=MaxUserNo; i++)
	{
		fU = new UserClass(i);
		fU->ReadData();
		fU->stU.PEOPLENO[6] = 0;
		if ( !strcmp(ID, fU->stU.ID) )
		{
			// GetGrade is not used in temp UserClass object.
			c_hprintf("%c%8s %8s %6s %2i%2i%2i   %2i%2i%2i %4i %-30s\n\r",
					(fU->stU.OK)?' ':'D',
					fU->stU.ID,
					fU->stU.NAME,
					fU->stU.PEOPLENO,
					fU->stU.JoinTime.year-1900,
					fU->stU.JoinTime.month,
					fU->stU.JoinTime.day,
					fU->stU.LogoutTime.year-1900,
					fU->stU.LogoutTime.month,
					fU->stU.LogoutTime.day,
					fU->stU.Level,
					fU->stU.WORKPLACE );
			++nPrinted;
		}
		delete fU;

		if (nPrinted == 20)
		{
			nPrinted = 0;
			ReadDataFile(105); // continue - ENTER , exit - P
			if ( AnswerIs('P','P',false) ) break;
		}
	}
	if (nPrinted == 0) ReadDataFile(106); // no data !
	else ReadDataFile(107);  // data finding is ended.
	ReadDataFile(95);
}
void ViewUserMenu::FindWithName()
{
	int nPrinted=0,i;
	char NAME[9];
	UserClass *fU;
	ReadDataFile(103); // input users name
	c_hgetln(NAME,"",8);
	if (!strcmp(NAME,"")) { ReadDataFile(34); ReadDataFile(95); return; }// canceled.
	ReadDataFile(104); // title.
	for (i=1; i<=MaxUserNo; i++)
	{
		fU = new UserClass(i);
		fU->ReadData();
		fU->stU.PEOPLENO[6] = 0;
		if ( !strcmp(NAME, fU->stU.NAME   ) )
		{
			// GetGrade is not used in temp UserClass object.
			c_hprintf("%c%8s %8s %6s %2i%2i%2i   %2i%2i%2i %4i %-30s\n\r",
					(fU->stU.OK)?' ':'D',
					fU->stU.NAME,
					fU->stU.ID,
					fU->stU.PEOPLENO,
					fU->stU.JoinTime.year-1900,
					fU->stU.JoinTime.month,
					fU->stU.JoinTime.day,
					fU->stU.LogoutTime.year-1900,
					fU->stU.LogoutTime.month,
					fU->stU.LogoutTime.day,
					fU->stU.Level,
					fU->stU.WORKPLACE );
			++nPrinted;
		}
		delete fU;

		if (nPrinted == 20)
		{
			nPrinted = 0;
			ReadDataFile(105); // continue - ENTER , exit - P
			if ( AnswerIs('P','P',false )) return;
		}
	}
	if (nPrinted == 0) ReadDataFile(106); // no data !
	else ReadDataFile(107);  // data finding is ended.
	ReadDataFile(95);
}
struct SortedData
{
	int UserNo;
	int data;  // point or level.. and so on
};
void ViewUserMenu::SortWithSomething(int toSort)
{
	int i,j,nPrinted=0;
	class UserClass *sU;
	struct SortedData *SD,tmpSD;
	ExitLoop=0;
	SD = (SortedData*) malloc(sizeof(SortedData)*MaxUserNo);
	if (SD == NULL)
	{
		ErrMsg("ERROR : Not enough memory - Viewing userdata - sort");
		return;
	}
	for (i=1; i<=MaxUserNo; i++)
	{
		sU=new UserClass(i);
		sU->ReadData();
		SD[i-1].UserNo = sU->UserNo;
		switch (toSort)
		{
			case UserLevel      : SD[i-1].data = sU->stU.Level;   break;
			case UserPoint      : SD[i-1].data = sU->stU.Point;   break;
			case UserLoginNo    : SD[i-1].data = sU->stU.LoginNo; break;
			case UserDnableSize : SD[i-1].data = sU->stU.DnableSize; break;
			case UserPdsAct     : SD[i-1].data = sU->stU.PdsAct; break;
			case UserBbsAct     : SD[i-1].data = sU->stU.BbsAct; break;
		}
		delete sU;
	}
	for (i=0; i <= MaxUserNo-2; i++)
		for (j=i+1; j <= MaxUserNo-1; j++)
		{
			if ( SD[i].data < SD[j].data )
			{
				tmpSD = SD[i];
				SD[i] = SD[j];
				SD[j] = tmpSD;
			}
		}
	ReadDataFile(110); // title
	for (i=1; i<=MaxUserNo; i++)
	{
		sU=new UserClass(SD[i-1].UserNo);
		sU->ReadData();
		// GetGrade is not used in temp UserClass object.
		if (sU->stU.OK)
		{
			c_hprintf("%4i %8s %8s   %2i%2i%2i %4i§Â %4i %4i %6iKB %4iàÅ %4iàÅ %6i¶Ö",
					i,
					sU->stU.NAME,
					sU->stU.ID,
					sU->stU.LogoutTime.year-1900,
					sU->stU.LogoutTime.month,
					sU->stU.LogoutTime.day,
					sU->stU.LoginNo,
					sU->stU.Level,
					sU->stU.Point,
					sU->stU.DnableSize,
					sU->stU.PdsAct,
					sU->stU.BbsAct,
					sU->stU.TimeBank);
			nPrinted++;
		}
		delete sU;
		if (nPrinted == 20)
		{
			nPrinted = 0;
			ReadDataFile(105); // continue - ENTER , exit - P
			if ( AnswerIs('P','P',false) ) break;
		}
	}

	free (SD);

	//if (nPrinted == 0) ReadDataFile(106); // no data !
	//else
	ReadDataFile(107);  // data finding is ended.
	ReadDataFile(95);
}
//--------------------------------------------------------------------------
//
//            Time Bank Object.
//--------------------------------------------------------------------------
TimeBankMenu::TimeBankMenu(char* _index) : BaseExec()
{
	strcpy(index, _index);
}
void TimeBankMenu::run()
{
	char instr[2];
	SetHanMode(false);
	ExitLoop=0;
	while ( !ExitLoop )
	{
		c_hclrscr();
		if (!ReadAnsiFile(strcat2(MENU[nAcc].ansifile,".MNU")))
		ReadDataFile(111); // TimeBankMenu
		c_hgetln(instr,"P",1);
		switch( atoi(instr) )
		{
			case 1:  DrawBackTime();  break;
			case 2:  SaveTime();	break;
			case 3:  SaveAllTime(); break;
		}
		if ( !stricmp(instr,"P") ) ExitLoop=1;
	}
	P_();
}
void TimeBankMenu::DrawBackTime()
{
	char sTimeToDraw[6];
	int TimeToDraw;
	ReadDataFile(112);	 // How much time will you drawback?
	c_hgetln(sTimeToDraw,"",5);
	TimeToDraw = atoi(sTimeToDraw);
	if ( TimeToDraw )
	{
		 if ( USER.stU.TimeBank >= TimeToDraw )
		 {
			 USER.stU.TimeBank -= TimeToDraw;
			 USER.stU.LeftTime += TimeToDraw;
			 ReadDataFile(113);  // time drawing back isl successed
		 }
		 else ReadDataFile(114);  // failed to draw back time.
	}
	else ReadDataFile(34);  // canceled.
	ReadDataFile(95); // press ENTER
}
void TimeBankMenu::SaveTime()
{
	char sTimeToSave[6];
	int TimeToSave;
	ReadDataFile(115); // How much time will you save?
	c_hgetln(sTimeToSave,"",5);
	TimeToSave = atoi(sTimeToSave);
	if ( TimeToSave > 0 )
	{
		 if ( USER.stU.LeftTime >= TimeToSave )
		 {
			 USER.stU.TimeBank += TimeToSave;
			 USER.stU.LeftTime -= TimeToSave;
			 ReadDataFile(116);  // time saving is successed
		 }
		 else ReadDataFile(117);  // failed to save time.
	}
	else ReadDataFile(34);  // canceled.
	ReadDataFile(95); // press ENTER
}
void TimeBankMenu::SaveAllTime()
{
	ReadDataFile(118);  // Will you really save all time?
	if ( AnswerIs('Y','Y',false) )
	{
		USER.stU.TimeBank += USER.stU.LeftTime;
		USER.stU.LeftTime = 0;
		ReadDataFile(119);   // Saved All Time.
	}
	else
	{
		ReadDataFile(34);
		ReadDataFile(95);
	}
}
