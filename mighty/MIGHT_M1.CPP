#include "headers.h"
#define SELF this
int MakeParam(char* COMMAND, int& num, unsigned char param[maxPARAM][lenPARAM])
{
	int iCMD=-1, iPARA;
	char now;
	bool end_of_loop=false, exitloop;
	num = -1;

	while ( !end_of_loop )
	{
		if (++num > maxPARAM) return TOO_MANY_PARAM;
		iPARA=-1;
		exitloop=false;
		while( !exitloop )
		{
			now=COMMAND[++iCMD];
			switch( now )
			{
				case ',':
				case ' ':
						if (iPARA!=-1)
						{
							param[num][++iPARA]=0;
							exitloop=true;
						}
						break;
				case '-':
						if (iPARA!=-1)
						{
							param[num][++iPARA]=0;
							param[++num][0]=now;
							param[num][1]=0;
						}
						else
						{
							param[num][0]=now;
							param[num][1]=0;
						}
						exitloop=true;
						break;

				case  0 :
						if (iPARA!=-1) param[num][++iPARA]=0;
						else --now; // in end, if a new param is NULL, --now;
						exitloop=true;
						end_of_loop=true;
						break;
				default :
						if (iPARA <= lenPARAM-3) param[num][++iPARA] = now;

			}

		}
	}
	++num;
	return NOERR;
}

CircleID::CircleID(char* path)
{
	 // member file
	 sprintf(temp_str, "%s\\%s\\SIG_USER.DAT", InstDir, path);
	 if ( access(temp_str,0) != -1)
	 {
		  fMF= fopen(temp_str, "r+b");
		  if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");
		  fseek(fMF, 0L, SEEK_END);
		  MaxItem = ftell(fMF) / sizeof(CID);
		  fseek(fMF, 0L, SEEK_SET);
	 }
	 else
	 {
		  fMF= fopen(temp_str, "w+b");
		  MaxItem = 0;
	 }
	 if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");
}
CircleID::~CircleID()
{
	 if (fMF) fclose(fMF);
}
void CircleID::Seek(long offset, int whence)
{
	 fseek(fMF, offset, whence);
}
void CircleID::ReadItem()
{
	 fread(&CID, sizeof(CID), 1, fMF);
}
void CircleID::WriteItem()
{
	 fwrite(&CID, sizeof(CID), 1, fMF);
}
void CircleID::Apply(char* ID)
{
	  if (FindItem(ID))
		  if (isApplied()) return;

	  fclose(fMF);
	  fMF= fopen("SIG_USER.DAT", "ab");
	  if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");

	  strcpy(CID.ID, ID);
	  CID.status = APPLIED;
	  CID.grade = 1;   // first grade is "BI HOI WON"
	  fwrite(&CID, sizeof(CID), 1, fMF);
	  MaxItem++;

	  fclose(fMF);
	  fMF= fopen("SIG_USER.DAT", "r+b");
	  if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");
}
// FindItem(char* ID) have to be called before calling Del()
void CircleID::Del()
{
	  int nID=0, nStored=0;
	  if ( !isAccepted() && !isDenied() ) return;

	  fseek(fMF, 0L, SEEK_SET);
	  if (MaxItem!=0)
	  {
			circle_user_t* AllId = new circle_user_t[MaxItem];
			circle_user_t  tCID;
			do
			{
				  fread(&tCID, sizeof(tCID), 1, fMF);
				  if ( strcmp(CID.ID, tCID.ID) )
				  {
						strcpy( AllId[nStored].ID, tCID.ID);
						AllId[nStored].status = tCID.status;
						AllId[nStored].grade = tCID.grade;
						nStored++;
				  }
			} while(++nID <= MaxItem);

			fclose(fMF);
			fMF= fopen("SIG_USER.DAT", "wb");
			if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");

			nID=0;
			fseek(fMF, 0L, SEEK_SET);
			while(++nID <= nStored)
			{
				  fwrite(&AllId[nID-1], sizeof(AllId[nID-1]), 1, fMF);
			}
			fclose(fMF);

			MaxItem = nStored;

			fMF= fopen("SIG_USER.DAT", "r+b");
			if (fMF==NULL) halt("ERROR : Can't open SIG_USER.DAT in CircleID");
			delete AllId;
	  }
}
int CircleID::FindItem(char* ID)
{
	  int nID=0;
	  circle_user_t tCID;
	  fseek(fMF, 0L, SEEK_SET);
	  while(++nID <= MaxItem)
	  {
			 fread(&tCID, sizeof(tCID), 1, fMF);
			 if ( !strcmp(ID, tCID.ID) )
			 {
				  strcpy(CID.ID, tCID.ID);
				  CID.grade = tCID.grade;
				  CID.status = tCID.status;
				  fseek(fMF, -(long)sizeof(tCID), SEEK_CUR);
				  return 1;
			 }
	  }
	  strcpy(CID.ID, ID);
	  CID.grade = 1;
	  CID.status = NOTAPPLIED;
	  return 0;
}
void CircleID::SetStatus(int st)
{
	  if (FindItem(CID.ID))
	  {
			CID.status = st;
			fwrite(this, sizeof(CID), 1, fMF);
	  }
}
void CircleID::SetGrade(int gr)
{
	  if (FindItem(CID.ID))
	  {
			CID.grade = gr;
			fwrite(this, sizeof(CID), 1, fMF);
	  }
}
//-------------------------------------------------------------------------
CircleMenu::CircleMenu(char* _index) : BaseMenu()
{
	 strcpy(path, _index);
	 strcpy(index, _index);
	 CID = new CircleID(_index);
}
CircleMenu::~CircleMenu()
{
	 delete CID;
}
void CircleMenu::PrintCMD()
{
	 if (!ReadAnsiFile("SUB.CMD") ) ReadDataFile(9);
}

