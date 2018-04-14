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

// Defining an empty partition to avoid wasting time initialising it every time
static std::vector<std::list<int> > emptyPart;

std::vector<std::list<int> > computePartitions(int n, int k, int prev) {
  std::list<int> v;

  if (n <= 0)
    return emptyPart;

  if (k == 1) {
    if (n <= prev) {
      v.push_back(n);
      std::vector<std::list<int> > partitions;
      partitions.emplace_back(v);
      return partitions;
    }
    return emptyPart;
  }

  // Generating partitions recursively
  std::vector<std::list<int> > partitions;

  for (auto i = std::min(prev, n - 1); i > 0; i--) {
    std::vector<std::list<int> >
        recursive_part = computePartitions(n - i, k - 1, i);

    for (auto part = recursive_part.begin(); part < recursive_part.end();
         part++) {
      (*part).insert((*part).begin(), i);
      partitions.emplace_back(*part);
    }
  }

  return partitions;
}

void Counting::Solve() {
  partitions = computePartitions(s, n, s);
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
