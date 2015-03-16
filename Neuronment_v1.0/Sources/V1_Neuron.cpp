/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "Globals.h"
#include "ND_Neuron.h"
#include "V1_Neuron.h"
#include "LogManager.h"

V1_Neuron::V1_Neuron()
{
  Type = Neuron_V1;
  ActivationLinkingWeights = HashTable(Data_double);
}

V1_Neuron::V1_Neuron(const V1_Neuron& orig) : ND_Neuron(Neuron_V1)
{
  if (orig.Type != Neuron_V1) {
    Log.Message("DV-017");
    ImplementationAssertion();
  }
  Type = orig.Type;
  Name = orig.Name;
  XPos = orig.XPos;
  YPos = orig.YPos;
  ZPos = orig.ZPos;
  Ori = orig.Ori;
  Spa = orig.Spa;
  Tem = orig.Tem;
  Activation = orig.Activation;
  DActivation = orig.DActivation;
  ActivationLinkingWeights = orig.ActivationLinkingWeights;
}

V1_Neuron::~V1_Neuron()
{
}

V1_Neuron::V1_Neuron(string NameP, double Xp, double Yp, double Zp, double OriP, double SpaP, double TemP, double ActiP, double DactP) : ND_Neuron(Neuron_V1)
{
  Type = Neuron_V1;
  Name = NameP;
  XPos = Xp;
  YPos = Yp;
  ZPos = Zp;
  Ori = OriP;
  Spa = SpaP;
  Tem = TemP;
  Activation.push_back(ActiP);
  DActivation.push_back(DactP);
  Type = Neuron_V1;
  ActivationLinkingWeights = HashTable(Data_double);
}

bool V1_Neuron::AddV1Link(V1_Neuron *NeuronP, double WeightP)
{
  ActivationLinkingList.push_back(NeuronP);
  ActivationLinkingWeights.QuickPutEntry_double(NeuronP->GetName(), WeightP);
  return true;
}

double V1_Neuron::GetOri()
{
  return Ori;
}

double V1_Neuron::GetSpa()
{
  return Spa;
}

double V1_Neuron::GetTem()
{
  return Tem;
}

bool V1_Neuron::SetExternalExcitation()
{
  string V1ExternalExcitatoryMethod = Simulation.GetSingleSetting_string(V1_EXTERNAL_EXCITATION_METHOD, DEFAULT_V1_EXTERNAL_EXCITATION_METHOD);
  if (V1ExternalExcitatoryMethod == "V1_F001") {
    double aP = Simulation.GetSingleSettingSafe_double("V1_F001_a", DEFAULT_V1_F001_A);
    double bP = Simulation.GetSingleSettingSafe_double("V1_F001_b", DEFAULT_V1_F001_B);
    double OrientationP = Simulation.GetSingleSettingSafe_double("V1_F001_orientation", DEFAULT_V1_F001_ORIENTATION);
    double SpatialFrequencyP = Simulation.GetSingleSettingSafe_double("V1_F001_spatial_frequency", DEFAULT_V1_F001_SPATIAL_FREQUENCY);
    double TemporalFrequencyP = Simulation.GetSingleSettingSafe_double("V1_F001_temporal_frequency", DEFAULT_V1_F001_TEMPORAL_FREQUENCY);
    double MagnitudeP = Simulation.GetSingleSettingSafe_double("V1_F001_magnitude", DEFAULT_V1_F001_MAGNITUDE);
    int PhaseP = Simulation.GetSingleSettingSafe_int("V1_F001_phase", DEFAULT_V1_F001_PHASE);
    double ToAdd = MagnitudeP * (exp(aP * deg_cos(OrientationP - Ori)) + bP * exp(aP * deg_cos(OrientationP - Ori + 180))) / exp(aP);
    if (ExternalExcitationTiming.size() == 0) {
      if (PhaseP != 0) {
        Log.Message("SD-027");
        return false;
      }
      if (Spa == SpatialFrequencyP && Tem == TemporalFrequencyP) {
        ExternalExcitationTiming.push_back(PhaseP);
        ExternalExcitationValue.push_back(ToAdd);
      } else {
        ExternalExcitationTiming.push_back(PhaseP);
        ExternalExcitationValue.push_back(0);
      }
      ExternalExcitationPointer = 0;
    } else {
      if (ExternalExcitationTiming.back() > PhaseP) {
        Log.Message("SD-025");
        return false;
      }
      if (ExternalExcitationTiming.back() == PhaseP) {
        if (Spa == SpatialFrequencyP && Tem == TemporalFrequencyP) {
          if (ExternalExcitationValue.back() < ToAdd) {
            ExternalExcitationValue.back() = ToAdd;
          }
        }
      } else {
        if (Spa == SpatialFrequencyP && Tem == TemporalFrequencyP) {
          ExternalExcitationTiming.push_back(PhaseP);
          ExternalExcitationValue.push_back(ToAdd);
        } else {
          ExternalExcitationTiming.push_back(PhaseP);
          ExternalExcitationValue.push_back(0);
        }
      }
    }
  } else {
    Log.Message("SD-036: " + V1ExternalExcitatoryMethod + " for " + V1_EXTERNAL_EXCITATION_METHOD);
    return false;
  }
  return true;
}

