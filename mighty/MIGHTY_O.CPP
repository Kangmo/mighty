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
//   WILL BE PERISHED BY COPY RIGHT LAW.   1995.11.1 KIM KANGMO	           //
//                                                                         //
//-------------------------------------------------------------------------//

SuperClass::SuperClass()
{
	  ExitLoop = 0;
}

int oIDtoRun=NULL;
char oINDEXtoRun[7];
void appObject(int oID, char* index)
{
		//printf("oID->%i", oID);  getch();
		if (oIDtoRun == 0)
		{
			  oIDtoRun = oID;
			  strcpy(oINDEXtoRun, index);
		}
		else halt("ERROR : object is duplicated. ");
}
void runObject()
{
		int ObjectID;
		ObjectID = oIDtoRun;
		oIDtoRun = NULL;
		switch (ObjectID)
		{
			case SUB     : SubMenu Sub(oINDEXtoRun); runOBJ=&Sub; Sub.run(); break;
			case BBS     : BbsMenu Bbs(oINDEXtoRun); runOBJ=&Bbs; Bbs.run(); break;
			case PDS     : PdsMenu Pds(oINDEXtoRun); runOBJ=&Pds; Pds.run(); break;
			case WMAIL   : WMailMenu WMail(oINDEXtoRun); runOBJ=&WMail; WMail.run(); break;
			case RMAIL   : RMailMenu RMail(oINDEXtoRun); runOBJ=&RMail; RMail.run(); break;
			case CHAT	 : Chat Chatting(oINDEXtoRun); runOBJ=&Chatting; Chatting.run(); break;
			case JOIN	 : JoinIn Join(oINDEXtoRun); runOBJ=&Join; Join.run(); break;
			case VUSER   : ViewUserMenu VUser(oINDEXtoRun); runOBJ=&VUser; VUser.run(); break;
			case TBANK   : TimeBankMenu TBank(oINDEXtoRun); runOBJ=&TBank; TBank.run(); break;
			case MSIG    : CircleMenu Circle(oINDEXtoRun); runOBJ=&Circle; Circle.run(); break;
			case NOTICE  : NoticeMenu Notice(oINDEXtoRun); runOBJ=&Notice; Notice.run(); break;
			case MBOX    : MBox MailBox(oINDEXtoRun); runOBJ=&MailBox; MailBox.run(); break;
			case MSEE    : MSee MailSee(oINDEXtoRun); runOBJ=&MailSee; MailSee.run(); break;
			case CDROMPDS: DnPdsMenu CdPds(oINDEXtoRun); runOBJ=&CdPds; CdPds.run(); break;
			case SMAIL   : SendMail  SMail(oINDEXtoRun); runOBJ=&SMail; SMail.run(); break;
			case SCRIPT  : ScriptMenu Script(oINDEXtoRun); runOBJ=&Script; Script.run(); break;
			case OMAIL   : BbsMenu OMail(oINDEXtoRun); runOBJ=&OMail; OMail.run(); break;
			case WAIT    : WaitConnect Wait; Wait.run(); break;
			case NULL    :
			case CUT     : CutConnect Cut; Cut.run(); break;
			case INPUTID : InputID Login; Login.run(); break;
			default   	 : halt("ERROR : Object manager is out of order.");
		}
}
//-----------------------------------------------------------------------
WaitConnect::WaitConnect()
{
		if (OpStart.hour<10)
		{
			 strPartTime[0]='0';
			 itoa(OpStart.hour,strPartTime+1,10);
		}
		else itoa(OpStart.hour,strPartTime,10);
		strPartTime[2]=':';
		if (OpStart.min<10)
		{
			 strPartTime[3]='0';
			 itoa(OpStart.min,strPartTime+4,10);
		}
		else itoa(OpStart.min,strPartTime+3,10);
		strPartTime[5]='-';
		if (OpEnd.hour<10)
		{
			 strPartTime[6]='0';
			 itoa(OpEnd.hour,strPartTime+7,10);
		}
		else itoa(OpEnd.hour,strPartTime+6,10);
		strPartTime[8]=':';
		if (OpEnd.min<10)
		{
			 strPartTime[9]='0';
			 itoa(OpEnd.min,strPartTime+10,10);
		}
		else itoa(OpEnd.min,strPartTime+9,10);
		strPartTime[11]=0;
		bWaiting=1;
}
WaitConnect::~WaitConnect()
{
		etimestr[0]=0;
		bWaiting=0;
}
#define STATUSDIFF 26
void WaitConnect::screenInit()
{
	 while( hlastwindow() != ERR_TOPOFSTACK );
	 while( hlastcurwindow() != ERR_TOPOFSTACK );
	 hwindow(1,1,SCRWIDTH, SCRHEIGHT);
	 hclrscr();
	 box3d( 0,ay2apy(2),639,ay2apy(30)-1,7,15,8);
	 kmPuts(1,1,"#1   @10†a∑°À°@15(@14MIGHTY@15) @9—°ØaÀa  @13ver 1@15.@130    @15(@12c@15) @14REFINED @11Soft            @15∫Å°AìA - F10   ");
	 box3d( scWGX-12, scWGY-12, scWGX + sWGX + 12, scWGY + sWGY + 12, 0, 0, 15);
	 box3d( scWGX-11, scWGY-11, scWGX + sWGX + 11, scWGY + sWGY + 11, barW, 15, 0);
	 box3d( scWGX-2, scWGY-2, scWGX + sWGX + 2, scWGY + sWGY + 2, bkW, 0, 15);
	 int StatusX=scSGX, StatusY=scSGY;
	 PrintValue(StatusX, StatusY, "ß°ß°µAØa ∑°üq", bName );
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "°AìAµwµbÆÅ",MenuNo);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "∂Öµw ¡∑ ∏Û≠¢ÆÅ",nAllLogin);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "∑°§Â ∏Û≠¢ÆÅ",nTodayLogin);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "≠•ì± ∏Û≠¢ÆÅ",nSonnimLogin);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "Ø•ãA àa∑≥",nNewJoin);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "†aª°†b ∏Û≠¢∏a ID",LastUserID);
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "†aª°†b ∏Û≠¢∏a ∑°üq",LastUserNAME);

	 char *sOpMode[3] = {
								  "â∑àÅ",
								  "§eâ∑àÅ",
								  "ß°â∑àÅ"
							  };
	 PrintValue(StatusX, StatusY+=STATUSDIFF, "∂Öµw §wØ¢", sOpMode[OpMode]);

	 _hangulmode=false;
	 STAT=HOST_STAT;
	 STAT_display();
	 hsetbkcolor(bkW);   hsetcolor(lW);
	 hwindow( scWTX, scWTY, scWTX + sWTX-1, scWTY + sWTY-1);
}

void WaitConnect::modemInit()
{
	 int ret;
	 char *text[4] =
		 { "°°ïQ∑i ¡°ã°—¡",
			 "Ø°«°â° ∑∂Øsì°îa",
			 ""};
	 ret = StdMsg(180, 230, text);
	 SioHangUp(port);
	 SioDelay(9);
	 SioTxFlush(port);
	 SioRxFlush(port);
	 SioDelay(9);
	 SioHayes(port, WaitInit);
	 if (ret == NOERR) SCR.pop();
	 gettime( &LastInit );
}
void WaitConnect::hostInit()
{
	 chdir( strcat2(InstDir,"\\TEMP") );
	 if ( !access("RDN.DAT",0) ) remove( "RDN.DAT" );
	 if (chdir( InstDir )) halt("ERROR : Mighty installed directory is invalid - run setup now.");
	 bAutoHan=1;
	 ERROR_NO=0;
	 bUserNotExist=0;
	 bTempSysopOn = 0;
	 bSysopHangUp = 0;
	 bChatMode = 0;
	 SPEED = 14400;
	 u_idx=1;
	 bChatting=0;
}
#define ValueBkCol 7
#define TitleBkCol 1
#define ValueCol 14
#define TitleCol 15

