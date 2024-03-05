#include "FileDescriptor.h"
#include <iostream>
#include <string>

struct row
{
    int N;
    std::string Country, City, Time, Temp, Humidity;
};

FileDescriptor::FileDescriptor(std::string* FilePath)
{
  Open(FilePath);
}

FileDescriptor::FileDescriptor()
{
}

bool FileDescriptor::Open(std::string* FilePath)
{
  if(File)
    Close();

  File.open(*FilePath, std::fstream::in);
  if(!File)
  {
    std::cout << "**" << FilePath->c_str() << "| Error, file not finded!" << "\n";
    Exist = false;
  }
  else
  {
    Exist = true;
    std::cout << "**File " << *FilePath << " is opened!\n";
    this->FilePath = *FilePath;
  }

  return Exist;
}

void FileDescriptor::Close()
{
  File.close();
}

void FileDescriptor::Print()
{
  if(Exist)
  {
    File.clear();
    char ch;
    while(!File.eof())
    {
      File >> ch;
      std::cout << ch;
    }
    std::cout << "\n";
  }
}

void FileDescriptor::Write(std::vector<row>* Row)
{
  if(File)
    Close();

  File.open(FilePath, std::fstream::out | std::fstream::trunc);
  for(row Row : *Row)
    File << Row.N << " " << Row.Country << " " << Row.City << " " << Row.Time << " " << Row.Temp << " " << Row.Humidity << "\n";

  Close();
}

std::string FileDescriptor::ReadLine()
{
  std::string Line;
  getline(File, Line);
  return Line;
}

FileDescriptor::~FileDescriptor()
{
  Close();
}
