//
// Created by ioana on 27.03.2018.
//

#include "problem.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>

//Contest structure and sorting methods
struct Contest {
  int games, comics;

  Contest(int games, int comics) : games(games), comics(comics) {}

  bool operator==(const Contest &contest2) {
    return games == contest2.games && comics == contest2.comics;
  }
};

struct more_games {
  inline bool operator()(const Contest &contest1, const Contest &contest2) {
    return contest1.games > contest2.games;
  }
};

struct more_comics {
  inline bool operator()(const Contest &contest1, const Contest &contest2) {
    return contest1.comics > contest2.comics;
  }
};

int N; //number of contests
std::vector<Contest> contests;
int prize_Jon, prize_Sam;

bool tema1::Brothers::Read(std::string filename) {
  std::ifstream f(filename);

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

  return true;
}

Contest Choose(bool Jon_picks) {
  Contest preferred_contest(0, 0);
  int comics_left = 0, games_left = 0;

  for (Contest c : contests) {
    comics_left += c.comics;
    games_left += c.games;
  }

  int max_difference = INT32_MIN;
  for (Contest c : contests) {
    int difference = prize_Jon - prize_Sam;
    if (Jon_picks) {
      difference = difference + c.games/*games_left*/ - comics_left + c.comics;
    } else {
      difference = -difference + c.comics/*comics_left*/ - games_left + c.games;
    }
//      difference = -difference;
//    //Jon: (liked_left - c.games) - (disliked_left - c.comics) = liked_left - disliked_left - (c.games - c.comics)
//    difference = liked_left - disliked_left - difference;

//    Jon: prize_Jon + liked_left - (prize_Sam + disliked_left - c.comics)
//    Sam: prize_Sam + liked_left - (prize_Jon + disliked_left - c.games)

//    Jon: prize_Jon +

    // difference < 0 => absolute value should be as small as possible => value should be as big as possible
    // difference > 0 => value should be as big as possible
    if (difference > max_difference) {
      preferred_contest = c;
      max_difference = difference;
    }
  }

  return preferred_contest;
}

void tema1::Brothers::Solve() {
  bool Jon_picks = true;

  Contest picked_contest(0, 0);

  while (!contests.empty()) {
    picked_contest = Choose(Jon_picks);

    contests.erase(find(contests.begin(), contests.end(), picked_contest));

    if (Jon_picks)
      prize_Jon += picked_contest.games;
    else
      prize_Sam += picked_contest.comics;

    if (Jon_picks)
      std::cout << "Jon: ";
    else
      std::cout << "Sam: ";
    std::cout << picked_contest.games << ' ' << picked_contest.comics << std::endl;

    Jon_picks = not Jon_picks;
  }
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
