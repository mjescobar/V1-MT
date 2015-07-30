
#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <vector>
using namespace std;
#include "enum.h"
#include "Neuron.h"

class Simulator {
public:
    Simulator();
    Simulator(const Simulator& orig);
    virtual ~Simulator();
    ReturnType AddNeuron(NeuronType *NeuronTypeP, string GroupP, int IdP, string BaseActivationP, vector<string> ParametersValueP);
#if 0
    bool InitializeNeurons();
    bool AddV1Diffusion();
    bool Simulate(int StepsP);
    bool PrintV1Activation(OrientationType OTypeP);
    bool PrintMTActivation(OrientationType OTypeP);
    bool PrintV1Activation(OrientationType OTypeP, string DestinationP);
    bool PrintMTActivation(OrientationType OTypeP, string DestinationP);
    bool PrintV1ExternalExcitation(int StepP, string DestinationP);
    bool PrintV1ExternalExcitation(int StepP);
    double GetV1Radius();
private:
    bool CreateV1NeuronVector();
    bool SetV1ActMethod();
    bool SetV1DacMethod();
    bool CreateMTNeuronVector();
    bool SetMTActMethod();
    bool SetMTDacMethod();
    bool SetV1V1ConnectionLinks();
    bool SetV1MTConnectionLinks();
#endif
private:
    vector<Neuron<int> > NeuronsInt;
    vector<Neuron<bool> > NeuronsBool;
    vector<Neuron<double> > NeuronsDouble;
    vector<Neuron<string> > NeuronsString;
    //double V1Radius;
    // MT Parameters
    //vector<MT_Neuron> MT_Neurons;
    // Status
    //bool Initialized;
};

#endif	/* SIMULATIONMANAGER_H */
