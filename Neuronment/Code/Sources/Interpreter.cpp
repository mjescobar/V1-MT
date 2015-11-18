
#include "enum.h"
#include "extern.h"
#include "Interpreter.h"
#include "LogManager.h"
#include "CommandLine.h"

Interpreter::Interpreter()
{
  Return(ReturnFail, "Message because this method should never be used");
  ImplementationAssertion(); //Lothar: Remove once the message assertion is configured
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
    return Return(ReturnFail, "UI-006");
  }
  NprocStream.open(NprocFile.c_str());
  if (NprocStream.fail()) {
    return Return(ReturnFail, "ER-003: " + NprocFile);
  }
  ReadyForReading = true;
  return ReturnSuccess;
}

ReturnType Interpreter::CloseFile()
{
  ReadyForReading = false;
  if (!NprocStream.is_open()) {
    return Return(ReturnFail, "ER-009: " + NprocFile);
  }
  NprocStream.close();
  if (NprocStream.is_open()) {
    return Return(ReturnFail, "ER-004: " + NprocFile);
  }
  return ReturnSuccess;
}

ReturnType Interpreter::Process()
{
  bool CommandReady;
  bool EarlyReturnInternal = false;
  bool LastLine = false;
  string Line;
  LocalManager = new CommandLine();
  while (!EndOfFileReached || LastLine) {
    LocalManager->IsReady(CommandReady);
    if (CommandReady) {
      string ThisCommand;
      LocalManager->GetCleanCommand(ThisCommand);
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
        LocalManager->Restart();
      } else {
        LastLine = false;
      }
    } else {
      if (!LastLine) {
        GetNextLine(Line);
        Log.Output(MessageAllways, Line);
        LocalManager->Append(Line);
        if (EndOfFileReached) {
          LastLine = true;
        }
      }
    }
  }
  if (!EarlyReturnInternal) {
    LocalManager->IsReady(CommandReady);
    if (!CommandReady) {
      Log.CodedMessage("IN-018");
      return ReturnSuccess;
    }
  }
  return ReturnSuccess;
}

ReturnType Interpreter::GetNextLine(string &LineP)
{
  string InternalLine;
  if (!ReadyForReading) {
    return Return(ReturnFail, "ER-005: " + NprocFile);
  }
  if (EndOfFileReached) {
    return Return(ReturnFail, "ER-006: " + NprocFile);
  }
  if (NprocStream.eof()) {
    return Return(ReturnFail, "ER-010: " + NprocFile);
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
  LocalManagerP.HasCommand(HasCommand);
  if (HasCommand) {
    LocalManagerP.GetCommand(Command);
  }
  LocalManagerP.HasRedirection(HasRedirection);
  if (HasRedirection) {
    LocalManagerP.GetRedirection(Redirection);
    LocalManagerP.GetRedirectionType(RedirectionMode);
  }
  LocalManagerP.HasComment(HasComment);
  if (HasComment) {
    LocalManagerP.GetCommand(Comment);
  }
  if (!HasCommand) {
    if (!HasRedirection) {
      // 00X
      return ReturnSuccess;
    } else {
      // 01X
      if (!HasComment) {
        // 010
        return Return(ReturnSuccess, "IN-019");
      } else {
        // 011
        return Return(ReturnSuccess, "IN-020");
      }
    }
  } else {
    ProcessCommand(LocalManagerP);
    return ReturnSuccess;
  }
}

ReturnType Interpreter::ProcessCommand(CommandLine &LocalManagerP)
{
  // Calculate function name
  string FunctionName = "";
  string FunctionNameToPrint = "";
  LocalManagerP.GetCleanCommand(FunctionNameToPrint);
  LocalManagerP.GetCleanCommand(FunctionName, "_");
  // Retrieve function name
  void* Function = NULL;
  if (Commands.GetEntryQuick(FunctionName, Function) == ReturnFail) {
    return Return(ReturnSuccess, "IN-001: " + FunctionNameToPrint);
  }
  // Execute function
  return ((ReturnType(*)(CommandLine&))Function)(LocalManagerP);
}
