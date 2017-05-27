#include "stdafx.h"
#include "lib\IoHelper.h"
#include "model\Sport.h"
#include "lib\pointcalc\PointCalculator.h"
#include "model\Division.h"
#include "lib\Validator.h"

///
/// Constructor, default
///
Sport::Sport() {
  pointcalc_ = NULL;
}

///
/// Constructor: std::string name
///
Sport::Sport(std::string name) {
  name_ = name;
  pointcalc_ = NULL;
}

///
/// Constructor: string name, int tabletype
///
Sport::Sport(std::string name, int tabletype) {
  name_ = name;
  tabletype_ = (PointCalculator::TableType)tabletype;
  pointcalc_ = PointCalculator::GetCalculator(tabletype_);
}

///
/// Destructor
///
Sport::~Sport() {
}

///
/// Mutator for Sport::name_
///
void Sport::set_name(std::string name) {
  name_ = name;
}

///
/// Mutator for Sport::tabletype_
///
void Sport::set_tabletype(int type) {
  tabletype_ = static_cast<PointCalculator::TableType>(type);
}

///
/// Accessor for Sport::name_
///
std::string Sport::name() const {
  return this->name_;
}

///
/// Accessor for Sport::tabletype_
///
int Sport::tabletype() const {
  return this->tabletype_;
}

///
/// Add division to Division set
///
Sport::IterBoolPair Sport::AddDivision(Division& division) {
  if (pointcalc_ == NULL) {
    pointcalc_ = PointCalculator::GetCalculator(tabletype_);
  }
  division.InjectCalculator(pointcalc_);
  return divisions_.Add(division); 
}

///
/// Find division in Division set
///
Sport::IterBoolPair Sport::FindDivision(const Division& div) const {
  return divisions_.Find(div);
}

///
/// Get collection (elements) of Divisions 
///
TCollection<Division>::CollectionPair Sport::GetDivisions() const {
  return divisions_.GetCollection();
}

///
/// Delete division in Division set
///
void Sport::DeleteDivision(std::set<Division>::iterator iter) {
  divisions_.Delete(iter);
}

///
/// Get number of divisions in Division set
///
int Sport::NumDivisions() const {
  return divisions_.Count();
}

///
/// Overloded equals operator 
///
int Sport::operator==(const Sport& sport) const {
  return !(_stricmp(name_.c_str() , sport.name().c_str()));
}

///
/// Overloaded lessthen used by std::set
///
bool Sport::operator<(const Sport& sport) const {
  return _stricmp(name_.c_str() , sport.name().c_str()) < 0;
}

///
/// Performs validation on the models data
///
bool Sport::Validate() {
  Validator v(this);
  v.Inject(name_, "Name").Length(3, 50).Chars(NameChars()).Required();
  return errors().empty();
}

///
/// Returns a string conntaining valid characters for the name_ attribute
///
std::string Sport::NameChars() {
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- \x91\x92\x9B\x9D\x86\x8F";
}

///
/// Friendly insertion operator for Sport
///
std::ostream& operator<<(std::ostream& os, const Sport& sport) { 
  os << sport.name_ << '\n' << sport.tabletype_ << '\n' << sport.NumDivisions();
  TCollection<Division>::CollectionPair iters = sport.GetDivisions();
  for (; iters.first != iters.second; ++iters.first)
    os << '\n' << *iters.first;
  return os;
}

///
/// Friendly extraction operator for Sport
///
std::istream& operator>>(std::istream& is, Sport& sport) {
  std::getline(is, sport.name_);
  if (!is)
    return is;
  int n;
  is >> n;
  is.ignore();
  sport.set_tabletype(n);
  is >> n;
  is.ignore();
  for (int h = 0; h < n; ++h) {
    Division division;
    is >> division;
    if (division.Validate())
      sport.AddDivision(division);
  }
  return is;
}

