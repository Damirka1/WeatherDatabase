#include "TableWorker.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include "Utilities.h"

TableWorker::TableWorker()
{
  Saved = true;
}

void ReadInput(row* Row)
{
  std::cout << "**Enter country\n";
  getline(std::cin, Row->Country);

  std::cout << "**Enter city\n";
  getline(std::cin, Row->City);

  std::cout << "**Enter time\n";
  getline(std::cin, Row->Time);

  std::cout << "**Enter temperature\n";
  getline(std::cin, Row->Temp);

  std::cout << "**Enter humidity\n";
  getline(std::cin, Row->Humidity);
}


void TableWorker::WriteToEnd()
{
  row Row;

  Row.N = N++;
  ReadInput(&Row);

  Rows.push_back(Row);

  std::cout << "**Added!\n";

  Saved = false;
}

void AppendToOutput(std::string* Output, std::string Str, int MaxSize)
{
  int Spaces = MaxSize - Str.length();

  if(Spaces >= 2)
  {
    for(int i = 0; i < Spaces / 2; i++)
    {
      Output->append(" ");
    }

    Output->append(Str);

    for(int i = 0; i < Spaces / 2; i++)
    {
      Output->append(" ");
    }

    if(Spaces % 2 != 0)
      Output->append(" ");
  }
  else
  {
    Output->append(Str);
    for(int i = 0; i < Spaces; i++)
      Output->append(" ");
  }


  Output->append(" | ");
}

void Print(std::vector<row>* Rows)
{
  int ChN = 1, ChC = 7, ChCt = 4, ChT = 4, ChTe = 11, ChHu = 8;

  for(const row& Row : *Rows)
  {
    if (std::to_string(Row.N).length() > ChN)
      ChN = std::to_string(Row.N).length();

    if(Row.Country.length() > ChC)
      ChC = Row.Country.length();

    if(Row.City.length() > ChCt)
      ChCt = Row.City.length();

    if(Row.Time.length() > ChT)
      ChT = Row.Time.length();

    if(Row.Temp.length() > ChTe)
      ChTe = Row.Temp.length();

    if(Row.Humidity.length() > ChHu)
      ChHu = Row.Humidity.length();
  }

  std::string Output = "| ";

  AppendToOutput(&Output, "#", ChN);
  AppendToOutput(&Output, "Country", ChC);
  AppendToOutput(&Output, "City", ChCt);
  AppendToOutput(&Output, "Time", ChT);
  AppendToOutput(&Output, "Temperature", ChTe);
  AppendToOutput(&Output, "Humidity", ChHu);
  Output.append("\n");

  for(const row& Row : *Rows)
  {
    Output.append("| ");

    AppendToOutput(&Output, std::to_string(Row.N), ChN);
    AppendToOutput(&Output, Row.Country, ChC);
    AppendToOutput(&Output, Row.City, ChCt);
    AppendToOutput(&Output, Row.Time, ChT);
    AppendToOutput(&Output, Row.Temp, ChTe);
    AppendToOutput(&Output, Row.Humidity, ChHu);
    Output.append("\n");
  }

  std::cout << Output;
}


void TableWorker::PrintTable()
{
  Print(&Rows);
}

void TableWorker::WriteToDataBase(FileDescriptor* F)
{
  F->Write(&Rows);
  std::cout << "**Saved!\n";
  Saved = true;
}

