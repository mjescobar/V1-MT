
#include "extern.h"
#include "LogManager.h"

LogManager::LogManager() :
MessagesLabel(LOG_MANAGER_HASH_SIZE),
MessagesText(LOG_MANAGER_HASH_SIZE),
MessagesDisabling(LOG_MANAGER_HASH_SIZE),
MessagesCount(LOG_MANAGER_HASH_SIZE),
MessagesDevelopmentAssert(LOG_MANAGER_HASH_SIZE),
MessagesRuntimeAssert(LOG_MANAGER_HASH_SIZE)
{
  ShowMessageInformation = DEFAULT_SHOW_MESSAGE_INFORMATION;
  ShowMessageCodedInformation = DEFAULT_SHOW_MESSAGE_CODED_INFORMATION;
  ShowMessageCoded = DEFAULT_SHOW_MESSAGE_CODED;
  ShowMessageDevelopment = DEFAULT_SHOW_MESSAGE_DEVELOPMENT;
  ShowMessageAllways = DEFAULT_SHOW_MESSAGE_ALLWAYS;
  Destination.push_back(&cout);
  Log.InitializeMessages();
}

LogManager::LogManager(const LogManager& orig)
{
  Log.CodedMessage("LM-100: LogManager copy constructor");
}

LogManager & LogManager::operator=(const LogManager & orig)
{
  Log.CodedMessage("LM-101: LogManager assignment operator");
  return *this;
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

ReturnType LogManager::MessageFail()
{
  Output(MessageAllways, string(LABEL_FAIL));
  return ReturnSuccess;
}

ReturnType LogManager::MessageDone()
{
  Output(MessageAllways, string(LABEL_DONE));
  return ReturnSuccess;
}

ReturnType LogManager::InitiateRedirection(string FilenameP, RedirectionType RedirectionModeP)
{
  if (RedirectionModeP == RedirectionNew) {
    ofstream *NewFile = new ofstream;
    NewFile->open(FilenameP.c_str(), ofstream::out);
    Destination.push_back(NewFile);
  } else if (RedirectionModeP == RedirectionAppend) {
    ofstream *NewFile = new ofstream;
    NewFile->open(FilenameP.c_str(), ofstream::app);
    Destination.push_back(NewFile);
  } else {
    return Return(ReturnFail, "LM-102");
  }
  if (!Destination.back()->good()) {
    if (FilenameP.size() == 0) {
      FilenameP = "Standard Output";
    }
    return Return(ReturnFail, "LM-103: " + FilenameP);
  }
  return ReturnSuccess;
}

ReturnType LogManager::TerminateRedirection()
{
  if (Destination.size() > 0) {
    if (Destination.back()->good()) {
      if (Destination.back() != &cout) {
        (dynamic_cast<ofstream*> (Destination.back()))->close();
        delete Destination.back();
      }
      Destination.pop_back();
    } else {
      return Return(ReturnFail, "LM-104");
    }
  } else {
    return Return(ReturnFail, "LM-105");
  }
  return ReturnSuccess;
}

ReturnType LogManager::IncreaseOutputLevel()
{
  //Lothar: error checking
  Destination.push_back(Destination.back());
  return ReturnSuccess;
}

ReturnType LogManager::DecreaseOutputLevel()
{
  //Lothar: error checking
  Destination.pop_back();
  return ReturnSuccess;
}

ReturnType LogManager::OutputHere(MessageType MessageTypeP, int MessageNestingP, string MessageP)
{
  //Lothar: delete output indentation
  ReturnType FromOutputHere = ReturnNone;
  if (MessageNestingP < Destination.size() - 1) {
    FromOutputHere = OutputHere(MessageTypeP, MessageNestingP + 1, MessageP);
  }
  if (FromOutputHere == ReturnNone) {
    if (!Destination[MessageNestingP]->good()) {
      return Return(ReturnFail, "LM-106");
    } else {
      int ThisStreamNesting = 0;
      for (int i = MessageNestingP; i >= 0; i--) {
        if (Destination[i] != Destination[MessageNestingP]) {
          ThisStreamNesting = i + 1;
          i = -1;
        }
      }
      for (int i = 0; i < MessageNestingP - ThisStreamNesting; i++) {
        *(Destination[MessageNestingP]) << LABEL_INDENTATION_STRING;
      }
      *(Destination[MessageNestingP]) << MessageP;
      Destination[MessageNestingP]->flush();
    }
  }
  return ReturnSuccess;
}

ReturnType LogManager::Output(MessageType MessageTypeP, string MessageP, bool NewLine)
{
  if (NewLine) {
    MessageP = MessageP + "\n";
  }
  if (ToPrint(MessageTypeP) == ReturnSuccess) {
    OutputHere(MessageTypeP, 0, MessageP);
  }
  return ReturnSuccess;
}

ReturnType LogManager::CodedMessage(string CodeP, bool SkipAssertionP)
{
  DataCheck(CodeP, "NonEmpty");
  bool LabelFound = false;
  bool CountFound = false;
  bool DisablingFound = false;
  bool RuntimeAssertFound = false;
  bool DevelopmentAssertFound = false;
  vector<int> Count;
  vector<string> Label;
  vector<int> Disabling;
  vector<bool> RuntimeAssert;
  vector<bool> DevelopmentAssert;
  string Code = CodeP.substr(0, 6);
  if (GetInternalValue(Code, MessagesCount, Count) == ReturnSuccess) {
    CountFound = true;
  }
  if (GetInternalValue(Code, MessagesLabel, Label) == ReturnSuccess) {
    LabelFound = true;
  }
  if (GetInternalValue(Code, MessagesDisabling, Disabling) == ReturnSuccess) {
    DisablingFound = true;
  }
  if (GetInternalValue(Code, MessagesRuntimeAssert, RuntimeAssert) == ReturnSuccess) {
    RuntimeAssertFound = true;
  }
  if (GetInternalValue(Code, MessagesDevelopmentAssert, DevelopmentAssert) == ReturnSuccess) {
    DevelopmentAssertFound = true;
  }
  if (!(DisablingFound && CountFound && DevelopmentAssertFound && RuntimeAssertFound && LabelFound)) {
    Output(MessageCoded, CodeP);
    Log.CodedMessage("LM-107");
  }
  if (Disabling[0]) {
    if (Count[0] < Disabling[0]) {
      Count[0]++;
      MessagesCount.PutEntry(Code, Count);
      Output(MessageCoded, LABEL_MESSAGE_STRING + CodeP);
      Output(MessageCodedInformation, LABEL_MESSAGE_STRING + Label[0]);
      if (Count[0] == Disabling[0]) {
        Output(MessageCoded, LABEL_MESSAGE_STRING + string("This message will no longer appear on the log"));
      }
    }
  } else {
    Output(MessageCoded, LABEL_MESSAGE_STRING + CodeP);
    Output(MessageCodedInformation, LABEL_MESSAGE_STRING + Label[0]);
  }
  if (!SkipAssertionP) {
    if (DevelopmentAssert[0]) {
      DevelopmentAssertion();
    }
    if (RuntimeAssert[0]) {
      RuntimeAssertion();
    }
  }
  return ReturnSuccess;
}

template <class VariableType> ReturnType LogManager::GetInternalValue(string CodeP, HashTable<VariableType> TableP, vector<VariableType> &ContentP)
{
  return TableP.GetEntry(CodeP, ContentP);
}

ReturnType LogManager::ToPrint(MessageType MessageTypeP)
{
  //Lothar: this should have a revision considering the latest changes on command line behavior
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
    return Return(ReturnFail, "DV-027");
    break;
  }
  return ReturnSuccess;
}
