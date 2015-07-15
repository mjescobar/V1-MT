/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

//#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <bits/basic_string.h>
//using namespace std;
//#include "enum.h"
//#include "define.h"
#include "tools.h"
//#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
//#include "SettingsManager.h"
#include "extern.h"

LogManager::LogManager() :
MessagesLabel(LOG_MANAGER_HASH_SIZE),
MessagesText(LOG_MANAGER_HASH_SIZE),
MessagesDisabling(LOG_MANAGER_HASH_SIZE),
MessagesCount(LOG_MANAGER_HASH_SIZE),
MessagesDevelopmentAssert(LOG_MANAGER_HASH_SIZE),
MessagesRuntimeAssert(LOG_MANAGER_HASH_SIZE),
MessagesImplementationAssert(LOG_MANAGER_HASH_SIZE)
{
  ShowMessageInformation = DEFAULT_SHOW_MESSAGE_INFORMATION;
  ShowMessageCodedInformation = DEFAULT_SHOW_MESSAGE_CODED_INFORMATION;
  ShowMessageCoded = DEFAULT_SHOW_MESSAGE_CODED;
  ShowMessageDevelopment = DEFAULT_SHOW_MESSAGE_DEVELOPMENT;
  ShowMessageAllways = DEFAULT_SHOW_MESSAGE_ALLWAYS;
  Destination.push_back(&cout);
  ReturnCatch(Log.InitializeMessages());
}

LogManager::LogManager(const LogManager& orig)
{
  Log.Message("DV-008: LogManager");
}

LogManager::~LogManager()
{
}

ReturnType LogManager::DisplayHeader()
{
  Output(MessageAllways, "====================================================================================");
  Output(MessageAllways, "========================== Neuronment v0.3 - " __DATE__ " ===========================");
  Output(MessageAllways, "====================================================================================");
  return ReturnSuccess;
}

ReturnType LogManager::DisplayFooter()
{
  Output(MessageAllways, "====================================================================================");
  Output(MessageAllways, " Bye!");
  return ReturnSuccess;
}

ReturnType LogManager::Message(string IdP, bool SkipAssertionP)
{
  DataCheck(IdP, "NonEmpty");

  vector<int> Disabling;
  bool DisablingFound;
  vector<int> Count;
  bool CountFound;
  vector<bool> DevelopmentAssert;
  bool DevelopmentAssertFound;
  vector<bool> RuntimeAssert;
  bool RuntimeAssertFound;
  vector<bool> ImplementationAssert;
  bool ImplementationAssertFound;
  vector<string> Label;
  bool LabelFound;

  string Id = IdP.substr(0, 6);

  ReturnCatch(GetInternalValue(Id, MessagesDisabling, Disabling, DisablingFound), "ContinueOnFail");
  ReturnCatch(GetInternalValue(Id, MessagesCount, Count, CountFound), "ContinueOnFail");
  ReturnCatch(GetInternalValue(Id, MessagesDevelopmentAssert, DevelopmentAssert, DevelopmentAssertFound), "ContinueOnFail");
  ReturnCatch(GetInternalValue(Id, MessagesRuntimeAssert, RuntimeAssert, RuntimeAssertFound), "ContinueOnFail");
  ReturnCatch(GetInternalValue(Id, MessagesImplementationAssert, ImplementationAssert, ImplementationAssertFound), "ContinueOnFail");
  ReturnCatch(GetInternalValue(Id, MessagesLabel, Label, LabelFound), "ContinueOnFail");

  if (!(DisablingFound && CountFound && DevelopmentAssertFound && RuntimeAssertFound && ImplementationAssertFound && LabelFound)) {
    Output(MessageCoded, IdP);
    Log.Message("DV-023");
  }

  if (Disabling[0]) {
    if (Count[0] < Disabling[0]) {
      Count[0]++;
      MessagesCount.PutEntry(Id, Count);
      Output(MessageCoded, LABEL_MESSAGE_STRING + IdP);
      Output(MessageCodedInformation, LABEL_MESSAGE_STRING + Label[0]);
      if (Count[0] == Disabling[0]) {
        Output(MessageCoded, LABEL_MESSAGE_STRING + string("This message will no longer appear on the log"));
      }
    }
  } else {
    Output(MessageCoded, LABEL_MESSAGE_STRING + IdP);
    Output(MessageCodedInformation, LABEL_MESSAGE_STRING + Label[0]);
  }
  if (!SkipAssertionP) {
    if (DevelopmentAssert[0]) {
      DevelopmentAssertion();
    }
    if (ImplementationAssert[0]) {
      ImplementationAssertion();
    }
    if (RuntimeAssert[0]) {
      RuntimeAssertion();
    }
  }
  return ReturnSuccess;
}

ReturnType LogManager::MessageFail()
{
  Output(MessageAllways, string(LABEL_FAIL));
}

ReturnType LogManager::MessageDone()
{
  Output(MessageAllways, string(LABEL_DONE));
}

