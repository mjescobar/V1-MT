
#include <string>
#include <vector>
using namespace std;

#ifndef NEURONTYPE_H
#define NEURONTYPE_H

class NeuronType {
public:
    NeuronType();
    NeuronType(const NeuronType& orig);
    NeuronType(string NameP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
    virtual ~NeuronType();
private:
    string Name;
    int ActivationLevels;
    vector<string> ActivationFunctions;
    vector<string> ParametersName;
    vector<string> ParametersType;
};

#endif /* NEURONTYPE_H */

