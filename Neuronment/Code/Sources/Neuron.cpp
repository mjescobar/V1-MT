
#include <vector>
using namespace std;
#include "tools.h"
#include "extern.h"
#include "Neuron.h"
#include "LogManager.h"
#include "NeuronType.h"

Neuron::Neuron()
{
}

Neuron::Neuron(const Neuron& orig)
{
  //Lothar: is this necesary? Should this be asserted?
  Id = orig.Id;
  Group = orig.Group;
  Type = orig.Type;
  ParameterValues = orig.ParameterValues;
  LinkingPointers = orig.LinkingPointers;
  LinkingParameters = orig.LinkingParameters;
  LinkingParametersLabels = orig.LinkingParametersLabels;
  Activation_double = orig.Activation_double;
}

Neuron::~Neuron()
{
}

Neuron::Neuron(NeuronType *TypeP, string GroupP, int IdP, vector<string> BaseActivationP, vector<string> ParameterValuesP)
{
  Id = IdP;
  Group = GroupP;
  ParameterValues = ParameterValuesP;
  Type = TypeP;
  int ActivationLevels;
  Type->GetActivationLevels(ActivationLevels); //Lothar: what if the activation levels need to be stair declared??
  if (BaseActivationP.size() != 0 && BaseActivationP.size() != ActivationLevels) {
    Log.CodedMessage("DV-035");
  }
  string DataType;
  Type->GetDataType(DataType);
  if (DataType == "double") {
    for (int i = 0; i < ActivationLevels; i++) {
      Activation_double.push_back(vector<double>());
      if (BaseActivationP.size() != 0) {
        Activation_double[i].push_back(ToDouble(BaseActivationP[i]));
      }
    }
  }
  //Lothar: check for other data types
}

ReturnType Neuron::AddLink(Neuron *NeuronP, vector<string> ParametersP)
{
  LinkingPointers.push_back(NeuronP);
  if (ParametersP.size() % 2 != 0) {
    //Lothar: parameter requiere nombre y valor;
    return ReturnFail;
  }
  for (int i = 0; i < ParametersP.size(); i += 2) {
    vector<string> Empty;
    LinkingParametersLabels.push_back(Empty);
    LinkingParametersLabels.back().push_back(ParametersP[i]);
    LinkingParameters.push_back(Empty);
    LinkingParameters.back().push_back(ParametersP[i + 1]);
  }
  return ReturnSuccess;
}

ReturnType Neuron::LoadActivation(vector<vector<double> > ExternalActivationP)
{
  if (Type->IsDataType("double") == ReturnFail) {
    return ReturnFail;
  }
  if (Type->IsActivationLevels(ToString((int) ExternalActivationP.size())) == ReturnFail) {
    return ReturnFail;
  }
  Activation_double = ExternalActivationP;
  return ReturnSuccess;
}

ReturnType Neuron::LoadActivation(vector<double> ExternalActivationP, int LevelP)
{
  if (Type->IsDataType("double") == ReturnFail) {
    return ReturnFail;
  }
  int TypeLevels;
  Type->GetActivationLevels(TypeLevels);
  if (TypeLevels <= LevelP) {
    return ReturnFail;
  }
  Activation_double[LevelP] = ExternalActivationP;
  return ReturnSuccess;
}

ReturnType Neuron::Calculate(int StepP)
{
  int ActivationLevels;
  Type->GetActivationLevels(ActivationLevels);
  for (int i = 0; i < ActivationLevels; i++) {
    if (Type->IsDataType("double") == ReturnSuccess) {
      if (Activation_double[i].size() <= StepP) {
        void* Function;
        Type->GetActivationFunction(i, Function);
        ((ReturnType(*)(Simulator*, Neuron*, int, int))Function)(SimulatorDepository.CurrentSimulator(), this, i, StepP);
      }
    }
    //Lothar: check for other datatypes
  }
  return ReturnSuccess;
}

ReturnType Neuron::Calculate(int StepP, int LevelP)
{
  int ActivationLevels;
  Type->GetActivationLevels(ActivationLevels);
  if (Type->IsDataType("double") == ReturnSuccess) {
    if (Activation_double[LevelP].size() <= StepP) {
      void* Function;
      Type->GetActivationFunction(LevelP, Function);
      ((ReturnType(*)(Simulator*, Neuron*, int, int))Function)(SimulatorDepository.CurrentSimulator(), this, LevelP, StepP);
    }
  }
  //Lothar: check for other datatypes
  return ReturnSuccess;
}

ReturnType Neuron::GetActivation(int LevelP, int StepP, double &ActivationP)
{
  if (LevelP < Activation_double.size()) {
    if (StepP >= Activation_double[LevelP].size()) {
      for (int i = Activation_double[LevelP].size(); i < StepP + 1; i++) {
        Calculate(i, LevelP);
      }
    }
  } else {
    return Return(ReturnFail,"Access out of range");
  }
  ActivationP = Activation_double[LevelP][StepP];
  return ReturnSuccess;
}

ReturnType Neuron::GetActivation(vector<vector <double> > &ActivationP)
{
  //Lothar: check for correct data type
  ActivationP = Activation_double;
  return ReturnSuccess;
}

