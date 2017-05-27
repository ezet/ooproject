#include "stdafx.h"
#include "lib\ErrorHandler.h"
#include "model\BaseModel.h"
#include "lib\Console.h"

namespace ErrorHandler {

void DisplayModelErrors(const BaseModel& model) {
  BaseModel::ErrorType errors = model.GetErrors();
  while (errors.first < errors.second)
    Console::PrintLn(*errors.first++);
}

void DisplayError(const std::string& errormsg) {
  Console::PrintLn("Error: " + errormsg);
}

void DisplayWarning(const std::string& warnmsg) {
  Console::PrintLn("Warning: " + warnmsg);
}

};