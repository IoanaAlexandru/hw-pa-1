//
// Created by ioana on 30.03.2018.
//

#include "problem.h"

int main() {
  tema1::Bears problem;

  if (!problem.Read("ursi.in")) {
    std::cerr << "Could not open file ursi.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("ursi.out")) {
    std::cerr << "Could not open file ursi.out" << std::endl;
    return -1;
  }

  return 0;
}
