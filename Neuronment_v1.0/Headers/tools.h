/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef TOOLS_H
#define	TOOLS_H

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;
#include "enum.h"
#include "define.h"

////////////////////////////////////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////////////////////////////////////

void ReturnAssertion();
void DevelopmentAssertion();
void ImplementationAssertion();
void RuntimeAssertion();

////////////////////////////////////////////////////////////////////////////////////
// Catching error returns
////////////////////////////////////////////////////////////////////////////////////

ReturnType ReturnCatch(ReturnType ReturnP, string ConditionsP = "");

////////////////////////////////////////////////////////////////////////////////////
// Hashing
////////////////////////////////////////////////////////////////////////////////////

ReturnType KeyToHashKey(string KeyP, unsigned int &HashKeyP);

////////////////////////////////////////////////////////////////////////////////////
// Data Validation
////////////////////////////////////////////////////////////////////////////////////

ReturnType DataCheck(string DataP, string ConditionsP);
ReturnType DataCheck(int DataP, string ConditionsP);
ReturnType DataCheck(char** DataP, string ConditionsP);
ReturnType DataCheck(char DataP, string ConditionsP);

////////////////////////////////////////////////////////////////////////////////////
// Tokens
////////////////////////////////////////////////////////////////////////////////////

//From: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
ReturnType Tokenize(const string& StringP, vector<string>& TokensP, const string& DelimetersP = "\t ");

////////////////////////////////////////////////////////////////////////////////////
// Trimming
////////////////////////////////////////////////////////////////////////////////////

ReturnType trim_right(string &StringP, string DelimetersP = " \f\n\r\t\v");
ReturnType trim_left(string &StringP, string DelimetersP = " \f\n\r\t\v");
ReturnType trim(string &StringP, string DelimetersP = " \f\n\r\t\v");

////////////////////////////////////////////////////////////////////////////////////
// Parsing
////////////////////////////////////////////////////////////////////////////////////

bool IntToString(int ValueP, string &ReturnP);
string IIntToString(int ValueP);

#if 0
/**
 * Transforms a string in a set of tokens without deleting the delimeters
 * From: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
 * @param str The original string
 * @param tokens The tokens destination vector
 * @param delimiters The delimeters for tokenization (default "\t ")
 */
void TokenizeNoDelete(const string& str, vector<string>& tokens, const string& delimiters);

////////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////////

ReturnType CheckString(string StringP, string ConditionsP);

ReturnType CheckInt(int IntP, string ConditionsP);

ReturnType CheckInt(int IntP, string ConditionsP, int LowerP, int UpperP);

////////////////////////////////////////////////////////////////////////////////////
// Arrays
////////////////////////////////////////////////////////////////////////////////////

/**
 * Duplicates an array
 * @param SourceP The original array as void*
 * @param SourceSizeP The number of element of the original array
 * @param TypeP The data type stored by the array
 * @return A duplicated array as void*
 */
void* DuplicateArray(void* SourceP, int SourceSizeP, DataType TypeP);

/**
 * Transform a char* to string
 * @param the char* to transform
 * @return the char* as string
 */
void CstringToString(char* CstringP, string &Return);

/**
 * char* to string
 * @param the char* to transform
 * @return the char* as string
 */
string ICstringToString(char* CstringP);

/**
 * double as string
 * @param ValueP The value to get converted
 * @param ReturnP The parsed value destination
 * @return
 */
bool DoubleToString(double ValueP, string &ReturnP);

/**
 * 
 * @param ValueP
 * @param ReturnP
 * @param 
 * @return 
 */
bool DoubleToString(double ValueP, string &ReturnP, int PrecisionP);

/**
 * double to string
 * @param ValueP double for parsing
 * @return the parsed value
 */
string IDoubleToString(double ValueP);

/**
 * 
 * @param ValueP
 * @param PrecisionP
 * @return 
 */
string IDoubleToString(double ValueP, int PrecisionP);

/**
 * string to bool
 * @param StringP The string to interpret
 * @param ReturnP The pointer for the destination
 * @return A boolean value according to the string
 */
void StringToBool(string StringP, bool &ReturnP);

/**
 * string to bool
 * @param StringP string for parsing
 * @return the parsed value
 */
bool IStringToBool(string StringP);

/**
 * 
 * @param StringP
 * @param ReturnP
 * @return 
 */
void BoolToString(bool ValueP, string &ReturnP);

/**
 * 
 * @param ValueP
 * @return 
 */
string IBoolToString(bool ValueP);

/**
 * string to double
 * @param StringP The string to be interpreted
 * @param ReturnP The pointer for the destination
 * @return true if the string was valid and interpreted, false otherwise
 */
bool StringToDouble(string StringP, double &ReturnP);

/**
 * string to double
 * @param StringP string for parsing
 * @return the parsed value
 */
double IStringToDouble(string StringP);

/**
 * string to int
 * @param StringP The string to be interpreted
 * @param ReturnP The pointer for the destination
 * @return true if the string was valid and interpreted, false otherwise
 */
bool StringToInt(string StringP, int &ReturnP);

/**
 * string to int
 * @param StringP string for parsing
 * @return the parsed value
 */
int IStringToInt(string StringP);

////////////////////////////////////////////////////////////////////////////////////
// String Formating
////////////////////////////////////////////////////////////////////////////////////

/**
 * Global function for string alignment
 * @param OriginalP Original String
 * @param SizeP Future string size
 * @param FillP Character to fill the missing length
 * @param SideP Side to add the missing length
 * @return A resized string
 */
string Alignment(string OriginalP, int SizeP, char FillP, SideType SideP);

/**
 * 
 * @param OriginalP
 * @return 
 */
string DeleteTrailingZeros(string OriginalP);

////////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////////

/**
 * Gets the cos for a deg valued angle
 * @param AngleP the angle in deg
 * @return the cos of the angle
 */
double deg_cos(double AngleP);

////////////////////////////////////////////////////////////////////////////////////
// Runtime Timing
////////////////////////////////////////////////////////////////////////////////////

/**
 * Prints the elapsed time in clock cycles from the previous function call
 * @return true if correctly printed
 */
bool PrintElapsedTime(clock_t* ElapsedTimeP);

////////////////////////////////////////////////////////////////////////////////////
// Command Line Processing
////////////////////////////////////////////////////////////////////////////////////

/**
 * Checks if a flag has been set on the command
 * @param TokensP The tokenized command
 * @param FlagP The flag that is been looked for
 * @return true is the flag exist
 */
bool GetFlag(vector<string> TokensP, string FlagP);

/**
 * Returns the value associated to a flag
 * @param TokensP The tokenized command
 * @param FlagP The flag that signals the value
 * @return The string indicated by the flag
 */
string GetFlagValue(vector<string> TokensP, string FlagP);

////////////////////////////////////////////////////////////////////////////////////
// Abbreviated math
////////////////////////////////////////////////////////////////////////////////////

double NonLinearity001(double ValueP, double MaxP, double AP, double BP);
#endif

#endif	/* TOOLS_H */
