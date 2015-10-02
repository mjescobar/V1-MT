
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
  Log.Output(MessageInformation, "Inside report_test");
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
  RedirectionType RedirectionMode;
  ReturnCatch(LocalManagerP.HasRedirection(HasRedirection));
  if (HasRedirection) {
    ReturnCatch(LocalManagerP.GetRedirection(Redirection));
    ReturnCatch(LocalManagerP.GetRedirectionType(RedirectionMode));
  }
  string NprocList;
  ReturnType ThisFileResult;
  if (LocalManagerP.GetFlag("nproc", NprocList) == ReturnSuccess) {
    if (NprocList.length() > 0) {
      vector<string> NprocFiles;
      ReturnCatch(Tokenize(NprocList, NprocFiles));
      for (int i = 0; i < NprocFiles.size(); i++) {
        Interpreter LocalInterpreter(NprocFiles[i]);
        ReturnCatch(LocalInterpreter.LoadFile());
        if (HasRedirection) {
          ReturnCatch(Log.InitiateRedirection(Redirection, RedirectionMode));
        } else {
          ReturnCatch(Log.IncreaseOutputLevel());
        }
        ThisFileResult = LocalInterpreter.Process(); //Done label
        if (HasRedirection) {
          ReturnCatch(Log.TerminateRedirection());
          RedirectionMode = RedirectionAppend;
        } else {
          ReturnCatch(Log.DecreaseOutputLevel());
        }
        ReturnCatch(LocalInterpreter.CloseFile());
      }
    } else {
      Log.CodedMessage("UI-006");
      return ReturnFail;
    }
  } else {
    Log.CodedMessage("UI-006");
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType varman_set(CommandLine &LocalManagerP)
{
  string VariableName;
  string VariableType;
  string VariableValue;
  string VariableSimulator;
  ReturnCatch(LocalManagerP.GetFlag("name", VariableName));
  ReturnCatch(LocalManagerP.GetFlag("type", VariableType));
  ReturnCatch(LocalManagerP.GetFlag("value", VariableValue));
  if (LocalManagerP.GetFlag("simulator", VariableSimulator) == ReturnFail) {
    return GlobalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
  } else {
    if (VariableSimulator == "current") {
      return SimulatorDepository.CurrentSimulator()->InternalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
    } else {
      return SimulatorDepository.GetSimulator(ToInt(VariableSimulator))->InternalVariables.SetSettingFromString(VariableName, VariableType, VariableValue);
    }
  }
}

ReturnType varman_get(CommandLine &LocalManagerP)
{
  string VariableName;
  string VariableValue;
  ReturnCatch(LocalManagerP.GetFlag("name", VariableName));
  ReturnCatch(GlobalVariables.GetSettingAsString(VariableName, VariableValue));
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
  return SimulatorDepository.AddSimulator();
}

ReturnType setsim_get_current_simulator(CommandLine &LocalManagerP)
{
  int CurrentSimulator;
  ReturnCatch(SimulatorDepository.GetSimulatorCurrent(CurrentSimulator));
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
  ReturnCatch(SimulatorDepository.GetSimulatorList(SimulatorList));
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
    Log.CodedMessage("IN-006: SimulatorId");
    return ReturnFail;
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Setting current simulator to Id " + ToString(SimulatorId));
  int SimulatorCount;
  ReturnCatch(SimulatorDepository.GetSimulatorCount(SimulatorCount));
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.CodedMessage("IN-024");
  }
  return SimulatorDepository.SetSimulatorCurrent(SimulatorId);
}

ReturnType setsim_remove_simulator(CommandLine &LocalManagerP)
{
  //Lothar check for correctly setting the new current pointer
  int SimulatorId;
  string SimulatorIdString;
  if (LocalManagerP.GetFlag("simulator_id", SimulatorIdString) == ReturnFail) {
    Log.CodedMessage("IN-006: SimulatorId");
    return ReturnFail;
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Removing simulator " + ToString(SimulatorId));
  int SimulatorCount;
  ReturnCatch(SimulatorDepository.GetSimulatorCount(SimulatorCount));
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.CodedMessage("IN-024");
  }
  SimulatorDepository.SetSimulatorCurrent(-1);
  return SimulatorDepository.RemoveSimulator(SimulatorId);
}

