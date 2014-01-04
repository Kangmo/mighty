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
//   WILL BE PERISHED BY COPY RIGHT LAW.     1995.11.1 KIM KANGMO          //
//                                                                         //
//-------------------------------------------------------------------------//
void box3d2(int x1, int y1, int x2, int y2, int c1, int c2)
{
	 box3d( x1-10, y1-10, x2+10, y2+10, c2, 15, 8);
	 box3d( x1-1, y1-1, x2+1, y2+1, 0, 8, 15);
	 box3d( x1, y1, x2, y2, c1, 15, 8);
}

int StdMsg(int x1, int y1, char *title[10])
{
		int max_X=0,size_Y,i;
		rCOLOR.push();
		htempwindow(1,1,80,30);

		for (i=0; i<10; i++)
		{
			if ( !strcmp(title[i],"") ) break;
			if ( max_X < strlen(title[i]) ) max_X = strlen(title[i]);
			size_Y = i;
		}
		if ( SCR.push(x1-6, y1-6, x1+max_X * _CW->charspace + 32,
			 y1 + (size_Y + 1)* _CW->linespace + 32) != NOERR ) return ERR;
		box3d(x1, y1, x1+max_X * _CW->charspace + 32,
					y1 + (size_Y +1 ) * _CW->linespace + 32, 0,0,0);
		box3d(x1-6, y1-6, x1+max_X * _CW->charspace + 26,
					y1 + (size_Y +1 ) * _CW->linespace + 26, 7,15,8);
		box3d(x1, y1, x1+max_X * _CW->charspace + 20,
					y1 + (size_Y +1 ) * _CW->linespace + 20, 1,8,15);
		box3d(x1+1, y1+1, x1+max_X * _CW->charspace + 19,
					y1 + (size_Y +1 ) * _CW->linespace + 19, 1,15,8);
		hsetcolor(10);
		hsetbkcolor(1);
		for (i=0; i<= size_Y; i++)
		{
				 hputspxy( x1+10+(max_X-strlen(title[i]))*_CW->charspace/2,
									 y1+10 + i*_CW->linespace, title[i]);
		}
		hlastwindow();
		rCOLOR.pop();
		return NOERR;
}

int BoxGetData(int x1, int y1, unsigned char *data, const char *picture)
{
		int ret;
		rCOLOR.push();
		htempwindow(1,1,80,30);

		if ( SCR.push(ax2apx(x1)-16, ay2apy(y1)-16,
				 ax2apx(x1+ strlen(picture))+22, ay2apy(y1+1)+ 22) != NOERR )
				 return ERR;
		box3d(ax2apx(x1)-10, ay2apy(y1)-10, ax2apx(x1+ strlen(picture))+22,
					ay2apy(y1+1)+ 22, 0,0,0);
		box3d(ax2apx(x1)-16, ay2apy(y1)-16, ax2apx(x1+ strlen(picture))+16,
					ay2apy(y1+1)+ 16, 7,15,8);
		box3d(ax2apx(x1)-10, ay2apy(y1)-10, ax2apx(x1+ strlen(picture))+10,
					ay2apy(y1+1)+ 10, 1,8,15);
		box3d(ax2apx(x1)-11, ay2apy(y1)-11, ax2apx(x1+ strlen(picture))+9,
					ay2apy(y1+1)+ 9, 1,15,8);
		hsetcolor(14);
		hsetbkcolor(1);
		hgotoxy (x1,y1);
		ret = hgetdata(data, picture);
		hlastwindow();
		rCOLOR.pop();
		if (ret == -1) return CANCEL;
		else return NOERR;
}

