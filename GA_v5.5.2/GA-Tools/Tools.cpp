/* 
 * File:   Tools.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 11, 2012, 11:50 AM
 */

#include <stdio.h>

#include "Tools.h"

void PrintMemory(const char *msg){
  struct sysinfo memInfo;
  sysinfo (&memInfo);
  long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
  virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
  virtualMemUsed *= memInfo.mem_unit;
  printf("%012lld",virtualMemUsed);
}
