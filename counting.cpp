//
// Copyright Ioana Alexandru 2018.
//

#include <cmath>
#include "./problem.h"

namespace tema1 {

bool Counting::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  compositions.clear();

  f >> s >> n >> i;

  f.close();
  return true;
}

void Counting::getCompositions(std::vector<int> v, int level) {
  compositions.push_back(v);

  while (true) {
    v[level]--;
    v[level + 1]++;
    if (v[level] >= v[level + 1])
      getCompositions(v, level + 1);
    else
      break;
  }
}

void Counting::Solve() {
  std::vector<int> comp(n, 1);
  comp[0] = s - (n - 1);
  getCompositions(comp, 0);

  for (auto c : compositions) {
    for (auto i  = c.begin(); i < c.end(); i++) {
      std::cout << *i;
      if (i != c.end() - 1)
        std::cout << "+";
    }
    std::cout << std::endl;
  }
}

bool Counting::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  if (i >= compositions.size()) {
    f << "-";
  } else {
    f << s << '=';
    auto comp = compositions.at(i);
    for (auto it = comp.end() - 1; it >= comp.begin(); it--) {
      f << *it;
      if (it != comp.begin())
        f << "+";
    }
  }

  f.close();
  return true;
}

}  // namespace tema1
