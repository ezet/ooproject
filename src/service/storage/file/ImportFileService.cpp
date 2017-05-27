#include "stdafx.h"
#include "service\storage\file\ImportFileService.h"
#include "Application.h"
#include "model\Player.h"
#include "model\Division.h"
#include "model\Team.h"
#include "lib\ErrorHandler.h"
#include "lib\Console.h"
#include "lib\SimpleCSV.h"
#include <fstream>
#include <string>

///
/// Constructor, default
///
ImportFileService::ImportFileService() {

}

///
/// Constructor, 
///
ImportFileService::ImportFileService(const std::string fname,
  const std::ios::openmode mode)
  : BaseFileService(fname, mode) {

}

///
/// Constructor
///
ImportFileService::ImportFileService(std::fstream& file) : BaseFileService(file) {

}

///
/// Destructor
///
ImportFileService::~ImportFileService() {

}

 
/// 
/// Imports results from a file
///
ImportFileService& ImportFileService::ImportResults(TCollection<Sport>* sports) {
  std::string tmp;
  std::getline(file(), tmp);
  Sport sport(tmp);
  // if sportname is valid
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sportiter = sports->Find(sport);
    // if sport exists
    if (sportiter.second) {
      int numdivisions;
      file() >> numdivisions;
      file().ignore();
      bool error = false;
      for (int i = 0; i < numdivisions && error == false; ++i) {
        std::getline(file(), tmp);
        Division division(tmp);
        // if division name is valid
        if (division.Validate()) {
          TCollection<Division>::IterBoolPair diviter = sportiter.first->FindDivision(division);
          // if division exists
          if (diviter.second) {
            int nummatches;
            file() >> nummatches;
            file().ignore();
            for (int j = 0; j < nummatches; ++j) {
              Match match;
              file() >> match;
              // if match and result is valid, add it
              if (match.Validate() && diviter.first->ValidateResult(match)) {
                const_cast<Division&>(*diviter.first).AddMatch(match);
              } else {
                ErrorHandler::DisplayModelErrors(match);
                error = true;
              }
            }
          } else {
            Console::PrintLn("No such division exists, aborting...");
            error = true;
          }
        } else {
          ErrorHandler::DisplayModelErrors(division);
          error = true;
        }
      }
    } else {
      Console::PrintLn("No such sport exists, aborting...");
    }
  } else {
    ErrorHandler::DisplayModelErrors(sport);
  }
  return *this; 
}

///
/// Imports a division from file
///
ImportFileService& ImportFileService::ImportDivision(Division* division,
                                                     TCollection<Player> *players) {
  int numteams;
  file() >> numteams;
  file().ignore();
  for (int i = 0; i < numteams; ++i) {
    Team team;
    LoadTeam(team, players);
    if (team.Validate())
      division->AddTeam(team);
  }
  Match match;
  while (file() >> match) {
    if (match.Validate())
      division->AddMatch(match);
  }
  return *this; 
}

///
/// Helper function for ImportDivision, reads CSV formatted teamdata from file
///
ImportFileService& ImportFileService::LoadTeam(Team& team, TCollection<Player> *players) {
  std::string tmp;
  std::getline(file(), tmp);
  team.set_name(tmp);
  std::getline(file(), tmp);
  team.set_address(tmp);
  int numplayers;
  file() >> numplayers;
  file().ignore();
  int id;
  for (int i = 0; i < numplayers; ++i) {
    std::getline(file(), tmp);
    SimpleCSV csv(tmp);
    // if entry has a second csv, add it as a new player
    if (!csv[1].empty()) {
      id = Application::GetId();
      players->Add(Player(id, csv[0], csv[1]));
    // else we grab his ID
    } else {
      id = atoi(csv[0].c_str());
    }
    team.AddPlayer(id);
  }
  return *this; 
}