void CircleMenu::Z_()
{
	 if (!ReadAnsiFile(strcat2( MENU[nAcc].ansifile, ".LGO")))
			ReadDataFile(166);
}
void CircleMenu::NewProcess(char *str)
{
	 if (USER.stU.OK == SYSOP || USER.GetGrade()== SYSOP)
	 {
			switch( atoi(str) )
			{
				 case 10 : PrintApplyId(); break;
				 case 11 : MakeMember(); break;
				 case 12 : DenyMember(); break;
				 case 13 : DelMember(); break;
				 case 14 : SetMemberGrade(); break;
				 case 15 : MakeMemberAll(); break;
				 case 16 : SetAllMemberGrade(); break;
			}
	 }
	 if (CID->FindItem(USER.stU.ID) && CID->isAccepted())
	 switch( atoi(str) )
	 {
			case 3 : DelSelf(); break;
			case 4 : PrintMemberId(); break;
	 }
	 switch( atoi(str) )
	 {
			case 1 : ApplySelf(); break;
			case 2 : ConfirmJoin(); break;
	 }
}
void CircleMenu::run()
{
	 int i;
	 char CMD[maxGETLN+1];
	 // because object appending time and object running time is not
	 // equal, chdir function is included in run() member function.
	 if ( chdir(InstDir) ) halt("ERROR : Can't change directory to mighty installed directory.");
	 if ( chdir(path) ) halt("ERROR : Can't change directory to mighty installed directory.");
	 c_hclrscr();
	 Z_();
	 ExitLoop=0;
	 while (ExitLoop!=1)
	 {
			PrintCMD();
			for (i=0; i< maxGETLN+1; i++) *(CMD+i)=0;
			c_hgetln(CMD,"P",maxGETLN);
			BaseProcess(CMD);
			NewProcess(CMD);
	 }
}

#define IDINALINE 4
void CircleMenu::PrintApplyId()
{
	 int nRead =0;
	 ReadDataFile(183);
	 CID->Seek(0L, SEEK_SET);
	 for (int nU=1; nU<=CID->MaxItem; nU++)
	 {
		  CID->ReadItem();
		  if ( CID->isApplied() )
		  {
				 nRead++;
				 c_hprintf("%8s  ", CID->CID.ID);
				 if (nRead % IDINALINE == 0) c_hprintf("\n\r");
		  }
	 }
	 ReadDataFile(179);
}
void CircleMenu::PrintMemberId()
{
	 int nRead =0;
	 ReadDataFile(184);
	 CID->Seek(0L, SEEK_SET);
	 for (int nU=1; nU<=CID->MaxItem; nU++)
	 {
		  CID->ReadItem();
		  if ( CID->isAccepted() )
		  {
				  nRead++;
				  c_hprintf("%8s[%8s]", CID->CID.ID, SigGrade[CID->CID.grade]);
				  if (nRead % IDINALINE == 0) c_hprintf("\n\r");
		  }
	 }
	 ReadDataFile(179);

}
void CircleMenu::MakeMember()
{
	 char IDS[91];
	 ReadDataFile(176);
	 c_hgetln(IDS, "", 90);
	 if ( strcmp(IDS,"") )
	 {
		  int MaxMember;
		  unsigned char MemberId[maxPARAM][lenPARAM];

		  MakeParam(IDS, MaxMember, MemberId);
		  c_hprintf("\n\r");
		  for (int nMember=1; nMember<=MaxMember; nMember++)
		  {
				if ( isRealId( MemberId[nMember-1] ) )
				{
					  CID->FindItem( MemberId[nMember-1] );
					  if ( CID->isNotApplied() )
					  {
							CID->Apply( MemberId[nMember-1] );
							CID->FindItem( MemberId[nMember-1] );
					  }
					  CID->Accept();
					  c_hprintf("%s“±·i Á¡‹¡—w‹s §¡ÒA¶¥·a¡ ÒA¶¥ ¡w”eµA ÂˆaÐaµv¯s“¡”a.\n\r", CID->CID.ID);
				}
				else c_hprintf("%s·e —w¢–A»¡ ´g·e ´a·¡—¡ ·³“¡”a.", MemberId[nMember-1]);
		  }
	 }
	 ReadDataFile(180);
}
void CircleMenu::DenyMember()
{
	 char IDS[81];
	 ReadDataFile(177);
	 c_hgetln(IDS, "", 80);
	 if ( strcmp(IDS,"") )
	 {
		  int MaxMember;
		  unsigned char MemberId[maxPARAM][lenPARAM];

		  MakeParam(IDS, MaxMember, MemberId);
		  c_hprintf("\n\r");
		  for (int nMember=1; nMember<=MaxMember; nMember++)
		  {
				if ( isRealId( MemberId[nMember-1] ) )
				{
					 CID->FindItem( MemberId[nMember-1] );
					 if ( !CID->isApplied() ) c_hprintf("%s“±·e ˆa·³¯¥À÷¸a ¡w”eµA ·¶»¡ ´g¯s“¡”a.\n\r", CID->CID.ID);
					 else
					 {
							CID->Deny();
							c_hprintf("%s“±· ˆa·³·i ˆá¦Ðaµv¯s“¡”a.",MemberId[nMember-1]);
					 }
				}
				else c_hprintf("%s·e —w¢–A»¡ ´g·e ´a·¡—¡ ·³“¡”a.", MemberId[nMember-1]);
		  }
	 }
	 ReadDataFile(181);
}

