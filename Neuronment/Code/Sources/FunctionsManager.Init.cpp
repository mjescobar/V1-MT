
#include "FunctionsManager.h"
#include "Functions.h"

ReturnType FunctionsManager::InitializeManager()
{
  Functions.PutEntryQuick("IO_ReadFromFile", (void*) Function000000);
  Functions.PutEntryQuick("Operations_MultiplicationSum", (void*) Function000001);
  return ReturnSuccess;
}
