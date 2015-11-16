
#ifndef FUNCTIONMANAGER_H
#define	FUNCTIONMANAGER_H

#include <string>
using namespace std;
#include "enum.h"
#include "HashTable.h"

class FunctionsManager {
public:
  /**
   * Empty constructor
   */
  FunctionsManager();
  
  /**
   * Copy constructor
   * @param orig
   */
  FunctionsManager(const FunctionsManager& orig);
  
  /**
   * Destructor
   */
  virtual ~FunctionsManager();
  
  /**
   * Initializes the list of possible functions for neuron operations. It is implemented on FunctionsManager.Init.cpp
   * @return 
   */
  ReturnType InitializeManager();
  
  /**
   * Loads the pointer to the function specified by it's table name
   * @param FunctionNameP    Name of the function
   * @param FunctionPointerP Pointer to return the function pointer
   * @return 
   */
  ReturnType GetFunction(string FunctionNameP, void* &FunctionPointerP);
  
private:
  HashTable<void*> Functions;
} ;

#endif
