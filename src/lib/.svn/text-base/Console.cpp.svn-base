#include "stdafx.h"
#include <iostream>
#include "lib\Command.h"
#include "config.h"

namespace Console {

  enum EventType { key_return };

  void PrintChar(const char ch) {
    std::cout << ch;
  }
  
  void Print(const std::string text) {
    std::cout << text;
  }

  void PrintLn(const std::string text) {
    std::cout << '\n' << text;
  }

  void PrintError(const std::string errormsg) {
    std::cerr << '\n' << errormsg;
  }

  void PrintLog(const std::string logmsg) {
    std::clog << '\n' << logmsg;
  }

  Command Prompt(const std::string prefix, const std::string postfix) {
    PrintLn(prefix + Config::default_prompt);
    std::string cmd;
    getline(std::cin, cmd);
    return Command(cmd);
  }

}