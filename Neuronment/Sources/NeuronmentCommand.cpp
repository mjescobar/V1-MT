
#include "SimulatorManager.h"


#include "LogManager.h"


#include <vector>
using namespace std;
#include "extern.h"
#include "VariableManager.h"
#include "CommandManager.h"
#include "SimulatorManager.h"
#include "LogManager.h"
#include "NeuronmentCommand.h"

ReturnType report_test(CommandManager &LocalManagerP)
{
  Log.Output(MessageInformation, "Inside report_test");
  return ReturnSuccess;
}

ReturnType rescue_nproc(CommandManager &LocalManagerP)
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
        InterpreterManager Interpreter(NprocFiles[i]);
        ReturnCatch(Interpreter.LoadFile());
        if (HasRedirection) {
          ReturnCatch(Log.StartOutput(Redirection, RedirectionMode));
        } else {
          ReturnCatch(Log.IncreaseOutputLevel());
        }
        ThisFileResult = Interpreter.Process(); //Done label
        if (HasRedirection) {
          ReturnCatch(Log.StopOutput());
          RedirectionMode = RedirectionAppend;
        } else {
          ReturnCatch(Log.DecreaseOutputLevel());
        }
        ReturnCatch(Interpreter.CloseFile());
      }
    } else {
      Log.Message("UI-006");
      return ReturnFail;
    }
  } else {
    Log.Message("UI-006");
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType varman_set(CommandManager &LocalManagerP)
{
  string VariableName;
  string VariableType;
  string VariableValue;
  ReturnCatch(LocalManagerP.GetFlag("name", VariableName));
  ReturnCatch(LocalManagerP.GetFlag("type", VariableType));
  ReturnCatch(LocalManagerP.GetFlag("value", VariableValue));
  return Variable.SetSettingFromString(VariableName, VariableType, VariableValue);
}

ReturnType varman_get(CommandManager &LocalManagerP)
{
  string VariableName;
  string VariableValue;
  ReturnCatch(LocalManagerP.GetFlag("name", VariableName));
  ReturnCatch(Variable.GetSettingAsString(VariableName, VariableValue));
  Log.Output(MessageAllways, VariableValue);
  return ReturnSuccess;
}

ReturnType rescue_end_nproc(CommandManager &LocalManagerP)
{
  EarlyReturn = true;
  return ReturnSuccess;
}

ReturnType setsim_add_simulator(CommandManager &LocalManagerP)
{
  return CoreSimulator.AddSimulator();
}

ReturnType setsim_get_current_simulator(CommandManager &LocalManagerP)
{
  int CurrentSimulator;
  ReturnCatch(CoreSimulator.GetSimulatorCurrent(CurrentSimulator));
  if (CurrentSimulator < 0) {
    Log.Output(MessageAllways, "There are no simulators started");
  } else {
    Log.Output(MessageAllways, "Current Simulator: " + ToString(CurrentSimulator));
  }
  return ReturnSuccess;
}

ReturnType setsim_get_simulators_list(CommandManager &LocalManagerP)
{
  vector<string> SimulatorList;
  ReturnCatch(CoreSimulator.GetSimulatorList(SimulatorList));
  if (SimulatorList.size() > 0) {
    for (int i = 0; i < SimulatorList.size(); i++) {
      Log.Output(MessageAllways, SimulatorList[i]);
    }
  } else {
    Log.Output(MessageAllways, "There are no simulators to report");
  }
  return ReturnSuccess;
}

ReturnType setsim_set_current_simulator(CommandManager &LocalManagerP)
{
  int SimulatorId;
  string SimulatorIdString;
  if (LocalManagerP.GetFlag("simulator_id", SimulatorIdString) == ReturnFail) {
    Log.Message("IN-006: SimulatorId");
    return ReturnFail;
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Setting current simulator to Id " + ToString(SimulatorId));
  int SimulatorCount;
  ReturnCatch(CoreSimulator.GetSimulatorCount(SimulatorCount));
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.Message("IN-024");
  }
  return CoreSimulator.SetSimulatorCurrent(SimulatorId);
}

ReturnType setsim_remove_simulator(CommandManager &LocalManagerP)
{
  //Lothar check for correctly setting the new current pointer
  int SimulatorId;
  string SimulatorIdString;
  if (LocalManagerP.GetFlag("simulator_id", SimulatorIdString) == ReturnFail) {
    Log.Message("IN-006: SimulatorId");
    return ReturnFail;
  }
  SimulatorId = ToInt(SimulatorIdString);
  Log.Output(MessageAllways, "Removing simulator " + ToString(SimulatorId));
  int SimulatorCount;
  ReturnCatch(CoreSimulator.GetSimulatorCount(SimulatorCount));
  if (SimulatorId < 0 || SimulatorId >= SimulatorCount) {
    Log.Message("IN-024");
  }
  CoreSimulator.SetSimulatorCurrent(-1);
  return CoreSimulator.RemoveSimulator(SimulatorId);
}

#if 0

bool InterpreterManager::RunsimCall(vector<string> TokensP)
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
    Log.Message("IN-004: " + TokensP[1]);
  } else {
    if (!Arguments) {

      Log.Message("IN-010");
    }
  }
  return Result;
}

bool InterpreterManager::ReportCall(vector<string> TokensP)
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
    Log.Message("IN-004: " + TokensP[1]);
  } else {
    if (!Arguments) {

      Log.Message("IN-010");
    }
  }
  return Result;
}

bool InterpreterManager::VarmanCall_SET(vector<string> TokensP)
{

  return Variables.StoreSetting(TokensP);
}

bool InterpreterManager::VarmanCall_PRINT(vector<string> TokensP)
{
  if (TokensP.size() == 3) {
    bool Valid = Variables.GetSettingValid(DeleteTrailingZeros(TokensP[2]));
    if (!Valid) {
      Log.Message("IN-002");
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
        Log.Message("DV-001");
        return false;
      }
    }
    Log.Output(Message_Allways, ToPrint);
    return true;
  } else {
    Log.Message("IN-010");

    return false;
  }
}

bool InterpreterManager::RescueCall_RETURN(vector<string> TokensP)
{
  EarlyReturn = true;
  return true;
}
#endif