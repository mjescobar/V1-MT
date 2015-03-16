/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef TOOLS_H
#define	TOOLS_H

////////////////////////////////////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////////////////////////////////////

/**
 * Assertion always. Unrecoverable error on execution
 */
void RuntimeAssertion();

/**
 * Assertion on development mode, gets disabled if compiled without the -DDEVELOPMENT
 */
void DevelopmentAssertion();

/**
 * Assertion when unimplemented feature requested. Assertion always
 */
void ImplementationAssertion();

////////////////////////////////////////////////////////////////////////////////////
// Tokens
////////////////////////////////////////////////////////////////////////////////////

/**
 * Transforms a string in a set of tokens
 * From: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
 * @param str The original string
 * @param tokens The tokens destination vector
 * @param delimiters The delimeters for tokenization (default "\t ")
 */
void Tokenize(const string& str, vector<string>& tokens, const string& delimiters = "\t ");

/**
 * Transforms a string in a set of tokens without deleting the delimeters
 * From: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
 * @param str The original string
 * @param tokens The tokens destination vector
 * @param delimiters The delimeters for tokenization (default "\t ")
 */
void TokenizeNoDelete(const string& str, vector<string>& tokens, const string& delimiters);

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

////////////////////////////////////////////////////////////////////////////////////
// Hashing
////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns the hash for a string
 * @param s String to get hash from
 * @return the Hash value
 */
unsigned int HashString(string s);

////////////////////////////////////////////////////////////////////////////////////
// Parsing
////////////////////////////////////////////////////////////////////////////////////

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
 * int to string
 * @param ValueP Value to transform
 * @param ReturnP The pointer for the destination
 * @return The formated string
 */
bool IntToString(int ValueP, string &ReturnP);

/**
 * int to string
 * @param ValueP value to parse
 * @return parsed string
 */
string IIntToString(int ValueP);

/**
 * double as string
 * @param ValueP The value to get converted
 * @param ReturnP The parsed value destination
 * @return true if succesful
 */
bool DoubleToString(double ValueP, string &ReturnP);

/**
 * double to string
 * @param ValueP double for parsing
 * @return the parsed value
 */
string IDoubleToString(double ValueP);

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
// Trimming
////////////////////////////////////////////////////////////////////////////////////

/**
 * Trim the characters from right
 * @param s String to trim
 * @return Trimmed string
 */
string trim_right(string s, string delimiters = " \f\n\r\t\v");

/**
 * Trim the characters from left
 * @param s String to trim
 * @return Trimmed string
 */
string trim_left(string s, string delimiters = " \f\n\r\t\v");

/**
 * Trim the characters from right and then left
 * @param s String to trim
 * @return Trimmed string
 */
string trim(string s, string delimiters = " \f\n\r\t\v");

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
 * formats int to length 3 filled with 0s to the left
 * @param NumberP
 * @return 
 */
string NNumber(int NumberP);

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
bool PrintElapsedTime();

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

#endif	/* TOOLS_H */
