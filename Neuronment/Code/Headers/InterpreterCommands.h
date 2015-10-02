
#ifndef NEURONMENTCOMMAND_H
#define NEURONMENTCOMMAND_H

#include "enum.h"
#include "CommandLine.h"

ReturnType report_test(CommandLine &LocalManagerP);
ReturnType report_neuron_activation(CommandLine &LocalManagerP);
ReturnType rescue_nproc(CommandLine &LocalManagerP);
ReturnType rescue_end_nproc(CommandLine &LocalManagerP);
ReturnType varman_set(CommandLine &LocalManagerP);
ReturnType varman_get(CommandLine &LocalManagerP);
ReturnType setsim_add_simulator(CommandLine &LocalManagerP);
ReturnType setsim_get_current_simulator(CommandLine &LocalManagerP);
ReturnType setsim_get_simulators_list(CommandLine &LocalManagerP);
ReturnType setsim_set_current_simulator(CommandLine &LocalManagerP);
ReturnType setsim_remove_simulator(CommandLine &LocalManagerP);
ReturnType setsim_new_neuron_type(CommandLine &LocalManagerP);
ReturnType setsim_add_neuron(CommandLine &LocalManagerP);
ReturnType setsim_add_link(CommandLine &LocalManagerP);
ReturnType runsim_simulate(CommandLine &LocalManagerP);

#endif
