#include "stdafx.h"
#include "model\BaseModel.h"
#include "model\Team.h"

///
/// Constructor, default
///
Team::Team() {}

///
/// Constructor, std::string
///
Team::Team(std::string name) {
  name_ = name;
}

///
/// Constructor, std::string, std::string
///
Team::Team(std::string name, std::string address) {
  name_ = name;
  address_ = address;
}

///
/// Destructor
///
Team::~Team() {}

///
/// Mutator for Team::name_
///
void Team::set_name(const std::string name) {
  name_ = name;
}

///
/// Mutator for Team::address_
///
void Team::set_address(const std::string address) {
  address_ = address;
}

///
/// Accessor for Team::name_
///
std::string Team::name() const {
  return name_;
}

///
/// Accessor for Team::address_
///
std::string Team::address() const {
  return address_;
}

///
/// Overloaded equality operator
///
bool Team::operator==(const Team& team) const {
  return !(_stricmp(name_.c_str() , team.name().c_str()));
}

///
/// Overloaded lessthan operator
///
bool Team::operator<(const Team& team) const {
    return _stricmp(name_.c_str() , team.name().c_str()) < 0;
}

///
/// Adds a player to the team
/// @param int id The player ID to add
/// @return An iterator to the player and a bool, true if player was added
///
TCollection<int>::IterBoolPair Team::AddPlayer(const int id) {
  return players_.Add(id);
}

///
/// Gets an iterator that can access all players in the team
/// @return Pair of iterators, .first is the first elem, .second is the last elem
///
TCollection<int>::CollectionPair Team::GetPlayers() const {
  return players_.GetCollection();
}

///
/// Removes a player from the team
/// @param int id ID of the player to remove
/// @return int Number of players removed
///
int Team::RemovePlayer(int id) {
  return players_.Delete(id);
}

///
/// Returns the number of players currently in the team
/// @return int Number of players in the team
///
int Team::NumPlayers() const {
  return players_.Count();
}

///
/// Removes all players from the team
///
void Team::ClearPlayers() {
  players_.Clear();
}

///
/// Performs validation on the model
/// @return bool True if the model is valid
///
bool Team::Validate() {
  Validator v(this);
  v.Inject(name_, "Name").Length(3, 50).Chars(NameChars()).Required();
  v.Inject(address_, "Address").Length(3, 50).Chars(AddrChars());
  return errors().empty();
}

///
/// Returns a string containing valid characters for the name_ attribute
/// @return string A string of valid characters
///
std::string Team::NameChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-\x91\x92\x9B\x9D\x86\x8F ";
}

///
/// Returns a string containing valid characters for the address_ attribute
/// @return string A string of valid characters
///
std::string Team::AddrChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\x91\x92\x9B\x9D\x86\x8F ";
}


///
/// Insertion operator
///
std::ostream& operator<<(std::ostream& os, const Team& team) {
  os << team.name() << '\n' << team.address() << '\n' << team.NumPlayers();
  TCollection<int>::CollectionPair iters = team.GetPlayers();
  for (; iters.first != iters.second; ++iters.first) {
    os << '\n' << *iters.first;
  }
  return os;
}

///
/// Extraction operator
///
std::istream& operator>>(std::istream& is, Team& team) {
  getline(is, team.name_);
  getline(is, team.address_);
  int n;
  is >> n;
  is.ignore();
  for (int i = 0; i < n; ++i) {
    int id;
    is >> id;
    is.ignore();
    team.AddPlayer(id);
  }
  return is;
}