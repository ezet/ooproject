#include "stdafx.h"
#include "Application.h"
#include "config.h"

// model layer
#include "model\Player.h"
#include "model\Sport.h"
#include "model\Division.h"
#include "model\Team.h"

// persistance layer
#include "service\storage\file\SystemFileService.h"
#include "service\storage\file\ImportFileService.h"
#include "service\storage\file\ExportFileService.h"

// helper libraries
#include "lib\TCollection.h"
#include "lib\Console.h"
#include "lib\IoHelper.h"
#include "lib\ErrorHandler.h"
#include "lib\Command.h"

// standard libraries
#include <iomanip>
#include <sstream>

// using directives
using namespace ErrorHandler;
using std::string;
using std::vector;
using std::ios;
using Console::PrintLn;
using Console::Print;

///
/// Keeps track of the last used ID
///
int Application::last_id_ = 0;

///
/// Constructor, default
///
Application::Application() {
  quit_ = false;
}

///
/// Destructor
///
Application::~Application() {
}


///
/// Prints the menu
///
void Application::PrintMenu() {
  std::cout << "\n\n  S  A(ll) | <id> | <name> - Print player(s)"
    << "\n  I  A(ll) | <name> - Print sport(s)"
    << "\n\n  N  S | I | D - New player, sport or division"
    << "\n  F  S | I | D - Remove player, sport or division"
    << "\n\n  L - Print division schedule to screen or file"
    << "\n  K - Print all matches for specific date to screen or file" 
    << "\n  T - Print the sport or division table(s) to screen or file"
    << "\n  R - Read results from file"
    << "\n  D - Data about all players in a team"
    << "\n  E - Add or remove a player from a team."
    << "\n  C - Print the division or team top 10 list of scorers to screen or file"
    << "\n  H - Help"
    << "\n  Q - Quit";
}

///
/// Initializes the application
///
void Application::Init() {
  PrintLn("Loading players...");
  SystemFileService(Config::player_file).LoadState(&players_).Close();
  // set the last used ID
  if (!players_.Empty()) {
    last_id_ = players_.GetLast().first->id();
  }
  Print("\tdone\nLoading sports...");
  SystemFileService(Config::sport_file).LoadState(&sports_).Close();
  Print("\tdone\n");

}

///
/// Prepares the application for shutdown
///
void Application::Quit() {
  PrintLn("Saving players...");
  SystemFileService(Config::player_file).SaveState(&players_).Close();
  Print("\tdone\nSaving sports...");
  SystemFileService(Config::sport_file).SaveState(&sports_).Close();
  Print("\tdone\nData successfully saved.\n");
  quit_ = true;
}

///
/// Runs the main loop
///
void Application::Run() {
  // 
  PrintMenu();
  while (!quit_) {
    Command command = Console::Prompt();

    // if command syntax is valid we dispatch to the command controller
    if (command.Validate()) {
      Dispatch(command);

      // else we fetch and print the errors
    } else {
      DisplayModelErrors(command);
    }
  }
}

///
/// Dispatches the control to a command action
///
void Application::Dispatch(Command& command) {
  switch(tolower(command.cmd())) {
  case 's': DisplayPlayer(command); break;
  case 'i': DisplaySport(command); break;
  case 'n': NewEntity(command); break;
  case 'f': DeleteEntity(command); break;
  case 'l': WriteSchedule(); break;
  case 'k': WriteResult(); break;
  case 't': WriteTable(); break;
  case 'r': ImportResults(); break;
  case 'd': DisplayTeam(); break;
  case 'e': EditTeam(); break;
  case 'c': TopPlayers(); break;
  case 'h': Help(); break;
  case 'q': Quit(); break;
  default: PrintLn(string("Invalid command: ") + command.cmd());
  }
}

///
/// Helper function to display a Player
///
void Application::PrintPlayer(const Player& player) const {
  std::ostringstream oss;
  oss << "\n\n\t\t\tPlayer ID: " << player.id()
    << "\n\t\t\tName: " << player.name()
    << "\n\t\t\tAddress: " << player.address() << std::endl;
  Console::Print(oss.str());
}

