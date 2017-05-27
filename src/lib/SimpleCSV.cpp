#include "stdafx.h"
#include "lib\SimpleCSV.h"
#include <string>
#include <vector>
#include <exception>

SimpleCSV::SimpleCSV() {
  delim_ = ',';
}

SimpleCSV::SimpleCSV(std::string str) {
  delim_ = ',';
  str_ = str;
  Parse();
}

void SimpleCSV::Parse() {
  Explode(std::string(str_));
}

std::string SimpleCSV::operator[](int i) {
  try {
    return csv_.at(i);
  } catch(std::out_of_range& e) {
    // if we're out of range, return an empty string
    //std::cout << e.what();
    e;
    return std::string();
  }
}

void SimpleCSV::Explode(std::string& str) {
  size_t n = str.find_first_of(delim_);
  csv_.push_back(str.substr(0, n));
  str.erase(0, n+1);
  if (!str.empty() && n != std::string::npos) {
    Explode(str);
  }
}