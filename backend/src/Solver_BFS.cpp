#include "Solver.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "Solver_BFS.h"

// Dummy implementation (replace with real logic later)
std::vector<std::string> SolverBFS::solve(const Cube& start) {
    std::cout << "[SolverBFS] Starting BFS solve...\n";

    std::vector<std::string> moves;
    // Add BFS logic here
    // For now, return empty solution
    return moves;
}

Solver* getBFSSolver() {
    return new SolverBFS();
}
class BFSSolver : public Solver {
public:
    std::vector<std::string> solve(const Cube& start) override {
        std::queue<std::pair<Cube, std::vector<std::string>>> q;
        std::unordered_set<std::string> visited;

        q.push({start, {}});
        visited.insert(start.toString());

        while (!q.empty()) {
            auto [current, path] = q.front();
            q.pop();

            if (current.isSolved()) return path;

            for (const auto& move : current.getPossibleMoves()) {
                Cube next = current;
                next.move(move);
                std::string sig = next.toString();
                if (!visited.count(sig)) {
                    visited.insert(sig);
                    auto new_path = path;
                    new_path.push_back(move);
                    q.push({next, new_path});
                }
            }
        }
        return {};
    }
};
