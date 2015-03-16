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

// Stores the environment settings
SettingsManager Environment;

// Stores the simulation settings
SettingsManager Simulation;

// Single Simulator for outside optimization testing
SimulationManager SingleSimulator;

// Main Interpreter Manager
InterpreterManager Interpreter;

// For elapsed timing calculations
bool ElapsedTimeInitialized;
clock_t ElapsedTime;
