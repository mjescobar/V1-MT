
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
#include "extern.h"
#include "tools.h"
#include "Functions.h"

// IO_ReadFromFile

ReturnType Function000000(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  //Lothar: Requires check for double neuron type
  int CurrentSize = -1;
  ReturnCatch(NeuronP->GetActivationSize(LevelP, CurrentSize));
  if (CurrentSize > 1) {
    Log.Output(MessageAllways, ToString(CurrentSize));
    return ReturnFail;
  }
  string File;
  ReturnCatch(NeuronP->GetTypeParameter("InputFile", File));
  double Point;
  vector<double> FromFile;
  ifstream DataFile(File.c_str());
  if (!DataFile.is_open()) {
    Log.Output(MessageAllways, File);
    return ReturnFail;
  }
  while (DataFile >> Point) {
    FromFile.push_back(Point);
  }
  DataFile.close();
  //Lothar: catch IO interactions
  NeuronP->LoadActivation(FromFile, LevelP);
  return ReturnSuccess;
}

// Operations_MultiplicationSum

ReturnType Function000001(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  int LinksCount;
  double Accumulator = 0;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double Activation;
    double Factor;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    ReturnCatch(SourceNeuron->GetActivation(LevelP, StepP, Activation));
    if (NeuronP->GetLinkParameter(i, "factor", Factor) == ReturnFail) {
      ReturnCatch(NeuronP->GetTypeParameter("DefaultFactor", Factor));
    }
    Accumulator += Activation * Factor;
    //Log.Output(MessageAllways,ToString(Activation) + " " + ToString(Factor));
  }
  NeuronP->ActivationPushBack(LevelP, Accumulator);
  return ReturnSuccess;
}

// Perceptron

ReturnType Function000002(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  int LinksCount;
  double Accumulator = 0;
  double Threshold;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double Activation;
    double Factor;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    ReturnCatch(SourceNeuron->GetActivation(LevelP, StepP, Activation));
    if (NeuronP->GetLinkParameter(i, "factor", Factor) == ReturnFail) {
      ReturnCatch(NeuronP->GetTypeParameter("DefaultFactor", Factor));
    }
    Accumulator += Activation * Factor;
    //Log.Output(MessageAllways,ToString(Activation) + " " + ToString(Factor));
  }
  if (NeuronP->GetTypeParameter("Threshold", Threshold) == ReturnFail) {
    //Lothar: threshold no encontrado, error
    return ReturnFail;
  }
  if (Accumulator >= Threshold) {
    Accumulator = 1;
  } else {
    Accumulator = 0;
  }
  NeuronP->ActivationPushBack(LevelP, Accumulator);
  return ReturnSuccess;
}

// V1 Diffusion (von misses??)

ReturnType Function000003(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  double A;
  double B;
  double PreferredOrientation;
  //double PreferredSpatialFrequency;
  //double PreferredTemporalFrequency;
  double Magnitude;
  double Orientation;
  ReturnCatch(NeuronP->GetTypeParameter("A", A)); //Lothar: what if values comes from global?
  ReturnCatch(NeuronP->GetTypeParameter("B", B));
  ReturnCatch(NeuronP->GetTypeParameter("PreferredOrientation", PreferredOrientation));
  //ReturnCatch(NeuronP->GetTypeParameter("PreferredSpatialFrequency", PreferredSpatialFrequency));
  //ReturnCatch(NeuronP->GetTypeParameter("PreferredTemporalFrequency", PreferredTemporalFrequency));
  ReturnCatch(NeuronP->GetTypeParameter("Magnitude", Magnitude));
  ReturnCatch(NeuronP->GetTypeParameter("Orientation", Orientation));
  NeuronP->ActivationPushBack(LevelP, Magnitude * (exp(A * deg_cos(PreferredOrientation - Orientation)) + B * exp(A * deg_cos(PreferredOrientation - Orientation + 180))) / exp(A));
  return ReturnSuccess;
}

// Neuroscience_V1Neuron_act

