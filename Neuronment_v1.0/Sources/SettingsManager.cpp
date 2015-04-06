/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;
#include "define.h"
#include "enum.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "Globals.h"
#include "Tools.h"
#include "SettingsManager.h"

SettingsManager::SettingsManager() :
Hash_int(Data_int, SETTINGS_MANAGER_INT_HASH_SIZE),
Hash_float(Data_float, SETTINGS_MANAGER_FLOAT_HASH_SIZE),
Hash_double(Data_double, SETTINGS_MANAGER_DOUBLE_HASH_SIZE),
Hash_string(Data_string, SETTINGS_MANAGER_STRING_HASH_SIZE),
Hash_bool(Data_bool, SETTINGS_MANAGER_BOOL_HASH_SIZE),
Hash_SettingType(Data_DataType, SETTINGS_MANAGER_SETTINGTYPE_HASH_SIZE),
Hash_SettingSize(Data_int, SETTINGS_MANAGER_SETTINGSIZE_HASH_SIZE)
{
}

SettingsManager::SettingsManager(const SettingsManager& orig)
{
  Hash_int = orig.Hash_int;
  Hash_float = orig.Hash_float;
  Hash_double = orig.Hash_double;
  Hash_string = orig.Hash_string;
  Hash_bool = orig.Hash_bool;
  Hash_SettingType = orig.Hash_SettingType;
  Hash_SettingSize = orig.Hash_SettingSize;
}

SettingsManager::~SettingsManager()
{
}

bool SettingsManager::SetSetting(string SettingP, DataType TypeP, int SizeP)
{
  HashEntry* SettingType = Hash_SettingType.GetEntry(SettingP);
  HashEntry* SettingSize = Hash_SettingSize.GetEntry(SettingP);
  if (SettingType || SettingSize) {
    Log.Message("DV-002: " + SettingP);
    return false;
  } else {
    void* ToType = malloc(sizeof (DataType));
    int* ToSize = (int*) malloc(sizeof (int));
    ((DataType*) ToType)[0] = TypeP;
    ((int*) ToSize)[0] = SizeP;
    bool ToReturn;
    ToReturn = Hash_SettingType.PutEntry(SettingP, ToType, 1, true);
    ToReturn &= Hash_SettingSize.PutEntry(SettingP, ToSize, 1, true);
    return ToReturn;
  }
}

int SettingsManager::GetSettingSize(string SettingP)
{
  int ToReturn = 0;
  HashEntry* Retrieved = Hash_SettingSize.GetEntry(SettingP);
  if (!Retrieved) {
    Log.Message("DV-005: " + SettingP);
    return 0;
  } else {
    if (Retrieved->GetValid()) {
      ToReturn = ((int*) Retrieved->GetContent())[0];
      return ToReturn;
    } else {
      Log.Message("DV-015");
      return 0;
    }
  }
}

DataType SettingsManager::GetSettingType(string SettingP)
{
  DataType ToReturn = Data_null;
  HashEntry* Retrieved = Hash_SettingType.GetEntry(SettingP);
  if (!Retrieved) {
    Log.Message("DV-005: " + SettingP);
    return Data_null;
  } else {
    if (Retrieved->GetValid()) {
      ToReturn = ((DataType*) Retrieved->GetContent())[0];
      return ToReturn;
    } else {
      Log.Message("DV-015");
      return Data_null;
    }
  }
}

bool SettingsManager::GetSettingValid(string SettingP)
{
  DataType ToReturn = Data_null;
  HashEntry* Retrieved = Hash_SettingType.GetEntry(SettingP);
  if (!Retrieved) {
    Log.Message("DV-005: " + SettingP);
    return false;
  } else {
    if (Retrieved->GetValid()) {
      return true;
    } else {
      return false;
    }
  }
}

void* SettingsManager::GetSettingContent(string SettingP)
{
  DataType SettingType = Data_null;
  HashEntry* Retrieved = Hash_SettingType.GetEntry(SettingP);
  if (!Retrieved) {
    Log.Message("DV-005: " + SettingP);
    return NULL;
  } else {
    SettingType = ((DataType*) Retrieved->GetContent())[0];
    switch (SettingType) {
    case Data_int:
      Retrieved = Hash_int.GetEntry(SettingP);
      break;
    case Data_bool:
      Retrieved = Hash_bool.GetEntry(SettingP);
      break;
    case Data_double:
      Retrieved = Hash_double.GetEntry(SettingP);
      break;
    case Data_string:
      Retrieved = Hash_string.GetEntry(SettingP);
      break;
    default:
      Log.Message("DV-001");
      return NULL;
    }
    if (Retrieved && Retrieved->GetValid()) {
      return Retrieved->GetContent();
    } else {
      return NULL;
    }
  }
}

