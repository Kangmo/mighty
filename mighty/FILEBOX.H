struct filedata_t
{
	char name[13];
	char attrib;
	char size[7];
	long intsize;
};
class CFileSelector
{
	private :
		int x1,y1,bar_index,fileno,ScrPushed;
		int bkcol1, bkcol2, bkcol3;
		char directory[100];
		struct filedata_t *filedata;
		void readfiledata();
		void process_scrollbar();
		void print_bar(int mode);
		void print_files(int start_index);
		int getfileno();
		int GetFileName();
		void DrawFileBox();
		void Change(filedata_t& fd1, filedata_t& fd2);
		int InitSelector();
		void OnScanKey();
		int OnEnterKey(char *filepath, char* filename,long& filesize);
		void ModifyDirectory();
		void Dir2NewDir();
		void Dir2BeforeDir();
		void PrintDir();
	public :
		int  maxx();
		int  maxy();
		CFileSelector(int x1_,int y1_, int bkcol1_, int bkcol2_, int bkcol3_);
		~CFileSelector();
		int SelectFile(char* fpath, char* fname, long& fsize);  // returns CANCEL if canceled.
};
