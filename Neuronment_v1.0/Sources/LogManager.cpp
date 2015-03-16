/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/basic_string.h>
using namespace std;
#include "enum.h"
#include "define.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "Globals.h"

void LogManager::SetSilentOutput()
{
  SilentOutput = true;
}

void LogManager::UnsetSilentOutput()
{
  SilentOutput = false;
}

void LogManager::SetMessages()
{
  Messages = true;
}

void LogManager::UnsetMessages()
{
  Messages = false;
}

LogManager::LogManager()
{
  Messages = DEFAULT_MESSAGES;
  SilentOutput = DEFAULT_SILENT_OUTPUT;
  MessagesLabel = HashTable(Data_string);
  MessagesText = HashTable(Data_string);
  MessagesDisabling = HashTable(Data_int);
  MessagesCount = HashTable(Data_int);
  MessagesDevelopmentAssert = HashTable(Data_bool);
  MessagesRuntimeAssert = HashTable(Data_bool);
  MessagesImplementationAssert = HashTable(Data_bool);
}

LogManager::LogManager(const LogManager& orig)
{
  Messages = orig.Messages;
  SilentOutput = orig.SilentOutput;
}

LogManager::~LogManager()
{
}

void LogManager::DisplayHelp()
{
  Output(Message_Allways, "Displaying basic program help");
}

void LogManager::DisplayHeader()
{
  Output(Message_Allways, "====================================================================================");
  Output(Message_Allways, "========================== Neuronment v0.3 - " __DATE__ " ===========================");
  Output(Message_Allways, "====================================================================================");
  Output(Message_Allways, "");
}

void LogManager::DisplayFooter()
{
  Output(Message_Allways, "");
  Output(Message_Allways, "====================================================================================");
  Output(Message_Allways, " Bye!");
}

void LogManager::DevelopmentMessage(string InfoP, string PrefixP, string TerminationP)
{
  OutputNNL(Message_Dev, PrefixP + InfoP + TerminationP);
}

void LogManager::Output(MessageType MessageTypeP, string OutputP)
{
  OutputNNL(MessageTypeP, OutputP + "\n");
}

void LogManager::OutputNNL(MessageType MessageTypeP, string OutputP)
{
  if (Redirection001.is_open()) {
    Redirection001 << OutputP;
    Redirection001.flush();
  } else {
    if (!SilentOutput) {
      cout << OutputP;
      cout.flush();
    }
  }
  if (SilentOutput && MessageTypeP == Message_Coded) {
    cout << ">" << OutputP;
    cout.flush();
  }
}

void LogManager::Message(string IdP)
{
  string Label = IdP.substr(0, 6);
  bool ToPrint = false;
  bool ToDisable = false;
  if (!MessagesCount.GetEntry(Label)) {
    Output(Message_Coded, IdP);
    Output(Message_Coded, "Message not registered");
    DevelopmentAssertion();
  } else {
    if (!MessagesDisabling.GetEntry(Label)) {
      Output(Message_Coded, IdP);
      Output(Message_Coded, "Message without apparition count");
      DevelopmentAssertion();
    } else {
      if (MessagesDisabling.QuickGetEntry_int(Label) > 0) {
        if (MessagesDisabling.QuickGetEntry_int(Label) > MessagesCount.QuickGetEntry_int(Label)) {
          ToPrint = true;
          MessagesCount.QuickUpdateEntry_int(Label, MessagesCount.QuickGetEntry_int(Label) + 1);
          if (MessagesDisabling.QuickGetEntry_int(Label) >= MessagesCount.QuickGetEntry_int(Label)) {
            ToDisable = true;
          }
        } else {
          ToPrint = false;
        }
      } else {
        ToPrint = true;
      }
    }
  }
  if (ToPrint) {
    bool ToRuntimeAssert = MessagesRuntimeAssert.QuickGetEntry_bool(Label);
    bool ToImplementationAssert = MessagesImplementationAssert.QuickGetEntry_bool(Label);
    bool ToDevelopmentAssert = MessagesDevelopmentAssert.QuickGetEntry_bool(Label);
    string Message = MessagesLabel.QuickGetEntry_string(Label);
    if (ToImplementationAssert || ToRuntimeAssert) {
      UnsetSilentOutput();
    } else {
#ifdef DEVELOPMENT
      if (ToDevelopmentAssert) {
        UnsetSilentOutput();
      }
#endif
    }
    Output(Message_Coded, "> " + IdP);
    Output(Message_Coded, "> " + Message);
    if (ToDisable) {
      Output(Message_Coded, "> This message will no longer appear on the log");
    }
    if (ToDevelopmentAssert) {
      DevelopmentAssertion();
    }
    if (ToImplementationAssert) {
      ImplementationAssertion();
    }
    if (ToRuntimeAssert) {
      RuntimeAssertion();
    }
  }
}

void LogManager::StartOutputRedirection001(string DestinationP)
{
  if (!Redirection001.is_open()) {
    Redirection001.open(DestinationP.c_str(), ofstream::out);
    if (!Redirection001.is_open()) {
      Log.Message("RP-003: " + DestinationP);
    }
  } else {
    Log.Message("RP-001: " + DestinationP);
  }
}

void LogManager::StopOutputRedirection001()
{
  if (Redirection001.is_open()) {
    Redirection001.close();
  } else {
    Log.Message("RP-002");
  }
}