void CircleMenu::DelMember()
{
	 char IDS[81];
	 ReadDataFile(178);
	 c_hgetln(IDS, "", 80);
	 if ( strcmp(IDS,"") )
	 {
		  int MaxMember;
		  unsigned char MemberId[maxPARAM][lenPARAM];

		  MakeParam(IDS, MaxMember, MemberId);
		  c_hprintf("\n\r");
		  for (int nMember=1; nMember<=MaxMember; nMember++)
		  {
				if ( isRealId( MemberId[nMember-1] ) )
				{
					 CID->FindItem( MemberId[nMember-1] );
					 if ( !CID->isAccepted() ) c_hprintf("%s“±·e •·Ñ¡ÒA ÒA¶¥ ¡w”eµA ·¶»¡ ´g¯s“¡”a.\n\r", CID->CID.ID);
					 else
					 {
							CID->Del();
							c_hprintf("%s“±·i •·Ñ¡ÒA ÒA¶¥ ¡w”eµA¬á ¬b¹AÐaµv¯s“¡”a.", MemberId[nMember-1]);
					 }
				}
				else c_hprintf("%s·e —w¢–A»¡ ´g·e ´a·¡—¡ ·³“¡”a.", MemberId[nMember-1]);
		  }
	 }
	 ReadDataFile(182);
}
void CircleMenu::SetMemberGrade()
{
	 int  gr;
	 char IDS[91];
	 char grade[3];
	 ReadDataFile(167); // input id to set grade.
	 c_hgetln(IDS, "", 90);

	 do
	 {
		  for(int i=1; i<=7; i++) c_hprintf("[%i] %s\n\r", i, SigGrade[i]);
		  ReadDataFile(301); // input new grade
		  c_hgetln(grade, "", 2);
		  if ( !strcmp(grade,"") ) break;
		  gr = atoi(grade);
	 } while(  gr<1 || gr>7 );

	 if ( strcmp(IDS,"") && strcmp(grade,"") )
	 {
		  int MaxMember;
		  unsigned char MemberId[maxPARAM][lenPARAM];
		  MakeParam(IDS, MaxMember, MemberId);
		  for (int nMember=1; nMember<=MaxMember; nMember++)
		  {
				if ( isRealId( MemberId[nMember-1] ) )
				{
					  CID->FindItem( MemberId[nMember-1] );
					  if ( CID->isAccepted() )
					  {
							c_hprintf("%s“±· •·Ñ¡ÒA —w‹s·i %sµA¬á %s¡ ¹¡¸÷Ðaµv¯s“¡”a.\n\r",MemberId[nMember-1],SigGrade[CID->CID.grade], SigGrade[gr]);
							CID->CID.grade = gr;
							CID->WriteItem();
					  } else c_hprintf("%s“±·e ·¡ •·Ñ¡ÒA· ÒA¶¥·¡ ´a“³“¡”a.\n\r",MemberId[nMember-1]);
				}
				else c_hprintf("%s·e —w¢–A»¡ ´g·e ´a·¡—¡ ·³“¡”a.\n\r", MemberId[nMember-1]);
		  }
	 }
}

