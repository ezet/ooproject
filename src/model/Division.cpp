#include "stdafx.h"
#include "model\Division.h"
#include "lib\TCollection.h"
#include "model\Match.h"
#include "model\Team.h"

///
/// Holds information about a team, used for generating
/// and displaying division tables.
///
Division::TeamData::TeamData() {
  wins_ = draws_ = losses_ = points_ = goals_ = goals_against_ = 0;
}

///
/// Constructor, default
///
Division::Division() {};

///
/// Constructor: std::string name
///
Division::Division(std::string name) {
  name_ = name;
}

///
/// Mutator for Division::name_
///
void Division::set_name(std::string name) {
  name_ = name;
}

///
/// Accessor for Division::name_
///
std::string Division::name() const {
  return name_;
}

///
/// Add team to Team set
///
Division::IterBoolPair Division::AddTeam(Team& team) {
  return teams_.Add(team);
}

///
/// Find team in Team set
///
Division::IterBoolPair Division::FindTeam(Team& team) const {
  return teams_.Find(team);
}

///
/// Get collection (elements) of Teams
///
TCollection<Team>::CollectionPair Division::GetTeams() const {
  return teams_.GetCollection();
}

///
/// Delete team in Team set
///
void Division::DeleteTeam(std::set<Team>::iterator iter) {
  teams_.Delete(iter);
}

///
/// Get number of teams in Team set
///
int Division::NumTeams() const {
  return teams_.Count();
}

///
/// Find a match in Match map. 
///
Division::MatchBoolPair Division::FindMatch(Match& match) const {
  OuterMatchMap::const_iterator outerit = matches_.find(match.home_team());
  InnerMatchMap::const_iterator innerit;
  bool found = false;
  if (outerit != matches_.end()) {
    innerit = outerit->second.find(match.guest_team());
    if (innerit != outerit->second.end()) {
      found = true;
    }
  }
  return make_pair(innerit, found);
}

///
/// Get iterator pair from the outer level of Match map
///
Division::OuterMatchPair Division::GetMatchIters() const {
  return make_pair(matches_.begin(), matches_.end());
}

///
/// Gets an iterator pair for the inner Match map specified by the iterator provided
///
Division::InnerMatchPair Division::GetMapMatches(const OuterMatchMap::const_iterator iter) const {
  return make_pair(iter->second.begin(), iter->second.end());
}

///
/// Get number of matches in Match map
///
int Division::NumMatches() const {
  int size = 0;
  OuterMatchPair iters = GetMatchIters();
  for (; iters.first != iters.second; ++iters.first) {
    size += iters.first->second.size();
  }
  return size;
}

///
/// Add match to Match map
///
void Division::AddMatch(const Match& match) {
  matches_[match.home_team()][match.guest_team()] = match;
}

///
/// Add result to Match map
///
void Division::AddResult(const Match& result) {
  matches_[result.home_team()][result.guest_team()] = result;
}

///
/// Validates a Match object
///
bool Division::ValidateResult(Match& res) const {
  // check that both teams exist, add an error otherwise
  if (!FindTeam(Team(res.home_team())).second)
    res.AddError("Home team does not exist: " + res.home_team());
  if (!FindTeam(Team(res.guest_team())).second)
    res.AddError("Guest team does not exist: " + res.guest_team());
  Division::MatchBoolPair matchiter = FindMatch(res);
  // if we find a Match involving the two teams
  if (matchiter.second) {
    Match match = matchiter.first->second;
    // if the registered date does not match the provided date we add an error
    if (res.date() != match.date()) {
      res.AddError("Invalid match date: " + res.date());
      // if a result is already registered we add an error
    } else if (match.HasResult()) {
      res.AddError("Result is already registered.");
      // if the score in the provided match object is not set (default -1) add an error
    } else if (res.home_score() < 0 || res.guest_score() < 0) {
      res.AddError("Score cannot be less than 0.");
    }
  }
  return !res.HasErrors();
}

