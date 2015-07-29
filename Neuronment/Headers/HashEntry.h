/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 2.0
 */

#ifndef HASHENTRY_H
#define	HASHENTRY_H

template <class EntryType> class HashEntry {
public:
  HashEntry();
  HashEntry(string KeyP, vector<EntryType> ContentP);
  HashEntry(const HashEntry& orig);
  virtual ~HashEntry();
  ReturnType GetHashKey(unsigned int &HashKeyP);
  ReturnType GetKey(string &KeyP);
  ReturnType GetCount(int &CountP);
  ReturnType GetContent(vector<EntryType> &ContentP);
private:
  string Key;
  unsigned int HashKey;
  vector<EntryType> Content;
};

#endif	/* HASHENTRY_H */
