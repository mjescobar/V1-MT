/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
//#include <cmath>
#include <fstream>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "Globals.h"
//#include "ND_Neuron.h"
//#include "LogManager.h"
//#include "MT_Neuron.h"

#include "StandardNeuron.h"

StandardNeuron::StandardNeuron()
{
  Type = "";
  Group = "";
  Name = "";
}

StandardNeuron::StandardNeuron(const StandardNeuron& orig)
{
  Type = orig.Type;
  Group = orig.Group;
  Attributes = orig.Attributes;
  AttributeLabels = orig.AttributeLabels;
  Activation = orig.Activation;
  ActivationCalculationOrder = orig.ActivationCalculationOrder;
  ActivationFunctions = orig.ActivationFunctions;
  ExternalExcitation = orig.ExternalExcitation;
  ExternalExcitationStepsCounter = orig.ExternalExcitationStepsCounter;
  Links = orig.Links;
  LinkingWeights = orig.LinkingWeights;
}

StandardNeuron::~StandardNeuron()
{
}

ReturnType StandardNeuron::SetType(string TypeP)
{
  CheckString(TypeP, "NonEmpty");
  if (Type == "") {
    Type = TypeP;
    return Return_Success;
  } else {
    if (Type != TypeP) {
      Type = TypeP;
      return Return_Success;
    } else {
      Type = TypeP;
      return Return_Success_with_warning;
    }
  }
}

ReturnType StandardNeuron::SetGroup(string GroupP)
{
  CheckString(GroupP, "NonEmpty");
  if (Group == "") {
    Group = GroupP;
    return Return_Success;
  } else {
    if (Group != GroupP) {
      Group = GroupP;
      return Return_Success;
    } else {
      Group = GroupP;
      return Return_Success_with_warning;
    }
  }
}

ReturnType StandardNeuron::SetName(string NameP)
{
  CheckString(NameP, "NonEmpty");
  if (Name == "") {
    Name = NameP;
    return Return_Success;
  } else {
    if (Name != NameP) {
      Name = NameP;
      return Return_Success;
    } else {
      Name = NameP;
      return Return_Success_with_warning;
    }
  }
}

ReturnType StandardNeuron::AddAttribute(string LabelP, double DefaultP)
{
  CheckString(LabelP, "NonEmpty");
  int AttributeFound = -1;
  for (int i = 0; i < AttributeLabels.size(); i++) {
    if (AttributeLabels[i] == LabelP) {
      AttributeFound = i;
    }
  }
  if (AttributeFound != -1) {
    Attributes[AttributeFound] = DefaultP;
    return Return_Success_with_warning;
  } else {
    Attributes.push_back(DefaultP);
    AttributeLabels.push_back(LabelP);
    return Return_Success;
  }
}

ReturnType StandardNeuron::SetAttribute(string LabelP, double ValueP)
{
  CheckString(LabelP, "NonEmpty");
  int AttributeFound = -1;
  for (int i = 0; i < AttributeLabels.size(); i++) {
    if (AttributeLabels[i] == LabelP) {
      AttributeFound = i;
    }
  }
  if (AttributeFound != -1) {
    Attributes.push_back(ValueP);
    AttributeLabels.push_back(LabelP);
    return Return_Success;
  } else {
    Log.Message("SD-002: " + LabelP);
    Attributes.push_back(ValueP);
    AttributeLabels.push_back(LabelP);
    return Return_Success_with_warning;
  }
}

ReturnType StandardNeuron::SetActivationLevels(int LevelsP)
{
  CheckInt(LevelsP, "GreaterThanZero");
  if (Activation.size() != 0) {
    Log.Message("SD-005");
    Activation.clear();
  }
  for (int i = 0; i < LevelsP; i++) {
    vector<double> Temporal;
    Activation.push_back(Temporal);
  }
  if (Activation.size() != LevelsP) {
    Log.Message("DV-004");
    return Return_Fail;
  }
  return Return_Success;
}

ReturnType StandardNeuron::SetActivationFunction(int LevelP, double (*ActivationFunctionP)())
{
  CheckInt(LevelP, "NonNegative");
  if (LevelP >= Activation.size()) {
    Log.Message("DV-010");
    return Return_Fail;
  }
  if (LevelP >= ActivationFunctions.size()) {
    for (int i = ActivationFunctions.size(); i <= LevelP; i++) {
      ActivationFunctions.push_back(NULL);
    }
  }
  ActivationFunctions[LevelP] = ActivationFunctionP;
  return Return_Success;
}