///
/// Helper function to display a Sport
///
void Application::PrintSport(const Sport& sport) const {
  std::ostringstream oss;
  oss << "\n\n\t\t" << sport.name()
    << "\t\tTabletype: ";
  switch(sport.tabletype()) {
  case 1: oss << "2-1-0"; break;
  case 2: oss << "3-1-0"; break;
  case 3: oss << "3-2-1-0"; break;
  }
  oss << "\n\n\t\tDivisions: " << sport.NumDivisions();
  Console::Print(oss.str());
}

///
/// Helper function to display a Divison
///
void Application::PrintDivision(const Division& division) const {
  std::ostringstream oss;
  oss << "\n\n\n\t\t" << division.name()
    << "\t\t\tTeams: " << division.NumTeams();
  Console::Print(oss.str());
}

///
/// Helper function to display a Team
///
void Application::PrintTeam(const Team& team) const {
  std::ostringstream oss;
  oss << "\n\n\t\tTeam: " << team.name()
    << "\n\t\tPlayers: " << team.NumPlayers()
    << "\n\t\tAddress: " << team.address();
  Console::Print(oss.str());
}

///
/// Helper function to display and format a schedule
///
void Application::PrintSchedule(std::vector<Match> matches) const {
  Console::PrintLn("\tDate\tHome\t\t\t\tAway\n\n");
  std::ostringstream oss;
  for (unsigned i = 0; i < matches.size(); i++) {
    oss << '\t' << matches[i].date().substr(6,2) << '/'
      <<  matches[i].date().substr(4,2)
      << '\t' << std::left << std::setw(24) 
      << matches[i].home_team()  << 'v' 
      << "\t" << matches[i].guest_team() << "\n"; 
  }
  Console::Print(oss.str());
}

///
/// Helper function to display and format results
///
void Application::PrintResult(std::vector<Match> matches) const {
  Console::PrintLn("\tDate\tHome\t\t\t\tAway\n\n");
  std::ostringstream oss;
  for (unsigned i = 0; i < matches.size(); i++) {
    oss << '\t' << matches[i].date().substr(6,2) << '/'
      << matches[i].date().substr(4,2)
      << '\t' << std::left << std::setw(24) 
      << matches[i].home_team();
    if (matches[i].HasResult()) {
      oss << matches[i].home_score() << '-' << matches[i].guest_score();
    } else {
      oss << 'v';
    }
    oss  << '\t' << matches[i].guest_team() << "\n"; 
  }
  Console::Print(oss.str());
}

///
/// Helper function to display and format table
///
void Application::PrintTable(const Division& division) const {
  std::vector<Division::TeamData> table = division.GetTable();
  std::vector<Division::TeamData>::const_iterator iter = table.begin();
  std::ostringstream oss;
  oss << "\n " << division.name() 
      << "\n\n" << "#  Team \t\t      W    D    L    PD    PTS\n\n";    
  for (int i = 1; iter != table.end(); ++iter, i++) {
    oss << std::left << std::setw(3) << i 
        << std::left << std::setw(23) << iter->name_  
        << "    " << iter->wins_ << "    " 
        << iter->draws_ << "    " << iter->losses_
        << "    " << iter->goals_ << '-' << iter->goals_against_  
        << "    " << iter->points_ << std::endl;
  }
  Console::Print(oss.str());
}


///
/// Returns the next ID to be used and increment the last_used
///
int Application::GetId() {
  return ++last_id_;
}

