#include "Cube.h"
#include "Solver_BFS.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(){
    std::ifstream file("test/test_cases.txt");
    if(!file){
        std::cerr << "Could not open test/test_cases.txt\n";
        return 1;
    }

    std::string line;
    std::size_t caseNo = 1;
    while(std::getline(file, line)){
        Cube cube;
        std::istringstream ss(line);
        std::string mv;
        while(ss >> mv) cube.move(mv);

        Solver* solver = getBFSSolver(20);
        auto path = solver->solve(cube);
        delete solver;

        std::cout << "Case " << caseNo++ << " scramble: " << line << "\n";
        std::cout << "Solution (" << path.size() << "): " << join(path) << "\n";
        cube.applyMoves(path);
        std::cout << (cube.isSolved() ? "Solved" : "FAILED") << "\n\n";
    }
}
