#ifndef SOLVER_H
#define SOLVER_H

#include "Cube.h"
#include <vector>
#include <string>

class Solver {
public:
    virtual ~Solver() = default;
    
    // Pure virtual function that all solvers must implement
    virtual std::vector<std::string> solve(const RubiksCube& cube, int maxDepth = 20) = 0;
    
    // Common utility functions
    virtual std::string getSolverName() const = 0;
    
protected:
    // Helper function to reconstruct path from parent mapping
    std::vector<std::string> reconstructPath(
        const std::string& startHash, 
        const std::string& endHash,
        const std::map<std::string, std::pair<std::string, std::string>>& parents
    );
    
    // Available moves for all solvers
    static const std::vector<std::string> MOVES;
};

#endif // SOLVER_H