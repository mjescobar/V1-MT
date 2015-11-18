
#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <vector>
using namespace std;
#include "enum.h"
#include "HashTable.h"
class Simulator;
#include "Neuron.h"
#include "VariableManager.h"

class Simulator {
public:
  /**
   * Empty constructor
   */
  Simulator();
  
  /**
   * Copy constructor
   * @param orig
   */
  Simulator(const Simulator& orig);
  
  /**
   * Destructor
   */
  virtual ~Simulator();
  
  /**
   * Adds a neuron to the simulator
   * @param NeuronTypeP      The type of the neuron to add
   * @param GroupP           The group name for the neuron to add
   * @param IdP              The id for the neuron to add
   * @param BaseActivationP  A base activation vector for the neuron to add
   * @param ParametersValueP A list of the parameters required to configure the neuron
   * @return 
   */
  ReturnType AddNeuron(NeuronType *NeuronTypeP, string GroupP, int IdP, string BaseActivationP, vector<string> ParametersValueP);
  
  /**
   * Returns a vector containing the pointers to all the neurons inside the simulator
   * @param NeuronsP Pointer to return the list
   * @return 
   */
  ReturnType GetNeurons(vector<Neuron*> &NeuronsP);
  
  /**
   * Returns a vector containing all the neurons that match the specified parameters.
   * If a parameter is empty, it is not considered in the exclusion process
   * @param NeuronsP Pointer to return the vector
   * @param IdP      ID to validate the neuron
   * @param TypeP    Neuron type to validate the neuron
   * @param GroupP   Neuron group name to validate the neuron
   * @return 
   */
  ReturnType GetNeurons(vector<Neuron*> &NeuronsP, string IdP, string TypeP, string GroupP);
  
  /**
   * Calculates the activation for all the neurons declared on the simulator
   * @return 
   */
  ReturnType Simulate();
  VariableManager InternalVariables;
private:
  vector<Neuron> Neurons;
} ;

#endif
