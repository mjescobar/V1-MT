/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

//#include <vector>
//#include <string>
#include <fstream>
//#include <string.h>
//using namespace std;
//#include "enum.h"
//#include "define.h"
#include "tools.h"
//#include "HashEntry.h"
//#include "HashTable.h"
//#include "LogManager.h"
//#include "SettingsManager.h"
#include "CommandManager.h"
#include "InterpreterManager.h"
//#include "Globals.h"
#include "extern.h"
#include "main.h"
#include "NeuronmentCommand.h"
#include "CommandManager.h"

// Stores the warning messages after a function termination
string ReturnMessage;
// Sets the log management instance of LogManager
LogManager Log;
// Stores the variables
//SettingsManager Variables;
// Single Simulator for outside optimization testing
//SimulationManager SingleSimulator;
// For early terminating a nproc reading
//bool EarlyReturn = false;

int main(int argc, char** argv)
{
  // Initialize global variables that require initialization
  ReturnCatch(SetGlobals());
  // Program Header
  ReturnCatch(Log.DisplayHeader());
  // Processing command line
  ReturnCatch(ProcessCommandLine(argc, argv), "ContinueOnFail");
  // Program Footer
  ReturnCatch(Log.DisplayFooter());
  return 0;
}

ReturnType ProcessCommandLine(int argcP, char** argvP)
{
  CommandManager CommandLine(argcP, argvP);
  //Lothar:
  //-verbose_messages
  //-no_verbose_messages
  //-no_output
  //-time
  return rescue_nproc(CommandLine);
}

ReturnType SetGlobals()
{
  // Initialize system variables list
  //Variables.InitializeVariables();
  // Returning process result
  return ReturnSuccess;
}
