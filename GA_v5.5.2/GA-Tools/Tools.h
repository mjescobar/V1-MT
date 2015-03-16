/* 
 * File:   Tools.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on December 2, 2012, 7:01 PM
 */

#ifndef TOOLS_H
#define	TOOLS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "sys/types.h"
#include "sys/sysinfo.h"
	
void PrintMemory(const char *msg=NULL);

#ifdef	__cplusplus
}
#endif

#endif	/* TOOLS_H */