void TableWorker::ReadFromBase(FileDescriptor* F, std::string* Path)
{
  F->Open(Path);
  std::string Line = F->ReadLine();
  Rows.clear();

  while(Line.size() > 0)
  {
    row Row;
    std::stringstream iss(Line);
    std::string Value;
    iss >> Value;

    Row.N = std::stoi(Value);

    iss >> Row.Country;
    iss >> Row.City;
    iss >> Row.Time;
    iss >> Row.Temp;
    iss >> Row.Humidity;

    Rows.push_back(Row);

    Line = F->ReadLine();
  }

  F->Close();

  if(Rows.size() > 0)
  {
    auto it = std::max_element(Rows.begin(), Rows.end(), [&](row& A, row& B)
    {
      return A.N < B.N;
    });

    N = it->N + 1;
  }
  Saved = true;
}
void TableWorker::Edit(int Index)
{
  if(Index >= Rows.size())
  {
    std::cout << "**Invalid index\n";
    return;
  }

  row* Row = &Rows[Index];

  while(true)
  {
    std::cout << "**What do you want to edit:\n"
    << "*Country     - 0\n"
    << "*City        - 1\n"
    << "*Time        - 2\n"
    << "*Temperature - 3\n"
    << "*Humidity    - 4\n"
    << "*All         - 5\n"
    << "*Exit        - 6\n";

    std::string Arg;
    getline(std::cin, Arg);

    int Val = ArgToInt(&Arg);

    if(Val == -1)
      continue;

    switch (Val)
    {
      case 0:
      std::cout << "**Enter country\n";
      getline(std::cin, Row->Country);
      Saved = false;
      break;

      case 1:
      std::cout << "**Enter city\n";
      getline(std::cin, Row->City);
      Saved = false;
      break;

      case 2:
      std::cout << "**Enter time\n";
      getline(std::cin, Row->Time);
      Saved = false;
      break;

      case 3:
      std::cout << "**Enter temperature\n";
      getline(std::cin, Row->Temp);
      Saved = false;
      break;

      case 4:
      std::cout << "**Enter humidity\n";
      getline(std::cin, Row->Humidity);
      Saved = false;
      break;

      case 5:
      ReadInput(Row);
      Saved = false;
      break;

      case 6:
      std::cout << "**Exit from edit menu\n";
      return;
    }
  }
}

void TableWorker::Insert(int Index)
{
  if(Index >= Rows.size())
  {
    std::cout << "**Invalid index\n";
    return;
  }
  row Row;
  Row.N = Index;
  ReadInput(&Row);

  Rows.insert(Rows.begin() + Index, Row);

  for(auto b = Rows.begin() + Index + 1, e = Rows.end(); b != e; ++b)
    b->N += 1;

  std::cout << "**Inserted!\n";

  Saved = false;
}

void TableWorker::Remove(int Index)
{
  if(Index >= Rows.size())
  {
    std::cout << "**Invalid index\n";
    return;
  }

  Rows.erase(Rows.begin() + Index);

  for(auto b = Rows.begin() + Index, e = Rows.end(); b != e; ++b)
    b->N -= 1;

  std::cout << "**Removed!\n";

  Saved = false;
}

bool TableWorker::IsSaved()
{
  return Saved;
}

