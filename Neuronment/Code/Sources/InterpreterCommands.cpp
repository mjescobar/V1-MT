
#include <vector>
using namespace std;
#include "extern.h"
#include "tools.h"
#include "NeuronType.h"
#include "Simulator.h"
#include "VariableManager.h"
#include "CommandLine.h"
#include "SimulatorManager.h"
#include "LogManager.h"
#include "InterpreterCommands.h"

ReturnType report_test(CommandLine &LocalManagerP)
{
  Log.Output(MessageInformation, "report_test");
  return ReturnSuccess;
}

ReturnType report_neuron_activation(CommandLine &LocalManagerP)
{
  string Id;
  string Type;
  string Group;
  LocalManagerP.GetFlag("id", Id);
  LocalManagerP.GetFlag("type", Type);
  LocalManagerP.GetFlag("group", Group);
  vector<Neuron*> NeuronsPointers;
  SimulatorDepository.CurrentSimulator()->GetNeurons(NeuronsPointers, Id, Type, Group);
  Log.Output(MessageAllways, "");
  string FromString;
  string ToString;
  int From = -1;
  int To = -1;
  if (LocalManagerP.GetFlag("from", FromString) == ReturnSuccess) {
    From = ToInt(FromString);
  }
  if (LocalManagerP.GetFlag("to", ToString) == ReturnSuccess) {
    To = ToInt(ToString);
  }
  for (int i = 0; i < NeuronsPointers.size(); i++) {
    NeuronsPointers[i]->PrintActivation(From, To);
  }
  return ReturnSuccess;

}

ReturnType rescue_nproc(CommandLine &LocalManagerP)
{
  bool HasRedirection;
  string Redirection;
  string NprocList;
  ReturnType ThisFileResult;
  RedirectionType RedirectionMode;

  LocalManagerP.HasRedirection(HasRedirection);
  if (HasRedirection) {
    LocalManagerP.GetRedirection(Redirection);
    LocalManagerP.GetRedirectionType(RedirectionMode);
  }
  if (LocalManagerP.GetFlag("nproc", NprocList) == ReturnSuccess) {
    if (NprocList.length() > 0) {
      vector<string> NprocFiles;
      Tokenize(NprocList, NprocFiles);
      for (int i = 0; i < NprocFiles.size(); i++) {
        Interpreter LocalInterpreter(NprocFiles[i]);
        LocalInterpreter.LoadFile();
        if (HasRedirection) {
          Log.InitiateRedirection(Redirection, RedirectionMode);
        } else {
          Log.IncreaseOutputLevel();
        }
        ThisFileResult = LocalInterpreter.Process();
        if (HasRedirection) {
          Log.TerminateRedirection();
          RedirectionMode = RedirectionAppend;
        } else {
          Log.DecreaseOutputLevel();
        }
        LocalInterpreter.CloseFile();
      }
    } else {
      return Return(ReturnFail, "UI-006", "IgnoreReturnValue"); //Lothar: The IgnoreReturnValue should be removed when UI-006 is correctly managed
    }
  } else {
    return Return(ReturnFail, "UI-006", "IgnoreReturnValue"); //Lothar: The IgnoreReturnValue should be removed when UI-006 is correctly managed
  }
  return ReturnSuccess;
}

ReturnType varman_set(CommandLine &LocalManagerP)
{
  string VariableName;
  string VariableType;
  string VariableValue;
  string VariableSimulator;
  LocalManagerP.GetFlag("name", VariableName);
  LocalManagerP.GetFlag("type", VariableType);
  LocalManagerP.GetFlag("value", VariableValue);
  if (LocalManagerP.GetFlag("simulator", VariableSimulator) == ReturnFail) {
    GlobalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
  } else {
    if (VariableSimulator == "current") {
      SimulatorDepository.CurrentSimulator()->InternalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
    } else {
      SimulatorDepository.GetSimulator(ToInt(VariableSimulator))->InternalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
    }
  }
  return ReturnSuccess;
}

ReturnType varman_get(CommandLine &LocalManagerP)
{
  string VariableName;
  string VariableValue;
  LocalManagerP.GetFlag("name", VariableName);
  GlobalVariables.GetSettingAsString(VariableName, VariableValue);
  Log.Output(MessageAllways, VariableValue);
  return ReturnSuccess;
}

