
#include <vector>
#include <string>
using namespace std;
#include "enum.h"
#include "extern.h"
#include "Simulator.h"
#include "LogManager.h"
#include "NeuronType.h"

Simulator::Simulator():
InternalVariables()
{
}

Simulator::Simulator(const Simulator& orig)
{
  InternalVariables = orig.InternalVariables;
  Neurons = orig.Neurons;
}

Simulator::~Simulator()
{
}

ReturnType Simulator::AddNeuron(NeuronType *NeuronTypeP, string GroupP, int IdP, string BaseActivationP, vector<string> ParameterValuesP)
{
  vector<string> FromBaseActivation;
  Tokenize(BaseActivationP, FromBaseActivation);
  Neurons.push_back(Neuron(NeuronTypeP, GroupP, IdP, FromBaseActivation, ParameterValuesP));
  return ReturnSuccess;
}

ReturnType Simulator::GetNeurons(vector<Neuron*> &NeuronsP)
{
  NeuronsP.clear();
  for (int i = 0; i < Neurons.size(); i++) {
    NeuronsP.push_back(&Neurons[i]);
  }
  return ReturnSuccess;
}

ReturnType Simulator::GetNeurons(vector<Neuron*> &NeuronsP, string IdP, string TypeP, string GroupP)
{
  NeuronsP.clear();
  for (int i = 0; i < Neurons.size(); i++) {
    bool ToPut = true;
    if (IdP != "") {
      if (Neurons[i].IsId(IdP) == ReturnFail) {
        ToPut = false;
      }
    }
    if (ToPut && (TypeP != "")) {
      if (Neurons[i].IsType(TypeP) == ReturnFail) {
        ToPut = false;
      }
    }
    if (ToPut && (GroupP != "")) {
      if (Neurons[i].IsGroup(GroupP) == ReturnFail) {
        ToPut = false;
      }
    }
    if (ToPut) {
      NeuronsP.push_back(&Neurons[i]);
    }
  }
  return ReturnSuccess;
}

ReturnType Simulator::Simulate()
{
  vector<int> SimulationSteps;
  GlobalVariables.GetSetting("SIM:Steps", SimulationSteps);
  for (int i = 0; i < SimulationSteps[0]; i++) {
    //Log.Output(MessageAllways, "."); //Lothar: Create a progress bar
    for (int j = 0; j < Neurons.size(); j++) {
      Neurons[j].Calculate(i);
    }
  }
  return ReturnSuccess;
}