void TableWorker::Find(std::string* Args)
{
  enum Type
  {
    Index,
    Country,
    City,
    Time,
    Temperature,
    Humidity,
    Max,
    Min,
    Average
  };

  std::vector<row> Finded;

  std::function<void(std::string* Key, Type FindBy)> Search = [&](std::string* Key, Type FindBy)
  {
    std::function<void(row*, std::string*)> Find = [&](row* Row, std::string* Key){};
    std::function<void(float*, float*)> Check = [&](float* A, float* B) {};
    bool Calculate = false;
    float Value = 0;

    switch (FindBy)
    {
      case Index:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->N == ArgToInt(Key))
          Finded.push_back(*Row);
      };
      break;

      case Country:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->Country == *Key)
          Finded.push_back(*Row);
      };
      break;

      case City:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->City == *Key)
          Finded.push_back(*Row);
      };
      break;

      case Time:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->Time == *Key)
          Finded.push_back(*Row);
      };
      break;

      case Temperature:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->Temp == *Key)
          Finded.push_back(*Row);
      };
      break;

      case Humidity:
      Find = [&](row* Row, std::string* Key)
      {
        if(Row->Humidity == *Key)
          Finded.push_back(*Row);
      };
      break;

      case Max:
      {
        Calculate = true;
        Check = [&](float* A, float* B)
        {
          if(*A > *B)
            *B = *A;
        };
        break;
      }
      case Min:
      {
        Calculate = true;
        Check = [&](float* A, float* B)
        {
          if(*A < *B)
            *B = *A;
        };
        break;
      }

      case Average:
      {
        Calculate = true;
        Check = [&](float* A, float* B)
        {
          *B += *A;
        };
        break;
      }
    }

    if(Calculate)
    {
      std::function<void(float*, row*)> Cal = [&](float* Value, row* Row) {};
      std::string SType;
      int begin = 0, end = 0;
      {
          std::stringstream ss(*Key);

          std::string Length;
          ss >> SType;
          ss >> Length;
          if(Length.size() > 0)
          {
            std::string beg, en;
            std::string* curr = &beg;
            for(auto b = Length.begin(), e = Length.end(); b != e; ++b)
            {
              if(*b == ':')
              {
                curr = &en;
                continue;
              }
              curr->push_back(*b);
            }
            if(beg.size() > 0)
              begin = ArgToInt(&beg);
            else
              begin = 0;
            if(en.size() > 0)
              end = ArgToInt(&en);
            else
              end = Rows.size();
          }
          else
            end = Rows.size();

          if(SType == "Index")
          {
            Value = (float)Rows[begin].N;
            Cal = [&](float* Value, row* Row)
            {
              float v = (float)Row->N;
              Check(&v, Value);
            };
          }
          else if(SType == "Temperature")
          {
            Value = (float)ArgToIntNoExcept(&Rows[begin].Temp);
            Cal = [&](float* Value, row* Row)
            {
              float v = (float)ArgToIntNoExcept(&Row->Temp);
              Check(&v, Value);
            };
          }
          else if(SType == "Humidity")
          {
            Value = (float)ArgToIntNoExcept(&Rows[begin].Humidity);
            Cal = [&](float* Value, row* Row)
            {
              float v = (float)ArgToIntNoExcept(&Row->Humidity);
              Check(&v, Value);
            };
          }
      }

      for(auto b = Rows.begin() + begin, e = Rows.begin() + end; b != e; ++b)
        Cal(&Value, &(*b));


      switch (FindBy)
      {
        case Max:
        {
          std::cout << "**Max value of " << SType << " is " << std::to_string(Value) << "\n";
          break;
        }
        case Min:
        {
          std::cout << "**Min value of " << SType << " is " << std::to_string(Value) << "\n";
          break;
        }
        case Average:
        {

          Value = Value / (end - begin);
          std::cout << "**Average value of " << SType << " is " << std::to_string(Value) << "\n";
          break;
        }
      }

      return;
    }

    for(auto b = Rows.begin(), e = Rows.end(); b != e; ++b)
    {
      Find(&(*b), Key);
    }
  };

  std::stringstream iss(*Args);

  std::string FindBy;
  std::string Key;
  iss >> FindBy;

  Key = Args->substr(FindBy.size() + 1);

  std::cout << "**" << FindBy << " | " << Key << "\n";

  if(FindBy == "Index")
    Search(&Key, Type::Index);
  else if(FindBy == "Country")
    Search(&Key, Type::Country);
  else if(FindBy == "City")
    Search(&Key, Type::City);
  else if(FindBy == "Time")
    Search(&Key, Type::Time);
  else if(FindBy == "Temperature")
    Search(&Key, Type::Temperature);
  else if(FindBy == "Humidity")
    Search(&Key, Type::Humidity);
  else if(FindBy == "Max")
  {
    Search(&Key, Type::Max);
    return;
  }
  else if(FindBy == "Min")
  {
    Search(&Key, Type::Min);
    return;
  }
  else if(FindBy == "Average")
  {
    Search(&Key, Type::Average);
    return;
  }
  else
  {
    for(auto b = Rows.begin(), e = Rows.end(); b != e; ++b)
    {
      if(b->N == ArgToIntNoExcept(&FindBy))
        Finded.push_back(*b);
      else if(b->Country == FindBy)
        Finded.push_back(*b);
      else if(b->City == FindBy)
        Finded.push_back(*b);
      else if(b->Time == FindBy)
        Finded.push_back(*b);
      else if(b->Temp == FindBy)
        Finded.push_back(*b);
      else if(b->Humidity == FindBy)
        Finded.push_back(*b);
    }
  }

  Print(&Finded);
}
