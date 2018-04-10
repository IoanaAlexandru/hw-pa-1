//
// Copyright Ioana Alexandru 2018
//

#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cmath>
#include "./problem.h"

int P,                     // number of tasks
    D,                     // length of a contest
    B,                     // length of break between tasks in a contest
    N;                     // number of contests obtained for minimum total loss
long long L;               // minimum total loss
std::vector<int> lengths;  // length of each task

struct Contest {
  int start, end;          // indices of first and last task in contest
  long long loss;          // loss associated with contest

  long long total_loss;    // total minimum loss from first contest to this one
  int total_contests;      // total number of contests associated with min loss

  Contest(int start, int end, long long loss) : start(start), end(end),
                                                loss(loss), total_loss(loss),
                                                total_contests(1) {}

  void set(long long total_loss, int total_contests) {
    this->total_loss = total_loss;
    this->total_contests = total_contests;
  }
};

bool tema1::Planning::Read(std::string filename) {
  std::ifstream f(filename);

  if (!f.is_open())
    return false;

  f >> P >> D >> B;

  lengths.clear();
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

  for (int i = P; i >= 1; i--) {
    int length = 0;
    for (int j = i; j >= 1; j--) {
      length += lengths[j];

      if (length <= D) {
        if (j == P)
          contests.emplace_back(j, i, 0);
        else
          contests.emplace_back(j, i, pow(D - length, 3));
      } else {
        break;
      }

      length += B;
    }
  }

  for (auto curr = contests.end() - 1; curr >= contests.begin(); curr--) {
    for (auto prev = curr + 1; prev < contests.end(); prev++) {
      if (prev->end + 1 < curr->start)
        break;
      if (prev->end + 1 != curr->start)
        continue;
      if ((curr->total_contests == 1 && curr->start != 1) ||
          curr->loss + prev->total_loss < curr->total_loss)
        curr->set(curr->loss + prev->total_loss, prev->total_contests + 1);
    }
  }

  L = contests[0].total_loss;
  N = contests[0].total_contests;
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
