#pragma once
#include <iostream>
#include <map>
#include "lib\TCollection.h"
#include "model\Player.h"
#include "model\Sport.h"


class Command;
class BaseModel;

class Application {
public:
  // Constructors and deconstructor
  Application();
  ~Application();

  ///
  /// Returns the next ID to be assigned
  /// @return int Next Player ID that can be assigned
  ///
  static int GetId();

  ///
  /// Initiates the application
  ///
  void Init();

  ///
  /// Dispatches control to a function based on the command provided as argument
  /// @param Command& command A command object
  ///
  void Dispatch(Command& command);

  ///
  /// Runs the application control loop
  ///
  void Run();

  ///
  /// Signals the application to exit on the next control loop
  ///
  void Quit();

private:
  ///
  /// Prints the default menu
  ///
  void PrintMenu();

  ///
  /// Helper function to print a Player object
  /// @param Player& player The player to print
  ///
  void PrintPlayer(const Player& player) const;

  ///
  /// Helper function to print a Sport object
  /// @param Sport& sport The sport to print
  ///
  void PrintSport(const Sport& sport) const;

  ///
  /// Helper function to print a Division object
  /// @param Division& division The division to print
  ///
  void PrintDivision(const Division& division) const;

  ///
  /// Helper function to print a Team object
  /// @param Team& team The team to print
  ///
  void PrintTeam(const Team& team) const;

  ///
  /// Helper function to print schedule from a vector of Match objects
  /// @param vector<Match> matches A vector of matches
  ///
  void PrintSchedule(std::vector<Match> matches) const;

  ///
  /// Helper function to print results from a vector of Match objects
  /// @param vector<Match> matches A vector of matches
  ///
  void PrintResult(std::vector<Match> matches) const;
  
  ///
  /// Helper function to print table from a division object
  /// @param Division& division The division containing the table to print
  ///
  void PrintTable(const Division& division) const;

  // Application command functions
  void DisplayPlayer(Command& cmd);
  void DisplaySport(Command& cmd);
  void NewEntity(Command& cmd);
  void NewPlayer();
  void NewSport();
  void NewDivision();
  void DeleteEntity(Command& cmd);
  void DeletePlayer();
  void DeleteSport();
  void DeleteDivision();
  void WriteSchedule();
  void WriteResult();
  void WriteTable();
  void ImportResults();
  void TopPlayers();
  void Help();
  void DisplayTeam();
  void EditTeam();

  ///
  /// defaults to false, application control loop exits if set to true
  ///
  bool quit_;

  ///
  /// holds the last used player ID
  ///
  static int last_id_;

  ///
  /// collection of players
  ///
  TCollection<Player> players_;

  ///
  /// collection of sports
  ///
  TCollection<Sport> sports_;
};