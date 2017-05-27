#include "stdafx.h"
#include "model\Match.h"
#include "lib\SimpleCSV.h"
#include <iostream>

///
/// Constructor, default
///
Match::Match() {
  home_score_ = -1;
  guest_score_ = -1;
}

///
/// Mutators
///
void Match::set_date(const char date[]) {
  strcpy_s(date_, 9, date);
}

void Match::set_home_team(const std::string team) {
  home_team_ = team;
}

void Match::set_guest_team(const std::string team) {
  guest_team_ = team;
}

void Match::set_home_score(const int score) {
  home_score_ = score;
}

void Match::set_guest_score(const int score) {
  guest_score_ = score;
}

///
/// Accessors
///
std::string Match::date() const {
  return std::string(date_);
}

std::string Match::home_team() const {
  return home_team_;
}

std::string Match::guest_team() const {
  return guest_team_;
}

int Match::home_score() const {
  return home_score_;
}

int Match::guest_score() const {
  return guest_score_;
}

bool Match::extended() const {
  return extended_;
}

///
/// Returns true if the match has a result registered
///
bool Match::HasResult() const {
  return home_score_ > -1 && guest_score_ > -1;
}

Match::GoalScorers Match::GetHomeScorers() const {
  return make_pair(home_scorers_.begin(), home_scorers_.end());
}

Match::GoalScorers Match::GetGuestScorers() const {
  return make_pair(guest_scorers_.begin(), guest_scorers_.end());
}

///
/// Model validation function
///
bool Match::Validate() { return true; }

///
/// Friendly extraction operator for Match
///
std::istream& operator>>(std::istream& is, Match& match) {
  std::string matchstring;
  std::getline(is, matchstring);
  SimpleCSV csv(matchstring);
  strcpy_s(match.date_, 9, csv[0].c_str());
  match.home_team_ = csv[1];
  match.guest_team_ = csv[2];
  if (!csv[3].empty() && !csv[4].empty()) {
    match.home_score_ = atoi(csv[3].c_str());
    match.guest_score_ = atoi(csv[4].c_str());
    int i = 5;
    int j = i + match.home_score_;
    for (; i < j; ++i)
      match.home_scorers_.push_back(atoi(csv[i].c_str()));
    j += match.guest_score_;
    for (; i < j; ++i)
      match.guest_scorers_.push_back(atoi(csv[i].c_str()));
    match.extended_ = !csv[i].empty() && atoi(csv[i].c_str());
  }
  return is;
}

///
/// Friendly insertion operator for Match
///
std::ostream& operator<<(std::ostream& os, const Match& match) {
  os << match.date() << ',' << match.home_team() << ',' << match.guest_team()
    << ',' << match.home_score_ << ',' << match.guest_score_;
  int count = match.home_scorers_.size();
  for (int i = 0; i < count; ++i)
    os << ',' << match.home_scorers_[i];
  count = match.guest_scorers_.size();
  for (int i = 0; i < count; ++i)
    os <<  ',' << match.guest_scorers_[i];
  os << ',' << match.extended_;
  return os;
}