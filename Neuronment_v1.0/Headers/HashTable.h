/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 2.0
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "tools.h"
#include "HashEntry.h"

template <class TableType> class HashTable {
public:
  HashTable();
  HashTable(int SizeP);
  HashTable(const HashTable& orig);
  virtual ~HashTable();
  ReturnType PutEntry(string KeyP, vector<TableType> ContentP);
  ReturnType PutEntryQuick(string KeyP, TableType Content);
  ReturnType GetEntry(string KeyP, vector<TableType> &ContentP);
  ReturnType GetEntryQuick(string KeyP, TableType &ContentP);
  ReturnType Clear();
private:
  bool IndexChecking(int IndexP, string KeyP);
  int Size;
  int Counter;
  HashEntry<TableType> **Table;
};

#endif	/* HASHTABLE_H */