ReturnType rescue_end_nproc(CommandLine &LocalManagerP)
{
  EarlyReturn = true;
  return ReturnSuccess;
}

ReturnType setsim_add_simulator(CommandLine &LocalManagerP)
{
  SimulatorDepository.AddSimulator();
  return ReturnSuccess;
}

ReturnType setsim_get_current_simulator(CommandLine &LocalManagerP)
{
  int CurrentSimulator;
  SimulatorDepository.GetSimulatorCurrent(CurrentSimulator);
  if (CurrentSimulator < 0) {
    Log.Output(MessageAllways, "There are no simulators started");
  } else {
    Log.Output(MessageAllways, "Current Simulator: " + ToString(CurrentSimulator));
  }
  return ReturnSuccess;
}

ReturnType setsim_get_simulators_list(CommandLine &LocalManagerP)
{
  vector<string> SimulatorList;
  SimulatorDepository.GetSimulatorList(SimulatorList);
  if (SimulatorList.size() > 0) {
    for (int i = 0; i < SimulatorList.size(); i++) {
      Log.Output(MessageAllways, SimulatorList[i]);
    }
  } else {
    Log.Output(MessageAllways, "There are no simulators to report");
  }
  return ReturnSuccess;
}

ReturnType setsim_set_current_simulator(CommandLine &LocalManagerP)
{
  int SimulatorId;
  string SimulatorIdString;
  if (LocalManagerP.GetFlag("simulator_id", SimulatorIdString) == ReturnFail) {
    return Return(ReturnFail, "IN-006: SimulatorId");
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Setting current simulator to Id " + ToString(SimulatorId));
  int SimulatorCount;
  SimulatorDepository.GetSimulatorCount(SimulatorCount);
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.CodedMessage("IN-024");
  }
  SimulatorDepository.SetSimulatorCurrent(SimulatorId);
  return ReturnSuccess;
}

ReturnType setsim_remove_simulator(CommandLine &LocalManagerP)
{
  //Lothar: check for correctly setting the new current pointer
  int SimulatorId;
  string SimulatorIdString;
  if (LocalManagerP.GetFlag("simulator_id", SimulatorIdString) == ReturnFail) {
    return Return(ReturnFail, "IN-006: SimulatorId");
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Removing simulator " + ToString(SimulatorId));
  int SimulatorCount;
  SimulatorDepository.GetSimulatorCount(SimulatorCount);
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.CodedMessage("IN-024");
  }
  SimulatorDepository.SetSimulatorCurrent(-1);
  SimulatorDepository.RemoveSimulator(SimulatorId);
  return ReturnSuccess;
}

ReturnType setsim_new_neuron_type(CommandLine &LocalManagerP)
{
  string Name;
  LocalManagerP.GetFlag("name", Name);
  int ActivationLevels;
  string ActivationLevelsString;
  LocalManagerP.GetFlag("activation_levels", ActivationLevelsString);
  ActivationLevels = ToInt(ActivationLevelsString);
  vector<string> ActivationFunctions;
  for (int i = 0; i < ActivationLevels; i++) {
    string Tmp;
    LocalManagerP.GetFlag("activation_function_" + ToString(i), Tmp);
    ActivationFunctions.push_back(Tmp);
  }
  string Parameters;
  vector<string> ParametersTokenized;
  LocalManagerP.GetFlag("parameters", Parameters);
  Tokenize(Parameters, ParametersTokenized);
  if (ParametersTokenized.size() % 2 != 0) {
    return Return(ReturnFail, "IN-025");
  }
  vector<string> ParametersName;
  vector<string> ParametersType;
  for (int i = 0; i < ParametersTokenized.size(); i = i + 2) {
    if (IsValidType(ParametersTokenized[i]) == ReturnFail) {
      return Return(ReturnFail, "IN-025");
    }
    ParametersName.push_back(ParametersTokenized[i + 1]);
    ParametersType.push_back(ParametersTokenized[i]);
  }
  string DataType;
  LocalManagerP.GetFlag("data_type", DataType);
    SimulatorDepository.AddNeuronType(Name, DataType, ActivationLevels, ActivationFunctions, ParametersName, ParametersType);
    string FastInput;
  if (LocalManagerP.GetFlag("fast_input", FastInput) != ReturnFail) {

    SimulatorDepository.SetNeuronTypeFastInput(Name, FastInput);
  }
  return ReturnSuccess;
}

