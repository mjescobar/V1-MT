/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <string>
#include <ctime>
#include <sstream>
#include <assert.h>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <fstream>
using namespace std;
#include "enum.h"
#include "define.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "Globals.h"
#include "Tools.h"
#include "main.h"

////////////////////////////////////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////////////////////////////////////

void RuntimeAssertion()
{
  Log.Message("ER-002");
  assert(0);
}

void DevelopmentAssertion()
{
#ifdef DEVELOPMENT
  Log.Message("ER-001");
  RuntimeAssertion();
#endif
}

void ImplementationAssertion()
{
  Log.Message("ER-008");
  RuntimeAssertion();
}

////////////////////////////////////////////////////////////////////////////////////
// Tokens
////////////////////////////////////////////////////////////////////////////////////

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters)
{
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  string::size_type pos = str.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }
}

void TokenizeNoDelete(const string& str, vector<string>& tokens, const string& delimiters)
{
  string::size_type lastPos = 0; //str.find_first_not_of(delimiters, 0);
  string::size_type pos = str.find_first_of(delimiters, lastPos + 1);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = pos; //str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    if (string::npos != lastPos) {
      pos = str.find_first_of(delimiters, lastPos + 1);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Arrays
////////////////////////////////////////////////////////////////////////////////////

void* DuplicateArray(void* SourceP, int CountP, DataType TypeP)
{
  void* ToReturn = NULL;
  if (SourceP == NULL) {
    return NULL;
  }
  switch (TypeP) {
  case Data_bool:
    ToReturn = malloc(sizeof (bool) * CountP);
    if (SourceP) {
      for (int i = 0; i < CountP; i++) {
        ((bool*)ToReturn)[i] = ((bool*)SourceP)[i];
      }
    }
    break;
  case Data_int:
    ToReturn = malloc(sizeof (int) * CountP);
    if (SourceP) {
      for (int i = 0; i < CountP; i++) {
        ((int*) ToReturn)[i] = ((int*) SourceP)[i];
      }
    }
    break;
  case Data_float:
    ToReturn = malloc(sizeof (float) * CountP);
    if (SourceP) {
      for (int i = 0; i < CountP; i++) {
        ((float*) ToReturn)[i] = ((float*) SourceP)[i];
      }
    }
    break;
  case Data_double:
    ToReturn = malloc(sizeof (double) * CountP);
    if (SourceP) {
      for (int i = 0; i < CountP; i++) {
        ((double*) ToReturn)[i] = ((double*) SourceP)[i];
      }
    }
    break;
  case Data_string:
    ToReturn = malloc(sizeof (string) * CountP);
    if (SourceP) {
      for (int i = 0; i < CountP; i++) {
        ((string*) ToReturn)[i] = ((string*) SourceP)[i];
      }
    }
    break;
  default:
    Log.Message("DV-001");
    ImplementationAssertion();
    return NULL;
  }
  return ToReturn;
}

////////////////////////////////////////////////////////////////////////////////////
// Hashing
////////////////////////////////////////////////////////////////////////////////////

unsigned int HashString(string s)
{
  unsigned h = HASH_C;
  int len = s.length();
  for (int i = 0; i < len; i++) {
    h = (h * HASH_A) ^ (s[i] * HASH_B);
  }
  return h;
}

////////////////////////////////////////////////////////////////////////////////////
// Parsing
////////////////////////////////////////////////////////////////////////////////////

void CstringToString(char* CstringP, string &ReturnP)
{
  stringstream ss;
  ss << CstringP;
  ReturnP = ss.str();
}

string ICstringToString(char* CstringP)
{
  string Tmp;
  CstringToString(CstringP, Tmp);
  return Tmp;
}

bool IntToString(int ValueP, string &ReturnP)
{
  stringstream ss;
  ss << ValueP;
  ReturnP = ss.str();
  return true;
}

string IIntToString(int ValueP)
{
  string ReturnP;
  IntToString(ValueP, ReturnP);
  return ReturnP;
}

bool DoubleToString(double ValueP, string &ReturnP)
{
  stringstream ss;
  ss << ValueP;
  ReturnP = ss.str();
  return true;
}

string IDoubleToString(double ValueP)
{
  string Tmp;
  DoubleToString(ValueP, Tmp);
  return Tmp;
}

void StringToBool(string StringP, bool &ReturnP)
{
  if (StringP == "TRUE"
          || StringP == "True"
          || StringP == "true"
          || StringP == "T"
          || StringP == "t"
          || StringP == "1") {
    ReturnP = true;
  } else {
    if (StringP == "FALSE"
            || StringP == "False"
            || StringP == "false"
            || StringP == "F"
            || StringP == "f"
            || StringP == "0") {
      ReturnP = false;
    } else {
      Log.Message("IN-007");
      ReturnP = false;
    }
  }
}

bool IStringToBool(string StringP)
{
  bool Tmp;
  StringToBool(StringP, Tmp);
  return Tmp;
}

void BoolToString(bool ValueP, string &ReturnP)
{
  if (ValueP) {
    ReturnP = "true";
  } else {
    ReturnP = "false";
  }
}

string IBoolToString(bool ValueP)
{
  string Tmp;
  BoolToString(ValueP, Tmp);
  return Tmp;
}

bool StringToDouble(string StringP, double &ReturnP)
{
  for (int i = 0; i < (int) StringP.length(); i++) {
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') {
      return false;
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return true;
}

double IStringToDouble(string StringP)
{
  double Tmp;
  StringToDouble(StringP, Tmp);
  return Tmp;
}

bool StringToInt(string StringP, int &ReturnP)
{
  for (int i = 0; i < (int) StringP.length(); i++) {
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') {
      return false;
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return true;
}

int IStringToInt(string StringP)
{
  int Tmp;
  StringToInt(StringP, Tmp);
  return Tmp;
}

////////////////////////////////////////////////////////////////////////////////////
// Trimming
////////////////////////////////////////////////////////////////////////////////////

/**
 * Trim the characters from right
 * @param s String to trim
 * @return Trimmed string
 */
string trim_right(string s, string delimiters)
{
  if (s.length() > 0) {
    return s.substr(0, s.find_last_not_of(delimiters) + 1);
  } else {
    return s;
  }
}

/**
 * Trim the characters from left
 * @param s String to trim
 * @return Trimmed string
 */
string trim_left(string s, string delimiters)
{
  if (s.length() > 0) {
    return s.substr(s.find_first_not_of(delimiters));
  } else {
    return s;
  }
}

/**
 * Trim the characters from right and then left
 * @param s String to trim
 * @return Trimmed string
 */
string trim(string s, string delimiters)
{
  if (s.length() > 0) {
    return trim_left(trim_right(s, delimiters), delimiters);
  } else {
    return s;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// String Formating
////////////////////////////////////////////////////////////////////////////////////

string Alignment(string OriginalP, int SizeP, char FillP, SideType SideP)
{
  int ToAdd = SizeP - OriginalP.length();
  if (ToAdd < 1) {
    return OriginalP;
  }
  for (int i = 0; i < ToAdd; i++) {
    if (SideP = Side_Right) {
      OriginalP = OriginalP + FillP;
    }
    if (SideP = Side_Left) {
      OriginalP = FillP + OriginalP;
    }
  }
  return OriginalP;
}

string NNumber(int NumberP)
{
  return Alignment(IIntToString(NumberP), NEURONS_NAME_SIZE, '0', Side_Left);
}

////////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////////

double deg_cos(double AngleP)
{
  return cos(AngleP * PI / 180);
}

////////////////////////////////////////////////////////////////////////////////////
// Runtime Timing
////////////////////////////////////////////////////////////////////////////////////

bool PrintElapsedTime()
{
  clock_t NewElapsedTime = clock();
  if (!ElapsedTimeInitialized) {
    ElapsedTime = NewElapsedTime;
    Log.Output(Message_Allways, "ET: Start");
    ElapsedTimeInitialized = true;
  } else {
    Log.Output(Message_Allways, "ET: " + IDoubleToString(double(NewElapsedTime - ElapsedTime)) + "(" + IDoubleToString(double(CLOCKS_PER_SEC)) + ")");
    ElapsedTime = NewElapsedTime;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Command Line Processing
////////////////////////////////////////////////////////////////////////////////////

bool GetFlag(vector<string> TokensP, string FlagP)
{
  for (int i = 0; i < TokensP.size(); i++) {
    if (TokensP[i][0] == '-') {
      if (TokensP[i].substr(1, TokensP[i].size() - 1) == FlagP) {
        return true;
      }
    }
  }
  return false;
}

string GetFlagValue(vector<string> TokensP, string FlagP)
{
  for (int i = 0; i < TokensP.size(); i++) {
    if (TokensP[i][0] == '-') {
      if (TokensP[i].substr(1, TokensP[i].size() - 1) == FlagP) {
        if (i + 1 < TokensP.size()) {
          if (TokensP[i + 1][0] != '-') {
            return TokensP[i + 1];
          }
        }
      }
    }
  }
  Log.Message("IN-006: In command \"" + TokensP[0] + " " + TokensP[1] + "\" flag \"" + FlagP + "\"");
  return "";
}

////////////////////////////////////////////////////////////////////////////////////
// Abbreviated math
////////////////////////////////////////////////////////////////////////////////////

double NonLinearity001(double ValueP, double MaxP, double AP, double BP)
{
  double Tem = (MaxP / (1 + exp(AP * (BP - ValueP))) - MaxP / (1 + exp(AP * (BP - 0))))*(MaxP / (MaxP - MaxP / (1 + exp(AP * (BP - 0)))));
  Tem = (Tem > 0) ? Tem : 0;
  return Tem;
}