int ButtonBox(int x1, int y1, char *title[10], char *button[4], char& ret)
{
		int max_X=0,size_Y,i,ch,buttNo,sum[4],pgab=_CW->charspace*2;
		int exitcode=0,count=0,color;
		char temp;
		temp = ret;
		rCOLOR.push();
		htempwindow(1,1,80,30);

		for (i=0; i<10; i++)
		{
			if ( !strcmp(title[i],"") ) break;
			if ( max_X < strlen(title[i]) ) max_X = strlen(title[i]);
			size_Y = i;
		}
		for (i=0; i<4; i++)
		{
			if ( !strcmp(button[i],"")) break;
			buttNo=i;
		}
		sum[0]=0;
		sum[1]=strlen(button[0]);
		sum[2]=sum[1]+strlen(button[1]);
		sum[3]=sum[2]+strlen(button[2]);
		if ( sum[buttNo+1]+(buttNo+2)*pgab/_CW->charspace > max_X ) max_X = sum[buttNo+1]+(buttNo+2)*pgab/_CW->charspace;
		pgab=( (max_X-sum[buttNo+1])*_CW->charspace ) / (buttNo+2);
		if ( SCR.push(x1-6, y1-6, x1+max_X * _CW->charspace + 32,
						 y1 + (size_Y + 3)* _CW->linespace + 32) != NOERR) return ERR;
		box3d(x1, y1, x1+max_X * _CW->charspace + 32,
					y1 + (size_Y +3 ) * _CW->linespace + 32, 0,0,0);
		box3d(x1-6, y1-6, x1+max_X * _CW->charspace + 26,
					y1 + (size_Y +3 ) * _CW->linespace + 26, 7,15,8);
		box3d(x1, y1, x1+max_X * _CW->charspace + 20,
					y1 + (size_Y +3 ) * _CW->linespace + 20, 1,8,15);
		box3d(x1+1, y1+1, x1+max_X * _CW->charspace + 19,
					y1 + (size_Y +3 ) * _CW->linespace + 19, 1,15,8);
		hsetcolor(10);
		hsetbkcolor(1);
		for (i=0; i<= size_Y; i++)
			 hputspxy( x1+10+(max_X-strlen(title[i]))*_CW->charspace/2,
								 y1+10 + i*_CW->linespace, title[i]);
																													 //  5
		hsetbkcolor(7);
		hsetcolor(15);
		for (i=0; i<= buttNo; i++)                             //  9
		{                                                     ///  24
			 box3d( x1+5+pgab*(i+1)+sum[i]*_CW->charspace,              //   28
							y1+10+(size_Y+1)*_CW->linespace+5,
							x1+15+pgab*(i+1)+(sum[i]+strlen(button[i]))*_CW->charspace,
							y1+10+(size_Y+1)*_CW->linespace+28 ,7,15,8);
			 box3d( x1+5+pgab*(i+1)+sum[i]*_CW->charspace+1,              //   28
							y1+10+(size_Y+1)*_CW->linespace+6,
							x1+15+pgab*(i+1)+(sum[i]+strlen(button[i]))*_CW->charspace-1,
							y1+10+(size_Y+1)*_CW->linespace+27,7,15,8);
			 hputspxy( x1+10+pgab*(i+1)+sum[i]*_CW->charspace,
								 y1+10+(size_Y+1)*_CW->linespace+9,
								 button[i]);
		}
		box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace,              //   28
					 y1+10+(size_Y+1)*_CW->linespace+5,
					 x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace,
					 y1+10+(size_Y+1)*_CW->linespace+28 ,7,8,15);
		box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace+1,              //   28
					 y1+10+(size_Y+1)*_CW->linespace+6,
					 x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace-1,
					 y1+10+(size_Y+1)*_CW->linespace+27 ,7,8,15);
