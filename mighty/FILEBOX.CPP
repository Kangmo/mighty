#include "headers.h"
#define M_t_(n) ;
//printf("[%i] %ld\n", n, farcoreleft());
char PathBuffer[200];
CFileSelector::CFileSelector(int x1_,int y1_, int bkcol1_, int bkcol2_, int bkcol3_)
{
	x1=x1_;
	y1=y1_;
	bkcol1 = bkcol1_;
	bkcol2 = bkcol2_;
	bkcol3 = bkcol3_;
	rCOLOR.push();
	ScrPushed = SCR.push(x1, y1, x1+10+45*CS, y1+24+(FILES+1)*LS);
	htempwindow(1,1,80,29);
	bar_index=1;
	strcpy(directory, PathBuffer);
}
CFileSelector::~CFileSelector()
{
	if (filedata) free(filedata);
	hlastwindow();
	if (ScrPushed==NOERR) SCR.pop();
	rCOLOR.pop();
}
int CFileSelector::maxx() { return x1+10+45*CS; }
int CFileSelector::maxy() { return y1+24+(FILES+1)*LS; }

int CFileSelector::GetFileName()
{
	char new_dir[301];
	CutOffSpace(directory);
	strcpy(new_dir, directory);
	hsetcolor(10); hsetbkcolor(bkcol2);
	hgotopxy(x1+7+5*CS, y1+7);
	if (hgetln(new_dir,30)==ESC) return CANCEL;
	CutOffSpace(new_dir);
	if (strcmp(directory, new_dir))
	{
		strcpy(directory, new_dir);
		bar_index=1;
		ModifyDirectory();
	}
}
int CFileSelector::getfileno()
{
	struct ffblk filetypes;
	fileno=0;
	if (findfirst(directory,&filetypes,FA_DIREC)==-1) return ERR;
	while( findnext(&filetypes) != -1) ++fileno;
}
void CFileSelector::Change(filedata_t& fd1, filedata_t& fd2)
{
	filedata_t tmpdata;
	tmpdata=fd1;
	fd1=fd2;
	fd2=tmpdata;
}
void CFileSelector::readfiledata()
{
	struct ffblk filetypes;
	int index=0,i,no_of_dir;
	findfirst(directory,&filetypes,FA_DIREC);
	while( findnext(&filetypes) != -1)
	{
		strcpy( filedata[index].name,filetypes.ff_name);
		filedata[index].attrib = filetypes.ff_attrib;
		filedata[index].intsize = filetypes.ff_fsize;
		if (filetypes.ff_fsize<1024)
		{
			ltoa(filetypes.ff_fsize, filedata[index].size, 10);
			strcat(filedata[index].size,"B");
		}
		else
		{
			ltoa(filetypes.ff_fsize/1024, filedata[index].size, 10);
			strcat(filedata[index].size,"K");
		}
		++index;
	}
	no_of_dir =0;
	for (i=0; i<fileno; i++)
	{
		if ( filedata[i].attrib == FA_DIREC )
		{
			strcpy(filedata[i].size,"[DIR]");
			strcat(filedata[i].name,"\\");
			Change(filedata[no_of_dir++], filedata[i]);
		}
	}
}
void CFileSelector::process_scrollbar()
{
	setfillstyle(1,bkcol1);
	bar (x1+10+42*CS+6, y1+10+LS, x1+10+45*CS-6, y1+18+(FILES+1)*LS);
	if (fileno==1)
		box3d (x1+10+42*CS+6, y1+9+LS, x1+10+45*CS-5, y1+9+LS+3*CS-12,
		bkcol1, 15, 8);
	else
	box3d (x1+10+42*CS+6, y1+10+LS+(10+FILES*LS-(3*CS-12))*(bar_index-1)/(fileno-1),
		x1+10+45*CS-6, y1+8+LS+(10+FILES*LS-(3*CS-12))*(bar_index-1)/(fileno-1)+3*CS-12,
		bkcol1, 15, 8);
}
void CFileSelector::print_bar(int mode)
{
	int bar_num = bar_index%(FILES*2);
	if (bar_num==0) bar_num=FILES*2;
	if (bar_num <=FILES)
	{
		box3d(x1+6, y1+17+LS*bar_num-1, x1+4+13*CS, y1+17+LS*(bar_num+1),
			(mode==DRAW)?10:bkcol2,(mode==DRAW)?15:bkcol2,(mode==DRAW)?8:bkcol2);
		hsetcolor((mode==DRAW)?12:15);  hsetbkcolor((mode==DRAW)?10:bkcol2);
		hprintfpxy(x1+10, y1+17+LS*bar_num,"%s",
					 filedata[bar_index-1].name);
	}
	else if (bar_num >FILES)
	{
		box3d(x1+7+21*CS, y1+17+LS*(bar_num-FILES)-1, x1+5+34*CS, y1+17+LS*(bar_num-FILES+1),
			(mode==DRAW)?10:bkcol2,(mode==DRAW)?15:bkcol2,(mode==DRAW)?8:bkcol2);
		hsetcolor((mode==DRAW)?12:15);  hsetbkcolor((mode==DRAW)?10:bkcol2);
		hprintfpxy(x1+11+21*CS, y1+17+LS*(bar_num-FILES),"%s",
					 filedata[bar_index-1].name);
	}
	process_scrollbar();
}
void CFileSelector::print_files(int start_index)
{
	int k;
	box3d (x1+5, y1+15+LS, x1+5+21*CS, y1+19+(FILES+1)*LS, bkcol2, 8, 15);
	box3d (x1+6+21*CS, y1+15+LS, x1+6+42*CS, y1+19+(FILES+1)*LS, bkcol2, 8, 15);
	box3d (x1+5+13*CS, y1+16+LS, x1+4+21*CS, y1+18+(FILES+1)*LS, bkcol3, 15, 8);
	box3d (x1+6+34*CS, y1+16+LS, x1+5+42*CS, y1+18+(FILES+1)*LS, bkcol3, 15, 8);
	if ( fileno<=0 ) return;
	for(k=1; k<=FILES; k++)
	{
		if (start_index+k-1>fileno) return ;
		hsetcolor(15); hsetbkcolor(bkcol2);
		hprintfpxy(x1+10, y1+17+LS*k,"%s",
					 filedata[start_index+k-2].name);
		hsetcolor(11); hsetbkcolor(bkcol3);
		hprintfpxy(x1+10+13*CS, y1+17+LS*k,"%6s",filedata[start_index+k-2].size);
	}
	for (k=1; k<=FILES; k++)
	{
		if (start_index+FILES+k-1>fileno) return;
		hsetcolor(15); hsetbkcolor(bkcol2);
		hprintfpxy(x1+11+21*CS, y1+17+LS*k, "%s",
					 filedata[start_index+FILES+k-2].name);
		hsetcolor(11); hsetbkcolor(bkcol3);
		hprintfpxy(x1+11+34*CS, y1+17+LS*k, "%6s",filedata[start_index+FILES+k-2].size);
	}
}
void CFileSelector::DrawFileBox()
{
	 hgotopxy(x1+7+5*CS, y1+7);
	 box3d (x1, y1, x1+10+45*CS, y1+24+(FILES+1)*LS, bkcol1, 15, 8);
	 box3d (x1+10+42*CS+5, y1+9+LS, x1+10+45*CS-5, y1+19+(FILES+1)*LS, bkcol1, 8, 15);
	 box3d (x1+5+5*CS, y1+5, x1+10+35*CS, y1+9+LS, bkcol2, 8, 15);
	 hsetcolor(13);
	 hsetbkcolor(bkcol1);
	 hprintfpxy(x1+6,y1+7,"NAME");
	 box3d (x1+5, y1+15+LS, x1+5+21*CS, y1+19+(FILES+1)*LS, bkcol2, 8, 15);
	 box3d (x1+6+21*CS, y1+15+LS, x1+6+42*CS, y1+19+(FILES+1)*LS, bkcol2, 8, 15);
}

