#ifndef SOLVER_BFS_H
#define SOLVER_BFS_H

#include "Solver.h"

class SolverBFS : public Solver {
public:
    std::vector<std::string> solve(const Cube& start) override;
};

// This function is used in main.cpp
Solver* getBFSSolver();

#endif
