/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include "extern.h"
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
      Result = SingleSimulator.Simulate(IStringToInt(TokensP[2]));
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
      Result = SingleSimulator.PrintV1ExternalExcitation(IStringToInt(TokensP[2]));
    } else {
      if (TokensP.size() == 4) {
        Result = SingleSimulator.PrintV1ExternalExcitation(IStringToInt(TokensP[2]), TokensP[3]);
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
        ToPrint = ToPrint + " " + IDoubleToString(((double*) Variables.GetSettingContent(DeleteTrailingZeros(TokensP[2])))[i]);
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