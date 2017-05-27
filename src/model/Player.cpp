#include "stdafx.h"
#include "model\Player.h"
#include "lib\Validator.h"
#include "lib\SimpleCSV.h"
#include <cctype>

///
/// Constructor, default
///
Player::Player() {
}

///
/// Constructor: int id
///
Player::Player(int id) {
  id_ = id;
}

///
/// Constructor: std::string name
///
Player::Player(std::string name) {
  name_ = name;
}

///
/// Constructor: int id, std::string name, std::string address
///
Player::Player(int id, std::string name, std::string address) {
  id_ = id;
  name_ = name;
  address_ = address;
}

///
/// Deconstructor
///
Player::~Player() {

}

///
/// Mutator for Player::id_
///
void Player::set_id(const int id) {
  id_ = id;
}

///
/// Mutator for Player::name_
///
void Player::set_name(const std::string& name) {
  name_ = name;
}

///
/// Mutator for Player::address_
///
void Player::set_address(const std::string& address) {
  address_ = address;
}

///
/// Accessor for Player::id_
///
int Player::id() const {
  return this->id_;
}

///
/// Accessor for Player::name_
///
std::string Player::name() const {
  return name_;
}

///
/// Accessor for Player::address_
///
std::string Player::address() const {
  return address_;
}

///
/// Overloaded equals operator
///
bool Player::operator==(const Player& player) const {
  return id_ == player.id();
}

///
/// Overloaded lessthan used by std::set
///
bool Player::operator<(const Player& player) const {
  return id_ < player.id();
}

///
/// Performs validation on the model
///
bool Player::Validate() {
  Validator v(this);
  v.Inject(name_, "Name").Length(3, 50).Chars(NameChars()).Required();
  v.Inject(address_, "Address").Length(3, 50).Chars(AddrChars());
  return errors().empty();
}

///
/// Returns a string conntaining valid characters for the name_ attribute
///
std::string Player::NameChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-\x91\x92\x9B\x9D\x86\x8F ";
}

///
/// Returns a string containing valid characters for the address_ attribute
///
std::string Player::AddrChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\x91\x92\x9B\x9D\x86\x8F ";
}

///
/// Friendly extraction operator for Player
///
std::istream& operator>>(std::istream& is, Player& player) {
  std::string tmp;
  std::getline(is, tmp);
  SimpleCSV csv(tmp); 

  bool numeric = true;
  tmp = csv[0];
  for (std::string::iterator it = tmp.begin(); it < tmp.end(); ++it) {
    if (!isdigit(*it)) {
      numeric = false;
      break;
    }
  }
  if (numeric) {
    player.set_id(atoi(tmp.c_str()));
    if (!csv[1].empty())
      player.set_name(csv[1]);
    if (!csv[2].empty())
      player.set_address(csv[2]);
  } else {
    player.set_name(csv[0]);
    if (!csv[1].empty())
      player.set_address(csv[1]);
  }
  return is;
}

///
/// Friendly insertion operator for Player
///
std::ostream& operator<<(std::ostream& os, const Player& player) {
  os << player.id() << ',' << player.name() << ',' << player.address();
  return os;
}