///
/// Displays a more descriptive menu
///
void Application::Help() {
  std::cout << "\n\n  S  A - Prints all the players in database"
    << "\n  S <id> - Prints data about player requested by ID"
    << "\n  S <name> - Prints data about player requested by name"
    << "\n\n  I  A - Prints data about all the sports in database"
    << "\n  I <name> - Prints data about sport requested by name"   
    << "\n\n  N S - Add a new player"
    << "\n  N I - Add a new sport"
    << "\n  N D - Add a new division to an existing sport"
    << "\n\n  F S - Remove a player from database"
    << "\n  F I - Remove a sport from database"
    << "\n  F D - Remove a division from a sport"
    << "\n\n  L - Print division schedule to screen or file"
    << "\n  K - Print all matches for specific date to screen or file" 
    << "\n  T - Print the sport or division table(s) to screen or file"
    << "\n  R - Read results from file"
    << "\n  D - Data about all players in a team"
    << "\n  E - Add or remove a player from a team."
    << "\n  C - Print the division or team top 10 list of scorers to screen or file"
    << "\n  H - Help"
    << "\n  Q - Quit";
}

///
/// Displays all or a single player specified by ID or name
///
void Application::DisplayPlayer(Command& cmd) {
  // if argument is empty we print an error message
  if (cmd.arg().empty()) {
    Console::PrintLn("No argument provided." + cmd.arg());

    // if argument is -all, display all the players
  } else if (cmd.arg() == "a" || cmd.arg() == "-a") {
    TCollection<Player>::CollectionPair players;
    players = players_.GetCollection();
    for (; players.first != players.second; ++players.first)
      PrintPlayer(*players.first);
  } else {
    TCollection<Player>::IterBoolPair player;

    // if argument is numeric we search by ID
    if (cmd.NumericArg()) {
      int id = atoi(cmd.arg().c_str());
      player = players_.Find(Player(id));

      // else we search by name
    } else {
      player = players_.FindByName(cmd.arg());
    }

    // if we found something, display the result
    if (player.second) {
      PrintPlayer(*player.first);

    } else {
      Console::PrintLn("Player does not exist.");
    }
  }
}

///
/// Gets the name for and prints a single sport
///
void Application::DisplaySport(Command& cmd) {

  if (cmd.arg().empty()) {
    Console::PrintLn("No argument provided");
    // Prints out all the sports, and number of divisions in each sport
  } else if(cmd.arg() == "-all" || cmd.arg() == "a") {
    TCollection<Sport>::CollectionPair sports;
    sports = sports_.GetCollection();
    if (sports.first == sports.second) {
      PrintLn("No sports in memory.");
    } else {
      for (; sports.first != sports.second; ++sports.first) {
        PrintSport(*sports.first);
      }
    }

  } else { 
    TCollection<Sport>::IterBoolPair sports;
    TCollection<Division>::IterBoolPair division;
    // search for sport
    sports = sports_.FindByName(cmd.arg());
    // sport is found, print all divisions and teams
    if (sports.second) {
      TCollection<Division>::CollectionPair division;
      TCollection<Team>::CollectionPair teams;
      TCollection<int>::CollectionPair players;
      PrintSport(*sports.first);
      if(sports.first->NumDivisions()) {
        division =  sports.first->GetDivisions();
        // iterating through all divisions and prints out each division, and all teams in the division
        for (; division.first != division.second; ++division.first) {
          PrintDivision(*division.first);
          teams = division.first->GetTeams();
          // iterating through all teams and prints out the team and number of players
          for (; teams.first != teams.second; ++teams.first) {
            PrintTeam(*teams.first);
            players = teams.first->GetPlayers();
          }
        }
      } else {
        DisplayError("No divisions are registered.");
      }
    } else {
      DisplayError("Sport does not exist");
    }
  }
}

///
/// Creates a new entity of type Player, Sport, or Division
///
void Application::NewEntity(Command& cmd) {
  std::string arg = cmd.arg();
  if (arg == "s") {
    NewPlayer();
  } else if (arg == "i") {
    NewSport();
  } else if (arg == "d") {
    NewDivision();
  } else {
    DisplayError("Invalid argument: " + arg);
  }
}

