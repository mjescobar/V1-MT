
#ifndef NEURONMENTCOMMAND_H
#define NEURONMENTCOMMAND_H

#include "enum.h"
#include "CommandLine.h"

/**
 * Testing command to check CommandLine basic function
 * @param LocalManagerP
 * @return 
 */
ReturnType report_test(CommandLine &LocalManagerP);

/**
 * Reports the neuron activation for the selected neurons
 * @param LocalManagerP
 * @return 
 */
ReturnType report_neuron_activation(CommandLine &LocalManagerP);

/**
 * Executes the specified nproc file
 * @param LocalManagerP
 * @return 
 */
ReturnType rescue_nproc(CommandLine &LocalManagerP);

/**
 * Terminates an nproc file reading
 * @param LocalManagerP
 * @return 
 */
ReturnType rescue_end_nproc(CommandLine &LocalManagerP);

/**
 * Sets an environment variable value
 * @param LocalManagerP
 * @return 
 */
ReturnType varman_set(CommandLine &LocalManagerP);

/**
 * Gets and environment variable value
 * @param LocalManagerP
 * @return 
 */
ReturnType varman_get(CommandLine &LocalManagerP);

/**
 * Creates a new simulator to work with
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_add_simulator(CommandLine &LocalManagerP);

/**
 * Returns the current simulator ID
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_get_current_simulator(CommandLine &LocalManagerP);

/**
 * Get a list of valid simulator ids
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_get_simulators_list(CommandLine &LocalManagerP);

/**
 * Sets the current simulator in use to the specified id
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_set_current_simulator(CommandLine &LocalManagerP);

/**
 * Removes a simulator from memory
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_remove_simulator(CommandLine &LocalManagerP);

/**
 * Declares a new neuron type
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_new_neuron_type(CommandLine &LocalManagerP);

/**
 * Adds a new neuron from a previously declared neuron type to the current simulator
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_add_neuron(CommandLine &LocalManagerP);

/**
 * Establishes all the possible links between 2 neuron groups
 * @param LocalManagerP
 * @return 
 */
ReturnType setsim_add_link(CommandLine &LocalManagerP);

/**
 * Calculates the simulation result for a simulator
 * @param LocalManagerP
 * @return 
 */
ReturnType runsim_simulate(CommandLine &LocalManagerP);

#endif
