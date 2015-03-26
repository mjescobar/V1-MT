/*
 * @author Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 * Generated by ConsolidatedDocumentation v1.0.xlsm
 * TimeStamp: 2015-03-26 16:16:57
 */

#ifndef DEFINE_H
#define DEFINE_H

// Math
#define PI 3.1415926535

// HashTable
#define HASH_A 611057
#define HASH_B 286421
#define HASH_C 126989
#define HASH_CAPACITY_MULTIPLICATOR 1.5

// HashTables Sizes
#define MAX_LINKING_NEURONS MAX_V1_NEURONS + MAX_MT_NEURONS
#define INTERPRETER_MANAGER_COMMANDS_HASH_SIZE 14
#define LOG_MANAGER_MESSAGES_HASH_SIZE 74
#define SETTINGS_MANAGER_INT_HASH_SIZE 1
#define SETTINGS_MANAGER_FLOAT_HASH_SIZE 0
#define SETTINGS_MANAGER_DOUBLE_HASH_SIZE 18 + MAX_V1_NEURONS + MAX_MT_NEURONS + MAX_V1_NEURONS * MAX_V1_NEURONS
#define SETTINGS_MANAGER_STRING_HASH_SIZE 10
#define SETTINGS_MANAGER_BOOL_HASH_SIZE 1
#define SETTINGS_MANAGER_SETTINGTYPE_HASH_SIZE SETTINGS_MANAGER_INT_HASH_SIZE + SETTINGS_MANAGER_FLOAT_HASH_SIZE + SETTINGS_MANAGER_DOUBLE_HASH_SIZE + SETTINGS_MANAGER_STRING_HASH_SIZE + SETTINGS_MANAGER_BOOL_HASH_SIZE
#define SETTINGS_MANAGER_SETTINGSIZE_HASH_SIZE SETTINGS_MANAGER_INT_HASH_SIZE + SETTINGS_MANAGER_FLOAT_HASH_SIZE + SETTINGS_MANAGER_DOUBLE_HASH_SIZE + SETTINGS_MANAGER_STRING_HASH_SIZE + SETTINGS_MANAGER_BOOL_HASH_SIZE

// Default Log Verbose Behavior
#define DEFAULT_MESSAGES true
#define DEFAULT_SILENT_OUTPUT false

// Environment Variables
#define HIDE_END "hide_end"
#define DEFAULT_HIDE_END false
#define NEURONS_NAME_SIZE 6


// V1 Neuron Settings

// V1 Neuron Parameters
#define V1_LABEL "V1"
#define MAX_V1_NEURONS 600

#define V1_FIRST_CALCULATION "V1_first_calculation"
#define DEFAULT_V1_FIRST_CALCULATION "none"
#define V1_ACTIVATION_METHOD "V1_act_method"
#define DEFAULT_V1_ACTIVATION_METHOD "none"
#define V1_DACTIVATION_METHOD "V1_dac_method"
#define DEFAULT_V1_DACTIVATION_METHOD "none"
#define V1_EXTERNAL_EXCITATION_METHOD "V1_external_excitation_method"
#define DEFAULT_V1_EXTERNAL_EXCITATION_METHOD "none"

// V1 Activation Methods
#define V1_A001 "V1_A001"

// V1_A001 Method Parameters
#define V1_A001_NL_MAX "V1_A001_nl_max"
#define DEFAULT_V1_A001_NL_MAX 1
#define V1_A001_NL_A "V1_A001_nl_a"
#define DEFAULT_V1_A001_NL_A 5
#define V1_A001_NL_B "V1_A001_nl_b"
#define DEFAULT_V1_A001_NL_B 0.17

// None

// V1 Derivate Activation Methods
#define V1_D001 "V1_D001"

// V1_D001 Method Parameters
#define V1_D001_CONDUCTANCE_LEAK "V1_D001_conductance_leak"
#define DEFAULT_V1_D001_CONDUCTANCE_LEAK -0.1
#define V1_D001_EXCITATORY_FACTOR "V1_D001_excitatory_factor"
#define DEFAULT_V1_D001_EXCITATORY_FACTOR 0.2
#define V1_D001_INHIBITION_FACTOR "V1_D001_inhibition_factor"
#define DEFAULT_V1_D001_INHIBITION_FACTOR -0.8

// V1 Diffusion Imput Methods
#define V1_F001 "V1_F001"

