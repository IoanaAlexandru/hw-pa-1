//
// Copyright Ioana Alexandru 2018
//

#include <algorithm>
#include "./problem.h"

namespace tema1 {

// Contest structure and sorting methods
struct Contest {
  int games, comics, sum;
  bool chosen;

  Contest(int games, int comics) :
      games(games), comics(comics), sum(games + comics), chosen(false) {}
};

// Defining operator for default sorting order
bool operator<(const Contest &contest1, const Contest &contest2) {
  if (contest1.sum == contest2.sum)
    return contest1.games > contest2.games;
  return contest1.sum > contest2.sum;
}

bool Brothers::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  prizes.clear();
  prize_Jon = prize_Sam = 0;

  f >> N;
  for (auto i = 0; i < N; i++) {
    int games, comics;
    f >> games >> comics;
    prizes.emplace_back(games, comics);
  }

  f.close();
  return true;
}

void Brothers::Solve() {
  // Creating sorted vector of contests
  std::vector<Contest> contests;
  for (auto p : prizes)
    contests.emplace_back(p.first, p.second);
  std::sort(contests.begin(), contests.end());

  bool Jon_picks{true}; // true if it's Jon's turn to pick a contest
  int max_sum{0};  // biggest sum of prizes among the contests not chosen yet

  // Using iterators that point to the first/last contest in a group with the
  // same (maximum, not chosen yet) sum of presents and the preferred contest
  auto start = contests.begin(), end = contests.begin(),
       picked_contest = contests.begin();

  for (auto i = 0; i < N; i++, Jon_picks = !Jon_picks) {
    // Place start and end iterators if necessary
    if (start == end)
      while (start->chosen)
        start++;

    if (start->sum != max_sum) {
      max_sum = start->sum;
      for (auto c = start; c != contests.end(); c++)
        if (c->sum == max_sum)
          end = c;
        else
          break;
    }

    // Assign contest to brother
    if (start == end) {
      picked_contest = start;
      start++;
      end++;
    } else {
      if (Jon_picks) {
        while (start->chosen)
          start++;
        picked_contest = start++;
      } else {
        while (end->chosen && end != start)
          end--;
        if (!end->chosen) {
          picked_contest = end--;
        } else {
          while (end->chosen)
            end++;
          picked_contest = end;
          start = ++end;
        }
      }
    }

    picked_contest->chosen = true;
    if (Jon_picks)
      prize_Jon += picked_contest->games;
    else
      prize_Sam += picked_contest->comics;
  }
}

bool Brothers::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << prize_Jon << ' ' << prize_Sam;

  f.close();
  return true;
}

}  // namespace tema1
