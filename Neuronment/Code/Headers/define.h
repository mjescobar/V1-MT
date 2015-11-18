#ifndef DEFINE_H
#define DEFINE_H













//LogManager
#define LABEL_DONE "DONE"
#define LABEL_FAIL "FAIL"
// Simulator Defines
#define CALCULATE_ACTIVATION "activation"
#define CALCULATE_DACTIVATION "dactivation"
// Interface Defines
#define LABEL_COMMENT_STRING "#"
#define LABEL_COMMENT_CHAR '#'
#define LABEL_REDIRECTION_STRING ">"
#define LABEL_REDIRECTION_CHAR '>'
#define LABEL_INDENTATION_STRING "    "
#define LABEL_MESSAGE_STRING ": "
#define LABEL_NEURON_SEPARATOR "'"
// Variable management calls
#define LABEL_VARIABLE_MANAGEMENT "varman"
#define VARMAN_SET "set"
#define VARMAN_PRINT "print"
// Run Simulation Calls
#define LABEL_RUN_SIMULATION "runsim"
#define RUNSIM_SS_INITIALIZE "ss_initialize"
#define RUNSIM_SS_ADD_V1_DIFFUSION "ss_add_V1_diffusion"
#define RUNSIM_SS_SIMULATE "ss_simulate"
// Reporting Calls
#define LABEL_REPORTING "report"
#define REPORT_SS_PRINT_V1_ACTIVATION "ss_print_V1_activation"
#define REPORT_SS_PRINT_V1_ACTIVATION_HORIZONTAL "ss_print_V1_activation_horizontal"
#define REPORT_SS_PRINT_V1_EXTERNAL_EXCITATION "ss_print_V1_external_excitation"
#define REPORT_SS_PRINT_MT_ACTIVATION "ss_print_MT_activation"
#define REPORT_SS_PRINT_MT_ACTIVATION_HORIZONTAL "ss_print_MT_activation_horizontal"
// IO Interaction Calls
#define LABEL_IO_INTERACTIONS "rescue"
#define RESCUE_NPROC "nproc"
#define RESCUE_RETURN "return"
// V1 Neurons
#define V1_LABEL "V1"
#define V1_A001 "V1_A001"
#define V1_F001 "V1_F001"
#define V1_D001 "V1_D001"
// MT Neurons
#define MT_LABEL "MT"
#define MT_A001 "MT_A001"
#define MT_D001 "MT_D001"
// V1V1 Linking
#define V1V1_L001 "V1V1_L001"
// V1MT Linking
#define V1MT_L001 "V1MT_L001"
// Others
#define SIMULATOR_ACTIVATION_FUNCTION_HASH_SIZE 10
// Math
#define PI 3.1415926535
// HashTable
#define HASH_A 611057
#define HASH_B 286421
#define HASH_C 126989
#define HASH_TABLE_MARGIN 1.5
// HashTables Sizes
#define COMMAND_MANAGER_HASH_SIZE 100
#define MAX_LINKING_NEURONS 610
#define INTERPRETER_MANAGER_COMMANDS_HASH_SIZE 25
#define LOG_MANAGER_HASH_SIZE 100
#define SETTINGS_MANAGER_INT_HASH_SIZE 100
#define SETTINGS_MANAGER_BOOL_HASH_SIZE 100
#define SETTINGS_MANAGER_DOUBLE_HASH_SIZE 100
#define SETTINGS_MANAGER_STRING_HASH_SIZE 100
#define SETTINGS_MANAGER_SETTINGTYPE_HASH_SIZE SETTINGS_MANAGER_INT_HASH_SIZE + SETTINGS_MANAGER_BOOL_HASH_SIZE + SETTINGS_MANAGER_DOUBLE_HASH_SIZE + SETTINGS_MANAGER_STRING_HASH_SIZE
#define SETTINGS_MANAGER_SETTINGSIZE_HASH_SIZE SETTINGS_MANAGER_INT_HASH_SIZE + SETTINGS_MANAGER_BOOL_HASH_SIZE + SETTINGS_MANAGER_DOUBLE_HASH_SIZE + SETTINGS_MANAGER_STRING_HASH_SIZE
// V1 Neurons
#define V1_MAX_NEURONS 600
// MT Neurons
#define MT_MAX_NEURONS 10
// Default Environment Values
#define DEFAULT_SHOW_MESSAGE_INFORMATION true
#define DEFAULT_SHOW_MESSAGE_CODED_INFORMATION true
#define DEFAULT_SHOW_MESSAGE_CODED true
#define DEFAULT_SHOW_MESSAGE_DEVELOPMENT true
#define DEFAULT_SHOW_MESSAGE_ALLWAYS true
#define DEFAULT_SHOW_ELAPSED_TIME false
// Default V1 Values
#define DEFAULT_V1_FIRST_CALCULATION "none"
#define DEFAULT_V1_ACTIVATION_METHOD "none"
#define DEFAULT_V1_DACTIVATION_METHOD "none"
#define DEFAULT_V1_EXTERNAL_EXCITATION_METHOD "none"
#define DEFAULT_V1_A001_NL_MAX 1
#define DEFAULT_V1_A001_NL_A 5
#define DEFAULT_V1_A001_NL_B 0,17
#define DEFAULT_V1_D001_CONDUCTANCE_LEAK -0,1
#define DEFAULT_V1_D001_EXCITATORY_FACTOR 0,2
#define DEFAULT_V1_D001_INHIBITION_FACTOR -0,8
#define DEFAULT_V1_D001_WEIGHT_FACTOR 100
#define DEFAULT_V1_F001_A 0
#define DEFAULT_V1_F001_B 0
#define DEFAULT_V1_F001_ORIENTATION 0
#define DEFAULT_V1_F001_SPATIAL_FREQUENCY 0
#define DEFAULT_V1_F001_TEMPORAL_FREQUENCY 0
#define DEFAULT_V1_F001_MAGNITUDE 0
#define DEFAULT_V1_F001_PHASE 0
// Default MT Values
#define DEFAULT_MT_FIRST_CALCULATION "none"
#define DEFAULT_MT_ACTIVATION_METHOD "none"
#define DEFAULT_MT_DACTIVATION_METHOD "none"
// Default Linking Values
#define DEFAULT_V1V1_CONNECTION_METHOD "none"
#define DEFAULT_V1V1_L001_BASE_WEIGHT_SOURCE "none"
#define DEFAULT_V1V1_L001_DEFAULT_WEIGHT 0
#define DEFAULT_V1MT_CONNECTION_METHOD "none"
#define DEFAULT_V1MT_L001_APERTURE 46
#define DEFAULT_V1MT_L001_AMPLIFICATION 1
#define DEFAULT_V1MT_L001_SIGMA 0,666666666666666
#define DEFAULT_V1MT_L001_MODULATION 5,33648681640625
// Default Simulator Values
#define DEFAULT_SIMULATOR_TIME_STEP 0,005
// Environment Variables
#define HIDE_END "ENV:hide_end"
#define MAX_NPROC_NESTING "ENV:max_nproc_nesting"
#define SHOW_ELAPSED_TIME "ENV:show_elapsed_time"
// V1 Variables
#define V1_FIRST_CALCULATION "SIM:V1_first_calculation"
#define V1_ACTIVATION_METHOD "SIM:V1_act_method"
#define V1_DACTIVATION_METHOD "SIM:V1_dac_method"
#define V1_EXTERNAL_EXCITATION_METHOD "SIM:V1_external_excitation_method"
// V1 Activation Methods
// V1_A001 Method Parameters
#define V1_A001_NL_MAX "SIM:V1_A001_nl_max"
#define V1_A001_NL_A "SIM:V1_A001_nl_a"
#define V1_A001_NL_B "SIM:V1_A001_nl_b"
// V1 Derivate Activation Methods
// V1_D001 Method Parameters
#define V1_D001_CONDUCTANCE_LEAK "SIM:V1_D001_conductance_leak"
#define V1_D001_EXCITATORY_FACTOR "SIM:V1_D001_excitatory_factor"
#define V1_D001_INHIBITION_FACTOR "SIM:V1_D001_inhibition_factor"
#define V1_D001_WEIGHT_FACTOR "SIM:V1_D001_weight_factor"
// V1 External Excitation Method
// V1_F001 Method Parameters
#define V1_F001_A "SIM:V1_F001_a"
#define V1_F001_B "SIM:V1_F001_b"
#define V1_F001_ORIENTATION "SIM:V1_F001_orientation"
#define V1_F001_SPATIAL_FREQUENCY "SIM:V1_F001_spatial_frequency"
#define V1_F001_TEMPORAL_FREQUENCY "SIM:V1_F001_temporal_frequency"
#define V1_F001_MAGNITUDE "SIM:V1_F001_magnitude"
#define V1_F001_PHASE "SIM:V1_F001_phase"
// MT Variables
#define MT_FIRST_CALCULATION "SIM:MT_first_calculation"
#define MT_ACTIVATION_METHOD "SIM:MT_act_method"
#define MT_DACTIVATION_METHOD "SIM:MT_dac_method"
// MT Activation Methods
// MT_A001 Parameters
// MT Derivate Activation Methods
// MT_D001 Parameters
// Linking Variables
// V1V1 Linking Methods
#define V1V1_CONNECTION_METHOD "SIM:V1V1_connection_method"
// V1V1_L001 Link Parameters
#define V1V1_L001_BASE_WEIGHT_SOURCE "SIM:V1V1_L001_base_weight_source"
#define V1V1_L001_DEFAULT_WEIGHT "SIM:V1V1_L001_default_weight"
// V1MT Linking Methods
#define V1MT_CONNECTION_METHOD "SIM:V1MT_connection_method"
// V1MT_L001 Link Parameters
#define V1MT_L001_APERTURE "SIM:V1MT_L001_aperture"
#define V1MT_L001_AMPLIFICATION "SIM:V1MT_L001_amplification"
#define V1MT_L001_SIGMA "SIM:V1MT_L001_sigma"
#define V1MT_L001_MODULATION "SIM:V1MT_L001_modulation"
// Simulator Variables
#define SIMULATOR_TIME_STEP "SIM:simulator_time_step"

#endif  /* DEFINE_H */
