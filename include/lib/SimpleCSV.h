#pragma once
#include <string>
#include <vector>

///
/// A simple CSV parser
///
class SimpleCSV {
public:

  ///
  /// Constructor, default
  ///
  SimpleCSV();

  ///
  /// Constructor, std::string
  ///
  SimpleCSV(std::string str);

  ///
  /// Parses a CSV string into a vector
  ///
  void Parse();

  ///
  /// Overloads the bracket operator for easy csv access
  ///
  std::string operator[](int i);

private:
  ///
  /// Recursively explodes a CSV string and pushes the values onto a vector
  ///
  void Explode(std::string& str);

  // holds a csv formatted string
  std::string str_;

  // holds csvalues
  std::vector<std::string> csv_;

  // a value separator used by explode, defaults to ',' (for CSV)
  char delim_;
};