bool V1_Neuron::SimulateStep(int StepP)
{
  if (DActivation.size() == StepP && Activation.size() == StepP) {
    DActivation.push_back(CalculateDActivation());
    Activation.push_back(CalculateActivation());
  } else {
    Log.Message("SD-030");
    return false;
  }
  return true;
}

double V1_Neuron::CalculateDActivation()
{
  double TDActivation = 0;
  string V1DActivationMethod = Simulation.GetSingleSetting_string(V1_DACTIVATION_METHOD, DEFAULT_V1_DACTIVATION_METHOD);
  if (V1DActivationMethod == "V1_D001") {
    // Previous activation influence
    TDActivation += Simulation.GetSingleSettingSafe_double(V1_D001_CONDUCTANCE_LEAK, DEFAULT_V1_D001_CONDUCTANCE_LEAK) * Activation.back();
    // Excitation influence
    TDActivation += Simulation.GetSingleSettingSafe_double(V1_D001_EXCITATORY_FACTOR, DEFAULT_V1_D001_EXCITATORY_FACTOR) * GetExternalExcitation(Activation.size());
    // V1 Surround Inhibition
    double Surround = 0;
    for (int i = 0; i < ActivationLinkingList.size(); i++) {
      if (ActivationLinkingList[i]->GetType() == Neuron_V1) {
        Surround += ActivationLinkingWeights.QuickGetEntry_double(ActivationLinkingList[i]->GetName());
      }
    }
    TDActivation += Surround * Simulation.GetSingleSettingSafe_double(V1_D001_INHIBITION_FACTOR, DEFAULT_V1_D001_INHIBITION_FACTOR);
  } else {
    Log.Message("SD-036: " + V1DActivationMethod + " for " + V1_DACTIVATION_METHOD);
  }
  return TDActivation;
}

double V1_Neuron::CalculateActivation()
{
  double TemporalActivation = 0;
  string V1ActivationMethod = Simulation.GetSingleSetting_string(V1_ACTIVATION_METHOD, DEFAULT_V1_ACTIVATION_METHOD);
  if (V1ActivationMethod == "V1_A001") {
    TemporalActivation += Activation.back();
    TemporalActivation += Simulation.GetSingleSetting_double("simulator_time_step", DEFAULT_SIMULATOR_TIME_STEP) * DActivation.back();
  } else {
    Log.Message("SD-036: " + V1ActivationMethod + " for " + V1_ACTIVATION_METHOD);
  }
  return TemporalActivation;
}

double V1_Neuron::GetLastActivation()
{
  return Activation.back();
}

bool CompareV1_NeuronForSorting(V1_Neuron aP, V1_Neuron bP)
{
  // Nearest to the 0,0
  if (aP.GetXPos() * aP.GetXPos() + aP.GetYPos() * aP.GetYPos() + aP.GetZPos() * aP.GetZPos() < bP.GetXPos() * bP.GetXPos() + bP.GetYPos() * bP.GetYPos() + bP.GetZPos() * bP.GetZPos()) {
    return true;
  } else if (aP.GetXPos() * aP.GetXPos() + aP.GetYPos() * aP.GetYPos() + aP.GetZPos() * aP.GetZPos() > bP.GetXPos() * bP.GetXPos() + bP.GetYPos() * bP.GetYPos() + bP.GetZPos() * bP.GetZPos()) {
    return false;
  } else {
    // Nearest to the 0,0 first by X, then by Y, then by Z
    if (aP.GetXPos() < bP.GetXPos()) {
      return true;
    } else if (aP.GetXPos() > bP.GetXPos()) {
      return false;
    } else {
      if (aP.GetYPos() < bP.GetYPos()) {
        return true;
      } else if (aP.GetYPos() > bP.GetYPos()) {
        return false;
      } else {
        if (aP.GetZPos() < bP.GetZPos()) {
          return true;
        } else if (aP.GetZPos() > bP.GetZPos()) {
          return false;
        } else {
          // Smallest spatial frequency
          if (aP.GetSpa() < bP.GetSpa()) {
            return true;
          } else if (aP.GetSpa() > bP.GetSpa()) {
            return false;
          } else {
            // Smallest temporal frequency
            if (aP.GetTem() < bP.GetTem()) {
              return true;
            } else if (aP.GetTem() > bP.GetTem()) {
              return false;
            } else {
              // Smallest orientation
              if (aP.GetOri() < bP.GetOri()) {
                return true;
              } else if (aP.GetOri() > bP.GetOri()) {
                return false;
              } else {
                // Name comparison
                if (aP.GetName() < bP.GetName()) {
                  return true;
                } else if (aP.GetName() > bP.GetName()) {
                  return false;
                } else {
                  // 2 identical parametrical cells
                  return false;
                }
              }
            }
          }
        }
      }
    }
  }
}
