
#include <vector>
using namespace std;
#include "tools.h"
#include "extern.h"
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
  ActivationFunctionsPointers = orig.ActivationFunctionsPointers;
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
  for (int i = 0; i < ActivationLevels; i++) {
    void* Tmp;
    ReturnCatch(FunctionDepository.GetFunction(ActivationFunctions[i], Tmp));
    ActivationFunctionsPointers.push_back(Tmp);
  }
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

ReturnType NeuronType::GetActivationFunction(int LevelP, void* &FunctionP)
{
  if (LevelP < 0 || LevelP >= ActivationLevels) {
    //Lothar error
    return ReturnFail;
  }
  FunctionP = ActivationFunctionsPointers[LevelP];
  return ReturnSuccess;
  // Lothar: hacer un catch mas completo y elegante. Estoy chato en el avión
}

ReturnType NeuronType::IsName(string NameP)
{
  if (NameP == Name) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType NeuronType::IsDataType(string DataTypeP)
{
  if (DataTypeP == DataType) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType NeuronType::IsActivationLevels(string ActivationLevelsP)
{
  if (ToInt(ActivationLevelsP) == ActivationLevels) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}
