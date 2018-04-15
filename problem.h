//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA1_PROBLEM_H
#define TEMA1_PROBLEM_H

#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <utility>
#include <vector>

namespace tema1 {

class Problem {
 public:
  /*
   * Read data from file.
   */
  virtual bool Read(std::string filename) = 0;

  /*
   * Solve problem.
   */
  virtual void Solve() = 0;

  /*
   * Write solution to file.
   */
  virtual bool Write(std::string filename) = 0;
};

class Brothers : public Problem {
  int prize_Jon, prize_Sam;
 public:
  int N;  // number of contests
  std::vector<std::pair<int, int> > prizes;

  Brothers() : prize_Jon(0), prize_Sam(0), N(0) {}

  int getPrizeJon() { return prize_Jon; }

  int getPrizeSam() { return prize_Sam; }

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Bears : public Problem {
  long long N;  // number of possible face combinations
 public:
  std::string message;

  Bears() : N(0), message("") {}

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Planning : public Problem {
  int N;                     // number of contests for obtained min total loss
  long long L;               // minimum total loss
 public:
  int P,                     // number of tasks
      D,                     // length of a contest
      B;                     // length of break between tasks in a contest
  std::vector<int> lengths;  // length of each task

  Planning() : N(0), L(0), P(0), D(0), B(0), lengths() {}

  int getN() { return N; }

  long long getL() { return L; }

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Counting : public Problem {
  std::vector<std::list<int> > partitions;
 public:
  unsigned int s, n, i;

  Counting() : partitions(), s(0), n(0), i(0) {}

  std::vector<std::list<int> > getPartitions() { return partitions; }

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

}  // namespace tema1

#endif // TEMA1_PROBLEM_H
