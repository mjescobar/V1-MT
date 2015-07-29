
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
  CurrentSimulator = -1;
}

SimulatorManager::SimulatorManager(const SimulatorManager& orig)
{
}

SimulatorManager::~SimulatorManager()
{
}

ReturnType SimulatorManager::AddSimulator()
{
  Simulator ToAdd;
  SimulatorList.push_back(ToAdd);
  if (CurrentSimulator < 0) {
    CurrentSimulator = 0;
  }
  return ReturnSuccess;
}

ReturnType SimulatorManager::GetSimulatorCurrent(int &CurrentSimulatorP)
{
  CurrentSimulatorP = CurrentSimulator;
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
    CurrentSimulator = SimulatorIdP;
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

ReturnType SimulatorManager::AddNeuronType(string NameP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP)
{
  NeuronType ToAdd(NameP, ActivationLevelsP, ActivationFunctionsP, ParametersNameP, ParametersTypeP);
  NeuronTypes.push_back(ToAdd);
  return ReturnSuccess;
}

ReturnType SimulatorManager::SetNeuronTypeFastInput(string NameP, string FastInputP)
{
  NeuronType *Type = NULL;
  ReturnCatch(GetNeuronType(NameP, &Type));
  vector<string> FastInputVector;
  ReturnCatch(Tokenize(FastInputP, FastInputVector));
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
  Log.Message("DV-034");
  return ReturnFail;
}