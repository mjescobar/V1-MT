/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef SETTINGSMANAGER_H
#define	SETTINGSMANAGER_H

class SettingsManager {
public:
    /**
     * Standard constructor
     */
    SettingsManager();

    /**
     * Copy constructor
     * @param orig original instance
     */
    SettingsManager(const SettingsManager& orig);

    /**
     * Standard destructor
     */
    virtual ~SettingsManager();

    /**
     * Configures the manager to knowledge a new possible setting
     * @param SettingP The setting name
     * @param TypeP The setting type
     * @param SizeP The number of parameters for the setting
     * @return True if success
     */
    bool SetSetting(string SettingP, DataType TypeP, int SizeP);

    /**
     * Returns the setting size for a setting
     * @param KeyP the setting key
     * @return The size
     */
    int GetSettingSize(string KeyP);

    /**
     * Returns the setting DataType for a setting
     * @param KeyP the setting key
     * @return The DataType
     */
    DataType GetSettingType(string KeyP);

    /**
     * Returns if the setting is valid to retrieve
     * @param KeyP The setting key
     * @return true if valid
     */
    bool GetSettingValid(string KeyP);

    /**
     * Returns the full content stored for a setting
     * @param KeyP The setting key
     * @return The content array
     */
    void* GetSettingContent(string KeyP);

    /**
     * Returns the full content stored for a setting, error if key not found
     * @param KeyP The setting key
     * @return The content array
     */
    void* GetSettingContentSafe(string KeyP);

    /**
     * Stores the Tokens as setting information
     * @param TokenP the tokenized nproc file line
     * @return true if successful
     */
    bool StoreSetting(vector<string> TokenP);

    ////////////////////////////////////////////////////////////////////////////////////
    // Boolean settings
    ////////////////////////////////////////////////////////////////////////////////////

    /**
     * Stores a boolean setting
     * @param TokenP The tokenized nproc file line
     * @return true if successfully stored, false otherwise
     */
    bool StoreSetting_bool(vector<string> TokenP);

    /**
     * Gets a boolean settings array
     * @param SettingP the setting key
     * @return the pointer to the setting array, null if not available
     */
    bool* GetSetting_bool(string SettingP);

    /**
     * Gets the first boolean value stored on a boolean variable setting
     * @param SettingP the setting key
     * @param DefaultP the value if setting not available
     * @return The boolean value stored, default if not available
     */
    bool GetSingleSetting_bool(string SettingP, bool DefaultP);

    ////////////////////////////////////////////////////////////////////////////////////
    // Double settings
    ////////////////////////////////////////////////////////////////////////////////////

    /**
     * Stores a double setting
     * @param TokenP The tokenized nproc file line
     * @return true if successfully stored, false otherwise
     */
    bool StoreSetting_double(vector<string> TokenP);

    /**
     * Gets a double settings array
     * @param SettingP The setting key
     * @return the pointer to the double array
     */
    double* GetSetting_double(string SettingP);

    /**
     * Gets the first double from the double array
     * @param SettingP the setting to get the double
     * @param DefaultP the default value if not found
     * @return The double value
     */
    double GetSingleSetting_double(string SettingP, double DefaultP);

    /**
     * Gets the first double from the double array, runtime error if not found
     * @param SettingP the setting to get the double
     * @param DefaultP the default value if not found
     * @return The double value
     */
    double GetSingleSettingSafe_double(string SettingP, double DefaultP);

    ////////////////////////////////////////////////////////////////////////////////////
    // String settings
    ////////////////////////////////////////////////////////////////////////////////////

    /**
     * Stores a double setting
     * @param TokenP The tokenized nproc file line
     * @return true if successfully stored, false otherwise
     */
    bool StoreSetting_string(vector<string> TokenP);

    /**
     * Gets a double settings array
     * @param SettingP The setting key
     * @return the pointer to the double array
     */
    string* GetSetting_string(string SettingP);

    /**
     * Gets the first double from the double array
     * @param SettingP the setting to get the double
     * @param DefaultP the default value if not found
     * @return The double value
     */
    string GetSingleSetting_string(string SettingP, string DefaultP);

    ////////////////////////////////////////////////////////////////////////////////////
    // Int settings
    ////////////////////////////////////////////////////////////////////////////////////

    /**
     * Stores a int setting
     * @param TokenP The tokenized nproc file line
     * @return true if successfully stored, false otherwise
     */
    bool StoreSetting_int(vector<string> TokenP);

    /**
     * Gets a int settings array
     * @param SettingP The setting key
     * @return the pointer to the double array
     */
    int* GetSetting_int(string SettingP);

    /**
     * Gets the first int from the double array
     * @param SettingP the setting to get the double
     * @param DefaultP the default value if not found
     * @return The double value
     */
    int GetSingleSetting_int(string SettingP, int DefaultP);

    /**
     * Gets the first int from the double array, runtime error if not found
     * @param SettingP the setting to get the double
     * @param DefaultP the default value if not found
     * @return The double value
     */
    int GetSingleSettingSafe_int(string SettingP, int DefaultP);

    /**
     * Loads variable list
     */
    void InitializeVariables();

private:
    HashTable Hash_bool;
    HashTable Hash_int;
    HashTable Hash_float;
    HashTable Hash_double;
    HashTable Hash_string;
    HashTable Hash_SettingType;
    HashTable Hash_SettingSize;
};

#endif	/* SETTINGSMANAGER_H */
