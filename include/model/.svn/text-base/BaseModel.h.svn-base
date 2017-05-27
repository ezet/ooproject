#pragma once
#include "lib\macros.h"
#include <string>
#include <vector>
#include <iterator>
#include <utility>

///
/// Provides an interface and basic methods for all models
///
class BaseModel {
public:
  typedef std::vector<std::string>::const_iterator ErrorIter;
  typedef std::pair<ErrorIter, ErrorIter> ErrorType;

  // Constructors and destructor
  BaseModel();
  virtual ~BaseModel();

  // Validation
  virtual bool Validate() =0;

  ///
  /// Add an error to the model
  ///
  virtual void AddError(std::string errormsg);

  ///
  /// Returns a pair of iterators, (error.begin(), error.end()).
  ///
  ErrorType GetErrors() const;

  ///
  /// Returns true if the model has any errors.
  ///
  bool HasErrors() const;

protected:
  // Accessor for the error vector.
  std::vector<std::string> errors() const;

private:
  ///
  /// A vector of errors, if any
  ///
  std::vector<std::string> errors_;
};