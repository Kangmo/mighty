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
//   "PLEASE GIVE ME YOUR HOST SOURCE" CAN HAVE THIS SOURCE.               //
//                                                                         //
//   ANYONE WHO GIVES THIS SOURCE TO OTHERS,                               //
//   ANYONE WHO SELLS TRANSFORMED PROGRAM BY COMPILING THIS SOURCE,        //
//   ANYONE WHO SELLS THIS SOURCE,                                         //
//   ANYONE WHO USES THIS PROGRAM AND THIS SOURCE FOR COMMECIAL PURPOSE    //
//                                                                         //
//   WILL BE PERISHED BY COPY RIGHT LAW.  1995.11.1 KIM KANGMO             //
//                                                                         //
//-------------------------------------------------------------------------//
char option;
int gx=-1,gy=-1,nowx,nowy;
int bLight=0, bBold=0, bUnder=0, bReverse=0, bUpper=0, bLower=0, bAnsiSaved=0;

struct ansibuf_t
{
	int cx,cy,col,bkcol;
	bool bLight,bBold,bUnder,bReverse,bUpper,bLower;
}AnsiBuf;

void InitAnsi()
{
	option= escstep = 0;
}
void mcode_run(int param)
{
	  switch (param) {
	  case 0:
			  hnormattr();
			  registerauxfont(NULL);
			  bLight = false;
			  bBold = false;
			  bUnder = false;
			  bReverse = false;
			  bUpper = false;
			  bLower = false;
			  break;
	  case 1:
			  bLight = true;
			  bBold = true;
			  hsetbold(true);
			  break;
	  case 4:
			  bUnder = true;
			  hsetunder(true);
			  break;
	  case 7:
			  bReverse = true;
			  hsetreverse(true);
			  break;
	  case 22:
			  bLight=false;
			  bBold=false;
			  hsetbold(false);
			  break;
	  case 24:
			  bUnder=false;
			  hsetunder(false);
			  break;
	  case 27:
			  bReverse=false;
			  hsetreverse(false);
			  break;


	  case 30:
			  if (bLight)
			  {
				  hsetcolor(8);
				  setcolor(8);
			  }
			  else
			  {

				  hsetcolor(0);
				  setcolor(0);
			  }
			  break;
	  case 31:
			  if (bLight)
			  {
				  hsetcolor(12);
				  setcolor(12);
			  }
			  else
			  {

				  hsetcolor(4);
				  setcolor(4);
			  }
			  break;
	  case 32:
			  if (bLight)
			  {
				  hsetcolor(10);
				  setcolor(10);
			  }
			  else
			  {

				  hsetcolor(2);
				  setcolor(2);
			  }
			  break;
	  case 33:
			  if (bLight)
			  {
				  hsetcolor(14);
				  setcolor(14);
			  }
			  else
			  {
				  hsetcolor(6);
				  setcolor(6);
			  }
			  break;
	  case 34:
			  if (bLight)
			  {
				  hsetcolor(9);
				  setcolor(9);
			  }
			  else
			  {

				  hsetcolor(1);
				  setcolor(1);
			  }
			  break;
	  case 35:
			  if (bLight)
			  {
				  hsetcolor(13);
				  setcolor(13);
			  }
			  else
			  {

				  hsetcolor(5);
				  setcolor(5);
			  }
			  break;
	  case 36:
			  if (bLight)
			  {
				  hsetcolor(11);
				  setcolor(11);
			  }
			  else
			  {

				  hsetcolor(3);
				  setcolor(3);
			  }
			  break;
	  case 37:
			  if (bLight)
			  {
				  hsetcolor(15);
				  setcolor(15);
			  }
			  else
			  {
				  hsetcolor(7);
				  setcolor(7);
			  }
			  break;
	  case 40:
			  if (bLight) hsetbkcolor(8);
			  else hsetbkcolor(0);
			  break;
	  case 41:
			  if (bLight) hsetbkcolor(12);
			  else hsetbkcolor(4);
			  break;
	  case 42:
			  if (bLight) hsetbkcolor(10);
			  else hsetbkcolor(2);
			  break;
	  case 43:
			  if (bLight) hsetbkcolor(14);
			  else hsetbkcolor(6);
			  break;
	  case 44:
			  if (bLight) hsetbkcolor(9);
			  else hsetbkcolor(1);
			  break;
	  case 45:
			  if (bLight) hsetbkcolor(13);
			  else hsetbkcolor(5);
			  break;
	  case 46:
			  if (bLight) hsetbkcolor(11);
			  else hsetbkcolor(3);
			  break;
	  case 47:
			  if (bLight) hsetbkcolor(15);
			  else hsetbkcolor(7);
			  break;
	  case 48: // lower letter
			  bLower = true;
			  bUpper = false;
			  registerauxfont(ENGAUX4);
			  break;
	  case 49: // upper letter
			  bUpper = true;
			  bLower = false;
			  registerauxfont(ENGAUX3);
			  break;
	  }
}
void execute_vt100(int cmd, int param1, int param2, int param3)
{
		int i,j,buf;
//		hprintf("cmd->%c, p1->%i, p2->%i, p3->%i, opt ->%c\n",cmd,param1,param2,param3,option);
//		getch();
//		return;
		switch (cmd) {
		case 'a':
				if ( (param1 <0) || (param2<0) ) break;
				if ( param3 <=0 ) param3=1;
				ellipse(gx, gy, -90 - param2*6, -90 - param1*6, param3, param3);
				break;
		case 'A':
				if (param1 <= 0) param1=1;
				hgotoxy(hwherex(), hwherey() - param1);
				break;
		case 'B':
				if (param1 <= 0) param1=1;
				hgotoxy(hwherex(), hwherey() + param1);
				break;
		case 'b':
				if ( (param1 < 0) || (param2 < 0) ) break;
				if ( gx == -1 || gy == -1) break;
				switch( option )
				{
					case 0   :  rectangle( gx-param1,  gy -param2,
											gx+param1,  gy +param2);
								break;
					case '?' :  setfillstyle(1,hgetbkcolor());
								bar( gx-param1,  gy -param2,
									 gx+param1,  gy +param2);
								break;
					case '>' :  buf = getcolor();
								setcolor(hgetbkcolor());
								rectangle( gx-param1,  gy -param2,
											gx+param1,  gy +param2);
								setcolor( buf );
								break;

					case '=' :
								if (param3 == -1) setfillstyle(1,getcolor());
								else setfillstyle(1,param3);
								bar( gx-param1,  gy -param2,
									  gx+param1,  gy +param2);
								break;
				}
				break;
		case 'C':
				if (param1 <= 0) param1 = 1;
				hgotoxy(hwherex() + param1, hwherey());
				break;
		case 'c':
				if ( (param1 < 0) || (param2 < 0) ) break;
				if ( gx == -1 || gy == -1) break;
				ellipse(gx,gy,0,360,param1/2,param2/2);
				break;
		case 'D':
				if (param1 <= 0) param1=1;
				hgotoxy(hwherex() - param1, hwherey());
				break;
		case 'F':
				if (option == '=')
				{
					  if ( param1 < 0 ) param1=0;
					  hsetcolor(param1);
					  setcolor(param1);
				}
				break;
		case 'G':
				if ( option == '=' )
				{
					  if ( param1 < 0 ) param1=0;
					  hsetbkcolor(param1);

				}
				else if ( param2 != -1)
				{
					  if ( param1 <=0) param1 =1;
					  if ( param2 <=0) param2 =1;
					  nowx = hwherex();
					  nowy = hwherey();

					  rectangle(ax2apx(nowx) + CS/2, ay2apy(nowy) + LS/2,
									ax2apx(nowx+param1-1) + CS/2, ay2apy(nowy+param2-1) +LS/2);
					  rectangle(ax2apx(nowx) + CS/2-1, ay2apy(nowy) + LS/2,
									ax2apx(nowx+param1-1) + CS/2-1, ay2apy(nowy+param2-1) +LS/2);
				}
				break;
		case 'g':
				if ( (param1 < 0) || (param2 < 0) ||
					 (param1 > hgetmaxpx() ) || (param2 > hgetmaxpy()) ) gy=gx=-1;
				else
				{
					gx=param1;
					gy=param2;
				}
				break;
		case 'f':
		case 'H':
				if ( param1 <= 0) param1=1;
				if ( param2 <= 0) param2=1;
				hgotoxy(param2, param1);
				break;
		case 'i':
				if( param1 < 0 || param2 <0 ) break;
				switch( option )
				{
					 case '?':
					 case '=':
					 case  0 :  if (param3 == -1) line(gx,gy,param1,param2);
									{
										buf = getcolor();
										setcolor(param3);
										line(gx,gy,param1,param2);
										setcolor(buf);
									}
									break;
					 case '>':  buf = getcolor();
									setcolor(hgetbkcolor());
									line(gx,gy,param1,param2);
									setcolor(buf);
									break;
				}

		case 'K':
				if (param1 == -1)
				{
						hallowautoscroll(false);
						nowx = hwherex();
						nowy = hwherey();
						for (i = nowx; i <= hgetmaxx(); i++) eputch(' ');
						hgotoxy(nowx,nowy);
						hallowautoscroll(true);
						break;
				}
				break;
		case 'J':
				switch (param1) {
				case -1:
				case 0:
						hallowautoscroll(false);
						for (i = hwherex(); i <= hgetmaxx(); i++)
								hprintfxy(i, hwherey(), " ");
						for (j = hwherey(); j <= hgetmaxy(); j++)
							 for (i = 1; i <= hgetmaxx(); i++)
								hprintfxy(i, j, " ");
						hallowautoscroll(true);
						break;
				case 1:
						hallowautoscroll(false);
						for (i = 1; i <= hwherex(); i++)
								hprintfxy(i, hwherey(), " ");
						hallowautoscroll(true);
						break;
				case 2:
						hclrscr();
						break;
				}
				break;
		case 'L':
				if (param1 <= 0) param1=1;

				if ( param1 >= hgetmaxy()-hwherey()+1)
				{
					  ScrollTime = onANSI;
					  hbackscrollxy(1, hwherey(), hgetmaxx(), hgetmaxy(), (hgetmaxy()-hwherey()+1)*LS-1 );
					  ScrollTime = onNORMAL;
					  buf = getcolor();
					  setcolor(hgetbkcolor());
					  line(ax2apx(1),ay2apy(hgetmaxy())+LS-1,ax2apx(hgetmaxx())+LS-1,ay2apy(hgetmaxy())+LS-1);
					  setcolor(buf);
				}
				else
				{
					  ScrollTime = onANSI;
					  hbackscrollxy(1, hwherey(), hgetmaxx(), hgetmaxy(), param1*LS );
					  ScrollTime = onNORMAL;
				}
				break;
		case 'M':
				if (param1 <= 0) param1=1;

				if ( param1 >= hgetmaxy()-hwherey()+1)
				{
					  ScrollTime = onANSI;
					  hscrollxy(1, hwherey(), hgetmaxx(), hgetmaxy(), (hgetmaxy()-hwherey()+1)*LS-1 );
					  ScrollTime = onNORMAL;
					  buf = getcolor();
					  setcolor(hgetbkcolor());
					  line(ax2apx(1),ay2apy(hwherey()),ax2apx(hgetmaxx())+LS-1,ay2apy(hwherey()));
					  setcolor(buf);
				}
				else
				{
					  ScrollTime = onANSI;
					  hscrollxy(1, hwherey(), hgetmaxx(), hgetmaxy(), param1*LS );
					  ScrollTime = onNORMAL;
				}
				break;
		case 'm':
				mcode_run(param1);
				mcode_run(param2);
				mcode_run(param3);
				break;
		case 'O':
				if (param1 < 0) break;
				nowx = hwherex();
				nowy = hwherey();
				switch (param1)
				{
					case 0 : line(ax2apx(nowx)+CS/2, ay2apy(nowy)+LS/2,
									  ax2apx(nowx+param2-1)+CS/2, ay2apy(nowy)+LS/2);
								break;
					case 1 : line(ax2apx(nowx)+CS/2, ay2apy(nowy)+LS/2,
									  ax2apx(nowx)+CS/2, ay2apy(nowy+param2-1)+LS/2);
								line(ax2apx(nowx)+CS/2-1, ay2apy(nowy)+LS/2,
									  ax2apx(nowx)+CS/2-1, ay2apy(nowy+param2-1)+LS/2);
								break;
				}
				break;
		case 'X':
		case 'P':
				if (param1 <= 0) param1=1;
				hallowautoscroll(false);
				nowx = hwherex();
				nowy = hwherey();
				if (param1 > hgetmaxx()-nowx) param1 = hgetmaxx()-nowx+1;
				if (hgetmaxx()-nowx >= param1)
				{
					long size = imagesize(ax2apx(nowx+param1), ay2apy(nowy), ax2apx(hgetmaxx())+CS-1,ay2py(nowy)+LS-1);
					char far* buffer=(char far*)farmalloc(size);
					hgetimage(ax2apx(nowx+param1), ay2apy(nowy), ax2apx(hgetmaxx())+CS-1,ay2py(nowy)+LS-1, buffer);
					hputimage(ax2apx(nowx), ay2apy(nowy),buffer);
					farfree(buffer);
				}
				hgotoxy(hgetmaxx()-param1+1,nowy);
				for (i = hgetmaxx()-param1+1; i <=hgetmaxx(); i++) eputch(' ');
				hgotoxy(nowx,nowy);
				hallowautoscroll(true);

				break;

		case 'p':
				if ( (param1 < 0) || (param1 > hgetmaxpx()) ) break;
				putpixel(param1, param2, getcolor());
				break;
		case '@':
				if (param1 <= 0) param1=1;

				hallowautoscroll(false);
				nowx=hwherex();
				nowy=hwherey();
				if (nowx <= hgetmaxx() - param1)
				{
					long size = imagesize(ax2apx(nowx), ay2apy(nowy), ax2apx(hgetmaxx()-param1)+CS-1,ay2py(nowy)+LS-1);
					char far* buffer=(char far*)malloc(size);
					hgetimage(ax2apx(nowx), ay2apy(nowy), ax2apx(hgetmaxx()-param1)+CS-1,ay2py(nowy)+LS-1,buffer);
					hputimage(ax2apx(nowx+param1), ay2apy(nowy), buffer);
					farfree(buffer);
				}
				for (i = nowx; i <= nowx+param1-1; i++)
				{
					if ( i > hgetmaxx() ) break;
					eputch(' ');
				}

				hgotoxy(nowx,nowy);
				hallowautoscroll(true);
				break;
		case 'r':
				if ( (param1 < 1) || (param1 > hgetmaxy()) ) return;
				if ( (param2 < 1) || (param2 > hgetmaxy()) ) return;
				if ( param1 > param2 ) return;
				if ( param3 < 0) param3 =1;

				if ( param3 >= param2-param1+1)
				{
					  ScrollTime = onANSI;
					  hscrollxy(1, param1, hgetmaxx(), param2, (param2-param1+1)*LS-1);
					  ScrollTime = onNORMAL;
					  buf = getcolor();
					  setcolor(hgetbkcolor());
					  line(ax2apx(1),ay2apy(param1),ax2apx(hgetmaxx())+LS-1,ay2apy(param1));
					  setcolor(buf);
				}
				else
				{
					  ScrollTime = onANSI;
					  hscrollxy(1, param1, hgetmaxx(), param2, param3*LS);
					  ScrollTime = onNORMAL;
				}
				break;
		case 's':
				if (param1==-1 )
				{
					AnsiBuf.cx = hwherex();
					AnsiBuf.cy = hwherey();
					AnsiBuf.col = hgetcolor();
					AnsiBuf.bkcol = hgetbkcolor();
					AnsiBuf.bLight = bLight;
					AnsiBuf.bBold = bBold;
					AnsiBuf.bUnder = bUnder;
					AnsiBuf.bReverse = bReverse;
					AnsiBuf.bLower = bLower;
					AnsiBuf.bUpper = bUpper;
					bAnsiSaved = 1;
				}
				break;
		case 'u':
				if (param1==-1 && bAnsiSaved )
				{
					hgotoxy(AnsiBuf.cx, AnsiBuf.cy);
					hsetcolor(AnsiBuf.col);
					setcolor(AnsiBuf.col);
					hsetbkcolor(AnsiBuf.bkcol);
					setbkcolor(AnsiBuf.bkcol);
					bLight = AnsiBuf.bLight;
					hsetbold( bBold = AnsiBuf.bBold );
					hsetunder( bUnder = AnsiBuf.bUnder );
					hsetreverse( bReverse = AnsiBuf.bReverse );
					if ( bUpper = AnsiBuf.bUpper ) registerauxfont(ENGAUX3);
					if ( bLower = AnsiBuf.bLower ) registerauxfont(ENGAUX4);
					if ( !bUpper && !bLower ) registerauxfont(NULL);
				}
				break;
		case 'z':
				if ( (param1 <0) || (param2<0) ) break;
				if ( param3 <=0 ) param3=1;
				ellipse(gx, gy, -90 + param1*6, -90 + param2*6, param3, param3);
				break;
	}
}