void WaitConnect::PrintValue(int px, int py, const char* title, int value)
{
	 int TitleLen = strlen(title);
	 rCOLOR.push();
	 box3d(px,py, px + (TitleLen +7)* CS, py + LS+4, ValueBkCol, 8, 15);
	 box3d(px+1,py+1, px + (TitleLen+1) * CS, py + LS+3, TitleBkCol, 15, 8);

	 hsetbkcolor(TitleBkCol);
	 hsetcolor(TitleCol);
	 hprintfpxy(px+4, py+2, "%s",title);

	 hsetbkcolor(ValueBkCol);
	 hsetcolor(ValueCol);
	 hprintfpxy(px+(TitleLen+1) * CS +4 , py+2, "%5i",value);
	 rCOLOR.pop();
}
void WaitConnect::PrintValue(int px, int py, const char* title, unsigned long value)
{
	 int TitleLen = strlen(title);
	 rCOLOR.push();
	 box3d(px,py, px + (TitleLen +10)* CS, py + LS+4, ValueBkCol, 8, 15);
	 box3d(px+1,py+1, px + (TitleLen+1) * CS, py + LS+3, TitleBkCol, 15, 8);

	 hsetbkcolor(TitleBkCol);
	 hsetcolor(TitleCol);
	 hprintfpxy(px+4, py+2, "%s",title);

	 hsetbkcolor(ValueBkCol);
	 hsetcolor(ValueCol);
	 hprintfpxy(px+(TitleLen+1) * CS +4 , py+2, "%8lu",value);
	 rCOLOR.pop();
}
void WaitConnect::PrintValue(int px, int py, const char* title, char* value)
{
	 int TitleLen = strlen(title);
	 int ValueLen = strlen(value);
	 rCOLOR.push();
	 box3d(px,py, px + (TitleLen + ValueLen + 2)* CS, py + LS+4, ValueBkCol, 8, 15);
	 box3d(px+1,py+1, px + (TitleLen+1) * CS, py + LS+3, TitleBkCol, 15, 8);

	 hsetbkcolor(TitleBkCol);
	 hsetcolor(TitleCol);
	 hprintfpxy(px+4, py+2, "%s",title);

	 hsetbkcolor(ValueBkCol);
	 hsetcolor(ValueCol);
	 hprintfpxy(px+(TitleLen+1) * CS +4 , py+2, "%s",value);
	 rCOLOR.pop();
}
#define WaitConnectLimSec 10
char bLogoPrinted=0;
void WaitConnect::run()
{
	 unsigned char bReady=1, bSpeedSet=0, bRing=0;
	 int ch, real_spd;
	 bLocal = 0;
	 hostInit();
	 makeIdIndex();
	 screenInit();
	 if (!bLogoPrinted) { MightyIs(); bLogoPrinted=1; }
	 modemInit();  // LastInit is in this function
	 while ( (bWaiting /*&& (bRing==0 || !SioDCD(port))*/) && !DoNullModem )
	 {
			 if ( !kbhit() && !SioTxQue(port) && !SioRxQue(port) )
			 {
					 gettime( &NOW );
					 if ( InitGab > 0 && !bRing )
					 {
						  if ( ElapseTime( LastInit.ti_hour, LastInit.ti_min,
													NOW.ti_hour, NOW.ti_min )  >= InitGab )
						  modemInit();
					 }
					 if (bUsePartT)
					 {
							if (  ( ElapseTime( OpStart.hour, OpStart.min,
															NOW.ti_hour, NOW.ti_min )    >=
											ElapseTime( OpStart.hour, OpStart.min,
															OpEnd.hour,OpEnd.min)  ) && bReady )
							{
									ErrMsg("∂ÖµwØ°àe∑° ¥aì°£aù° ∏Â—¡üi §hª° ¥gØsì°îa");
									bReady=0;
									SioHayes(port,"ats0=0");
									wputsxy(STATWIN, 8, 1, "∏Â—¡¥e§h∑q");
							}
							if (  ( ElapseTime( OpStart.hour, OpStart.min,
															NOW.ti_hour, NOW.ti_min )	<
											ElapseTime( OpStart.hour, OpStart.min,
															OpEnd.hour,OpEnd.min)  ) && (bReady==0) )
							{
								 ErrMsg("∂ÖµwØ°àe∑° ñA¥· ∏Â—¡üi §hØsì°îa");
								 bReady=1;
								 SioHayes(port, "ats0=1");
								 wputsxy(STATWIN, 8, 1, "∏Û≠¢îÅã°∫ó");
							}
					 }
					 else if ( bReady==0 )
					 {
							bReady=1;
							SioHayes(port,"ats0=1");
							wputsxy(STATWIN, 8, 1, "∏Û≠¢îÅã°∫ó");
					 }

					 cursor_display();  // in this function, time display is included
			 }

			 if (SioRxQue(port))
			 {
					ch=SioGetc(port,0);
					hputch(ch);
					if (  ( ch=='R' ) && bReady==1 )
						 if (findStr("ING"))
						 {
								wputsxy(STATWIN, 8, 1, "ü∑Ø•—°àqª°");
								bRing=1;
								bSpeedSet=0;
						 }
					if ( ch=='N')
						 if (findStr("O CARRIER"))
						 {
								wputsxy(STATWIN, 8, 1, "∏Â—¡îÅã°∫ó");
								bRing=0;
						 }
					//if ( bRing == 1 )
						 if (ch=='C')
						 {
							 if (findStr("ONNECT "))
									if (SetModemSpeed(real_spd)) bSpeedSet=1;
						 }
						 if ( bSpeedSet )
						 {
								time_t first, second;
								first = time(NULL);
								while (!SioDCD(port))
								{
									  while (SioRxQue(port)) hputch(SioGetc(port,9));
									  second = time(NULL);
									  if ( difftime(second, first) > WaitConnectLimSec ) break;
								}
								if (SioDCD(port))
								{
									  WriteLogData("‘ê ∏Û≠¢ ¨˜â∑ : %6lBPS ‘ë\n", SPEED);
									  wputsxy(STATWIN, 8, 1, "∏Û≠¢  ¨˜â∑");
									  SioBaud(port, real_spd);
									  bWaiting=0;
								}
								else
								{
									  modemInit();
									  bSpeedSet=0;
								}
						 }
			 }
			 if (kbhit())
			 {
					ch = getch();
					if ( ch==0 ) process_ctrlkey(ch);
					if (ch != 0) SioPutc(port, ch);
			 }
		}

		if ( SioDCD(port) )
		{
			 if (DoNullModem) wputsxy(STATWIN, 8, 1, "COM1  	");
			 else wputsxy(STATWIN, 8, 1, "∑A∏·	    ");
		}
		else wputsxy(STATWIN, 8, 1, "ù°ƒÈ      ");
		appObject(INPUTID, NULL);
}
int WaitConnect::SetModemSpeed(int& spd)
{
		char spdstr[7];
		SioGets(port, spdstr, 6, -1);
		hprintf("%s\n\r",spdstr);
		SPEED=atol(spdstr);
		if (SPEED <= 300L)  { SPEED=300;  spd=Baud300; }
		else if (SPEED <= 600L )  { SPEED=600L;  spd=Baud600; }
		else if (SPEED <= 1200L) { SPEED=1200L; spd=Baud1200; }
		else if (SPEED <= 2400L) { SPEED=2400L; spd=Baud2400; }
		else if (SPEED <= 4800L) { SPEED=4800L; spd=Baud4800; }
		else if (SPEED <= 9600L) { SPEED=9600L; spd=Baud9600; }
		else if (SPEED <= 19200L) { SPEED=19200L; spd=Baud19200; }
		else if (SPEED <= 38400L) { SPEED=38400L; spd=Baud38400; }
		else if (SPEED <= 57600L) { SPEED=57600L; spd=Baud57600; }
		else if (SPEED <= 115200L) { SPEED=115200L; spd=Baud115200; }
		else { hputs("Error of host program. come to HiTel(go glline)"); return 0; }
		return 1;
}
void CutConnect::run()
{
			 int count=3;
			 SaveLogData();
			 if ( aliveUSER )
			 {
					USER.SaveData();    // (∏aï∑) : ≠•ì±∑Å âw∂Å ∏·∏w¥gâ° ãaê∑ ®aπaêaµ±.
					if (!ReadAnsiFile("BYE.MSG") )
						 ReadDataFile(18);    // in SaveData, when UserNo==nGUEST
					delay(1500);
					USER.UserExit();         // return
			 }
			 if (!bLocal)
			 {
					while ( count-- > 0 )
					{
						 if ( !SioHangUp(port) )
						 {
								ErrMsg("∏Û≠¢∑i ègìeïAµA Ø©ÃÅ–ñØsì°îa");
								ErrMsg("îaØ° ègâVØsì°îa");
						 }
						 else break;
					}
					if ( SioDCD(port) )
							 ErrMsg("∏Û≠¢ègã°Ø©ÃÅ : îÅã°°°óaù° ói¥·àsì°îa.");
			 }
			 appObject(WAIT, NULL);
}
InputID::InputID()
{
		hsetcolor(15);
		hsetbkcolor(0);
		hwindow(1,1,hgetmaxax(), hgetmaxay()-(bChatMode?CBOXLINES+2:1));
		SioRxFlush(port);
		SioTxFlush(port);
		c_hclrscr();
		bInputId = 1;
}
InputID::~InputID()
{
		bInputId = 0;
}
//  mode   0 : 5§ÂµA àÈ√• ã°“Aüi îa ëΩ√±
//         1 : ≠•ì± ∏Û≠¢
//         2 : àa∑≥ñE ¥a∑°ó°ù° ∏Û≠¢.
//         3 : ï°ØaÆ… ¨a∂w
void InputID::run()
{
		unsigned char UserPass[9],mode=0;
		int count=4,i,UserNo;
		ReadAnsiFile("MIGHTY.LGO");
		ReadDataFile(39);  // Mighty host logo.. input guest or sonnim...
		c_hprintf("¿·∑q µ°Ø•¶Ö∑e  IDîÅØ• \"%s\"üi ∑≥ùb–a≠A∂a\n\n\r",LoginId);
		ReadDataFile(165);
		mode=0;
		SetHanMode(false);
		while ( count-- >=0 )
		{
			 UserNo = -1;
			 memset(LOGIN,0,11);
			 memset(UserPass,0,9);
			 c_hputs("\n\r¨a∂w∏aID : ");
			 c_hgetln(LOGIN," ",8); // This makes computer to use up counts.
									// and user can't see this.
			 if (  !strcmp(LOGIN,LoginId)   )  // LoginId is sonnim id
			 {
					mode=1;
					break;
			 }
			 for (i=1; i<=MaxUserNo; i++)
					if (!strcmp( IdIndex[i-1].ID, LOGIN) )
					{
							UserNo = i;
							break;
					}
			 if ( UserNo == -1 )
			 {
					c_hputs("ówù¢ñAª° ¥g∑e ID∑≥ì°îa.");
			 }
			 else
			 {
					c_hputs("¥q    —° : ");

					bPassInput=1;
					c_hgetln(UserPass, "", 8);
					bPassInput=0;

					if (!strcmp( IdIndex[UserNo-1].PASS, UserPass ) )
					{
						 mode = 2;
						 break;
					}
					else  c_hputs("\n\r¥q—°àa Àiü≥ì°îa.");
			 }
			 c_hputs("\n\r");
		}
		GetAllTime( &tLogin);
		if (SPEED < MinSpeed)
		{
			  if (!ReadAnsiFile("LOWSPEED.MSG"))
					  c_hprintf("%sµAìe %u∑°¨w∑Å ≠¢ï°üi àaª• °°ïQ†e∑° ∏Û≠¢–iÆÅ ∑∂Øsì°îa.",bName,MinSpeed);
			  appObject(CUT, NULL);
			  WriteLogData("%s","‘ˇ ∏Û≠¢≠¢ï°àa ¬A∏· ∏Û≠¢≠¢ï°•°îa êx¥a¨· ∏Û≠¢ π∑ûa");
		}
		// it is certain that this is not sig menu, so I used stU.OK
		else switch (mode)
		{
				case 0 :	         appObject(CUT,NULL);
										break;
				case 1 : WriteLogData("‘ˇ %s¥a∑°ó°ù° ù°ãa∑•–q",LoginId);
							switch (OpMode)
							{
								 case 0 :
										if (!ReadAnsiFile("SONNIM.MSG"))
										ReadDataFile(2); // "Welcome Sonnim" text file
										if (!aliveUSER) USER.ReadData( nGUEST );
										else halt("ERROR : happened processing user object-1");
										if ( USER.stU.LeftTime > 0 )
										{
											 STAT=USER_STAT;
											 STAT_display();
											 HostInitialize();
											 if ( Type2I(NOTICE) != ERR )
											 appMenuObject( Type2I(NOTICE) );
											 else appMenuObject( Me2I("000000"));
										}
										else
										{
											 appObject(WAIT, NULL);
										}
										break;
								 case 1 :
										if (!ReadAnsiFile("MIDOPEN.MSG"))
										ReadDataFile(157);
										if (AnswerIs('Y','N',true))
										{
											 if (!aliveUSER) USER.ReadData( nGUEST );
											 else halt("ERROR : happened processing user object-1");
											 if ( USER.stU.LeftTime > 0 )
											 {
												  STAT=USER_STAT;
												  STAT_display();
												  HostInitialize();
												  if ( Type2I(JOIN) != ERR )
														appMenuObject( Type2I(JOIN) );
												  else halt("ERROR : Can't find Join Menu. Run setup and make Join Menu");
											 }
											 else appObject(CUT, NULL);
										}
										else
										{
											 if (!ReadAnsiFile("NOJOIN.MSG"))
													ReadDataFile(158); // connection closed.
											 appObject(CUT, NULL);
										}
										break;
								 case 2 :
										if (!ReadAnsiFile("CLOSE.MSG"))
										ReadDataFile(156);
										WriteLogData("‘ê ß°â∑àÅ ∂Öµw∑°£aù° —°ØaÀaàa àwπAù° ∏Û≠¢ èg∑q ‘ë");
										appObject( CUT, NULL);
										break;
							}
							if (aliveUSER)
							{
										nSonnimLogin++;
										nTodayLogin++;
										nAllLogin++;
										strcpy(LastUserID, LOGIN);
										strcpy(LastUserNAME, "≠•ì±");
							}
							break;
				case 2 : if (!aliveUSER)
							{
								 USER.ReadData( UserNo );
								 WriteLogData("‘ˇ %s¥a∑°ó°ù° ù°ãa∑•–q", USER.stU.ID);
								 if (!USER.stU.OK)
								 {
										 if (!ReadAnsiFile("CANTUSE.MSG"))
											  ReadDataFile(160);
										 WriteLogData("‘ê ¨a∂w∫óª° ¥a∑°ó°∑°£aù° —°ØaÀaàa àwπAù° ∏Û≠¢èg∑q ‘ë");
										 appObject(CUT, NULL);
								 }
								 else
								 {
										 GiveTimeAndDnableSize();
										 if( !ReadAnsiFile("USERINFO.MSG") )
											 USER.ViewInfo();
										 if ( USER.stU.LeftTime > 0 )
										 {
											  STAT=USER_STAT;
											  STAT_display();
											  HostInitialize();
											  class CheckMail CM;
											  CM.run();
											  if ( Type2I(NOTICE) != ERR )
											  appMenuObject( Type2I(NOTICE) );
											  else appMenuObject( Me2I("000000"));
										 }
										 else
										 {
											  ReadDataFile(42);
											  WriteLogData("‘ê Ø°àe∑i ¢ÅñÅ ¨a∂w–aµa —°ØaÀaàa àwπAù° ∏Û≠¢ èg∑q ‘ë");
											  appObject(CUT, NULL);
										 }
								 }
								 if (aliveUSER)
								 {
										 nAllLogin++;
										 nTodayLogin++;
										 strcpy(LastUserID, USER.stU.ID);
										 strcpy(LastUserNAME, USER.stU.NAME);
								 }

							} else halt("ERROR : happened processing user object-2");
							break;
		}
}
void InputID::GiveTimeAndDnableSize()
{
		if ( tLogin.day != USER.stU.LogoutTime.day ||
			  tLogin.month != USER.stU.LogoutTime.month ||
			  tLogin.year != USER.stU.LogoutTime.year )
		{
			  if (!ReadAnsiFile("1STLOGIN.MSG"))
			  {
					 ReadDataFile(164);
					 if (GiveDnableSize) ReadDataFile(191);
			  }
			  USER.stU.LeftTime = LEVEL[Le2I(USER.stU.Level)].time;
			  if (GiveDnableSize)
				  USER.stU.DnableSize = LEVEL[Le2I(USER.stU.Level)].sizeDN;
		}
}
//-------------------------------------------------------------------------
//         File Stack Object
//-------------------------------------------------------------------------
CFileStack::CFileStack()
{
	files=0;
}
CFileStack::~CFileStack()
{
	clearstack();
}
bool CFileStack::Push(char* newfile)
{
   if ( files >= MAX_FILE_STACK ) return false;
	FileName[++files-1] = (char*) malloc(strlen(newfile)+1);
	if (FileName[files-1]==NULL) ErrMsg("Not Enough memory - File Stack 's push()");
   strcpy(FileName[files-1],newfile);
   return true;
}
bool CFileStack::Pop(char* oldfile)
{
	if ( files <= 0 ) return false;
	strcpy(oldfile,FileName[files-1]);
	free(FileName[files-- -1]);
	return true;
}
void CFileStack::clearstack()
{
	if ( files <=0 ) return;
	for(int index=1; index<=files; index++) free(FileName[index-1]);
	files=0;
}

