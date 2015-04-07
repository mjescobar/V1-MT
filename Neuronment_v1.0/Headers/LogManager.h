/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef LOGMANAGER_H
#define	LOGMANAGER_H

#include <vector>

class LogManager {
public:
    /**
     * Default constructor
     */
    LogManager();

    /**
     * Copy method
     * @param orig the original instance
     */
    LogManager(const LogManager& orig);

    /**
     * Default destructor
     */
    virtual ~LogManager();

    /**
     * Prints the program help for incorrect command call
     */
    void DisplayHelp();

    /**
     * Prints a table standardized message
     * @param IdP The message ID
     */
    void Message(string IdP);

    /**
     * Show a program header for program initialization
     */
    void DisplayHeader();

    /**
     * Shows a program footer at the end
     */
    void DisplayFooter();

    /**
     * Prints a development objective message
     * Not though for daily use
     * @param InfoP The message
     */
    void DevelopmentMessage(string InfoP, string PrefixP = ">", string TerminationP = "\n");

    /**
     * Manages the official output strings
     * @param OutputP The string to print
     */
    void Output(MessageType MessageTypeP, string OutputP);

    /**
     * Sets the standardized messages on
     */
    void SetMessages();

    /**
     * Unsets the standardized messages on
     */
    void UnsetMessages();

    /**
     * Silences the official output
     */
    void SetSilentOutput();

    /**
     * Un silences the official output
     */
    void UnsetSilentOutput();

    /**
     * Prints to output without line termination
     * @param OutputP the string to print
     */
    void OutputNNL(MessageType MessageTypeP, string OutputP);

    /**
     * Sets the output redirection file and opens it
     * @param DestinationP the path for redirecting
     */
    void StartOutputRedirection(string DestinationP);

    /**
     * Stops the redirection and closes the redirection file
     */
    void StopOutputRedirection();

    /**
     * Initialize the messages text
     * @return true if initialized correctly
     */
    void InitializeMessages();

private:
    bool Messages;
    bool SilentOutput;
    int RedirectionLevel;
    vector<ofstream*> Redirection;
    HashTable MessagesLabel; //Stores the short messages text
    HashTable MessagesText; //Stores a message full text for man proposes
    HashTable MessagesDisabling; //Maximum number of message apparitions
    HashTable MessagesCount; //Counter of message apparitions
    HashTable MessagesDevelopmentAssert; //Stores info if the message should Development Assert
    HashTable MessagesRuntimeAssert; //Stores info if the message should runtime assert
    HashTable MessagesImplementationAssert; //Stores info if the message should implementation assert
};

#endif	/* LOGMANAGER_H */
