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
#include "Tools.h"
#include "HashEntry.h"
#include "HashTable.h"
#include "LogManager.h"
#include "Globals.h"

HashEntry::HashEntry()
{
  Key = "";
  HashKey = 0;
  Type = Data_null;
  Content = NULL;
  Count = 0;
  Valid = false;
}

HashEntry::HashEntry(const HashEntry& orig)
{
  Key = orig.Key;
  HashKey = orig.HashKey;
  Type = orig.Type;
  Content = DuplicateArray(Content, Count, Type);
  Count = orig.Count;
  Valid = orig.Valid;
}

HashEntry::~HashEntry()
{
  if (Type == Data_string) {
    for (int i = 0; i < Count; i++) {
      (&((string*) Content)[i])->~string();
    }
  }
  if (Type != Data_function) {
    free(Content);
  }
}

HashEntry::HashEntry(string KeyP, DataType TypeP, void* ContentP, int CountP, bool ValidP)
{
  Key = KeyP;
  HashKey = HashString(KeyP);
  Type = TypeP;
  Content = ContentP;
  Count = CountP;
  Valid = ValidP;
}

unsigned int HashEntry::GetHashKey()
{
  return HashKey;
}

string HashEntry::GetKey()
{
  return Key;
}

int HashEntry::GetCount()
{
  return Count;
}

void* HashEntry::GetContent()
{
  return Content;
}

bool HashEntry::GetValid()
{
  return Valid;
}
