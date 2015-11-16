
#ifndef COMMANDMANAGER_H
#define	COMMANDMANAGER_H

#include <vector>
#include <string>
using namespace std;
#include "enum.h"
#include "HashTable.h"

class CommandLine {
public:
  /**
   * Empty constructor
   * Initializes the hash table with COMMAND_MANAGER_HASH_SIZE slots
   */
  CommandLine();

  /**
   * Copy constructor
   * @param orig
   */
  CommandLine(const CommandLine& orig);

  /**
   * Destructor
   */
  virtual ~CommandLine();

  /**
   * Assignment operator
   * @param orig
   * @return 
   */
  CommandLine & operator=(const CommandLine & orig);

  /**
   * Command line constructor
   * Constructs a CommandLine instance starting from the main arguments
   * @param argcP The argc main argument
   * @param argvP The argv main argument
   */
  CommandLine(int argcP, char** argvP);

  /**
   * Prepares the instance to process a new set of strings
   * @return 
   */
  ReturnType Restart();

  /**
   * Appends the string to the command to process
   * @param  StringP String to add
   * @return 
   */
  ReturnType Append(string StringP);

  /**
   * Returns ReturnSuccess if a flag indicated by FlagP exists
   * @param FlagP The flag to check
   * @return 
   */
  ReturnType GetFlag(string FlagP);

  /**
   * Returns the value stored on the indicated flag
   * @param FlagP  The flag to retrieve the value
   * @param ValueP The pointer where the value will be stored
   * @return 
   */
  ReturnType GetFlag(string FlagP, string &ValueP);

  /**
   * Returns the full command formed after appends including redirections
   * @param CommandP The pointer to store the command
   * @return 
   */
  ReturnType GetCommand(string &CommandP);

  /**
   * Returns a string formed by the directive or the directive and subdirective
   * separated by a Separator string
   * @param CleanCommandP The pointer to return the value
   * @param Separator     The string to separate the directive and subdirective
   * @return 
   */
  ReturnType GetCleanCommand(string &CleanCommandP, string Separator = " ");

  /**
   * Returns the redirection file indicated on the command
   * @param RedirectionP The pointer to return the file name
   * @return 
   */
  ReturnType GetRedirection(string &RedirectionP);

  /**
   * Retrieves the redirection type it if exists
   * @param RedirectionModeP
   * @return 
   */
  ReturnType GetRedirectionType(RedirectionType &RedirectionModeP);

  /**
   * Indicates if the command is ready for analysis
   * @param ReadyP The pointer to return the status
   * @return
   */
  ReturnType IsReady(bool &ReadyP);

  /**
   * Indicates if the command line has a command
   * @param HasCommandP The pointer to return the value
   * @return
   */
  ReturnType HasCommand(bool &HasCommandP);

  /**
   * Indicates if the command line has a comment
   * @param HasCommentP The pointer to return the value
   * @return
   */
  ReturnType HasComment(bool &HasCommentP);

  /**
   * Indicates if the command has a redirection
   * @param HasRedirectionP The pointer to return the value
   * @return
   */
  ReturnType HasRedirection(bool &HasRedirectionP);

private:

  /**
   * Appends the first argc elements from argv to the command to process
   * @param argcP The amount of elements to add
   * @param argvP The array containing the elements to add
   * @return
   */
  ReturnType Append(int argcP, char** argvP);

  /**
   * Returns the comment stored on the instance
   * @param CommentP The pointer to return the value
   * @return
   */
  ReturnType GetComment(string &CommentP);

  /**
   * Return the full line stored on the instance
   * @param FullLine The pointer to return the value
   * @return
   */
  ReturnType GetFullLine(string &FullLine);

  /**
   * Returns a vector containing all the allowed characters on a string
   * @param AllowedChars Pointer to return the list
   * @return
   */
  ReturnType GetAllowedChars(vector<string> &AllowedChars);

  /**
   * Processes the command string and sets the ready status
   * @return
   */
  ReturnType ProcessFullCommand();

  bool               Ready;
  string             FullLine;
  string             FullCommand;
  string             Command;
  string             Redirection;
  string             Comment;
  RedirectionType    RedirectionMode;
  vector<string>     Directives;
  HashTable<string> *FlagValues;
} ;

#endif
