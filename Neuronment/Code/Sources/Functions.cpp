
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include "extern.h"
#include "tools.h"
#include "Functions.h"

// IO_ReadFromFile

ReturnType Function000000(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  //Lothar: check for double neuron type
  int CurrentSize = -1;
  ReturnCatch(NeuronP->GetActivationSize(LevelP, CurrentSize));
  if (CurrentSize > 1) {
    //Lothar: error, neurona ya leida desde archivo
    Log.Output(MessageAllways, ToString(CurrentSize));
    return ReturnFail;
  }
  string File;

  ReturnCatch(NeuronP->GetTypeParameter("InputFile", File));
  double Point;
  vector<double> FromFile;
  ifstream DataFile(File.c_str());
  if (!DataFile.is_open()) {
    //Lothar file not opened
    Log.Output(MessageAllways, File);
    return ReturnFail;
  }
  while (DataFile >> Point) {
    FromFile.push_back(Point);
  }
  DataFile.close();
  //Lothar: catch IO interactions
  ReturnCatch(NeuronP->LoadActivation(FromFile, LevelP));
  return ReturnSuccess;
}

// Operations_MultiplicationSum

ReturnType Function000001(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  int LinksCount;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double Activation;
    double Factor;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    ReturnCatch(SourceNeuron->GetActivation(LevelP, StepP, Activation));
    if (NeuronP->GetLinkParameter(i, "factor", Factor) == ReturnFail) {
      if (NeuronP->GetTypeParameter("DefaultFactor", Factor) == ReturnFail) {
        //Lothar: factor no encontrado, error
        return ReturnFail;
      }
    }
    NeuronP->ActivationPushBack(LevelP, Activation * Factor);
    //Log.Output(MessageAllways,ToString(Activation) + " " + ToString(Factor));
  }
  return ReturnSuccess;
}

//MT_A001

ReturnType Function000002(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  return ReturnSuccess;
  /*
  double TemporalActivation = 0;
  vector<Neuron<double>*> Links;
  vector<string> ListNameVector;
  SimulatorP->InternalVariables.GetSetting("MT_001:connection_list", ListNameVector);
  if (ListNameVector.size() != 1) {
    //Lothar error con el tamaño de la lista
    return ReturnFail;
  }
  NeuronP->GetLink(ListNameVector[0], Links);
  for (int i = 0; i < Links.size(); i++) {
    double SourceActivation = Links[i]->Activation[LevelP].size(); //((V1_Neuron*) ActivationLinkingList[i])->GetLastActivation();
    double SourceWeight = ToDouble((NeuronP->LinksParameters[i])[0]); //ActivationLinkingWeights.QuickGetEntry_double(((V1_Neuron*) ActivationLinkingList[i])->GetName());
    TemporalActivation += SourceActivation * SourceWeight;
  }
  TemporalActivation = (TemporalActivation < 0) ? 0 : TemporalActivation;
  NeuronP->Activation[LevelP].push_back(TemporalActivation);
  return ReturnSuccess;
   * */
}
