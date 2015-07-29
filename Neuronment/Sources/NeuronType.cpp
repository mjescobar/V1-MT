
#include "NeuronType.h"

NeuronType::NeuronType()
{
}

NeuronType::NeuronType(const NeuronType& orig)
{
  Name = orig.Name;
  ActivationLevels = orig.ActivationLevels;
  ActivationFunctions = orig.ActivationFunctions;
  ParametersName = orig.ParametersName;
  ParametersType = orig.ParametersType;
}

NeuronType::~NeuronType()
{
}

NeuronType::NeuronType(string NameP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP)
{
  Name = NameP;
  ActivationLevels = ActivationLevelsP;
  ActivationFunctions = ActivationFunctionsP;
  ParametersName = ParametersNameP;
  ParametersType = ParametersTypeP;
}