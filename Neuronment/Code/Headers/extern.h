
#ifndef EXTERN_H
#define EXTERN_H

#include <string>
#include "LogManager.h"
#include "Interpreter.h"
#include "SimulatorManager.h"
#include "VariableManager.h"
#include "FunctionsManager.h"

// Global Variables
extern bool       EarlyReturn;
extern string     ErrorMessage;
extern ReturnType ErrorReturn;

// Global Object Instances
extern LogManager       Log;
extern VariableManager  GlobalVariables;
extern SimulatorManager SimulatorDepository;
extern FunctionsManager FunctionDepository;

#endif
