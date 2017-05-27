#pragma once
#include "lib\TCollection.h"
#include "model\Sport.h"
#include "model\Team.h"
#include "model\Match.h"
#include <vector>
#include <algorithm>

class PointCalculator;

class Division : public BaseModel {
public:
  typedef std::map<std::string, Match> InnerMatchMap;
  typedef std::map<std::string, InnerMatchMap> OuterMatchMap;
  typedef std::pair<OuterMatchMap::const_iterator, OuterMatchMap::const_iterator> OuterMatchPair;
  typedef std::pair<InnerMatchMap::const_iterator, InnerMatchMap::const_iterator> InnerMatchPair;
  typedef TCollection<Team>::IterBoolPair IterBoolPair;
  typedef std::pair<InnerMatchMap::const_iterator, bool> MatchBoolPair;

  ///
  /// Holds information about a team, used for generating
  /// and displaying division tables.
  ///
  struct TeamData {
    TeamData();
    std::string name_;
    int matches_, wins_, draws_, losses_, points_;
    int goals_, goals_against_;
  };

  ///
  /// Constructor, default
  ///
  Division();

  ///
  /// Constructor: std::string name
  ///
  explicit Division(std::string name);

  ///
  /// Mutator for Division::name_
  ///
  void set_name(std::string name);

  ///
  /// Accessor for Division::name_
  ///
  std::string name() const;

  ///
  /// Add team to Team set
  ///
  IterBoolPair AddTeam(Team& team);

  ///
  /// Find team in Team set
  ///
  IterBoolPair FindTeam(Team& team) const;

  ///
  /// Get collection (elements) of Teams
  ///
  TCollection<Team>::CollectionPair GetTeams() const;

  ///
  /// Delete team in Team set
  ///
  void DeleteTeam(std::set<Team>::iterator iter);

  ///
  /// Get number of teams in Team set
  ///
  int NumTeams() const;

  ///
  /// Find a match in Match map
  ///
  MatchBoolPair FindMatch(Match& match) const;

  ///
  /// Get iterator pair from the outer level of Match map
  ///
  OuterMatchPair GetMatchIters() const;

  ///
  /// Gets an iterator pair for the inner Match map specified by the iterator provided
  ///
  InnerMatchPair GetMapMatches(const OuterMatchMap::const_iterator iter) const;

  ///
  /// Get number of matches in Match map
  ///
  int NumMatches() const;

  ///
  /// Add match to Match map
  ///
  void AddMatch(const Match& match);

  ///
  /// Add result to Match map
  ///
  void AddResult(const Match& match);

  ///
  /// Validates a Match object
  ///
  bool ValidateResult(Match& match) const;

  ///
  /// Generates a table for the division, returns a vector of TeamData objects.
  ///
  std::vector<TeamData> GetTable() const;

  ///
  /// Returns a vector of player IDs in the division sorted desc by amount of goals
  ///
  void GetTopScorers() const;

  ///
  /// Returns a vector of player IDs in given team sorted desc by amount of goals
  ///
  void GetTopScorers(const std::string team) const;

  ///
  /// Overloded equals operator 
  ///
  int operator==(const Division& division) const;

  ///
  /// Overloaded lessthen used by std::set
  ///
  bool operator<(const Division& division) const;

  ///
  /// Attach calculator to Division object
  ///
  void InjectCalculator(PointCalculator *calc);

  ///
  /// Performs validation on the models data
  ///
  virtual bool Validate();



private:
  ///
  /// Functor, compares TeamData objects by TeamData::_points
  ///
  struct ByPoints : public std::binary_function<TeamData, TeamData, bool> {
    bool operator() (const TeamData& x, const TeamData& y) const {
      return x.points_ > y.points_;
    }
  };

  ///
  /// Returns a string containing valid characters for the name_ attribute
  ///
  std::string NameChars();

  ///
  /// Friendly insertion operator for Division
  ///
  friend std::ostream& operator<<(std::ostream& out, const Division& division);

  ///
  /// Friendly extraction operator for Division
  ///
  friend std::istream& operator>>(std::istream& in,  Division& division);

  std::string name_;
  TCollection<Team> teams_;
  std::map< std::string, std::map<std::string, Match> > matches_;
  PointCalculator *calc_;

};