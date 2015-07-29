/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <string>
//#include <ctime>
#include <sstream>
//#include <assert.h>
//#include <vector>
//#include <stdlib.h>
//#include <cmath>
#include <iomanip>
//#include <fstream>
using namespace std;
//#include "enum.h"
//#include "define.h"
//#include "HashEntry.h"
//#include "HashTable.h"
//#include "LogManager.h"
//#include "SettingsManager.h"
//#include "Globals.h"
#include "tools.h"
#include "extern.h"

////////////////////////////////////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////////////////////////////////////

void ReturnAssertion()
{
  Log.Message("DV-019");
  assert(0);
}

void DevelopmentAssertion()
{
#ifdef DEVELOPMENT
  Log.Message("ER-001", true);
  Log.OutputEmptyLine(MessageAllways);
  assert(0);
#else
  Log.Message("ER-011");
#endif
}

void ImplementationAssertion()
{
  Log.Message("ER-008", true);
  Log.OutputEmptyLine(MessageAllways);
  assert(0);
}

void RuntimeAssertion()
{
  Log.Message("ER-002", true);
  Log.OutputEmptyLine(MessageAllways);
  assert(0);
}

////////////////////////////////////////////////////////////////////////////////////
// Catching error returns
////////////////////////////////////////////////////////////////////////////////////

