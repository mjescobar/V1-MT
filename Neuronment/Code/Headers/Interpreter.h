
#ifndef INTERPRETERMANAGER_H
#define	INTERPRETERMANAGER_H

#include <fstream>
using namespace std;
#include "HashTable.h"
#include "CommandLine.h"

class Interpreter {
public:
  /**
   * Default constructor
   */
  Interpreter();
  
  /**
   * Copy constructor
   * @param orig
   */
  Interpreter(const Interpreter& orig);
  
  /**
   * Creates a new interpreter instance from the specified filename
   * @param NprocFileP
   */
  Interpreter(string NprocFileP);
  
  /**
   * Destructor
   */
  virtual ~Interpreter();

  /**
   * Opens the file stream for the previously specified nproc file
   * @return 
   */
  ReturnType LoadFile();
  
  /**
   * Closes the nproc file stream associated to the instance
   * @return 
   */
  ReturnType CloseFile();
  
  /**
   * Processes the nproc file associated to the instance
   * @return 
   */
  ReturnType Process();
  
private:
  /**
   * Loads the list of directives valid to the interpreter. Implemented on Interpreter.Init.cpp
   * @return 
   */
  ReturnType InitializeInterpreter();
  
  /**
   * Gets a next line from the input stream to interpret
   * @param LineP The pointer to return the line
   * @return 
   */
  ReturnType GetNextLine(string &LineP);
  
  /**
   * Processes a full command line already inside a CommandLine instance
   * @param LocalManagerP
   * @return 
   */
  ReturnType ProcessLine(CommandLine &LocalManagerP);
  
  /**
   * Processes the specific command declared on the CommandLine instance
   * @param LocalManagerP
   * @return 
   */
  ReturnType ProcessCommand(CommandLine &LocalManagerP);

  bool EndOfFileReached;
  bool ReadyForReading;
  string NprocFile;
  string LastLine;
  clock_t ElapsedTime;
  ifstream NprocStream;
  HashTable<void*> Commands;
  CommandLine *LocalManager;
} ;

#endif
