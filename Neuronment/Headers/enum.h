/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef ENUMS_H
#define	ENUMS_H

/** To inform a process result */
enum ReturnType {
  ReturnNone,
  ReturnSuccess,
  ReturnSuccessWarning,
  ReturnFail
};

/** Used to indicate the message type for output */
enum MessageType {
  MessageInformation = 0,
  MessageCodedInformation = 5,
  MessageCoded = 10,
  MessageDevelopment = 20,
  MessageAllways = 30
};

enum RedirectionType {
  RedirectionNone,
  RedirectionNew,
  RedirectionAppend
};

#if 0

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

/** To process three state output functions */
enum ResultType {
  Result_true,
  Result_false,
  Result_silent
};

/** To process command lines */
enum ArgumentType {
  Directive,
  SubDirective,
  Flag,
  FlaggedAttribute
};

/** Data types for use and processing */
enum DataType {
  Data_null,
  Data_int,
  Data_bool,
  Data_voidp,
  Data_double,
  Data_string
};
#endif

#endif	/* ENUMS_H */
