#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

class Cube;

// Generic solver interface
class Solver {
public:
    virtual ~Solver() = default;
    virtual std::vector<std::string> solve(const Cube &start) = 0;
};

#endif
