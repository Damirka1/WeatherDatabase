#include <vector>
#include <string>
#include "FileDescriptor.h"

struct row
{
    int N;
    std::string Country, City, Time, Temp, Humidity;
};

class TableWorker
{
private:
  std::vector<row> Rows;
  int N;
  bool Saved;

public:
    TableWorker();

    void WriteToEnd();

    void PrintTable();

    void WriteToDataBase(FileDescriptor* F);

    void ReadFromBase(FileDescriptor* F, std::string* Path);

    bool IsSaved();

    void Edit(int Index);

    void Insert(int Index);

    void Remove(int Index);

    void Find(std::string* Args);

};
