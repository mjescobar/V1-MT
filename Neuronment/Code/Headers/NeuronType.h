
#include <string>
#include <vector>
using namespace std;
#include "enum.h"

#ifndef NEURONTYPE_H
#define NEURONTYPE_H

class NeuronType {
public:
  /**
   * Empty constructor
   */
  NeuronType();
  
  /**
   * Copy constructor
   * @param orig
   */
  NeuronType(const NeuronType& orig);
  
  /**
   * Main constructor
   * @param NameP                Name for the neuron type
   * @param DataTypeP            Type for the neuron type
   * @param ActivationLevelsP    Number of activation levels to be considered
   * @param ActivationFunctionsP List of functions to calculate the activation of each activation level
   * @param ParametersNameP      Name of the parameters provided at construction
   * @param ParametersTypeP      Values of the parameters provided at construction
   */
  NeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
  
  /**
   * Destructor
   */
  virtual ~NeuronType();
  
  /**
   * Returns the neuron type name
   * @param NameP Pointer to return the value
   * @return 
   */
  ReturnType GetName(string &NameP);
  
  /**
   * Returns the neuron type data type
   * @param DataTypeP Pointer to return the value
   * @return 
   */
  ReturnType GetDataType(string &DataTypeP);
  
  /**
   * Returns the activation levels for the neuron type
   * @param ActivationLevelsP Pointer to return the value
   * @return 
   */
  ReturnType GetActivationLevels(int &ActivationLevelsP);
  
  /**
   * Configures a list of parameters for input without declaration at neuron construction
   * @param FastInputP The vector containing the parameter list
   * @return 
   */
  ReturnType SetFastInput(vector<string> FastInputP);
  
  /**
   * Returns the configured list for fast input
   * @param FastInputP Pointer to return the values
   * @return 
   */
  ReturnType GetFastInput(vector<string> &FastInputP);
  
  /**
   * Returns a list of the parameters names valid for the neuron type
   * @param ParametersNameP Pointer to return the list
   * @return 
   */
  ReturnType GetParametersName(vector<string> &ParametersNameP);
  
  /**
   * Returns a pointer to the function that should be used to calculate an specific activation level for the neuron type
   * @param LevelP    The activation level to retrieve the information
   * @param FunctionP Pointer to return the pointer to the function
   * @return 
   */
  ReturnType GetActivationFunction(int LevelP, void* &FunctionP);

  /**
   * Validates if the neuron type instance name corresponds to the specified value
   * @param NameP The value to check
   * @return 
   */  
  ReturnType IsName(string NameP);
  
  /**
   * Validates if the neuron type instance data type corresponds to the specified value
   * @param DataTypeP The data type to validate
   * @return 
   */
  ReturnType IsDataType(string DataTypeP);
  
  /**
   * Validates if the neuron activation levels corresponds to the indicated value
   * @param ActivationLevelsP The value to validate
   * @return 
   */
  ReturnType IsActivationLevels(string ActivationLevelsP);
  
private:
  string Name;
  string DataType;
  int ActivationLevels;
  vector<string> ActivationFunctions;
  vector<void*> ActivationFunctionsPointers;
  vector<string> ParametersName;
  vector<string> ParametersType;
  vector<string> FastInput;
} ;

#endif
