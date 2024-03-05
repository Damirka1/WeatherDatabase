class CommandReader
{
private:
  FileDescriptor* FD;
  TableWorker* TW;
  bool BaseOpened;

public:
  CommandReader(FileDescriptor* FD, TableWorker* TW);

  int StartRead();

};
