#include "stdafx.h"
#include "service\storage\file\BaseFileService.h"
#include <fstream>

///
/// Constructor, default
///
BaseFileService::BaseFileService() {
  file_ = new std::fstream();
  owner_ = true;
}

///
/// Constructor
///
BaseFileService::BaseFileService(const std::string fname,
  const std::ios::openmode mode) {
    file_ = new std::fstream();
    Open(fname.c_str(), mode);
    owner_ = true;

}

///
/// Constructor
///
BaseFileService::BaseFileService(std::fstream& file) {
  file_ = &file;
  owner_ = false;

}

///
/// Destructor, only deletes fstream if this object created it
///
BaseFileService::~BaseFileService() {
  if (owner_)
    delete file_;
}

///
/// Mutator for BaseFileService::file_
///
void BaseFileService::set_file(std::fstream& file) {
  file_ = &file;
}

///
/// Accessor for BaseFileService::file_
///
std::fstream& BaseFileService::file() {
  return *file_;
}

///
/// Opens a new filestream by string
///
BaseFileService& BaseFileService::Open(const std::string fname,
  const std::ios::openmode mode) {
    return Open(fname.c_str(), mode);
}

///
/// Opens a new filestream by c-array
///
BaseFileService& BaseFileService::Open(const char *fname,
  const std::ios::openmode mode) {
    this->Close();
    file_->open(fname, mode);
    return *this;
}

///
/// Opens a new filestream for output only
///
BaseFileService& BaseFileService::OpenOut(const std::string fname,
  const std::ios::openmode mode) {
    return OpenOut(fname.c_str(), mode);
}

///
/// Opens a new filestream for output only
///
BaseFileService& BaseFileService::OpenOut(const char* fname,
  const std::ios::openmode mode) {
    this->Close();
    file_->open(fname, mode);
    return *this;
}

///
/// Opens a new filestream for input only
///
BaseFileService& BaseFileService::OpenIn(const std::string fname,
  const std::ios::openmode mode) {
    return OpenIn(fname.c_str(), mode);
}

///
/// Opens a new filestream for input only
///
BaseFileService& BaseFileService::OpenIn(const char* fname,
  const std::ios::openmode mode) {
    this->Close();
    file_->open(fname, mode);
    return *this;
}

///
/// Closes the filestream
///
BaseFileService& BaseFileService::Close() {
  if (file_->is_open())
    file_->close();
  return *this;
}