//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

int main() {
  tema1::Planning problem;

  if (!problem.Read("planificare.in")) {
    std::cerr << "Could not open file planificare.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("planificare.out")) {
    std::cerr << "Could not open file planificare.out" << std::endl;
    return -1;
  }

  return 0;
}
