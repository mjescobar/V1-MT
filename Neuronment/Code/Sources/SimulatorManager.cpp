
#include <vector>
#include <string>
using namespace std;
#include "extern.h"
#include "tools.h"
#include "LogManager.h"
#include "NeuronType.h"
#include "SimulatorManager.h"

SimulatorManager::SimulatorManager()
{
  Current = -1;
}

SimulatorManager::SimulatorManager(const SimulatorManager& orig)
{
}

SimulatorManager::~SimulatorManager()
{
}

Simulator* SimulatorManager::CurrentSimulator()
{
  if (Current < 0 || Current >= SimulatorList.size()) {
    Log.CodedMessage("DV-038"); //Lothar: null return just in case??
  }
  return &(SimulatorList[Current]);
}

Simulator* SimulatorManager::GetSimulator(int IdP)
{
  if (IdP < 0 || IdP >= SimulatorList.size()) {
    Log.CodedMessage("DV-038"); //Lothar: null return just in case??
  }
  return &(SimulatorList[IdP]);
}

ReturnType SimulatorManager::AddSimulator()
{
  SimulatorList.push_back(Simulator());
  if (Current < 0) {
    Current = 0;
  }
  return ReturnSuccess;
}

ReturnType SimulatorManager::GetSimulatorCurrent(int &CurrentP)
{
  CurrentP = Current;
  return ReturnSuccess;
}

ReturnType SimulatorManager::GetSimulatorList(vector<string> &SimulatorListP)
{
  SimulatorListP.clear();
  for (int i = 0; i < SimulatorList.size(); i++) {
    SimulatorListP.push_back("Simulator: " + ToString(i));
  }
  return ReturnSuccess;
}

ReturnType SimulatorManager::SetSimulatorCurrent(int SimulatorIdP)
{
  if (SimulatorIdP >= -1 && SimulatorIdP < SimulatorList.size()) {
    Current = SimulatorIdP;
    return ReturnSuccess;
  }
  return ReturnFail;
}

ReturnType SimulatorManager::RemoveSimulator(int SimulatorIdP)
{
  if (SimulatorIdP >= 0 && SimulatorIdP < SimulatorList.size()) {
    SimulatorList.erase(SimulatorList.begin() + SimulatorIdP);
    return ReturnSuccess;
  }
  return ReturnFail;
}

ReturnType SimulatorManager::GetSimulatorCount(int &CountP)
{
  CountP = SimulatorList.size();
  return ReturnSuccess;
}

ReturnType SimulatorManager::AddNeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP)
{
  NeuronTypes.push_back(NeuronType(NameP, DataTypeP, ActivationLevelsP, ActivationFunctionsP, ParametersNameP, ParametersTypeP));
  return ReturnSuccess;
}

ReturnType SimulatorManager::SetNeuronTypeFastInput(string NameP, string FastInputP)
{
  NeuronType *Type = NULL;
  GetNeuronType(NameP, &Type);
  vector<string> FastInputVector;
  Tokenize(FastInputP, FastInputVector);
  Type->SetFastInput(FastInputVector);
  return ReturnSuccess;
}

ReturnType SimulatorManager::GetNeuronType(string NameP, NeuronType **TypeP)
{
  int Id = -1;
  for (int i = 0; i < NeuronTypes.size(); i++) {
    string Name;
    NeuronTypes[i].GetName(Name);
    if (Name == NameP) {
      *TypeP = &(NeuronTypes[i]);
      return ReturnSuccess;
    }
  }
  return Return(ReturnFail,"DV-034");
}
