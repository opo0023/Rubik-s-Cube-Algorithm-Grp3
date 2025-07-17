#ifndef SOLVER_H
#define SOLVER_H

#include "Cube.h"
#include <vector>
#include <string>

class Solver {
public:
    virtual std::vector<std::string> solve(const Cube& scrambled) = 0;
    virtual ~Solver() = default;
};

#endif
