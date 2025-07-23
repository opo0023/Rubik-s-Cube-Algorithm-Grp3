#ifndef SOLVER_LBL_H
#define SOLVER_LBL_H

#include "Solver.h"

/*
  Layer-By-Layer (LBL) solver:

    1. White cross
    2. White corners (complete first layer)
    3. Second layer edges
    4. Orient last layer (OLL)
    5. Permute last layer (PLL)

  Each step
    - Looks at the cube (pattern recognition)
    - Apply a small set of known algorithms
    Not shortest solution but straight forward
*/
class SolverLBL : public Solver {
public:
    std::vector<std::string> solve(const Cube &start) override;
};

Solver* getLBLSolver();

#endif 
