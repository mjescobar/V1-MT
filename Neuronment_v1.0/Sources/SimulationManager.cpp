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
  ToReturn = CreateV1NeuronVector();
  if (!ToReturn) {
    return false;
  }
  // Setting the V1 activation calculation method
  ToReturn = SetV1ActMethod();
  if (!ToReturn) {
    return false;
  }
  // Setting the V1 dactivation calculation method
  ToReturn = SetV1DacMethod();
  if (!ToReturn) {
    return false;
  }
  // MT Settings
  // Creating the MT_Neurons Vector
  ToReturn = CreateMTNeuronVector();
  if (!ToReturn) {
    return false;
  }
  // Setting the MT activation calculation method
  ToReturn = SetMTActMethod();
  if (!ToReturn) {
    return false;
  }
  // Setting the MT dactivation calculation method
  ToReturn = SetMTDacMethod();
  if (!ToReturn) {
    return false;
  }
  // V1V1 Settings
  // Setting V1V1 connection links
  ToReturn = SetV1V1ConnectionLinks();
  if (!ToReturn) {
    return false;
  }
  // MTMT Settings
  // Setting MT-MT connection links

  // V1MT Settings
  // Setting V1MT connection links
  ToReturn = SetV1MTConnectionLinks();
  if (!ToReturn) {
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
    Name = "V1" + NNumber(i);
    if (Simulation.GetSettingValid(Name)) {
      Data = Simulation.GetSetting_double(Name);
      if (Data) {
        V1_Neuron ToAdd = V1_Neuron(Name, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5], Data[6], Data[7]);
        vector<V1_Neuron>::iterator it = lower_bound(V1_Neurons.begin(), V1_Neurons.end(), ToAdd, CompareV1_NeuronForSorting);
        V1_Neurons.insert(it, ToAdd);
        Log.OutputNNL(Message_Allways, ".");
      }
    }
  }
  Log.Output(Message_Allways, "");
  Log.Output(Message_Allways, "Total V1_Neuron inserted: " + IIntToString(V1_Neurons.size()));
  if (V1_Neurons.size() == 0) {
    Log.Message("SD-015");
    return false;
  }
  return true;
}