ReturnType setsim_new_neuron_type(CommandLine &LocalManagerP)
{
  string Name;
  ReturnCatch(LocalManagerP.GetFlag("name", Name));
  int ActivationLevels;
  string ActivationLevelsString;
  ReturnCatch(LocalManagerP.GetFlag("activation_levels", ActivationLevelsString));
  ActivationLevels = ToInt(ActivationLevelsString);
  vector<string> ActivationFunctions;
  for (int i = 0; i < ActivationLevels; i++) {
    string Tmp;
    ReturnCatch(LocalManagerP.GetFlag("activation_function_" + ToString(i), Tmp));
    ActivationFunctions.push_back(Tmp);
  }
  string Parameters;
  vector<string> ParametersTokenized;
  ReturnCatch(LocalManagerP.GetFlag("parameters", Parameters));
  ReturnCatch(Tokenize(Parameters, ParametersTokenized));
  if (ParametersTokenized.size() % 2 != 0) {
    Log.CodedMessage("IN-025");
    return ReturnFail;
  }
  vector<string> ParametersName;
  vector<string> ParametersType;
  for (int i = 0; i < ParametersTokenized.size(); i = i + 2) {
    if (IsValidType(ParametersTokenized[i]) == ReturnFail) {
      Log.CodedMessage("IN-025");
      return ReturnFail;
    }
    ParametersName.push_back(ParametersTokenized[i + 1]);
    ParametersType.push_back(ParametersTokenized[i]);
  }
  string DataType;
  ReturnCatch(LocalManagerP.GetFlag("data_type", DataType));
  ReturnCatch(SimulatorDepository.AddNeuronType(Name, DataType, ActivationLevels, ActivationFunctions, ParametersName, ParametersType));
  string FastInput;
  if (LocalManagerP.GetFlag("fast_input", FastInput) != ReturnFail) {
    ReturnCatch(SimulatorDepository.SetNeuronTypeFastInput(Name, FastInput));
  }
  return ReturnSuccess;
}

ReturnType setsim_add_neuron(CommandLine &LocalManagerP)
{
  NeuronType *NewNeuronType;
  string NeuronTypeName;
  ReturnCatch(LocalManagerP.GetFlag("neuron_type", NeuronTypeName));
  ReturnCatch(SimulatorDepository.GetNeuronType(NeuronTypeName, &NewNeuronType));
  string Group;
  ReturnCatch(LocalManagerP.GetFlag("group", Group));
  string IdAsString;
  int Id;
  ReturnCatch(LocalManagerP.GetFlag("id", IdAsString));
  Id = ToInt(IdAsString);
  //Lothar check for repeated IDs
  string BaseActivation;
  LocalManagerP.GetFlag("base_activation", BaseActivation);
  string FastInput;
  vector<string> FastInputTokens;
  vector<string> FastInputList;
  if (LocalManagerP.GetFlag("fast_input", FastInput) != ReturnFail) {
    ReturnCatch(Tokenize(FastInput, FastInputTokens));
    ReturnCatch(NewNeuronType->GetFastInput(FastInputList));
    if (FastInputList.size() != FastInputTokens.size()) {
      Log.CodedMessage("DV-039");
    }
  }
  vector<string> ParametersName;
  ReturnCatch(NewNeuronType->GetParametersName(ParametersName));
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
        Log.CodedMessage("DV-040: " + ParametersName[i]);
        return ReturnFail;
      } else {
        ParameterValues.push_back(Dummy);
      }
    } else {
      ParameterValues.push_back(FastInputTokens[FastIndex]);
    }
  }
  return SimulatorDepository.CurrentSimulator()->AddNeuron(NewNeuronType, Group, Id, BaseActivation, ParameterValues);
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
  return SimulatorDepository.CurrentSimulator()->Simulate();
}

#if 0

