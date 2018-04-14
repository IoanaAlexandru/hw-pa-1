//
// Copyright Ioana Alexandru 2018.
//

#include <cmath>
#include <tr1/unordered_map>
#include "./problem.h"

namespace tema1 {

const int kMaxN = 150, kMaxS = 150;

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

static std::vector<std::list<int> > emptyPart;

int hash(int i, int j, int k) {
  return (i * kMaxN + j) * kMaxS + k;
}

std::vector<std::list<int> > computePartitions(int n, int k, int prev,
            std::tr1::unordered_map<int, std::vector<std::list<int> > > memo) {
  std::list<int> v;

  std::vector<std::list<int> > m = memo.find(hash(n, k, prev));
  if (m != memo.end())
    return m;

  if (n <= 0)
    return emptyPart;

  if (k == 1) {
    if (n <= prev) {
      v.push_back(n);
      std::vector<std::list<int> > partitions;
      partitions.emplace_back(v);
      memo.insert(hash(n, k, prev), partitions);
      return partitions;
    }
    return emptyPart;
  }

  std::vector<std::list<int> > partitions;

  for (auto i = std::min(prev, n); i > 0; i--) {
    std::vector<std::list<int> >
        recursive_part = computePartitions(n - i, k - 1, i, memo);

    for (auto part = recursive_part.begin(); part < recursive_part.end();
         part++) {
      (*part).insert((*part).begin(), i);
      partitions.emplace_back(*part);
    }
  }

  getElem(memo, n, k, prev) = partitions;
  return partitions;
}

void Counting::Solve() {
  // use memoization
  std::tr1::unordered_map<int, <std::vector<std::list<int> >>> memo;

  partitions = computePartitions(s, n, s, memo);

//  for (auto c : partitions) {
//    for (auto &i : c) {
//      std::cout << i;
//      if (&i != &c.back())
//        std::cout << "+";
//    }
//    std::cout << std::endl;
//  }
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
