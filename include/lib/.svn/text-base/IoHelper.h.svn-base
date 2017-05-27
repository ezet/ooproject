#pragma once
#include <string>

///
/// Helper functions for console-based IO operations
///
namespace IoHelper {


  // Configuration
extern std::istream& is;
extern std::ostream& os;

///
/// Enum type for selecting a GetInt mode
///
enum InputMode;

///
/// Displays a string and gets an int from the console,  using one of two modes
///
int GetInt(const std::string text, const int mode=0);

///
/// Gets an int from the console using regular extraction operators
///
int GetIntStd(const std::string text);

///
/// Gets an int from the console as a string, then converts it and returns it as int
///
int GetIntStrict(const std::string text);

///
/// Gets an int within specified range
///
int GetIntInRange(const std::string text, const int min, const int max, const int mode=0);

///
/// Gets a date from console
///
tm GetDate(const std::string text);

///
/// Gets a character from console
///
char GetChar(const std::string text);

///
/// Gets a line from console
///
std::string GetLine(const std::string text);

///
/// Returns true if the provided string is an integer
///
bool IsInt(const std::string str);
}