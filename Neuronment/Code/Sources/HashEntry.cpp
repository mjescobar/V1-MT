
#include "tools.h"
#include "HashEntry.h"

template <class EntryType> HashEntry<EntryType>::HashEntry()
{
  Key = "";
  HashKey = 0;
  Content.empty();
  //Lothar: should be asserted?
}

template <class EntryType> HashEntry<EntryType>::HashEntry(string KeyP, vector<EntryType> ContentP)
{
  unsigned int HashKeyP;
  KeyToHashKey(KeyP, HashKeyP);
  Key = KeyP;
  HashKey = HashKeyP;
  Content = ContentP;
}

template <class EntryType> HashEntry<EntryType>::HashEntry(const HashEntry& orig)
{
  Key = orig.Key;
  HashKey = orig.HashKey;
  Content = orig.Content;
}

template <class EntryType> HashEntry<EntryType>::~HashEntry()
{
}

template <class EntryType> HashEntry<EntryType> & HashEntry<EntryType>::operator=(const HashEntry<EntryType>& orig)
{
  Key = orig.Key;
  HashKey = orig.HashKey;
  Content = orig.Content;
  return *this;
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetKey(string &KeyP)
{
  KeyP = Key;
  return Return(ReturnSuccess);
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetHashKey(unsigned int &HashKeyP)
{
  HashKeyP = HashKey;
  return Return(ReturnSuccess);
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetCount(int &CountP)
{
  CountP = Content.size();
  return Return(ReturnSuccess);
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetContent(vector<EntryType> &ContentP)
{
  ContentP = Content;
  return Return(ReturnSuccess);
}

template class HashEntry<int>;
template class HashEntry<bool>;
template class HashEntry<void*>;
template class HashEntry<double>;
template class HashEntry<string>;
