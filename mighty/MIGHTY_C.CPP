#include "headers.h"
void ErrChk(int code)
{
	 if (code < 0) halt("ERROR : Can't initialize comm port");
}
void SioPuts(int port, unsigned char *s)
{
	while (*s) SioPutc(port, *s++);
}
int SioHangUp(int port)
{
	 if (DoNullModem) return 1;
	 if ( SioDCD(port) )
	 {
			ErrChk( SioDTR( port, 'C' ) );
			SioDelay(18);
	 }
	 if ( SioDCD(port) )
	 {
			SioDelay(9);
			SioPuts(port, "+++");
			SioDelay(18);
			SioPuts(port, "ATH1");
			SioPutc(port, '\n');
			SioDelay(18);
	 }
	 SioDTR(port, 'S');
	 if ( SioDCD(port) ) return 0;
	 else return 1;
}
/*
void SioGets(int port, unsigned char *str, int no)
{
	int i=0, ch;
	do {
				if( no-- > 0 )
				{
					  while( !SioRxQue(port) )
					  if ( !bWaiting && !bLocal && !SioDCD(port) )
					  {
							 *(str+i)='\0';
							 return;
					  }
					  ch = SioGetc(port, 18);
					  if (ch >0) *(str+ i++) = ch;
				}
				else *(str+i)='\0';
		 }  while (*(str+i)!='\0');
} */
// gets no characters from comm port.
// if current character on comm port is r_ch,
// do not save r_ch and exit function
#define isNum(ch) ((ch)>='0' && (ch)<='9')
// if r_ch <0, SioGets only gets number. this is for detecting connect speed
void SioGets(int port, unsigned char *str, int no, char r_ch)
{
	int i=0, ch;
	int count=0;
	do {
				if( no-- > 0 )
				{
					  while( !SioRxQue(port) )
					  if ( !bWaiting && !bLocal && !SioDCD(port) )
					  {
							*(str+i)='\0';
							return;
					  }
					  ch = SioGetc(port, 18);
					  if (ch >0)
					  {
						  if (r_ch>=0)
						  {
							  if (ch==r_ch) *(str+i)='\0';
							  else *(str+ i++) = ch;
						  }
						  else
						  {
							  if (!isNum(ch)) *(str+i)='\0';
							  else *(str+ i++) = ch;
						  }
					  }
					  else count++;
					  if (count > 20) *(str+i)='\0';
				}
				else *(str+i)='\0';
		 }  while (*(str+i)!='\0');
}
int SioTxReady(int port)
{
	 return ( SioTxQue(port) < Size16K );
}
void SioHayes(int port, char *s)
{
	 char c;
	 int Code;
	 SioRxFlush(port);
	 SioDelay(4);
	 while(*s)
	 {
			c = toupper( *s );
			switch(c)
			{
				case '!': /* replace ! with carriage return */
						c = CR;
						break;
				case '~': /* delay 1/2 second */
						SioDelay(9);
						c = ' ';
						break;
				case ' ': /* delay 1/4 second */
						SioDelay(4);
						break;
			}
			SioPutc(port,(char)(0x7f & c));
			SioDelay(1);
			Code = SioGetc(port,18);
			if(!bPDrun && Code>0) hputch(Code);
			s++;
	 }
	 c_hputch('\r');
}
void c_hputch(unsigned char ch)
{
	 if (bLocal==0 && !bDontSendComm)
	 {
		  while (!SioTxReady(port));
		  SioPutc(port, ch);
	 }
	 if (ch == ESC || escstep > 0) process_vt100(ch);
	 else hputch(ch);
}
//puts a string to modem(when not local state) and moniter
void c_hputs(unsigned char *str)
{
	 while(*str)
	 {
			 if (bLocal==0 &&!bDontSendComm)
			 {
				 while (!SioTxReady(port)) ;
				 SioPutc(port, *str);
			 }
			 if (*str == ESC || escstep > 0) process_vt100(*str);
			 else hputch(*str);
			 str++;
	 }
}
int c_hprintf(const char *format, ...)
{
		char buffer[1024];
		int cnt,i=0;
		va_list arglist;
		va_start(arglist, format);
		cnt = vsprintf(buffer, format, arglist);
		while(buffer[i])
		{
			  c_hputch( buffer[i]);
			  i++;
		}
		va_end(arglist);
		return cnt;
}


void c_hclrscr( )
{
	 if (!bLocal && !bDontSendComm) SioPuts(port, "[=0G[2J[1;1H");
	 hclrscr();
}
void c_hgotoxy(int x, int y)
{
	 char s_X[6], s_Y[6];
	 if (!bLocal && !bDontSendComm)
	 {
			itoa(x,s_X,10);
			itoa(y,s_Y,10);
			SioPuts(port, strcat2(strcat2(strcat2(strcat2("[",s_Y),";"),s_X),"H"));
	 }
	 hgotoxy(x,y);
}

