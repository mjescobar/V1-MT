
#include <string>
#include <vector>
using namespace std;
#include "enum.h"
#include "NeuronType.h"
#include "Simulator.h"

#ifndef SIMULATORMANAGER_H
#define SIMULATORMANAGER_H

class SimulatorManager {
public:
  /**
   * Empty constructor
   */
  SimulatorManager();
  
  /**
   * Copy constructor
   * @param orig
   */
  SimulatorManager(const SimulatorManager& orig);
  
  /**
   * Destructor
   */
  virtual ~SimulatorManager();
  
  /**
   * Returns the current simulator in use
   * @return A pointer to the current simulator
   */
  Simulator* CurrentSimulator();
  
  /**
   * Returns a specific simulator identified by its id
   * @param IdP The simulator ID
   * @return    A pointer to the specified simulator
   */
  Simulator* GetSimulator(int IdP);
  
  /**
   * Adds an empty simulator to the manager
   * @return 
   */
  ReturnType AddSimulator();
  
  /**
   * Removes the specified simulator from the manager
   * @param SimulatorIdP The id of the simulator to remove
   * @return 
   */
  ReturnType RemoveSimulator(int SimulatorIdP);
  
  /**
   * Changes the current simulator to the specified ID
   * @param SimulatorIdP The id of the simulator to set as current
   * @return 
   */
  ReturnType SetSimulatorCurrent(int SimulatorIdP);
  
  /**
   * Gets a pointer to the current simulator
   * @param CurrentSimulatorP Pointer to get the pointer to the current simulator
   * @return 
   */
  ReturnType GetSimulatorCurrent(int &CurrentSimulatorP);
  
  /**
   * Returns a list of all the currently valid simulators
   * @param SimulatorListP Pointer to return the simulators list
   * @return 
   */
  ReturnType GetSimulatorList(vector<string> &SimulatorListP);
  
  /**
   * Returns the current simulators count
   * @param CountP Pointer to return the simulator count
   * @return 
   */
  ReturnType GetSimulatorCount(int &CountP);
  
  /**
   * Adds a new neuron type to be available for the neurons on the simulators depending on this simulator manager
   * @param NameP                Name of the neuron type
   * @param DataTypeP            The neuron type datatype
   * @param ActivationLevelsP    The number of activation levels
   * @param ActivationFunctionsP The list of activation functions for each level
   * @param ParametersNameP      List of parameter names accepted by the neuron type
   * @param ParametersTypeP      List of types for the parameters accepted by the neuron type
   * @return 
   */
  ReturnType AddNeuronType(string NameP, string DataTypeP, int ActivationLevelsP, vector<string> ActivationFunctionsP, vector<string> ParametersNameP, vector<string> ParametersTypeP);
  
  /**
   * Sets the list for fast input for a specific neuron type
   * @param NameP      The name of the neuron type to set the fast input list
   * @param FastInputP The fast input list
   * @return 
   */
  ReturnType SetNeuronTypeFastInput(string NameP, string FastInputP);
  
  /**
   * Returns a pointer to a neuron type structure
   * @param NameP Neuron type name to retrieve the pointer
   * @param TypeP Pointer to return the pointer to the neuron type
   * @return 
   */
  ReturnType GetNeuronType(string NameP, NeuronType **TypeP); //Lothar: shouldn't this use ne *& for the TypeP
  
private:
  int Current;
  vector<Simulator> SimulatorList;
  vector<NeuronType> NeuronTypes;
} ;

#endif /* SIMULATORMANAGER_H */
