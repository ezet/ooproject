#include "stdafx.h"
#include "service\storage\file\ExportFileService.h"
#include "model\Match.h"
#include "model\Division.h"
#include <algorithm>
#include <iomanip>

///
/// Constructor, default
///
ExportFileService::ExportFileService() {

}

///
/// Constructor
///
ExportFileService::ExportFileService(const std::string fname,
                                     const std::ios::openmode mode)
  : BaseFileService(fname, mode) {
}

///
/// Constructor
///
ExportFileService::ExportFileService(std::fstream& file) : BaseFileService(file) {

}

///
/// Destructor
///
ExportFileService::~ExportFileService() {

}

///
/// Exports a match schedule
///
ExportFileService& ExportFileService::ExportMatchSchedule(const std::vector<Match> matches) {
  file() << "\tDate\tHome\t\t\t\tAway\n\n";
  for (unsigned i = 0; i < matches.size(); i++) {
    file() << '\t' << matches[i].date().substr(6,2) << '/'
           <<  matches[i].date().substr(4,2)
           << '\t' << std::left << std::setw(24) 
           << matches[i].home_team()  << 'v' 
           << '\t' << matches[i].guest_team() << "\n";       
  }
  return *this;
}

///
/// Exports results
///
ExportFileService& ExportFileService::ExportResult(const std::vector<Match> matches) {
  file() << "\tDate\tHome\t\t\t\tAway\n\n";
  for (unsigned i = 0; i < matches.size(); i++) {
    file() << '\t'  << matches[i].date().substr(6,2) << '/'
           <<  matches[i].date().substr(4,2)
           << "\t" << std::left << std::setw(24) 
           << matches[i].home_team(); 

    if(matches[i].HasResult()) {
      file() << matches[i].home_score() << '-' << matches[i].guest_score();
    } else {
      file() << 'v';
    }

    file() << '\t' << matches[i].guest_team() << "\n";  
  }
  return *this;
}

///
/// Exports a division table
///
ExportFileService& ExportFileService::ExportTable(const Division& division) {
  std::vector<Division::TeamData> table = division.GetTable();
  std::vector<Division::TeamData>::const_iterator iter = table.begin();
  file()  << division.name() << "\n\n" 
          << "#  Team \t\t      W    D    L    PD    PTS\n\n";    
  for (int i = 1; iter != table.end(); ++iter, i++) {
    file() << "\t" << std::left << std::setw(3) << i 
           << std::left << std::setw(23) << iter->name_  
           << "    " << iter->wins_ << "    " 
           << iter->draws_ << "    " << iter->losses_
           << "    " << iter->goals_ << '-' << iter->goals_against_  
           << "    " << iter->points_ << std::endl;
  }
  return *this;
}