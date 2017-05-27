#pragma once
#include <string>


// Forward declarations
class BaseModel;

namespace ErrorHandler {
  ///
  /// Displays all errors on a model
  ///
  void DisplayModelErrors(const BaseModel& model);

  ///
  /// Displays a single error message
  ///
  void DisplayError(const std::string& errormsg);

  ///
  /// Displays a warning message
  ///
  void DisplayWarning(const std::string& warnmsg);

};