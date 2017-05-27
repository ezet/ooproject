#pragma once
#include "model\BaseModel.h"
#include <sstream>
#include <cctype>

class BaseModel;

class Validator {
public:
  enum ValidatorType { string_length, is_digit, int_range, required, contains_only };

  ///
  /// Constructors and destructor
  ///
  Validator(BaseModel* model);
  virtual ~Validator();

  ///
  /// Injects an int variable and an alias used to referr to the variable
  ///
  Validator& Inject(int var, std::string name);

  ///
  /// Injects a string variable and an alias used to referr to the variable
  ///
  Validator& Inject(std::string var, std::string name);

  ///
  /// Adds an error to the model
  ///
  void AddError(const std::string errormsg) const;

  ///
  /// Sets an error if the variable is considered empty
  ///
  Validator& Required();

  ///
  /// Sets an error if the length of the string is outside provided boundaries
  ///
  Validator& Length(size_t min, size_t max);

  ///
  /// Sets an error if an int is outside the provided limits
  ///
  Validator& InRange(int min, int max);

  ///
  /// Sets an error if a string contains any characters NOT present in the provided
  /// string of characters.
  ///
  Validator& Chars(std::string chars);

  ///
  /// Sets an error if the property is NOT considered alphanumeric
  ///
  Validator& IsAlpha();

  ///
  /// Sets an error if the properpy is NOT considered numeric
  ///
  Validator& IsNumeric();

  ///
  /// Sets an error if the provided function returns false. The function should
  /// accept a single character as its argument, and return a bool value.
  ///
  Validator& IsTrue(bool (*fn)(const char), std::string errormsg);
  

private:
  ///
  /// The currently injected model
  ///
  BaseModel *model_;

  ///
  /// The currently active variable that is being validated
  ///
  std::string var_;

  ///
  /// An alias of the active variable, used in error messages
  ///
  std::string name_;
};