///
/// Fetches info for and creates a new player
///
void Application::NewPlayer() {
  //Player player(IoHelper::GetInt("Enter player ID: "));
  Player player(IoHelper::GetLine("Enter player name: "));
  player.set_address(IoHelper::GetLine("Enter player address: "));

  // if the player data is valid we add the player
  if (player.Validate()) {
    player.set_id(Application::GetId());
    TCollection<Player>::IterBoolPair pair;
    pair = players_.Add(player);
    if (pair.second) {
      Console::PrintLn("Player successfully added.");
    } else {
      DisplayError("A player with that ID already exists. Operation aborted.");
    }

    // else we fetch and print the errors
  } else {
    DisplayModelErrors(player);
  }
}

///
/// Fetches info for and creates a new sport
///
void Application::NewSport() {
  std::string sportname = IoHelper::GetLine("Enter sport name: ");
  Console::PrintLn(" Tabletype: \n  1. 2-1-0\n  2. 3-1-0\n  3. 3-2-1-0");
  int choice = IoHelper::GetIntInRange("\n Choice: ", 1, 3);

  Sport sport(sportname,choice);


  // if the sport name is valid we add it
  if  (sport.Validate()) {
    TCollection<Sport>::IterBoolPair pair;
    pair = sports_.Add(sport);

    // if the sport was successfully added, ie. did not already exist
    if (pair.second) {
      Console::PrintLn("Sport successfully added");
    } else {
      DisplayError("Sport already exists. Operation aborted.");
    }

    // if the sport name was invalid, we fetch and print the errors
  } else {
    DisplayModelErrors(sport);
  }
}

///
/// Fetches info for and creates a new division
///
void Application::NewDivision() {
  Sport sport(IoHelper::GetLine("Sport: "));

  // if the sportname is valid we search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sport_pair = sports_.Find(sport);

    // if we find a sport with the given name we ask for a division name
    if (sport_pair.second) {
      Division division(IoHelper::GetLine("Enter division name: "));

      // if the division name is valid, we check if the division exists
      if (division.Validate()) {
        if (!sport_pair.first->FindDivision(division).second) {

          // if the division doesn't exist, we get a filename and load it
          std::string fname = IoHelper::GetLine("Name of file: ");
          ImportFileService(fname).ImportDivision(&division, &players_).Close();
          // and finally add it to the sport
          const_cast<Sport&>(*sport_pair.first).AddDivision(division);
          Console::PrintLn("Division successfully added.");

        } else {
          DisplayError("Division already exists in the sport."); 
        }
      } else {
        DisplayModelErrors(division);
      }
    } else {
      DisplayError("Sport does not exist."); 
    }
  } else {
    DisplayModelErrors(sport);
  }
}

///
/// Helper function to find which entity should be deleted
///
void Application::DeleteEntity(Command &cmd) {
  std::string arg = cmd.arg();
  if (arg == "s") {
    DeletePlayer();
  } else if (arg == "i") {
    DeleteSport();
  } else if (arg == "d") {
    DeleteDivision();
  } else {
    Console::PrintLn("Invalid argument: " + arg);
  }
}

///
/// Gets a player ID and deletes the player
///
void Application::DeletePlayer() {
  Player player(IoHelper::GetInt("Enter player ID: "));

  // search for player ID
  TCollection<Player>::IterBoolPair pair = players_.Find(player);

  // if we found a player, we delete it
  if (pair.second) {
    players_.Delete(*pair.first);
    Console::Print("Player successfully deleted.");
  } else {
    Console::Print("No such player exists. Operation aborted.");
  }
}

///
/// Gets a sport name and deletes the sport
///
void Application::DeleteSport() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));

  // if the sportname is valid, we search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair pair = sports_.Find(sport);

    // if we found a sport, get confirmation and possibly delete it
    if (pair.second) {
      char confirm = IoHelper::GetChar("Do you really want to delete (y/n)?");
      if (confirm == tolower('y')) {
        sports_.Delete(*pair.first);
        Console::PrintLn("Sport successfully deleted.");
      } else {
        Console::PrintLn("Operation aborted.");
      }

      // if we didn't find the sport
    } else {
      Console::PrintLn("No such sport exists. Operation aborted.");
    }

    // if the sportname was invalid, fetch and print any errors
  } else {
    DisplayModelErrors(sport);
  }
}