/*		hputspxy( x1+12+pgab*(ret+1)+sum[ret]*_CW->charspace,
							y1+12+(size_Y+1)*_CW->linespace+9,
							button[ret]);  */
		while( !exitcode )
		{
			 if (!kbhit())
			 {
						if (count++ >1000)
						{
										do { color=random(15); }
													while( (color == 7) || (color == 0 ) );
										hsetcolor(color);
										hputspxy( x1+11+pgab*(ret+1)+sum[ret]*_CW->charspace,
															y1+11+(size_Y+1)*_CW->linespace+9,
															button[ret]);
								count=0;
						}
			 }
			 else
			 {
					ch = getch();
					if (ch==0)
					{
						 switch(getch())
						 {
								case _RTARR :
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+5,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace,
																	y1+10+(size_Y+1)*_CW->linespace+28 ,7,15,8);
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace+1,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+6,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace-1,
																	y1+10+(size_Y+1)*_CW->linespace+27 ,7,15,8);
													 hsetcolor(15);
													 hputspxy( x1+10+pgab*(ret+1)+sum[ret]*_CW->charspace,
																		 y1+10+(size_Y+1)*_CW->linespace+9,
																		 button[ret]);

													 if (ret==buttNo) ret=0;
													 else (ret)++;
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+5,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace,
																	y1+10+(size_Y+1)*_CW->linespace+28 ,7,8,15);
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace+1,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+6,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace-1,
																	y1+10+(size_Y+1)*_CW->linespace+27 ,7,8,15);
/*													 hputspxy( x1+12+pgab*(ret+1)+sum[ret]*_CW->charspace,
																		 y1+12+(size_Y+1)*_CW->linespace+9,
																		 button[ret]); */
													 break;
							 case _LTARR :
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+5,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace,
																	y1+10+(size_Y+1)*_CW->linespace+28 ,7,15,8);
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace+1,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+6,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace-1,
																	y1+10+(size_Y+1)*_CW->linespace+27 ,7,15,8);
													 hsetcolor(15);
													 hputspxy( x1+10+pgab*(ret+1)+sum[ret]*_CW->charspace,
																		 y1+10+(size_Y+1)*_CW->linespace+9,
																		 button[ret]);
													 if (ret==0) ret=buttNo;
													 else (ret)--;
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+5,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace,
																	y1+10+(size_Y+1)*_CW->linespace+28 ,7,8,15);
													 box3d( x1+5+pgab*(ret+1)+sum[ret]*_CW->charspace+1,              //   28
																	y1+10+(size_Y+1)*_CW->linespace+5+1,
																	x1+15+pgab*(ret+1)+(sum[ret]+strlen(button[ret]))*_CW->charspace-1,
																	y1+10+(size_Y+1)*_CW->linespace+27 ,7,8,15);
/*													 hputspxy( x1+12+pgab*(ret+1)+sum[ret]*_CW->charspace,
																		 y1+12+(size_Y+1)*_CW->linespace+9,
																		 button[ret]);*/
						 }
					}
			 }
			 if (ch==13) exitcode=1;
			 if (ch==27) { ret=temp; exitcode=CANCEL; }
		}
		hlastwindow();
		rCOLOR.pop();
		if (ch==13) exitcode=NOERR;
		return exitcode;
}

void SelectBoxBAR(int x1, int y1, int size_PX, char *title, int y, int c, int bk)
{
			 setfillstyle(1,bk);
			 bar(   x1+1, y1+ y*_CW->linespace+5,
							x1+size_PX+9, y1+(y+1)*_CW->linespace+4);
			 hsetcolor(c);
			 hsetbkcolor(bk);
			 hputspxy(x1+5,y1+y *_CW->linespace+5,title);
}

