#include "headers.h"
#define np1 17
#define np2 11
#include "debug.h"

char pass1[]="@%MS_AQ>Z)#JD(XMQ";
char pass2[]="+\|/*&zmO~`";

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
//   " GIVE ME YOUR HOST SOURCE" CAN HAVE THIS SOURCE.                     //
//                                                                         //
//   ANYONE WHO GIVES THIS SOURCE TO OTHERS,                               //
//   ANYONE WHO SELLS TRANSFORMED PROGRAM BY COMPILING THIS SOURCE,        //
//   ANYONE WHO SELLS THIS SOURCE,                                         //
//   ANYONE WHO USES THIS PROGRAM AND THIS SOURCE FOR COMMECIAL PURPOSE    //
//                                                                         //
//   WILL BE PERISHED BY COPY RIGHT LAW.       1995.11.1 KIM KANGMO        //
//                                                                         //
//-------------------------------------------------------------------------//


CDataFile::~CDataFile()
{
		free( doff );
		free( size );
		XMMfree(hndXmsData);
}
CDataFile::CDataFile(char* filename)
{
		long count,filelen;
		int index, datanum;
		unsigned long datasize, alldatasize, pileddatasize;
		char ch, *DATA;
		printf("Reading mighty.dat from HARD DISK....");

		if ( access(filename,0) ) halt("Data file does not exist ");
		FILE *InFile = fopen(filename,"rb");
		if ( InFile == NULL ) halt("Not enough memory-m.");

		fseek(InFile,0L,SEEK_END);
		filelen = ftell(InFile);
		fseek(InFile,0L,SEEK_SET);

		FILE *fp = tmpfile();

		if (fp == NULL) halt("Not enough memory-m.");

		count = 0;
		while( count++ < filelen )
		{
			ch=fgetc(InFile);
			fputc( ch^pass2[count % np2], fp );
		}
		fclose (InFile);

		InFile = tmpfile();
		if ( InFile == NULL ) halt("Not enough memory -m.");

		rewind(fp);

		count =0;

		while( count++ < filelen )
		{
			ch=fgetc(fp);
			fputc( ch^pass1[count % np1], InFile );
		}
		fclose (fp);


		// Data Number counting routine.
		maxdatanum=0;

		rewind( InFile );
		count=0;
		while( count++ < filelen )
		{
				ch=fgetc(InFile);
				if (ch=='') ++maxdatanum;
		}

		size = (unsigned long*) malloc(sizeof(unsigned long) * maxdatanum);
		if (size==NULL) halt("ERROR : Not enough memory - D1");

		datanum=1, datasize=0, alldatasize=0;
		rewind(InFile);
		while( datanum <= maxdatanum )
		{
				ch=fgetc(InFile);

				++datasize;
				++alldatasize;
				if (ch=='')
				{
					 size[datanum++ -1] = datasize;
					 datasize=0;
				}
		}

		if (XMMcoreleft() < alldatasize) halt("ERROR : Not eough XMS memory");
		hndXmsData = XMMalloc(alldatasize);

		doff = (unsigned long*) malloc(sizeof(unsigned long) * maxdatanum);
		if (doff==NULL) halt("ERROR : Not enough memory - D2");
		doff[0]=0;
		index=0, datanum=1, pileddatasize=0;
		DATA = (char*) malloc(size[0]);
		rewind(InFile);
		while( datanum <= maxdatanum )
		{
				ch=fgetc(InFile);
				if (ch=='')
				{
					 DATA[index]=0;
					 XMMcopyto(size[datanum-1],
								DATA,
								hndXmsData, doff[datanum-1] );
					 free(DATA);

					 if (datanum < maxdatanum)
					 {
						  pileddatasize += size[datanum-1];
						  doff[datanum] = pileddatasize;
					 }

					 datanum++;

					 if (datanum <= maxdatanum)
					 {
						  DATA = (char*) malloc(size[datanum-1]);
						  if (DATA ==NULL) halt("ERROR : Not enough memory - D3");
						  index=0;
					 }
				}
				else DATA[index++] = ch;

		}

		fclose (InFile);
		printf("OK !\n");
}
void CDataFile::Read(int n)
{
		int index=0;
		char str[MAX_MACRO_LEN+1],ch, *DATA;

		DATA = (char*) malloc( size[n-1] );
		if (DATA==NULL) halt("Error : Not enough memory for copying XMM to convential mem.");
		XMMcopyfrom (size[n-1],
					 hndXmsData, doff[n-1],
					 DATA);

		while ( (ch = DATA[index++]) != 0 )
		{
			#ifdef DEBUG  // when debugging, the module, ProcessMacro does not exist.
						c_hputch(ch);
						if (ch=='\n') c_hputch('\r');
			#else
				if ( ch == '$' && DATA[index] == '$')
				{
						memset(str,0,MAX_MACRO_LEN+1);
						strncpy(str,DATA+index+1,MAX_MACRO_LEN);
						index+=ProcessMacro(str)+1;
				}
				else
				{
						c_hputch(ch);
						if (ch=='\n') c_hputch('\r');
				}
			#endif
		}
		free(DATA);
}
