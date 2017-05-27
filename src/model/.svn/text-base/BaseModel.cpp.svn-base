#include "stdafx.h"
#include "model\BaseModel.h"
#include <vector>
#include <string>


///
/// Constructor, default
///
BaseModel::BaseModel() {

}


///
/// Destructor
///
BaseModel::~BaseModel() {

}


///
/// Accessor for errors_
///
std::vector<std::string> BaseModel::errors() const {
  return errors_;
}


///
/// Adds an error to the model
///
void BaseModel::AddError(std::string errormsg) {
  errors_.push_back(errormsg);
}


///
/// Returns a pair of iterators to the beginning and end of the set of errors.
///
BaseModel::ErrorType BaseModel::GetErrors() const {
  return make_pair(errors_.begin(), errors_.end());
}

bool BaseModel::HasErrors() const {
  return !errors_.empty();
}