int SelectBox(int x1, int y1, int bL, int bSL, int bBK, int bSBK, char *title[20], int *ret)
{                          // 15  14   1   13
	 char ch;
	 int size_PX, size_PY, size_X=0, size_Y,i,exitcode=0,temp;
	 temp =*ret;
	 rCOLOR.push();
	 htempwindow(1,1,80,30);
	 for (i=0; i<20; i++)
	 {
			if (!strcmp(title[i],"")) break;
			size_Y=i;
			if ( size_X < strlen(title[i]) ) size_X = strlen(title[i]);
	 }
	 size_PX=size_X * _CW->charspace;
	 size_PY=(size_Y+1) * _CW->linespace;

	 if ( SCR.push(x1, y1, x1+size_PX+10, y1+size_PY+10) != NOERR )
			return ERR;

	 box3d(x1, y1, x1+size_PX+10, y1+size_PY+10, bBK, 15, 8);
	 hsetcolor(bL);
	 hsetbkcolor(bBK);
	 for (i=0; i<=size_Y; i++) hputspxy(x1+5,y1+5+i*_CW->linespace,title[i]);

	 SelectBoxBAR(x1, y1, size_PX, title[*ret], *ret, bSL, bSBK);

	 while( !exitcode )
	 {
			ch=getch();
			if (ch == 0)
					ch=getch();
					switch(ch)
					{
						 case  _LTARR:
						 case  _UPARR:

							SelectBoxBAR(x1, y1, size_PX, title[*ret], *ret, bL, bBK);
														if (*ret == 0) *ret = size_Y;
														else (*ret)--;

							SelectBoxBAR(x1, y1, size_PX, title[*ret], *ret, bSL, bSBK);

														break;

						 case  _RTARR:
						 case  _DNARR:

							SelectBoxBAR(x1, y1, size_PX, title[*ret], *ret, bL, bBK);
														if (*ret == size_Y) *ret = 0;
														else (*ret)++;
							SelectBoxBAR(x1, y1, size_PX, title[*ret], *ret, bSL, bSBK);

					}
			if (ch==27)
			{
				 *ret = temp;
				 exitcode = CANCEL;
			}
			if (ch==13) exitcode = NOERR;
	 }
	 hlastwindow();
	 rCOLOR.pop();
	 return exitcode;
}

int PopupBox(int x1, int y1, int bL, int bSL, int bBK, int bSBK, char *title[20], void(*RunFunc[20])(void))
{                          // 15  14   1   13
	 char ch;
	 int size_PX, size_PY, size_X=0, size_Y,i,exitcode=0,selno=0;
	 rCOLOR.push();
	 htempwindow(1,1,80,30);
	 for (i=0; i<20; i++)
	 {
			if (!strcmp(title[i],"")) break;
			size_Y=i;
			if ( size_X < strlen(title[i]) ) size_X = strlen(title[i]);
	 }
	 size_PX=size_X * _CW->charspace;
	 size_PY=(size_Y+1) * _CW->linespace;

	 if ( SCR.push(x1, y1, x1+size_PX+10, y1+size_PY+10) != NOERR )
			return ERR;

	 box3d(x1, y1, x1+size_PX+10, y1+size_PY+10, bBK, 15, 8);
	 hsetcolor(bL);
	 hsetbkcolor(bBK);
	 for (i=0; i<=size_Y; i++) hputspxy(x1+5,y1+5+i*_CW->linespace,title[i]);

	 SelectBoxBAR(x1, y1, size_PX, title[selno], selno, bSL, bSBK);

	 while( !exitcode )
	 {
			ch=getch();
			if (ch == 0)
					ch=getch();
					switch(ch)
					{
						 case  _LTARR:
						 case  _UPARR:

							SelectBoxBAR(x1, y1, size_PX, title[selno], selno, bL, bBK);
														if (selno == 0) selno = size_Y;
														else (selno)--;

							SelectBoxBAR(x1, y1, size_PX, title[selno], selno, bSL, bSBK);

														break;

						 case  _RTARR:
						 case  _DNARR:

							SelectBoxBAR(x1, y1, size_PX, title[selno], selno, bL, bBK);
														if (selno == size_Y)  selno= 0;
														else selno++;
							SelectBoxBAR(x1, y1, size_PX, title[selno], selno, bSL, bSBK);

					}
			if (ch==27) exitcode = CANCEL;
			if (ch==13) (*RunFunc[selno])();
	 }
	 hlastwindow();
	 rCOLOR.pop();
	 return NOERR;
}
