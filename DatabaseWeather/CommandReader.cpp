#include "TableWorker.h"
#include "CommandReader.h"
#include <iostream>
#include <sstream>
#include "Utilities.h"

CommandReader::CommandReader(FileDescriptor* FD, TableWorker* TW)
{
  this->FD = FD;
  this->TW = TW;
  BaseOpened = false;
}

int CommandReader::StartRead()
{
  std::string str;
  std::string Command;
  std::string Arguments;

  while (true)
  {
    std::cout << "**Enter command:\n";
    Command = "";
    getline(std::cin, str);

    std::stringstream iss(str);
    iss >> Command;
    if(Command == "Open")
    {
      iss >> Arguments;
      BaseOpened = true;
      TW->ReadFromBase(FD, &Arguments);
    }
    else if (Command == "Help")
    {
      std::cout << "**All commands:\n"
      << "Open   [File name]  - is opening file\n"
      << "Print               - printing to console\n"
      << "Add                 - create new record to the end of data base\n"
      << "Find [Record, Record type, Calc(Min, Max, Average)]"
      << " [-Record type: Record, -Calc: Record type] [-Calc: range(1:2)]\n"
      << "                    - Find specified value\n"
      << "Insert [Index]      - insert by index\n"
      << "Edit   [Index]      - edit corresponding  record\n"
      << "Remove [Index]      - remove by index\n"
      << "Save                - save to opened file\n"
      << "Exit                - exit from programm\n";
    }
    else if (Command == "Print")
    {
      TW->PrintTable();
    }
    else if (Command == "Find")
    {
      Arguments = str.substr(Command.size() + 1);
      TW->Find(&Arguments);
    }
    else if (Command == "Add")
    {
      if(!BaseOpened)
      {
        std::cout << "**Befor add open your data base\n";
        continue;
      }
      TW->WriteToEnd();
    }
    else if (Command == "Insert")
    {
      if(!BaseOpened)
      {
        std::cout << "**Befor add open your data base\n";
        continue;
      }
      iss >> Arguments;
      int Index = -1;
      Index = ArgToInt(&Arguments);

      if(Index == -1)
        continue;

      TW->Insert(Index);
    }
    else if (Command == "Edit")
    {
      if(!BaseOpened)
      {
        std::cout << "**Befor add open your data base\n";
        continue;
      }
      iss >> Arguments;
      int Index = -1;
      Index = ArgToInt(&Arguments);

      if(Index == -1)
        continue;

      TW->Edit(Index);
    }
    else if (Command == "Remove")
    {
      if(!BaseOpened)
      {
        std::cout << "**Befor save open your data base\n";
        continue;
      }
      iss >> Arguments;
      int Index = -1;
      Index = ArgToInt(&Arguments);

      TW->Remove(Index);
    }
    else if (Command == "Save")
    {
      if(!BaseOpened)
      {
        std::cout << "**Befor save open your data base\n";
        continue;
      }
      TW->WriteToDataBase(FD);
    }
    else if (Command == "Exit")
    {
      if(!TW->IsSaved())
      {
        std::cout << "**WARNING!\n"
        << "*You haven't saved your data\n"
        << "*Save your data? (y/n)\n";

        std::string Answer;

        std::cin >> Answer;

        if(Answer == "y")
          TW->WriteToDataBase(FD);
      }

      return 0;
    }
  }
}
