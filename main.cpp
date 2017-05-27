/**
 * OOProject
 *
 * author     Lars Kristian Dahl <http://www.krisd.com>
 * version    $Id$  
 * copyright  Copyright (c) Lars Kristian Dahl <http://www.krisd.com>
 * license    http://www.apache.org/licenses/LICENSE-2.0
 */

// Precompiled header
#include "stdafx.h"

#include "Application.h"

// For locale settings
#include <Windows.h>

#include "test\test.h"
// Set to true to enable tests
static const bool DEBUG = 0;

// Tests to run
void RunUnitTests() {
 // FileServiceTest();
 // PlayerTest();
  //IoTest();
  SportTest();
  //DivisionTest();
}


int main(int argc, char* argv[]) { 
  setlocale(LC_ALL, "C");
  _wsetlocale(LC_ALL, L"C");
  SetConsoleOutputCP(850);
  SetConsoleCP(850);

  if (DEBUG) RunUnitTests();

  Application app;
  try {
  app.Init();
  app.Run();
    } catch (std::out_of_range& e) {
    std::cout << "exception";
    std::cout << e.what();
  }

  return 0;
}