///
/// Generates a table for the division, returns a vector of TeamData objects.
/// The function uses a map for collecting the information, since we perform
/// alot of lookups. It then copies it into a vector, sorts it, and returns the
/// vector.
///
std::vector<Division::TeamData> Division::GetTable() const {
  std::map<std::string, TeamData> table;
  OuterMatchPair homeiters = GetMatchIters();
  std::vector<TeamData> tabledata;
  // iterate through all the home teams
  for (; homeiters.first != homeiters.second; ++homeiters.first) {
    std::string hometeam = homeiters.first->first;
    InnerMatchPair guestiters = GetMapMatches(homeiters.first);
    // iterate through all the matches the hometeam has registered
    for (; guestiters.first != guestiters.second; ++guestiters.first) {
      // if the match has a registered result we collect some information
      if (guestiters.first->second.HasResult()) {
        std::pair<int, int> pts = calc_->Calculate(guestiters.first->second);
        std::string guestteam = guestiters.first->first;
        table[hometeam].name_ = hometeam;
        table[hometeam].points_ += pts.first;
        table[hometeam].goals_ += guestiters.first->second.home_score();
        table[hometeam].goals_against_ += guestiters.first->second.guest_score();
        table[guestteam].name_ = guestteam;
        table[guestteam].points_ += pts.second;
        table[guestteam].goals_ += guestiters.first->second.guest_score();
        table[guestteam].goals_against_ += guestiters.first->second.home_score();
        // add to the win/draw/loss stats
        if (pts.first < pts.second) {
          table[hometeam].losses_ += 1;
          table[guestteam].wins_ += 1;
        } else if (pts.first == pts.second) {
          table[hometeam].draws_ += 1;
          table[guestteam].draws_ += 1;
        } else {
          table[hometeam].wins_ += 1;
          table[guestteam].losses_ += 1;
        }
      }
    }
  }
  // push the generated map onto a vector so we can sort it
  std::map<std::string, TeamData>::iterator iter = table.begin();
  for (; iter != table.end(); ++iter) {
    tabledata.push_back(iter->second);
  }
  // sort the vector by points
  std::sort(tabledata.begin(), tabledata.end(), ByPoints());
  return tabledata;
}

///
/// Returns a vector of player IDs sorted desc by amount of goals
///
void Division::GetTopScorers() const {
  std::map<int, int> topscorermap;
  OuterMatchPair homeiters = GetMatchIters();
  for (; homeiters.first != homeiters.second; ++homeiters.first) {
    InnerMatchPair guestiters = GetMapMatches(homeiters.first);
    for (; guestiters.first != guestiters.second; ++guestiters.first) {
      Match::GoalScorers scorers = guestiters.first->second.GetHomeScorers();
      for (; scorers.first < scorers.second; ++scorers.first) {
        topscorermap[*scorers.first] += 1;
      }
      scorers = guestiters.first->second.GetGuestScorers();
      for (; scorers.first < scorers.second; ++scorers.first) {
        topscorermap[*scorers.first] += 1;
      }
    }
  }
  // push the generated map onto a vector so we can sort it
  std::vector<std::pair<int, int> > topscorers;
  std::map<int, int>::iterator iter = topscorermap.begin();
  for (; iter != topscorermap.end(); ++iter) {
    topscorers.push_back(std::make_pair(iter->first, iter->second));
  }
  // sort the vector by player scores
  //std::sort(topscorers.begin(), topscorers.end(), ByPoints());
  //return topscorers;
}

///
/// Returns a vector of player IDs sorted desc by amount of goals
///
void Division::GetTopScorers(const std::string team) const {

}

///
/// Overloded equals operator 
///
int Division::operator==(const Division& division) const {
  return !(_stricmp(name_.c_str() , division.name().c_str()));
}

///
/// Overloaded lessthen used by std::set
///
bool Division::operator<(const Division& division) const {
  return _stricmp(name_.c_str() , division.name().c_str()) < 0;
}

///
/// Attach calculator to Division object
///
void Division::InjectCalculator(PointCalculator *calc) {
  calc_ = calc;
}

///
/// Performs validation on the models data
///
bool Division::Validate() {
  Validator v(this);
  v.Inject(name_, "Name").Length(3, 50).Chars(NameChars()).Required();
  return errors().empty();
}

///
/// Returns a string containing valid characters for the name_ attribute
///
std::string Division::NameChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-\x91\x92\x9B\x9D\x86\x8F ";
}

///
/// Friendly insertion operator for Division
///
std::ostream& operator<<(std::ostream& os, const Division& division) {
  os << division.name_ << '\n' << division.NumTeams() << '\n';
  TCollection<Team>::CollectionPair iters = division.GetTeams();
  for (; iters.first != iters.second; ++iters.first) {
    os << *iters.first << '\n';
  }
  os << division.NumMatches();
  Division::OuterMatchPair teams = division.GetMatchIters();
  for (; teams.first != teams.second; ++teams.first) {
    Division::InnerMatchPair matchiters = division.GetMapMatches(teams.first);
    for (; matchiters.first != matchiters.second; ++matchiters.first){
      os << '\n' << matchiters.first->second;
    }
  }
  return os;
}

///
/// Friendly extraction operator for Division
///
std::istream& operator>>(std::istream& is,  Division& division) {
  std::getline(is, division.name_);
  int n;
  is >> n;
  is.ignore();
  for (int i = 0; i < n; ++i) {
    Team team;
    is >> team;
    if (team.Validate())
      division.AddTeam(team);
  }
  is >> n;
  is.ignore();
  for (int i = 0; i < n; ++i) {
    Match match;
    is >> match;
    if (match.Validate())
      division.AddMatch(match);
  }
  return is;
}