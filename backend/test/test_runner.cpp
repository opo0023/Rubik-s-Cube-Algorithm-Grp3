#include "Cube.h"
#include "Solver.h"
#include <fstream>
#include <iostream>
#include <sstream>

extern Solver* getBFSSolver();

int main() {
    std::ifstream file("test/test_cases.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Cube cube;
        std::string move;

        while (ss >> move)
            cube.move(move);

        Solver* solver = getBFSSolver();
        auto solution = solver->solve(cube);

        std::cout << "Scrambled: " << line << "\n";
        std::cout << "Solution: ";
        for (const auto& m : solution) std::cout << m << " ";
        std::cout << "\n\n";

        delete solver;
    }

    return 0;
}
