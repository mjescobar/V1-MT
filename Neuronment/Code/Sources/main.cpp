
#include "enum.h"
#include "tools.h"
#include "LogManager.h"
#include "CommandLine.h"
#include "VariableManager.h"
#include "SimulatorManager.h"
#include "FunctionsManager.h"
#include "InterpreterCommands.h"

// Global Variables
bool       EarlyReturn  = false;
string     ErrorMessage = "";
ReturnType ErrorReturn  = ReturnSuccess;

// Global Object Instances
LogManager       Log;
VariableManager  GlobalVariables;
FunctionsManager FunctionDepository;
SimulatorManager SimulatorDepository;

int main(int argc, char** argv)
{
  CommandLine CommandLine(argc, argv);

  Log.DisplayHeader();
  rescue_nproc(CommandLine);
  Log.DisplayFooter();

  return 0;
}
