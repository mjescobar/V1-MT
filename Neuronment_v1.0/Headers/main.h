/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef MAIN_H
#define	MAIN_H

/**
 * Read and process command line arguments
 * @param argc main argc
 * @param argv main argv
 * @return true if success
 */
bool ReadCommandLineArguments(int argc, char** argv);

/**
 * Initialize the global values
 * @return true if success
 */
bool SetGlobals();

#endif	/* MAIN_H */
