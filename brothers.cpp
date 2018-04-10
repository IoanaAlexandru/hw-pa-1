//
// Copyright Ioana Alexandru 2018
//

#include <set>
#include <algorithm>
#include <fstream>
#include <vector>
#include "./problem.h"

// Contest structure and sorting methods
struct Contest {
  int games, comics, sum;
  bool chosen;

  Contest(int games, int comics) :
          games(games), comics(comics), sum(games + comics), chosen(false) {}

  bool operator==(const Contest &contest2) {
    return games == contest2.games && comics == contest2.comics;
  }
};

// Defining operator for default sorting order
bool operator<(const Contest &contest1, const Contest &contest2) {
  if (contest1.sum == contest2.sum)
    return contest1.games > contest2.games;
  return contest1.sum > contest2.sum;
}

int N;  // number of contests
std::vector<Contest> contests;
int prize_Jon, prize_Sam;

bool tema1::Brothers::Read(std::string filename) {
  std::ifstream f(filename);

  if (!f.is_open())
    return false;

  f >> N;

  contests.clear();

  for (int i = 0; i < N; i++) {
    int games, comics;
    f >> games >> comics;
    contests.emplace_back(games, comics);
  }

  f.close();

  std::sort(contests.begin(), contests.end());

  prize_Jon = prize_Sam = 0;

  return true;
}

void tema1::Brothers::Solve() {
  bool Jon_picks {true};
  // variable true if it's Jon's turn to pick a contest, false if it's Sam's

  auto start = contests.begin(), end = contests.begin();
  // iterators pointing to the first/last contest in a group that has the same
  // (maximum not chosen yet) sum of presents

  auto picked_contest = contests.begin();
  int max_sum {0};

  for (int i = 0; i < N; i++, Jon_picks = !Jon_picks) {
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

bool tema1::Brothers::Write(std::string filename) {
  std::ofstream f(filename);

  if (!f.is_open())
    return false;

  f << prize_Jon << ' ' << prize_Sam;

  f.close();

  return true;
}
