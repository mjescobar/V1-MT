
#include <string>
#include <vector>
using namespace std;
#include "enum.h"

#ifndef NEURONTYPE_H
#define NEURONTYPE_H

class NeuronType {
public:
  NeuronType();
  NeuronType(const NeuronType& orig);
  NeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
  virtual ~NeuronType();
  ReturnType GetName(string &NameP);
  ReturnType GetDataType(string &DataTypeP);
  ReturnType GetActivationLevels(int &ActivationLevelsP);
  ReturnType SetFastInput(vector<string> FastInputP);
  ReturnType GetFastInput(vector<string> &FastInputP);
  ReturnType GetParametersName(vector<string> &ParametersNameP);
  ReturnType GetActivationFunction(int LevelP, void* &FunctionP);
  ReturnType GetListsNames(vector<string> &ListNamesP);
  ReturnType IsName(string NameP);
  ReturnType IsDataType(string DataTypeP);
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
};

#endif
