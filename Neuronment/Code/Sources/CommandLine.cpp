
#include "tools.h"
#include "extern.h"
#include "define.h"
#include "LogManager.h"
#include "CommandLine.h"

CommandLine::CommandLine()
{
  FullCommand = "";
  Directives.clear();
  Ready = false;
  Redirection = "";
  RedirectionMode = RedirectionNone;
  Command = "";
  Comment = "";
  FlagValues = new HashTable<string>(COMMAND_MANAGER_HASH_SIZE);
}

CommandLine::CommandLine(const CommandLine& orig)
{
  Log.CodedMessage("DV-001: CommandManager copy constructor");
}

CommandLine::~CommandLine()
{
  delete FlagValues;
}

CommandLine & CommandLine::operator=(const CommandLine & orig){
  Log.CodedMessage("DV-001: CommandManager assignment operator");
  return *this;
}

CommandLine::CommandLine(int argcP, char** argvP)
{
  FullCommand = "";
  Directives.clear();
  Ready = false;
  Redirection = "";
  RedirectionMode = RedirectionNone;
  Command = "";
  Comment = "";
  FlagValues = new HashTable<string>(COMMAND_MANAGER_HASH_SIZE);
  Append(argcP, argvP);
}

ReturnType CommandLine::Restart()
{
  Ready = false;
  FullLine = "";
  FullCommand = "";
  Command = "";
  Redirection = "";
  Comment = "";
  Directives.clear();
  RedirectionMode = RedirectionNone;
  delete FlagValues;
  FlagValues = new HashTable<string>(COMMAND_MANAGER_HASH_SIZE);
  return ReturnSuccess;
}

ReturnType CommandLine::Append(string StringP)
{
  if (Ready) {
    Ready = false;
    FullCommand = StringP;
  } else {
    FullCommand = FullCommand + " " + StringP;
  }
  if (DataCheck(FullCommand[FullCommand.size() - 1], "IsBackSlash") == ReturnSuccess) {
    Ready = false;
    FullCommand.substr(0, FullCommand.size() - 1);
  } else {
    ProcessFullCommand();
  }
  return ReturnSuccess;
}

ReturnType CommandLine::GetFlag(string FlagP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  string Dummy; //Lothar: straight getentryquick types?
  if (FlagValues->GetEntryQuick(FlagP, Dummy) == ReturnSuccess) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType CommandLine::GetFlag(string FlagP, string &ValueP) //Lothar: how list flags are processed?
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  if (FlagValues->GetEntryQuick(FlagP, ValueP) == ReturnSuccess) {
    return ReturnSuccess;
  } else {
    return ReturnFail;
  }
}

ReturnType CommandLine::GetCommand(string &CommandP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  CommandP = Command;
  return ReturnSuccess;
}

ReturnType CommandLine::GetCleanCommand(string &CleanCommandP, string Separator)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  CleanCommandP = "";
  for (int i = 0; i < Directives.size(); i++) {
    if (CleanCommandP.empty()) {
      CleanCommandP = Directives[0];
    } else {
      CleanCommandP = CleanCommandP + Separator + Directives[i];
    }
  }
  return ReturnSuccess;
}

ReturnType CommandLine::GetRedirection(string &RedirectionP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  RedirectionP = Redirection;
  return ReturnSuccess;
}

ReturnType CommandLine::GetRedirectionType(RedirectionType &RedirectionModeP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  RedirectionModeP = RedirectionMode;
  return ReturnSuccess;
}

ReturnType CommandLine::IsReady(bool &ReadyP)
{
  ReadyP = Ready;
  return ReturnSuccess;
}

ReturnType CommandLine::HasCommand(bool &HasCommandP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  if (Command.length() > 0) {
    HasCommandP = true;
  } else {
    HasCommandP = false;
  }
  return ReturnSuccess;
}

ReturnType CommandLine::HasComment(bool &HasCommentP)
{
  if (Ready) {
    if (Comment.length() > 0) {
      HasCommentP = true;
    } else {
      HasCommentP = false;
    }
    return ReturnSuccess;
  } else {
    return Return(ReturnFail, "DV-024");
  }
}

