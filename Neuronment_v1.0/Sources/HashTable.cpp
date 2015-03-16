/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;
#include "enum.h"
#include "define.h"
#include "HashEntry.h"
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "SettingsManager.h"
#include "Globals.h"
#include "HashTable.h"

HashTable::HashTable()
{
  TableType = Data_null;
  Table = NULL;
}

HashTable::HashTable(const HashTable& orig)
{
  Table = new HashEntry*[HASH_SIZE];
  for (int i = 0; i < HASH_SIZE; i++) {
    if (orig.Table[i] != NULL) {
      Table[i] = new HashEntry();
      Table[i] = orig.Table[i];
    } else {
      Table[i] = NULL;
    }
  }
  TableType = orig.TableType;
}

HashTable::~HashTable()
{
  if (Table) {
    for (int i = 0; i < HASH_SIZE; i++) {
      if (Table[i] != NULL) {
        delete Table[i];
        Table[i] = NULL;
      }
    }
    Table = NULL;
  }
}

HashTable::HashTable(DataType TableTypeP)
{
  TableType = TableTypeP;
  Table = new HashEntry*[HASH_SIZE];
  for (int i = 0; i < HASH_SIZE; i++) {
    Table[i] = NULL;
  }
}

bool HashTable::PutEntry(string KeyP, void* ContentP, int CountP, bool ValidP)
{
  unsigned int HashKeyP = HashString(KeyP);
  int Index = HashKeyP % HASH_SIZE;
  while (Table[Index] != NULL && Table[Index]->GetKey() != KeyP) {
    Index = (Index + 1) % HASH_SIZE;
    if (Index == HashKeyP % HASH_SIZE) {
      Log.Message("DV-013");
      return false;
    }
  }
  if (Table[Index] != NULL) {
    delete Table[Index];
  }
  Table[Index] = new HashEntry(KeyP, TableType, ContentP, CountP, ValidP);
  return true;
}

HashEntry* HashTable::GetEntry(string KeyP)
{
  unsigned int HashKeyP = HashString(KeyP);
  int Index = HashKeyP % HASH_SIZE;
  while (Table[Index] != NULL && Table[Index]->GetKey() != KeyP) {
    Index = (Index + 1) % HASH_SIZE;
    if (Index == HashKeyP % HASH_SIZE) {
      return NULL;
    }
  }
  if (Table[Index] == NULL) {
    return NULL;
  } else {
    return Table[Index];
  }
}

bool HashTable::QuickPutEntry_double(string KeyP, double ValueP)
{
  if (TableType == Data_double) {
    void* Content = malloc(sizeof (double));
    ((double*) Content)[0] = ValueP;
    return PutEntry(KeyP, Content, 1, true);
  } else {
    Log.Message("DV-012");
    return false;
  }
}

bool HashTable::QuickPutEntry_bool(string KeyP, bool ValueP)
{
  if (TableType == Data_bool) {
    void* Content = malloc(sizeof (bool));
    ((bool*) Content)[0] = ValueP;
    return PutEntry(KeyP, Content, 1, true);
  } else {
    Log.Message("DV-012");
    return false;
  }
}

double HashTable::QuickGetEntry_double(string KeyP)
{
  if (TableType != Data_double) {
    Log.Message("DV-012");
    return 0;
  }
  HashEntry* Retreived = GetEntry(KeyP);
  if (!Retreived) {
    Log.Message("DV-018");
    return 0;
  }
  return ((double*) Retreived->GetContent())[0];
}

int HashTable::QuickGetEntry_int(string KeyP)
{
  if (TableType != Data_int) {
    Log.Message("DV-012");
    return 0;
  }
  HashEntry* Retreived = GetEntry(KeyP);
  if (!Retreived) {
    Log.Message("DV-018");
    return 0;
  }
  return ((int*) Retreived->GetContent())[0];
}

bool HashTable::QuickUpdateEntry_int(string KeyP, int ValueP)
{
  if (TableType != Data_int) {
    Log.Message("DV-012");
    return false;
  }
  HashEntry* Retreived = GetEntry(KeyP);
  if (!Retreived) {
    Log.Message("DV-018");
    return false;
  }
  ((int*) Retreived->GetContent())[0] = ValueP;
  return true;
}

bool HashTable::QuickGetEntry_bool(string KeyP)
{
  if (TableType != Data_bool) {
    Log.Message("DV-012");
    return false;
  }
  HashEntry* Retreived = GetEntry(KeyP);
  if (!Retreived) {
    Log.Message("DV-018");
    return false;
  }
  return ((bool*) Retreived->GetContent())[0];
}

string HashTable::QuickGetEntry_string(string KeyP)
{
  if (TableType != Data_string) {
    Log.Message("DV-012");
    return "";
  }
  HashEntry* Retreived = GetEntry(KeyP);
  if (!Retreived) {
    Log.Message("DV-018");
    return "";
  }
  return ((string*) Retreived->GetContent())[0];
}

bool HashTable::QuickPutEntry_string(string KeyP, string ValueP)
{
  if (TableType == Data_string) {
    void* ToPut = malloc(sizeof (string));
    new (&((string*) ToPut)[0]) std::string(ValueP);
    return PutEntry(KeyP, ToPut, 1, true);
  } else {
    Log.Message("DV-012");
    return false;
  }
}

bool HashTable::QuickPutEntry_int(string KeyP, int ValueP)
{
  if (TableType == Data_int) {
    void* Content = malloc(sizeof (int));
    ((int*) Content)[0] = ValueP;
    return PutEntry(KeyP, Content, 1, true);
  } else {
    Log.Message("DV-012");
    return false;
  }
}

bool HashTable::QuickPutEntry_function(string KeyP, void* FunctionP)
{
  if (TableType == Data_function) {
    return PutEntry(KeyP, FunctionP, 1, true);
  } else {
    Log.Message("DV-012");
    return false;
  }
}