///
/// Gets a division name and deletes the division
///
void Application::DeleteDivision() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));

  // if the sport name is valid, we search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sport_pair = sports_.Find(sport);
    if (sport_pair.second) {
      Division div(IoHelper::GetLine("Enter division name: "));

      // if the division name valid, we search for it
      if (div.Validate()) {
        TCollection<Division>::IterBoolPair div_pair = sport_pair.first->FindDivision(div);

        // if we found a division, get confirmation and possibly delete it
        if (div_pair.second) {
          char confirm = IoHelper::GetChar("Do you really want to delete (y/n)?");
          if (confirm == tolower('y')) {
            const_cast<Sport&>(*sport_pair.first).DeleteDivision(div_pair.first);
            Console::Print("Division successfully deleted.");
          } else {
            Console::Print("Operation aborted.");
          }

          // if we didn't find the division
        } else {
          Console::Print("No such division exists. Operation aborted.");
        }

        // if the division name was invalid, fetch and print any errors
      } else {
        DisplayModelErrors(div);
      }
    }
  }
}

///
/// Gets a team name and displays all players the team
///
void Application::DisplayTeam() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));

  // if sport name is valid we do a search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sport_pair = sports_.Find(sport);

    // if we found a sport, get a division name
    if (sport_pair.second) {
      Division div(IoHelper::GetLine("Enter division name: "));

      // if the division name is valid we do a search for it
      if (div.Validate()) {
        TCollection<Division>::IterBoolPair div_pair = sport_pair.first->FindDivision(div);

        // if we found a division, get a team name
        if (div_pair.second) {
          Team team(IoHelper::GetLine("Enter team name: "));

          // if the team name is valid, we search for it
          if (team.Validate()) {
            TCollection<Team>::IterBoolPair team_pair = div_pair.first->FindTeam(team);

            // if we found a team, we fetch the player ids
            if (team_pair.second) {
              TCollection<int>::CollectionPair player_ids = team_pair.first->GetPlayers();

              // iterate over the player ids and pass the related player object to a print function
              for (; player_ids.first != player_ids.second; ++player_ids.first) {
                PrintPlayer(*players_.Find(Player(*player_ids.first)).first);
              }
            } else {
              Console::Print("No such team exists, aborting...");
            }
          } else {
            DisplayModelErrors(team);
          }
        } else {
          Console::Print("No such division exists, aborting...");
        }
      } else {
        DisplayModelErrors(div);
      }
    } else {
      Console::Print("No such sport exists, aborting...");
    }
  } else {
    DisplayModelErrors(sport);
  }
}

///
/// Gets a team name and adds or removes a player from the team
///
void Application::EditTeam() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));

  // if sport name is valid we do a search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sport_pair = sports_.Find(sport);

    // if we found a sport, get a division name
    if (sport_pair.second) {
      Division div(IoHelper::GetLine("Enter division name: "));

      // if the division name is valid we do a search for it
      if (div.Validate()) {
        TCollection<Division>::IterBoolPair div_pair = sport_pair.first->FindDivision(div);

        // if we found a division, get a team name
        if (div_pair.second) {
          Team team(IoHelper::GetLine("Enter team name: "));

          // if the team name is valid, we search for it
          if (team.Validate()) {
            TCollection<Team>::IterBoolPair team_pair = div_pair.first->FindTeam(team);

            // if we found a team, ask for add/delete option and a player id
            if (team_pair.second) {
              char cmd = IoHelper::GetChar("Do you wish to add or delete a player (a/d)?");
              int id = IoHelper::GetInt("Enter player ID: ");
              // if player exists
              if (players_.Find(Player(id)).second) {
                // add or remove the player from the team
                if (cmd == 'a') {
                  const_cast<Team&>(*team_pair.first).AddPlayer(id);
                } else if (cmd == 'd'){
                  const_cast<Team&>(*team_pair.first).RemovePlayer(id);
                } else {
                  Console::PrintLn("Invalid argument.");
                }
              } else {
                Console::PrintLn("No player with that ID exists.");
              }
            } else {
              Console::PrintLn("No such team exists, aborting...");
            }
          } else {
            DisplayModelErrors(team);
          }
        } else {
          Console::PrintLn("No such division exists, aborting...");
        }
      } else {
        DisplayModelErrors(div);
      }
    } else {
      Console::PrintLn("No such sport exists, aborting...");
    }
  } else {
    DisplayModelErrors(sport);
  }
} 

