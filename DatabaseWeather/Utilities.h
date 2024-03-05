#include <string>
#include <iostream>

static int ArgToInt(std::string* Arg)
{
  int Value;
  try
  {
    Value = std::stoi(*Arg);
  }
  catch(std::invalid_argument ex)
  {
    std::cout << "**Invalid argument!\n";
    return -1;
  }
  return Value;
}

static int ArgToIntNoExcept(std::string* Arg)
{
  int Value;
  try
  {
    Value = std::stoi(*Arg);
  }
  catch(std::invalid_argument ex)
  {
    return -1;
  }
  return Value;
}
