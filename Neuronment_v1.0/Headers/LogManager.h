/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef LOGMANAGER_H
#define	LOGMANAGER_H

#include "HashTable.h"

class LogManager {
public:
  LogManager();
  LogManager(const LogManager& orig);
  virtual ~LogManager();
  ReturnType DisplayHeader();
  ReturnType DisplayFooter();
  ReturnType Message(string IdP, bool SkipAssertionP = false);
  ReturnType MessageFail();
  ReturnType MessageDone();
  ReturnType StartOutput(string FilenameP, RedirectionType RedirectionModeP);
  ReturnType IncreaseOutputLevel();
  ReturnType DecreaseOutputLevel();
  ReturnType StopOutput();
  ReturnType OutputHere(MessageType MessageTypeP, string OutputP, int NprocNestingP);
  ReturnType Output(MessageType MessageTypeP, string OutputP, bool NewLine = true);
  ReturnType OutputEmptyLine(MessageType LevelP);
  ReturnType OutputNproc(MessageType LevelP, string MessageP);
  ReturnType ToPrint(MessageType MessageTypeP);
  /* 
      void DevelopmentMessage(string InfoP, string PrefixP = ">", string TerminationP = "\n");
      void UnsetMessages();
      void SetMessages();
      void SetFullSilentOutput();
      void UnsetFullSilentOutput();
   */
private:
  ReturnType InitializeMessages();
  template <class VariableType> ReturnType GetInternalValue(string IdP, HashTable<VariableType> TableP, vector<VariableType> &ContentP, bool &FlagP);
  vector<ostream*> Destination;
  HashTable<int> MessagesDisabling; //Maximum number of message apparitions
  HashTable<int> MessagesCount; //Counter of message apparitions
  bool ShowMessageInformation;
  bool ShowMessageCodedInformation;
  bool ShowMessageCoded;
  bool ShowMessageDevelopment;
  bool ShowMessageAllways;
  HashTable<bool> MessagesDevelopmentAssert; //Stores info if the message should Development Assert
  HashTable<bool> MessagesRuntimeAssert; //Stores info if the message should runtime assert
  HashTable<bool> MessagesImplementationAssert; //Stores info if the message should implementation assert
  HashTable<string> MessagesLabel; //Stores the short messages text
  HashTable<string> MessagesText; //Stores a message full text for man proposes
};

//template<> ReturnType LogManager::GetInternalValue<int>(string IdP, HashTable<int> TableP, vector<int> &ContentP, bool &FlagP);
//template<> ReturnType LogManager::GetInternalValue<double>(string IdP, HashTable<double> TableP, vector<double> &ContentP, bool &FlagP);
//template<> ReturnType LogManager::GetInternalValue<string>(string IdP, HashTable<string> TableP, vector<string> &ContentP, bool &FlagP);


#endif	/* LOGMANAGER_H */
