
#include <string>
#include <vector>
//#include <stdlib.h>
//#include <fstream>
using namespace std;
//#include "define.h"
//#include "enum.h"
//#include "HashEntry.h"
#include "HashTable.h"
//#include "LogManager.h"
#include "extern.h"
#include "tools.h"
#include "VariableManager.h"
#include "LogManager.h"

VariableManager::VariableManager() :
HashInt(SETTINGS_MANAGER_INT_HASH_SIZE),
HashBool(SETTINGS_MANAGER_BOOL_HASH_SIZE),
HashDouble(SETTINGS_MANAGER_DOUBLE_HASH_SIZE),
HashString(SETTINGS_MANAGER_STRING_HASH_SIZE)
{
}

VariableManager::VariableManager(const VariableManager& orig)
{
  HashInt = orig.HashInt;
  HashBool = orig.HashBool;
  HashDouble = orig.HashDouble;
  HashString = orig.HashString;
}

VariableManager::~VariableManager()
{
}

ReturnType VariableManager::SetSettingFromString(string VariableP, string TypeP, string ValueP)
{
  vector<string> TokenizedValueP;
  vector<int> ValuesInt;
  vector<bool> ValuesBool;
  vector<double> ValuesDouble;
  vector<string> ValuesString;
  if (IsValidType(TypeP) == ReturnFail) {
    Log.CodedMessage("DV-033");
    return ReturnFail;
  }
  ReturnCatch(Tokenize(ValueP, TokenizedValueP));
  for (int i = 0; i < TokenizedValueP.size(); i++) {
    if (TypeP == "int") {
      ValuesInt.push_back(ToInt(TokenizedValueP[i]));
    } else if (TypeP == "bool") {
      ValuesBool.push_back(ToBool(TokenizedValueP[i]));
    } else if (TypeP == "double") {
      ValuesDouble.push_back(ToDouble(TokenizedValueP[i]));
    } else if (TypeP == "string") {
      ValuesString.push_back(TokenizedValueP[i]);
    } else {
      Log.CodedMessage("DV-033");
      return ReturnFail;
    }
  }
  if (TypeP == "int") {
    SetSetting(VariableP, ValuesInt);
  } else if (TypeP == "bool") {
    SetSetting(VariableP, ValuesBool);
  } else if (TypeP == "double") {
    SetSetting(VariableP, ValuesDouble);
  } else if (TypeP == "string") {
    SetSetting(VariableP, ValuesString);
  } else {
    Log.CodedMessage("DV-033");
    return ReturnFail;
  }
  return ReturnSuccess;
}

template <class VariableType> ReturnType VariableManager::SetSetting(string VariableP, vector<VariableType> &ValueP)
{
  HashTable<VariableType> *LocalTable = NULL;
  ReturnCatch(GetHashTable(VariableType(), &LocalTable));
  if (CheckUnicity(LocalTable, VariableP) == ReturnFail) {
    Log.CodedMessage("DV-002");
    return ReturnFail;
  }
  ReturnCatch(LocalTable->PutEntry(VariableP, ValueP));
  return ReturnSuccess;
}