ReturnType StandardNeuron::SetLink(StandardNeuron &LinkingNeuronP, vector<double> LinkingWeightsP)
{
  int Found = -1;
  for (int i = 0; i < Links.size(); i++) {
    if (Links[i] == &LinkingNeuronP) {
      Found = i;
      i = Links.size();
    }
  }
  if (Found < 0) {
    Links.push_back(&LinkingNeuronP);
    LinkingWeights.push_back(LinkingWeightsP);
    return Return_Success;
  } else {
    LinkingWeights[Found] = LinkingWeightsP;
    return Return_Success_with_warning;
  }
}

ReturnType StandardNeuron::GetAttribute(string LabelP, double &ParameterP)
{
  CheckString(LabelP, "NonEmpty");
  int Found = -1;
  for (int i = 0; i < AttributeLabels.size(); i++) {
    if (AttributeLabels[i] == LabelP) {
      Found = i;
      i = AttributeLabels.size();
    }
  }
  if (Found < 0) {
    Log.Message("SD-006");
    return Return_Fail;
  } else {
    ParameterP = Attributes[Found];
    return Return_Success;
  }
}

ReturnType StandardNeuron::GetType(string &TypeP)
{
  TypeP = Type;
  return Return_Success;
}

ReturnType StandardNeuron::GetGroup(string &GroupP)
{
  GroupP = Group;
  return Return_Success;
}

ReturnType StandardNeuron::GetName(string &NameP)
{
  NameP = Name;
  return Return_Success;
}

ReturnType StandardNeuron::SetActivationCalculationOrder(vector<int> OrderP)
{
  if (Activation.size() != OrderP.size()) {
    Log.Message("DV-011");
    return Return_Fail;
  }
  for (int i = 0; i < Activation.size(); i++) {
    bool Found = false;
    for (int j = 0; j < OrderP.size(); j++) {
      if (OrderP[j] == i) {
        Found = true;
        j = OrderP.size();
      }
    }
    if (!Found) {
      Log.Message("DV-014");
      return Return_Fail;
    }
  }
  ActivationCalculationOrder = OrderP;
  return Return_Success;
}

ReturnType StandardNeuron::GetActivation(int LevelP, double &ActivationP, int StepsP)
{
  CheckInt(LevelP, "Range[]", 0, Activation.size());
  CheckInt(Activation.size() - StepsP - 1, "NonNegative");
  ActivationP = Activation[LevelP][Activation.size() - 1 - StepsP];
  return Return_Success;
}

ReturnType StandardNeuron::SetExternalExcitation(vector<vector<double> > ExternalExcitationP, vector<int> ExternalExcitationStepsCounterP)
{
  if (ExternalExcitationP.size() < 1 || ExternalExcitationP.size() != ExternalExcitationStepsCounterP.size()) {
    Log.Message("DV-016");
    return Return_Fail;
  }
  ExternalExcitation = ExternalExcitationP;
  ExternalExcitationStepsCounter = ExternalExcitationStepsCounterP;
  return Return_Success;
}

ReturnType StandardNeuron::CalculateExternalExcitation(int StepP, vector<double> &ExternalExcitationP)
{
  CheckInt(StepP, "NonNegative");
  if (ExternalExcitation.size() < 1) {
    Log.Message("SD-017");
    return Return_Fail;
  }
  int Accumulated = 0;
  for (int i = 0; i < ExternalExcitation.size(); i++) {
    Accumulated += ExternalExcitationStepsCounter[i];
    if (StepP < Accumulated) {
      ExternalExcitationP = ExternalExcitation[i];
      return Return_Success;
    }
  }
  Log.Message("DV-018");
  return Return_Fail;
}

ReturnType StandardNeuron::CalculateActivationStep(int IterationP)
{
  double CalculatedActivation;
  ReturnType Return = (((ReturnType(*)(StandardNeuron*, double*))(ActivationFunctions[ActivationCalculationOrder[IterationP]]))(this, &CalculatedActivation));
  if (Return == Return_Fail) {
    Log.Message("SD-007");
    return Return_Fail;
  }
  Activation[ActivationCalculationOrder[IterationP]].push_back(CalculatedActivation);
  if (Return == Return_Success_with_warning) {
    return Return_Success_with_warning;
  } else {
    return Return_Success;
  }
}
