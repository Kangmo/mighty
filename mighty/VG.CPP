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
//   WILL BE PERISHED BY COPY RIGHT LAW.      1995.2.3 KIM KANGMO          //
//                                                                         //
//-------------------------------------------------------------------------//

/* Ansi Code ---> 	*/
#include "headers.h"
#include <bios.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include <stdarg.h>
#include <process.h>
#include <stdlib.h>
#include <alloc.h>
#include <dos.h>
#define SCRX 15
#define SCRY 10
#define SMX 10
#define SMY 4
#define MBC WLIGHTGREEN
#define MBKC 0
#define GABX 4
#define MLINES 24
#define MAXX 7
#define SMEY 9
#define SMEX 40
#define NCDLINECOLOR WDARKGRAY
#define UPBARSTARTY 44
#define DNBARSTARTY 435
#define FS 127
#define CANCEL  -1
#define NOERR    0

void EditMenu(void);

//----------------------------------------------------------------------
//                MENU  MAKE   PART
int no=0, MaxNo = 0;

void MenuScreenInit()
{
	c_hprintf("[=%iG", MBKC);
	c_hclrscr();
	c_hprintf("\n\r    †a∑°À° —°ØaÀa ver 1.0R  °AìA ∑°ï∑ã°        NUMLOCK ∑i íâú·∫Å≠A∂a\n\r");
	c_hprintf("        —¡¨iŒa«° : °AìA∑°ï∑        µE»· : âi∏˜         ¬·≠° : P");
	c_hprintf("[=9F[%i;%iH[%i;%iG[%i;%iH[%i;%iG",1,1,80,SMY,SMY,1,80,30-SMY);
}

void PrintBar(int num, int c)
{

	 int tempbkcolor,tempcolor;
	 int Mx = SMX + (MENU[num-1].X - 1) * GABX;
	 int My = SMY + (num % MLINES);
		 if (num % MLINES == 0) My += MLINES;
	 tempbkcolor = hgetbkcolor();
	 tempcolor = hgetcolor();
	 c_hgotoxy (Mx,My);
	 c_hprintf("[=%iG",c);
	 if (c==MBC) {
			 if (MENU[num-1].run != 0)
				 c_hprintf( "[=0F[%i]",MENU[num-1].run );
	 }
	 else
	 {
			 if (MENU[num-1].run != 0)
				 c_hprintf( "[=9F[%i][=%iF",MENU[num-1].run,MENU[num-1].color==MBKC?3:MENU[num-1].color);
	 }
	 c_hputs(MENU[num-1].title);
	 c_hprintf("[=%iF[=%iG",tempcolor,tempbkcolor);
}
void PrintHead(int num)
{
	 int Mx = SMX + (MENU[num-1].X - 1) * GABX;
	 int My = SMY + (num % MLINES);
		 if (num % MLINES == 0) My += MLINES;
	 c_hprintf("[=%iG[=%iF", MBKC, NCDLINECOLOR );
	 if (MENU[num-1].f2 ) { c_hgotoxy( SMX+GABX-2, My ); c_hputs("‘∫"); }  // |;
	 if (MENU[num-1].f3 ) { c_hgotoxy( SMX+2*GABX-2, My ); c_hputs("‘∫"); }
	 if (MENU[num-1].f4 ) { c_hgotoxy( SMX+3*GABX-2, My ); c_hputs("‘∫"); }
	 if (MENU[num-1].f5 ) { c_hgotoxy( SMX+4*GABX-2, My ); c_hputs("‘∫"); }
	 if (MENU[num-1].f6 ) { c_hgotoxy( SMX+5*GABX-2, My ); c_hputs("‘∫"); }

	 // rectangle ansi code.
	 switch (MENU[num-1].head) {
		 case 0 : break;
		 case 1 : c_hgotoxy( Mx-2, My);
					 c_hputs("‘Ã");  // |-
					 break;

		 case 2 : c_hgotoxy( Mx-2, My);
					 c_hputs("‘»"); // |_
					 break;
	 }
}
void PrintMenu( int start )
{

	 int end;
	 if (MaxNo == 0) return;
	 if (MaxNo - start < MLINES ) end = MaxNo;
	 else end = start + MLINES -1 ;
	 MenuScreenInit();
	 for (int i = start; i <= end ;i++ )
	 {
		  PrintHead(i);
		  PrintBar(i,MBKC);
	 }
}
void UpArr()
{
	if ( no <= 1 ) return;
	no--;

	if ( (( no % MLINES ) == 0 ) && ( no >= MLINES ) )
	{
		 PrintMenu( no - MLINES + 1 );
		 PrintBar( no, MBC);
	}
	else {
				PrintBar(no+1,MBKC);
				PrintBar(no,MBC);
			 }
}
void DnArr()
{
	if ( no >= MaxNo )  return;
	no++;

	if ( ((no -1) % MLINES ) == 0 ) {
		 PrintMenu( no );
		 PrintBar( no, MBC);
	}
	else {
				PrintBar(no-1,MBKC);
				PrintBar(no,MBC);
			 }

}
int count=0;
int VG()
{
	int ch;
	int exitcode;
	MaxNo = MenuNo;
	no = 1;
	c_hputs("[s");
	MenuScreenInit();
	c_hprintf("[=%iF",NCDLINECOLOR);
	PrintMenu(1);
	PrintBar(no,MBC);
	int endroutine = 0;
	while ( endroutine == 0 )
		if ( kbhit() || SioRxQue(port) ) {
			if (SioRxQue(port)) ch=SioGetc(port, 18);
			else if (kbhit()) ch=getch();
			switch(ch) {
				case 0 :
							ch = getch();
							switch(ch) {
								case 72 : UpArr();  break;
								case 80 : DnArr();
							}
							break;
				case '4' :
				case '8' :  UpArr();
								break;
				case '6' :
				case '2' :  DnArr();
								break;
				case 13  :  endroutine=1;
								exitcode=no;
								break;
				case  27 :
				case 'P' :
				case 'p' :  endroutine = 1;
								exitcode=-1;
								break;
			}
		} else if (!bLocal && !SioDCD(port)) exitcode=-1;
		c_hputs("[u");
		return exitcode;
}
