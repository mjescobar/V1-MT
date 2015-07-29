
#include <string>
#include <vector>
using namespace std;
#include "enum.h"
#include "NeuronType.h"
#include "Simulator.h"

#ifndef SIMULATORMANAGER_H
#define SIMULATORMANAGER_H

class SimulatorManager {
public:
    SimulatorManager();
    SimulatorManager(const SimulatorManager& orig);
    virtual ~SimulatorManager();
    ReturnType AddSimulator();
    ReturnType AddNeuronType(string NameP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
    ReturnType RemoveSimulator(int SimulatorIdP);
    ReturnType SetSimulatorCurrent(int SimulatorIdP);
    ReturnType GetSimulatorCurrent(int &CurrentSimulatorP);
    ReturnType GetSimulatorList(vector<string> &SimulatorListP);
    ReturnType GetSimulatorCount(int &CountP);
private:
    int CurrentSimulator;
    vector<Simulator> SimulatorList;
    vector<NeuronType> NeuronTypes;
};

#endif /* SIMULATORMANAGER_H */