ReturnType CommandLine::HasRedirection(bool &HasRedirectionP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  if (Redirection.length() > 0) {
    HasRedirectionP = true;
  } else {
    HasRedirectionP = false;
  }
  return ReturnSuccess;
}

ReturnType CommandLine::Append(int argcP, char** argvP)
{
  DataCheck(argvP, "NotNull");
  string Tmp = "";
  for (int i = 0; i < argcP; i++) {
    Tmp = Tmp + argvP[i];
    if (i + 1 < argcP) {
      Tmp = Tmp + " ";
    }
  }
  if (DataCheck(Tmp, "NonEmpty") == ReturnFail) {
    return Return(ReturnFail, "SD-011");
  }
  Append(Tmp);
  return ReturnSuccess;
}

ReturnType CommandLine::GetComment(string &CommentP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  CommentP = Comment;
  return ReturnSuccess;
}

ReturnType CommandLine::GetFullLine(string &FullLineP)
{
  if (!Ready) {
    return Return(ReturnFail, "DV-024");
  }
  FullLineP = FullLine;
  return ReturnSuccess;
}

ReturnType CommandLine::GetAllowedChars(vector<string>& AllowedCharsP)
{
  AllowedCharsP.clear();
  AllowedCharsP.push_back("IsTab");
  AllowedCharsP.push_back("IsSpace");
  AllowedCharsP.push_back("IsNumberSign");
  AllowedCharsP.push_back("IsHyphen");
  AllowedCharsP.push_back("IsDot");
  AllowedCharsP.push_back("IsSlash");
  AllowedCharsP.push_back("IsNumber");
  AllowedCharsP.push_back("IsLessThan");
  AllowedCharsP.push_back("IsGreaterThan");
  AllowedCharsP.push_back("IsLetter");
  AllowedCharsP.push_back("IsBackSlash");
  AllowedCharsP.push_back("IsUnderscore");
  AllowedCharsP.push_back("IsCurlyBraces");
  AllowedCharsP.push_back("IsColon");
  return ReturnSuccess;
}

