//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA1_PROBLEM_H
#define TEMA1_PROBLEM_H

#include <iostream>

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
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };

  class Bears : public Problem {
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };

  class Planning : public Problem {
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };
}

#endif // TEMA1_PROBLEM_H