ReturnType VariableManager::GetSettingAsString(string VariableP, string &VariableValue)
{
  vector<int> VariableValueInt;
  vector<bool> VariableValueBool;
  vector<double> VariableValueDouble;
  vector<string> VariableValueString;
  HashInt.GetEntry(VariableP, VariableValueInt);
  HashBool.GetEntry(VariableP, VariableValueBool);
  HashDouble.GetEntry(VariableP, VariableValueDouble);
  HashString.GetEntry(VariableP, VariableValueString);
  int TotalFound = 0;
  if (VariableValueInt.size() > 0) {
    TotalFound++;
  }
  if (VariableValueBool.size() > 0) {
    TotalFound++;
  }
  if (VariableValueDouble.size() > 0) {
    TotalFound++;
  }
  if (VariableValueString.size() > 0) {
    TotalFound++;
  }
  if (TotalFound < 1) {
    Log.CodedMessage("IN-002: " + VariableP);
    return ReturnFail;
  } else if (TotalFound > 1) {
    Log.CodedMessage("IN-013: " + VariableP);
    return ReturnFail;
  } else {
    string ToReturn;
    for (int i = 0; i < VariableValueInt.size(); i++) {
      if (ToReturn.length() != 0) {
        ToReturn = ToReturn + " ";
      }
      ToReturn = ToReturn + ToString(VariableValueInt[i]);
    }
    for (int i = 0; i < VariableValueBool.size(); i++) {
      if (ToReturn.length() != 0) {
        ToReturn = ToReturn + " ";
      }
      ToReturn = ToReturn + ToString(VariableValueBool[i]);
    }
    for (int i = 0; i < VariableValueDouble.size(); i++) {
      if (ToReturn.length() != 0) {
        ToReturn = ToReturn + " ";
      }
      ToReturn = ToReturn + ToString(VariableValueDouble[i]);
    }
    for (int i = 0; i < VariableValueString.size(); i++) {
      if (ToReturn.length() != 0) {
        ToReturn = ToReturn + " ";
      }
      ToReturn = ToReturn + VariableValueString[i];
    }
    VariableValue = ToReturn;
  }
  return ReturnSuccess;
}

template <class VariableType> ReturnType VariableManager::GetSetting(string VariableP, vector<VariableType> &ValueP)
{
  HashTable<VariableType> *LocalTable = NULL;
  ReturnCatch(GetHashTable(VariableType(), &LocalTable));
  if (CheckUnicity(LocalTable, VariableP) == ReturnFail) {
    Log.CodedMessage("DV-002");
    return ReturnFail;
  }
  return LocalTable->GetEntry(VariableP, ValueP);
}

template <class VariableType > ReturnType VariableManager::CheckUnicity(HashTable<VariableType> *LocalTableP, string VariableP)
{
  if ((void*) &HashInt != (void*) LocalTableP) {
    vector<int> Dummy;
    if (HashInt.GetEntry(VariableP, Dummy) != ReturnFail) {
      return ReturnFail;
    }
  }
  if ((void*) &HashBool != (void*) LocalTableP) {
    vector<bool> Dummy;
    if (HashBool.GetEntry(VariableP, Dummy) != ReturnFail) {
      return ReturnFail;
    }
  }
  if ((void*) &HashDouble != (void*) LocalTableP) {
    vector<double> Dummy;
    if (HashDouble.GetEntry(VariableP, Dummy) != ReturnFail) {
      return ReturnFail;
    }
  }
  if ((void*) &HashString != (void*) LocalTableP) {
    vector<string> Dummy;
    if (HashString.GetEntry(VariableP, Dummy) != ReturnFail) {

      return ReturnFail;
    }
  }
  return ReturnSuccess;
}

ReturnType VariableManager::GetHashTable(int DummyP, HashTable<int> **HashTableP)
{
  *HashTableP = &HashInt;
  return ReturnSuccess;
}

ReturnType VariableManager::GetHashTable(bool DummyP, HashTable<bool> **HashTableP)
{
  *HashTableP = &HashBool;
  return ReturnSuccess;
}

ReturnType VariableManager::GetHashTable(double DummyP, HashTable<double> **HashTableP)
{
  *HashTableP = &HashDouble;
  return ReturnSuccess;
}

ReturnType VariableManager::GetHashTable(string DummyP, HashTable<string> **HashTableP)
{
  *HashTableP = &HashString;
  return ReturnSuccess;
}

template ReturnType VariableManager::GetSetting<int>(string VariableP, vector<int> &ValueP);
template ReturnType VariableManager::GetSetting<bool>(string VariableP, vector<bool> &ValueP);
template ReturnType VariableManager::GetSetting<double>(string VariableP, vector<double> &ValueP);
template ReturnType VariableManager::GetSetting<string>(string VariableP, vector<string> &ValueP);
