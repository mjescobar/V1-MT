
#include "LogManager.h"

/**
 * Loads the previously declared coded messages
 * @return 
 */
ReturnType LogManager::InitializeMessages()
{
  // IN-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-001", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-001", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-001", "NProc instruction not recognized"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-001", "The directive (first word on the nproc command) trying to get interpreted is not on the list of possible directives. Please go to the Reference Manual chapter \"Directives\" to get a full list of valid directives."));
  // IN-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-002", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-002", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-002", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-002", "Trying to get an undeclared variable"));
  // IN-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-003", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-003", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-003", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-003", "More than one destination file has been detected for redirection"));
  // IN-004
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-004", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-004", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-004", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-004", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-004", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-004", "Unidentified sub directive, ignoring line"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-004", "The sub-directive (second word on the nproc command)  trying to get interpreted is not on the list of possible directives. Please go to the Reference Manual chapter \"Directives\" to get a full list of valid directives."));
  // IN-005
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-005", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-005", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-005", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-005", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-005", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-005", "Unidentified setting, ignoring line"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-005", "A value has tried to be written on an un-identified or un-available configuration variable. This nproc line will be ommited."));
  // IN-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-006", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-006", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-006", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-006", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-006", "Flag not found"));
  // IN-007
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-007", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-007", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-007", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-007", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-007", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-007", "A boolean argument has not been properly written. Will be interpreted as false"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-007", "A string been read as boolean does not match any of the possible true values (true, True, T, t, 1) neither false (false, False, F, f, 0). It will be interpreted and stored as false."));
  // IN-008
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-008", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-008", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-008", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-008", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-008", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-008", "The maximum amount of possible nested \"rescue nproc\" calls has been reached"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-008", "Each time a \"rescue nproc\" instruction is called, the execution of this new nproc file increases in 1 the nesting level of execution. This message appears when the nesting level has reached the maximum allowed."));
  // IN-009
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-009", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-009", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-009", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-009", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-009", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-009", "Trying to redirect an empty command"));
  // IN-010
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-010", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-010", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-010", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-010", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-010", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-010", "Incorrect amount of arguments for the command, ignoring line"));
  ReturnCatch(MessagesText.PutEntryQuick("IN-010", "The number of arguments of the command does not match the minimum required. This line will be ignored."));
  // IN-011
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-011", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-011", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-011", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-011", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-011", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-011", "Character not allowed for command detected"));
  // IN-012
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-012", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-012", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-012", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-012", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-012", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-012", "Value without flag. If you are trying to set a list do not forget the curly braces"));
  // IN-013
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-013", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-013", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-013", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-013", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-013", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-013", "The list curly braces delimeter should be isolated by spaces"));
  // IN-014
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-014", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-014", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-014", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-014", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-014", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-014", "A dash must be continuated (without spaces in the middle) by a string when used for a flag"));
  // IN-015
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-015", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-015", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-015", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-015", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-015", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-015", "Command list not closed"));
  // IN-016
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-016", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-016", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-016", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-016", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-016", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-016", "Nproc file opened correctly"));
  // IN-017
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-017", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-017", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-017", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-017", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-017", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-017", "Nproc file closed correctly"));
  // IN-018
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-018", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-018", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-018", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-018", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-018", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-018", "Nproc file finished processing without completing the last command reading"));
  // IN-019
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-019", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-019", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-019", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-019", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-019", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-019", "Nothing to redirect"));
  // IN-020
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-020", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-020", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-020", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-020", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-020", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-020", "Redirection without a command to redirect"));
  // IN-021
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-021", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-021", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-021", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-021", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-021", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-021", "Redirection does not specify a destination file"));
  // IN-022
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-022", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-022", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-022", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-022", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-022", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-022", "Nested lists are not allowed"));
  // IN-023
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-023", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-023", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-023", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-023", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-023", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-023", "A line continuation character must be preceded by a space"));
  // IN-024
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-024", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-024", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-024", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-024", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-024", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-024", "Simulator ID out of bounds"));
  // IN-025
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("IN-025", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("IN-025", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("IN-025", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("IN-025", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("IN-025", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("IN-025", "Incorrect parameter list"));
  // Command Line Issues
  // UI-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("UI-001", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("UI-001", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("UI-001", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("UI-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("UI-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("UI-001", "Duplicated or contradictory flags on command call"));
  ReturnCatch(MessagesText.PutEntryQuick("UI-001", "The Neuronment command-line call has a flag declared more than once or two flags that are different are trying to set a contradictory behaivior."));
  // UI-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("UI-002", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("UI-002", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("UI-002", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("UI-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("UI-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("UI-002", "Flag expected"));
  ReturnCatch(MessagesText.PutEntryQuick("UI-002", "The Neuronment command-line call holds a value in a place where should be a flag (a tring starting with \"-\")."));
  // UI-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("UI-003", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("UI-003", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("UI-003", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("UI-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("UI-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("UI-003", "Flag not recognized, flag omitted"));
  ReturnCatch(MessagesText.PutEntryQuick("UI-003", "The Neuronment command-line call has detected a flag that is not on the list of possible flags. This flag will be ignored."));
  // UI-004
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("UI-004", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("UI-004", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("UI-004", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("UI-004", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("UI-004", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("UI-004", "Label without content"));
  ReturnCatch(MessagesText.PutEntryQuick("UI-004", "The Neuronment command-line call has a flag that requires a value, but the value has not been found. If you are trying to use a negative number put it between quotes."));
  // UI-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("UI-006", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("UI-006", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("UI-006", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("UI-006", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("UI-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("UI-006", "Empty Nproc file list"));
  // File IO Issues
  // ER-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-001", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-001", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-001", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-001", "Development assertion"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-001", "The program arrived to an unexpected set of conditions."));
  // ER-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-002", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-002", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-002", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-002", "Runtime Assertion"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-002", "Something went wrong running the program. Terminating."));
  // ER-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-003", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-003", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-003", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-003", "File could not be opened"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-003", "The nproc required for execution file could not be oppened."));
  // ER-004
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-004", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-004", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-004", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-004", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-004", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-004", "File could not be properly closed"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-004", "The nproc file previously executed did notreturned a propper closed status from the OS when trying to close the file."));
  // ER-005
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-005", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-005", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-005", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-005", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-005", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-005", "Trying to get a new line from a non ready file"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-005", "This happens when for some reason the interpreter is trying to get a new line from a file that has not been properly oppened."));
  // ER-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-006", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-006", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-006", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-006", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-006", "Trying to get a new line from a file already at the end"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-006", "This happens when for some reason the interpreter is trying to get a new line from a file already at the EOF."));
  // ER-007
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-007", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-007", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-007", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-007", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-007", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-007", "Fail on getting a new line from nproc file"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-007", "This happens when for some reason the file stream under interpretation is not able to retreive a new line from the nproc file, even if it is not at the EOF."));
  // ER-008
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-008", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-008", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-008", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-008", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-008", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-008", "Implementation Assertion"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-008", "There is a problem or an incompete implementation of a required feature."));
  // ER-009
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-009", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-009", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-009", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-009", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-009", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-009", "Trying to close an unopened file"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-009", "The interpreter is trying to close a file that has not been oppened."));
  // ER-010
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-010", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-010", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-010", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-010", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-010", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-010", "Required file is empty"));
  ReturnCatch(MessagesText.PutEntryQuick("ER-010", "The interpreter requires a file for execution. In this case the file name is empty."));
  // ER-011
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("ER-011", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("ER-011", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("ER-011", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("ER-011", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("ER-011", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("ER-011", "Development assertion skipped in full running mode"));
  // Implementation Issues
  // DV-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-001", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-001", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-001", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-001", "Missing implementation"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-001", "The build in use has identified a procedure wich has not been implemented."));
  // DV-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-002", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-002", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-002", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-002", "Trying to set a variable that already exist with another data type"));
  // DV-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-003", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-003", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-003", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-003", "Trying to load a setting of an unsupported type"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-003", "Neuronment has many internal data types but only a few of them are intended for data handling. In this case, a data type not intended for data handling is trying to be used for data handling."));
  // DV-004
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-004", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-004", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-004", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-004", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-004", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-004", "The Activation dimentions weren't created correctly"));
  // DV-005
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-005", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-005", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-005", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-005", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-005", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-005", "Trying to use an unsupported setting"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-005", "Neuronment is trying to get an information parameter from a variable that does not exists or have not been declared jet."));
  // DV-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-006", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-006", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-006", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-006", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-006", "Trying to read an incorrect data type for the setting"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-006", "In Neuronment the variables have a specific type of value declared at their declaration. In this case, the variable value is trying to be used as a diferent type of the one declared."));
  // DV-007
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-007", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-007", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-007", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-007", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-007", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-007", "The setting count is different than the declared setting count on the HashEntry"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-007", "When retrieving a variable list of values, the number of values retrieved is different from the number of values that where declared at the variable configuration."));
  // DV-008
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-008", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-008", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-008", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-008", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-008", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-008", "Copying an instance that never should be copied"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-008", "The Neuronment sequencer as instance is trying to be copied to another instance. This is not suppose to happen as a sequencer should never be copied."));
  // DV-009
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-009", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-009", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-009", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-009", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-009", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-009", "A variable validation has not been processed correctly"));
  // DV-010
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-010", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-010", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-010", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-010", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-010", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-010", "Trying to set an activation function for an activation level that doesn't exists"));
  // DV-011
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-011", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-011", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-011", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-011", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-011", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-011", "Trying to set an invalid list of calculation order vector"));
  // DV-012
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-012", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-012", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-012", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-012", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-012", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-012", "Trying a quick access of incorrect type"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-012", "When trying to quick retrieve a value from a single element value list, the function in use is triying to retrieve a value from a a variable of different type that the one that is supose to retrieve."));
  // DV-013
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-013", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-013", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-013", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-013", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-013", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-013", "A variable name is dulicated on different data types"));
  // DV-014
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-014", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-014", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-014", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-014", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-014", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-014", "The calculation list is not properly formatted"));
  // DV-015
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-015", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-015", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-015", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-015", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-015", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-015", "Setting declared but has not been initialized"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-015", "The variable has been declared but it does not have any value stored. This is unexpected as at the variable declaration a default value should have been declared and stored."));
  // DV-016
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-016", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-016", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-016", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-016", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-016", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-016", "External excitation not propperly formated"));
  // DV-017
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-017", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-017", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-017", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-017", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-017", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-017", "Discrepancy on neuron type on assignment"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-017", "A instance of a neuron of certain type is trying to be copied on an instance of a neuron of another incompatible type."));
  // DV-018
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-018", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-018", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-018", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-018", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-018", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-018", "Trying to get an external excitation out of bounds"));
  // DV-018
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-018", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-018", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-018", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-018", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-018", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-018", "Trying to quick retrieve un-existent value"));
  ReturnCatch(MessagesText.PutEntryQuick("DV-018", "When trying to quick retrieve a value from a single element value list, the function in use is triying to retrieve a value from a a variable that does not stores any value. This is unexpected as it should have stored a default value at the variable declaration."));
  // DV-019
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-019", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-019", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-019", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-019", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-019", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-019", "ReturnCatch has a non procecced catching expression"));
  // DV-020
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-020", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-020", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-020", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-020", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-020", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-020", "ReturnCatch has found a warning"));
  // DV-021
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-021", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-021", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-021", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-021", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-021", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-021", "ReturnCatch has detected a failure"));
  // DV-022
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-022", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-022", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-022", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-022", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-022", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-022", "DataCheck has a non processed chacking expression"));
  // DV-023
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-023", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-023", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-023", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-023", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-023", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-023", "Not possible to retrieve all the required values for coded message"));
  // DV-024
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-024", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-024", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-024", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-024", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-024", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-024", "Trying to get status from a non ready command"));
  // DV-025
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-025", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-025", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-025", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-025", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-025", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-025", "No calid redirection mode declared at redirection time"));
  // DV-026
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-026", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-026", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-026", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-026", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-026", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-026", "Trying to close a redirection at 0 redirection level"));
  // DV-027
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-027", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-027", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-027", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-027", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-027", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-027", "Not recognized message type"));
  // DV-028
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-028", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-028", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-028", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-028", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-028", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-028", "Invalid NprocNesting reached"));
  // DV-029
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-029", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-029", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-029", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-029", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-029", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-029", "cout redirection not of type RedirectionNone"));
  // SD-030
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-030", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-030", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-030", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-030", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-030", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-030", "Internal simulation pointer corruption"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-030", "The simulator is trying to start the claculation of a new step but the counter of steps for the calculations for the activation and the derivate of activation are different. This means that there is an uncomplete calculation from the previous step."));
  // SD-031
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-031", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-031", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-031", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-031", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-031", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-031", "Trying to compare 2 identical neurons"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-031", "When comparing 2 different instances of a neuron of a same type, there is no difference in the instance attributes that allows to identify each one unequivocaly. This is unexpected as at minimum 2 different instances of a neuron should have al least a different name."));
  // SD-032
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-032", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-032", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-032", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-032", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-032", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-032", "Empty pointer to function entry"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-032", "The interpreter has identified a directive that has not a valid function to execute."));
  // DV-033
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-033", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-033", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-033", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-033", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-033", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-033", "Trying to use an unsupported data type"));
  // DV-034
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-034", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-034", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-034", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-034", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-034", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-034", "Neuron type not found"));
  // DV-035
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-035", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-035", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-035", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-035", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-035", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-035", "The neuron type activation levels require a different amount of base activation values"));
  // DV-036
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-036", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-036", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-036", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-036", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-036", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-036", "The neuron type is of different type than the data structur that uses it"));
  // DV-037
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-037", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-037", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-037", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-037", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-037", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-037", "Neuron data type not supported"));
  // DV-038
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-038", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-038", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-038", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-038", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-038", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-038", "Not valid current simulator pointer"));
  // DV-039
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-039", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-039", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-039", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-039", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-039", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-039", "Fast input list size isn't compatible with the declared fast input list for the neuron type"));
  // DV-040
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("DV-040", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("DV-040", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("DV-040", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("DV-040", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("DV-040", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("DV-040", "add_neuron doesn't find all the required parameters"));
  // Reporting Issues
  // RP-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("RP-001", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("RP-001", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("RP-001", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("RP-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("RP-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("RP-001", "Trying to close a not good stream"));
  ReturnCatch(MessagesText.PutEntryQuick("RP-001", "The interpreter is trying to close a redirection file that has not been oppened."));
  // RP-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("RP-002", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("RP-002", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("RP-002", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("RP-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("RP-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("RP-002", "Problem obtaining the output stream"));
  ReturnCatch(MessagesText.PutEntryQuick("RP-002", "When trying to open a file for redirection the OS failed to give a successful operation result."));
  // RP-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("RP-003", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("RP-003", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("RP-003", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("RP-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("RP-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("RP-003", "Trying to use a not good stream for output"));
  // Simulator Interface Issues
  // SD-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-001", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-001", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-001", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-001", "Simple Simulator Not Initialized"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-001", "Trying to start a simulation on a simulator that has not been build."));
  // SD-002
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-002", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-002", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-002", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-002", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-002", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-002", "Trying to set a neuron attribute that doesn't exists"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-002", "When defining an attribute for a neuron, the label indicated is not on the list of possible attributes. To avoid this error try adding the attribute to the list of possible attributes first."));
  // SD-003
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-003", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-003", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-003", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-003", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-003", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-003", "DataCheck for string requieres a string \"Non Empty\""));
  // SD-004
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-004", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-004", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-004", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-004", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-004", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-004", "Int doesn't comply with the input conditions"));
  // SD-005
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-005", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-005", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-005", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-005", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-005", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-005", "Setting activation levels on a neuron that already has sctivation levels set. All information will be deleted."));
  // SD-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-006", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-006", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-006", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-006", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-006", "Neuron attribute label not found"));
  // SD-007
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-007", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-007", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-007", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-007", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-007", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-007", "Problem calculating next activation"));
  // SD-008
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-008", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-008", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-008", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-008", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-008", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-008", "DataCheck for int requires an int \"Greater Than Zero\""));
  // SD-009
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-009", true));
 // ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-009", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-009", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-009", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-009", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-009", "DataCheck for int requires an int \"Non Negative\""));
  // SD-010
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-010", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-010", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-010", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-010", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-010", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-010", "DataCheck for char** requires a \"Not NULL\" pointer"));
  // SD-011
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-011", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-011", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-011", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-011", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-011", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-011", "The system command line has been interpreted as an empty string for processing"));
  // SD-015
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-015", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-015", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-015", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-015", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-015", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-015", "No V1_Neuron created"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-015", "There are not V1 neurons declared and no neuron has been build for the simulation. The simulator requires at least one V1 neuron to work."));
  // SD-016
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-016", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-016", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-016", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-016", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-016", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-016", "No MT_Neuron created"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-016", "There are not MT neurons declared and no neuron has been build for the simulation. The simulator requires at least one MT neuron to work."));
  // SD-017
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-017", true));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-017", true));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-017", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-017", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-017", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-017", "External Excitation has not been set"));
  // SD-021
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-021", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-021", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-021", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-021", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-021", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-021", "Invalid timing for eternal excitation"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-021", "The simulator is trying to access a negative time step. All time steps have a equal or greater than zero value."));
  // SD-025
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-025", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-025", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-025", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-025", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-025", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-025", "Unordered external excitation phase insertion attempt"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-025", "When declaring the external exitations, the fases should be declared in consecutive order. In this case there seems to be a gap at the moment of declaring the different phases."));
  // SD-027
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-027", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-027", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-027", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-027", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-027", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-027", "First diffusion phase should be always zero"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-027", "When declaring the external exitations, the fases should be declared in consecutive order. The first phase should be declared as phase 0."));
  // SD-028
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-028", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-028", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-028", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-028", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-028", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-028", "The number of steps for simulate needs to be at least 1"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-028", "The miminum number of steps to calculate a simulation is 1. In this case, the value configured for this number of steps is zero or negative."));
  // SD-033
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-033", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-033", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-033", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-033", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-033", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-033", "Trying to access an invalid activation TimeStep"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-033", "Each time step has a index number from zero up to the number of steps simulated minus one. In this case, there is an attempt to access a timestep outside this range."));
  // SD-036
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-036", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-036", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-036", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-036", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-036", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-036", "Setting not recognized"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-036", "This happens when a user or default configured setting has a value that cannot be used for simulation."));
  // SD-037
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("SD-037", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("SD-037", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("SD-037", true));
  ReturnCatch(MessagesDisabling.PutEntryQuick("SD-037", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("SD-037", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("SD-037", "Setting required"));
  ReturnCatch(MessagesText.PutEntryQuick("SD-037", "When trying to retrieve a variable value, the variable does not exists."));
  // Warnings
  // WN-001
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("WN-001", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("WN-001", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("WN-001", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("WN-001", 0));
  ReturnCatch(MessagesCount.PutEntryQuick("WN-001", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("WN-001", "Early nproc termination reached"));
  // WN-006
  ReturnCatch(MessagesDevelopmentAssert.PutEntryQuick("WN-006", false));
  //ReturnCatch(MessagesImplementationAssert.PutEntryQuick("WN-006", false));
  ReturnCatch(MessagesRuntimeAssert.PutEntryQuick("WN-006", false));
  ReturnCatch(MessagesDisabling.PutEntryQuick("WN-006", 1));
  ReturnCatch(MessagesCount.PutEntryQuick("WN-006", 0));
  ReturnCatch(MessagesLabel.PutEntryQuick("WN-006", "There are undocumented calculations in use"));
  ReturnCatch(MessagesText.PutEntryQuick("WN-006", "The simulator is calculating using mathematical functions that does not have documented references."));
  return ReturnSuccess;
}
