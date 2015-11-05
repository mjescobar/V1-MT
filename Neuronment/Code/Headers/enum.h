
#ifndef ENUMS_H
#define	ENUMS_H

/** To inform a process result */
enum ReturnType {
  ReturnNone,
  ReturnSuccess,
  ReturnFail
};

/** Used to indicate the message type for output */
enum MessageType {
  MessageInformation      = 0,
  MessageCodedInformation = 5,
  MessageCoded            = 10,
  MessageDevelopment      = 20,
  MessageAllways          = 30
};

enum RedirectionType {
  RedirectionNone,
  RedirectionNew,
  RedirectionAppend
};

#endif