int CFileSelector::InitSelector()
{
	bar_index = 1;
	do {
			if (GetFileName()==CANCEL) return CANCEL;
		} while( (getfileno() == ERR) );
	filedata = (struct filedata_t*)malloc(sizeof(struct filedata_t)*(fileno+1));
	readfiledata();
	print_files(1);
	print_bar(DRAW);
}
int CFileSelector::SelectFile(char *fpath, char* fname, long& fsize)
{
	char ch;
	DrawFileBox();
	if (InitSelector()==CANCEL) return CANCEL;
		while(1)
		{
			ch=getch();
			switch(ch)
			{
				case     0 : OnScanKey();
							 break;
				case   TAB : print_bar(RECOVER);
								 if (InitSelector()==CANCEL) return CANCEL;
								 break;
				case ENTER : if (OnEnterKey(fpath,fname,fsize)==FILESELOK)
									 return NOERR;
								 break;
				case   ESC : return CANCEL;
			}
		}
}
void CFileSelector::ModifyDirectory()
{
	 int i;
	 bool PointFound = false;
	 CutOffSpace(directory);
	 if ( !strcmp(directory, "*.*") )
	 {
		  getcwd(directory,90);
		  strcat(directory, "\\*.*");
		  return;
	 }
	 for (i=strlen(directory); i>=1; i--)
	 {
		if ( directory[i-1]=='\\' ) break;
		if ( directory[i-1]=='.' ) PointFound=true;
	 }
	 if ( PointFound==false )
	 {
		 if (directory[strlen(directory)-1]=='\\')
			strcat(directory,"*.*");
		 else strcat(directory,"\\*.*");
	 }
	 else if(directory[strlen(directory)-1]=='.')
			 strcat(directory,"*");
	 PrintDir();
}

