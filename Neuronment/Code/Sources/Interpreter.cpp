
//#include <vector>
//#include <sstream>
//#include <fstream>
//using namespace std;
#include "enum.h"
//#include "define.h"
#include "extern.h"
//#include "Tools.h"
//#include "HashEntry.h"
//#include "LogManager.h"
//#include "SettingsManager.h"
//#include "Globals.h"
#include "Interpreter.h"
#include "LogManager.h"
#include "CommandLine.h"

Interpreter::Interpreter()
{
  RuntimeAssertion();
}

Interpreter::Interpreter(const Interpreter& orig)
{
  Log.CodedMessage("DV-008: InterpreterManager");
}

Interpreter::Interpreter(string NprocFileP) :
Commands(INTERPRETER_MANAGER_COMMANDS_HASH_SIZE)
{
  NprocFile = NprocFileP;
  ReadyForReading = false;
  EndOfFileReached = false;
  ElapsedTime = clock();
  InitializeInterpreter();
}

Interpreter::~Interpreter()
{
  delete LocalManager;
}

ReturnType Interpreter::LoadFile()
{
  if (NprocFile.length() < 1) {
    Log.CodedMessage("UI-006");
    return ReturnFail;
  }
  NprocStream.open(NprocFile.c_str());
  if (NprocStream.fail()) {
    Log.CodedMessage("ER-003: " + NprocFile);
    return ReturnFail;
  }
  ReadyForReading = true;
  return ReturnSuccess;
}

ReturnType Interpreter::CloseFile()
{
  ReadyForReading = false;
  if (!NprocStream.is_open()) {
    Log.CodedMessage("ER-009: " + NprocFile);
    return ReturnFail;
  }
  NprocStream.close();
  if (NprocStream.is_open()) {
    Log.CodedMessage("ER-004: " + NprocFile);
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType Interpreter::Process()
{
  bool CommandReady;
  bool EarlyReturnInternal = false;
  ;
  bool LastLine = false;
  string Line;
  LocalManager = new CommandLine();
  while (!EndOfFileReached || LastLine) {
    ReturnCatch(LocalManager->IsReady(CommandReady));
    if (CommandReady) {
      string ThisCommand;
      ReturnCatch(LocalManager->GetCleanCommand(ThisCommand));
      ReturnType ThisCommandResult = ProcessLine(*LocalManager);
      if (EarlyReturn == true) {
        EarlyReturn = false;
        EarlyReturnInternal = true;
        Log.CodedMessage("WN-001");
      }
      if (!(ThisCommand == "rescue nproc" || ThisCommand == "")) {
        if (ThisCommandResult == ReturnFail) {
          Log.MessageFail();
        } else {
          Log.MessageDone();
        }
      }
      if (EarlyReturnInternal) {
        break;
      }
      if (!LastLine) {
        ReturnCatch(LocalManager->Restart());
      } else {
        LastLine = false;
      }
    } else {
      if (!LastLine) {
        ReturnCatch(GetNextLine(Line));
        ReturnCatch(Log.Output(MessageAllways, Line));
        ReturnCatch(LocalManager->Append(Line));
        if (EndOfFileReached) {
          LastLine = true;
        }
      }
    }
  }
  if (!EarlyReturnInternal) {
    ReturnCatch(LocalManager->IsReady(CommandReady));
    if (!CommandReady) {
      Log.CodedMessage("IN-018");
      return ReturnSuccessWarning;
    }
  }
  return ReturnSuccess;
}

ReturnType Interpreter::GetNextLine(string &LineP)
{
  string InternalLine;
  if (!ReadyForReading) {
    Log.CodedMessage("ER-005: " + NprocFile);
    return ReturnFail;
  }
  if (EndOfFileReached) {
    Log.CodedMessage("ER-006: " + NprocFile);
    return ReturnFail;
  }
  if (NprocStream.eof()) {
    Log.CodedMessage("ER-010: " + NprocFile);
    return ReturnFail;
  }
  getline(NprocStream, InternalLine);
  LastLine = trim_right(InternalLine, "\n\r");
  if (NprocStream.eof()) {
    EndOfFileReached = true;
  }
  LineP = InternalLine;
  return ReturnSuccess;
}

ReturnType Interpreter::ProcessLine(CommandLine &LocalManagerP)
{
  // Retrieving values
  bool HasCommand;
  string Command;
  bool HasRedirection;
  string Redirection;
  RedirectionType RedirectionMode;
  bool HasComment;
  string Comment;
  ReturnCatch(LocalManagerP.HasCommand(HasCommand));
  if (HasCommand) {
    ReturnCatch(LocalManagerP.GetCommand(Command));
  }
  ReturnCatch(LocalManagerP.HasRedirection(HasRedirection));
  if (HasRedirection) {
    ReturnCatch(LocalManagerP.GetRedirection(Redirection));
    ReturnCatch(LocalManagerP.GetRedirectionType(RedirectionMode));
  }
  ReturnCatch(LocalManagerP.HasComment(HasComment));
  if (HasComment) {
    ReturnCatch(LocalManagerP.GetCommand(Comment));
  }
  if (!HasCommand) {
    if (!HasRedirection) {
      // 00X
      return ReturnSuccess;
    } else {
      // 01X
      if (!HasComment) {
        // 010
        Log.CodedMessage("IN-019");
        return ReturnSuccessWarning;
      } else {
        // 011
        Log.CodedMessage("IN-020");
        return ReturnSuccessWarning;
      }
    }
  } else {
    ReturnCatch(ProcessCommand(LocalManagerP));
    return ReturnSuccess;
  }
}

ReturnType Interpreter::ProcessCommand(CommandLine &LocalManagerP)
{
  // Calculate function name
  string FunctionName = "";
  string FunctionNameToPrint = "";
  ReturnCatch(LocalManagerP.GetCleanCommand(FunctionNameToPrint));
  ReturnCatch(LocalManagerP.GetCleanCommand(FunctionName, "_"));
  // Retrieve function name
  void* Function = NULL;
  if (Commands.GetEntryQuick(FunctionName, Function) == ReturnFail) {
    Log.CodedMessage("IN-001: " + FunctionNameToPrint);
    return ReturnSuccessWarning;
  }
  // Execute function
  return ((ReturnType(*)(CommandLine&))Function)(LocalManagerP);
}