bool SimulationManager::SetV1ActMethod()
{
  string V1ActivationMethod = Simulation.GetSingleSetting_string(V1_ACTIVATION_METHOD, DEFAULT_V1_ACTIVATION_METHOD);
  Log.Output(Message_Allways, "V1 activation calculation method: " + V1ActivationMethod);
  if (V1ActivationMethod == "V1_A001") {
    for (int i = 0; i < V1_Neurons.size(); i++) {
      V1_Neurons[i].SetActivationMethod("V1_A001");
    }
  } else {
    Log.Message("SD-036: " + V1ActivationMethod + " for " + V1_ACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::SetV1DacMethod()
{
  string V1DActivationMethod = Simulation.GetSingleSetting_string(V1_DACTIVATION_METHOD, DEFAULT_V1_DACTIVATION_METHOD);
  Log.Output(Message_Allways, "V1 dactivation calculation method: " + V1DActivationMethod);
  if (V1DActivationMethod == "V1_D001") {
    void* Dummy;
    Dummy = Simulation.GetSettingContentSafe("V1_D001_excitatory_factor");
    Dummy = Simulation.GetSettingContentSafe("V1_D001_conductance_leak");
    Dummy = Simulation.GetSettingContentSafe("V1_D001_inhibition_factor");
    for (int i = 0; i < V1_Neurons.size(); i++) {
      V1_Neurons[i].SetDActivationMethod("V1_D001");
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
    Name = "MT" + NNumber(i);
    if (Simulation.GetSettingValid(Name)) {
      Data = Simulation.GetSetting_double(Name);
      if (Data) {
        MT_Neuron ToAdd = MT_Neuron(Name, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]);
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
  string MTActivationMethod = Simulation.GetSingleSetting_string(MT_ACTIVATION_METHOD, DEFAULT_MT_ACTIVATION_METHOD);
  Log.Output(Message_Allways, "MT activation calculation method: " + MTActivationMethod);
  if (MTActivationMethod == "MT_A001") {
    for (int i = 0; i < MT_Neurons.size(); i++) {
      MT_Neurons[i].SetActivationMethod("MT_A001");
    }
  } else {
    Log.Message("SD-036: " + MTActivationMethod + " for " + MT_ACTIVATION_METHOD);
    return false;
  }
  return true;
}

bool SimulationManager::SetMTDacMethod()
{
  string MTDActivationMethod = Simulation.GetSingleSetting_string(MT_DACTIVATION_METHOD, DEFAULT_MT_DACTIVATION_METHOD);
  Log.Output(Message_Allways, "MT dactivation calculation method: " + MTDActivationMethod);
  if (MTDActivationMethod == "MT_D001") {
    for (int i = 0; i < MT_Neurons.size(); i++) {
      MT_Neurons[i].SetActivationMethod("MT_D001");
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
  string V1V1BaseWeightSource = Simulation.GetSingleSetting_string(V1V1_BASE_WEIGHT_SOURCE, DEFAULT_V1V1_BASE_WEIGHT_SOURCE);
  string V1V1WeightAdaptation = Simulation.GetSingleSetting_string(V1V1_WEIGHT_ADAPTATION, DEFAULT_V1V1_WEIGHT_ADAPTATION);
  Log.Output(Message_Allways, "V1V1 base weight source: " + V1V1BaseWeightSource);
  Log.Output(Message_Allways, "V1V1 weight adaptation method: " + V1V1WeightAdaptation);
  if (V1V1WeightAdaptation == "V1V1_A001") {
    for (int i = 0; i < V1_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        double Distance = V1_Neurons[i].DistanceToNeuron(V1_Neurons[j]);
        double SpatialFrequency = V1_Neurons[i].GetSpa();
        double RFSize = 1.5 * 0.5622 / SpatialFrequency;
        Log.Message("WN-006: RFSize");
        double Sigma = 2.2 * RFSize / 3.0;
        Log.Message("WN-006: Sigma");
        double AdaptedWeight = exp(-(Distance) / (2 * Sigma * Sigma));
        Log.Message("WN-006: AdaptedWeight");
        V1_Neurons[i].AddV1Link(&(V1_Neurons[j]), GetV1V1BaseWeight(V1V1BaseWeightSource, i, j) * AdaptedWeight);
        Log.Message("WN-006: LinkWeight calculation");
      }
    }
    for (int i = 0; i < V1_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        V1_Neurons[i].SetLinkingWeight(V1_Neurons[j].GetName(), V1_Neurons[i].GetLinkingWeight(V1_Neurons[j].GetName()) / V1_Neurons[i].ConnectionCount(Neuron_V1));
        Log.Message("WN-006: V1V1 LinkWeight count correction");
      }
    }
    return true;
  }
  Log.Message("SD-036: " + V1V1WeightAdaptation + " for " + V1V1_WEIGHT_ADAPTATION);
  return false;
}

double SimulationManager::GetV1V1BaseWeight(string MethodP, int DestinationP, int OriginP)
{
  if (MethodP == "default_weight") {
    return Simulation.GetSingleSetting_double(V1V1_DEFAULT_WEIGHT, DEFAULT_V1V1_DEFAULT_WEIGHT);
  }
  if (MethodP == "from_setsim_values_or_default") {
    return Simulation.GetSingleSetting_double(V1_Neurons[DestinationP].GetName() + ":" + V1_Neurons[OriginP].GetName(), Simulation.GetSingleSetting_double(V1V1_DEFAULT_WEIGHT, DEFAULT_V1V1_DEFAULT_WEIGHT));
  }
  if (MethodP == "from_setsim_values_or_error") {
    return Simulation.GetSingleSetting_double(V1_Neurons[DestinationP].GetName() + V1_Neurons[OriginP].GetName(), Simulation.GetSingleSetting_double(V1V1_DEFAULT_WEIGHT, DEFAULT_V1V1_DEFAULT_WEIGHT));
  }
  Log.Message("SD-036: " + MethodP + " for " + V1V1_DEFAULT_WEIGHT);
}

bool SimulationManager::SetV1MTConnectionLinks()
{
  Log.Output(Message_Allways, "Creating V1MT links");
  string V1MTConnectionMethod = Simulation.GetSingleSetting_string(V1MT_CONNECTION_METHOD, DEFAULT_V1MT_CONNECTION_METHOD);
  Log.Output(Message_Allways, "V1MT linking method: " + V1MTConnectionMethod);
  if (V1MTConnectionMethod == "V1MT_L001") {
    void* Dummy;
    Dummy = Simulation.GetSettingContentSafe("V1MT_L001_sigma");
    Dummy = Simulation.GetSettingContentSafe("V1MT_L001_amplification");
    Dummy = Simulation.GetSettingContentSafe("V1MT_L001_modulation");
    Dummy = Simulation.GetSettingContentSafe("V1MT_L001_aperture");
    for (int i = 0; i < MT_Neurons.size(); i++) {
      for (int j = 0; j < V1_Neurons.size(); j++) {
        MT_Neurons[i].AddV1Link(&(V1_Neurons[j]));
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
