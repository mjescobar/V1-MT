
#ifndef HASHENTRY_H
#define	HASHENTRY_H

template <class EntryType> class HashEntry {
public:
  /**
   * Empty constructor
   */
  HashEntry();

  /**
   * Base constructor
   * @param KeyP     The entry key (it will be hashed inside)
   * @param ContentP The vector containing the data to store
   */
  HashEntry(string KeyP, vector<EntryType> ContentP);

  /**
   * Copy constructor
   * @param orig
   */
  HashEntry(const HashEntry& orig);

  /**
   * Destructor
   */
  virtual ~HashEntry();

  /**
   * Assignment operator
   * @param orig
   * @return 
   */
  HashEntry & operator=(const HashEntry& orig);

  /**
   * Returns the hashed key of the instance
   * @param HashKeyP
   * @return 
   */
  ReturnType GetHashKey(unsigned int &HashKeyP);

  /**
   * Returns the full stored key fo the instance
   * @param KeyP
   * @return 
   */
  ReturnType GetKey(string &KeyP);

  /**
   * Returns the amount of elements stored in the content vector
   * @param CountP
   * @return 
   */
  ReturnType GetCount(int &CountP);

  /**
   * Returns the vector content
   * @param ContentP
   * @return 
   */
  ReturnType GetContent(vector<EntryType> &ContentP);

private:
  string            Key;
  unsigned int      HashKey;
  vector<EntryType> Content;
} ;

#endif
