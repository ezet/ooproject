#pragma once
#include "model\BaseModel.h"
#include <vector>
#include <string>

// Forward declarations
class Team;

class Match : public BaseModel {
public:
  // Functor for sorting by T::date
  template <class T>
  struct DateLess : std::binary_function<T, T, bool> {
    bool operator() (const T& x, const T& y) const {
      return x.date() < y.date();
    }
  };

  typedef std::set<Team>::iterator TeamIter;
  typedef std::vector<int>::const_iterator ScorerIter;
  typedef std::pair<ScorerIter, ScorerIter> GoalScorers;

  ///
  /// Constructor, default
  ///
  Match();

  ///
  /// Mutators
  ///
  void set_date(const char date[]);

  void set_home_team(const std::string team);

  void set_guest_team(const std::string team);

  void set_home_score(const int score);

  void set_guest_score(const int score);

  ///
  /// Accessors
  ///
  std::string date() const;

  std::string home_team() const;

  std::string guest_team() const;

  int home_score() const;

  int guest_score() const;

  bool extended() const;

  ///
  /// Returns true if the match has a result registered
  ///
  bool HasResult() const;

  GoalScorers GetHomeScorers() const;

  GoalScorers GetGuestScorers() const;

  ///
  /// Model validation function
  ///
  virtual bool Validate();

private:

  // friendly input and output operators
  friend std::istream& operator>>(std::istream& in, Match& s);
  friend std::ostream& operator<<(std::ostream& out, const Match& s);

  ///
  /// Match date
  ///
  char date_[9];

  ///
  /// Name of the home team
  ///
  std::string home_team_;
  
  ///
  /// Name of the guest team
  ///
  std::string guest_team_;

  ///
  /// Score for the home team
  ///
  int home_score_;

  ///
  /// Score for the guest team
  ///
  int guest_score_;

  ///
  /// If the match was extended or not
  ///
  bool extended_;

  ///
  /// Ids of the players on the home team who scored
  ///
  std::vector<int> home_scorers_;

  ///
  /// Ids of the players on the home team who scored
  ///
  std::vector<int> guest_scorers_;
};