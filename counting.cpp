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

void Counting::Solve() {
  std::vector<int> comp(s + 1, 0);

  auto k = 1, y = s - 1;

  while (k != 0) {
    int x = comp[k - 1] + 1;
    k -= 1;
    while (2 * x <= y) {
      comp[k] = x;
      y -= x;
      k += 1;
    }
    int l = k + 1;
    while (x <= y) {
      comp[k] = x;
      comp[l] = y;

      if (k + 2 == n)
        compositions.emplace_back(comp.begin(), comp.begin() + k + 2);

      x += 1;
      y -= 1;
    }
    comp[k] = x + y;
    y = x + y - 1;

    if (k + 1 == n)
      compositions.emplace_back(comp.begin(), comp.begin() + k + 1);
  }

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
