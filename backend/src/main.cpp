#include "Cube.h"
#include "Solver_BFS.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>

int main(){
    std::cout << "Enter scramble moves (space-separated). Empty line = solved cube.\n> ";
    std::string line; std::getline(std::cin, line);

    Cube cube;
    if(!line.empty()){
        std::istringstream ss(line);
        std::string mv;
        while(ss >> mv) cube.move(mv);
    }

    // BFS only (per requirement)
    std::size_t maxDepth = 20;
    std::cout << "Max BFS depth (default 20)? ";
    std::string mdLine; std::getline(std::cin, mdLine);
    if(!mdLine.empty()) maxDepth = static_cast<std::size_t>(std::stoi(mdLine));

    Solver* solver = getBFSSolver(maxDepth);
    auto solution = solver->solve(cube);
    delete solver;

    if(solution.empty() && !cube.isSolved()){
        std::cout << "No solution found within depth " << maxDepth << ".\n";
        return 0;
    }

    std::cout << "Solution (" << solution.size() << " moves): " << join(solution) << "\n";

    cube.applyMoves(solution);
    std::cout << (cube.isSolved() ? "Verified solved!\n" : "NOT solved?!\n");

    // print final 54 characters (e.g., WWWWWWWWWGGGGGGGGG...)
    std::cout << cube.hash() << "\n";

    return 0;
}
