
#ifndef INTERPRETERMANAGER_H
#define	INTERPRETERMANAGER_H

#include <fstream>
using namespace std;
#include "HashTable.h"
#include "CommandLine.h"

class Interpreter {
public:
  Interpreter();
  Interpreter(const Interpreter& orig);
  Interpreter(string NprocFileP);
  virtual ~Interpreter();
  //  bool SetNproc(string NprocP);
  ReturnType LoadFile();
  ReturnType CloseFile();
  ReturnType Process();
  ReturnType InitializeInterpreter();
  //  ReturnType Execute();
private:
  ReturnType GetNextLine(string &LineP);
  ReturnType ProcessLine(CommandLine &LocalManagerP);
  ReturnType ProcessCommand(CommandLine &LocalManagerP);

  bool EndOfFileReached;
  bool ReadyForReading;
  string NprocFile;
  string LastLine;
  clock_t ElapsedTime;
  ifstream NprocStream;
  HashTable<void*> Commands;
  CommandLine *LocalManager;
};

#endif