void process_vt100(int rc)
{
		static char param1[3 + 1], param2[3 + 1], param3[ 3 + 1];
		static int param1ptr = 0, param2ptr = 0, param3ptr = 0;

		switch (escstep) {
		case 0:
				if (rc == ESC) escstep++;
				break;
		case 1:
				if (rc == '[') escstep++;
				else InitAnsi();
				param2ptr = param1ptr = 0;
				break;
		case 2:
				if (rc=='=')  { option=rc; break; }
				if (rc=='>')  { option=rc; break; }
				if (rc=='?')  { option=rc; break; }
				if (isdigit(rc)) {
						if (param1ptr < 3) param1[param1ptr++] = rc;
						else InitAnsi();
						break;
				}
				escstep++;
				param1[param1ptr] = '\0';
		case 3:
				if (rc == ';') {
						escstep++;
						break;
				}
				escstep++;
		case 4:
				if (isdigit(rc)) {
						if (param2ptr < 3) param2[param2ptr++] = rc;
						else InitAnsi();
						break;
				}
				escstep++;
				param2[param2ptr] = '\0';
		case 5:
				if (rc == ';')
				{
					 escstep++;
					 break;
				}
				else
				{
					 if (!isalpha(rc) && rc != '@') break;
					 execute_vt100(rc, (param1ptr == 0) ? -1 : atoi(param1),
										(param2ptr == 0) ? -1 : atoi(param2),
										-1 );
					 InitAnsi();
					 break;
				}
		case 6:
				if (isdigit(rc)) {
						if (param3ptr < 3) param3[param3ptr++] = rc;
						else InitAnsi();
						break;
				}
				escstep++;
				param3[param3ptr] = '\0';
		case 7:
				if (!isalpha(rc)) break;
				execute_vt100(rc, (param1ptr == 0) ? -1 : atoi(param1),
								  (param2ptr == 0) ? -1 : atoi(param2),
								  (param3ptr == 0) ? -1 : atoi(param3) );
				InitAnsi();
		}
}


