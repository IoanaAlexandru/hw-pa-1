//
// Copyright Ioana Alexandru 2018
//

#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include "./problem.h"

const double kMod = 1e9 + 7;

std::string message;
double N;  // number of possible face combinations

bool tema1::Bears::Read(std::string filename) {
  std::ifstream f;
  f.open(filename);

  if (!f.is_open())
    return false;

  f >> message;
  // message = " " + message;

  f.close();

  N = 0ULL;

  return true;
}

unsigned long factorial(unsigned long n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

unsigned long CountCarets(unsigned long m, unsigned long n) {
  unsigned long carets = 0;

  for (unsigned long i = m; i <= n; i++) {
    if (message.at(i) == '^')
      carets++;
  }

  return carets;
}

void find(std::string substring, int last_char, const std::string &curr_string,
          int &occurences) {
  if (substring == curr_string) {
    occurences++;
    return;
  }

  char next = substring.at(curr_string.length());
  // next char that should be matched

  for (int i = last_char + 1; i < message.length(); i++)
    if (message.at(i) == next)
      find(substring, i, curr_string + next, occurences);
}

void tema1::Bears::Solve() {
  unsigned long msg_len = message.length() - 1;
  unsigned long msg_carets = CountCarets(1, msg_len),
          msg_underscores = msg_len - msg_carets;

  int occurences[msg_underscores + 1], occurence;
  for (int i = 0; i <= msg_underscores; i++) {
    std::string emoticon = "^";
    for (int j = 0; j < i; j++)
      emoticon += "_";
    emoticon += "^";
    occurence = 0;
    find(emoticon, -1, "", occurence);
    occurences[i] = occurence;
  }

  for (int i = 0; i <= msg_underscores; i++)
    std::cout << occurences[i] << " ";
}

bool tema1::Bears::Write(std::string filename) {
  std::ofstream f;
  f.open(filename);

  if (!f.is_open())
    return false;

  f << N << ' ';

  f.close();

  return true;
}
