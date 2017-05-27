#pragma once
#include <iostream>
#include "lib\Command.h"

namespace Console {

  enum EventType { key_return };

  ///
  /// Prints a single character to console
  ///
  void PrintChar(const char ch);

  ///
  /// Prints a string to console
  ///
  void Print(const std::string text);

  ///
  /// Prints a string to console, but places a newline first
  void PrintLn(const std::string text);

  ///
  /// Prints a string to std::cerr
  ///
  void PrintError(const std::string errormsg);

  ///
  /// Displays a console prompt, with optional prefix and postfix
  ///
  Command Prompt(const std::string prefix = "", const std::string postfix="");

  ///
  /// Helper function to safely read from streams
  ///
  template <class Type>
  std::istream& ReadStream(std::istream& is, Type& value) {
    std::string s;
    getline(is, s);
    if (is.good()) {
      std::stringstream ss(s);
      ss >> value;
      if (!ss.good()) {
        is.setstate(ss.rdstate());
      }
    }
    return is;
  }

}