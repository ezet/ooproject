#pragma once
#include <fstream>
#include "service\storage\StorageService.h"

// Forward declarations
class BaseModel;

///
/// Provides a simplified interface and some basic methods for interacting with files
///
class BaseFileService : public StorageService {
public:

  ///
  /// Constructor, default
  ///
  BaseFileService();

  ///
  /// Constructor
  /// @param fname Filename
  /// @param openmode IOS openmode
  /// 
  explicit BaseFileService(const std::string fname,
    const std::ios::openmode=std::ios::out|std::ios::in);

  ///
  /// Constructor
  /// @param fstream& file Existing filestream
  ///
  explicit BaseFileService(std::fstream& file);

  ///
  /// Destructor
  ///
  virtual ~BaseFileService();

  ///
  /// Opens a new filestream
  /// @param string fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& Open(const std::string fname,
    const std::ios::openmode=std::ios::out|std::ios::in);

  ///
  /// Opens a new filestream
  /// @param char* fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& Open(const char *fname,
    const std::ios::openmode=std::ios::out|std::ios::in);

  ///
  /// Opens a new filestream for output
  /// @param string fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& OpenOut(const std::string fname,
    const std::ios::openmode=std::ios::out);

  ///
  /// Opens a new filestream for output
  /// @param char* fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& OpenOut(const char *fname,
    const std::ios::openmode=std::ios::out);

  ///
  /// Opens a new filestream for input
  /// @param string fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& OpenIn(const std::string fname,
    const std::ios::openmode=std::ios::in);

  ///
  /// Opens a new filestream for input
  /// @param char* fname Filename
  /// @param openmode IOS openmode
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& OpenIn(const char *fname,
    const std::ios::openmode=std::ios::in);

  ///
  /// Closes the filestream
  /// @return BaseFileService& *this for chaining
  ///
  BaseFileService& Close();

protected:
  ///
  /// Mutator for file_
  /// @param fstream& file The fstream object to set
  ///
  void set_file(std::fstream& file);

  ///
  /// Accessor for file_
  /// @return fstream& The file_ object
  ///
  std::fstream& file() ;

private:
  ///
  /// Filestream owner flag
  ///
  int owner_;
  
  ///
  /// Filestream to operate on
  ///
  std::fstream* file_;
};