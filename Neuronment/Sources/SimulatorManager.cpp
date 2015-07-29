
#include "tools.h"
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