ReturnType setsim_add_neuron(CommandLine &LocalManagerP)
{
  NeuronType *NewNeuronType;
    string NeuronTypeName;
    LocalManagerP.GetFlag("neuron_type", NeuronTypeName);
    SimulatorDepository.GetNeuronType(NeuronTypeName, &NewNeuronType);
    string Group;
    LocalManagerP.GetFlag("group", Group);
    string IdAsString;
    int Id;
    LocalManagerP.GetFlag("id", IdAsString);
    Id = ToInt(IdAsString);
    //Lothar: check for repeated IDs
    string BaseActivation;
    LocalManagerP.GetFlag("base_activation", BaseActivation);
    string FastInput;
    vector<string> FastInputTokens;
    vector<string> FastInputList;
  if (LocalManagerP.GetFlag("fast_input", FastInput) != ReturnFail) {
    Tokenize(FastInput, FastInputTokens);
      NewNeuronType->GetFastInput(FastInputList);
    if (FastInputList.size() != FastInputTokens.size()) {
      Log.CodedMessage("DV-039");
    }
  }
  vector<string> ParametersName;
    NewNeuronType->GetParametersName(ParametersName);
    vector<string> ParameterValues;
  for (int i = 0; i < ParametersName.size(); i++) {
    int FastIndex = -1;
    for (int j = 0; j < FastInputList.size(); j++) {
      if (ParametersName[i] == FastInputList[j]) {
        FastIndex = j;
          j = FastInputList.size();
      }
    }
    if (FastIndex < 0) {
      string Dummy;
      if (LocalManagerP.GetFlag(ParametersName[i], Dummy) == ReturnFail) {
        return Return(ReturnFail, "DV-040: " + ParametersName[i]);
      } else {
        ParameterValues.push_back(Dummy);
      }
    } else {
      ParameterValues.push_back(FastInputTokens[FastIndex]);
    }
  }
  SimulatorDepository.CurrentSimulator()->AddNeuron(NewNeuronType, Group, Id, BaseActivation, ParameterValues);

  return ReturnSuccess;
}

ReturnType setsim_add_link(CommandLine &LocalManagerP)
{
  string ToId;
    string ToType;
    string ToGroup;
    LocalManagerP.GetFlag("to_id", ToId);
    LocalManagerP.GetFlag("to_type", ToType);
    LocalManagerP.GetFlag("to_group", ToGroup);
    vector<Neuron*> ToNeuronsPointers;
    SimulatorDepository.CurrentSimulator()->GetNeurons(ToNeuronsPointers, ToId, ToType, ToGroup);
    string FromId;
    string FromType;
    string FromGroup;
    LocalManagerP.GetFlag("from_id", FromId);
    LocalManagerP.GetFlag("from_type", FromType);
    LocalManagerP.GetFlag("from_group", FromGroup);
    bool Verbose = false;
  if (LocalManagerP.GetFlag("verbose") != ReturnFail) {
    Verbose = true;
  }
  vector<Neuron*> FromNeuronsPointers;
    SimulatorDepository.CurrentSimulator()->GetNeurons(FromNeuronsPointers, FromId, FromType, FromGroup);
    string Parameters;
    LocalManagerP.GetFlag("parameters", Parameters);
    vector<string> ParametersVector;
  if (Parameters.length() > 0) {
    Tokenize(Parameters, ParametersVector);
  } else {
    ParametersVector.clear();
  }
  if (Verbose) {
    Log.Output(MessageAllways, "Generating links"); //Lothar: fix labels
  }
  for (int i = 0; i < ToNeuronsPointers.size(); i++) {
    for (int j = 0; j < FromNeuronsPointers.size(); j++) {
      if (Verbose) {
        Log.Output(MessageAllways, "Linking neuron " + ToString(i) + " with neuron " + ToString(j)); //Lothar: fix labels
      }
      ToNeuronsPointers[i]->AddLink(FromNeuronsPointers[j], ParametersVector);
    }
  }
  return ReturnSuccess;
}

ReturnType runsim_simulate(CommandLine &LocalManagerP)
{
  SimulatorDepository.CurrentSimulator()->Simulate();
  return ReturnSuccess;
}
