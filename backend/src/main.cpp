#include "Cube.h"
#include "Solver.h"
#include <iostream>

extern Solver* getBFSSolver(); // forward declaration

int main() {
    Cube cube;
    cube.move("F");
    cube.move("R");
    cube.move("U'");

    std::cout << "Scrambled Cube:\n";
    std::cout << cube.toString();

    Solver* solver = getBFSSolver();
    auto solution = solver->solve(cube);

    std::cout << "Solution (" << solution.size() << " moves): ";
    for (const auto& move : solution) std::cout << move << " ";
    std::cout << "\n";

    delete solver;
    return 0;
}