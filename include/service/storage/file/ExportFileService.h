#pragma once
#include "service\storage\file\BaseFileService.h"
#include "model\Match.h"

// Forward declarations
class Match;
class Division;

///
/// Handles custom file export operations
///
class ExportFileService : public BaseFileService {
public:
  ///
  /// Constructor, default
  ///
  ExportFileService();

  ///
  /// Constructor
  /// @param fstream& file Existing fstream
  ///
  explicit ExportFileService(std::fstream& file);

  ///
  /// Constructor
  /// @param string fname Filename
  /// @param openmode IOS openmode 
  ///
  ExportFileService(const std::string fname,
    const std::ios::openmode=std::ios::out|std::ios::in);

  ///
  /// Destructor
  ///
  virtual ~ExportFileService();

  ///
  /// Exports a match schedule
  /// @param vector<Match> A vector of matches ordered by date
  /// @return ExportFileService& *this for chaining
  ///
  ExportFileService& ExportMatchSchedule(const std::vector<Match> matches);

  ///
  /// Exports results
  /// @param vector<Match> A vector of matches
  /// @return ExportFileService& *this for chaining
  ///
  ExportFileService& ExportResult(const std::vector<Match> matches);

  ///
  /// Exports a division table
  /// @param Divison& division The division to export a table from
  /// @return ExportFileService& *this for chaining
  ///
  ExportFileService& ExportTable(const Division& division);
};