//-------------------------------------------------------------------------
//         USERCLASS
//-------------------------------------------------------------------------
UserClass::UserClass()
{
		bRealUser=1;
		RDNfiles=0;
		SigGrade=1;
}
UserClass::UserClass(int UserNo_)
{
		UserNo=UserNo_;  // when guest.... UserNo is nGUEST;
		if (UserNo==nGUEST) GuestData();
		RDNfiles=0;
		bRealUser=0;
		SigGrade=1;
}
// only USER can do ReadData(int UserNo_)
void UserClass::ReadData(int UserNo_)
{
		UserNo=UserNo_;  // when guest.... UserNo is nGUEST;
		if (UserNo==nGUEST)
		{
			GuestData();
		}
		else ReadData();
		aliveUSER=1;
}
void UserClass::UserExit()
{
		if (bRealUser)
		{
			aliveUSER=0;
			bUserNotExist =1;
			//printf("USER IS OUT NOW!!");
			//getch();
		}
}
int UserClass::GetGrade()
{
		if (MENUDATA[nAcc].signum==0) //when current menu is not circle(sig)
			  return stU.OK;
		else return SigGrade;
}
void UserClass::AddPoint(int n)
{
	 stU.Point += n;
	 SetLevel();
}
void UserClass::SetLevel()
{
	 if ( Le2I(stU.Level) < LevelNo-1 )
	 for (int i=LevelNo-1; i>=0; i--)
	 {
		 if ( LEVEL[i].point <= stU.Point && LEVEL[i].level > stU.Level )
		 {
			 //hprintf("point L:%i <= U:%i, level L:%i > U:%i",
			 //LEVEL[i].point, stU.Point, LEVEL[i].level, stU.Level);getch();
			 if (i==0) halt("LOGIC ERROR : While setting level");
			 stU.Level=LEVEL[i].level;
			 if (!bPDrun)
				  if (!ReadAnsiFile("LEVELUP.MSG")) ReadDataFile(65);  // Your level is upgraded.
			 break;
		 }
	 }
}
void UserClass::ViewPf()
{
	 int len,i;
	 len=8-(strlen(stU.ID)+strlen(stU.NAME) )/2;

	 c_hputs("\n\r");
	 for (i=1; i<=len; i++) c_hputch('-');
	 c_hprintf("-- < %s(%s)ì±∑Å Ø•¨w∏˜•° > --",stU.ID, stU.NAME);
	 for (i=1; i<=len; i++) c_hputch('-');
	 c_hprintf("\n\ràa ∑≥ ∑© ∏a : %4iëe %2i∂© %2i∑© %2iØ° %2i¶Ö",stU.JoinTime.year,stU.JoinTime.month,stU.JoinTime.day,stU.JoinTime.hour,stU.JoinTime.min);
	 c_hprintf("\n\r∑°§Â   ∏Û≠¢ : %4iëe %2i∂© %2i∑© %2iØ° %2i¶Ö",stU.LoginTime.year,stU.LoginTime.month,stU.LoginTime.day,stU.LoginTime.hour,stU.LoginTime.min);
	 c_hprintf("\n\r¬Aãe   π∑ûa : %4iëe %2i∂© %2i∑© %2iØ° %2i¶Ö",stU.LogoutTime.year,stU.LogoutTime.month,stU.LogoutTime.day,stU.LogoutTime.hour,stU.LogoutTime.min);
	 c_hprintf("\n\r¡∑ ∏Û ≠¢ : %-4i(“A)   Ø°àe∑e–ó : %-4i(¶Ö)",stU.LoginNo,stU.TimeBank);
	 c_hprintf("\n\r—e∏ÅùA•I : %-4i       —e∏Å∏ÒÆÅ : %-4i(∏Ò)",stU.Level,stU.Point);
	 c_hprintf("\n\rêq∑eØ°àe : %-4i(¶Ö)   îa∂Öàaìw : %-4i(KB)", stU.LeftTime,stU.DnableSize);
	 c_hprintf("\n\rùA•I¥Û∑i ∂·–Å œ©∂a–e ∏ÒÆÅ : %i(∏Ò)",LEVEL[Le2I(stU.Level)+1].point - stU.Point);
	 c_hprintf("\n\r-----------------------------------------\n\n\r");
}
void UserClass::ViewInfo()
{
		if (!ReadAnsiFile("USERPF.MSG")) ReadDataFile(1);
}
void UserClass::GuestData()
{
		strcpy(stU.ID,"≠•ì±");
		strcpy(stU.NAME,"£°—¬∏˜");
		stU.PASS[0]=0;
		strcpy(stU.PEOPLENO,"£°—¬∏˜");
		stU.MAILNO[0]=0;
		stU.ADDRESS[0]=0; stU.TELNO[0]=0; stU.BBNO[0]=0;
		strcpy(stU.WORKPLACE,"£°—¬∏˜");
		stU.MEMO[0][0]=0; stU.MEMO[1][0]=0; stU.MEMO[2][0]=0;

		for(int i=0; i<15; i++) {if (LEVEL[i].level >= SonnimLev) break;}
		stU.OK =NONEMEMBER; stU.BbsAct=0; stU.PdsAct =0; stU.UpDataSize=0;
		stU.DnDataSize =0;  stU.LoginNo=1; stU.Point =LEVEL[i].point;
		stU.Level = SonnimLev; stU.LeftTime =LEVEL[i].time; stU.TimeBank =0;
		stU.DnableSize = LEVEL[i].sizeDN; stU.UsedTime=0;
		stU.LoginTime.year = tLogin.year;
		stU.LoginTime.month = tLogin.month;
		stU.LoginTime.day = tLogin.day;
		stU.LoginTime.hour = tLogin.hour;
		stU.LoginTime.min = tLogin.min;
		stU.LogoutTime.year = 0;
		stU.LogoutTime.month = 0;
		stU.LogoutTime.day = 0;
		stU.LogoutTime.hour = 0;
		stU.LogoutTime.min = 0;
}

