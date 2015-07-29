
#include <string>
#include <vector>
using namespace std;
#include "enum.h"
#include "Simulator.h"

#ifndef SIMULATORMANAGER_H
#define SIMULATORMANAGER_H

class SimulatorManager {
public:
    SimulatorManager();
    SimulatorManager(const SimulatorManager& orig);
    virtual ~SimulatorManager();
    ReturnType AddSimulator();
    ReturnType RemoveSimulator(int SimulatorIdP);
    ReturnType SetSimulatorCurrent(int SimulatorIdP);
    ReturnType GetSimulatorCurrent(int &CurrentSimulatorP);
    ReturnType GetSimulatorList(vector<string> &SimulatorListP);
    ReturnType GetSimulatorCount(int &CountP);
private:
    int CurrentSimulator;
    vector<Simulator> SimulatorList;
};

#endif /* SIMULATORMANAGER_H */

