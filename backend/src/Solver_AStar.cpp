#include "Solver.h"
#include "Utilities.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>

// Node structure for A* search
struct AStarNode {
    Cube cube;
    int gScore; // Cost from start
    int fScore; // gScore + heuristic
    std::string hash;
    std::string moveUsed;
    
    AStarNode(const Cube& c, int g, int f, const std::string& h, const std::string& move = "")
        : cube(c), gScore(g), fScore(f), hash(h), moveUsed(move) {}
    
    // For priority queue (min-heap based on fScore)
    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

std::vector<std::string> AStarSolver::solve(const Cube& cube) {
    // Reset statistics
    nodesExplored = 0;
    
    // If already solved, return empty solution
    if (cube.isSolved()) {
        return {};
    }
    
    // A* data structures
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
    std::unordered_set<std::string> closedSet;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, std::string> moveToReach;
    std::unordered_map<std::string, int> gScores;
    
    // Initialize with starting cube
    std::string startHash = cube.getStateHash();
    int startHeuristic = calculateHeuristic(cube);
    openSet.emplace(cube, 0, startHeuristic, startHash);
    gScores[startHash] = 0;
    parent[startHash] = "";
    
    // Get all possible moves
    std::vector<std::string> possibleMoves = cube.getAllValidMoves();
    
    DebugUtils::debugPrint("Starting A* with max depth: " + std::to_string(maxDepth));
    DebugUtils::debugPrint("Initial heuristic: " + std::to_string(startHeuristic));
    
    while (!openSet.empty()) {
        AStarNode current = openSet.top();
        openSet.pop();
        nodesExplored++;
        
        // Skip if already processed
        if (closedSet.count(current.hash)) {
            continue;
        }
        
        // Add to closed set
        closedSet.insert(current.hash);
        
        // Check depth limit
        if (current.gScore >= maxDepth) {
            continue;
        }
        
        if (DebugUtils::isDebugEnabled() && nodesExplored % 1000 == 0) {
            std::cout << "A* nodes explored: " << nodesExplored 
                      << ", current depth: " << current.gScore 
                      << ", f-score: " << current.fScore << std::endl;
        }
        
        // Try all possible moves
        for (const std::string& move : possibleMoves) {
            Cube nextCube = current.cube;
            
            try {
                nextCube.applyMove(move);
            } catch (const std::exception& e) {
                continue; // Skip invalid moves
            }
            
            std::string nextHash = nextCube.getStateHash();
            
            // Skip if in closed set
            if (closedSet.count(nextHash)) {
                continue;
            }
            
            int tentativeGScore = current.gScore + 1;
            
            // Skip if we found a better path to this state
            if (gScores.count(nextHash) && tentativeGScore >= gScores[nextHash]) {
                continue;
            }
            
            // Record this path
            gScores[nextHash] = tentativeGScore;
            parent[nextHash] = current.hash;
            moveToReach[nextHash] = move;
            
            // Check if solved
            if (nextCube.isSolved()) {
                DebugUtils::debugPrint("Solution found at depth " + std::to_string(tentativeGScore));
                
                // Reconstruct path
                std::vector<std::string> solution;
                std::string currentHash = nextHash;
                
                while (!parent[currentHash].empty()) {
                    solution.push_back(moveToReach[currentHash]);
                    currentHash = parent[currentHash];
                }
                
                std::reverse(solution.begin(), solution.end());
                return solution;
            }
            
            // Calculate heuristic and add to open set
            int heuristic = calculateHeuristic(nextCube);
            int fScore = tentativeGScore + heuristic;
            openSet.emplace(nextCube, tentativeGScore, fScore, nextHash, move);
        }
    }
    
    DebugUtils::debugPrint("A* search exhausted without finding solution");
    return {}; // No solution found
}

int AStarSolver::calculateHeuristic(const Cube& cube) const {
    switch (heuristicType) {
        case 1:
            return misplacedTilesHeuristic(cube);
        case 2:
            return correctFaceletsHeuristic(cube);
        default:
            return misplacedTilesHeuristic(cube);
    }
}

int AStarSolver::misplacedTilesHeuristic(const Cube& cube) const {
    int misplaced = 0;
    
    // Check each face
    auto checkFace = [&](const std::array<char, 9>& face, char expectedColor) {
        for (char c : face) {
            if (c != expectedColor) {
                misplaced++;
            }
        }
    };
    
    checkFace(cube.getYellow(), 'y');
    checkFace(cube.getRed(), 'r');
    checkFace(cube.getWhite(), 'w');
    checkFace(cube.getBlue(), 'b');
    checkFace(cube.getGreen(), 'g');
    checkFace(cube.getOrange(), 'o');
    
    // Divide by 4 since each move affects multiple tiles
    return misplaced / 4;
}

int AStarSolver::correctFaceletsHeuristic(const Cube& cube) const {
    int correct = 0;
    
    // Count correct facelets
    auto countCorrect = [&](const std::array<char, 9>& face, char expectedColor) {
        for (char c : face) {
            if (c == expectedColor) {
                correct++;
            }
        }
    };
    
    countCorrect(cube.getYellow(), 'y');
    countCorrect(cube.getRed(), 'r');
    countCorrect(cube.getWhite(), 'w');
    countCorrect(cube.getBlue(), 'b');
    countCorrect(cube.getGreen(), 'g');
    countCorrect(cube.getOrange(), 'o');
    
    // Return estimate of moves needed (54 total facelets)
    return (54 - correct) / 4;
}