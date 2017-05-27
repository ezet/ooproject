#include "stdafx.h"
#include "lib\Validator.h"
#include "model\BaseModel.h"


///
/// Constructor
///
Validator::Validator(BaseModel* model) {
  model_ = model;
}

///
/// Destructor
///
Validator::~Validator() { }


///
/// Injects a variable of type INT and an alias for the variable.
/// Converts the int variable to std::string and passes all arguments
/// to another Inject method that accepts a string variable.
///
Validator& Validator::Inject(int var, std::string name) {
  std::ostringstream oss;
  oss << var;
  return Inject(oss.str(), name);
}


///
/// Injects a variable of type std::string and an alias for the variable,
/// and stores them in the object for later use.
///
Validator& Validator::Inject(std::string var, std::string name) {
  var_ = var;
  name_ = name;
  return *this;
}


///
/// Adds an error message to the currently active model.
///
void Validator::AddError(const std::string errormsg) const {
  model_->AddError(errormsg);
}

///
/// Validator function
/// Adds an error if the variable is an empty string.
///
Validator& Validator::Required() {
  if (var_.empty())
    AddError(name_ + " cannot be empty.");
  return *this;
}

///
/// Validator function
/// Adds an error if the string is shorter or longer than parameters min and max.
///
Validator& Validator::Length(size_t min, size_t max) {
  if (!var_.empty()) {
    if (var_.size() < min || var_.size() > max) {
      std::ostringstream oss;
      oss << name_ << " must be " << min << "-" << max << " characters long.";
      AddError(oss.str());
    }
  }
  return *this;
}

///
/// Validator function
/// Adds an error if the c-builtin isalpha() returns false for any of the
/// characters in the string.
///
Validator& Validator::IsAlpha() {
  if (!var_.empty()) {
    bool is_alpha = true;
    for (std::string::iterator it = var_.begin(); it < var_.end(); ++it) {
      if ((int)*it < 0)
        *it *= -1;
      if (!isalpha(*it))
        is_alpha = false;
    }
    if (!is_alpha)
      AddError(name_ + " must contain valid alphabetic characters.");
  }
  return *this;
}


///
/// Adds an error if the c-builtin isdigit() returns false for any of the 
/// characters in the string.
///
Validator& Validator::IsNumeric() {
  if (!var_.empty()) {
    bool is_numeric = true;
    for (std::string::iterator it = var_.begin(); it < var_.end(); ++it) {
      if ((int)*it < 0)
        *it *= -1;
      if (!isdigit(*it))
        is_numeric = false;
    }
    if (!is_numeric)
      AddError(name_ + " must be a valid number.");
  }
  return *this;
}


///
/// Adds an error with the supplied errormsg if the supplied function *fn 
/// returns false for any of the characters in the string.
///
Validator& Validator::IsTrue(bool (*fn)(const char), std::string errormsg) {
  if (!var_.empty()) {
    bool is_true = true;
    for (std::string::iterator it = var_.begin(); it < var_.end(); ++it) {
      if ((int)*it < 0)
        *it *= -1;
      if (!fn(*it))
        is_true = false;
    }
    if (!is_true)
      AddError(name_ + errormsg);
  }
  return *this;
}

///
/// Adds an error if the validated string contains any character NOT present 
/// in the supplied string.
///
Validator& Validator::Chars(std::string chars) {
  if (!var_.empty()) {
    if (std::string::npos != var_.find_first_not_of(chars))
      AddError(name_ + " cannot contain illegal characters.");
  }
  return *this;
}

///
/// Adds an error if the string, after being converted to an int, is NOT
/// within the range specified by the parameters min and max.
///
Validator& Validator::InRange(int min, int max) {
  if (!var_.empty()) {
    int intvar;
    std::istringstream iss(var_);
    iss >> intvar;
    if (intvar < min || intvar > max) {
      std::ostringstream oss;
      oss << name_ << " must be a value between " << min << " - " << max << ".";
      AddError(oss.str()); 
    }
  }
  return *this;
}