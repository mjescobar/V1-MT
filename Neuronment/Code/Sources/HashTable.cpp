
#include "tools.h"
#include "HashTable.h"
#include "extern.h"

template <class TableType> HashTable<TableType>::HashTable()
{
  Size = 0;
  Counter = 0;
  Table = NULL;
}

template <class TableType> HashTable<TableType>::HashTable(int SizeP)
{
  ReturnCatch(DataCheck(SizeP, "GreaterThanZero"));
  Size = SizeP * HASH_TABLE_MARGIN*HASH_TABLE_MARGIN;
  Counter = 0;
  Table = new HashEntry<TableType>*[Size];
  for (int i = 0; i < Size; i++) {
    Table[i] = NULL;
  }
}

template <class TableType> HashTable<TableType>::HashTable(const HashTable& orig)
{
  ReturnCatch(DataCheck(orig.Size, "GreaterThanZero"));
  Size = orig.Size;
  Counter = orig.Counter;
  Table = new HashEntry<TableType>*[Size];
  for (int i = 0; i < Size; i++) {
    if (orig.Table[i] != NULL) {
      Table[i] = new HashEntry<TableType>;
      *(Table[i]) = *(orig.Table[i]);
    } else {
      Table[i] = NULL;
    }
  }
}

template <class TableType> HashTable<TableType>::~HashTable()
{
  if (Table) {
    for (int i = 0; i < Size; i++) {
      if (Table[i] != NULL) {
        delete Table[i];
        Table[i] = NULL;
      }
    }
    delete Table;
    Table = NULL;
  }
}

template <class TableType> HashTable<TableType> & HashTable<TableType>::operator=(const HashTable<TableType>& orig)
{
  if (Table) {
    for (int i = 0; i < Size; i++) {
      if (Table[i] != NULL) {
        delete Table[i];
        Table[i] = NULL;
      }
    }
    delete Table;
    Table = NULL;
  }
  Size = orig.Size;
  Counter = orig.Counter;
  Table = new HashEntry<TableType>*[Size];
  for (int i = 0; i < Size; i++) {
    if (orig.Table[i] != NULL) {
      Table[i] = new HashEntry<TableType>;
      *(Table[i]) = *(orig.Table[i]);
    } else {
      Table[i] = NULL;
    }
  }
  return *this;
}

template <class TableType> ReturnType HashTable<TableType>::PutEntry(string KeyP, vector<TableType> ContentP)
{
  // If adding a new element requires a table resizing
  if (Counter + 1 > Size / HASH_TABLE_MARGIN) {
    // Creating resizing required variables
    double OldSize;
    HashEntry<TableType> **OldTable;
    // Storing old table values
    OldSize = Size;
    OldTable = Table;
    // Resetting values for resized table
    Counter = 0;
    Size = Size*HASH_TABLE_MARGIN;
    Table = new HashEntry<TableType>*[Size];
    for (int i = 0; i < Size; i++) {
      Table[i] = NULL;
    }
    // Filling resized table with old values
    for (int i = 0; i < OldSize; i++) {
      if (OldTable[i] != NULL) {
        // Creating entry retrieve variables
        string Key;
        vector<TableType> Content;
        // Retrieving old entry values
        ReturnCatch(OldTable[i]->GetKey(Key));
        ReturnCatch(OldTable[i]->GetContent(Content));
        // Adding values to the new table;
        PutEntry(Key, Content);
        delete OldTable[i];
        OldTable[i] = NULL;
      }
    }
    delete OldTable;
    OldTable = NULL;
  }
  // Adding new entry
  // Declaring temporal variables
  int Index;
  bool IndexOk;
  unsigned int HashKeyP;
  // Inserting new entry
  ReturnCatch(KeyToHashKey(KeyP, HashKeyP));
  Index = HashKeyP % Size;
  IndexOk = IndexChecking(Index, KeyP);
  while (IndexOk) {
    Index = (Index + 1) % Size;
    IndexOk = IndexChecking(Index, KeyP);
  }
  if (Table[Index] != NULL) {
    delete Table[Index];
    Table[Index] = NULL;
    Counter--;
  }
  Table[Index] = new HashEntry<TableType>(KeyP, ContentP);
  Counter++;
  return ReturnSuccess;
}

template <class TableType> ReturnType HashTable<TableType>::PutEntryQuick(string KeyP, TableType ContentP)
{
  vector<TableType> Temporal;
  Temporal.push_back(ContentP);
  ReturnCatch(PutEntry(KeyP, Temporal));
  return ReturnSuccess;
}

template <class TableType> ReturnType HashTable<TableType>::GetEntry(string KeyP, vector<TableType> &ContentP)
{
  // Declaring temporal variables
  int Index;
  bool IndexOk;
  unsigned int HashKey;
  // Calculating the key index
  ReturnCatch(KeyToHashKey(KeyP, HashKey));
  Index = HashKey % Size;
  IndexOk = IndexChecking(Index, KeyP);
  while (IndexOk) {
    Index = (Index + 1) % Size;
    IndexOk = IndexChecking(Index, KeyP);
  }
  if (Table[Index] == NULL) {
    return ReturnFail;
  } else {
    ReturnCatch(Table[Index]->GetContent(ContentP));
    return ReturnSuccess;
  }
}

template <class TableType> ReturnType HashTable<TableType>::GetEntryQuick(string KeyP, TableType &ContentP)
{
  vector<TableType> Temporal;
  if (GetEntry(KeyP, Temporal) == ReturnFail) {
    return ReturnFail;
  } else {
    ContentP = Temporal[0];
    if (Temporal.size() != 1) {
      DevelopmentAssertion();
      return ReturnSuccessWarning;
    }
    return ReturnSuccess;
  }
}

template <class TableType> ReturnType HashTable<TableType>::Clear()
{
  if (Table) {
    for (int i = 0; i < Size; i++) {
      if (Table[i] != NULL) {
        delete Table[i];
        Table[i] = NULL;
      }
    }
  }
  return ReturnSuccess;
}

////////////////////////////////////////////////////////////////////////////////////
// Internals
////////////////////////////////////////////////////////////////////////////////////

template <class TableType> bool HashTable<TableType>::IndexChecking(int IndexP, string KeyP)
{
  string Key;
  if (Table[IndexP] == NULL) {
    return false;
  } else {
    ReturnCatch(Table[IndexP]->GetKey(Key));
    if (Key == KeyP) {
      return false;
    } else {
      return true;
    }
  }
}

template class HashTable<int>;
template class HashTable<bool>;
template class HashTable<void*>;
template class HashTable<double>;
template class HashTable<string>;