ReturnType LogManager::OutputEmptyLine(MessageType LevelP)
{
  return Log.Output(LevelP, "");
}

ReturnType LogManager::OutputNproc(MessageType LevelP, string MessageP)
{
  ReturnCatch(Log.Output(LevelP, MessageP));
  return ReturnSuccess;
}

ReturnType LogManager::StartOutput(string FilenameP, RedirectionType RedirectionModeP)
{
  if (RedirectionModeP == RedirectionNew) {
    ofstream *NewFile = new ofstream;
    NewFile->open(FilenameP.c_str(), ofstream::out);
    Destination.push_back(NewFile);
  } else if (RedirectionModeP = RedirectionAppend) {
    ofstream *NewFile = new ofstream;
    NewFile->open(FilenameP.c_str(), ofstream::app);
    Destination.push_back(NewFile);
  } else {
    Log.Message("DV-025");
    return ReturnFail;
  }
  if (!Destination.back()->good()) {
    if (FilenameP.size() == 0) {
      FilenameP = "Standard Output";
    }
    Log.Message("RP-002: " + FilenameP);
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType LogManager::IncreaseOutputLevel()
{
  Destination.push_back(Destination.back());
  return ReturnSuccess;
}

ReturnType LogManager::DecreaseOutputLevel()
{
  Destination.pop_back();
  return ReturnSuccess;
}

ReturnType LogManager::StopOutput()
{
  if (Destination.size() > 0) {
    if (Destination.back()->good()) {
      if (Destination.back() != &cout) {
        (dynamic_cast<ofstream*> (Destination.back()))->close();
        delete Destination.back();
      }
      Destination.pop_back();
    } else {
      Log.Message("RP-001");
      return ReturnFail;
    }
  } else {
    Log.Message("DV-026");
    return ReturnFail;
  }
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Internals
////////////////////////////////////////////////////////////////////////////////////

ReturnType LogManager::Output(MessageType MessageTypeP, string OutputP, bool NewLine)
{
  if (NewLine) {
    OutputP = OutputP + "\n";
  }
  if (ToPrint(MessageTypeP) == ReturnSuccess) {
    OutputHere(MessageTypeP, OutputP, 0);
  }
  return ReturnSuccess;
}

ReturnType LogManager::OutputHere(MessageType MessageTypeP, string OutputP, int NprocNestingP)
{
  ReturnType FromOutputHere = ReturnNone;
  // Recursive Call
  if (NprocNestingP < Destination.size() - 1) {
    FromOutputHere = OutputHere(MessageTypeP, OutputP, NprocNestingP + 1);
  }
  if (FromOutputHere == ReturnNone) {
    if (!Destination[NprocNestingP]->good()) {
      Log.Message("RP-003");
      return ReturnFail;
    } else {
      int ThisStreamNesting = 0;
      for (int i = NprocNestingP; i >= 0; i--) {
        if (Destination[i] != Destination[NprocNestingP]) {
          ThisStreamNesting = i + 1;
          i = -1;
        }
      }
      for (int i = 0; i < NprocNestingP - ThisStreamNesting ; i++) {
        *(Destination[NprocNestingP]) << LABEL_INDENTATION_STRING;
      }
      *(Destination[NprocNestingP]) << OutputP;
      Destination[NprocNestingP]->flush();
    }
  }
  return ReturnSuccess;
}

ReturnType LogManager::ToPrint(MessageType MessageTypeP)
{
  switch (MessageTypeP) {
  case MessageCoded:
    if (!ShowMessageCoded) {
      return ReturnFail;
    }
    break;
  case MessageAllways:
    if (!ShowMessageAllways) {
      return ReturnFail;
    }
    break;
  case MessageInformation:
    if (!ShowMessageInformation) {
      return ReturnFail;
    }
    break;
  case MessageDevelopment:
    if (!ShowMessageDevelopment) {
      return ReturnFail;
    }
    break;
  case MessageCodedInformation:
    if (!ShowMessageCodedInformation) {
      return ReturnFail;
    }
    break;
  default:
    Log.Message("DV-027");
    return ReturnFail;
    break;
  }
  return ReturnSuccess;
}

template <class VariableType> ReturnType LogManager::GetInternalValue(string IdP, HashTable<VariableType> TableP, vector<VariableType> &ContentP, bool &FlagP)
{
  if (TableP.GetEntry(IdP, ContentP) == ReturnFail) {
    Output(MessageCoded, LABEL_MESSAGE_STRING + IdP);
    Output(MessageCoded, LABEL_MESSAGE_STRING + ReturnMessage);
    Output(MessageCoded, LABEL_MESSAGE_STRING + string("Coded message not found"));
    DevelopmentAssertion();
    ContentP.clear();
    FlagP = false;
    return ReturnFail;
  } else {
    FlagP = true;
    return ReturnSuccess;
  }
}