ReturnType Function000004(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  if (StepP < 1) {
    //Lothar: requires base activation
    return ReturnFail;
  }
  double Tmp1;
  double TemporalActivation = 0;
  ReturnCatch(NeuronP->GetActivation(LevelP, StepP - 1, Tmp1));
  TemporalActivation += Tmp1;
  ReturnCatch(NeuronP->GetActivation(LevelP + 1, StepP, Tmp1));
  vector<double> Tmp2;
  if(GlobalVariables.GetSetting("SIM:StepSize", Tmp2)==ReturnFail){
    return Return(ReturnFail,"StepSize no definido");
  }
  TemporalActivation += Tmp2[0] * Tmp1;
  string TypeName;
  ReturnCatch(NeuronP->GetTypeName(TypeName));
  string GroupName;
  ReturnCatch(NeuronP->GetGroupName(GroupName));
  double NonLinearityA;
  if (NeuronP->GetTypeParameter("NonLinearityA", NonLinearityA) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":NonLinearityA", NonLinearityA) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":NonLinearityA", NonLinearityA) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:NonLinearityA", NonLinearityA) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double NonLinearityB;
  if (NeuronP->GetTypeParameter("NonLinearityB", NonLinearityB) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":NonLinearityB", NonLinearityB) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":NonLinearityB", NonLinearityB) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:NonLinearityB", NonLinearityB) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double NonLinearityMax;
  if (NeuronP->GetTypeParameter("NonLinearityMax", NonLinearityMax) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":NonLinearityMax", NonLinearityMax) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":NonLinearityMax", NonLinearityMax) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:NonLinearityMax", NonLinearityMax) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  // NonLinearity Calculation
  TemporalActivation = (NonLinearityMax / (1 + exp(NonLinearityA * (NonLinearityB - TemporalActivation))) - NonLinearityMax / (1 + exp(NonLinearityA * (NonLinearityB - 0))))*(NonLinearityMax / (NonLinearityMax - NonLinearityMax / (1 + exp(NonLinearityA * (NonLinearityB - 0)))));
  TemporalActivation = (TemporalActivation > 0) ? TemporalActivation : 0;
  NeuronP->ActivationPushBack(LevelP, TemporalActivation);
  return ReturnSuccess;
}

// Neuroscience_V1Neuron_dac

ReturnType Function000005(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  string TypeName;
  ReturnCatch(NeuronP->GetTypeName(TypeName));
  string GroupName;
  ReturnCatch(NeuronP->GetGroupName(GroupName));
  double ConductanceLeak;
  if (NeuronP->GetTypeParameter("ConductanceLeak", ConductanceLeak) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":ConductanceLeak", ConductanceLeak) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":ConductanceLeak", ConductanceLeak) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:ConductanceLeak", ConductanceLeak) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double ExitatoryFactor;
  if (NeuronP->GetTypeParameter("ExitatoryFactor", ExitatoryFactor) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":ExitatoryFactor", ExitatoryFactor) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":ExitatoryFactor", ExitatoryFactor) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:ExitatoryFactor", ExitatoryFactor) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double WeightFactor;
  if (NeuronP->GetTypeParameter("WeightFactor", WeightFactor) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":WeightFactor", WeightFactor) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":WeightFactor", WeightFactor) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:WeightFactor", WeightFactor) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double InhibitionFactor;
  if (NeuronP->GetTypeParameter("InhibitionFactor", InhibitionFactor) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":InhibitionFactor", InhibitionFactor) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":InhibitionFactor", InhibitionFactor) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:InhibitionFactor", InhibitionFactor) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  string ExternalExcitationType;
  if (NeuronP->GetTypeParameter("ExternalExcitationType", ExternalExcitationType) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":ExternalExcitationType", ExternalExcitationType) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":ExternalExcitationType", ExternalExcitationType) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:ExternalExcitationType", ExternalExcitationType) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double TDactivation;
  ReturnCatch(NeuronP->GetActivation(LevelP, StepP - 1, TDactivation));
  TDactivation *= ConductanceLeak;
  int LinksCount;
  double ExternalExcitation = 0;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double Activation;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    if (SourceNeuron->IsType(ExternalExcitationType) == ReturnSuccess) {
      ReturnCatch(SourceNeuron->GetActivation(LevelP - 1, StepP - 1, Activation));
      ExternalExcitation += Activation;
    }
  }
  TDactivation += ExternalExcitation*ExitatoryFactor;
  //Lothar: inhibition calculation goes here
  NeuronP->ActivationPushBack(LevelP, TDactivation);
  return ReturnSuccess;
}

// Neuroscience_MTNeuron_act

