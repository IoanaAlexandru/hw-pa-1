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
  partitions.clear();

  f >> s >> n >> i;

  f.close();
  return true;
}

bool order(int first, int second) {
  return first > second;
}

std::vector<std::list<int> > computePartitions(int n, int k, int pre) {
  std::vector<std::list<int> > partitions;
  std::list<int> v;

  if (n <= 0)
    return partitions;

  if (k == 1) {
    if (n <= pre) {
      v.push_back(n);
      partitions.push_back(v);
    }
    return partitions;
  }

  for (auto i = std::min(pre, n); i > 0; i--) {
    for (auto part : computePartitions(n - i, k - 1, i)) {
      v.push_back(i);
      v.merge(part, order);
      partitions.push_back(v);
      v.clear();
    }
  }

  return partitions;
}

void Counting::Solve() {
  partitions = computePartitions(s, n, s);

  for (auto c : partitions) {
    for (auto &i : c) {
      std::cout << i;
      if (&i != &c.back())
        std::cout << "+";
    }
    std::cout << std::endl;
  }
}

bool Counting::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  if (i >= partitions.size()) {
    f << "-";
  } else {
    f << s << '=';
    auto part = partitions.at(i);
    for (auto &it : part) {
      f << it;
      if (&it != &part.back())
        f << "+";
    }
  }

  f.close();
  return true;
}

}  // namespace tema1
