
#include "FunctionsManager.h"

FunctionsManager::FunctionsManager() :
Functions(SIMULATOR_ACTIVATION_FUNCTION_HASH_SIZE) //Lothar: set correct define name
{
  InitializeManager();
}

FunctionsManager::FunctionsManager(const FunctionsManager& orig)
{
}

FunctionsManager::~FunctionsManager()
{
}

ReturnType FunctionsManager::GetFunction(string FunctionNameP, void* &FunctionPointerP)
{
  Functions.GetEntryQuick(FunctionNameP, FunctionPointerP);
  return ReturnSuccess;
}
