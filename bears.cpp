//
// Copyright Ioana Alexandru 2018
//

#include <cstring>
#include "./problem.h"

namespace tema1 {

const int kMod = 1e9 + 7;

bool tema1::Bears::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  N = 0ULL;

  f >> message;

  f.close();
  return true;
}

unsigned int countCarets(const std::string &message) {
  unsigned int count = 0;
  for (char i : message) {
    if (i == '^')
      count++;
  }
  return count;
}

void tema1::Bears::Solve() {
  auto carets = countCarets(message);

  if (carets % 2 != 0 || message.at(0) != '^' ||
      message.at(message.length() - 1) != '^')
    return;  // no valid kaomoji combinations （ㅎ(ｪ)ㅎ）

  auto length = message.length();

  // Creating matrix for DP  (￣(ｴ)￣)・・・
  int kaomoji[length][carets + 1] {};
  // where kaomoji[i][j] = number of faces that can be obtained up to index i
  // considering j 'open' (unpaired) carets

  kaomoji[0][1] = 1;

  int curr_carets = 1;  // current number of carets

  for (unsigned long i = 1; i < length; i++) {
    char c = message.at(i);
    if (c == '^') {
      curr_carets++;
      kaomoji[i][0] = kaomoji[i - 1][1];
    }

    for (auto j = 0; j <= curr_carets; j++) {
      if (c == '^' && j != 0) {
        // We can either consider the new caret as being open (so the faces that
        // can be obtained stay the same) or close any of the open carets
        kaomoji[i][j] = (kaomoji[i - 1][j - 1] +
              (j + 1) * kaomoji[i - 1][j + 1]) % kMod;
      } else if (c == '_'){
        kaomoji[i][j] = (j * kaomoji[i - 1][j]) % kMod;  // _ can be added anywhere
      }
    }
  }

  for (auto i = 0; i < length; i++) {
    for (auto j = 0; j <= carets; j++) {
      if (j == 0)
        std::cout << message.at(i) << "  ";
      std::cout << kaomoji[i][j] << ' ';
    }
    std::cout << std::endl;
  }

  N =  kaomoji[length - 1][0];
  // Done!  ヽ( ˋ(ｴ)´ )ﾉ
}

bool tema1::Bears::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << N;

  /*(*￣(ｴ)￣*)/* Kaomoji bear approves /*(*￣(ｴ)￣*)*/

  f.close();
  return true;
}

}  // namespace tema1
