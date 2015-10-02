
#ifndef COMMANDMANAGER_H
#define	COMMANDMANAGER_H

#include <vector>
#include <string>
using namespace std;
#include "enum.h"
#include "HashTable.h"

class CommandLine {
public:
  //Standard methods
  CommandLine();
  CommandLine(const CommandLine& orig);
  virtual ~CommandLine();
  CommandLine & operator=(const CommandLine & orig); //Lothar: to implement
  //Special constructor
  CommandLine(int argcP, char** argvP);
  //Command line process methods
  ReturnType Restart();
  ReturnType Append(int argc, char** argv);
  ReturnType Append(string StringP);
  //Command line data methods
  ReturnType GetFlag(string FlagP);
  ReturnType GetFlag(string FlagP, string &ValueP);
  ReturnType GetCommand(string &CommandP);
  ReturnType GetCleanCommand(string &CleanCommandP, string Separator = " ");
  ReturnType GetRedirection(string &RedirectionP);
  ReturnType GetRedirectionType(RedirectionType &RedirectionModeP);
  //Command line information methods
  ReturnType IsReady(bool &ReadyP);
  ReturnType HasCommand(bool &HasCommandP);
  ReturnType HasComment(bool &HasCommentP);
  ReturnType HasRedirection(bool &HasRedirectionP);
private:
  //Methods
  ReturnType GetComment(string &CommentP);
  ReturnType GetFullLine(string &FullLine);
  ReturnType GetDirectives(vector<string> &DirectivesP);
  ReturnType ProcessFullCommand();
  ReturnType GetAllowedChars(vector<string> &AllowedChars);
  //Members
  bool Ready;
  string FullLine;
  string FullCommand;
  string Command;
  string Redirection;
  string Comment;
  RedirectionType RedirectionMode;
  vector<string> Directives;
  HashTable<string> *FlagValues;
};

#endif
