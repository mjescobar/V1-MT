
#ifndef NEURONMENTCOMMAND_H
#define NEURONMENTCOMMAND_H

#include "enum.h"
#include "CommandManager.h"

ReturnType report_test(CommandManager &LocalManagerP);
ReturnType rescue_nproc(CommandManager &LocalManagerP);
ReturnType rescue_end_nproc(CommandManager &LocalManagerP);
ReturnType varman_set(CommandManager &LocalManagerP);
ReturnType varman_get(CommandManager &LocalManagerP);
ReturnType setsim_add_simulator(CommandManager &LocalManagerP);
ReturnType setsim_get_current_simulator(CommandManager &LocalManagerP);
ReturnType setsim_get_simulators_list(CommandManager &LocalManagerP);
ReturnType setsim_set_current_simulator(CommandManager &LocalManagerP);
ReturnType setsim_remove_simulator(CommandManager &LocalManagerP);
ReturnType setsim_new_neuron_type(CommandManager &LocalManagerP);
ReturnType setsim_add_neuron(CommandManager &LocalManagerP);
#endif /* NEURONMENTCOMMAND_H */

