#include "stdafx.h"
#include "lib\pointcalc\Calc3210.h"
#include "model\Match.h"
#include <utility>

Calc3210::Calc3210() {}
Calc3210::~Calc3210() {}

std::pair<int, int> Calc3210::Calculate(const Match& match) const {
  int hpts = Win();
  int gpts = Loss();
  if (match.extended())
    hpts = Extended();
  if (match.home_score() < match.guest_score()) {
    gpts = hpts;
    hpts = Loss();
  } else if (match.home_score() == match.guest_score()) {
    hpts = gpts = Draw();
  }
  return std::make_pair(hpts, gpts);
}

int Calc3210::Win() const { return 3; }
int Calc3210::Draw() const { return 1; }
int Calc3210::Loss() const{ return 0; }
int Calc3210::Extended() const { return 2; }