ReturnType CommandLine::ProcessFullCommand()
{
  FullLine = FullCommand;
  // Processing the line continuation character
  for (int i = 0; i < FullCommand.size(); i++) {
    if (DataCheck(FullCommand[i], "IsBackSlash") == ReturnSuccess) {
      FullCommand[i] = ' ';
    }
  }
  trim(FullCommand);
  if (FullCommand.size()) {
    // Check that all the characters are authorized
    vector<string> AllowedChars;
    GetAllowedChars(AllowedChars);
    for (int i = 0; i < Command.size(); i++) {
      bool Allowed = false;
      for (int j = 0; j < AllowedChars.size(); j++) {
        if (DataCheck(Command[i], AllowedChars[j]) == ReturnSuccess) {
          Allowed = true;
          j = AllowedChars.size();
        }
      }
      if (!Allowed) {
        return Return(ReturnFail, "IN-011");
      }
    }
    // Processing comments
    string LookingForComment = FullCommand;
    trim(LookingForComment);
    for (int i = 0; i < LookingForComment.size(); i++) {
      if (DataCheck(LookingForComment[i], "IsNumberSign") == ReturnSuccess) {
        if (i > 0) {
          FullCommand = LookingForComment.substr(0, i);
          Comment = LookingForComment.substr(i, LookingForComment.size() - FullCommand.size());
          i = LookingForComment.size();
        } else {
          FullCommand = "";
          Comment = LookingForComment;
        }
      }
    }
    // Processing redirection
    Command = "";
    Redirection = "";
    bool RedirectionDetected = false;
    for (int i = 0; i < FullCommand.size(); i++) {
      if (DataCheck(FullCommand[i], "IsGreaterThan") == ReturnSuccess) {
        if (i > 0) {
          Command = FullCommand.substr(0, i - 1);
          trim(Command);
          Redirection = FullCommand.substr(i + 1, FullCommand.size() - i - 1);
          trim(Redirection);
        } else {
          Command = "";
          Redirection = FullCommand.substr(1, FullCommand.size() - 1);
          trim(Redirection);
        }
        RedirectionDetected = true;
        i = FullCommand.size();
        if (Redirection.size() < 1) {
          Log.CodedMessage("IN-021");
        }
      }
    }
    if (!RedirectionDetected) {
      Command = FullCommand;
    } else {
      if (DataCheck(Redirection[0], "IsGreaterThan") == ReturnSuccess) {
        RedirectionMode = RedirectionAppend;
        Redirection = Redirection.substr(1, Redirection.size() - 1);
      } else {
        RedirectionMode = RedirectionNew;
      }
      trim(Redirection);
      vector<string> InternalRedirectionTokenize;
      Tokenize(Redirection, InternalRedirectionTokenize);
      if (InternalRedirectionTokenize.size() > 1) {
        Log.CodedMessage("IN-003");
        Redirection = InternalRedirectionTokenize[0];
      }
      trim(Redirection);
      Tokenize(Redirection, InternalRedirectionTokenize);
      if (InternalRedirectionTokenize.size() > 1) {
        Log.CodedMessage("IN-003");
        Redirection = InternalRedirectionTokenize[0];
      }
    }
    trim(Redirection);
    // Tokenizing and storing words
    vector<string> Tokens;
    Tokenize(Command, Tokens);
    bool InPreamble = true;
    bool InFlag = false;
    bool InList = false;
    string Flag;
    string Value;
    for (int i = 0; i < Tokens.size(); i++) {
      string Token;
      Token = Tokens[i];
      trim(Token);
      if (InPreamble) {
        if (DataCheck(Token[0], "IsHyphen") == ReturnFail) {
          Directives.push_back(Token);
        } else {
          InPreamble = false;
          InFlag = true;
          Value = "";
          Flag = Token.substr(1, Token.size() - 1);
          if (Flag.size() < 1) {
            return Return(ReturnFail, "IN-014");
          }
        }
      } else {
        if (InFlag) {
          if (InList) {
            if (DataCheck(Token[Token.size() - 1], "IsCurlyBracesClose") == ReturnSuccess) {
              if (Token.size() == 1) {
                InList = false;
                InFlag = false;
                FlagValues->PutEntryQuick(Flag, Value);
              } else {
                Log.CodedMessage("IN-013");
                return ReturnFail;
              }
            } else {
              if (DataCheck(Token[0], "IsCurlyBracesOpen") == ReturnSuccess) {
                if (Token.size() == 1) {
                  Log.CodedMessage("IN-021");
                } else {
                  Log.CodedMessage("IN-013");
                }
                return ReturnFail;
              }
              if (Token.size() > 0) {
                if (Value.size() > 0) {
                  Value = Value + " ";
                }
                Value = Value + Token;
              }
            }
          } else {
            if (DataCheck(Token[0], "IsCurlyBracesOpen") == ReturnSuccess) {
              if (Token.size() == 1) {
                InList = true;
              } else {
                return Return(ReturnFail, "IN-013");
              }
            } else {
              InFlag = false;
              if (DataCheck(Token[0], "IsHyphen") == ReturnSuccess) {
                FlagValues->PutEntryQuick(Flag, "");
                InFlag = true;
                Value = "";
                Flag = Token.substr(1, Token.size() - 1);
                if (Flag.size() < 1) {
                  return Return(ReturnFail, "IN-014");
                }
              } else {
                FlagValues->PutEntryQuick(Flag, Token);
              }
            }
          }
        } else {
          if (DataCheck(Token[0], "IsHyphen") == ReturnSuccess) {
            InFlag = true;
            Flag = Token.substr(1, Token.size() - 1);
            if (Flag.size() < 1) {
              return Return(ReturnFail, "IN-014");
            }
            Value = "";
          } else {
            return Return(ReturnFail, "IN-012");
          }
        }
      }
    }
    if (InList) {
      return Return(ReturnFail, "IN-015");

    }
    if (InFlag) {
      FlagValues->PutEntryQuick(Flag, "");
    }
    Ready = true;
    return ReturnSuccess;
  } else {
    FullCommand = "";
    Directives.clear();
    Ready = true;
    Redirection = "";
    RedirectionMode = RedirectionNone;
    Command = "";
    Comment = "";
    return ReturnSuccess;
  }
}