///
/// Writes out the schedule for a specified sport and division. (To either file or console)
///
void Application::WriteSchedule() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));
  TCollection<Sport>::IterBoolPair pair = sports_.Find(sport);

  // if we found the sport we search for the specified division
  if(pair.second) {
    Division division(IoHelper::GetLine("Enter division name: "));
    TCollection<Division>::IterBoolPair div_pair = pair.first->FindDivision(division);

    // if we found the division, ask the user to enter a filename or a blank
    if(div_pair.second) {
      std::string fname = IoHelper::GetLine("Print to file or console? (filename / enter): ");

      // fetch and iterate through all matches placing them in a vector
      Division::OuterMatchPair iters = div_pair.first->GetMatchIters();
      std::vector<Match> matches;
      for (; iters.first != iters.second; ++iters.first) {
        Division::InnerMatchPair matchiters = division.GetMapMatches(iters.first);
        for (; matchiters.first != matchiters.second; ++matchiters.first) {
          matches.push_back(matchiters.first->second);
        }
      }

      // sort the vector by date
      std::sort(matches.begin(), matches.end(), Match::DateLess<Match>());

      // if we got a blank line we print to the console
      if (fname.empty()) {
        PrintSchedule(matches);
        // else we write to the specified file
      } else {
        ExportFileService expfs(fname, ios::out);
        expfs.ExportMatchSchedule(matches);
        expfs.Close();
      }
    } else { 
      Console::PrintLn("Division does not exist.");
    } 
  } else {
    Console::PrintLn("Sport does not exist.");
  }
}

///
/// Imports results from a pre-defined file
///
void Application::ImportResults() {
  ImportFileService(Config::results_file).ImportResults(&sports_).Close();
}

///
/// Write all matches given a certain date (with results if any registered)
/// to file or screen
///
void Application::WriteResult() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));
  TCollection<Sport>::IterBoolPair sports = sports_.Find(sport);
  TCollection<Division>::IterBoolPair div_pair;
  Division::OuterMatchPair iters; 
  Division::InnerMatchPair matchiters;
  std::vector<Match> matches;


  // sport exists
  if(sports.second) {
    std::string divname = (IoHelper::GetLine("Divison name / enter: "));
    std::string date = (IoHelper::GetLine("Enter date: "));

    // If a division name is entered, search for it, and
    // add all valid matches to the vector.
    if(!divname.empty()) {
      Division division(divname);
      div_pair = sports.first->FindDivision(division);

      // divisions exists
      if(div_pair.second) {
        iters = div_pair.first->GetMatchIters();
        // iterate through all the matches and add those who match the date in the vector.
        for (; iters.first != iters.second; ++iters.first) {
          matchiters = division.GetMapMatches(iters.first);
          for (; matchiters.first != matchiters.second; ++matchiters.first) {
            if(matchiters.first->second.date() == date) {
              matches.push_back(matchiters.first->second);
            }
          }
        }
      } else {
        Console::PrintLn("Division does not exist");
      }

    } 

    // If the division field was blank, we iterate through all divisions in the sport
    // and add all the matches that is equal to the date specified in the vector
    if (divname.empty()) {
      TCollection<Division>::CollectionPair divisions;
      if(sports.first->NumDivisions()) {
        divisions =  sports.first->GetDivisions();
        // iterate through all the divisions
        for (; divisions.first != divisions.second; ++divisions.first) {
          iters = (*divisions.first).GetMatchIters();
          // get the map containing the matches
          for (; iters.first != iters.second; ++iters.first) {
            matchiters = (*divisions.first).GetMapMatches(iters.first);
            // iterate through all the matches and place them in the vector
            // if the date match the input
            for (; matchiters.first != matchiters.second; ++matchiters.first) {
              if(matchiters.first->second.date() == date) {
                matches.push_back(matchiters.first->second);
              }
            }
          }
        }
      }
    }

    // If division exists or division field was empty we ask for file or console
    if(div_pair.second || divname.empty()) {
      std::string fname = (IoHelper::GetLine("Print to file or console? (filename / enter): "));
      // No filename given, print to screen
      if(fname.empty()) {
        PrintResult(matches);
        // Filename given, print to specified filename
      } else {
        ExportFileService expfs(fname, ios::out);
        expfs.ExportResult(matches);
        expfs.Close();
      }
    }
  } else {
    Console::PrintLn("Sport does not exist");
  }
}

