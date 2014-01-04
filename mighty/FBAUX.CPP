/* these objects are used for CFileSelector.
	but, danbi processes background image work,
	so, these objects are empty */
#include "hanbgi.h"
#include "han240.h"
#include "constdef.h"
#include "version.h"
#include "fbaux.h"
_SCR::_SCR()
{
}
int _SCR::push(int x1, int y1, int x2, int y2)
{
	 return NOERR;
}
int _SCR::pop()
{
	 return NOERR;
}

_rCOLOR::_rCOLOR()
{
	 top = -1;
}

_rCOLOR::push()
{
	 if (++top==1) return ERR;
	 COLORS[top].hc = hgetcolor();
	 COLORS[top].hbkc = hgetbkcolor();
	 COLORS[top].c = getcolor();
	 COLORS[top].bkc = getbkcolor();
	 COLORS[top].x=hwherex();
	 COLORS[top].y=hwherey();
}
_rCOLOR::pop()
{
	 if (top==-1) return ERR;
	 hsetcolor(COLORS[top].hc);
	 hsetbkcolor(COLORS[top].hbkc);
	 setcolor(COLORS[top].c);
	 setbkcolor(COLORS[top].bkc);
	 hgotoxy(COLORS[top].x, COLORS[top].y);
	 top--;
}
void box3d(int x1, int y1, int x2, int y2, int c, int ul, int dr)
{
		setfillstyle(1,c);
		bar(x1,y1,x2,y2);
		setcolor(ul);
		line(x1,y1,x2,y1);
		line(x1,y1,x1,y2);
		setcolor(dr);
		line(x2,y1,x2,y2);
		line(x1,y2,x2,y2);
}
