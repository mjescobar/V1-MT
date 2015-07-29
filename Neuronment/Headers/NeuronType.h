
#include <string>
#include <vector>
using namespace std;
#include "enum.h"

#ifndef NEURONTYPE_H
#define NEURONTYPE_H

class NeuronType {
public:
    NeuronType();
    NeuronType(const NeuronType& orig);
    NeuronType(string NameP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
    virtual ~NeuronType();
    ReturnType GetName(string &NameP);
    ReturnType SetFastInput(vector<string> FastInputP);
private:
    string Name;
    int ActivationLevels;
    vector<string> ActivationFunctions;
    vector<string> ParametersName;
    vector<string> ParametersType;
    vector<string> FastInput;
};

#endif /* NEURONTYPE_H */

