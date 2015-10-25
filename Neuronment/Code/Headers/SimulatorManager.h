
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
    Simulator* CurrentSimulator();
    Simulator* GetSimulator(int IdP);
    ReturnType AddSimulator();
    ReturnType RemoveSimulator(int SimulatorIdP);
    ReturnType SetSimulatorCurrent(int SimulatorIdP);
    ReturnType GetSimulatorCurrent(int &CurrentSimulatorP);
    ReturnType GetSimulatorList(vector<string> &SimulatorListP);
    ReturnType GetSimulatorCount(int &CountP);
    ReturnType AddNeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
    ReturnType SetNeuronTypeFastInput(string NameP,string FastInputP);
    ReturnType GetNeuronType(string NameP, NeuronType **TypeP);
private:
    int Current;
    vector<Simulator> SimulatorList;
    vector<NeuronType> NeuronTypes;
};

#endif /* SIMULATORMANAGER_H */