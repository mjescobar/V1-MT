
#include <vector>


#include "NeuronType.h"

NeuronType::NeuronType()
{
}

NeuronType::NeuronType(const NeuronType& orig)
{
  Name = orig.Name;
  DataType = orig.DataType;
  ActivationLevels = orig.ActivationLevels;
  ActivationFunctions = orig.ActivationFunctions;
  ParametersName = orig.ParametersName;
  ParametersType = orig.ParametersType;
  FastInput = orig.FastInput;
}

NeuronType::~NeuronType()
{
}

NeuronType::NeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP)
{
  Name = NameP;
  DataType = DataTypeP;
  ActivationLevels = ActivationLevelsP;
  //Lothar check function compatibility
  ActivationFunctions = ActivationFunctionsP;
  ParametersName = ParametersNameP;
  ParametersType = ParametersTypeP;
  FastInput.clear();
}

ReturnType NeuronType::GetName(string &NameP)
{
  NameP = Name;
  return ReturnSuccess;
}

ReturnType NeuronType::GetActivationLevels(int &ActivationLevelsP)
{
  ActivationLevelsP = ActivationLevels;
  return ReturnSuccess;
}

ReturnType NeuronType::SetFastInput(vector<string> FastInputP)
{
  FastInput = FastInputP;
  return ReturnSuccess;
}

ReturnType NeuronType::GetFastInput(vector<string> &FastInputP)
{
  FastInputP = FastInput;
  return ReturnSuccess;
}

ReturnType NeuronType::GetDataType(string &DataTypeP)
{
  DataTypeP = DataType;
  return ReturnSuccess;
}

ReturnType NeuronType::GetParametersName(vector<string> &ParametersNameP)
{
  ParametersNameP = ParametersName;
  return ReturnSuccess;
}