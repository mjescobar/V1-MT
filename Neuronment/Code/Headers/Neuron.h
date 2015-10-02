
#include <vector>
using namespace std;
#include "NeuronType.h"
#include "Simulator.h"

#ifndef NEURON_H
#define NEURON_H

class Neuron {
public:
  Neuron();
  Neuron(const Neuron& orig);
  virtual ~Neuron();
  Neuron(NeuronType *TypeP, string GroupP, int IdP, vector<string> BaseActivationP, vector<string> ParameterValuesP);
  ReturnType AddLink(Neuron *NeuronP, vector<string> ParametersP);
  ReturnType LoadActivation(vector<vector<double> > ExternalActivationP);
  ReturnType LoadActivation(vector<double> ExternalActivationP, int LevelP);
  ReturnType Calculate(int StepP);
  ReturnType Calculate(int StepP, int LevelP);
  ReturnType GetActivation(int LevelP, int StepP, double &ActivationP);//Lothar: replicate for other data types
  ReturnType GetActivation(vector<vector <double> > &ActivationP);
//  ReturnType GetLinks(vector<Neuron*> &LinksP);
//  ReturnType GetActivationSize(int &ActivationSize);
//  ReturnType CalculateActivationStep();
//  template <class DataType> ReturnType GetActivationStep(int StepP, DataType &ActivationP);
  ReturnType ActivationPushBack(int LevelP, double ValueP); // Lothar check for other types
  ReturnType GetTypeParameter(string NameP, string &ValueP);
  ReturnType GetTypeParameter(string NameP, double &ValueP); //Lothar check for other types
  ReturnType GetLinkParameter(int LinkP, string NameP, double &ValueP); //Lothar: replicar para diferentes data types
  ReturnType GetLinksCount(int &CountP);
  ReturnType GetLinksNeuron(int IndexP, Neuron* &NeuronP);
  ReturnType GetActivationSize(int LevelP, int &SizeP);
  ReturnType IsId(string IdP);
  ReturnType IsGroup(string GroupP);
  ReturnType IsType(string TypeP);
  ReturnType PrintActivation(int FromP, int ToP);
  ReturnType GetGroupName(string &GroupNameP);
  ReturnType GetTypeName(string &TypeNameP);
private:
  // Identification parameters
  int Id;
  string Group;
  NeuronType *Type;
  // Behavior parameters
  vector<string> ParameterValues;
  // Linking parameters
  vector<Neuron*> LinkingPointers;
  vector<vector<string> > LinkingParameters;
  vector<vector<string> > LinkingParametersLabels;
  // Activation storage
  vector<vector<double> > Activation_double;
};

#endif
