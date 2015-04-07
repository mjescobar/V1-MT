/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "InterpreterManager.h"
#include "Globals.h"
#include "main.h"

int main(int argc, char** argv)
{
  // Initialize global variables that require initialization
  SetGlobals();
  // Initialize Globals
  Log.InitializeMessages();
  Variables.InitializeVariables();
  // Read command line arguments
  ReadCommandLineArguments(argc, argv);
  // Program Header
  Log.DisplayHeader();
  // Open file to read
  Interpreter.LoadFile();
  // Reads the nproc file line by line
  Interpreter.Process();
  // Close nproc file
  Interpreter.CloseFile();
  // Program Footer
  Log.DisplayFooter();
  return 0;
}

bool ReadCommandLineArguments(int argc, char** argv)
{
  bool NprocStatus = false;
  bool VerboseDevelopmentStatus = false;
  bool VerboseMessagesStatus = false;
  for (int i = 1; i < argc; i++) {
    // Identifying argument label
    if (argv[i][0] == '-') {
      // Checking if procedure file
      if (strcmp(argv[i], "-nproc") == 0) {
        // if the procedure file has already been stored
        if (NprocStatus) {
          Log.Message("UI-001");
          Log.DisplayHelp();
          RuntimeAssertion();
          return false;
        } else {
          if (i + 1 < argc) {
            i++;
            if (argv[i][0] != '-') {
              if (Interpreter.SetNproc(ICstringToString(argv[i]))) {
                NprocStatus = true;
                continue;
              } else {
                DevelopmentAssertion();
              }
            } else {
              Log.Message("UI-004");
              RuntimeAssertion();
              return false;
            }
          } else {
            Log.Message("UI-004");
            RuntimeAssertion();
            return false;
          }
        }
      }
      if (strcmp(argv[i], "-verbose_messages") == 0) {
        if (VerboseMessagesStatus) {
          Log.Message("UI-001");
          Log.DisplayHelp();
          RuntimeAssertion();
          return false;
        } else {
          Log.SetMessages();
          VerboseMessagesStatus = true;
          continue;
        }
      }
      if (strcmp(argv[i], "-no_verbose_messages") == 0) {
        if (VerboseMessagesStatus) {
          Log.Message("UI-001");
          Log.DisplayHelp();
          RuntimeAssertion();
          return false;
        } else {
          Log.UnsetMessages();
          VerboseMessagesStatus = true;
          continue;
        }
      }
      if (strcmp(argv[i], "-no_output") == 0) {
        Log.SetFullSilentOutput();
        continue;
      }
      if (strcmp(argv[i], "-time") == 0) {
        Variables.QuickSetSetting(SHOW_ELAPSED_TIME, "true");
        continue;
      }
      Log.Message("UI-003: " + string(argv[i]));
      Log.DisplayHelp();
      DevelopmentAssertion();
      continue;
    } else {
      Log.Message("UI-002");
      Log.DisplayHelp();
      RuntimeAssertion();
      return false;
    }
  }
  return true;
}

bool SetGlobals()
{
  return true;
}
