#include "stdafx.h"
#include "lib\pointcalc\PointCalculator.h"
#include "lib\pointcalc\Calc210.h"
#include "lib\pointcalc\Calc310.h"
#include "lib\pointcalc\Calc3210.h"

PointCalculator::PointCalculator() {

}

PointCalculator::~PointCalculator() {

}

PointCalculator* PointCalculator::GetCalculator(TableType type) {
  PointCalculator *calc;
  switch (type) {
  case t210: calc = new Calc210; break;
  case t310: calc = new Calc310; break;
  case t3210: calc = new Calc3210; break;
  }
  return calc;
}