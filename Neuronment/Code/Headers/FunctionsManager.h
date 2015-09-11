
#ifndef FUNCTIONMANAGER_H
#define	FUNCTIONMANAGER_H

#include <string>
using namespace std;
#include "enum.h"
#include "HashTable.h"

class FunctionsManager {
public:
  FunctionsManager();
  FunctionsManager(const FunctionsManager& orig);
  virtual ~FunctionsManager();
  ReturnType InitializeManager();
  ReturnType GetFunction(string FunctionNameP, void* &FunctionPointerP);
private:
  HashTable<void*> Functions;
};

#endif