void* SettingsManager::GetSettingContentSafe(string SettingP)
{
  void* ToReturn = GetSettingContent(SettingP);
  if (ToReturn) {
    return ToReturn;
  } else {
    Log.Message("SD-037: " + SettingP);
    return NULL;
  }
}

bool SettingsManager::StoreSetting(vector<string> TokenP)
{
  DataType SettingType = GetSettingType(TokenP[2]);
  int SettingSize = GetSettingSize(TokenP[2]);
  if (SettingSize > 0 && SettingType != Data_null) {
    if (TokenP.size() != SettingSize + 3) {
      Log.Message("IN-010");
      return false;
    }
    switch (SettingType) {
    case Data_bool:
      return StoreSetting_bool(TokenP);
    case Data_int:
      return StoreSetting_int(TokenP);
    case Data_float:
      Log.Message("DV-001");
      //      return StoreSetting_float(TokenP, SettingSize);
    case Data_double:
      return StoreSetting_double(TokenP);
    case Data_string:
      return StoreSetting_string(TokenP);
    default:
      Log.Message("DV-003");
      return false;
    }
  } else {
    Log.Message("IN-005");
    return false;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Boolean settings
////////////////////////////////////////////////////////////////////////////////////

bool SettingsManager::StoreSetting_bool(vector<string> TokenP)
{
  HashEntry* Retrieved = Hash_bool.GetEntry(TokenP[2]);
  int SettingSize = ((int*) Hash_SettingSize.GetEntry(TokenP[2])->GetContent())[0];
  if (Retrieved) {
    Log.Message("IN-003");
  }
  void* ToPut = malloc(sizeof (bool) * SettingSize);
  for (int i = 0; i < SettingSize; i++) {
    ((bool*)ToPut)[i] = IStringToBool(TokenP[3 + i]);
  }
  return Hash_bool.PutEntry(TokenP[2], ToPut, SettingSize, true);
}

bool* SettingsManager::GetSetting_bool(string SettingP)
{
  DataType SettingType = GetSettingType(SettingP);
  int SettingSize = GetSettingSize(SettingP);
  if (SettingSize > 0 && SettingType != Data_null) {
    if (SettingType == Data_bool) {
      HashEntry* Retrieved = Hash_bool.GetEntry(SettingP);
      if (!Retrieved || !Retrieved->GetValid()) {
        return NULL;
      } else {
        if (Retrieved->GetCount() != SettingSize) {
          Log.Message("DV-007");
          return NULL;
        } else {
          return (bool*) Retrieved->GetContent();
        }
      }
    } else {
      Log.Message("DV-006: " + SettingP + " as Data_bool");
      return NULL;
    }
  } else {
    Log.Message("DV-005: " + SettingP);
    return NULL;
  }
}

bool SettingsManager::GetSingleSetting_bool(string SettingP, bool DefaultP)
{
  bool* StoredSetting = GetSetting_bool(SettingP);
  if (StoredSetting) {
    return StoredSetting[0];
  } else {
    return DefaultP;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Double settings
////////////////////////////////////////////////////////////////////////////////////

bool SettingsManager::StoreSetting_double(vector<string> TokenP)
{
  HashEntry* Retrieved = Hash_double.GetEntry(TokenP[2]);
  int SettingSize = ((int*) Hash_SettingSize.GetEntry(TokenP[2])->GetContent())[0];
  if (Retrieved) {
    Log.Message("IN-003");
  }
  void* ToPut = malloc(sizeof (double) * SettingSize);
  for (int i = 0; i < SettingSize; i++) {
    ((double*) ToPut)[i] = IStringToDouble(TokenP[3 + i]);
  }
  return Hash_double.PutEntry(TokenP[2], ToPut, SettingSize, true);
}

double* SettingsManager::GetSetting_double(string SettingP)
{
  DataType SettingType = GetSettingType(SettingP);
  int SettingSize = GetSettingSize(SettingP);
  if (SettingSize > 0 && SettingType != Data_null) {
    if (SettingType == Data_double) {
      HashEntry* Retrieved = Hash_double.GetEntry(SettingP);
      if (!Retrieved || !Retrieved->GetValid()) {
        return NULL;
      } else {
        if (Retrieved->GetCount() != SettingSize) {
          Log.Message("DV-007");
          return NULL;
        } else {
          return (double*) Retrieved->GetContent();
        }
      }
    } else {
      Log.Message("DV-006: " + SettingP + " as Data_double");
      return NULL;
    }
  } else {
    Log.Message("DV-005: " + SettingP);
    return NULL;
  }
}

double SettingsManager::GetSingleSetting_double(string SettingP, double DefaultP)
{
  double* StoredSetting = GetSetting_double(SettingP);
  if (StoredSetting) {
    return StoredSetting[0];
  } else {
    return DefaultP;
  }
}

double SettingsManager::GetSingleSettingSafe_double(string SettingP, double DefaultP)
{
  if (GetSettingContent(SettingP)) {
    return GetSingleSetting_double(SettingP, DefaultP);
  } else {
    Log.Message("SD-037: " + SettingP);
    return DefaultP;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// String settings
////////////////////////////////////////////////////////////////////////////////////

bool SettingsManager::StoreSetting_string(vector<string> TokenP)
{
  HashEntry* Retrieved = Hash_string.GetEntry(TokenP[2]);
  int SettingSize = ((int*) Hash_SettingSize.GetEntry(TokenP[2])->GetContent())[0];
  if (Retrieved) {
    Log.Message("IN-003");
  }
  void* ToPut = malloc(sizeof (string) * SettingSize);
  for (int i = 0; i < SettingSize; i++) {
    new (&((string*) ToPut)[i]) std::string(TokenP[3 + i]);
  }
  return Hash_string.PutEntry(TokenP[2], ToPut, SettingSize, true);
}

string* SettingsManager::GetSetting_string(string SettingP)
{
  DataType SettingType = GetSettingType(SettingP);
  int SettingSize = GetSettingSize(SettingP);
  if (SettingSize > 0 && SettingType != Data_null) {
    if (SettingType == Data_string) {
      HashEntry* Retrieved = Hash_string.GetEntry(SettingP);
      if (!Retrieved || !Retrieved->GetValid()) {
        return NULL;
      } else {
        if (Retrieved->GetCount() != SettingSize) {
          Log.Message("DV-007");
          return NULL;
        } else {
          return (string*) Retrieved->GetContent();
        }
      }
    } else {
      Log.Message("DV-006: " + SettingP + " as Data_string");
      return NULL;
    }
  } else {
    Log.Message("DV-005: " + SettingP);
    return NULL;
  }
}

string SettingsManager::GetSingleSetting_string(string SettingP, string DefaultP)
{
  string* StoredSetting = GetSetting_string(SettingP);
  if (StoredSetting) {
    return StoredSetting[0];
  } else {
    return DefaultP;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Int settings
////////////////////////////////////////////////////////////////////////////////////

bool SettingsManager::StoreSetting_int(vector<string> TokenP)
{
  HashEntry* Retrieved = Hash_int.GetEntry(TokenP[2]);
  int SettingSize = ((int*) Hash_SettingSize.GetEntry(TokenP[2])->GetContent())[0];
  if (Retrieved) {
    Log.Message("IN-003");
  }
  void* ToPut = malloc(sizeof (double) * SettingSize);
  for (int i = 0; i < SettingSize; i++) {
    ((double*) ToPut)[i] = IStringToDouble(TokenP[3 + i]);
  }
  return Hash_int.PutEntry(TokenP[2], ToPut, SettingSize, true);
}

int* SettingsManager::GetSetting_int(string SettingP)
{
  DataType SettingType = GetSettingType(SettingP);
  int SettingSize = GetSettingSize(SettingP);
  if (SettingSize > 0 && SettingType != Data_null) {
    if (SettingType == Data_int) {
      HashEntry* Retrieved = Hash_int.GetEntry(SettingP);
      if (!Retrieved || !Retrieved->GetValid()) {
        return NULL;
      } else {
        if (Retrieved->GetCount() != SettingSize) {
          Log.Message("DV-007");
          return NULL;
        } else {
          return (int*) Retrieved->GetContent();
        }
      }
    } else {
      Log.Message("DV-006: " + SettingP + " as Data_int");
      return NULL;
    }
  } else {
    Log.Message("DV-005: " + SettingP);
    return NULL;
  }
}

int SettingsManager::GetSingleSetting_int(string SettingP, int DefaultP)
{
  int* StoredSetting = GetSetting_int(SettingP);
  if (StoredSetting) {
    return StoredSetting[0];
  } else {
    return DefaultP;
  }
}

int SettingsManager::GetSingleSettingSafe_int(string SettingP, int DefaultP)
{
  if (GetSettingContent(SettingP)) {
    return GetSingleSetting_int(SettingP, DefaultP);
  } else {
    Log.Message("SD-037: " + SettingP);
    return DefaultP;
  }
}