ReturnType Neuron::ActivationPushBack(int LevelP, double ValueP)
{
  //Lothar: check neuron type
  if (LevelP >= Activation_double.size()) {
    return Return(ReturnFail,"Access out of range");
  }
  Activation_double[LevelP].push_back(ValueP);
  return ReturnSuccess;
}

ReturnType Neuron::GetTypeParameter(string NameP, string &ValueP)
{
  int ParameterId = -1;
  vector<string> Names;
  Type->GetParametersName(Names);
  for (int i = 0; i < Names.size(); i++) {
    if (Names[i] == NameP) {
      ParameterId = i;
      i = Names.size();
    }
  }
  if (ParameterId < 0) {
    //return Return(ReturnFail,"Parameter not found");
    return ReturnFail;
  }
  ValueP = ParameterValues[ParameterId];
  return ReturnSuccess;
}

ReturnType Neuron::GetTypeParameter(string NameP, double &ValueP)
{
  int ParameterId = -1;
  vector<string> Names;
  Type->GetParametersName(Names);
  for (int i = 0; i < Names.size(); i++) {
    if (Names[i] == NameP) {
      ParameterId = i;
      i = Names.size();
    }
  }
  if (ParameterId < 0) {
    //return Return(ReturnFail,"Parameter not found");
    return ReturnFail;
  }
  ValueP = ToDouble(ParameterValues[ParameterId]);
  return ReturnSuccess;
}

ReturnType Neuron::GetLinkParameter(int LinkP, string NameP, double &ValueP)
{
  int index = -1;
  for (int i = 0; i < LinkingParametersLabels[LinkP].size(); i++) {
    if (LinkingParametersLabels[LinkP][i] == NameP) {
      index = i;
      i = LinkingParametersLabels[LinkP].size();
    }
  }
  if (index == -1) {
    return Return(ReturnFail,"Linking parameter label not found");
  }
  ValueP = ToDouble(LinkingParameters[LinkP][index]);
  return ReturnSuccess;
}

ReturnType Neuron::GetLinksCount(int &CountP)
{
  CountP = LinkingPointers.size();
  return ReturnSuccess;
}

ReturnType Neuron::GetLinksNeuron(int IndexP, Neuron* &NeuronP)
{
  if (LinkingPointers.size() > IndexP) {
    NeuronP = LinkingPointers[IndexP];
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType Neuron::GetActivationSize(int LevelP, int &SizeP)
{
  int Size = -1;
  if (Type->IsDataType("double") == ReturnSuccess) {
    if (LevelP < Activation_double.size()) {
      Size = Activation_double[LevelP].size();
    } else {
      return Return(ReturnFail,"Incorrect activation level");
    }
  }
  if (Size == -1) {
    return Return(ReturnFail,"Neuron type DataType not found");
  }
  SizeP = Size;
  return ReturnSuccess;
}

ReturnType Neuron::IsId(string IdP)
{
  if (ToInt(IdP) == Id) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType Neuron::IsGroup(string GroupP)
{
  if (GroupP == Group) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType Neuron::IsType(string TypeP)
{
  if (Type->IsName(TypeP) == ReturnSuccess) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType Neuron::PrintActivation(int FromP, int ToP)
{
  if (Type->IsDataType("double") == ReturnSuccess) {
    vector<vector<double> > Activation;
    GetActivation(Activation);
    int MaxActivationCounter = 0;
    for (int i = 0; i < Activation.size(); i++) {
      if (MaxActivationCounter < Activation[i].size()) {
        MaxActivationCounter = Activation[i].size();
      }
    }
    if (ToP != -1 && MaxActivationCounter > ToP) {
      MaxActivationCounter = ToP + 1;
    }
    int Starting = 0;
    if (FromP != -1 && FromP > Starting) {
      Starting = FromP;
    }
    //Lothar: error if MaxActivationCounter is 0
    Log.Output(MessageAllways, "Id   : " + ToString(Id));
    Log.Output(MessageAllways, "Group: " + Group);
    string TypeString;
    Type->GetName(TypeString);
    Log.Output(MessageAllways, "Type : " + TypeString);
    for (int i = -1; i < (int)Activation.size(); i++) {
      if (i == -1) {
        Log.Output(MessageAllways, "Step\t", false);
      } else {
        Log.Output(MessageAllways, ToString(i) + "\t", false);
      }
    }
    Log.Output(MessageAllways, "");
    for (int i = -1; i < (int)Activation.size(); i++) {
      Log.Output(MessageAllways, "--------", false);
    }
    Log.Output(MessageAllways, "");
    for (int i = Starting; i < MaxActivationCounter; i++) {
      Log.Output(MessageAllways, ToString(i) + "\t", false);
      for (int j = 0; j < Activation.size(); j++) {
        if (i < Activation[j].size()) {
          Log.Output(MessageAllways, ToString(Activation[j][i]) + "\t", false);
        } else {
          Log.Output(MessageAllways, "\t", false);
        }
      }
      Log.Output(MessageAllways, "");
    }
    Log.Output(MessageAllways, "");
    return ReturnSuccess;
  }
  return ReturnFail;
}

ReturnType Neuron::GetGroupName(string &GroupNameP)
{
  GroupNameP = Group;
  return ReturnSuccess;
}

ReturnType Neuron::GetTypeName(string &TypeNameP)
{
  return Type->GetName(TypeNameP);
}
