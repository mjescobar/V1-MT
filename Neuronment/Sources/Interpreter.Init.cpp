
//#include <vector>
//#include <sstream>
//#include <fstream>
//using namespace std;
#include "enum.h"
//#include "define.h"
//#include "Tools.h"
//#include "HashEntry.h"
//#include "HashTable.h"
//#include "LogManager.h"
//#include "SettingsManager.h"
//#include "Globals.h"
#include "Interpreter.h"
#include "InterpreterCommands.h"

ReturnType Interpreter::InitializeInterpreter()
{
  Commands.PutEntryQuick("report_test", (void*) report_test);
  // I/O Interaction Commands
  Commands.PutEntryQuick("rescue_nproc", (void*) rescue_nproc);
  Commands.PutEntryQuick("rescue_end_nproc", (void*) rescue_end_nproc);
  // Variable management
  Commands.PutEntryQuick("varman_set", (void*) varman_set);
  Commands.PutEntryQuick("varman_get", (void*) varman_get);
  // Simulator management
  Commands.PutEntryQuick("setsim_add_simulator", (void*) setsim_add_simulator);
  Commands.PutEntryQuick("setsim_get_current_simulator", (void*) setsim_get_current_simulator);
  Commands.PutEntryQuick("setsim_get_simulators_list", (void*) setsim_get_simulators_list);
  Commands.PutEntryQuick("setsim_set_current_simulator", (void*) setsim_set_current_simulator);
  Commands.PutEntryQuick("setsim_remove_simulator", (void*) setsim_remove_simulator);
  Commands.PutEntryQuick("setsim_new_neuron_type", (void*) setsim_new_neuron_type);
  Commands.PutEntryQuick("setsim_add_neuron", (void*) setsim_add_neuron);
  Commands.PutEntryQuick("setsim_add_link", (void*) setsim_add_link);
  // Simulator calculations
  Commands.PutEntryQuick("runsim_simulate", (void*) runsim_simulate);
  return ReturnSuccess;
}
