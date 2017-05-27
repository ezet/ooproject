#include "stdafx.h"
#include "lib\pointcalc\Calc310.h"
#include "model\Match.h"
#include <utility>

Calc310::Calc310() {}
Calc310::~Calc310() {}

std::pair<int, int> Calc310::Calculate(const Match& match) const {
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

int Calc310::Win() const { return 3; }
int Calc310::Draw() const { return 1; }
int Calc310::Loss() const { return 0; }
int Calc310::Extended() const { return 0; }