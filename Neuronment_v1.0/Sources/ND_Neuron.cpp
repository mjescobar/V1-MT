/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "Globals.h"
#include "ND_Neuron.h"

ND_Neuron::ND_Neuron()
{
  Type = Neuron_ND;
  XPos = 0;
  YPos = 0;
  ZPos = 0;
  Name = "";
  ActivationMethod = "";
  DActivationMethod = "";
  ExternalExcitationPointer = -1;
}

ND_Neuron::ND_Neuron(NeuronType FutureType)
{
  Type = FutureType;
}

ND_Neuron::ND_Neuron(const ND_Neuron& orig)
{
  Type = orig.Type;
  XPos = orig.XPos;
  YPos = orig.YPos;
  ZPos = orig.ZPos;
  Name = Name;
  ActivationMethod = orig.ActivationMethod;
  DActivationMethod = orig.DActivationMethod;
  ExternalExcitationPointer = orig.ExternalExcitationPointer;
}

ND_Neuron::~ND_Neuron()
{
}

string ND_Neuron::GetName()
{
  return Name;
}

bool ND_Neuron::SetActivationMethod(string MethodP)
{
  ActivationMethod = MethodP;
  return true;
}

bool ND_Neuron::SetDActivationMethod(string MethodP)
{
  DActivationMethod = MethodP;
  return true;
}

double ND_Neuron::GetXPos()
{
  return XPos;
}

double ND_Neuron::GetYPos()
{
  return YPos;
}

double ND_Neuron::GetZPos()
{
  return ZPos;
}

NeuronType ND_Neuron::GetType()
{
  return Type;
}

double ND_Neuron::GetExternalExcitation(int StepP)
{
  if (StepP >= 0) {
    if (ExternalExcitationTiming.size() > ExternalExcitationPointer + 1) {
      if (ExternalExcitationTiming[ExternalExcitationPointer + 1] <= StepP) {
        ExternalExcitationPointer++;
      }
    }
    return ExternalExcitationValue[ExternalExcitationPointer];
  } else {
    Log.Message("SD-021");
  }
}

double ND_Neuron::GetActivation(int TimeStepP)
{
  if (TimeStepP < 0 || TimeStepP >= Activation.size()) {
    Log.Message("SD-033");
  } else {
    return Activation[TimeStepP];
  }
}

int ND_Neuron::GetActivationSteps()
{
  return Activation.size();
}

double ND_Neuron::DistanceToNeuron(ND_Neuron DestinationP)
{
  return sqrt((XPos - DestinationP.GetXPos())*(XPos - DestinationP.GetXPos())+(YPos - DestinationP.GetYPos())*(YPos - DestinationP.GetYPos())+(ZPos - DestinationP.GetZPos())*(ZPos - DestinationP.GetZPos()));
}

int ND_Neuron::ConnectionCount(NeuronType TypeP)
{
  int Counter = 0;
  for (int i = 0; i < ActivationLinkingList.size(); i++) {
    if (ActivationLinkingList[i]->Type == TypeP) {
      Counter++;
    }
  }
  return Counter;
}

double ND_Neuron::GetLinkingWeight(string NeuronNameP)
{
  return ((double*) ActivationLinkingWeights.GetEntry(NeuronNameP)->GetContent())[0];
}

bool ND_Neuron::SetLinkingWeight(string NeuronNameP, double NewWeightP)
{
  ((double*) ActivationLinkingWeights.GetEntry(NeuronNameP)->GetContent())[0] = NewWeightP;
}

bool ND_Neuron::SimulateStep(int StepP)
{
  if (DActivation.size() == StepP && Activation.size() == StepP) {
    if (FirstCalculation == CALCULATE_DACTIVATION) {
      DActivation.push_back(CalculateDActivation());
      Activation.push_back(CalculateActivation());
      return true;
    }
    if (FirstCalculation == CALCULATE_ACTIVATION) {
      Activation.push_back(CalculateActivation());
      DActivation.push_back(CalculateDActivation());
      return true;
    }
    return false;
  } else {
    Log.Message("SD-030");
    return false;
  }
}

void ND_Neuron::SetFirstCalculation(string PFirstCalculation)
{
  FirstCalculation = PFirstCalculation;
}

double ND_Neuron::CalculateDActivation()
{
  return 0;
}

double ND_Neuron::CalculateActivation()
{
  return 0;
}