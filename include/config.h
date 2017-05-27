#pragma once;
#include <vector>
#include <string>


///
/// This namespace holds all configuration options for the application
///
namespace Config {

  enum Interface { console, ncurse, gui };
  enum Storage { plainfile, xml, db };
  extern Interface iface;
  extern Storage storage;

  // default prompt to be displayed in the console
  extern std::string default_prompt;

  // default message to be displayed when application starts
  extern std::string default_welcome;

  // file where player data is stored
  extern std::string player_file;

  // file where sport data is stored
  extern std::string sport_file;

  // file where result data is stored
  extern std::string results_file;

  // case sensitivity settings
  extern bool command_nocase;

  extern bool search_nocase;
}