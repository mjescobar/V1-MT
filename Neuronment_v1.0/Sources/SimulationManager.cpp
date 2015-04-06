/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
using namespace std;
#include "enum.h"
#include "define.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "Tools.h"
#include "Globals.h"
#include "SettingsManager.h"
#include "ND_Neuron.h"
#include "V1_Neuron.h"
#include "MT_Neuron.h"
#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
  Initialized = false;
  V1Radius = 0;
}

SimulationManager::SimulationManager(const SimulationManager& orig)
{
}

SimulationManager::~SimulationManager()
{
}

bool SimulationManager::InitializeNeurons()
{
  bool ToReturn = false;
  // V1 Settings
  // Creating the V1_Neurons Vector
  if (!CreateV1NeuronVector()) {
    return false;
  }
  // Setting the V1 activation calculation method
  if (!SetV1ActMethod()) {
    return false;
  }
  // Setting the V1 dactivation calculation method
  if (!SetV1DacMethod()) {
    return false;
  }
  // MT Settings
  // Creating the MT_Neurons Vector
  if (!CreateMTNeuronVector()) {
    return false;
  }
  // Setting the MT activation calculation method
  if (!SetMTActMethod()) {
    return false;
  }
  // Setting the MT dactivation calculation method
  if (!SetMTDacMethod()) {
    return false;
  }
  // V1V1 Settings
  // Setting V1V1 connection links
  if (!SetV1V1ConnectionLinks()) {
    return false;
  }
  // MTMT Settings
  // Setting MT-MT connection links
  // None declared

  // V1MT Settings
  // Setting V1MT connection links
  if (!SetV1MTConnectionLinks()) {
    return false;
  }
  Initialized = true;
  return true;
}

bool SimulationManager::CreateV1NeuronVector()
{
  string Name;
  double* Data;
  Log.Output(Message_Allways, "Filling V1_Neurons vector");
  V1_Neurons.reserve(MAX_V1_NEURONS);
  for (int i = 0; i < MAX_V1_NEURONS; i++) {
    Name = V1_LABEL + NNumber(i);
    if (Variables.GetSettingValid("SIM:" + Name)) {
      Data = Variables.GetSetting_double("SIM:" + Name);
      if (Data) {
        V1_Neuron ToAdd = V1_Neuron(Name, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5], Data[6], Data[7]);
        ToAdd.SetFirstCalculation(*Variables.GetSetting_string(V1_FIRST_CALCULATION));
        vector<V1_Neuron>::iterator it = lower_bound(V1_Neurons.begin(), V1_Neurons.end(), ToAdd, CompareV1_NeuronForSorting);
        V1_Neurons.insert(it, ToAdd);
        V1Radius = (V1Radius < sqrt(pow(Data[0], 2) + pow(Data[1], 2) + pow(Data[2], 2))) ? sqrt(pow(Data[0], 2) + pow(Data[1], 2) + pow(Data[2], 2)) : V1Radius;
        Log.OutputNNL(Message_Allways, ".");
      }
    }
  }
  Log.Output(Message_Allways, "");
  Log.Output(Message_Allways, "Total V1_Neuron inserted: " + IIntToString(V1_Neurons.size()));
  Log.Output(Message_Allways, "V1 Radius:                " + IDoubleToString(V1Radius));
  if (V1_Neurons.size() == 0) {
    Log.Message("SD-015");
    return false;
  }
  return true;
}

