/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef COMMANDMANAGER_H
#define	COMMANDMANAGER_H

#include <vector>
#include <string>
using namespace std;
#include <enum.h>
#include <HashTable.h>

class CommandManager {
public:
  CommandManager();
  CommandManager(const CommandManager& orig);
  CommandManager(int argcP, char** argvP);
  virtual ~CommandManager();
  ReturnType Append(int argc, char** argv);
  ReturnType Append(string StringP);
  ReturnType IsReady(bool &ReadyP);
  ReturnType GetFlag(string FlagP, string &ValueP);
  ReturnType GetDirectives(vector<string> &DirectivesP);
  ReturnType GetCleanCommand(string &CleanCommandP, string Separator = " ");
  ReturnType GetComment(string &CommentP);
  ReturnType GetCommand(string &CommandP);
  ReturnType GetRedirection(string &RedirectionP);
  ReturnType GetRedirectionType(RedirectionType &RedirectionModeP);
  ReturnType GetFullLine(string &FullLine);
  ReturnType HasCommand(bool &HasCommandP);
  ReturnType HasComment(bool &HasCommentP);
  ReturnType HasRedirection(bool &HasRedirectionP);
  ReturnType Restart();
private:
  ReturnType ProcessFullCommand();
  ReturnType GetAllowedChars(vector<string> &AllowedChars);
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

#endif	/* COMMANDMANAGER_H */

