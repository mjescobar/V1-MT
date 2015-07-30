
#include <vector>
using namespace std;
#include "NeuronType.h"

#ifndef NEURON_H
#define NEURON_H

template <class DataType> class Neuron {
public:
    Neuron();
    Neuron(const Neuron& orig);
    virtual ~Neuron();
    Neuron(NeuronType *TypeP, string GroupP, int IdP, vector<DataType> BaseActivationP, vector<string> ParameterValuesP);
private:
    int Id;
    string Group;
    NeuronType *Type;
    vector<string> ParameterValues;
    vector<vector<DataType> > Activation;
    vector<Neuron<int>* > LinksInt;
    vector<Neuron<bool>* > LinksBool;
    vector<Neuron<double>* > LinksDouble;
    vector<Neuron<string>* > LinksString;
    int CurrentPointer;
};

#endif /* NEURON_H */

