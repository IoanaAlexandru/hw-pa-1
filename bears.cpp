//
// Copyright Ioana Alexandru 2018
//

#include <cstring>
#include "./problem.h"

namespace tema1 {

const double kMod = 1e9 + 7;

bool tema1::Bears::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  N = 0ULL;

  f >> message;

  f.close();
  return true;
}

void tema1::Bears::Solve() {
}

bool tema1::Bears::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << N;

  f.close();
  return true;
}

}  // namespace tema1
