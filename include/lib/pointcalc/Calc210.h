#pragma once
#include "lib\pointcalc\PointCalculator.h"

// forward declarations
class Match;

class Calc210 : public PointCalculator {
public:
  Calc210();
  virtual ~Calc210();

  virtual std::pair<int, int> Calculate(const Match& match) const;

private:
  virtual int Win() const;
  virtual int Draw() const;
  virtual int Loss() const;
  virtual int Extended() const;
};