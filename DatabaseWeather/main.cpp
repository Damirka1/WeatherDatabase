#include <fstream>
#include "TableWorker.h"
#include "CommandReader.h"

int main(int argc, char** argv)
{
  // Используется для работ с файлом базы данных.
  FileDescriptor FD;
  // Используется для обработке и хранения данных базы данных.
  TableWorker TW;
  // Считывает все входящие в консоль команды и выполняет их.
  CommandReader CR(&FD, &TW);

  return CR.StartRead();
}
