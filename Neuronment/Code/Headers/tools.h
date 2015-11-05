
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

/**
 * Assertion on unexpected known manageable set of conditions
 */
void DevelopmentAssertion();

/**
 * Assertion on unexpected known unmanageable set of conditions
 */
void ImplementationAssertion();

/**
 * Assertion on unexpected unknown set of conditions
 */
void RuntimeAssertion();

////////////////////////////////////////////////////////////////////////////////////
// Catching error returns
////////////////////////////////////////////////////////////////////////////////////

/**
 * To process a return value before return
 * @param ReturnP        The status to return
 * @param ReturnMessageP The message to return (optional)
 * @return               Equals to the status to return
 */
ReturnType Return(ReturnType ReturnP, string ConditionsP = "", string ReturnMessageP = "");

////////////////////////////////////////////////////////////////////////////////////
// Hashing
////////////////////////////////////////////////////////////////////////////////////

/**
 * Transforms a string in to a hash table index
 * @param KeyP     The string to hash
 * @param HashKeyP The resulting key
 * @return
 */
ReturnType KeyToHashKey(string KeyP, unsigned int &HashKeyP);

////////////////////////////////////////////////////////////////////////////////////
// Data Validation
////////////////////////////////////////////////////////////////////////////////////

/**
 * Checks the specified conditions for a string
 * @param DataP       The data to check
 * @param ConditionsP The conditions to check
 * @return
 */
ReturnType DataCheck(string DataP, string ConditionsP);

/**
 * Checks the specified conditions for a int
 * @param DataP       The data to check
 * @param ConditionsP The conditions to check
 * @return
 */
ReturnType DataCheck(int DataP, string ConditionsP);

/**
 * Checks the specified conditions for a char**
 * @param DataP       The data to check
 * @param ConditionsP The conditions to check
 * @return
 */
ReturnType DataCheck(char** DataP, string ConditionsP);

/**
 * Checks the specified conditions for a char
 * @param DataP       The data to check
 * @param ConditionsP The conditions to check
 * @return
 */
ReturnType DataCheck(char DataP, string ConditionsP);

/**
 * Checks that the TypeP strings contains a valid type
 * @param TypeP The type string to validate
 * @return 
 */
ReturnType IsValidType(string TypeP);

////////////////////////////////////////////////////////////////////////////////////
// Tokens
////////////////////////////////////////////////////////////////////////////////////

/**
 * Tokenizes a string in a vector of tokens by the specified delimeter list
 * Obtained from: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
 * @param StringP     The string to tokenize
 * @param TokensP     The resulting vector
 * @param DelimetersP The delimeter to tokenize
 * @return 
 */
ReturnType Tokenize(const string& StringP, vector<string>& TokensP, const string& DelimetersP = "\t ");

////////////////////////////////////////////////////////////////////////////////////
// Trimming
////////////////////////////////////////////////////////////////////////////////////

/**
 * Trims the delimeter characters from the specified string by the right
 * @param StringP     The string to trim
 * @param DelimetersP The delimeters to trim
 * @return 
 */
ReturnType trim_right(string &StringP, string DelimetersP = " \f\n\r\t\v");

/**
 * Trims the delimeter characters from the specified string by the left
 * @param StringP     The string to trim
 * @param DelimetersP The delimeters to trim
 * @return 
 */
ReturnType trim_left(string &StringP, string DelimetersP = " \f\n\r\t\v");

/**
 * Trims the delimeter characters from the specified string by the right and the left
 * @param StringP     The string to trim
 * @param DelimetersP The delimeters to trim
 * @return 
 */
ReturnType trim(string &StringP, string DelimetersP = " \f\n\r\t\v");

////////////////////////////////////////////////////////////////////////////////////
// Parsing
////////////////////////////////////////////////////////////////////////////////////

/**
 * Parses a int to string
 * @param ValueP  The value to Parse
 * @param ReturnP The return string
 * @return 
 */
ReturnType ToString(int ValueP, string &ReturnP);

/**
 * Parses a bool to string
 * @param ValueP  The value to Parse
 * @param ReturnP The return string
 * @return 
 */
ReturnType ToString(bool ValueP, string &ReturnP);

/**
 * Parses a double to string
 * @param ValueP     The value to Parse
 * @param ReturnP    The return string
 * @param PrecisionP The number of decimals to print
 * @return 
 */
ReturnType ToString(double ValueP, string &ReturnP, int PrecisionP);

/**
 * Inline ToString for int
 * @param  ValueP The value to cast
 * @return        The casted value
 */
string ToString(int ValueP);

/**
 * Inline ToString for bool
 * @param  ValueP The value to cast
 * @return        The casted value
 */
string ToString(bool ValueP);

/**
 * Inline ToString for double
 * @param ValueP     The value to cast
 * @param PrecisionP The number of decimals to print
 * @return           The casted value
 */
string ToString(double ValueP, int PrecisionP = 6);

/**
 * Parses a string to int
 * @param StringP The string to parse
 * @param ReturnP The parsed value
 * @return 
 */
ReturnType ToInt(string StringP, int &ReturnP);

/**
 * Inline ToInt
 * @param StringP The string to parse
 * @return        The parsed value
 */
int ToInt(string StringP);

/**
 * Parses a string to bool
 * @param StringP The string to parse
 * @param ReturnP The parsed value
 * @return 
 */
ReturnType ToBool(string StringP, bool &ReturnP);

/**
 * Inline ToBool
 * @param StringP The string to parse
 * @return        The parsed value
 */
bool ToBool(string StringP);

/**
 * Parses a string to a double
 * @param StringP The string to parse
 * @param ReturnP The parsed value
 * @return 
 */
ReturnType ToDouble(string StringP, double &ReturnP);

/**
 * Inline ToDouble
 * @param StringP The string to parse
 * @return        The parsed value
 */
double ToDouble(string StringP);

/**
 * Returns a string with the "int" value
 * @param DummyP
 * @return 
 */
string TypeToString(int DummyP);

/**
 * Returns a string with the "bool" value
 * @param DummyP
 * @return 
 */
string TypeToString(bool DummyP);

/**
 * Returns a string with the "double" value
 * @param DummyP
 * @return 
 */
string TypeToString(double DummyP);

/**
 * Returns a string with the "string" value
 * @param DummyP
 * @return 
 */
string TypeToString(string DummyP);

////////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////////

/**
 * Calculates the cosine for a deg angle
 * @param AngleP The angle for calculation
 * @return       The cosine of AngleP
 */
double deg_cos(double AngleP);

/**
 * Calculates the sine for a deg angle
 * @param AngleP The angle for calculation
 * @return       The sine of AngleP
 */
double deg_sin(double AngleP);

////////////////////////////////////////////////////////////////////////////////////
// Deprecated
////////////////////////////////////////////////////////////////////////////////////

ReturnType ReturnCatch(ReturnType ReturnP, string ConditionsP = "");

#endif
