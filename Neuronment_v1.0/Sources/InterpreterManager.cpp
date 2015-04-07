/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "Globals.h"
#include "InterpreterManager.h"

InterpreterManager::InterpreterManager()
{
  ReadyForReading = false;
  EndOfFileReached = false;
  nproc = "";
  ElapsedTime = clock();
  Commands = HashTable(Data_function, INTERPRETER_MANAGER_COMMANDS_HASH_SIZE);
  NprocNesting++;
  InitializeInterpreter();
}

InterpreterManager::InterpreterManager(const InterpreterManager& orig)
{
  ReadyForReading = orig.ReadyForReading;
  EndOfFileReached = orig.EndOfFileReached;
  nproc = orig.nproc;
  Commands = orig.Commands;
  ElapsedTime = orig.ElapsedTime;
}

InterpreterManager::~InterpreterManager()
{
  NprocNesting--;
}

bool InterpreterManager::LoadFile()
{
  if (nproc.length() < 1) {
    Log.Message("UI-006");
    return false;
  }
  NprocStream.open(nproc.c_str());
  if (NprocStream.fail()) {
    Log.Message("ER-003: " + nproc);
    return false;
  }
  ReadyForReading = true;
  return true;
}

bool InterpreterManager::CloseFile()
{
  ReadyForReading = false;
  if (!NprocStream.is_open()) {
    Log.Message("ER-009: " + nproc);
    return false;
  }
  NprocStream.close();
  if (NprocStream.is_open()) {
    Log.Message("ER-004: " + nproc);
    return false;
  }
  return true;
}

bool InterpreterManager::NextLine()
{
  if (!ReadyForReading) {
    Log.Message("ER-005: " + nproc);
    return false;
  }
  if (EndOfFileReached) {
    Log.Message("ER-006: " + nproc);
    return false;
  }
  if (NprocStream.eof()) {
    Log.Message("ER-010: " + nproc);
    return false;
  }
  getline(NprocStream, LastLine);
  LastLine = trim_right(LastLine, "\n\r");
  if (NprocStream.eof()) {
    EndOfFileReached = true;
  }
  return true;
}

bool InterpreterManager::GetEndOfFileReached()
{
  return EndOfFileReached;
}

ResultType InterpreterManager::InterpretateLine()
{
  vector<string> PreTokens;
  vector<string> RedirectionTokens;
  vector<string> Tokens;
  if (trim(LastLine).size() < 1) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  TokenizeNoDelete(LastLine, PreTokens, LABEL_COMMENT_STRING);
  // If the line is a comment from the first character
  if (PreTokens[0][0] == LABEL_COMMENT_CHAR) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  // If the line is a comment from character n but without a command
  if (PreTokens.size() > 1 && trim(PreTokens[0]).size() == 0 && PreTokens[1][0] == LABEL_COMMENT_CHAR) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  // If the line holds a command
  Log.Output(Message_Allways, LastLine);
  // Looking for possible redirection
  Tokenize(trim(PreTokens[0]), RedirectionTokens, LABEL_REDIRECTION_STRING);
  // More than one redirection character
  if (RedirectionTokens.size() > 2 || RedirectionTokens.size() < 1) {
    Log.Message("IN-010");
    return Result_false;
  }
  // If there is redirection, set the redirection
  if (RedirectionTokens.size() == 2) {
    Log.StartOutputRedirection(trim(RedirectionTokens[1]));
  }
  Tokenize(trim(RedirectionTokens[0]), Tokens);
  if (Tokens.size() < 1) {
    return Result_silent;
  }
  for (int i = 0; i < Tokens.size(); i++) {
    Tokens[i] = trim(Tokens[i]);
  }
  if (Tokens.size() > 1) {
    string CommandString;
    string ToMessage;
    CommandString = Tokens[0] + Tokens[1];
    ToMessage = Tokens[0] + " " + Tokens[1];
    if (Commands.GetEntry(CommandString) != NULL) {
      if (Commands.GetEntry(CommandString)->GetContent() != NULL) {
        if (((bool (*)(vector<string>))(Commands.GetEntry(CommandString)->GetContent()))(Tokens)) {
          Log.StopOutputRedirection();
          return Result_true;
        } else {
          Log.StopOutputRedirection();
          return Result_false;
        }
      } else {
        Log.StopOutputRedirection();
        Log.Message("SD-032");
        return Result_false;
      }
    } else {
      Log.StopOutputRedirection();
      Log.Message("IN-001: " + ToMessage);
      return Result_false;
    }
  } else {
    Log.StopOutputRedirection();
    Log.Message("IN-010");
    return Result_false;
  }
}

bool InterpreterManager::SetNproc(string NprocP)
{
  if (NprocP.length() > 0) {
    nproc = NprocP;
    return true;
  } else {
    Log.Message("UI-006");
    return false;
  }
}

void InterpreterManager::Process()
{
  ResultType Result;
  while (!GetEndOfFileReached() && !EarlyReturn) {
    if (!NextLine()) {
      Log.Message("ER-007: " + nproc);
    } else {
      Result = InterpretateLine();
      if (Result != Result_silent) {
        if (Variables.GetSingleSetting_bool(SHOW_ELAPSED_TIME, DEFAULT_SHOW_ELAPSED_TIME)) {
          PrintElapsedTime(&ElapsedTime);
        }
        if (!Variables.GetSingleSetting_bool(HIDE_END, DEFAULT_HIDE_END)) {
          string VerboseResult = (Result == Result_true) ? LABEL_DONE : LABEL_FAIL;
          Log.Output(Message_Allways, VerboseResult);
        }
      }
    }
  }
}

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

bool InterpreterManager::RescueCall_NPROC(vector<string> TokensP)
{
  if (NprocNesting > Variables.GetSingleSetting_int(MAX_NPROC_NESTING, DEFAULT_MAX_NPROC_NESTING)) {
    Log.Message("IN-008");
    return false;
  }
  bool SilentFlag = GetFlag(TokensP, "silent");
  string FileName = GetFlagValue(TokensP, "file");
  if (FileName.size() == 0) {
    Log.Message("IN-010");
    return false;
  }
  InterpreterManager LocalInterpreter;
  LocalInterpreter.InitializeInterpreter();
  LocalInterpreter.SetNproc(FileName);
  LocalInterpreter.LoadFile();
  if (SilentFlag) {
    Log.SetSilentOutput();
  }
  LocalInterpreter.Process();
  if (SilentFlag) {
    Log.UnsetSilentOutput();
  }
  LocalInterpreter.CloseFile();
  EarlyReturn = false;
  return true;
}