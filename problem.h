//
// Created by ioana on 27.03.2018.
//

#ifndef TEMA1_PROBLEM_H
#define TEMA1_PROBLEM_H

#include <iostream>

namespace tema1 {
  class problem {
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

  class Brothers : public problem {
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };

  class Bears : public problem {
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };

  class Planning : public problem {
  public:
    bool Read(std::string filename) override;

    void Solve() override;

    bool Write(std::string filename) override;
  };
}

#endif //TEMA1_PROBLEM_H
