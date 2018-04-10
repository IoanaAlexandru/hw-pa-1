//
// Copyright Ioana Alexandru 2018
//

#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cmath>
#include "./problem.h"

int P, D, B, L, N;
std::vector<int> lengths;

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
  // std::vector<Contest> contests;
  double costs[P + 1][P + 1] = {};

  for (int i = 1; i <= P; i++) {
    int length = 0;
    for (int j = i; j <= P; j++) {
      length += lengths[j];

      if (length <= D) {
        if (j == P)
          costs[i][j] = 0;
        else
          costs[i][j] = pow(D - length, 3);
      } else {
        costs[i][j] = -1;

        length += B;
      }
    }
  }

  int i = 0;

  while (i <= P) {
    double min_cost = INT32_MAX;
    int next_i = i;

    for (int j = i; j <= P; j++) {
      std::cout << costs[i][j] << " ";

      if (costs[i][j] == -1)
        break;

      if (costs[i][j] < min_cost) {
        std::cout << "L = " << L << std::endl;
        min_cost = costs[i][j];
        next_i = j + 1;  // task j was assigned, so j + 1 is next
      }
    }
    std::cout << std::endl;

    L += min_cost;
    N++;
    i = next_i;
  }

  N--;
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
