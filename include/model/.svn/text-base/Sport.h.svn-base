#pragma once
#include "lib\TCollection.h"
#include "model\BaseModel.h"
#include "lib\pointcalc\PointCalculator.h"
#include "model\Division.h"
#include <string>
#include <set>
#include <utility>
#include <iterator>

// Forward declarations
class Division;

class Sport : public BaseModel {
public: 
  typedef TCollection<Division>::IterBoolPair IterBoolPair;

  ///
  /// Constructor, default
  ///
  Sport();

  ///
  /// Constructor: std::string name
  ///
  explicit Sport(std::string name);

  ///
  /// Constructor: string name, int tabletype
  ///
  explicit Sport(std::string name, int tabletype);

  ///
  /// Destructor
  ///
  virtual ~Sport();

  ///
  /// Mutator for Sport::name_
  ///
  void set_name(std::string name);

  ///
  /// Mutator for Sport::tabletype_
  ///
  void set_tabletype(int type);

  ///
  /// Accessor for Sport::name_
  ///
  std::string name() const;

  ///
  /// Accessor for Sport::tabletype_
  ///
  int tabletype() const;

  ///
  /// Add division to Division set
  ///
  IterBoolPair AddDivision(Division& division);

  ///
  /// Find division in Division set
  ///
  IterBoolPair FindDivision(const Division& div) const;

  ///
  /// Get collection (elements) of Divisions 
  ///
  TCollection<Division>::CollectionPair GetDivisions() const;

  ///
  /// Delete division in Division set
  ///
  void DeleteDivision(std::set<Division>::iterator iter);

  ///
  /// Get number of divisions in Division set
  ///
  int NumDivisions() const;

  ///
  /// Overloded equals operator 
  ///
  int operator==(const Sport &sport) const;

  ///
  /// Overloaded lessthen used by std::set
  ///
  bool operator<(const Sport &sport) const;

  ///
  /// Performs validation on the models data
  ///
  virtual bool Validate();

private:
  ///
  /// Returns a string conntaining valid characters for the name_ attribute
  ///
  std::string NameChars();

  // Friendly input and output operators
  friend std::ostream& operator<<(std::ostream& out, const Sport& sport);
  friend std::istream& operator>>(std::istream& in,  Sport& sport);

  ///
  /// Name of the sport
  ///
  std::string name_;

  ///
  /// A set of all the divisions within the sport
  ///
  TCollection<Division> divisions_;

  ///
  /// The scoremodel used to rate teams
  ///
  PointCalculator::TableType tabletype_;

  ///
  /// An instance of a PointCalculator, used to calculate points based on tabletype
  ///
  PointCalculator *pointcalc_;

};