
#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "tools.h"
#include "HashEntry.h"

template <class TableType> class HashTable {
public:
  /**
   * Empty constructor
   */
  HashTable();
  
  /**
   * Constructs a table considering the indicated size amount of slots
   * @param SizeP
   */
  HashTable(int SizeP);
  
  /**
   * Copy constructor
   * @param orig
   */
  HashTable(const HashTable& orig);
  
  /**
   * Destructor
   */
  virtual ~HashTable();
  
  /**
   * Assignment operator
   * @param orig
   * @return 
   */
  HashTable & operator=(const HashTable & orig);
  
  /**
   * Puts the specified content vector  inside the table. If the key already 
   * exists, the content is replaced
   * @param KeyP     Key for the element
   * @param ContentP Content to store
   * @return
   */
  ReturnType PutEntry(string KeyP, vector<TableType> ContentP);
  
  /**
   * Puts the specified content value in a single element vector content for the
   * key. If the element exists it will be replaced.
   * @param KeyP    Key for the element
   * @param Content Content to store
   * @return
   */
  ReturnType PutEntryQuick(string KeyP, TableType Content);
  
  /**
   * Returns the entry vector content for the specified key. If the key doesn't
   * exists a ReturnFail is returned
   * @param KeyP     Key of the element
   * @param ContentP Content destination
   * @return         Not caught
   */
  ReturnType GetEntry(string KeyP, vector<TableType> &ContentP);
  
  /**
   * Returns the first element of the vector content for the specified key. If
   * it doesn't exists returns ReturnFail
   * @param KeyP     Key of the element
   * @param ContentP Content destination
   * @return
   */
  ReturnType GetEntryQuick(string KeyP, TableType &ContentP);

  /**
   * Deletes the content of the hash table
   * @return
   */
  ReturnType Clear();
  
private:
  /**
   * Checks if the key of the index corresponds
   * @param IndexP Index to check
   * @param KeyP   Key to validate
   * @return       true if corresponds
   */
  bool IndexChecking(int IndexP, string KeyP);
  
  int                    Size;
  int                    Counter;
  HashEntry<TableType> **Table;
};

#endif
