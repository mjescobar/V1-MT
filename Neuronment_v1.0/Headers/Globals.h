/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#include "ND_Neuron.h"
#include "V1_Neuron.h"
#include "MT_Neuron.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "SimulationManager.h"
#include "InterpreterManager.h"

extern LogManager Log;
extern SettingsManager Variables;
extern SimulationManager SingleSimulator;
extern InterpreterManager Interpreter;
extern int NprocNesting;
extern bool ElapsedTimeInitialized;
extern clock_t ElapsedTime;

#endif	/* GLOBALS_H */