void CircleMenu::SetAllMemberGrade()
{
	 int i, gr;
	 char grade[3];
	 do
	 {
		  for(i=1; i<=7; i++) c_hprintf("[%i] %s\n\r", i, SigGrade[i]);
		  ReadDataFile(301); //  input new grade
		  c_hgetln(grade, "", 2);
		  if( !strcmp(grade,"") ) break;
		  gr = atoi(grade);
	 } while( gr<1 || gr>7 );
	 ReadDataFile(302); // are you sure?
	 if (AnswerIs('Y', 'N', false))
	 {
		  CID->Seek(0L, SEEK_SET);
		  for (i=1; i<=CID->MaxItem; i++)
		  {
			  CID->ReadItem();
			  c_hprintf("%s“±· •·Ñ¡ÒA —w‹s·i %sµA¬á %s¡ ¹¡¸÷Ðaµv¯s“¡”a.\n\r",CID->CID.ID,SigGrade[CID->CID.grade], SigGrade[gr]);
			  CID->CID.grade = gr;
			  CID->Seek(-(long)sizeof(CID->CID),SEEK_CUR);
			  CID->WriteItem();
		  }
		  ReadDataFile(303); // member grade setting completed
	 }else ReadDataFile(304); // canceled
}
void CircleMenu::MakeMemberAll()
{
	 int nAccepted =0 ;

	 ReadDataFile(185);
	 if ( AnswerIs('Y','N',false) )
	 {
			CID->Seek(0L, SEEK_SET);
			for (int nU=1; nU<=MaxUserNo; nU++)
			{
				 CID->ReadItem();
				 if ( CID->isApplied() )
				 {
						 CID->Accept();
						 CID->Seek(-(long)(sizeof(CID->CID)), SEEK_CUR);
						 CID->WriteItem();
						 c_hprintf("%s“±·i Á¡‹¡—w‹s §¡ÒA¶¥·a¡ ÒA¶¥ ¡w”eµA ÂˆaÐaµv¯s“¡”a.\n\r", CID->CID.ID);
						 nAccepted++;
						 if ( nAccepted%20 == 0) ReadDataFile(186);
				 }
			}
	 }
	 ReadDataFile(180);
}
void CircleMenu::ApplySelf()
{
	 CID->FindItem( USER.stU.ID );
	 switch (CID->CID.status)
	 {
			case NOTAPPLIED : CID->Apply(USER.stU.ID); ReadDataFile(171); break;
			case APPLIED    : ReadDataFile(168); break;
			case ACCEPTED   : ReadDataFile(169); break;
			case DENIED     : ReadDataFile(170); break;
	 }
}
void CircleMenu::ConfirmJoin()
{
	 CID->FindItem( USER.stU.ID );
	 switch (CID->CID.status)
	 {
			case NOTAPPLIED :
			case APPLIED    : ReadDataFile(187);  break;
								case ACCEPTED   : c_hprintf("%s“±·e %s(·a)¡ •·Ñ¡ÒA ÒA¶¥·³“¡”a.\n\r", CID->CID.ID, SigGrade[CID->CID.grade]);
                                          break;
			case DENIED     : ReadDataFile(170);  break;
	 }
}
void CircleMenu::DelSelf()
{
	 CID->FindItem( USER.stU.ID );

	 ReadDataFile(173);
	 if ( AnswerIs('Y','N',false) )
	 {
			 if (CID->isAccepted())
			 {
					CID->Del();
					ReadDataFile(174);
			 }
			 else ReadDataFile(187);
	 }
	 else ReadDataFile(175);
}
//---------------------------------------------------------------------
//              SMAIL MENU CLASS
//---------------------------------------------------------------------
SendMail::SendMail(char* _index) : BaseExec()
{
	strcpy(index, _index);
}
void SendMail::run()
{
	 ExitLoop=0;
	 c_hclrscr();

	 if (USER.UserNo==nGUEST) ReadDataFile(290); // guest can't use wmail
	 else
	 {
		 // mail concerned menu do not have to do with index directory.
		 class WMailMenu WMail("000000", (unsigned char*)MENU[nAcc].sysid);
		 WMail.run();
		 sprintf(temp_str, "%s\\%s", InstDir, index);
		 chdir(temp_str);
	 }
	 // temp_str is global variable
	 // path is directory of TEXTMenu
	 P_();
}
//---------------------------------------------------------------------
//              SCRIPT MENU CLASS
//---------------------------------------------------------------------

ScriptMenu::ScriptMenu(char* _index) : BaseExec()
{
	strcpy(index, _index);
}
void ScriptMenu::run()
{
	ExitLoop=0;
	c_hclrscr();
	sprintf(temp_str, "%s\\%s.scr", InstDir, MENU[ nAcc ].ansifile);
	RunScript( temp_str );
	P_();
}
