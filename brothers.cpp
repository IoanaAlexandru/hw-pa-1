//
// Created by ioana on 27.03.2018.
//

#include "Problem.h"
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

  return true;
}

Contest Choose(bool Jon_picks, std::vector<Contest> &most_disliked) {
  Contest preferred_contest(0, 0);

  int max_difference = INT32_MIN;
  for (Contest c : most_disliked) {
    int difference;

    if (c == most_disliked.at(0))
      if (Jon_picks)
        difference = c.games - most_disliked.at(1).comics;
      else
        difference = c.comics - most_disliked.at(1).games;
    else
      if (Jon_picks)
        difference = c.games - most_disliked.at(0).comics;
      else
        difference = c.comics - most_disliked.at(0).games;

    std::cout << "diff = " << difference << std::endl;
    if (difference > max_difference) {
      preferred_contest = c;
      max_difference = difference;
    }
    std::cout << "max diff = " << max_difference << std::endl;
  }

  return preferred_contest;
}

void tema1::Brothers::Solve() {
  bool Jon_picks = true;

  std::vector<Contest> most_games = std::vector<Contest>(contests);
  std::sort(most_games.begin(), most_games.end(), more_games());
  std::vector<Contest> most_comics = std::vector<Contest>(contests);
  std::sort(most_comics.begin(), most_comics.end(), more_comics());

  Contest picked_contest(0, 0);

  while (!most_games.empty()) {
    if (most_games.at(0) == most_comics.at(0)) {
      picked_contest = most_comics.at(0);

      most_comics.erase(most_comics.begin());
      most_games.erase(most_games.begin());
    } else {
      if (Jon_picks)
        picked_contest = Choose(Jon_picks, most_comics);
      else
        picked_contest = Choose(Jon_picks, most_games);

      most_comics.erase(find(most_comics.begin(), most_comics.end(), picked_contest));
      most_games.erase(find(most_games.begin(), most_games.end(), picked_contest));
    }

    if (Jon_picks)
      prize_Jon += picked_contest.games;
    else
      prize_Sam += picked_contest.comics;

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
