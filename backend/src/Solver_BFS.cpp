#include "Solver.h"
#include <queue>
#include <unordered_set>
#include <map>
#include <iostream>

// Define the static member
const std::vector<std::string> Solver::MOVES = {
    "F", "F'", "U", "U'", "R", "R'", "L", "L'", "B", "B'", "D", "D'"
};

std::vector<std::string> Solver::reconstructPath(
    const std::string& startHash, 
    const std::string& endHash,
    const std::map<std::string, std::pair<std::string, std::string>>& parents
) {
    std::vector<std::string> path;
    std::string current = endHash;
    
    while (current != startHash && parents.find(current) != parents.end()) {
        path.push_back(parents.at(current).second); // the move
        current = parents.at(current).first; // the parent state
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

class BFSSolver : public Solver {
public:
    std::string getSolverName() const override {
        return "BFS";
    }
    
    std::vector<std::string> solve(const RubiksCube& cube, int maxDepth = 20) override {
        if (cube.isSolved()) {
            return {}; // Already solved
        }
        
        std::queue<std::pair<RubiksCube, int>> queue; // cube state and depth
        std::unordered_set<std::string> visited;
        std::map<std::string, std::pair<std::string, std::string>> parents; // state -> (parent_state, move)
        
        std::string startHash = cube.getStateHash();
        queue.push({cube, 0});
        visited.insert(startHash);
        
        int statesExplored = 0;
        
        while (!queue.empty()) {
            auto [currentCube, depth] = queue.front();
            queue.pop();
            
            statesExplored++;
            if (statesExplored % 10000 == 0) {
                std::cout << "Explored " << statesExplored << " states at depth " << depth << std::endl;
            }
            
            // Check depth limit
            if (depth >= maxDepth) {
                continue;
            }
            
            // Try all possible moves
            for (const std::string& move : MOVES) {
                RubiksCube nextCube = currentCube;
                nextCube.applyMove(move);
                
                std::string nextHash = nextCube.getStateHash();
                
                if (nextCube.isSolved()) {
                    // Found solution
                    parents[nextHash] = {currentCube.getStateHash(), move};
                    std::cout << "Solution found! States explored: " << statesExplored << std::endl;
                    return reconstructPath(startHash, nextHash, parents);
                }
                
                if (visited.find(nextHash) == visited.end()) {
                    visited.insert(nextHash);
                    parents[nextHash] = {currentCube.getStateHash(), move};
                    queue.push({nextCube, depth + 1});
                }
            }
            
            // Safety check to prevent infinite loops
            if (statesExplored > 500000) {
                std::cout << "Search space too large, terminating after " << statesExplored << " states..." << std::endl;
                break;
            }
        }
        
        std::cout << "No solution found within depth " << maxDepth << std::endl;
        return {}; // No solution found
    }
};