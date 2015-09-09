
#include "extern.h"
#include "tools.h"
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
  Log.Message("DV-008: CommandManager");
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

CommandLine::~CommandLine()
{
  delete FlagValues;
}

ReturnType CommandLine::Append(int argc, char** argv)
{
  ReturnCatch(DataCheck(argv, "NotNull"));
  string Tmp = "";
  for (int i = 0; i < argc; i++) {
    Tmp = Tmp + argv[i];
    if (i + 1 < argc) {
      Tmp = Tmp + " ";
    }
  }
  if (DataCheck(Tmp, "NonEmpty") == ReturnFail) {
    Log.Message("SD-011");
    return ReturnFail;
  }
  ReturnCatch(Append(Tmp));
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
    return ReturnSuccess;
  } else {
    ReturnCatch(ProcessFullCommand());
    return ReturnSuccess;
  }
}

ReturnType CommandLine::ProcessFullCommand()
{
  // Storing the full line
  ReturnMessage = "";
  for (int i = 0; i < FullCommand.size(); i++) {
    if (DataCheck(FullCommand[i], "IsBackSlash") == ReturnSuccess) {
      FullCommand[i] = ' ';
    }
  }
  FullLine = FullCommand;
  ReturnCatch(trim(FullCommand));
  if (FullCommand.size()) {
    // Removing comments from line
    string LookingForComment = FullCommand;
    ReturnCatch(trim(LookingForComment));
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
    // Dividing string for redirection
    Command = "";
    Redirection = "";
    bool RedirectionDetected = false;
    for (int i = 0; i < FullCommand.size(); i++) {
      if (DataCheck(FullCommand[i], "IsGreaterThan") == ReturnSuccess) {
        if (i > 0) {
          Command = FullCommand.substr(0, i - 1);
          ReturnCatch(trim(Command));
          Redirection = FullCommand.substr(i + 1, FullCommand.size() - i - 1);
          ReturnCatch(trim(Redirection));
        } else {
          Command = "";
          Redirection = FullCommand.substr(1, FullCommand.size() - 1);
          ReturnCatch(trim(Redirection));
        }
        RedirectionDetected = true;
        i = FullCommand.size();
        if (Redirection.size() < 1) {
          Log.Message("IN-021");
          ReturnMessage = "IN-021";
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
      ReturnCatch(trim(Redirection));
      vector<string> InternalRedirectionTokenize;
      ReturnCatch(Tokenize(Redirection, InternalRedirectionTokenize));
      if (InternalRedirectionTokenize.size() > 1) {
        Log.Message("IN-003");
        Redirection = InternalRedirectionTokenize[0];
      }
      ReturnCatch(trim(Redirection));
      ReturnCatch(Tokenize(Redirection, InternalRedirectionTokenize));
      if (InternalRedirectionTokenize.size() > 1) {
        Log.Message("IN-003");
        Redirection = InternalRedirectionTokenize[0];
      }
    }
    ReturnCatch(trim(Redirection));
    // Check that all the characters are authorized
    vector<string> AllowedChars;
    ReturnCatch(GetAllowedChars(AllowedChars));
    for (int i = 0; i < Command.size(); i++) {
      bool Allowed = false;
      for (int j = 0; j < AllowedChars.size(); j++) {
        if (DataCheck(Command[i], AllowedChars[j]) == ReturnSuccess) {
          Allowed = true;
          j = AllowedChars.size();
        }
      }
      if (!Allowed) {
        Log.Message("IN-011");
        return ReturnFail;
      }
    }
    // Tokenizing and storing words
    vector<string> Tokens;
    ReturnCatch(Tokenize(Command, Tokens));
    bool InPreamble = true;
    bool InFlag = false;
    bool InList = false;
    string Flag;
    string Value;
    for (int i = 0; i < Tokens.size(); i++) {
      string Token;
      Token = Tokens[i];
      ReturnCatch(trim(Token));
      if (InPreamble) {
        if (DataCheck(Token[0], "IsHyphen") == ReturnFail) {
          Directives.push_back(Token);
        } else {
          InPreamble = false;
          InFlag = true;
          Value = "";
          Flag = Token.substr(1, Token.size() - 1);
          if (Flag.size() < 1) {
            Log.Message("IN-014");
            return ReturnFail;
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
                Log.Message("IN-013");
                return ReturnFail;
              }
            } else {
              if (DataCheck(Token[0], "IsCurlyBracesOpen") == ReturnSuccess) {
                if (Token.size() == 1) {
                  Log.Message("IN-021");
                } else {
                  Log.Message("IN-013");
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
                Log.Message("IN-013");
                return ReturnFail;
              }
            } else {
              InFlag = false;
              if (DataCheck(Token[0], "IsHyphen") == ReturnSuccess) {
                FlagValues->PutEntryQuick(Flag, "");
                InFlag = true;
                Value = "";
                Flag = Token.substr(1, Token.size() - 1);
                if (Flag.size() < 1) {
                  Log.Message("IN-014");
                  return ReturnFail;
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
              Log.Message("IN-014");
              return ReturnFail;
            }
            Value = "";
          } else {
            Log.Message("IN-012");
            return ReturnFail;
          }
        }
      }
    }
    if (InList) {
      Log.Message("IN-015");
      return ReturnFail;
    }
    if (InFlag) {
      FlagValues->PutEntryQuick(Flag, "");
    }
    Ready = true;
    if (ReturnMessage.size() == 0) {
      return ReturnSuccess;
    } else {
      return ReturnSuccessWarning;
    }
  } else {
    FullCommand = "";
    Directives.clear();
    Ready = true;
    Redirection = "";
    RedirectionMode = RedirectionNone;
    Command = "";
    Comment = "";
    if (ReturnMessage.size() == 0) {
      return ReturnSuccess;
    } else {
      return ReturnSuccessWarning;
    }
  }
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

ReturnType CommandLine::IsReady(bool &ReadyP)
{
  ReadyP = Ready;
  return ReturnSuccess;
}

ReturnType CommandLine::GetFlag(string FlagP, string &ValueP)
{
  if (Ready) {
    return FlagValues->GetEntryQuick(FlagP, ValueP);
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetFlag(string FlagP)
{
  if (Ready) {
    string Dummy;
    return FlagValues->GetEntryQuick(FlagP, Dummy);
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetDirectives(vector<string> &DirectivesP)
{
  if (Ready) {
    DirectivesP = Directives;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetCleanCommand(string &CleanCommandP, string Separator)
{
  if (Ready) {
    CleanCommandP = "";
    for (int i = 0; i < Directives.size(); i++) {
      if (CleanCommandP.empty()) {
        CleanCommandP = Directives[0];
      } else {
        CleanCommandP = CleanCommandP + Separator + Directives[i];
      }
    }
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetComment(string &CommentP)
{
  if (Ready) {
    CommentP = Comment;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetCommand(string &CommandP)
{
  if (Ready) {
    CommandP = Command;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetRedirection(string &RedirectionP)
{
  if (Ready) {
    RedirectionP = Redirection;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetRedirectionType(RedirectionType &RedirectionModeP)
{
  if (Ready) {
    RedirectionModeP = RedirectionMode;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::GetFullLine(string &FullLineP)
{
  if (Ready) {
    FullLineP = FullLine;
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::HasCommand(bool &HasCommandP)
{
  if (Ready) {
    if (Command.length() > 0) {
      HasCommandP = true;
    } else {
      HasCommandP = false;
    }
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
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
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::HasRedirection(bool &HasRedirectionP)
{
  if (Ready) {
    if (Redirection.length() > 0) {
      HasRedirectionP = true;
    } else {
      HasRedirectionP = false;
    }
    return ReturnSuccess;
  } else {
    Log.Message("DV-024");
    return ReturnFail;
  }
}

ReturnType CommandLine::Restart()
{
  FullCommand = "";
  Directives.clear();
  Ready = false;
  Redirection = "";
  RedirectionMode = RedirectionNone;
  Command = "";
  Comment = "";
  return ReturnSuccess;
}
