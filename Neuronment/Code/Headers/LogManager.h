
#ifndef LOGMANAGER_H
#define	LOGMANAGER_H

#include "HashTable.h"

class LogManager {
public:
  /**
   * Emtpy constructor
   */
  LogManager();

  /**
   * Copy constructor
   * @param orig
   */
  LogManager(const LogManager& orig);

  /**
   * Destructor
   */
  virtual ~LogManager();

  /**
   * Assignment operator
   * @param orig
   * @return 
   */
  LogManager & operator=(const LogManager & orig);

  /**
   * Prints the Neuronment template header
   * @return 
   */
  ReturnType DisplayHeader();

  /**
   * Prints the Neuronment template footer
   * @return 
   */
  ReturnType DisplayFooter();

  /**
   * Prints the Fail label in a new line
   * @return 
   */
  ReturnType MessageFail();

  /**
   * Prints the Done label in a new line
   * @return 
   */
  ReturnType MessageDone();

  /**
   * Initiates an output redirection
   * @param FilenameP        File name for the redirection
   * @param RedirectionModeP RedirectionNew|RedirectionAppend
   * @return 
   */
  ReturnType InitiateRedirection(string FilenameP, RedirectionType RedirectionModeP);

  /**
   * Terminates the newest output redirection
   * @return 
   */
  ReturnType TerminateRedirection();

  /**
   * Adds a new redirection level with the same stream as the one currently used
   * @return 
   */
  ReturnType IncreaseOutputLevel();

  /**
   * Decreases the redirection level by one without closing the stream
   * @return 
   */
  ReturnType DecreaseOutputLevel();

  /**
   * Prints a message to the specific nesting level
   * @param MessageTypeP    Message type to print
   * @param MessageNestingP Leven of nesting in which the message should be printed
   * @param MessageP        The message to print
   * @return 
   */
  ReturnType OutputHere(MessageType MessageTypeP, int MessageNestingP, string MessageP);

  /**
   * Basic printing function
   * @param MessageTypeP Message type to print
   * @param MessageP     The message to print
   * @param NewLine      If the message should include a line termination at the end
   * @return 
   */
  ReturnType Output(MessageType MessageTypeP, string MessageP, bool NewLine = true);

  /**
   * Prints a coded message
   * The CodeP string 
   * @param CodeP          The string identifying the message. It accepts additional comments after the first 6 characters
   * @param SkipAssertionP If the message includes an assertion, this parameter allows to skip the assertion execution
   * @return 
   */
  ReturnType CodedMessage(string CodeP, bool SkipAssertionP = false);

private:
  /**
   * Initializes the list of avalable messages. Its implementation is found in LogManager.init.cpp
   * @return 
   */
  ReturnType InitializeMessages();

  /**
   * Checks if the indicated MessageType should or should not be printed
   * @param MessageTypeP
   * @return 
   */
  ReturnType ToPrint(MessageType MessageTypeP);

  /**
   * Retrieves the coded message stored information on a specific table
   * @param CodeP    The code message information to lookup
   * @param TableP   The table containing the information
   * @param ContentP The vector to return the content
   * @return 
   */
  template <class VariableType> ReturnType GetInternalValue(string CodeP, HashTable<VariableType> TableP, vector<VariableType> &ContentP);
  
  bool              ShowMessageInformation;
  bool              ShowMessageCodedInformation;
  bool              ShowMessageCoded;
  bool              ShowMessageDevelopment;
  bool              ShowMessageAllways;
  HashTable<int>    MessagesDisabling;
  HashTable<int>    MessagesCount;
  HashTable<bool>   MessagesDevelopmentAssert;
  HashTable<bool>   MessagesRuntimeAssert;
  vector<ostream*>  Destination;
  HashTable<string> MessagesLabel;
  HashTable<string> MessagesText;
} ;

#endif
