#include <iostream>
#include "Problem.h"

int main() {
  tema1::Brothers problem;

  if (!problem.Read("frati.in")) {
    std::cerr << "Could not open file frati.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("frati.out")) {
    std::cerr << "Could not open file frati.in" << std::endl;
    return -1;
  }

  return 0;
}