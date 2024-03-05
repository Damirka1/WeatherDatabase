#include <fstream>
#include <vector>

struct row;

class FileDescriptor
{
private:
  std::fstream File;
  std::string FilePath;
  bool Exist;

public:
  FileDescriptor(std::string* FilePath);

  FileDescriptor();

  bool Open(std::string* FilePath);

  void Close();

  void Print();

  void Write(std::vector<row>* Row);

  std::string ReadLine();

  ~FileDescriptor();

};
