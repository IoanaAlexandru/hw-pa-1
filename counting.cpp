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
  int i = 1;

  while (v[level + i - 1] > v[level + i]) {
    v[level]--;
    v[level + i]++;
    if (v[level + i - 1] >= v[level + i])
      getCompositions(v, level + i);
    else {
      i++;
      v[level]++;
      v[level + i - 1]--;
    }
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
    for (auto it = comp.begin(); it < comp.end(); it++) {
      f << *it;
      if (it != comp.end() - 1)
        f << "+";
    }
  }

  f.close();
  return true;
}

}  // namespace tema1
