#include "stdafx.h"
#include "lib\IoHelper.h"
#include "lib\Console.h"
#include <iostream>
#include <sstream>
#include <ctime>

namespace IoHelper {

// configuration
std::istream& is = std::cin;
std::ostream& os = std::cout;

enum InputMode { std, strict };


int GetInt(const std::string text, const int mode) {
  int n;
  if (mode == 0)
    n = GetIntStd(text);
  else
    n = GetIntStrict(text);
  return n;
}

int GetIntStd(const std::string text) {
  int n;
  do {
    is.clear();
    is.sync();
    os << '\n' << text;
    is >> std::noskipws >> n;
    if (!is)
      os << "\nPlease enter a valid integer.";
  } while (!is);
  is.sync();
  return n;
}

int GetIntStrict(const std::string text) {
  std::string str = GetLine("\n" + text);
  while (!IsInt(str)) {
    os << "\nPlease enter a valid integer.";
    str = GetLine("\n" + text);
  }
  return atoi(str.c_str());
}

int GetIntInRange(const std::string text, const int min, const int max, const int mode) {
  int n = GetInt(text, mode);
  while (n < min || n > max) {
    std::cout << "\nPlease enter a valid integer in the range "
              << min << " - " << max << '.';
    n = GetInt(text, mode);
  }
  return n;
}

tm GetDate(const std::string text) {
  std::string date = GetLine(text);
  return tm();
}

char GetChar(const std::string text) {
  char c;
  do {
    is.clear();
    is.sync();
    os << '\n' << text;
    is >> std::noskipws >> c;
    if (!is)
      os << "\nPlease enter a valid character.";
  } while (!is);
  is.sync();
  return c;
}

std::string GetLine(const std::string text) {
  os << text;
  std::string str;
  is.sync();
  getline(is, str);
  return str;
}

bool IsInt(const std::string str) {
  bool is_int = true;
  for (std::string::const_iterator it = str.begin(); it < str.end(); ++it)
    if (!isdigit(*it))
      is_int = false;
  return is_int;
}

}