void CFileSelector::PrintDir()
{
	 box3d (x1+5+5*CS, y1+5, x1+10+35*CS, y1+9+LS, bkcol2, 8, 15);
	 hsetbkcolor(bkcol2);
	 hsetcolor(10);
	 hgotopxy(x1+7+5*CS, y1+7);
	 hputs(directory);
}
void CFileSelector::Dir2NewDir()
{
	 int toINS;
	 for (toINS=strlen(directory); toINS>=1; toINS--)
		if ( directory[toINS-1]=='\\' )
		{
			strnins( directory, toINS,
					filedata[bar_index-1].name,
					strlen(filedata[bar_index-1].name) );
			break;
		}
	 // inserting position is after '\\'
}
void CFileSelector::Dir2BeforeDir()
{
	 // 92 is ascii code of slash \\
	 int toDEL, HowMany=0;
	 bool SlashFound = false;
	 for (toDEL=strlen(directory); toDEL>=1; toDEL--)
	 {
		if ( ( directory[toDEL-1]=='\\' ) && SlashFound )
		{
			strndel(directory,toDEL,HowMany);
			break;
		}
		if ( directory[toDEL-1]=='\\' ) SlashFound=true;
		if ( SlashFound==true ) ++HowMany;
	 }
	 // deleteing position is after '\\'
}
// filename==NULL -> get filepath  : ends with \\
// filepath==NULL -> get filename & filesize
int CFileSelector::OnEnterKey(char* filepath, char* filename, long& filesize)
{
	int i;
	bool bDotFound=false;
	if ( filedata[bar_index-1].attrib == FA_DIREC )
	{
		if ( !strcmp(filedata[bar_index-1].name,"..\\") ) Dir2BeforeDir();
		else  Dir2NewDir();
		PrintDir();
		getfileno();
		if (filedata) free(filedata);
		filedata = (struct filedata_t*)malloc(sizeof(filedata_t)*(fileno+1));
		readfiledata();
		print_files(1);
		bar_index=1;
		print_bar(DRAW);
	}
	else
	{
		strcpy(PathBuffer,directory);
		if (filename != NULL)
		{
			strcpy(filename,filedata[bar_index-1].name);
			filesize = filedata[bar_index-1].intsize;
		}
		if (filepath != NULL)
		{
			strcpy(filepath,directory);
			/* cutting filename from path */
			for (i=strlen(filepath); i>=1; i--)
			{
				if ( filepath[i-1]=='\\' ) break;
				if ( filepath[i-1]=='.' ) { bDotFound=true; break; }
			}
			if (bDotFound)
			{
				for (i=strlen(filepath); i>=1; i--)
				{
				  if ( filepath[i-1]!='\\' ) filepath[i-1]=0;
				  else break;
				}
			}
		}
		return FILESELOK;
	}
	return NOERR;
}
// bar_index starts from 1
void CFileSelector::OnScanKey()
{

	switch( getch() )
	{
		 case UPARR_ :
			  if ( ((bar_index-1)%(FILES*2)==0) && (bar_index!=1) )
			  {
					--bar_index;
					print_files(bar_index-FILES*2+1);
					print_bar(DRAW);
					break;
			  }
			  if (bar_index>1)
			  {
					print_bar(RECOVER);
					bar_index--;
					print_bar(DRAW);
			  }
			  break;
		 case DNARR_ :
			  if ( ((bar_index)%(FILES*2)==0) && (bar_index<fileno) )
			  {
					++bar_index;
					print_files(bar_index);
					print_bar(DRAW);
					break;
			  }
			  if (bar_index<fileno)
			  {
					print_bar(RECOVER);
					bar_index++;
					print_bar(DRAW);
			  }
			  break;
		 case LTARR_ :
			  if (bar_index > FILES)
			  {
					 bar_index-= FILES;
					 print_files(bar_index);
					 print_bar(DRAW);
			  }
			  break;
		 case RTARR_ :
			  if ( bar_index < fileno - FILES )
			  {
					 bar_index+= FILES;
					 print_files(bar_index);
					 print_bar(DRAW);
			  }
			  break;
	}
}
