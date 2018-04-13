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
  sums.clear();

  f >> s >> n >> i;

  f.close();
  return true;
}

void Counting::Solve() {
  std::set<std::multiset<int> > dp[n + 1];
  // dp[i] -> i terms with the sum s

  std::multiset<int> v;
  v.emplace(s);
  dp[1].emplace(v);

  // Saving terms 2..s as a sum of two terms
  std::vector<std::pair<int, int> > split_terms[s + 1];

  for (auto i = 2; i <= s; i++) {
    for (auto j = (int) ceil((double) i / 2); j < i; j++)
    split_terms[i].emplace_back(j, i - j);
  }

  for (auto nr_of_terms = 2; nr_of_terms <= n; nr_of_terms++) {
    auto prev_sums = dp[nr_of_terms - 1];
    for (auto prev_sum : prev_sums) {
      std::set<std::multiset<int> > curr_sums;
      int prev_term = -1;

      for (auto term : prev_sum) {
        if (term == 1 || term == prev_term)
          continue;

        auto term_removed = prev_sum;
        term_removed.erase(term);

        for (auto new_terms : split_terms[term]) {
          auto new_sum = term_removed;

          new_sum.emplace(new_terms.first);
          new_sum.emplace(new_terms.second);

          curr_sums.emplace(new_sum);
        }

        prev_term = term;
      }

      dp[nr_of_terms].insert(curr_sums.begin(), curr_sums.end());
      curr_sums.clear();
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
