#pragma once
#include "lib\TCollection.h"
#include "model\BaseModel.h"
#include "lib\Validator.h"
#include <string>

class Team : public BaseModel {
public:
  typedef TCollection<int>::IterBoolPair IterBoolPair;

  ///
  /// Constructor, default
  ///
  Team();

  ///
  /// Constructor, std::string
  ///
  explicit Team(std::string name);

  ///
  /// Constructor, std::string, std::string
  ///
  Team(std::string name, std::string address);

  ///
  /// Destructor
  ///
  virtual ~Team();

  ///
  /// Mutator for Team::name_
  ///
  void set_name(const std::string name);

  ///
  /// Mutator for Team::address_
  ///
  void set_address(const std::string address);

  ///
  /// Accessor for Team::name_
  ///
  std::string name() const;

  ///
  /// Accessor for Team::address_
  ///
  std::string address() const;

  ///
  /// Overloaded equality operator
  ///
  bool operator==(const Team& team) const;

  ///
  /// Overloaded lessthan operator
  ///
  bool operator<(const Team& team) const;

  ///
  /// Adds a player to the team
  /// @param int id The player ID to add
  /// @return An iterator to the player and a bool, true if player was added
  ///
  TCollection<int>::IterBoolPair AddPlayer(const int id);

  ///
  /// Gets an iterator that can access all players in the team
  /// @return Pair of iterators, .first is the first elem, .second is the last elem
  ///
  TCollection<int>::CollectionPair GetPlayers() const;

  ///
  /// Removes a player from the team
  /// @param int id ID of the player to remove
  /// @return int Number of players removed
  ///
  int RemovePlayer(const int id);

  ///
  /// Returns the number of players currently in the team
  /// @return int Number of players in the team
  ///
  int NumPlayers() const;

  ///
  /// Removes all players from the team
  ///
  void ClearPlayers();

  ///
  /// Performs validation on the model
  /// @return bool True if the model is valid
  ///
  bool Validate();

private:
  ///
  /// Returns a string containing valid characters for the name_ attribute
  /// @return string A string of valid characters
  ///
  std::string NameChars();

  ///
  /// Returns a string containing valid characters for the address_ attribute
  /// @return string A string of valid characters
  ///
  std::string AddrChars();

  ///
  /// Insertion operator
  ///
  friend std::ostream& operator<<(std::ostream& os, const Team& team);

  ///
  /// Extraction operator
  ///
  friend std::istream& operator>>(std::istream& is, Team& team);  

  ///
  /// The name of the team
  ///
  std::string name_;

  ///
  /// The address of the team
  ///
  std::string address_;

  ///
  /// Container with the player IDs of the players in the team
  ///
  TCollection<int> players_;
};