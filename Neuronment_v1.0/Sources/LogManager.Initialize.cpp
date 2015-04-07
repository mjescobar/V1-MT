/*
 * @author Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 * Generated by ConsolidatedDocumentation v1.0.xlsm
 * TimeStamp: 2015-04-07 12:04:59
 */

//#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//#include <bits/basic_string.h>
using namespace std;
#include "enum.h"
#include "define.h"
//#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
//#include "SettingsManager.h"
//#include "Globals.h"

void LogManager::InitializeMessages()
{
  // Reading Nproc File Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-001", true);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-001", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-001", false);
  MessagesDisabling.QuickPutEntry_int("IN-001", 0);
  MessagesCount.QuickPutEntry_int("IN-001", 0);
  MessagesLabel.QuickPutEntry_string("IN-001","NProc directive not recognized");
  MessagesText.QuickPutEntry_string("IN-001", "The directive (first word on the nproc command) trying to get interpreted is not on the list of possible directives. Please go to the Reference Manual chapter \"Directives\" to get a full list of valid directives.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-002", true);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-002", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-002", false);
  MessagesDisabling.QuickPutEntry_int("IN-002", 0);
  MessagesCount.QuickPutEntry_int("IN-002", 0);
  MessagesLabel.QuickPutEntry_string("IN-002","Trying to report an undeclared variable");
  MessagesText.QuickPutEntry_string("IN-002", "The Simulator as well as the Simulation Environment has a list of predefined variables so store and retrieve information. The variable been addressed is not part of the list. The user is not allowed to create new variables.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-004", true);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-004", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-004", false);
  MessagesDisabling.QuickPutEntry_int("IN-004", 0);
  MessagesCount.QuickPutEntry_int("IN-004", 0);
  MessagesLabel.QuickPutEntry_string("IN-004","Unidentified sub directive, ignoring line");
  MessagesText.QuickPutEntry_string("IN-004", "The sub-directive (second word on the nproc command)  trying to get interpreted is not on the list of possible directives. Please go to the Reference Manual chapter \"Directives\" to get a full list of valid directives.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-005", false);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-005", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-005", false);
  MessagesDisabling.QuickPutEntry_int("IN-005", 0);
  MessagesCount.QuickPutEntry_int("IN-005", 0);
  MessagesLabel.QuickPutEntry_string("IN-005","Unidentified setting, ignoring line");
  MessagesText.QuickPutEntry_string("IN-005", "A value has tried to be written on an un-identified or un-available configuration variable. This nproc line will be ommited");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-006", false);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-006", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-006", false);
  MessagesDisabling.QuickPutEntry_int("IN-006", 0);
  MessagesCount.QuickPutEntry_int("IN-006", 0);
  MessagesLabel.QuickPutEntry_string("IN-006","Flag not found or without a value");
  MessagesText.QuickPutEntry_string("IN-006", "The command on execution requires the definition of a flag (a word that starts with \"-\" in the arguments) that isn't present or without a value (if a flag requires a value, the next word after it should be the string representing the value for the flag. This string must NOT start with a \"-\". If the value is a negative number put it between quotes).");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-007", false);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-007", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-007", false);
  MessagesDisabling.QuickPutEntry_int("IN-007", 0);
  MessagesCount.QuickPutEntry_int("IN-007", 0);
  MessagesLabel.QuickPutEntry_string("IN-007","A boolean argument has not been properly written. Will be interpreted as false");
  MessagesText.QuickPutEntry_string("IN-007", "A string been read as boolean doen't match any of the possible true values (true, True, T, t, 1) neither false (false, False, F, f, 0). It will be interpreted and stored as false.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-008", false);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-008", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-008", true);
  MessagesDisabling.QuickPutEntry_int("IN-008", 0);
  MessagesCount.QuickPutEntry_int("IN-008", 0);
  MessagesLabel.QuickPutEntry_string("IN-008","The maximum amount of possible nested \"rescue nproc\" calls has been reached");
  MessagesDevelopmentAssert.QuickPutEntry_bool("IN-010", false);
  MessagesImplementationAssert.QuickPutEntry_bool("IN-010", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("IN-010", false);
  MessagesDisabling.QuickPutEntry_int("IN-010", 0);
  MessagesCount.QuickPutEntry_int("IN-010", 0);
  MessagesLabel.QuickPutEntry_string("IN-010","Incorrect amount of arguments for the command, ignoring line");
  MessagesText.QuickPutEntry_string("IN-010", "The number of arguments of the command doesn't match the minimum required. This line will be ignored.");
  // Command Line Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("UI-001", false);
  MessagesImplementationAssert.QuickPutEntry_bool("UI-001", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("UI-001", true);
  MessagesDisabling.QuickPutEntry_int("UI-001", 0);
  MessagesCount.QuickPutEntry_int("UI-001", 0);
  MessagesLabel.QuickPutEntry_string("UI-001","Duplicated or contradictory flags on command call");
  MessagesText.QuickPutEntry_string("UI-001", "The Neuronment command-line call has a flag declared more than once or two flags that are different are trying to set a contradictory behaivior");
  MessagesDevelopmentAssert.QuickPutEntry_bool("UI-002", false);
  MessagesImplementationAssert.QuickPutEntry_bool("UI-002", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("UI-002", true);
  MessagesDisabling.QuickPutEntry_int("UI-002", 0);
  MessagesCount.QuickPutEntry_int("UI-002", 0);
  MessagesLabel.QuickPutEntry_string("UI-002","Flag expected");
  MessagesText.QuickPutEntry_string("UI-002", "The Neuronment command-line call holds a value in a place where should be a flag (a tring starting with \"-\").");
  MessagesDevelopmentAssert.QuickPutEntry_bool("UI-003", false);
  MessagesImplementationAssert.QuickPutEntry_bool("UI-003", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("UI-003", false);
  MessagesDisabling.QuickPutEntry_int("UI-003", 0);
  MessagesCount.QuickPutEntry_int("UI-003", 0);
  MessagesLabel.QuickPutEntry_string("UI-003","Flag not recognized, flag omitted");
  MessagesText.QuickPutEntry_string("UI-003", "The Neuronment command-line call has detected a flag that isn't on the list of possible flags. This flag will be ignored.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("UI-004", false);
  MessagesImplementationAssert.QuickPutEntry_bool("UI-004", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("UI-004", true);
  MessagesDisabling.QuickPutEntry_int("UI-004", 0);
  MessagesCount.QuickPutEntry_int("UI-004", 0);
  MessagesLabel.QuickPutEntry_string("UI-004","Label without content");
  MessagesText.QuickPutEntry_string("UI-004", "The Neuronment command-line call has a flag that requires a value, but the value hasn't been found. If you are trying to use a negative number put it between quotes.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("UI-006", false);
  MessagesImplementationAssert.QuickPutEntry_bool("UI-006", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("UI-006", true);
  MessagesDisabling.QuickPutEntry_int("UI-006", 0);
  MessagesCount.QuickPutEntry_int("UI-006", 0);
  MessagesLabel.QuickPutEntry_string("UI-006","Empty NProc name");
  MessagesText.QuickPutEntry_string("UI-006", "The call to Neuronment requires a mandatory nproc file to be processed.");
  // File IO Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-001", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-001", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-001", false);
  MessagesDisabling.QuickPutEntry_int("ER-001", 0);
  MessagesCount.QuickPutEntry_int("ER-001", 0);
  MessagesLabel.QuickPutEntry_string("ER-001","Development Assetion");
  MessagesText.QuickPutEntry_string("ER-001", "The program arrived to an unexpected set of conditions.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-002", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-002", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-002", false);
  MessagesDisabling.QuickPutEntry_int("ER-002", 0);
  MessagesCount.QuickPutEntry_int("ER-002", 0);
  MessagesLabel.QuickPutEntry_string("ER-002","Runtime Assertion");
  MessagesText.QuickPutEntry_string("ER-002", "Something went wrong running the program. Terminating");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-003", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-003", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-003", true);
  MessagesDisabling.QuickPutEntry_int("ER-003", 0);
  MessagesCount.QuickPutEntry_int("ER-003", 0);
  MessagesLabel.QuickPutEntry_string("ER-003","File couldn't be opened");
  MessagesText.QuickPutEntry_string("ER-003", "The nproc required for execution file couldn't be oppened");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-004", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-004", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-004", false);
  MessagesDisabling.QuickPutEntry_int("ER-004", 0);
  MessagesCount.QuickPutEntry_int("ER-004", 0);
  MessagesLabel.QuickPutEntry_string("ER-004","File couldn't be properly closed");
  MessagesText.QuickPutEntry_string("ER-004", "The nproc file previously executed didn't returned a propper closed status from the OS.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-005", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-005", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-005", true);
  MessagesDisabling.QuickPutEntry_int("ER-005", 0);
  MessagesCount.QuickPutEntry_int("ER-005", 0);
  MessagesLabel.QuickPutEntry_string("ER-005","Trying to get a new line from a non ready file");
  MessagesText.QuickPutEntry_string("ER-005", "This happens when for some reason the interpreter is trying to get a new line from a file that hasn't been properly oppened");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-006", true);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-006", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-006", false);
  MessagesDisabling.QuickPutEntry_int("ER-006", 0);
  MessagesCount.QuickPutEntry_int("ER-006", 0);
  MessagesLabel.QuickPutEntry_string("ER-006","Trying to get a new line from a file already at the end");
  MessagesText.QuickPutEntry_string("ER-006", "This happens when for some reason the interpreter is trying to get a new line from a file already at the EOF");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-007", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-007", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-007", true);
  MessagesDisabling.QuickPutEntry_int("ER-007", 0);
  MessagesCount.QuickPutEntry_int("ER-007", 0);
  MessagesLabel.QuickPutEntry_string("ER-007","Fail on getting a new line from nproc file");
  MessagesText.QuickPutEntry_string("ER-007", "This happens when for some reason the file stream under interpretation isn't able to retreive a new line from the nproc file, even if it is not at the EOF.");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-008", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-008", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-008", true);
  MessagesDisabling.QuickPutEntry_int("ER-008", 0);
  MessagesCount.QuickPutEntry_int("ER-008", 0);
  MessagesLabel.QuickPutEntry_string("ER-008","Implementation Assertion");
  MessagesText.QuickPutEntry_string("ER-008", "There is a problem or an incompete implementation of a required feature");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-009", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-009", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-009", false);
  MessagesDisabling.QuickPutEntry_int("ER-009", 0);
  MessagesCount.QuickPutEntry_int("ER-009", 0);
  MessagesLabel.QuickPutEntry_string("ER-009","Trying to close an unopened file");
  MessagesText.QuickPutEntry_string("ER-009", "The interpreter is trying to close a file that hasn't been oppened");
  MessagesDevelopmentAssert.QuickPutEntry_bool("ER-010", false);
  MessagesImplementationAssert.QuickPutEntry_bool("ER-010", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("ER-010", true);
  MessagesDisabling.QuickPutEntry_int("ER-010", 0);
  MessagesCount.QuickPutEntry_int("ER-010", 0);
  MessagesLabel.QuickPutEntry_string("ER-010","Required file is empty");
  MessagesText.QuickPutEntry_string("ER-010", "The interpreter requires a file for execution. In this case the file name is empty.");
  // Implementation Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-001", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-001", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-001", false);
  MessagesDisabling.QuickPutEntry_int("DV-001", 0);
  MessagesCount.QuickPutEntry_int("DV-001", 0);
  MessagesLabel.QuickPutEntry_string("DV-001","Missing implementation");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-002", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-002", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-002", false);
  MessagesDisabling.QuickPutEntry_int("DV-002", 0);
  MessagesCount.QuickPutEntry_int("DV-002", 0);
  MessagesLabel.QuickPutEntry_string("DV-002","Trying to declare a previously declared setting");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-003", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-003", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-003", false);
  MessagesDisabling.QuickPutEntry_int("DV-003", 0);
  MessagesCount.QuickPutEntry_int("DV-003", 0);
  MessagesLabel.QuickPutEntry_string("DV-003","Trying to load a setting of an unsupported type");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-005", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-005", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-005", false);
  MessagesDisabling.QuickPutEntry_int("DV-005", 0);
  MessagesCount.QuickPutEntry_int("DV-005", 0);
  MessagesLabel.QuickPutEntry_string("DV-005","Trying to use an unsupported setting");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-006", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-006", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-006", false);
  MessagesDisabling.QuickPutEntry_int("DV-006", 0);
  MessagesCount.QuickPutEntry_int("DV-006", 0);
  MessagesLabel.QuickPutEntry_string("DV-006","Trying to read an incorrect data type for the setting");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-007", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-007", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-007", false);
  MessagesDisabling.QuickPutEntry_int("DV-007", 0);
  MessagesCount.QuickPutEntry_int("DV-007", 0);
  MessagesLabel.QuickPutEntry_string("DV-007","The setting count is different than the declared setting count on the HashEntry");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-008", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-008", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-008", false);
  MessagesDisabling.QuickPutEntry_int("DV-008", 0);
  MessagesCount.QuickPutEntry_int("DV-008", 0);
  MessagesLabel.QuickPutEntry_string("DV-008","The Log manager is being copied and this should NEVER happen");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-012", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-012", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-012", false);
  MessagesDisabling.QuickPutEntry_int("DV-012", 0);
  MessagesCount.QuickPutEntry_int("DV-012", 0);
  MessagesLabel.QuickPutEntry_string("DV-012","Trying a quick access of incorrect type");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-013", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-013", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-013", false);
  MessagesDisabling.QuickPutEntry_int("DV-013", 0);
  MessagesCount.QuickPutEntry_int("DV-013", 0);
  MessagesLabel.QuickPutEntry_string("DV-013","Hash Table Full");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-015", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-015", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-015", false);
  MessagesDisabling.QuickPutEntry_int("DV-015", 0);
  MessagesCount.QuickPutEntry_int("DV-015", 0);
  MessagesLabel.QuickPutEntry_string("DV-015","Setting declared but hasn't been initialized");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-017", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-017", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-017", false);
  MessagesDisabling.QuickPutEntry_int("DV-017", 0);
  MessagesCount.QuickPutEntry_int("DV-017", 0);
  MessagesLabel.QuickPutEntry_string("DV-017","Discrepancy on neuron type on assignment");
  MessagesDevelopmentAssert.QuickPutEntry_bool("DV-018", false);
  MessagesImplementationAssert.QuickPutEntry_bool("DV-018", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("DV-018", false);
  MessagesDisabling.QuickPutEntry_int("DV-018", 0);
  MessagesCount.QuickPutEntry_int("DV-018", 0);
  MessagesLabel.QuickPutEntry_string("DV-018","Trying to quick retrieve un-existent value");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-030", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-030", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-030", false);
  MessagesDisabling.QuickPutEntry_int("SD-030", 0);
  MessagesCount.QuickPutEntry_int("SD-030", 0);
  MessagesLabel.QuickPutEntry_string("SD-030","Internal simulation pointer corruption");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-031", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-031", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-031", false);
  MessagesDisabling.QuickPutEntry_int("SD-031", 0);
  MessagesCount.QuickPutEntry_int("SD-031", 0);
  MessagesLabel.QuickPutEntry_string("SD-031","Trying to compare 2 identical MT cells");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-032", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-032", true);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-032", false);
  MessagesDisabling.QuickPutEntry_int("SD-032", 0);
  MessagesCount.QuickPutEntry_int("SD-032", 0);
  MessagesLabel.QuickPutEntry_string("SD-032","Empty pointer to function entry");
  // Reporting Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("RP-002", false);
  MessagesImplementationAssert.QuickPutEntry_bool("RP-002", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("RP-002", true);
  MessagesDisabling.QuickPutEntry_int("RP-002", 0);
  MessagesCount.QuickPutEntry_int("RP-002", 0);
  MessagesLabel.QuickPutEntry_string("RP-002","Trying to close a non opened stream");
  MessagesDevelopmentAssert.QuickPutEntry_bool("RP-003", false);
  MessagesImplementationAssert.QuickPutEntry_bool("RP-003", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("RP-003", true);
  MessagesDisabling.QuickPutEntry_int("RP-003", 0);
  MessagesCount.QuickPutEntry_int("RP-003", 0);
  MessagesLabel.QuickPutEntry_string("RP-003","Stream didn't oppened correctly");
  // Simulator Interface Issues
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-001", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-001", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-001", true);
  MessagesDisabling.QuickPutEntry_int("SD-001", 0);
  MessagesCount.QuickPutEntry_int("SD-001", 0);
  MessagesLabel.QuickPutEntry_string("SD-001","Simple Simulator Not Initialized");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-015", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-015", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-015", true);
  MessagesDisabling.QuickPutEntry_int("SD-015", 0);
  MessagesCount.QuickPutEntry_int("SD-015", 0);
  MessagesLabel.QuickPutEntry_string("SD-015","No V1_Neuron created");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-016", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-016", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-016", true);
  MessagesDisabling.QuickPutEntry_int("SD-016", 0);
  MessagesCount.QuickPutEntry_int("SD-016", 0);
  MessagesLabel.QuickPutEntry_string("SD-016","No MT_Neuron created");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-021", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-021", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-021", true);
  MessagesDisabling.QuickPutEntry_int("SD-021", 0);
  MessagesCount.QuickPutEntry_int("SD-021", 0);
  MessagesLabel.QuickPutEntry_string("SD-021","Invalid timing for eternal excitation");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-025", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-025", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-025", true);
  MessagesDisabling.QuickPutEntry_int("SD-025", 0);
  MessagesCount.QuickPutEntry_int("SD-025", 0);
  MessagesLabel.QuickPutEntry_string("SD-025","Unordered external excitation phase insertion attempt");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-027", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-027", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-027", true);
  MessagesDisabling.QuickPutEntry_int("SD-027", 0);
  MessagesCount.QuickPutEntry_int("SD-027", 0);
  MessagesLabel.QuickPutEntry_string("SD-027","First diffusion phase should be always zero");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-028", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-028", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-028", true);
  MessagesDisabling.QuickPutEntry_int("SD-028", 0);
  MessagesCount.QuickPutEntry_int("SD-028", 0);
  MessagesLabel.QuickPutEntry_string("SD-028","The number of steps for simulate needs to be at least 1");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-033", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-033", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-033", true);
  MessagesDisabling.QuickPutEntry_int("SD-033", 0);
  MessagesCount.QuickPutEntry_int("SD-033", 0);
  MessagesLabel.QuickPutEntry_string("SD-033","Trying to access an invalid activation TimeStep");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-036", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-036", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-036", true);
  MessagesDisabling.QuickPutEntry_int("SD-036", 0);
  MessagesCount.QuickPutEntry_int("SD-036", 0);
  MessagesLabel.QuickPutEntry_string("SD-036","Setting not recognized");
  MessagesDevelopmentAssert.QuickPutEntry_bool("SD-037", false);
  MessagesImplementationAssert.QuickPutEntry_bool("SD-037", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("SD-037", true);
  MessagesDisabling.QuickPutEntry_int("SD-037", 0);
  MessagesCount.QuickPutEntry_int("SD-037", 0);
  MessagesLabel.QuickPutEntry_string("SD-037","Setting required");
  // Warnings
  MessagesDevelopmentAssert.QuickPutEntry_bool("WN-006", false);
  MessagesImplementationAssert.QuickPutEntry_bool("WN-006", false);
  MessagesRuntimeAssert.QuickPutEntry_bool("WN-006", false);
  MessagesDisabling.QuickPutEntry_int("WN-006", 1);
  MessagesCount.QuickPutEntry_int("WN-006", 0);
  MessagesLabel.QuickPutEntry_string("WN-006","There are undocumented calculations in use");
}
