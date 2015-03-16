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
#include "MT_Neuron.h"
#include "LogManager.h"

MT_Neuron::MT_Neuron()
{
  Type = Neuron_MT;
  ActivationLinkingWeights = HashTable(Data_double);
}

MT_Neuron::MT_Neuron(const MT_Neuron& orig) : ND_Neuron(Neuron_MT)
{
  if (orig.Type != Neuron_MT) {
    Log.Message("DV-017");
  }
  Type = orig.Type;
  Name = orig.Name;
  Ori = orig.Ori;
  XPos = orig.XPos;
  YPos = orig.YPos;
  ZPos = orig.ZPos;
  Activation = orig.Activation;
  DActivation = orig.DActivation;
  ActivationLinkingWeights = orig.ActivationLinkingWeights;
}

MT_Neuron::~MT_Neuron()
{
}

MT_Neuron::MT_Neuron(string NameP, double Xp, double Yp, double Zp, double OriP, double ActiP, double DactP) : ND_Neuron(Neuron_MT)
{
  Type = Neuron_MT;
  Name = NameP;
  Ori = OriP;
  XPos = Xp;
  YPos = Yp;
  ZPos = Zp;
  Activation.push_back(ActiP);
  DActivation.push_back(DactP);
  ActivationLinkingWeights = HashTable(Data_double);
}

bool MT_Neuron::AddV1Link(V1_Neuron* NeuronP)
{
  string V1MTConnectionMethod = Simulation.GetSingleSetting_string(V1MT_CONNECTION_METHOD, DEFAULT_V1MT_CONNECTION_METHOD);
  if (V1MTConnectionMethod == V1MT_L001) {
    double Modulation = Simulation.GetSingleSetting_double(V1MT_L001_MODULATION, DEFAULT_V1MT_L001_MODULATION);
    double Sigma = Simulation.GetSingleSetting_double(V1MT_L001_SIGMA, DEFAULT_V1MT_L001_SIGMA);
    double Amplification = Simulation.GetSingleSetting_double(V1MT_L001_AMPLIFICATION, DEFAULT_V1MT_L001_AMPLIFICATION);
    double Aperture = Simulation.GetSingleSetting_double(V1MT_L001_APERTURE, DEFAULT_V1MT_L001_APERTURE);
    double DeltaAngle = (abs(Ori - NeuronP->GetOri()) >= 180) ? 360 - abs(Ori - NeuronP->GetOri()) : abs(Ori - NeuronP->GetOri());
    double Distance = sqrt((XPos - NeuronP->GetXPos())*(XPos - NeuronP->GetXPos())+(YPos - NeuronP->GetYPos())*(YPos - NeuronP->GetYPos())+(ZPos - NeuronP->GetZPos())*(ZPos - NeuronP->GetZPos()));
    double Weight = Amplification * exp(-(Distance) / (2 * Sigma * Sigma)) * (pow(abs(deg_cos(DeltaAngle)), Modulation) * deg_cos(DeltaAngle));
    if (DeltaAngle <= Aperture || DeltaAngle >= 360 - Aperture) {
      ActivationLinkingList.push_back(NeuronP);
      ActivationLinkingWeights.QuickPutEntry_double(NeuronP->GetName(), Weight);
    }
    return true;
  }
  Log.Message("SD-036: "+V1MTConnectionMethod+" for "+V1MT_CONNECTION_METHOD);
  return false;
}

bool MT_Neuron::SimulateStep(int StepP)
{
  if (Activation.size() == StepP) {
    Activation.push_back(CalculateActivation());
  } else {
    Log.Message("SD-030");
    return false;
  }
  return true;
}

double MT_Neuron::CalculateActivation()
{
  double TemporalActivation = 0;
  string MTActivationMethod = Simulation.GetSingleSetting_string(MT_ACTIVATION_METHOD, DEFAULT_MT_ACTIVATION_METHOD);
  if (MTActivationMethod == MT_A001) {
    for (int i = 0; i < ActivationLinkingList.size(); i++) {
      if (ActivationLinkingList[i]->GetType() == Neuron_V1) {
        TemporalActivation += ((V1_Neuron*) ActivationLinkingList[i])->GetLastActivation(); // * ActivationLinkingWeights.GetEntry(ActivationLinkingList[i]->GetName());
      }
    }
  } else {
    Log.Message("SD-036: " + MTActivationMethod + " for " + MT_ACTIVATION_METHOD);
  }
  return TemporalActivation;
}

double MT_Neuron::GetOri()
{
  return Ori;
}

bool CompareMT_NeuronForSorting(MT_Neuron AP, MT_Neuron BP)
{
  // Nearest to the 0,0
  if (AP.GetXPos() * AP.GetXPos() + AP.GetYPos() * AP.GetYPos() + AP.GetZPos() * AP.GetZPos() < BP.GetXPos() * BP.GetXPos() + BP.GetYPos() * BP.GetYPos() + BP.GetZPos() * BP.GetZPos()) {
    return true;
  } else if (AP.GetXPos() * AP.GetXPos() + AP.GetYPos() * AP.GetYPos() + AP.GetZPos() * AP.GetZPos() > BP.GetXPos() * BP.GetXPos() + BP.GetYPos() * BP.GetYPos() + BP.GetZPos() * BP.GetZPos()) {
    return false;
  } else {
    // Nearest to the 0,0 first by X, then by Y, then by Z
    if (AP.GetXPos() < BP.GetXPos()) {
      return true;
    } else if (AP.GetXPos() > BP.GetXPos()) {
      return false;
    } else {
      if (AP.GetYPos() < BP.GetYPos()) {
        return true;
      } else if (AP.GetYPos() > BP.GetYPos()) {
        return false;
      } else {
        if (AP.GetZPos() < BP.GetZPos()) {
          return true;
        } else if (AP.GetZPos() > BP.GetZPos()) {
          return false;
        } else {
          // Smallest orientation
          if (AP.GetOri() < BP.GetOri()) {
            return true;
          } else if (AP.GetOri() > BP.GetOri()) {
            return false;
          } else {
            // Name comparison
            if (AP.GetName() < BP.GetName()) {
              return true;
            } else if (AP.GetName() > BP.GetName()) {
              return false;
            } else {
              Log.Message("SD-031");
              return false;
            }
          }
        }
      }
    }
  }
}
