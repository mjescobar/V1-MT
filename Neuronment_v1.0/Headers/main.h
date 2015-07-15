/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef MAIN_H
#define	MAIN_H

//#include "LogManager.h"

ReturnType SetGlobals();

ReturnType ProcessCommandLine(int argcP, char** argvP);

#if 0
bool ReadCommandLineArguments(int argc, char** argv);
#endif

#endif	/* MAIN_H */
