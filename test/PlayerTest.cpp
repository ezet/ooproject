#include "stdafx.h"
#include "model\Player.h"
#include "lib\TCollection.h"

void PlayerTest() {
  //CPlayer players;
  TCollection<Player> players;
  std::pair<std::set<Player>::iterator, bool> stdpair;
  std::set<Player>::iterator iter;

  Player player1(123, "lars", "oklandslio");
  Player player2(123, "lars", "oklandslio");
  Player player3(123, "lars", "oklandslio");

  // Insertion
  stdpair = players.Add(player1);
  std::cout << *(stdpair.first) << (stdpair.second);

  stdpair = players.Add(player1);
  std::cout << *(stdpair.first) << (stdpair.second);

  // Find by ID
  stdpair = players.Find(Player(123));
  std::cout << "\nFound by id: " << *iter;

  stdpair = players.Find(Player(0));
  //std::cout << *iter;

  // Find by name and write to cout
  //players.FindByName("lars")->Write(std::cout);

  // Find by name and write to file
  std::ofstream ofile("test.dat");
  //players.FindByName("lars")->Write(ofile);


  //players.Find("WillFail")->Write(std::cout);
  //std::cout << *iter;

}