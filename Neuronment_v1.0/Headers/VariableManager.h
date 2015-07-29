
#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>
using namespace std;
#include "HashTable.h"
#include "enum.h"

class VariableManager {
public:
    VariableManager();
    VariableManager(const VariableManager& orig);
    virtual ~VariableManager();
    ReturnType SetSettingFromString(string VariableP, string TypeP, string ValueP);
    ReturnType GetSettingAsString(string VariableP, string &VariableValue);
    template <class VariableType> ReturnType SetSetting(string VariableP, vector<VariableType> &ValueP);
    template <class VariableType> ReturnType GetSetting(string VariableP, vector<VariableType> &ValueP);
private:
    ReturnType IsValidType(string TypeP);
    template <class VariableType> ReturnType CheckUnicity(HashTable<VariableType> *LocalTableP, string VariableP);
    ReturnType GetHashTable(int DummyP, HashTable<int> **HashTableP);
    ReturnType GetHashTable(bool DummyP, HashTable<bool> **HashTableP);
    ReturnType GetHashTable(double DummyP, HashTable<double> **HashTableP);
    ReturnType GetHashTable(string DummyP, HashTable<string> **HashTableP);
    HashTable<int> HashInt;
    HashTable<bool> HashBool;
    HashTable<double> HashDouble;
    HashTable<string> HashString;
};

#endif /* VARIABLEMANAGER_H */
