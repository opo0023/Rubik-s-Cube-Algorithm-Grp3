#include "Cube.h"
#include "Solver_BFS.h"
#include "Solver_LBL.h"
#include "Validator.h"
#include "Utilities.h"

#include <iostream>
#include <sstream>

/*
  HOW IT TAKES INPUT:

  Option 1) Moves line (e.g. "U2 R' F B' L2 D"):
     - Start from a solved cube, apply these moves to scramble it.

  Option 2) 54-character string:
     - Directly describes every sticker.
     - Parse & check if it’s a physically possible cube.

  Then pick BFS (shortest path up to depth) or LBL.
*/

int main(){
    std::cout << "Input type? (1=Moves, 2=54-char state): ";
    std::string t; std::getline(std::cin, t);

    Cube cube;
    if(t == "2"){
        std::cout << "Enter 54-char state:\n> ";
        std::string s54; std::getline(std::cin, s54);
        std::string err;
        if(!parseCubeFromString(s54, cube, err)){
            std::cerr << "Invalid cube: " << err << "\n";
            return 1;
        }
    }else{
        std::cout << "Enter scramble moves (space-separated). Empty line = solved cube.\n> ";
        std::string line; std::getline(std::cin, line);
        std::istringstream ss(line);
        std::string mv;
        while(ss >> mv) cube.move(mv);
    }

    std::cout << "Algorithm? (1=BFS shortest, 2=Layer-by-Layer): ";
    std::string alg; std::getline(std::cin, alg);

    std::vector<std::string> solution;

    if(alg == "2"){
        Solver* s = getLBLSolver();
        solution = s->solve(cube);
        delete s;
        if(solution.empty() && !cube.isSolved()){
            std::cout << "LBL solver didn’t finish. Try BFS.\n";
            return 0;
        }
    }else{
        std::cout << "Max BFS depth (default 20)? ";
        std::string md; std::getline(std::cin, md);
        std::size_t maxDepth = md.empty()?20:static_cast<std::size_t>(std::stoi(md));
        Solver* s = getBFSSolver(maxDepth);
        solution = s->solve(cube);
        delete s;
        if(solution.empty() && !cube.isSolved()){
            std::cout << "No solution found within depth " << maxDepth << ".\n";
            return 0;
        }
    }

    std::cout << "Solution (" << solution.size() << " moves): " << join(solution) << "\n";
    cube.applyMoves(solution);
    std::cout << (cube.isSolved()? "Verified solved!\n" : "NOT solved?!\n");
    std::cout << cube.hash() << "\n";
    return 0;
}
