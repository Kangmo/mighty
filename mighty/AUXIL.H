class _SCR {
private:
public:
	 push(int x1, int y1, int x2, int y2);
	 pop();
	 _SCR();
};


struct _colors{
	 int x,y;
	 int c, bkc;
	 int hc,hbkc;
};

class _rCOLOR {
private:
	 struct _colors COLORS[1];
	 int top;
public:
	 push();
	 pop();
	 _rCOLOR();
	 virtual ~_rCOLOR() {}
};
void box3d(int x1, int y1, int x2, int y2, int c, int ul, int dr);
