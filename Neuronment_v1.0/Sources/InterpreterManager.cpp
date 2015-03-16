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
  Commands = HashTable(Data_function);
  InitializeInterpreter();
}

InterpreterManager::InterpreterManager(const InterpreterManager& orig)
{
  ReadyForReading = orig.ReadyForReading;
  EndOfFileReached = orig.EndOfFileReached;
  nproc = orig.nproc;
  Commands = orig.Commands;
}

InterpreterManager::~InterpreterManager()
{
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
  vector<string> Tokens;
  if (trim(LastLine).size() < 1) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  TokenizeNoDelete(LastLine, PreTokens, LABEL_COMMENT_STRING);
  if (PreTokens[0][0] == LABEL_COMMENT_CHAR) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  if (PreTokens.size() > 1 && trim(PreTokens[0]).size() == 0 && PreTokens[1][0] == LABEL_COMMENT_CHAR) {
    Log.Output(Message_Allways, LastLine);
    return Result_silent;
  }
  Log.Output(Message_Allways, LastLine);
  Tokenize(trim(PreTokens[0]), Tokens);
  if (Tokens.size() < 1) {
    return Result_silent;
  }
  for (int i = 0; i < Tokens.size(); i++) {
    Tokens[i] = trim(Tokens[i]);
  }
  if (Tokens.size() > 1) {
    string CommandString;
    string ToMessage;
    if (Tokens[0] == LABEL_ENVIRONMENT_SETTINGS || Tokens[0] == LABEL_SIMULATOR_SETTINGS) {
      CommandString = Tokens[0];
      ToMessage = Tokens[0];
    } else {
      CommandString = Tokens[0] + Tokens[1];
      ToMessage = Tokens[0] + " " + Tokens[1];
    }
    if (Commands.GetEntry(CommandString) != NULL) {
      if (Commands.GetEntry(CommandString)->GetContent() != NULL) {
        if (((bool (*)(vector<string>))(Commands.GetEntry(CommandString)->GetContent()))(Tokens)) {
          return Result_true;
        } else {
          return Result_false;
        }
      } else {
        Log.Message("SD-032");
        return Result_false;
      }
    } else {
      Log.Message("IN-001: " + ToMessage);
      return Result_false;
    }
  } else {
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
  while (!GetEndOfFileReached()) {
    if (!NextLine()) {
      Log.Message("ER-007: " + nproc);
    } else {
      Result = InterpretateLine();
      if (Result != Result_silent) {
        if (!Environment.GetSingleSetting_bool(HIDE_END, DEFAULT_HIDE_END)) {
          string VerboseResult = (Result == Result_true) ? LABEL_DONE : LABEL_FAIL;
          Log.Output(Message_Allways, VerboseResult);
        }
      }
    }
  }
}

bool InterpreterManager::ReportCallSettingPrint(SettingsManager &TempManager, vector<string> TokensP)
{
  bool Valid = TempManager.GetSettingValid(TokensP[2]);
  if (!Valid) {
    Log.Message("IN-002");
    return false;
  }
  DataType SettingType = TempManager.GetSettingType(TokensP[2]);
  string ToPrint = TokensP[2] + ":";
  for (int i = 0; i < TempManager.GetSettingSize(TokensP[2]); i++) {
    switch (SettingType) {
    case Data_bool:
      if (((bool*)TempManager.GetSettingContent(TokensP[2]))[i]) {
        ToPrint = ToPrint + " TRUE";
      } else {
        ToPrint = ToPrint + " FALSE";
      }
      break;
    case Data_double:
      ToPrint = ToPrint + " " + IDoubleToString(((double*) TempManager.GetSettingContent(TokensP[2]))[i]);
      break;
    default:
      Log.Message("DV-001");
      return false;
    }
  }
  Log.Output(Message_Allways, ToPrint);
  return true;
}

bool InterpreterManager::SetenvCall(vector<string> TokensP)
{
  return Environment.StoreSetting(TokensP);
}

bool InterpreterManager::SetsimCall(vector<string> TokensP)
{
  return Simulation.StoreSetting(TokensP);
}

bool InterpreterManager::RunsimCall(vector<string> TokensP)
{
  bool Result = false;
  bool Found = false;
  bool Arguments = true;
  if (TokensP[1] == SS_INITIALIZE) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.InitializeNeurons();
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == SS_ADD_V1_DIFFUSION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.AddV1Diffusion();
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == SS_SIMULATE) {
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
  if (TokensP[1] == PRINT_ENV) {
    Found = true;
    if (TokensP.size() == 3) {
      Result = ReportCallSettingPrint(Environment, TokensP);
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == PRINT_SIM) {
    Found = true;
    if (TokensP.size() == 3) {
      Result = ReportCallSettingPrint(Simulation, TokensP);
    } else {
      Arguments = false;
    }
  }
  if (TokensP[1] == SS_PRINT_V1_ACTIVATION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintV1Activation(Orientation_Vertical);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintV1Activation(Orientation_Vertical, TokensP[2]);
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == SS_PRINT_V1_ACTIVATION_HORIZONTAL) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintV1Activation(Orientation_Horizontal);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintV1Activation(Orientation_Horizontal, TokensP[2]);
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == SS_PRINT_V1_EXTERNAL_EXCITATION) {
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
  if (TokensP[1] == SS_PRINT_MT_ACTIVATION) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintMTActivation(Orientation_Vertical);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintMTActivation(Orientation_Vertical, TokensP[2]);
      } else {
        Arguments = false;
      }
    }
  }
  if (TokensP[1] == SS_PRINT_MT_ACTIVATION_HORIZONTAL) {
    Found = true;
    if (TokensP.size() == 2) {
      Result = SingleSimulator.PrintMTActivation(Orientation_Horizontal);
    } else {
      if (TokensP.size() == 3) {
        Result = SingleSimulator.PrintMTActivation(Orientation_Horizontal, TokensP[2]);
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

bool InterpreterManager::RescueCall(vector<string> TokensP)
{
  bool Result = false;
  bool Found = false;
  if (!Found) {
    Log.Message("IN-004: " + TokensP[1]);
  }
  return Result;
}

bool InterpreterManager::RescueCall_NPROC(vector<string> TokensP)
{
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
  return true;
}
