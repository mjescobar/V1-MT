
#include "tools.h"
#include "LogManager.h"
#include "CommandLine.h"
#include "VariableManager.h"
#include "SimulatorManager.h"
#include "FunctionsManager.h"
#include "InterpreterCommands.h"

LogManager Log;
bool EarlyReturn = false;
VariableManager GlobalVariables;
FunctionsManager FunctionDepository;
SimulatorManager SimulatorDepository;

int main(int argc, char** argv)
{   
  ReturnCatch(Log.DisplayHeader());

  CommandLine CommandLine(argc, argv);
  rescue_nproc(CommandLine);

  ReturnCatch(Log.DisplayFooter());
  return 0;
}