void UserClass::SaveData()  // Always executed before HangUp
{
		int bFirstSave=1, i;
		struct User_t tmpU;
		FILE *fOUT,*fUD;  // real in file, buffer for in file,
		if (UserNo == nGUEST) return; // after join,USER->UserNo = ++MaxUserNo;
		if (bTempSysopOn)
		{
			 bTempSysopOn = 0;
			 USER.stU.OK = RealGrade;
			 RealGrade = -1;
		}

		if ( access(strcat2(InstDir,"\\USERDATA.DAT"),0) != -1 )
		{
			fUD = fopen(strcat2(InstDir,"\\USERDATA.DAT"),"rb");
			if (fUD==NULL) halt("ERROR : NOT ENOUGH MEMORY WHILE SAVING (NEW)USERDATA.DAT");
			for(i=1; i<=MaxUserNo; i++)
			{
				fread(&tmpU, sizeof(User_t), 1, fUD);
				if (!strcmp(tmpU.ID, stU.ID))
				{
					bFirstSave=0;
					break;
				}
			}
			fclose(fUD);
		}
		if ( !strcmp(USER.stU.NAME,stU.NAME) ) GetAllTime( &stU.LogoutTime);

		if ( !bFirstSave )
		{
			 fOUT=fopen(strcat2(InstDir,"\\USERDATA.DAT"),"r+b");
			 for(i=1; i<=MaxUserNo; i++)
			 {
				 fread(&tmpU, sizeof(User_t), 1, fOUT);
				 if (!strcmp(tmpU.ID, stU.ID))
				 {
					 fseek(fOUT, -(long)(sizeof(User_t)), SEEK_CUR);
					 break;
				 }
			 }
		}
		else fOUT=fopen(strcat2(InstDir,"\\USERDATA.DAT"),"ab");
		if (fOUT == NULL ) halt("ERROR : NOT ENOUGH MEMORY WHILE SAVING USERDATA.DAT");

		fwrite(&stU, sizeof(stU), 1, fOUT);
		fclose( fOUT );
}
void UserClass::ReadData()      //  When User ID is guest.. return.
{
		if ( UserNo == nGUEST ) return;
		FILE *fIN = fopen(strcat2(InstDir,"\\USERDATA.DAT"),"rb");
		if ( fIN == NULL )
				halt("ERROR : Happend while reading User data");

		fseek(fIN, (long)( sizeof(struct User_t)*(UserNo-1) ), SEEK_SET);
		fread(&stU, sizeof(struct User_t), 1, fIN);

		stU.LoginTime.year = tLogin.year;
		stU.LoginTime.month = tLogin.month;
		stU.LoginTime.day = tLogin.day;
		stU.LoginTime.hour = tLogin.hour;
		stU.LoginTime.min = tLogin.min;
		stU.LoginNo++;

		fclose(fIN);
}

