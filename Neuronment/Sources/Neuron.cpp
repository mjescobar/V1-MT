
#include <vector>
using namespace std;
#include "tools.h"
#include "extern.h"
#include "Neuron.h"
#include "LogManager.h"
#include "NeuronType.h"

template <class DataType> Neuron<DataType>::Neuron()
{
}

template <class DataType> Neuron<DataType>::Neuron(const Neuron& orig)
{
  Id = orig.Id;
  Group = orig.Group;
  Type = orig.Type;
  Activation = orig.Activation;
  LinksInt = orig.LinksInt;
  LinksBool = orig.LinksBool;
  LinksDouble = orig.LinksDouble;
  LinksString = orig.LinksString;
  CurrentPointer = orig.CurrentPointer;
}

template <class DataType> Neuron<DataType>::~Neuron()
{
}

template <class DataType> Neuron<DataType>::Neuron(NeuronType *TypeP, string GroupP, int IdP, vector<DataType> BaseActivationP, vector<string> ParameterValuesP)
{
  Id = IdP;
  Group = Group;
  ParameterValues = ParameterValuesP;
  string NeuronTypeDataType;
  TypeP->GetDataType(NeuronTypeDataType);
  if (NeuronTypeDataType != TypeToString(DataType())) {
    Log.Message("DV-036");
  }
  Type = TypeP;
  int ActivationLevels;
  ReturnCatch(Type->GetActivationLevels(ActivationLevels));
  if (BaseActivationP.size() != ActivationLevels) {
    Log.Message("DV-035");
  }
  for (int i = 0; i < ActivationLevels; i++) {
    Activation.push_back(vector<DataType>());
    Activation[i].push_back(BaseActivationP[i]);
  }
  CurrentPointer = 0;
}

template class Neuron<int>;
template class Neuron<bool>;
template class Neuron<double>;
template class Neuron<string>;
