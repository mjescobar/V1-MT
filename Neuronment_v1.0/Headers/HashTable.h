/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

class HashTable {
public:
    /**
     * Null HashTable constructor
     */
    HashTable();

    /**
     * Copy HashTable
     * @param orig Original HashTable
     */
    HashTable(const HashTable& orig);

    /**
     * Destructor
     */
    virtual ~HashTable();

    /**
     * Initialize HashTable
     * @param TableTypeP Type of data to store
     * @param HashSizeP Max amount of elements in the table
     */
    HashTable(DataType TableTypeP, int HashSizeP);

    /**
     * Stores a new HashEntry
     * @param KeyP Key string
     * @param ContentP Pointer to the content to store
     * @param CountP Number of elements on the content
     * @param ValidP True if data valid to retreive
     * @return True if correctly put
     */
    bool PutEntry(string KeyP, void* ContentP, int CountP, bool ValidP);

    /**
     * Returns the entry stored on the table
     * @param KeyP The key to look for
     * @return The pointer to the entry, NULL if not found
     */
    HashEntry* GetEntry(string KeyP);

    /**
     * To quick storage of a single double value
     * @param KeyP The key for retreive
     * @param ValueP The value to store
     * @return true if succesful
     */
    bool QuickPutEntry_double(string KeyP, double ValueP);

    /**
     * 
     * @param KeyP
     * @param ValueP
     * @return 
     */
    bool QuickPutEntry_bool(string KeyP, bool ValueP);

    /**
     * Returns the entry stored on the table
     * @param KeyP The key to look for
     * @return The pointer to the entry, NULL if not found
     */
    double QuickGetEntry_double(string KeyP);

    /**
     * 
     * @param KeyP
     * @return 
     */
    int QuickGetEntry_int(string KeyP);

    /**
     * 
     * @param KeyP
     * @return 
     */
    bool QuickUpdateEntry_int(string KeyP, int ValueP);

    /**
     * 
     * @param KeyP
     * @return 
     */
    bool QuickGetEntry_bool(string KeyP);

    /**
     * 
     * @param KeyP
     * @return 
     */
    string QuickGetEntry_string(string KeyP);

    /**
     * 
     * @param KeyP
     * @param ValueP
     * @return 
     */
    bool QuickPutEntry_string(string KeyP, string ValueP);

    /**
     * 
     * @param KeyP
     * @param ValueP
     * @return 
     */
    bool QuickPutEntry_int(string KeyP, int ValueP);

    /**
     * 
     * @param KeyP
     * @param FunctionP
     * @return 
     */
    bool QuickPutEntry_function(string KeyP, void* FunctionP);

private:
    int HashSize;
    DataType TableType;
    HashEntry **Table;
};

#endif	/* HASHTABLE_H */