//-------------------------------------------------------------------------//
//                 Sysop Menu                                              //
//                  SMorder Object.                                        //
//-------------------------------------------------------------------------//

SMorder::SMorder()
{
	 if (getcwd(direc,99)==NULL) halt("ERROR : Memorizing directory.");
	 if (aliveUSER) USER.SaveData();
	 WriteLogData("‘ˇ Ø°¨s°AìA Ø©–ó Ø°ï°");
}
SMorder::~SMorder()
{
	 if (chdir(direc)==-1) halt("ERROR : Changing memorized directory");
	 if (aliveUSER) USER.ReadData();
}
void SMorder::run()
{
	 char instr[3],pass[9];
	 if (!bWaiting)
	 {
			ReadDataFile(120);
			bPassInput=1;
			c_hgetln(pass,"", 8);
			bPassInput=0;
	 }
	 SetHanMode(false);
	 if (bWaiting || !strcmp(pass,SmPass))
	 {
		 WriteLogData("‘ˇ Ø°¨s°AìA Ø©–ó ¨˜â∑");
		 do
		 {
			 c_hclrscr();
			 if (!ReadAnsiFile("SYSMENU.MSG")) ReadDataFile(121); // menu
			 c_hgetln(instr,"P",2);

			 switch( atoi(instr) )
			 {
				  case 1 : AppUserData();  break;
				  case 2 : ReindexUserData();  break;
				  case 3 : BackupUserData();  break;
				  case 4 : RecoverUserData();  break;
				  case 5 : MakeUserData2Txt();  break;
				  case 6 : ReindexNowMenuData();  break;
				  case 7 : ReindexAllMenuData();  break;
				  case 8 : BackupMenuData();  break;
				  case 9 : RecoverMenuData();  break;
				  case 10 : RemoteDosShell();  break;
			 }
		 } while ( strcmp(instr,"P") && strcmp(instr,"p") );
	 }
	 else
	 {
		 WriteLogData("‘ˇ ¥q—°üi °µ†x¬Å¥·¨· Ø°¨s°AìA Ø©–ó Ø©ÃÅ");
		 ReadDataFile(125);
	 }
}