bool Interpreter::RunsimCall(vector<string> TokensP)
{
  bool Result = false;
  bool Found = false;
  bool Arguments = true;
  if (TokensP[1] == RUNSIM_SS_INITIALIZE) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.InitializeNeurons();
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == RUNSIM_SS_ADD_V1_DIFFUSION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.AddV1Diffusion();
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == RUNSIM_SS_SIMULATE) {
    Found = true;
    if (TokensP.size() == 3) {
      Result = SingleSimulator.Simulate(ToInt(TokensP[2]));
    } else {
      Arguments = false;
    }
  }
  if (!Found) {
    Log.CodedMessage("IN-004: " + TokensP[1]);
  } else {
    if (!Arguments) {

      Log.CodedMessage("IN-010");
    }
  }
  return Result;
}

bool Interpreter::ReportCall(vector<string> TokensP)
{
  bool Result = false;
  bool Found = false;
  bool Arguments = true;
  if (TokensP[1] == REPORT_SS_PRINT_V1_ACTIVATION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintV1Activation(Orientation_Vertical);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintV1Activation(Orientation_Vertical, trim(TokensP[2]));
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == REPORT_SS_PRINT_V1_ACTIVATION_HORIZONTAL) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintV1Activation(Orientation_Horizontal);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintV1Activation(Orientation_Horizontal, trim(TokensP[2]));
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == REPORT_SS_PRINT_V1_EXTERNAL_EXCITATION) {
    Found = true;
    if (TokensP.size() == 3) {
      Result = SingleSimulator.PrintV1ExternalExcitation(ToInt(TokensP[2]));
    } else {
      if (TokensP.size() == 4) {
        Result = SingleSimulator.PrintV1ExternalExcitation(ToInt(TokensP[2]), TokensP[3]);
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == REPORT_SS_PRINT_MT_ACTIVATION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintMTActivation(Orientation_Vertical);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintMTActivation(Orientation_Vertical, trim(TokensP[2]));
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == REPORT_SS_PRINT_MT_ACTIVATION_HORIZONTAL) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintMTActivation(Orientation_Horizontal);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintMTActivation(Orientation_Horizontal, trim(TokensP[2]));
      } else {
        Arguments = false;
      }
    }
  }
  if (!Found) {
    Log.CodedMessage("IN-004: " + TokensP[1]);
  } else {
    if (!Arguments) {

      Log.CodedMessage("IN-010");
    }
  }
  return Result;
}

bool Interpreter::VarmanCall_SET(vector<string> TokensP)
{

  return Variables.StoreSetting(TokensP);
}

bool Interpreter::VarmanCall_PRINT(vector<string> TokensP)
{
  if (TokensP.size() == 3) {
    bool Valid = Variables.GetSettingValid(DeleteTrailingZeros(TokensP[2]));
    if (!Valid) {
      Log.CodedMessage("IN-002");
      return false;
    }
    DataType SettingType = Variables.GetSettingType(DeleteTrailingZeros(TokensP[2]));
    string ToPrint = "";
    if (DeleteTrailingZeros(TokensP[2]) != TokensP[2]) {
      ToPrint = TokensP[2] + "(" + DeleteTrailingZeros(TokensP[2]) + ") =";
    } else {
      ToPrint = TokensP[2] + " =";
    }
    for (int i = 0; i < Variables.GetSettingSize(DeleteTrailingZeros(TokensP[2])); i++) {
      switch (SettingType) {
      case Data_bool:
        if (((bool*)Variables.GetSettingContent(DeleteTrailingZeros(TokensP[2])))[i]) {
          ToPrint = ToPrint + " TRUE";
        } else {
          ToPrint = ToPrint + " FALSE";
        }
        break;
      case Data_double:
        ToPrint = ToPrint + " " + ToString(((double*) Variables.GetSettingContent(DeleteTrailingZeros(TokensP[2])))[i]);
        break;
      case Data_string:
        ToPrint = ToPrint + " " + ((string*) Variables.GetSettingContent(DeleteTrailingZeros(TokensP[2])))[i];
        break;
      default:
        Log.CodedMessage("DV-001");
        return false;
      }
    }
    Log.Output(Message_Allways, ToPrint);
    return true;
  } else {
    Log.CodedMessage("IN-010");

    return false;
  }
}

bool Interpreter::RescueCall_RETURN(vector<string> TokensP)
{
  EarlyReturn = true;
  return true;
}
#endif
