class _PD {
private:
	 int noTOP,bBarBK;
	 int TOP_X[11];
	 int MENU_X[11];
	 int lenTOP[11];
	 int noMENU[11];
	 int sizeMENU[11];
	 int _scrX, _scrY;
	 int tx1, ty1, tx2, ty2;
	 int mx1, my1, mx2, my2;
	 int tmp1, tmp2;
	 int px,py;
	 int pby[11];
	 int tL, tSL, tBK, tSBK, mL, mBL, mSL, mBK1, mBK2, mSBK, UL, DR;
	 int GAB;
	 void TopButton(int mode);
	 void menuBar(int mode);
	 int menuBoard();
	 int move_topBar();
public:
	 int x() { return px; }
	 int y() { return py; }
	 void run();
	 void topBar();
	 _PD(int x1, int y1, int _GAB=0, int _tL, int _tSL, int _tBK, int _tSBK, int _mL, int _mBL, int _mSL, int _mBK1, int _mBK2, int _mSBK, int _UL, int _DR);
};

struct _image{
	 int x1, y1;
	 unsigned char far *image;
};


class _SCR {
private:
	 class CXmsImage* pXmsImg[20];
	 int top;
public:
	 push(int x1, int y1, int x2, int y2);
	 pop();
	 _SCR();
	 virtual ~_SCR();
};

class CXmsImage
{
   private :
	  int bSuccess;
	  int x,y,nTileX,nTileY,LastTileXSize,LastTileYSize,TileXSize,TileYSize;
	  unsigned long TileSize, ydoff, xdoff;
	  int hndXmsImg;
   public :
	  CXmsImage();
	  ~CXmsImage();
	  void settile(int _sizeX, int _sizeY);
	  void get(int x1, int y1, int x2, int y2);
	  void put();
};

struct _colors{
	 int x,y;
	 int c, bkc;
	 int hc,hbkc;
};

class _rCOLOR {
private:
	 struct _colors COLORS[10];
	 int top;
public:
	 push();
	 pop();
	 _rCOLOR();
	 virtual ~_rCOLOR() {}
};
