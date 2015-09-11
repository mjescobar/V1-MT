
#ifndef LOGMANAGER_H
#define	LOGMANAGER_H

#include "HashTable.h"

class LogManager {
public:
  //Standard methods
  LogManager();
  LogManager(const LogManager& orig);
  virtual ~LogManager();
  LogManager & operator=(const LogManager & orig);
  //Basic messages
  ReturnType DisplayHeader();
  ReturnType DisplayFooter();
  ReturnType MessageFail();
  ReturnType MessageDone();
  //Redirections
  ReturnType InitiateRedirection(string FilenameP, RedirectionType RedirectionModeP);
  ReturnType TerminateRedirection();
  ReturnType IncreaseOutputLevel();
  ReturnType DecreaseOutputLevel();
  //Base output messages
  ReturnType OutputHere(MessageType MessageTypeP, int MessageNestingP, string MessageP);
  ReturnType Output(MessageType MessageTypeP, string MessageP, bool NewLine = true);
  //Coded messages
  ReturnType CodedMessage(string CodeP, bool SkipAssertionP = false);
private:
  // Methods
  ReturnType InitializeMessages();
  template <class VariableType> ReturnType GetInternalValue(string CodeP, HashTable<VariableType> TableP, vector<VariableType> &ContentP);
  ReturnType ToPrint(MessageType MessageTypeP);
  // Members
  vector<ostream*> Destination;
  HashTable<int> MessagesDisabling;
  HashTable<int> MessagesCount;
  bool ShowMessageInformation;
  bool ShowMessageCodedInformation;
  bool ShowMessageCoded;
  bool ShowMessageDevelopment;
  bool ShowMessageAllways;
  HashTable<bool> MessagesDevelopmentAssert;
  HashTable<bool> MessagesRuntimeAssert;
  HashTable<string> MessagesLabel;
  HashTable<string> MessagesText;
};

#endif
