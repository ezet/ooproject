#pragma once
#include "lib\pointcalc\PointCalculator.h"

// forward declarations
class Match;

class Calc3210 : public PointCalculator {
public:
  ///
  /// Constructor, default
  ///
  Calc3210();

  ///
  /// Destructor
  ///
  virtual ~Calc3210();

  ///
  /// Calculates the points for a match, and returns the points in a pair
  /// with values (homescore, guestscore)
  ///
  virtual std::pair<int, int> Calculate(const Match& match) const;

private:
  virtual int Win() const;
  virtual int Draw() const;
  virtual int Loss() const;
  virtual int Extended() const;
};