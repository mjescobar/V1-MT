
#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>
using namespace std;
#include "HashTable.h"
#include "enum.h"

class VariableManager {
public:
  /**
   * Empty constructor
   */
  VariableManager();

  /**
   * Copy constructor
   * @param orig
   */
  VariableManager(const VariableManager& orig);

  /**
   * Destructor
   */
  virtual ~VariableManager();

  /**
   * Sets a setting from a string
   * @param VariableP The name of the variable to set
   * @param TypeP     The type fo the variable to set
   * @param ValueP    The value to set, it will be processed as a list separated by spaces
   * @return 
   */
  ReturnType SetSettingFromString(string VariableP, string TypeP, string ValueP);

  /**
   * Returns the value of a setting as a string
   * @param VariableP     The variable to retrieve
   * @param VariableValue Pointer to return the value
   * @return 
   */
  ReturnType GetSettingAsString(string VariableP, string &VariableValue);

  /**
   * Sets a variable value from a data type specific vector
   * @param VariableP The variable to store the value
   * @param ValueP    The vector containing the values to store
   * @return 
   */
  template <class VariableType> ReturnType SetSetting(string VariableP, vector<VariableType> &ValueP);

  /**
   * Returns a vector containing the variable values
   * @param VariableP The name of the variable
   * @param ValueP    Pointer to return the vector of values
   * @return 
   */
  template <class VariableType> ReturnType GetSetting(string VariableP, vector<VariableType> &ValueP);

  /**
   * Returns the first value of the vector of values stored by a variable
   * @param VariableP The variable name
   * @param ValueP    Pointer to return the value
   * @return 
   */
  template <class VariableType> ReturnType GetSetting(string VariableP, VariableType &ValueP);

private:
  /**
   * Checks that the variable name doesn't exists on the specified table
   * @param LocalTableP The table in which the name should be searched
   * @param VariableP   The variable name to search for
   * @return 
   */
  template <class VariableType> ReturnType CheckUnicity(HashTable<VariableType> *LocalTableP, string VariableP);

  /**
   * Returns the int variable hash table
   * @param DummyP     Dummy to specify the data type
   * @param HashTableP Pointer to return the pointer to the type hash table
   * @return 
   */
  ReturnType GetHashTable(int DummyP, HashTable<int> **HashTableP);

  /**
   * Returns the bool variable hash table
   * @param DummyP     Dummy to specify the data type
   * @param HashTableP Pointer to return the pointer to the type hash table
   * @return 
   */
  ReturnType GetHashTable(bool DummyP, HashTable<bool> **HashTableP);

  /**
   * Returns the double variable hash table
   * @param DummyP     Dummy to specify the data type
   * @param HashTableP Pointer to return the pointer to the type hash table
   * @return 
   */
  ReturnType GetHashTable(double DummyP, HashTable<double> **HashTableP);

  /**
   * Returns the string variable hash table
   * @param DummyP     Dummy to specify the data type
   * @param HashTableP Pointer to return the pointer to the type hash table
   * @return 
   */
  ReturnType GetHashTable(string DummyP, HashTable<string> **HashTableP);

  HashTable<int> HashInt;
  HashTable<bool> HashBool;
  HashTable<double> HashDouble;
  HashTable<string> HashString;
};

#endif
