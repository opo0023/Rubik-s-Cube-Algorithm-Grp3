#ifndef SOLVER_BFS_H
#define SOLVER_BFS_H

#include "Solver.h"
#include <cstddef>

// Breadth-First Search solver (*shortest* solution up to max depth).
class SolverBFS : public Solver {
public:
    explicit SolverBFS(std::size_t maxDepth = 20);
    std::vector<std::string> solve(const Cube &start) override;
private:
    std::size_t maxDepth_;
};

// helper
Solver* getBFSSolver(std::size_t maxDepth = 20);

#endif // SOLVER_BFS_H
