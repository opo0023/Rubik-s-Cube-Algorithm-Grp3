#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

class Cube;

// Abstract base to allow swapping algorithms if we want to add it later.
class Solver {
public:
    virtual ~Solver() = default;
    virtual std::vector<std::string> solve(const Cube &start) = 0;
};

#endif 
