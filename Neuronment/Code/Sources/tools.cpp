
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;
#include "tools.h"
#include "extern.h"

////////////////////////////////////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////////////////////////////////////

void DevelopmentAssertion()
{
#ifdef DEVELOPMENT
  Log.CodedMessage("ER-001", true);
  Log.Output(MessageAllways, "");
  assert(0);
#else
  Log.CodedMessage("ER-011");
#endif
}

void ImplementationAssertion()
{
  Log.CodedMessage("ER-008", true);
  Log.Output(MessageAllways, "");
  assert(0);
}

void RuntimeAssertion()
{
  Log.CodedMessage("ER-002", true);
  Log.Output(MessageAllways, "");
  assert(0);
}

////////////////////////////////////////////////////////////////////////////////////
// Catching error returns
////////////////////////////////////////////////////////////////////////////////////

ReturnType Return(ReturnType ReturnP, string ReturnMessageP, string ConditionsP)
{
  ErrorReturn = ReturnP;
  ErrorMessage = ReturnMessageP;
  if (ReturnMessageP.length() > 0) {
    Log.CodedMessage(ReturnMessageP);
  }
  if (ConditionsP == "IgnoreReturnValue"){
    return ReturnP;
  }
  if (ReturnP == ReturnFail) {
    Log.CodedMessage("DV-021");
  }

  return ReturnP;
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
      return Return(ReturnFail, "SD-003");
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    return Return(ReturnFail, "DV-022");
  }
  return ReturnSuccess;
}

ReturnType DataCheck(int DataP, string ConditionsP)
{
  if (ConditionsP == "GreaterThanZero") {
    if (DataP <= 0) {
      return Return(ReturnFail, "SD-008");
    }
    return ReturnSuccess;
  }
  if (ConditionsP == "NonNegative") {
    if (DataP < 0) {
      return Return(ReturnFail, "SD-009");
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    return Return(ReturnFail, "DV-009: " + ConditionsP);
  }
  return ReturnSuccess;
}

ReturnType DataCheck(char** DataP, string ConditionsP)
{
  if (ConditionsP == "NotNull") {
    if (DataP < 0) {
      Log.CodedMessage("SD-010");
      return ReturnFail;
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    Log.CodedMessage("DV-009: + ConditionsP");
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
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsApostrophe") {
    if (DataP == 39) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsLessThan") {
    if (DataP == 60) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsGreaterThan") {
    if (DataP == 62) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsSpace") {
    if (DataP == 32) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsHyphen") {
    if (DataP == 45) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsDot") {
    if (DataP == 46) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsUnderscore") {
    if (DataP == 95) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsNumberSign") {
    if (DataP == 35) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsSlash") {
    if (DataP == 47) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsBackSlash") {
    if (DataP == 92) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsTab") {
    if (DataP == 9) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBraces") {
    if (DataP == 123 || DataP == 125) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBracesOpen") {
    if (DataP == 123) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsCurlyBracesClose") {
    if (DataP == 125) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP == "IsColon") {
    if (DataP == 58) {
      return  ReturnSuccess;
    }
    return ReturnFail;
  }
  if (ConditionsP != "") {
    Log.CodedMessage("DV-009: " + ConditionsP);
    return ReturnFail;
  }
  return  ReturnSuccess;
}

ReturnType IsValidType(string TypeP)
{
  if (TypeP == "int") {
    return  ReturnSuccess;
  } else if (TypeP == "bool") {
    return  ReturnSuccess;
  } else if (TypeP == "double") {
    return  ReturnSuccess;
  } else if (TypeP == "string") {
    return  ReturnSuccess;
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
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') { //Lothar: proper char evaluation
      return Return(ReturnFail, "", "Unauthorized chars on string conversion, runtime assert");
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return ReturnSuccess;
}

int ToInt(string StringP)
{
  int Tmp;
  ToInt(StringP, Tmp);
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
      ReturnP = false;
      return Return(ReturnSuccess, "IN-007: " + StringP);
    }
  }
  return ReturnSuccess;
}

bool ToBool(string StringP)
{
  bool Tmp;
  ToBool(StringP, Tmp);
  return Tmp;
}

ReturnType ToDouble(string StringP, double &ReturnP)
{
  for (int i = 0; i < (int) StringP.length(); i++) {
    if ((StringP[i] < '0' or StringP[i] > '9') and StringP[i] != '-' and StringP[i] != '.') {//Lothar: proper char evaluation
      return Return(ReturnFail); //Lothar: proper coded message (toint reference))
    }
  }
  stringstream ss(StringP);
  ss >> ReturnP;
  return ReturnSuccess;
}

double ToDouble(string StringP)
{
  double Tmp;
  ToDouble(StringP, Tmp);
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

string TypeToString(int DummyP)
{
  return "int";
}

string TypeToString(bool DummyP)
{
  return "bool";
}

string TypeToString(double DummyP)
{
  return "double";
}

string TypeToString(string DummyP)
{
  return "string";
}

////////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////////

double deg_cos(double AngleP)
{
  return cos(AngleP * PI / 180.0);
}

double deg_sin(double AngleP)
{
  return sin(AngleP * PI / 180.0);
}

////////////////////////////////////////////////////////////////////////////////////
// Deprecated
////////////////////////////////////////////////////////////////////////////////////

ReturnType ReturnCatch(ReturnType ReturnP, string ConditionsP)
{
  //Log.CodedMessage("SY-001");
  if (ConditionsP == "FailAssertOnDebug") {
    if (ReturnP == ReturnFail) {
      Log.CodedMessage("DV-021");
    }
    return ReturnSuccess;
  }
  if (ConditionsP != "") {
    ImplementationAssertion();
  }
/*if (ReturnP == ReturnSuccessWarning) {
    Log.CodedMessage("DV-020");
  }*/
  if (ReturnP == ReturnFail) {
    Log.CodedMessage("DV-021");
  }
  return ReturnSuccess;
}