ReturnType Function000006(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  string TypeName;
  ReturnCatch(NeuronP->GetTypeName(TypeName));
  string GroupName;
  ReturnCatch(NeuronP->GetGroupName(GroupName));
  double V1Radius = 0.1; //Lothar: this should be calculated correctly by: (SimulatorP.GetV1Radius() < 0.1) ? 0.1 : SimulatorP.GetV1Radius();
  double Modulation;
  if (NeuronP->GetTypeParameter("Modulation", Modulation) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":Modulation", Modulation) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":Modulation", Modulation) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:Modulation", Modulation) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double Sigma;
  if (NeuronP->GetTypeParameter("Sigma", Sigma) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":Sigma", Sigma) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":Sigma", Sigma) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:Sigma", Sigma) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double Amplification;
  if (NeuronP->GetTypeParameter("Amplification", Amplification) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":Amplification", Amplification) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":Amplification", Amplification) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:Amplification", Amplification) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double Aperture;
  if (NeuronP->GetTypeParameter("Aperture", Aperture) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":Aperture", Aperture) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":Aperture", Aperture) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:Aperture", Aperture) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  double Ori;
  if (NeuronP->GetTypeParameter("Orientation", Ori) == ReturnFail) {
    return ReturnFail;
  }
  double TemporalActivation = 0;
  int LinksCount;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double SourceActivation;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    ReturnCatch(SourceNeuron->GetActivation(LevelP, StepP, SourceActivation));
    double SourceOrientation;
    if (SourceNeuron->GetTypeParameter("Orientation", SourceOrientation) == ReturnFail) {
      return ReturnFail;
    }
    double SourceX;
    if (SourceNeuron->GetTypeParameter("X", SourceX) == ReturnFail) {
      return ReturnFail;
    }
    double SourceY;
    if (SourceNeuron->GetTypeParameter("Y", SourceY) == ReturnFail) {
      return ReturnFail;
    }
    double SourceZ;
    if (SourceNeuron->GetTypeParameter("Z", SourceZ) == ReturnFail) {
      return ReturnFail;
    }
    double X;
    if (NeuronP->GetTypeParameter("X", X) == ReturnFail) {
      return ReturnFail;
    }
    double Y;
    if (NeuronP->GetTypeParameter("Y", Y) == ReturnFail) {
      return ReturnFail;
    }
    double Z;
    if (NeuronP->GetTypeParameter("Z", Z) == ReturnFail) {
      return ReturnFail;
    }
    double DeltaAngle = (abs(Ori - SourceOrientation) >= 180.0) ? 360.0 - abs(Ori - SourceOrientation) : abs(Ori - SourceOrientation);
    double Distance = sqrt(pow(X - SourceX, 2.0) + pow(Y - SourceY, 2.0) + pow(Z - SourceZ, 2.0));
    double Weight;
    if (DeltaAngle <= Aperture || DeltaAngle >= 180.0 - Aperture) {
      Weight = Amplification * exp(-(Distance) / (2.0 * pow(Sigma * V1Radius, 2.0))) * (pow(abs(deg_cos(DeltaAngle)), Modulation) * deg_cos(DeltaAngle));
    } else {
      Weight = 0;
    }
    TemporalActivation += SourceActivation*Weight;
  }
  TemporalActivation = (TemporalActivation < 0) ? 0 : TemporalActivation;
  NeuronP->ActivationPushBack(LevelP, TemporalActivation);
  return ReturnSuccess;
}

// Operations_Vector_Average

ReturnType Function000007(Simulator *SimulatorP, Neuron *NeuronP, int LevelP, int StepP)
{
  string TypeName;
  ReturnCatch(NeuronP->GetTypeName(TypeName));
  string GroupName;
  ReturnCatch(NeuronP->GetGroupName(GroupName));
  double XAccumulated = 0;
  double YAccumulated = 0;
  string Parameter;
  if (NeuronP->GetTypeParameter("Parameter", Parameter) == ReturnFail) {
    if (GlobalVariables.GetSetting("FUN:" + TypeName + ":" + GroupName + ":Parameter", Parameter) == ReturnFail) {
      if (GlobalVariables.GetSetting("FUN:" + TypeName + ":Parameter", Parameter) == ReturnFail) {
        if (GlobalVariables.GetSetting("FUN:Parameter", Parameter) == ReturnFail) {
          return ReturnFail;
        }
      }
    }
  }
  int LinksCount;
  NeuronP->GetLinksCount(LinksCount);
  for (int i = 0; i < LinksCount; i++) {
    double SourceActivation;
    Neuron* SourceNeuron;
    NeuronP->GetLinksNeuron(i, SourceNeuron);
    ReturnCatch(SourceNeuron->GetActivation(LevelP, StepP, SourceActivation));
    double SourceOrientation;
    if (SourceNeuron->GetTypeParameter("Orientation", SourceOrientation) == ReturnFail) {
      return ReturnFail;
    }
    XAccumulated += SourceActivation * deg_cos(SourceOrientation);
    YAccumulated += SourceActivation * deg_sin(SourceOrientation);
  }
  if (Parameter == "Angle") {
    NeuronP->ActivationPushBack(LevelP, atan2(YAccumulated, XAccumulated)*180 / PI);
  } else if (Parameter == "Magnitude") {
    NeuronP->ActivationPushBack(LevelP, sqrt(YAccumulated * YAccumulated + XAccumulated * XAccumulated));
  } else {
    //Lothar: error, parameter type not supported
    return ReturnFail;
  }
  return ReturnSuccess;
}

//Lothar: what if more than 2 deg derivation is required for calculation with the base_activation???
