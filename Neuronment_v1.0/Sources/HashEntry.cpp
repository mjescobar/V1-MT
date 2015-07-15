/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 2.0
 */

#include "tools.h"
#include "HashEntry.h"

template <class EntryType> HashEntry<EntryType>::HashEntry()
{
  Key = "";
  HashKey = 0;
  Content.empty();
}

template <class EntryType> HashEntry<EntryType>::HashEntry(string KeyP, vector<EntryType> ContentP)
{
  unsigned int HashKeyP;
  ReturnCatch(KeyToHashKey(KeyP, HashKeyP));
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

template <class EntryType> ReturnType HashEntry<EntryType>::GetKey(string &KeyP)
{
  KeyP = Key;
  return ReturnSuccess;
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetHashKey(unsigned int &HashKeyP)
{
  HashKeyP = HashKey;
  return ReturnSuccess;
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetCount(int &CountP)
{
  CountP = Content.size();
  return ReturnSuccess;
}

template <class EntryType> ReturnType HashEntry<EntryType>::GetContent(vector<EntryType> &ContentP)
{
  ContentP = Content;
  return ReturnSuccess;
}

template class HashEntry<int>;
template class HashEntry<bool>;
template class HashEntry<void*>;
template class HashEntry<double>;
template class HashEntry<string>;
