#pragma once
#include "model\BaseModel.h"

class Command : public BaseModel {
public:
  // Constructors and destructor
  Command(bool nocase=true);
  explicit Command(std::string command, bool nocase=true);
  ~Command();

  // Accessors
  char cmd();
  std::string arg();

  // Performs validation on the model
  bool Validate();

  // Parses a command string
  void Parse();

  // Returns true if the argument is numeric
  bool NumericArg();

private:
  // Friendly insertion and extraction operators
  friend std::ostream& operator<<(std::ostream& is, Command& cmd);
  friend std::istream& operator>>(std::istream& is, Command& cmd);

  // holds the whole command string, the actual command and the argument
  std::string command_, cmd_, arg_;
  bool nocase_;
};