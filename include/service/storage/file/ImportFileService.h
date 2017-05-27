#pragma once
#include "service\storage\file\BaseFileService.h"
#include "lib\TCollection.h"

class Player;
class Sport;
class Division;
class Team;
class Match;

class ImportFileService : public BaseFileService {
public:
  ImportFileService();

  explicit ImportFileService(std::fstream& file);

  ImportFileService(const std::string fname,
                    const std::ios::openmode=std::ios::out|std::ios::in);

  virtual ~ImportFileService();

  ImportFileService& ImportResults(TCollection<Sport> *sports);

  ImportFileService& ImportDivision(Division* division, TCollection<Player> *players);

private:
  ImportFileService& LoadTeam(Team& team, TCollection<Player>* players);
};

