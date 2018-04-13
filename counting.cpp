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
  sums.clear();

  f >> s >> n >> i;

  f.close();
  return true;
}

void Counting::Solve() {
  std::set<std::multiset<int> > dp[n + 1];

  std::vector<int> v;
  v.push_back(s);
  dp[1].emplace(v);

  for (auto nr_of_terms = 2; nr_of_terms <= n; nr_of_terms++) {
    auto prev_sums = dp[nr_of_terms - 1];
    for (auto prev_sum : prev_sums) {
      for (auto term : prev_sum) {
        std::set<std::multiset<int> > curr_sums;
        std::vector<int> terms;

        for (auto prev_term : prev_sum)
            if (prev_term != term)
              terms.push_back(prev_term);

        for (auto new_term = term / 2; new_term >= 1; new_term--) {
          terms.push_back(new_term);
          terms.push_back(term - new_term);
          curr_sums.emplace(terms);
          terms.pop_back();
          terms.pop_back();
        }

        dp[nr_of_terms].insert(curr_sums.begin(), curr_sums.end());
        curr_sums.clear();
      }
    }
  }

  sums = dp[n];
}

bool Counting::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  if (i >= sums.size()) {
    f << "-";
  } else {
    f << s << '=';
    auto in = 0;
    for (auto sum : sums) {
      if (in == i) {
        for (auto it: sum) {
          f << it;
          if (it != *(--sum.end()))
            f << '+';
        }
        break;
      }
      in++;
    }
  }

  f.close();
  return true;
}

}  // namespace tema1
