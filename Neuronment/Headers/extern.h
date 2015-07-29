/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef EXTERN_H
#define EXTERN_H

#include <string>
#include "LogManager.h"
#include "InterpreterManager.h"
#include "SimulatorManager.h"
#include "VariableManager.h"

extern string ReturnMessage;
extern LogManager Log;
extern InterpreterManager Interpreter;
extern VariableManager Variable;
extern SimulatorManager CoreSimulator;
extern bool EarlyReturn;

#endif /* EXTERN_H */
