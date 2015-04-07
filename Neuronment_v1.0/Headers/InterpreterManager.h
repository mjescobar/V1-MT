/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef INTERPRETERMANAGER_H
#define	INTERPRETERMANAGER_H

class InterpreterManager {
public:
    /**
     * Default constructor
     */
    InterpreterManager();

    /**
     * Copy method
     * @param orig original instance
     */
    InterpreterManager(const InterpreterManager& orig);

    /**
     * Default destructor
     */
    virtual ~InterpreterManager();

    /**
     * Sets the name of the file to read
     * @param NprocP filename
     * @return true if stored correctly
     */
    bool SetNproc(string NprocP);

    /**
     * Opens nproc file for reading
     * @return true if successful
     */
    bool LoadFile();

    /**
     * Closes the file stream
     * @return true if closed correctly
     */
    bool CloseFile();

    /**
     * Controls the line by line file reading
     */
    void Process();

    /**
     * Initialize list of commands for interpretation
     */
    void InitializeInterpreter();

private:
    /**
     * Interprets the last red line and derives the values
     * for interpreters callers
     * @return true if successful
     */
    ResultType InterpretateLine();

    /**
     * Returns true if at the en of the file
     * @return true if at the end of the file
     */
    bool GetEndOfFileReached();

    /**
     * Goes to the next line on the file
     * @return true if successful
     */
    bool NextLine();

    /**
     * Takes charge of the setenv directives
     * @param TokensP tokens from the file line
     * @return true if successful
     */
    static bool SetenvCall(vector<string> TokensP);

    /**
     * Takes charge of the setsim directives
     * @param TokensP tokens from the file line
     * @return true if successful
     */
    static bool SetsimCall(vector<string> TokensP);

    /**
     * Takes charge of the runsim directives
     * @param TokensP tokens from the file line
     * @return true if successful
     */
    static bool RunsimCall(vector<string> TokensP);

    /**
     * Takes charge of the report directives
     * @param TokensP tokens from the file line
     * @return true if successful
     */
    static bool ReportCall(vector<string> TokensP);

    /**
     * Process "rescue nproc"
     * @param TokensP Tokenized command
     * @return true if successful
     */
    static bool RescueCall_NPROC(vector<string> TokensP);

    /**
     * Process "rescue return"
     * @param TokensP Tokenized command
     * @return true if successful
     */
    static bool RescueCall_RETURN(vector<string> TokensP);

    /**
     * Process "varman set"
     * @param TokensP Tokenized command
     * @return true if successful
     */
    static bool VarmanCall_SET(vector<string> TokensP);

    /**
     * Process "varman print"
     * @param TokensP Tokenized command
     * @return true if successful
     */
    static bool VarmanCall_PRINT(vector<string> TokensP);

    bool EndOfFileReached;
    bool ReadyForReading;
    string nproc;
    string LastLine;
    ifstream NprocStream;
    clock_t ElapsedTime;
    HashTable Commands;
};

#endif	/* INTERPRETERMANAGER_H */
