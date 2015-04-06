/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef ENUMS_H
#define	ENUMS_H

/** Data types for use and processing */
enum DataType {
    Data_null,
    Data_DataType,
    Data_bool,
    Data_int,
    Data_float,
    Data_double,
    Data_string,
    Data_function
};

/** Types of neuron */
enum NeuronType {
    Neuron_ND,
    Neuron_V1,
    Neuron_MT
};

/** Used to indicate direction for string edition */
enum SideType {
    Side_Right,
    Side_Left
};

/** Used to indicate sense of data at reporting */
enum OrientationType {
    Orientation_Horizontal,
    Orientation_Vertical
};

/** Used to indicate the message type for output */
enum MessageType {
    Message_Coded,
    Message_Dev,
    Message_Allways
};

/** To process three state output functions */
enum ResultType {
    Result_true,
    Result_false,
    Result_silent
};

#endif	/* ENUMS_H */
