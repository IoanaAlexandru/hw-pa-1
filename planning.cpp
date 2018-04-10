//
// Copyright Ioana Alexandru 2018
//

#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cmath>
#include "./problem.h"

int P, D, B, N;
long long L;
std::vector<int> lengths;

struct Contest {
  int start, end;
  long long cost;

  Contest(int start, int end, long long cost) : start(start), end(end),
                                                cost(cost) {}
};

struct Result {
  long long cost;
  int contests;
  bool assigned;

  Result(long long cost, bool assigned) : cost(cost), contests(1),
                                          assigned(assigned) {}

  void set(long long cost, int contests, bool assigned) {
    this->cost = cost;
    this->contests = contests;
    this->assigned = assigned;
  }
};

bool tema1::Planning::Read(std::string filename) {
  std::ifstream f(filename);

  if (!f.is_open())
    return false;

  f >> P >> D >> B;

  lengths.push_back(-1);  // virtual element

  for (int i = 0; i < P; i++) {
    int length;
    f >> length;
    lengths.push_back(length);
  }

  f.close();

  L = N = 0;

  return true;
}

void tema1::Planning::Solve() {
  std::vector<Contest> contests;

  for (int i = 1; i <= P; i++) {
    int length = 0;
    for (int j = i; j <= P; j++) {
      length += lengths[j];

      if (length <= D) {
        if (j == P)
          contests.emplace_back(i, j, 0);
        else
          contests.emplace_back(i, j, pow(D - length, 3));
      } else {
        break;
      }

      length += B;
    }
  }

  std::vector<Result> dp;

  for (Contest c : contests)
    dp.emplace_back(c.cost, c.start == 1);

  for (unsigned long i = 1; i < contests.size(); i++) {
    for (unsigned long j = 0; j < i; j++) {
      if (contests.at(j).end + 1 != contests.at(i).start)
        continue;
      if (!dp.at(i).assigned)
        dp.at(i).set(contests.at(i).cost + dp.at(j).cost, dp.at(j).contests + 1,
                     true);
      else if (dp.at(j).cost + contests.at(i).cost < dp.at(i).cost)
        dp.at(i).set(dp.at(j).cost + contests.at(i).cost, dp.at(j).contests + 1,
                     true);
    }
  }

  L = dp.at(dp.size() - 1).cost;
  N = dp.at(dp.size() - 1).contests;
}

bool tema1::Planning::Write(std::string filename) {
  std::ofstream f;
  f.open(filename);

  if (!f.is_open())
    return false;

  f << L << ' ' << N;

  f.close();

  return true;
}
