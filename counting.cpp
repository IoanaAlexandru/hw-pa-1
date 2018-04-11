//
// Copyright Ioana Alexandru 2018.
//

#include "./problem.h"

namespace tema1 {

bool Counting::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  sum = "-";

  f >> s >> n >> i;

  f.close();
  return true;
}

void Counting::Solve() {

}

bool Counting::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << sum;

  f.close();
  return true;
}

}  // namespace tema1
