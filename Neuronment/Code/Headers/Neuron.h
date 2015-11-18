
#include <vector>
using namespace std;
#include "NeuronType.h"
#include "Simulator.h"

#ifndef NEURON_H
#define NEURON_H

class Neuron {
public:
  /**
   * Default constructor
   */
  Neuron();
  
  /**
   * Copy constructor
   * @param orig
   */
  Neuron(const Neuron& orig);
  
  /**
   * Destructor
   */
  virtual ~Neuron();
  
  /**
   * Main instance constructor
   * @param TypeP            Neuron type previously declared
   * @param GroupP           Name for the neuron group
   * @param IdP              A number as identifying ID
   * @param BaseActivationP  A vector containing the base activation for each activation
   * @param ParameterValuesP List of parameters required to configure the neuron
   */
  Neuron(NeuronType *TypeP, string GroupP, int IdP, vector<string> BaseActivationP, vector<string> ParameterValuesP);
  
  /**
   * Configures a link between the current instance and the specified neuron
   * @param NeuronP     The neuron to link to
   * @param ParametersP The list of parameters to use on the linking configuration
   * @return 
   */
  ReturnType AddLink(Neuron *NeuronP, vector<string> ParametersP);
  
  /**
   * Loads the activation for the full activation array
   * @param ExternalActivationP Vector containing the activation information
   * @return 
   */
  ReturnType LoadActivation(vector<vector<double> > ExternalActivationP);
  
  /**
   * Loads the activation for an specific activation level
   * @param ExternalActivationP Vector containing the activation information
   * @param LevelP              The lever where the information needs to be stored
   * @return 
   */
  ReturnType LoadActivation(vector<double> ExternalActivationP, int LevelP);
  
  /**
   * Calculates the activation for all the activation levels on a specific step
   * @param StepP Step to calculate the activations
   * @return 
   */
  ReturnType Calculate(int StepP);
  
  /**
   * Calculates the activation for an specific step and activation level
   * @param StepP  The step to calculate
   * @param LevelP The level to calculate
   * @return 
   */
  ReturnType Calculate(int StepP, int LevelP);
  
  /**
   * Returns the activation for an specific activationlevel and step
   * @param LevelP      Activation level to retrieve information
   * @param StepP       The step to retrieve the information
   * @param ActivationP Pointer to return the information
   * @return 
   */
  ReturnType GetActivation(int LevelP, int StepP, double &ActivationP);//Lothar: replicate for other data types
  
  /**
   * Returns the full activation array for the neuron
   * @param ActivationP Pointer to return the information
   * @return 
   */
  ReturnType GetActivation(vector<vector <double> > &ActivationP);
  
  /**
   * Inserts the specified value in the list of activations for an specific activation level
   * @param LevelP The activation level to store the activation value
   * @param ValueP The value to store
   * @return 
   */
  ReturnType ActivationPushBack(int LevelP, double ValueP); //Lothar check for other types
  
  /**
   * Returns a string stored neuron type parameter
   * @param NameP  The name of the parameter to retrieve
   * @param ValueP Pointer to return the value
   * @return 
   */
  ReturnType GetTypeParameter(string NameP, string &ValueP);
  
  /**
   * Returns a double stored neuron type parameter
   * @param NameP  The name of the parameter to retrieve
   * @param ValueP Pointer to return the value
   * @return 
   */
  ReturnType GetTypeParameter(string NameP, double &ValueP); //Lothar check for other types
  
  /**
   * Returns a double stored neuron link parameter 
   * @param LinkP  The link ID
   * @param NameP  The name of the parameter to retrieve
   * @param ValueP A pointer to return the value
   * @return 
   */
  ReturnType GetLinkParameter(int LinkP, string NameP, double &ValueP); //Lothar: replicar para diferentes data types
  
  /**
   * Returns the amount of links currently configured for the neuron
   * @param CountP Pointer to return the value
   * @return 
   */
  ReturnType GetLinksCount(int &CountP);
  
  /**
   * Returns a pointer to the neuron configured for an specific link ID
   * @param IndexP  The link ID to retrieve the information
   * @param NeuronP Pointer to return the linked neuron pointer
   * @return 
   */
  ReturnType GetLinksNeuron(int IndexP, Neuron* &NeuronP);
  
  /**
   * Returns the current count of elements for an specific activation level
   * @param LevelP The activation level to retrieve the information
   * @param SizeP  Pointer to return the valie
   * @return 
   */
  ReturnType GetActivationSize(int LevelP, int &SizeP);
  
  /**
   * Validates if the neuron ID corresponds to the specified neuron ID
   * @param IdP The neuron ID to validate
   * @return 
   */
  ReturnType IsId(string IdP);
  
  /**
   * Validates if the neuron group corresponds to the specified neuron group
   * @param GroupP The neuron group to validate
   * @return 
   */
  ReturnType IsGroup(string GroupP);
  
  /**
   * Validates if the neuron group corresponds to the specified neuron type
   * @param TypeP The neuron type name to validate
   * @return 
   */
  ReturnType IsType(string TypeP);
  
  /**
   * Prints to output the array of activation between the indicated limits (included)
   * @param FromP The lower array limit
   * @param ToP   The upper array limit
   * @return 
   */
  ReturnType PrintActivation(int FromP, int ToP);
  
  /**
   * Returns the neuron group name
   * @param GroupNameP Pointer to return the valie
   * @return 
   */
  ReturnType GetGroupName(string &GroupNameP);
  
  /**
   * Returns the neuron type name
   * @param TypeNameP Pointer to return the value
   * @return 
   */
  ReturnType GetTypeName(string &TypeNameP);
  
private:
  int Id;
  string Group;
  NeuronType *Type;
  vector<string> ParameterValues;
  vector<Neuron*> LinkingPointers;
  vector<vector<string> > LinkingParameters;
  vector<vector<double> > Activation_double;
  vector<vector<string> > LinkingParametersLabels;
} ;

#endif
