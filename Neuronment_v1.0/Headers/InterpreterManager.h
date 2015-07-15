/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef INTERPRETERMANAGER_H
#define	INTERPRETERMANAGER_H

#include <fstream>
using namespace std;
#include "CommandManager.h"
#include "HashTable.h"

class InterpreterManager {
public:
  InterpreterManager();
  InterpreterManager(const InterpreterManager& orig);
  InterpreterManager(string NprocFileP);
  virtual ~InterpreterManager();
  //  bool SetNproc(string NprocP);
  ReturnType LoadFile();
  ReturnType CloseFile();
  ReturnType Process();
  ReturnType InitializeInterpreter();
  //  ReturnType Execute();
private:
  ReturnType GetNextLine(string &LineP);
  ReturnType ProcessLine(CommandManager &LocalManagerP);
  ReturnType ProcessCommand(CommandManager &LocalManagerP);

  bool EndOfFileReached;
  bool ReadyForReading;
  string NprocFile;
  string LastLine;
  clock_t ElapsedTime;
  ifstream NprocStream;
  HashTable<void*> Commands;
  CommandManager *LocalManager;
};

#endif	/* INTERPRETERMANAGER_H */
