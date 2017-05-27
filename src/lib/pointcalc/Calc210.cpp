#include "stdafx.h"
#include "lib\pointcalc\Calc210.h"
#include "model\Match.h"
#include <utility>

Calc210::Calc210() {}
Calc210::~Calc210() {}

std::pair<int, int> Calc210::Calculate(const Match& match) const {
  int hpts = Win();
  int gpts = Loss();
  if (match.home_score() < match.guest_score()) {
    gpts = hpts;
    hpts = Loss();
  } else if (match.home_score() == match.guest_score()) {
    hpts = gpts = Draw();
  }
  return std::make_pair(hpts, gpts);
}

int Calc210::Win() const { return 2; }
int Calc210::Draw() const { return 1; }
int Calc210::Loss() const { return 0; }
int Calc210::Extended() const { return 0; }