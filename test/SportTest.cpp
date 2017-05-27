#include "stdafx.h"
#include "model\Sport.h"
#include "model\Division.h"
#include "lib\TCollection.h"
#include "lib\IoHelper.h"
#include "lib\Console.h"

void SportTest() {


  TCollection<Sport> sports;
  int table_choice = 1;

  Console::Print("Sports Add() test:");
  std::cout << "\nAdded: " << (sports.Add(Sport("sport1", 1))).second;
  std::cout << "\nCount(): " << sports.Count() << "\n\n";

  TCollection<Sport>::IterBoolPair pair;

  // find sport and add division
  pair = sports.Find(Sport("sport1"));
  const_cast<Sport&>(*pair.first).AddDivision(Division("div1"));

  // find sport and add division
  pair = sports.Find(Sport("sport1"));
  const_cast<Sport&>(*pair.first).AddDivision(Division("div2"));

  Sport sport = *sports.Find(Sport("sport1")).first;
  Console::Print("\n\nDivision test:");
  std::cout << "\nFound Division 1, should be 1: " << sport.FindDivision(Division("div1")).second;
  std::cout << "\nNumDivisions(), should be 2: " << sport.NumDivisions();

  sport.AddDivision(Division("div3"));
  sports.Add(sport);
  std::cout << "\nNumDivisions(), should be 3: " << sport.NumDivisions();
  
};