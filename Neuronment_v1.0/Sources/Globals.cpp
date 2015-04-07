/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;
#include "enum.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "ND_Neuron.h"
#include "V1_Neuron.h"
#include "MT_Neuron.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "SimulationManager.h"
#include "InterpreterManager.h"

// Sets the log management instance of LogManager
LogManager Log;

// Stores the variables
SettingsManager Variables;

// Single Simulator for outside optimization testing
SimulationManager SingleSimulator;

// Main Interpreter Manager
InterpreterManager Interpreter;

// For counting the Nproc nexting level
int NprocNesting = 0;

// For early terminating a nproc reading
bool EarlyReturn = false;

// For elapsed timing calculations
bool ElapsedTimeInitialized;
clock_t ElapsedTime;
