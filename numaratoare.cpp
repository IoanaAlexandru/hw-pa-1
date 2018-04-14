//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

int main() {
  tema1::Counting problem;

  if (!problem.Read("numaratoare.in")) {
    std::cerr << "Could not open file numaratoare.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("numaratoare.out")) {
    std::cerr << "Could not open file numaratoare.out" << std::endl;
    return -1;
  }

  return 0;
}