ReturnType ReturnCatch(ReturnType ReturnP, string ConditionsP)
{
  if (ConditionsP == "ContinueOnFail") {
    return ReturnSuccess;
  }
  if (ConditionsP == "FailAssertOnDebug") {
    if (ReturnP == ReturnFail) {
      Log.Message("DV-021: " + ReturnMessage);
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    ReturnAssertion();
  }
  if (ReturnP == ReturnSuccessWarning) {
    Log.Message("DV-020: " + ReturnMessage);
  }
  if (ReturnP == ReturnFail) {
    Log.Message("DV-021: " + ReturnMessage);
  }
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Hashing
////////////////////////////////////////////////////////////////////////////////////

ReturnType KeyToHashKey(string KeyP, unsigned int &HashKeyP)
{
  unsigned HashKey = HASH_C;
  int KeyLength = KeyP.length();
  for (int i = 0; i < KeyLength; i++) {
    HashKey = (HashKey * HASH_A) ^ (KeyP[i] * HASH_B);
  }
  HashKeyP = HashKey;
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Data Validation
////////////////////////////////////////////////////////////////////////////////////

ReturnType DataCheck(string DataP, string ConditionsP)
{
  if (ConditionsP == "NonEmpty") {
    if (DataP == "") {
      Log.Message("SD-003");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.Message("DV-022");
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType DataCheck(int DataP, string ConditionsP)
{
  if (ConditionsP == "GreaterThanZero") {
    if (DataP <= 0) {
      Log.Message("SD-008");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "NonNegative") {
    if (DataP < 0) {
      Log.Message("SD-009");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.Message("DV-009: " + ConditionsP);
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType DataCheck(char** DataP, string ConditionsP)
{
  if (ConditionsP == "NotNull") {
    if (DataP < 0) {
      Log.Message("SD-010");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.Message("DV-009: " + ConditionsP);
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType DataCheck(char DataP, string ConditionsP)
{
  if (ConditionsP == "IsLetter") {
    if ((DataP >= 65 && DataP <= 90) || (DataP >= 97 && DataP <= 122)) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsNumber") {
    if (DataP >= 48 && DataP <= 57) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsApostrophe") {
    if (DataP == 39) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsLessThan") {
    if (DataP == 60) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsGreaterThan") {
    if (DataP == 62) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsSpace") {
    if (DataP == 32) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsHyphen") {
    if (DataP == 45) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsDot") {
    if (DataP == 46) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsUnderscore") {
    if (DataP == 95) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsNumberSign") {
    if (DataP == 35) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsSlash") {
    if (DataP == 47) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsBackSlash") {
    if (DataP == 92) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsTab") {
    if (DataP == 9) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBraces") {
    if (DataP == 123 || DataP == 125) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBracesOpen") {
    if (DataP == 123) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBracesClose") {
    if (DataP == 125) {
      return ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP != "") {
    Log.Message("DV-009: " + ConditionsP);
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType IsValidType(string TypeP)
{
  if (TypeP == "int") {
    return ReturnSuccess;
  } else if (TypeP == "bool") {
    return ReturnSuccess;
  } else if (TypeP == "double") {
    return ReturnSuccess;
  } else if (TypeP == "string") {
    return ReturnSuccess;
  }
  return ReturnFail;
}

////////////////////////////////////////////////////////////////////////////////////
// Tokens
////////////////////////////////////////////////////////////////////////////////////

ReturnType Tokenize(const string& StringP, vector<string>& TokensP, const string& DelimetersP)
{
  TokensP.clear();
  string::size_type lastPos = StringP.find_first_not_of(DelimetersP, 0);
  string::size_type pos = StringP.find_first_of(DelimetersP, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    TokensP.push_back(StringP.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = StringP.find_first_not_of(DelimetersP, pos);
    // Find next "non-delimiter"
    pos = StringP.find_first_of(DelimetersP, lastPos);
  }
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Trimming
////////////////////////////////////////////////////////////////////////////////////

ReturnType trim_right(string &StringP, string DelimetersP)
{
  string String = StringP;
  if (String.length() > 0) {
    StringP = String.substr(0, String.find_last_not_of(DelimetersP) + 1);
  }
  return ReturnSuccess;
}

ReturnType trim_left(string &StringP, string DelimetersP)
{
  string String = StringP;
  if (String.length() > 0) {
    StringP = String.substr(String.find_first_not_of(DelimetersP));
  }
  return ReturnSuccess;
}

ReturnType trim(string &StringP, string DelimetersP)
{
  string String = StringP;
  if (String.length() > 0) {
    ReturnCatch(trim_right(StringP, DelimetersP));
    ReturnCatch(trim_left(StringP, DelimetersP));
  }
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Parsing
////////////////////////////////////////////////////////////////////////////////////

ReturnType ToString(int ValueP, string &ReturnP)
{
  stringstream ss;
  ss << ValueP;
  ReturnP = ss.str();
  return ReturnSuccess;
}

string ToString(int ValueP)
{
  string ReturnP;
  ToString(ValueP, ReturnP);
  return ReturnP;
}

ReturnType ToInt(string StringP, int &ReturnP)
{
  for (int i = 0; i < (int) StringP.length(); i++) {
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') {
      return ReturnFail;
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return ReturnSuccess;
}

int ToInt(string StringP)
{
  int Tmp;
  ReturnCatch(ToInt(StringP, Tmp), "FailAssertOnDebug");
  return Tmp;
}

ReturnType ToBool(string StringP, bool &ReturnP)
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
      Log.Message("IN-007"); //Lothar
      ReturnMessage = "IN-007";
      ReturnP = false;
      return ReturnSuccessWarning;
    }
  }
}

bool ToBool(string StringP)
{
  bool Tmp;
  ReturnCatch(ToBool(StringP, Tmp), "FailAssertOnDebug");
  return Tmp;
}

ReturnType ToDouble(string StringP, double &ReturnP)
{
  for (int i = 0; i < (int) StringP.length(); i++) {
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') {
      return ReturnFail;
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return ReturnSuccess;
}

double ToDouble(string StringP)
{
  double Tmp;
  ReturnCatch(ToDouble(StringP, Tmp), "FailAssertOnDebug");
  return Tmp;
}

ReturnType ToString(double ValueP, string &ReturnP, int PrecisionP)
{
  stringstream ss;
  ss << fixed << setprecision(PrecisionP) << ValueP;
  ReturnP = ss.str();
  return ReturnSuccess;
}

string ToString(double ValueP, int PrecisionP)
{
  string Tmp;
  ToString(ValueP, Tmp, PrecisionP);
  return Tmp;
}

ReturnType ToString(bool ValueP, string &ReturnP)
{
  if (ValueP) {
    ReturnP = "true";
  } else {
    ReturnP = "false";
  }
  return ReturnSuccess;
}

string ToString(bool ValueP)
{
  string Tmp;
  ToString(ValueP, Tmp);
  return Tmp;
}

#if 0

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

ReturnType CheckInt(int IntP, string ConditionsP)
{
  if (ConditionsP == "GreaterThanZero") {
    if (IntP <= 0) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "NonNegative") {
    if (IntP < 0) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.Message("DV-009");
    return ReturnFail;
  }
  return ReturnSuccess;
}

ReturnType CheckInt(int IntP, string ConditionsP, int LowerP, int UpperP)
{
  if (ConditionsP == "Range[]") {
    if (IntP < LowerP || IntP > UpperP) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "Range[[") {
    if (IntP < LowerP || IntP >= UpperP) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "Range]]") {
    if (IntP <= LowerP || IntP > UpperP) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "Range][") {
    if (IntP <= LowerP || IntP >= UpperP) {
      Log.Message("SD-004");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.Message("DV-009");
    return ReturnFail;
  }
  return ReturnSuccess;
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
    if (SideP == Side_Right) {
      OriginalP = OriginalP + FillP;
    }
    if (SideP == Side_Left) {
      OriginalP = FillP + OriginalP;
    }
  }
  return OriginalP;
}

string DeleteTrailingZeros(string OriginalP)
{
  string CleanString = "";
  bool Deleted = false;
  for (int i = 0; i < OriginalP.size(); i++) {
    if (OriginalP[i] == '\'') {
      i++;
      Deleted = true;
      while (OriginalP[i] == '0') {
        i++;
      }
    }
    if (i < OriginalP.size()) {
      if (OriginalP[i] <= '9' && OriginalP[i] >= '0') {
        if (Deleted) {
          CleanString = CleanString + "'" + OriginalP[i];
          Deleted = false;
        } else {
          CleanString = CleanString + OriginalP[i];
        }
      } else {
        if (Deleted) {
          CleanString = CleanString + "'0" + OriginalP[i];
          Deleted = false;
        } else {
          CleanString = CleanString + OriginalP[i];
        }
      }
    } else {
      CleanString = CleanString + "'0";
    }
  }
  return CleanString;
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

bool PrintElapsedTime(clock_t* ElapsedTimeP)
{
  clock_t NewElapsedTime = clock();
  Log.Output(Message_Allways, "TIME: " + ToString(double(NewElapsedTime - *ElapsedTimeP) / CLOCKS_PER_SEC, 3) + "[s]");
  *ElapsedTimeP = NewElapsedTime;
  return true;
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

#endif