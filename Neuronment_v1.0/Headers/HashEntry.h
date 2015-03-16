/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef HASHENTRY_H
#define	HASHENTRY_H

class HashEntry {
public:
    /**
     * Creates an empty HashEntry
     */
    HashEntry();

    /**
     * Copy a HashEntry
     * @param orig The original HashEntry
     */
    HashEntry(const HashEntry& orig);

    /**
     * HashEntry default destructor
     */
    virtual ~HashEntry();

    /**
     * HashEntry standard constructor
     * @param KeyP The string key
     * @param TypeP The HashEntry data type
     * @param ContentP The pointer to the content to be stored
     * @param CountP The size of elements on the content pointer
     * @param ValidP Sets if the content can be read
     */
    HashEntry(string KeyP, DataType TypeP, void* ContentP, int CountP, bool ValidP);

    /**
     * Returns the HashEntry Hash Key
     * @return the key
     */
    unsigned int GetHashKey();

    /**
     * Returns the string key
     * @return the key
     */
    string GetKey();

    /**
     * Returns the amount of elements on the content
     * @return The amount of elements
     */
    int GetCount();

    /**
     * Returns the pointer to the content
     * @return The pointer to the content
     */
    void* GetContent();

    /**
     * Returns if the content is ready for reading
     * @return The content validity
     */
    bool GetValid();

private:
    string Key;
    unsigned int HashKey;
    DataType Type;
    void* Content;
    int Count;
    bool Valid;
};

#endif	/* HASHENTRY_H */