void SMorder::PrintUserData()
{
	 c_hclrscr();
	 c_hprintf("1.“A∂•ówãs:%-8s    2.¥a∑°ó°:%-8s   3.∑°üq:%-8s   4.¥q—°:%-8s\n\r", Grade[appU->stU.OK], appU->stU.ID, appU->stU.NAME, appU->stU.PASS );
	 c_hprintf("5.∏Â—¡:%-14s  6.´°´°:%-14s   7.∫Å£•ówù¢:%-14s\n\r", appU->stU.TELNO, appU->stU.BBNO, appU->stU.PEOPLENO);
	 c_hprintf("8.∂ÅÕe§Â—°:%-7s     9.∫Å≠°:%-50s", appU->stU.MAILNO, appU->stU.ADDRESS);
	 c_hprintf("10.∏ÒÆÅ:%4i(∏Ò)       11.ùA•I:%4i             12.Ø°àe∑e–ó:%4i(¶Ö)\n\r", appU->stU.Point, appU->stU.Level, appU->stU.TimeBank);
	 c_hprintf("13.êq∑eØ°àe:%4i(¶Ö)   14.îa∂Öàaìwú∑:%4i(KB)\n\n\r",appU->stU.LeftTime, appU->stU.DnableSize);
	 c_hprintf("15.ª¢ ∏w : %-30s\n\r",appU->stU.WORKPLACE);
	 c_hprintf("16.°A°°1 : %-50s\n\r", appU->stU.MEMO[0]);
	 c_hprintf("17.°A°°2 : %-50s\n\r", appU->stU.MEMO[1]);
	 c_hprintf("18.°A°°3 : %-50s\n\n\r", appU->stU.MEMO[2]);
	 c_hprintf("àa  ∑≥  Ø°  àb : %4i/%2i/%2i %2iØ°%2i¶Ö      ¡∑∏Û≠¢ : %5i(“A)\n\r", appU->stU.JoinTime.year, appU->stU.JoinTime.month, appU->stU.JoinTime.day, appU->stU.JoinTime.hour, appU->stU.JoinTime.min, appU->stU.LoginNo);
	 c_hprintf("¬Aãe ∏Û≠¢ Ø°àb : %4i/%2i/%2i %2iØ°%2i¶Ö\n\r", appU->stU.LoginTime.year, appU->stU.LoginTime.month, appU->stU.LoginTime.day, appU->stU.LoginTime.hour, appU->stU.LoginTime.min);
	 c_hprintf("¬Aãe π∑ûa Ø°àb : %4i/%2i/%2i %2iØ°%2i¶Ö\n\r", appU->stU.LogoutTime.year, appU->stU.LogoutTime.month, appU->stU.LogoutTime.day, appU->stU.LogoutTime.hour, appU->stU.LogoutTime.min);
	 c_hprintf("[àbπ∑—…ï∑]   âAØ°Ãe   ∏aûaØ©   ¥Ûù°óaú∑   îa∂Öù°óaú∑\n\r");
	 c_hprintf("             %4i“A   %4i“A    %5iKB      %5iKB\n\n\r", appU->stU.BbsAct, appU->stU.PdsAct, appU->stU.UpDataSize, appU->stU.DnDataSize);
	 c_hprintf("[¥|¨aúq B] [îa∑q¨aúq F,ENTER] [è{êë P] ÆÅ∏˜–i §Â—° : ");
}
void SMorder::FindWithName()
{
	int UserNo;
	char NAME[9];
	UserClass *fU;
	ReadDataFile(103); // input users id
	SetHanMode(true);
	c_hgetln(NAME,"",8);
	if (!strcmp(NAME,"")) { ReadDataFile(34); ReadDataFile(95); return; }// canceled.
	for (UserNo=1; UserNo<=MaxUserNo; UserNo++)
	{
		fU = new UserClass(UserNo);
		fU->ReadData();
		if ( !strcmp(NAME, fU->stU.NAME) )
		{
			AppUserData(UserNo);
		}
		delete fU;

	}
}
void SMorder::FindWithId()
{
	int UserNo;
	char ID[9];
	UserClass *fU;
	ReadDataFile(108); // input users id
	SetHanMode(false);
	c_hgetln(ID,"",8);
	if (!strcmp(ID,"")) { ReadDataFile(34); ReadDataFile(95); return; }// canceled.
	for (UserNo=1; UserNo<=MaxUserNo; UserNo++)
	{
		fU = new UserClass(UserNo);
		fU->ReadData();
		if ( !strcmp(ID, fU->stU.ID) )
		{
			AppUserData(UserNo);
		}
		delete fU;
	}
}
void SMorder::FindWithNumber()
{
	char numstr[6];
	ReadDataFile(123); // input user data.
	c_hgetln(numstr,"",5);
	if ( is_int(numstr) )  AppUserData(atoi(numstr));
}
void SMorder::AppUserData(int num)
{
	int ret=1;
	if ( (num >= 1) && (num <= MaxUserNo) )
	{
		while(ret)
		{
			bUpdated=0;
			ret = RealAppUserData(num);
			switch(ret)
			{
				case -1 : if (num > 1) --num;         break;
				case 1  : if (num < MaxUserNo) ++num; break;
			}
		}
	}
}
void SMorder::InputData(char* title, unsigned char* str, int len)
{
	c_hprintf("¨Åù°∂Ö %s : ",title);
	c_hgetln(temp_str,"", len);
	if ( strcmp(temp_str,"") )
	{
		strcpy(str, temp_str);
		bUpdated=1;
	}
}
void SMorder::InputData(char* title, int& var)
{
	c_hprintf("¨Åù°∂Ö %s : ",title);
	c_hgetln(temp_str,"", 4);
	if ( is_int(temp_str) )
	{
		var = atoi(temp_str);
		bUpdated=1;
	}
}
void SMorder::InputOK()
{
	int tOK;
	ReadDataFile(124);
	c_hgetln(temp_str,"",1);
	if ( is_int(temp_str) )
	{
		 tOK = atoi(temp_str);
		 if ( tOK >=1 && tOK <=8 )
		 {
			 appU->stU.OK = tOK-1;
			 bUpdated=1;
		 }
	}
}
int SMorder::RealAppUserData(int num)
{
	char instr[3],retcode;
	appU = new UserClass(num);
	appU->ReadData();
	while( 1 )
	{
		PrintUserData();
		SetHanMode(false);
		c_hgetln(instr,"P",2);
		switch( atoi(instr) )
		{
			case 1 : InputOK();
					 break;
			case 2 : SetHanMode(false);
					 InputData("¥a∑°ó°",appU->stU.ID,8);
					 break;
			case 3 : SetHanMode(true);
					 InputData("∑°üq",appU->stU.NAME,8);
					 break;
			case 4 : SetHanMode(false);
					 InputData("¥q—°",appU->stU.PASS,8);
					 break;
			case 5 : SetHanMode(true);
					 InputData("∏Â—¡§Â—°",appU->stU.TELNO,14);
					 break;
			case 6 : SetHanMode(true);
					 InputData("´°´°§Â—°",appU->stU.BBNO,14);
					 break;
			case 7 : InputData("∫Å£•ówù¢§Â—°",appU->stU.PEOPLENO,14);
					 break;
			case 8 : SetHanMode(false);
					 InputData("∂ÅÕe§Â—°",appU->stU.MAILNO,7);
					 break;
			case 9 : SetHanMode(true);
					 InputData("∫Å≠°",appU->stU.ADDRESS,50);
					 break;
			case 10: InputData("∏ÒÆÅ",appU->stU.Point);  break;
			case 11: InputData("ùA•I",appU->stU.Level);  break;
			case 12: InputData("Ø°àe∑e–ó ∏·¬Çú∑",appU->stU.TimeBank);  break;
			case 13: InputData("êq∑eØ°àe",appU->stU.LeftTime);  break;
			case 14: InputData("îa∂Öàaìwú∑",appU->stU.DnableSize);  break;
			case 15: SetHanMode(true);
					 InputData("ª¢∏w",appU->stU.WORKPLACE,30);
					 break;
			case 16: SetHanMode(true);
					 InputData("°A°° 1",appU->stU.MEMO[0],50);
					 break;
			case 17: SetHanMode(true);
					 InputData("°A°° 2",appU->stU.MEMO[1],50);
					 break;
			case 18: SetHanMode(true);
					 InputData("°A°° 3",appU->stU.MEMO[2],50);
					 break;
		}
		if ( !strcmp(instr,"P") || !strcmp(instr,"p") )
		{  retcode = 0;  break;  }
		if ( !strcmp(instr,"F") || !strcmp(instr,"f") || !strcmp(instr,"") )
		{  retcode = 1;  break;  }
		if ( !strcmp(instr,"B") || !strcmp(instr,"b") )
		{  retcode =-1;  break;  }
	}
	if (bUpdated) appU->SaveData();
	delete appU;

	return retcode;
}
void SMorder::AppUserData()
{
	 char instr[2];
	 do
	 {
		 ReadDataFile(122); // menu
		 SetHanMode(false);
		 c_hgetln(instr,"P",1);
		 switch( atoi(instr) )
		 {
			  case 1 : FindWithNumber();  break;
			  case 2 : FindWithName();  break;
			  case 3 : FindWithId();  break;
		 }
	 } while ( strcmp(instr,"P") && strcmp(instr,"p") );

}
void SMorder::ReindexUserData()
{
	 char ch;
	 int UserNo, nOK=0;
	 struct User_t stU;
	 ReadDataFile(126); // now starting reindexing userdata.
	 FILE *fIN = fopen(strcat2(InstDir,"\\USERDATA.DAT"),"rb");
	 if ( fIN == NULL ) halt("ERROR : Happend while reading User data");
	 FILE *fSource = tmpfile();
	 if ( fSource == NULL ) halt("ERROR : Happend while reading User data");
	 while ( ( ch=fgetc(fIN) ) != EOF )
	 {
		  fputc(ch,fSource);
	 }
	 fclose (fIN);
	 FILE *fReindex = fopen(strcat2(InstDir,"\\USERDATA.DAT"),"wb");
	 if ( fReindex == NULL ) halt("ERROR : Happend while reading User data");

	 fseek(fSource, 0L, SEEK_SET);
	 for (UserNo=1; UserNo<=MaxUserNo; UserNo++)
	 {
		fread(&stU, sizeof(struct User_t), 1, fSource);
		if (stU.OK != DELETED )
		{
			++nOK;
			fwrite(&stU, sizeof(struct User_t), 1, fReindex);
		}
	 }
	 MaxUserNo = nOK;
	 fclose (fSource);
	 fclose (fReindex);
}
void SMorder::BackupUserData()
{
	 ReadDataFile(127);
	 if (chdir(InstDir) == -1) halt("ERROR : Can't change to install directory for userdata backup.");
	 system("arj a userdata.bak userdata.dat > bak.tmp");
	 remove("BAK.TMP");
	 ReadDataFile(130);
}
void SMorder::RecoverUserData()
{

	 if (chdir(InstDir) == -1) halt("ERROR : Can't change to install directory for userdata recover.");
	 if (access("userdata.bak",0)==-1)  ReadDataFile(128);
	 else
	 {
		 ReadDataFile(131);
		 system("arj e -y userdata.bak > bak.tmp");
		 remove("BAK.TMP");
		 ReadDataFile(129);
	 }
}
void SMorder::MakeUserData2Txt(){}
//  reindex menu data of current directoy
void SMorder::ReindexMenuData(int type)
{
	 int nOK=0,MenuItem,MaxMenuItem;
	 char ch,oldfname[13],newfname[13];
	 struct MenuIndex_t MI;
	 if ( access("MENUDATA.IDX",0) == -1 ) return;
	 FILE *fIN = fopen("MENUDATA.IDX","rb");
	 if ( fIN == NULL ) halt("ERROR : Happend while reading User data");
	 FILE *fSource = tmpfile();
	 if ( fSource == NULL ) halt("ERROR : Happend while reading User data");
	 while ( ( ch=fgetc(fIN) ) != EOF )
	 {
		  fputc(ch,fSource);
	 }
	 fclose (fIN);

	 FILE *fReindex = fopen("MENUDATA.IDX","wb");
	 if ( fReindex == NULL ) halt("ERROR : Happend while reindexing Menu data");
	 /*
	 if ( type == RMAIL && access("MAIL.HD",0) != -1 )
	 {
		FILE *fHD=fopen("MAIL.HD","rb");
		if (fHD == NULL) halt("ERROR : Reindexing MENUDATA - Can't open MAIL.HD");
		fread(&MH, sizeof(MH), 1, fHD );
		fclose(fHD);
	 } */
	 fseek(fSource,0L,SEEK_END);
	 MaxMenuItem = ftell(fSource) / sizeof(MenuIndex_t);
	 fseek(fSource,0L,SEEK_SET);
	 for (MenuItem=1; MenuItem<=MaxMenuItem; MenuItem++)
	 {
		fread(&MI, sizeof(struct MenuIndex_t), 1, fSource);
		/*
		hprintf("\n\rMI.n = %i   nOK = %i    MI.alive = %i  MI.id=%s",MI.n,nOK,MI.alive,MI.id);
		getch();
		*/
		if (MI.alive == 0)
		{
			GetFileName(MI.n, oldfname);
			if (remove(oldfname)== -1) halt("ERROR : Reindexing - removing txt file");
			switch(type)
			{
				case PDS   : sprintf(oldfname,"%i.P_T",MI.n);
							 if (remove(oldfname)== -1) halt("ERROR : Reindexing - removing pt file");
							 break;
				//case RMAIL : sprintf(oldfname,"%i.MI",MI.n);
				//			 if (remove(oldfname)== -1) halt("ERROR : Reindexing - removing mi file");
			}
		}
		else
		{
			++nOK;
			if (MI.n != nOK)
			{
				GetFileName(MI.n, oldfname);
				GetFileName(nOK, newfname);
				if (rename(oldfname, newfname)==-1) halt("ERROR : Reindexing - renaming txt");
				switch(type)
				{
					 case PDS   : sprintf(oldfname,"%i.P_T",MI.n);
								  sprintf(newfname,"%i.P_T",nOK);
								  if (rename(oldfname,newfname)== -1) halt("ERROR : Reindexing - renaming pt");
								  break;
					 //case RMAIL : sprintf(oldfname,"%i.MI",MI.n);
					 //			  sprintf(newfname,"%i.MI",nOK);
					 //			  if (rename(oldfname,newfname)== -1) halt("ERROR : Reindexing - renaming mi");
					 //			  if (MH.end==MI.n) MH.end = nOK;
					 //			  if (MH.start==MI.n) MH.start = nOK;
				}
				MI.n = nOK;
			}
			fwrite(&MI, sizeof(struct MenuIndex_t), 1, fReindex);
		}
	 }
	 if (nOK==0) remove("MENUDATA.IDX");
	 fclose (fSource);
	 fclose (fReindex);
}
void SMorder::ReindexNowMenuData()
{
	 switch(MENU[nAcc].type)
	 {
		 case  OMAIL  :
		 case  BBS    :
		 case  PDS    :
		 case  NOTICE :
				c_hprintf("—e∏Å °AìA∑• %s∑Å ïA∑°»·üi ü°∑•ïBØa –aâVØsì°åa?",MENU[nAcc].title);

				if (AnswerIs('Y','N',false))
				{
					if (chdir(direc) == -1) halt("ERROR : Can't change to install directory for now menudata reindexing");
					ReindexMenuData(MENU[nAcc].type);
				}
				break;
		 default :  ReadDataFile(132);
	 }
}
void SMorder::ReindexAllMenuData()
{
	 int nMenu;
	 ReadDataFile(133);
	 if ( AnswerIs('Y','N',false) )
	 {
		 for (nMenu=1; nMenu<=MenuNo; nMenu++)
		 {
			 switch( MENU[nMenu-1].type )
			 {
				 case  BBS    :
				 case  PDS    :
				 case  NOTICE :
						/*if (MENU[nMenu-1].type == RMAIL)
						{
							if (chdir(InstDir) == -1) halt("ERROR : Can't change directory for all menudata reindexing.");
							if (chdir("MAIL") == -1) halt("ERROR : Can't change directory for mail menudata reindexing.");
						}
						else
						{ */
						if (chdir(InstDir) == -1) halt("ERROR : Can't change directory for all menudata reindexing-1.");
						//hprintf("%s\n\r",MENU[nMenu-1].index); getch();
						if (chdir(MENU[nMenu-1].index) == -1) halt("ERROR : Can't change directory for all menudata reindexing-2.");
						//}
						ReindexMenuData(MENU[nMenu-1].type);
						c_hprintf("[%i] %s(%s) ü°∑•ïBØa µ≈ûa\n\r", nMenu, MENU[nMenu-1].title, MENU[nMenu-1].index);
			 }
		 }
		 ReadDataFile(134);
	 }
}
void SMorder::BackupMenuData()
{
	 int MenuItem,ret,bFail=0;

	 if (chdir(InstDir) == -1) halt("ERROR : Can't change to install directory for userdata recover.");
	 remove ("MENUBAK.ARJ");
	 ReadDataFile(144);  //will you really backup?...
	 if (AnswerIs('Y','N',false))
	 {
		  ReadDataFile(146);  // backup now started...
		  ret = system("ARJ a -y MENUBAK.ARJ MENUDATA.DAT > BAK.TMP");
		  if (ret != 0)
		  {
				c_hprintf("MENUDATA.DAT §Ç¥Û Ø©ÃÅ\n\r");
				bFail = 1;
		  }
		  else c_hprintf("MENUDATA.DAT §Ç¥Û µ≈ûa\n\r");

		  for (MenuItem=1; MenuItem<=MenuNo; MenuItem++)
		  {
			   switch ( MENU[MenuItem-1].type )
			   {
					case BBS :
					case PDS :
					case NOTICE :
						sprintf(temp_str,"ARJ a -y MENUBAK.ARJ %s > BAK.TMP", MENU[MenuItem-1].index);
						ret = system(temp_str);
						if (ret != 0)
						{
							 c_hprintf("[%i] %s(%s) §Ç¥Û Ø©ÃÅ\n\r", MenuItem, MENU[MenuItem -1].title, MENU[MenuItem-1].index);
							 bFail = 1;
						}
						else c_hprintf("[%i] %s(%s) §Ç¥Û µ≈ûa\n\r", MenuItem, MENU[MenuItem -1].title, MENU[MenuItem-1].index);
			   }
		  }
		  remove("BAK.TMP");
		  if (bFail) ReadDataFile(148); // backup failed.
		  else ReadDataFile(149);  // successfully backuped.
	 }
}
void SMorder::RecoverMenuData()
{
	 int ret;

	 if (chdir(InstDir) == -1) halt("ERROR : Can't change to install directory for userdata recover.");

	 if ( access("MENUBAK.ARJ" ,0) == -1 )
	 {
		  ReadDataFile(152); // no backup data
		  return;
	 }
	 ReadDataFile(147); //starting ..
	 ret = system("ARJ x -y MENUBAK.ARJ > BAK.TMP");
	 if (ret != 0) ReadDataFile(150); // recover failed.
	 else
	 {
		 remove("BAK.TMP");
		 ReadDataFile(151); // recover successed.
	 }
}
void SMorder::RemoteDosShell()
{
	 class RDS *pRDS;
	 pRDS = new RDS();
	 pRDS->run();
	 delete pRDS;
}
//--------------------------------------------------------------------------
//
//               remote dos shell  object
//--------------------------------------------------------------------------

