#include "stdafx.h"
#include "lib\Command.h"
#include "lib\Validator.h"
#include <iostream>
#include <sstream>

///
/// Constructor, default
///
Command::Command(bool nocase) {
  nocase_ = nocase;
}

///
/// Constructor, std::string
///
Command::Command(std::string command, bool nocase) {
  command_ = command;
  nocase_ = nocase;
  Parse();
}

///
/// Destructor
///
Command::~Command() { }

///
/// Performs a validation of the objects data
///
bool Command::Validate() {
  Validator v(this);
  v.Inject(cmd_, "Command").Length(1, 1).Required().IsAlpha();
  return errors().empty();
}

///
/// Parses the command string and splits into two parts, command and argument.
///
void Command::Parse() {
  std::istringstream iss(command_);
  iss >> std::noskipws >> cmd_;
  iss.ignore(1, ' ');
  getline(iss, arg_);
  if (nocase_ && !cmd_.empty()) {
    for (size_t i = 0; i < cmd_.size(); ++i) {
      cmd_[i] = tolower(cmd_[i]);
    }
    if (!arg_.empty()) {
      for (size_t i = 0; i < arg_.size(); ++i) {
        arg_[i] = tolower(arg_[i]);
      }
    }
  }
}


///
/// Accessor for cmd_
///
char Command::cmd() {
  return cmd_[0];
}


///
/// Accessor for arg_
///
std::string Command::arg() {
  return arg_;
}


///
/// Returns true if the argument is numeric, false otherwise.
bool Command::NumericArg() {
  bool numeric = true;
  for (std::string::iterator it = arg_.begin(); it < arg_.end(); ++it)
    if (!isdigit(*it)) {
      std::cout << *it;
      numeric = false;
    }
    return numeric;
}


///
/// Friendly insertion operator
///
std::istream& operator>>(std::istream& is, Command& cmd) {
  getline(is, cmd.command_);
  return is;
}


///
/// Friendly extraction operator
///
std::ostream& operator<<(std::ostream& os, Command& cmd) {
  os << cmd.command_;
  return os;
}