///
/// Prints the table for each division in a sport, or a specified division
///
void Application::WriteTable() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));
  TCollection<Sport>::IterBoolPair sports = sports_.Find(sport);
  TCollection<Division>::IterBoolPair div_pair;

  // sport exists
  if (sports.second) {
    std::string divname = (IoHelper::GetLine("Divison name / enter: "));
    std::string fname = (IoHelper::GetLine("Print to file or console? (filename / enter): "));
    ExportFileService expfs(fname, ios::out);

    // if a division name is entered, search for it, and call
    // the ExportTable or PrintTable function.
    if (!divname.empty()) {
      Division division(divname);
      div_pair = sports.first->FindDivision(division);

      // division exists
      if (div_pair.second) {
        if(fname.empty()) { 
          PrintTable(*div_pair.first);
        } else { 
          expfs.ExportTable(*div_pair.first);
          expfs.Close();
        }
      } else {
        Console::PrintLn("Division does not exist");
      }

      // If the division field was blank, iterate through all the
      // divisions in the sport, and call the ExportTable or PrintTable for each
    } else {
      TCollection<Division>::CollectionPair divisions;
      if(sports.first->NumDivisions()) {
        divisions =  sports.first->GetDivisions();
        for (; divisions.first != divisions.second; ++divisions.first) {
          if(fname.empty()) { 
            PrintTable(*divisions.first);
          } else { 
            expfs.ExportTable(*divisions.first);
            expfs.Close();
          }
        }  
      }
    }

  } else {
    Console::PrintLn("Sport does not exist");
  }
}



void Application::TopPlayers() {
  Sport sport(IoHelper::GetLine("Enter sport name: "));

  // if sport name is valid we do a search for it
  if (sport.Validate()) {
    TCollection<Sport>::IterBoolPair sport_pair = sports_.Find(sport);

    // if we found a sport, get a division name
    if (sport_pair.second) {
      Division div(IoHelper::GetLine("Enter division name: "));

      // if the division name is valid we do a search for it
      if (div.Validate()) {
        TCollection<Division>::IterBoolPair div_pair = sport_pair.first->FindDivision(div);


        // if we found a division, get a team name
        if (div_pair.second) {
          Team team(IoHelper::GetLine("Enter team name: "));
          if (team.name().empty()) {
            div_pair.first->GetTopScorers();

          } else {
            // if the team name is valid, we search for it
            if (team.Validate()) {
              TCollection<Team>::IterBoolPair team_pair = div_pair.first->FindTeam(team);

              // if we found a team, fetch the top players
              if (team_pair.second) {
                div_pair.first->GetTopScorers(team.name());

              } else {
                Console::PrintLn("No such team exists, aborting...");
              }
            } else {
              DisplayModelErrors(team);
            }
          }
        } else {
          Console::PrintLn("No such division exists, aborting...");
        }
      } else {
        DisplayModelErrors(div);
      }
    } else {
      Console::PrintLn("No such sport exists, aborting...");
    }
  } else {
    DisplayModelErrors(sport);
  }
}
