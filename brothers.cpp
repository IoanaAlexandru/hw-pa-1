//
// Created by ioana on 27.03.2018.
//

#include "problem.h"
#include <vector>
#include <algorithm>
#include <fstream>

//Contest structure and sorting methods
struct Contest {
  int games, comics;

  Contest(int games, int comics) : games(games), comics(comics) {}

  bool operator==(const Contest &contest2) {
    return games == contest2.games && comics == contest2.comics;
  }

  bool operator<(const Contest &contest2) {
    return games + comics < contest2.games + contest2.comics;
  }
};

int N; //number of contests
std::vector<Contest> contests;
int prize_Jon, prize_Sam;

bool tema1::Brothers::Read(std::string filename) {
  std::ifstream f;
  f.open(filename);

  if (!f.is_open())
    return false;

  f >> N;

  for (int i = 0; i < N; i++) {
    int games, comics;
    f >> games >> comics;
    contests.emplace_back(games, comics);
  }

  f.close();

  prize_Jon = prize_Sam = 0;

  std::sort(contests.rbegin(), contests.rend());

  return true;
}

Contest Choose(bool Jon_picks) {
  Contest preferred_contest = contests.at(0);
  int preferred_contest_nr = 0, nr = -1;

  int max_sum = preferred_contest.comics + preferred_contest.games;

  for (Contest c : contests) {
    nr++;

    if (c == contests.at(0))
      continue;
    if (c.comics + c.games == max_sum)
      if (Jon_picks) {
        if (c.games > preferred_contest.games) {
          preferred_contest = c;
          preferred_contest_nr = nr;
        }
      } else {
        if (c.comics > preferred_contest.comics) {
          preferred_contest = c;
          preferred_contest_nr = nr;
        }
      }
    else
      break;
  }

  contests.erase(contests.begin() + preferred_contest_nr);

  return preferred_contest;
}

void tema1::Brothers::Solve() {
  bool Jon_picks = true;

  Contest picked_contest(0, 0);

  while (contests.size() > 1) {
    picked_contest = Choose(Jon_picks);

    //contests.erase(find(contests.begin(), contests.end(), picked_contest));

    if (Jon_picks)
      prize_Jon += picked_contest.games;
    else
      prize_Sam += picked_contest.comics;

    //std::cout << picked_contest.games << ' ' << picked_contest.comics << std::endl;

    Jon_picks = not Jon_picks;
  }

  picked_contest = contests.at(0);

  if (Jon_picks)
    prize_Jon += picked_contest.games;
  else
    prize_Sam += picked_contest.comics;

  std::cout << picked_contest.games << ' ' << picked_contest.comics << std::endl;
}

bool tema1::Brothers::Write(std::string filename) {
  std::ofstream f;
  f.open(filename);

  if (!f.is_open())
    return false;

  f << prize_Jon << ' ' << prize_Sam;

  f.close();

  return true;
}
