//
// Copyright Ioana Alexandru 2018
//

#include "problem.h"

int main() {
  tema1::Brothers problem;

  if (!problem.Read("frati.in")) {
    std::cerr << "Could not open file frati.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("frati.out")) {
    std::cerr << "Could not open file frati.out" << std::endl;
    return -1;
  }

  return 0;
}