bool SimulationManager::SetV1ActMethod()
{
  string V1ActivationMethod = Variables.GetSingleSetting_string(V1_ACTIVATION_METHOD, DEFAULT_V1_ACTIVATION_METHOD);
  Log.Output(Message_Allways, "V1 activation calculation method: " + V1ActivationMethod);
  if (V1ActivationMethod == V1_A001) {
    for (int i = 0; i < V1_Neurons.size(); i++) {
      V1_Neurons[i].SetActivationMethod(V1_A001);
    }
  } else {
    Log.Message("SD-036: " + V1ActivationMethod + " for " + V1_ACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::SetV1DacMethod()
{
  string V1DActivationMethod = Variables.GetSingleSetting_string(V1_DACTIVATION_METHOD, DEFAULT_V1_DACTIVATION_METHOD);
  Log.Output(Message_Allways, "V1 dactivation calculation method: " + V1DActivationMethod);
  if (V1DActivationMethod == V1_D001) {
    void* Dummy;
    Dummy = Variables.GetSettingContentSafe(V1_D001_EXCITATORY_FACTOR);
    Dummy = Variables.GetSettingContentSafe(V1_D001_CONDUCTANCE_LEAK);
    Dummy = Variables.GetSettingContentSafe(V1_D001_INHIBITION_FACTOR);
    for (int i = 0; i < V1_Neurons.size(); i++) {
      V1_Neurons[i].SetDActivationMethod(V1_D001);
    }
  } else {
    Log.Message("SD-036: " + V1DActivationMethod + " for " + V1_DACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::CreateMTNeuronVector()
{
  string Name;
  double* Data;
  Log.Output(Message_Allways, "Filling MT_Neurons vector");
  for (int i = 0; i < MAX_MT_NEURONS; i++) {
    Name = string("SIM:") + string(MT_LABEL) + NNumber(i);
    if (Variables.GetSettingValid(Name)) {
      Data = Variables.GetSetting_double(Name);
      if (Data) {
        MT_Neuron ToAdd = MT_Neuron(Name, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]);
        ToAdd.SetFirstCalculation(*Variables.GetSetting_string(MT_FIRST_CALCULATION));
        vector<MT_Neuron>::iterator it = lower_bound(MT_Neurons.begin(), MT_Neurons.end(), ToAdd, CompareMT_NeuronForSorting);
        MT_Neurons.insert(it, ToAdd);
        Log.OutputNNL(Message_Allways, ".");
      }
    }
  }
  Log.Output(Message_Allways, "");
  Log.Output(Message_Allways, "Total MT_Neuron inserted: " + IIntToString(MT_Neurons.size()));
  if (MT_Neurons.size() == 0) {
    Log.Message("SD-016");
    return false;
  }
  return true;
}

bool SimulationManager::SetMTActMethod()
{
  string MTActivationMethod = Variables.GetSingleSetting_string(MT_ACTIVATION_METHOD, DEFAULT_MT_ACTIVATION_METHOD);
  Log.Output(Message_Allways, "MT activation calculation method: " + MTActivationMethod);
  if (MTActivationMethod == MT_A001) {
    for (int i = 0; i < MT_Neurons.size(); i++) {
      MT_Neurons[i].SetActivationMethod(MT_A001);
    }
  } else {
    Log.Message("SD-036: " + MTActivationMethod + " for " + MT_ACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::SetMTDacMethod()
{
  string MTDActivationMethod = Variables.GetSingleSetting_string(MT_DACTIVATION_METHOD, DEFAULT_MT_DACTIVATION_METHOD);
  Log.Output(Message_Allways, "MT dactivation calculation method: " + MTDActivationMethod);
  if (MTDActivationMethod == MT_D001) {
    for (int i = 0; i < MT_Neurons.size(); i++) {
      MT_Neurons[i].SetActivationMethod(MT_D001);
    }
  } else {
    Log.Message("SD-036: " + MTDActivationMethod + " for " + MT_DACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::SetV1V1ConnectionLinks()
{
  Log.Output(Message_Allways, "Creating V1V1 links");
  string V1V1ConnectionMethod = Variables.GetSingleSetting_string(V1V1_CONNECTION_METHOD, DEFAULT_V1V1_CONNECTION_METHOD);
  Log.Output(Message_Allways, "V1V1 connection method: " + V1V1ConnectionMethod);
  if (V1V1ConnectionMethod == V1V1_L001) {
    string V1V1BaseWeightSource = Variables.GetSingleSetting_string(V1V1_L001_BASE_WEIGHT_SOURCE, DEFAULT_V1V1_L001_BASE_WEIGHT_SOURCE);
    Log.Output(Message_Allways, "V1V1_L001 Base Weight Source: " + V1V1BaseWeightSource);
    for (int i = 0; i < V1_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        V1_Neurons[i].AddV1Link(&(V1_Neurons[j]), *this);
      }
    }
    for (int i = 0; i < V1_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        V1_Neurons[i].SetLinkingWeight(V1_Neurons[j].GetName(), V1_Neurons[i].GetLinkingWeight(V1_Neurons[j].GetName()) / (double) V1_Neurons[i].ConnectionCount(Neuron_V1));
        Log.Message("WN-006: V1V1 LinkWeight count correction");
      }
    }
    return true;
  }
  Log.Message("SD-036: " + V1V1ConnectionMethod + " for " + V1V1_CONNECTION_METHOD);
  return false;
}

bool SimulationManager::SetV1MTConnectionLinks()
{
  Log.Output(Message_Allways, "Creating V1MT links");
  string V1MTConnectionMethod = Variables.GetSingleSetting_string(V1MT_CONNECTION_METHOD, DEFAULT_V1MT_CONNECTION_METHOD);
  Log.Output(Message_Allways, "V1MT linking method: " + V1MTConnectionMethod);
  if (V1MTConnectionMethod == "V1MT_L001") {
    void* Dummy;
    Dummy = Variables.GetSettingContentSafe(V1MT_L001_SIGMA);
    Dummy = Variables.GetSettingContentSafe(V1MT_L001_AMPLIFICATION);
    Dummy = Variables.GetSettingContentSafe(V1MT_L001_MODULATION);
    Dummy = Variables.GetSettingContentSafe(V1MT_L001_APERTURE);
    for (int i = 0; i < MT_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        MT_Neurons[i].AddV1Link(&(V1_Neurons[j]), *this);
      }
    }
  } else {
    Log.Message("SD-036: " + V1MTConnectionMethod + " for " + V1MT_CONNECTION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::AddV1Diffusion()
{
  for (int i = 0; i < V1_Neurons.size(); i++) {
    V1_Neurons[i].SetExternalExcitation();
  }
  return true;
}

bool SimulationManager::Simulate(int StepsP)
{
  if (StepsP < 1) {
    Log.Message("SD-028");
    return false;
  }
  for (int i = 1; i < StepsP; i++) {
    for (int j = 0; j < V1_Neurons.size(); j++) {
      V1_Neurons[j].SimulateStep(i);
    }
    for (int j = 0; j < MT_Neurons.size(); j++) {
      MT_Neurons[j].SimulateStep(i);
    }
    Log.OutputNNL(Message_Allways, ".");
  }
  Log.Output(Message_Allways, "");
  return true;
}

bool SimulationManager::PrintV1Activation(OrientationType OTypeP)
{
  if (Initialized) {
    if (OTypeP == Orientation_Vertical) {
      Log.OutputNNL(Message_Allways, "V1_Neuron Name       :\t");
      for (int i = 0; i < V1_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, V1_Neurons[i].GetName());
        if (i == V1_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      Log.OutputNNL(Message_Allways, "Spatial Frequency    :\t");
      for (int i = 0; i < V1_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, IDoubleToString(V1_Neurons[i].GetSpa()));
        if (i == V1_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      Log.OutputNNL(Message_Allways, "Temporal Frequency   :\t");
      for (int i = 0; i < V1_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, IDoubleToString(V1_Neurons[i].GetTem()));
        if (i == V1_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      Log.OutputNNL(Message_Allways, "Pref. Orientation:\t");
      for (int i = 0; i < V1_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, IDoubleToString(V1_Neurons[i].GetOri()));
        if (i == V1_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      for (int j = 0; j < V1_Neurons[0].GetActivationSteps(); j++) {
        Log.OutputNNL(Message_Allways, IIntToString(j) + "\t");
        for (int i = 0; i < V1_Neurons.size(); i++) {
          Log.OutputNNL(Message_Allways, IDoubleToString(V1_Neurons[i].GetActivation(j)));
          if (i == V1_Neurons.size() - 1) {
            Log.OutputNNL(Message_Allways, "\n");
          } else {
            Log.OutputNNL(Message_Allways, "\t");
          }
        }
      }
      return true;
    }
    if (OTypeP == Orientation_Horizontal) {
      Log.OutputNNL(Message_Allways, "Name\tSpatial Freq.\tTemporal Freq.\tPref. Orientation\t");
      for (int i = 0; i < V1_Neurons[0].GetActivationSteps(); i++) {
        Log.OutputNNL(Message_Allways, IIntToString(i));
        if (i == V1_Neurons[0].GetActivationSteps() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      for (int i = 0; i < V1_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, V1_Neurons[i].GetName() + "\t" + IDoubleToString(V1_Neurons[i].GetSpa()) + "\t" + IDoubleToString(V1_Neurons[i].GetTem()) + "\t" + IDoubleToString(V1_Neurons[i].GetOri()) + "\t");
        for (int j = 0; j < V1_Neurons[i].GetActivationSteps(); j++) {
          Log.OutputNNL(Message_Allways, IDoubleToString(V1_Neurons[i].GetActivation(j)));
          if (j == V1_Neurons[i].GetActivationSteps() - 1) {
            Log.OutputNNL(Message_Allways, "\n");
          } else {
            Log.OutputNNL(Message_Allways, "\t");
          }
        }
      }
    }
  } else {
    Log.Message("SD-001");
    return false;
  }
}

bool SimulationManager::PrintV1Activation(OrientationType OTypeP, string DestinationP)
{
  Log.StartOutputRedirection001(DestinationP);
  PrintV1Activation(OTypeP);
  Log.StopOutputRedirection001();
  return true;
}

bool SimulationManager::PrintMTActivation(OrientationType OTypeP)
{
  if (Initialized) {
    if (OTypeP == Orientation_Vertical) {
      Log.OutputNNL(Message_Allways, "MT_Neuron Name       :\t");
      for (int i = 0; i < MT_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, MT_Neurons[i].GetName());
        if (i == MT_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      Log.OutputNNL(Message_Allways, "Preferred Orientation:\t");
      for (int i = 0; i < MT_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, IDoubleToString(MT_Neurons[i].GetOri()));
        if (i == MT_Neurons.size() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      for (int j = 0; j < MT_Neurons[0].GetActivationSteps(); j++) {
        Log.OutputNNL(Message_Allways, IIntToString(j) + "\t");
        for (int i = 0; i < MT_Neurons.size(); i++) {
          Log.OutputNNL(Message_Allways, IDoubleToString(MT_Neurons[i].GetActivation(j)));
          if (i == MT_Neurons.size() - 1) {
            Log.OutputNNL(Message_Allways, "\n");
          } else {
            Log.OutputNNL(Message_Allways, "\t");
          }
        }
      }
      return true;
    }
    if (OTypeP == Orientation_Horizontal) {
      Log.OutputNNL(Message_Allways, "Name\tPref. Orientation\t");
      for (int i = 0; i < MT_Neurons[0].GetActivationSteps(); i++) {
        Log.OutputNNL(Message_Allways, IIntToString(i));
        if (i == MT_Neurons[0].GetActivationSteps() - 1) {
          Log.OutputNNL(Message_Allways, "\n");
        } else {
          Log.OutputNNL(Message_Allways, "\t");
        }
      }
      for (int i = 0; i < MT_Neurons.size(); i++) {
        Log.OutputNNL(Message_Allways, MT_Neurons[i].GetName() + "\t" + IDoubleToString(MT_Neurons[i].GetOri()) + "\t");
        for (int j = 0; j < MT_Neurons[i].GetActivationSteps(); j++) {
          Log.OutputNNL(Message_Allways, IDoubleToString(MT_Neurons[i].GetActivation(j)));
          if (j == MT_Neurons[i].GetActivationSteps() - 1) {
            Log.OutputNNL(Message_Allways, "\n");
          } else {
            Log.OutputNNL(Message_Allways, "\t");
          }
        }
      }
    }
  } else {
    Log.Message("SD-001");
    return false;
  }
}

bool SimulationManager::PrintMTActivation(OrientationType OTypeP, string DestinationP)
{
  Log.StartOutputRedirection001(DestinationP);
  PrintMTActivation(OTypeP);
  Log.StopOutputRedirection001();
  return true;
}

bool SimulationManager::PrintV1ExternalExcitation(int TimeStepP, string DestinationP)
{
  Log.StartOutputRedirection001(DestinationP);
  PrintV1ExternalExcitation(TimeStepP);
  Log.StopOutputRedirection001();
  return true;
}

bool SimulationManager::PrintV1ExternalExcitation(int TimeStepP)
{
  if (Initialized) {
    Log.Output(Message_Allways, "Name\tOrientation\tSpatial Freq.\tTemporal Freq.\tValue");
    for (int i = 0; i < V1_Neurons.size(); i++) {
      Log.OutputNNL(Message_Allways, V1_Neurons[i].GetName() + "\t" + IDoubleToString(V1_Neurons[i].GetOri()) + "\t" + IDoubleToString(V1_Neurons[i].GetSpa()) + "\t" + IDoubleToString(V1_Neurons[i].GetTem()) + "\t");
      Log.Output(Message_Allways, IDoubleToString(V1_Neurons[i].GetExternalExcitation(TimeStepP)));
    }
    return true;
  } else {
    Log.Message("SD-001");
    return false;
  }
}

double SimulationManager::GetV1Radius()
{
  return V1Radius;
}
