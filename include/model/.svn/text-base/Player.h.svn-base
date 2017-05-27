#pragma once
#include "model\BaseModel.h"
#include <string>

class Player : public BaseModel {
public:
  ///
  /// Constructor, default
  ///
  Player();

  ///
  /// Constructor: int id
  ///
  explicit Player(int id);

  ///
  /// Constructor: std::string name
  ///
  explicit Player(std::string name);

  ///
  /// Constructor: int id, std::string name, std::string address
  ///
  Player(int id, std::string name, std::string address);

  ///
  /// Deconstructor
  ///
  virtual ~Player();

  ///
  /// Mutator for Player::id_
  ///
  void set_id(const int id);

  ///
  /// Mutator for Player::name_
  ///
  void set_name(const std::string& name);

  ///
  /// Mutator for Player::address_
  ///
  void set_address(const std::string& address);

  ///
  /// Accessor for Player::id_
  ///
  int id() const;

  ///
  /// Accessor for Player::name_
  ///
  std::string name() const;

  ///
  /// Accessor for Player::address_
  ///
  std::string address() const;

  ///
  /// Overloaded equals operator
  ///
  bool operator==(const Player& player) const;

  ///
  /// Overloaded lessthan used by std::set
  ///
  bool operator<(const Player& player) const;

  ///
  /// Performs validation on the model
  ///
  virtual bool Validate();

private:
  ///
  /// Returns a string conntaining valid characters for the name_ attribute
  ///
  std::string NameChars();

  ///
  /// Returns a string containing valid characters for the address_ attribute
  ///
  std::string AddrChars();

  // friendly input and output operators
  friend std::istream& operator>>(std::istream& in, Player& s);
  friend std::ostream& operator<<(std::ostream& out, const Player& s);

  ///
  /// A unique ID identifying the player
  ///
  int id_;

  ///
  /// The name of the player
  ///
  std::string name_;

  ///
  /// The address of the player
  ///
  std::string address_;
};