// V1_F001 Method Parameters
#define V1_F001_A "V1_F001_a"
#define DEFAULT_V1_F001_A 0
#define V1_F001_B "V1_F001_b"
#define DEFAULT_V1_F001_B 0
#define V1_F001_ORIENTATION "V1_F001_orientation"
#define DEFAULT_V1_F001_ORIENTATION 0
#define V1_F001_SPATIAL_FREQUENCY "V1_F001_spatial_frequency"
#define DEFAULT_V1_F001_SPATIAL_FREQUENCY 0
#define V1_F001_TEMPORAL_FREQUENCY "V1_F001_temporal_frequency"
#define DEFAULT_V1_F001_TEMPORAL_FREQUENCY 0
#define V1_F001_MAGNITUDE "V1_F001_magnitude"
#define DEFAULT_V1_F001_MAGNITUDE 0
#define V1_F001_PHASE "V1_F001_phase"
#define DEFAULT_V1_F001_PHASE 0

// MT Neuron Settings

// MT Neuron Parameters
#define MT_LABEL "MT"
#define MAX_MT_NEURONS 10

#define MT_FIRST_CALCULATION "MT_first_calculation"
#define DEFAULT_MT_FIRST_CALCULATION "none"
#define MT_ACTIVATION_METHOD "MT_act_method"
#define DEFAULT_MT_ACTIVATION_METHOD "none"
#define MT_DACTIVATION_METHOD "MT_dac_method"
#define DEFAULT_MT_DACTIVATION_METHOD "none"

// MT Activation Methods
#define MT_A001 "MT_A001"

// MT_A001 Parameters

// None

// MT Derivate Activation Methods
#define MT_D001 "MT_D001"

// MT_D001 Parameters

// None

// Neuron Linking

// V1V1 Linking Methods
#define V1V1_CONNECTION_METHOD "V1V1_connection_method"
#define DEFAULT_V1V1_CONNECTION_METHOD "none"
#define V1V1_L001 "V1V1_L001"

// V1V1_L001 Link Parameters
#define V1V1_L001_BASE_WEIGHT_SOURCE "V1V1_L001_base_weight_source"
#define DEFAULT_V1V1_L001_BASE_WEIGHT_SOURCE "none"
#define V1V1_L001_DEFAULT_WEIGHT "V1V1_L001_default_weight"
#define DEFAULT_V1V1_L001_DEFAULT_WEIGHT 0


// MTMT Link Methods

// None

// V1MT Linking Methods
#define V1MT_CONNECTION_METHOD "V1MT_connection_method"
#define DEFAULT_V1MT_CONNECTION_METHOD "none"
#define V1MT_L001 "V1MT_L001"

// V1MT_L001 Link Parameters
#define V1MT_L001_APERTURE "V1MT_L001_aperture"
#define DEFAULT_V1MT_L001_APERTURE PI/4.0+0.1
#define V1MT_L001_AMPLIFICATION "V1MT_L001_amplification"
#define DEFAULT_V1MT_L001_AMPLIFICATION 1
#define V1MT_L001_SIGMA "V1MT_L001_sigma"
#define DEFAULT_V1MT_L001_SIGMA 2.0/3.0
#define V1MT_L001_MODULATION "V1MT_L001_modulation"
#define DEFAULT_V1MT_L001_MODULATION 5.33648681640625

// Defines

// Simulator Defines
#define SIMULATOR_TIME_STEP "simulator_time_step"
#define DEFAULT_SIMULATOR_TIME_STEP 0.005
#define CALCULATE_ACTIVATION "activation"
#define CALCULATE_DACTIVATION "dactivation"

// Interface Defines
#define LABEL_DONE "DONE"
#define LABEL_FAIL "FAIL"
#define LABEL_ENVIRONMENT_SETTINGS "setenv"
#define LABEL_SIMULATOR_SETTINGS "setsim"
#define LABEL_COMMENT_STRING "#"
#define LABEL_COMMENT_CHAR '#'

// Run Simulation Calls
#define LABEL_RUN_SIMULATION "runsim"
#define SS_INITIALIZE "ss_initialize"
#define SS_ADD_V1_DIFFUSION "ss_add_V1_diffusion"
#define SS_SIMULATE "ss_simulate"

// Reporting Calls
#define LABEL_REPORTING "report"
#define PRINT_ENV "print_env"
#define PRINT_SIM "print_sim"
#define SS_PRINT_V1_ACTIVATION "ss_print_V1_activation"
#define SS_PRINT_V1_ACTIVATION_HORIZONTAL "ss_print_V1_activation_horizontal"
#define SS_PRINT_V1_EXTERNAL_EXCITATION "ss_print_V1_external_excitation"
#define SS_PRINT_MT_ACTIVATION "ss_print_MT_activation"
#define SS_PRINT_MT_ACTIVATION_HORIZONTAL "ss_print_MT_activation_horizontal"

// IO Interaction Calls
#define LABEL_IO_INTERACTIONS "rescue"
#define NPROC "nproc"

#endif  /* DEFINE_H */