RDS::RDS()
{
	 hclrscr();
	 rCOLOR.push();
	 hclrscr();
	 hsetcolor(7);
	 ReadDataFile(135);// doing mighty host remote dos shell.
	 gotoxy(1,2); // for Dos error
}
RDS::~RDS()
{
	 rCOLOR.pop();
	 hclrscr();
	 STAT_display();
}
void RDS::PrintPrompt()
{

	 char Prompt[100];
	 getcwd(Prompt,99);
	 strcat(Prompt,">");
	 c_hputs(Prompt);
}
void RDS::ScrFile2Comm()
{
	 char ch;
	 FILE *fScr = fopen(strcat2(InstDir,"\\scr.tmp"),"rt");
	 if (fScr==NULL)
	 {
		 c_hputs("Bad command or file name\n\n\r");
		 gotoxy(1,2);
	 }
	 else
	 {
		 while( (ch=fgetc(fScr)) != EOF )
		 {
			 c_hputch(ch);
			 if (ch=='\n') c_hputch('\r');
		 }
		 if (remove(strcat2(InstDir,"\\scr.tmp"))==-1) halt("ERROR : logic error - rds");
		 fclose(fScr);
	 }
}
int RDS::PossibleRun()
{
	int i,ret = 1;
	char *NoRun[] = { "NCD" ,"ncd" ,"M" ,"m", "FF", "ff", "FILEFIND",
					  "filefind", "HTT", "htt", "p", "P", "PARK", "park",
					  "PCT","pct","NCC", "HWP", "hwp", "WIN", "win", "I",
					  "i", "SETUP", "setup" };
	for (i=1; i<=25; i++)
	{
		if (!strcmp(OrderStr,NoRun[i-1]))
		{
			ReadDataFile(136); // if you use this
			ret = 0;
			break;
		}
	}
	if (!strcmp(OrderStr,"")) ret=0;
	return ret;
}
void RDS::run()
{
	 SetHanMode(false);
	 do
	 {
		 PrintPrompt();
		 c_hgetln(OrderStr,"EXIT", 256);
		 if ( PossibleRun() )
		 {
			sprintf(temp_str,"%s > %s\\scr.tmp", OrderStr, InstDir);
			system(temp_str);
			ScrFile2Comm();
		 }
	 } while( strcmp(OrderStr,"EXIT") && strcmp(OrderStr,"exit") );
}
#define FRAMEWIN &framewin
CWndFrame::CWndFrame(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep)
{
	 x1=x1p;
	 y1=y1p;
	 x2=x2p;
	 y2=y2p;
	 bkcol = bk;
	 title=titlep;
	 hsetwindow(FRAMEWIN, x1, y1, x2, y2, bk, fr, DEFWIN);
	 wsetbkcolor(FRAMEWIN,bk);
	 wsetcolor(FRAMEWIN,fr);
	 //wregisterhanfont(STATWIN, HAN8GD1);
	 wallowautoscroll(FRAMEWIN, true);
}
#define TitleBarColor 1
void CWndFrame::Run()
{
	 rCOLOR.push();
	 htempwindow(1,1,hgetmaxax(), hgetmaxay()-1);
	 SCR.push(ax2apx(x1)-2, ay2apy(y1-1)-5, ax2apx(x2)+CS+2, ay2apy(y2)+LS+2);
	 box3d(ax2apx(x1)-2, ay2apy(y1-1)-5, ax2apx(x2)+CS+2, ay2apy(y2)+LS+2, bkcol, 15, 8);
	 box3d(ax2apx(x1)-1, ay2apy(y1-1)-4, ax2apx(x2)+CS+1, ay2apy(y1)-2, TitleBarColor,15,8);
	 box3d(ax2apx(x1)-1, ay2apy(y1)-1, ax2apx(x2)+CS+1, ay2apy(y2)+LS+1, bkcol, 8,15);
	 hsetbkcolor(TitleBarColor);
	 hsetcolor(15);
	 hputspxy(ax2apx(x1+(x2-x1-strlen(title))/2-1), ay2apy(y1-1)+-3, title);
	 bDontSendComm = 1;
	 bFrameExist = 1;
	 htempcurwindow(FRAMEWIN);
	 hclrscr();
	 DoSpecial();
	 hclrscr();
	 hlastcurwindow();
	 bFrameExist = 0;
	 bDontSendComm = 0;
	 SCR.pop();
	 hlastwindow();
	 rCOLOR.pop();
}
void CSMWin::DoSpecial()
{
	  class SMorder *SMO;
	  SMO=new SMorder();
	  SMO->run();
	  delete SMO;
}
CSMWin::CSMWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep)	: CWndFrame(x1p, y1p, x2p, y2p, bk, fr, titlep)
{}

void CLogoWin::DoSpecial()
{
	  // †a∑°À° —°ØaÀa ≠°àÅ∑Å Ø°∏b
	  bDontSendComm=1;
	  for (int DataNum=198; DataNum<=232; DataNum++)
	  {
			ReadDataFile(DataNum);
			delay(500);
			if (kbhit()) { getch(); break; }
	  }
	  bDontSendComm=0;
	  delay(1000);
}
CLogoWin::CLogoWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep)	: CWndFrame(x1p, y1p, x2p, y2p, bk, fr, titlep)
{}
/*
void CEmulWin::DoSpecial()
{
	  char ch;
	  ReadDataFile(271); // symple emulater.
	  do
	  {
			while( SioRxQue(port) )  hputch( SioGetc(port, 18) );

	  }
}
CEmulWin::CEmulWin(int x1p, int y1p, int x2p, int y2p, int bk, int fr, char* titlep)	: CWndFrame(x1p, y1p, x2p, y2p, bk, fr, titlep)
{}*/
