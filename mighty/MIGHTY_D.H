class CDataFile
{
		private:
			 unsigned long* size;
			 unsigned long* doff;
			 int hndXmsData;
			 int maxdatanum;
		public:
			 void Read(int n);
			 CDataFile(char *filename);
			 ~CDataFile();
};
